/*
 * [The "BSD license"]
 *  Copyright (c) 2012 Terence Parr
 *  Copyright (c) 2012 Sam Harwell
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 *  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Antlr 4 C++ Runtime
 * Gael Hatchue
 */

#include <antlr/misc/IntervalSet.h>
#include <antlr/misc/MurmurHash.h>
#include <antlr/Lexer.h>
#include <antlr/Token.h>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <typeinfo>

namespace antlr4 {
namespace misc {

const IntervalSet IntervalSet::COMPLETE_CHAR_SET = IntervalSet::of(0, Lexer::MAX_CHAR_VALUE);
const IntervalSet IntervalSet::EMPTY_SET = IntervalSet();

IntervalSet::IntervalSet(const std::list<Interval>& intervals)
    :   intervals(intervals.begin(), intervals.end()),
        readonly(false)
{
}

IntervalSet::IntervalSet(const IntervalSet& set)
    :   Key<IntSet>(),
        IntSet(),
        intervals(set.intervals),
        readonly(set.readonly)
{
}

IntervalSet::IntervalSet(const IntervalSet* set)
    :   readonly(false)
{
    intervals.reserve(2);
    addAll(set);
}

IntervalSet::IntervalSet()
    :   readonly(false)
{
    intervals.reserve(2);
}

IntervalSet::IntervalSet(antlr_int32_t el)
    :   readonly(false)
{
    intervals.reserve(1);
    add(el);
}

IntervalSet::IntervalSet(antlr_int32_t e1, antlr_int32_t e2)
    :   readonly(false)
{
    intervals.reserve(2);
    add(e1);
    add(e2);
}

/** Create a set with a single element, el. */
IntervalSet IntervalSet::of(antlr_int32_t a)
{
    IntervalSet s;
    s.add(a);
    return s;
}

/** Create a set with all ints within range [a..b] (inclusive) */
IntervalSet IntervalSet::of(antlr_int32_t a, antlr_int32_t b)
{
    IntervalSet s;
    s.add(a,b);
    return s;
}

void IntervalSet::clear()
{
    if ( readonly ) throw std::logic_error("can't alter readonly IntervalSet");
    intervals.clear();
}

/** Add a single element to the set.  An isolated element is stored
 *  as a range el..el.
 */
void IntervalSet::add(antlr_int32_t el)
{
    if ( readonly ) throw std::logic_error("can't alter readonly IntervalSet");
    add(el,el);
}

/** Add interval; i.e., add all integers from a to b to set.
 *  If b<a, do nothing.
 *  Keep list in sorted order (by left range value).
 *  If overlap, combine ranges.  For example,
 *  If this is {1..5, 10..20}, adding 6..7 yields
 *  {1..5, 6..7, 10..20}.  Adding 4..8 yields {1..8, 10..20}.
 */
void IntervalSet::add(antlr_int32_t a, antlr_int32_t b)
{
    add(Interval::of(a, b));
}

// copy on write so we can cache a..a intervals and sets of that
void IntervalSet::add(const Interval& addition)
{
    if ( readonly ) throw std::logic_error("can't alter readonly IntervalSet");
    //System.out.println("add "+addition+" to "+intervals.toString());
    if ( addition.b<addition.a ) {
        return;
    }
    // find position in list
    // Use iterators as we modify list in place
    for (std::vector<Interval>::iterator iter = intervals.begin(); iter != intervals.end(); iter++) {
        const Interval& r = *iter;
        if ( addition == r ) {
            return;
        }
        if ( addition.adjacent(r) || !addition.disjoint(r) ) {
            // next to each other, make a single larger interval
            Interval bigger = addition.union_(r);
            *iter = bigger;
            // make sure we didn't just create an interval that
            // should be merged with next interval in list
            while ( (iter+1) != intervals.end() ) {
                Interval next = *(++iter);
                if ( !bigger.adjacent(next) && bigger.disjoint(next) ) {
                    break;
                }

                // if we bump up against or overlap next, merge
                iter = intervals.erase(iter);   // remove this one
                iter--; // move backwards to what we just set
                *iter = bigger.union_(next); // set to 3 merged ones
            }
            return;
        }
        if ( addition.startsBeforeDisjoint(r) ) {
            // insert before r
            intervals.insert(iter, addition);
            return;
        }
        // if disjoint and after r, a future iteration will handle it
    }
    // ok, must be after last interval (and disjoint from last interval)
    // just add it
    intervals.push_back(addition);
}

/** combine all sets in the array returned the or'd value */
IntervalSet IntervalSet::or_(const std::vector<IntervalSet>& sets)
{
    IntervalSet r;
    for (std::vector<IntervalSet>::const_iterator it; it != sets.end(); it++)
        r.addAll(&(*it));
    return r;
}

IntervalSet* IntervalSet::addAll(const IntSet* set)
{
    if ( set==NULL ) {
        return this;
    }
    const IntervalSet* other = dynamic_cast<const IntervalSet*>(set);
    if ( !other ) {
        throw std::invalid_argument(std::string(
                "can't add non IntSet (")+
                typeid(*set).name()+
                ") to IntervalSet");
    }
    // walk set and add each interval
    antlr_uint32_t n = other->intervals.size();
    for (antlr_uint32_t i = 0; i < n; i++) {
        const Interval& I = other->intervals[i];
        this->add(I.a,I.b);
    }
    return this;
}

IntervalSet* IntervalSet::complement(antlr_int32_t minElement, antlr_int32_t maxElement) const
{
    IntervalSet s = IntervalSet::of(minElement,maxElement);
    return this->complement(&s);
}

/** Given the set of possible values (rather than, say UNICODE or MAXINT),
 *  return a new set containing all elements in vocabulary, but not in
 *  this.  The computation is (vocabulary - this).
 *
 *  'this' is assumed to be either a subset or equal to vocabulary.
 */
IntervalSet* IntervalSet::complement(const IntSet* vocabulary) const
{
    if ( vocabulary==NULL ) {
        return NULL; // nothing in common with null set
    }
    const IntervalSet* vocabularyIS = dynamic_cast<const IntervalSet*>(vocabulary);
    if ( !(vocabularyIS) ) {
        throw std::invalid_argument(std::string(
            "can't complement with non IntervalSet (")+
            typeid(*vocabulary).name()+")");
    }
    antlr_int32_t maxElement = vocabularyIS->getMaxElement();

    antlr_auto_ptr<IntervalSet> comp(new IntervalSet());
    antlr_uint32_t n = intervals.size();
    if ( n ==0 ) {
        return comp.release();
    }
    const Interval& first = intervals[0];
    // add a range from 0 to first.a constrained to vocab
    if ( first.a > 0 ) {
        IntervalSet s = IntervalSet::of(0, first.a-1);
        antlr_auto_ptr<IntervalSet> a(s.and_(vocabularyIS));
        comp->addAll(a.get());
    }
    for (antlr_uint32_t i=1; i<n; i++) { // from 2nd interval .. nth
        const Interval& previous = intervals[i-1];
        const Interval& current = intervals[i];
        IntervalSet s = IntervalSet::of(previous.b+1, current.a-1);
        antlr_auto_ptr<IntervalSet> a(s.and_(vocabularyIS));
        comp->addAll(a.get());
    }
    const Interval& last = intervals[n -1];
    // add a range from last.b to maxElement constrained to vocab
    if ( last.b < maxElement ) {
        IntervalSet s = IntervalSet::of(last.b+1, maxElement);
        antlr_auto_ptr<IntervalSet> a(s.and_(vocabularyIS));
        comp->addAll(a.get());
    }
    return comp.release();
}

/** Compute this-other via this&~other.
 *  Return a new set containing all elements in this but not in other.
 *  other is assumed to be a subset of this;
 *  anything that is in other but not in this will be ignored.
 */
IntervalSet* IntervalSet::subtract(const IntSet* other) const
{
    // assume the whole unicode range here for the complement
    // because it doesn't matter.  Anything beyond the max of this' set
    // will be ignored since we are doing this & ~other.  The intersection
    // will be empty.  The only problem would be when this' set max value
    // goes beyond MAX_CHAR_VALUE, but hopefully the constant MAX_CHAR_VALUE
    // will prevent this.
    antlr_auto_ptr<IntervalSet> comp(
        dynamic_cast<const IntervalSet*>(other)->complement(&COMPLETE_CHAR_SET));
    return this->and_(comp.get());
}

IntervalSet* IntervalSet::or_(const IntSet* a) const
{
    antlr_auto_ptr<IntervalSet> o(new IntervalSet());
    o->addAll(this);
    o->addAll(a);
    return o.release();
}

/** Return a new set with the intersection of this set with other.  Because
 *  the intervals are sorted, we can use an iterator for each list and
 *  just walk them together.  This is roughly O(min(n,m)) for interval
 *  list lengths n and m.
 */
IntervalSet* IntervalSet::and_(const IntSet* other) const
{
    if ( other==NULL ) { //|| !(other instanceof IntervalSet) ) {
        return NULL; // nothing in common with null set
    }

    const std::vector<Interval>& myIntervals = this->intervals;
    const std::vector<Interval>& theirIntervals = dynamic_cast<const IntervalSet*>(other)->intervals;
    antlr_auto_ptr<IntervalSet> intersection;
    antlr_uint32_t mySize = myIntervals.size();
    antlr_uint32_t theirSize = theirIntervals.size();
    antlr_uint32_t i = 0;
    antlr_uint32_t j = 0;
    // iterate down both interval lists looking for nondisjoint intervals
    while ( i<mySize && j<theirSize ) {
        const Interval& mine = myIntervals[i];
        const Interval& theirs = theirIntervals[j];
        //System.out.println("mine="+mine+" and theirs="+theirs);
        if ( mine.startsBeforeDisjoint(theirs) ) {
            // move this iterator looking for interval that might overlap
            i++;
        }
        else if ( theirs.startsBeforeDisjoint(mine) ) {
            // move other iterator looking for interval that might overlap
            j++;
        }
        else if ( mine.properlyContains(theirs) ) {
            // overlap, add intersection, get next theirs
            if ( intersection.get()==NULL ) {
                intersection.reset(new IntervalSet());
            }
            intersection->add(mine.intersection(theirs));
            j++;
        }
        else if ( theirs.properlyContains(mine) ) {
            // overlap, add intersection, get next mine
            if ( intersection.get()==NULL) {
                intersection.reset(new IntervalSet());
            }
            intersection->add(mine.intersection(theirs));
            i++;
        }
        else if ( !mine.disjoint(theirs) ) {
            // overlap, add intersection
            if ( intersection.get()==NULL ) {
                intersection.reset(new IntervalSet());
            }
            intersection->add(mine.intersection(theirs));
            // Move the iterator of lower range [a..b], but not
            // the upper range as it may contain elements that will collide
            // with the next iterator. So, if mine=[0..115] and
            // theirs=[115..200], then intersection is 115 and move mine
            // but not theirs as theirs may collide with the next range
            // in thisIter.
            // move both iterators to next ranges
            if ( mine.startsAfterNonDisjoint(theirs) ) {
                j++;
            }
            else if ( theirs.startsAfterNonDisjoint(mine) ) {
                i++;
            }
        }
    }
    if ( intersection.get()==NULL) {
        return new IntervalSet();
    }
    return intersection.release();
}

/** Is el in any range of this set? */
bool IntervalSet::contains(antlr_int32_t el) const
{
    antlr_uint32_t n = intervals.size();
    for (antlr_uint32_t i = 0; i < n; i++) {
        const Interval& I = intervals[i];
        antlr_int32_t a = I.a;
        antlr_int32_t b = I.b;
        if ( el<a ) {
            break; // list is sorted and el is before this interval; not here
        }
        if ( el>=a && el<=b ) {
            return true; // found in this interval
        }
    }
    return false;
    /*
    for (ListIterator iter = intervals.listIterator(); iter.hasNext();) {
        Interval I = (Interval) iter.next();
        if ( el<I.a ) {
            break; // list is sorted and el is before this interval; not here
        }
        if ( el>=I.a && el<=I.b ) {
            return true; // found in this interval
        }
    }
    return false;
    */
}

/** return true if this set has no members */
bool IntervalSet::isNil() const
{
    return intervals.empty();
}

/** If this set is a single integer, return it otherwise Token.INVALID_TYPE */
antlr_int32_t IntervalSet::getSingleElement() const
{
    if ( intervals.size()==1 ) {
        const Interval& I = intervals[0];
        if ( I.a == I.b ) {
            return I.a;
        }
    }
    return Token::INVALID_TYPE;
}

antlr_int32_t IntervalSet::getMaxElement() const
{
    if ( isNil() ) {
        return Token::INVALID_TYPE;
    }
    const Interval& last = intervals[intervals.size()-1];
    return last.b;
}

/** Return minimum element >= 0 */
antlr_int32_t IntervalSet::getMinElement() const
{
    if ( isNil() ) {
        return Token::INVALID_TYPE;
    }
    antlr_uint32_t n = intervals.size();
    for (antlr_uint32_t i = 0; i < n; i++) {
        const Interval& I = intervals[i];
        antlr_int32_t a = I.a;
        antlr_int32_t b = I.b;
        for (antlr_int32_t v=a; v<=b; v++) {
            if ( v>=0 ) return v;
        }
    }
    return Token::INVALID_TYPE;
}

/** Return a list of Interval objects. */
const std::vector<Interval>& IntervalSet::getIntervals() const
{
    return intervals;
}

antlr_int32_t IntervalSet::hashCode() const
{
    antlr_int32_t hash = MurmurHash::initialize();
    for (std::vector<Interval>::const_iterator it = intervals.begin(); it != intervals.end(); it++) {
        const Interval& I = *it;
        hash = MurmurHash::update(hash, I.a);
        hash = MurmurHash::update(hash, I.b);
    }

    hash = MurmurHash::finish(hash, intervals.size() * 2);
    return hash;
}

/** Are two IntervalSets equal?  Because all intervals are sorted
 *  and disjoint, equals is a simple linear walk over both lists
 *  to make sure they are the same.  Interval.equals() is used
 *  by the List.equals() method to check the ranges.
 */
bool IntervalSet::equals(const Key<IntSet>* o) const
{
    const IntervalSet* other = dynamic_cast<const IntervalSet*>(o);
    antlr_uint32_t n = intervals.size();
    if ( !other || n != other->intervals.size() ) {
        return false;
    }
    for (antlr_uint32_t i = 0; i < n; i++)
        if ( !(intervals[i] == other->intervals[i]) )
            return false;
    return true;
}

IntSet* IntervalSet::clone() const
{
    return new IntervalSet(*this);
}

std::string IntervalSet::toString() const
{
    return toString(false);
}

std::string IntervalSet::toString(bool elemAreChar) const
{
    std::stringstream stream;
    if ( this->intervals.empty() ) {
        return "{}";
    }
    if ( this->size()>1 ) {
        stream << "{";
    }
    for (std::vector<Interval>::const_iterator iter = intervals.begin(); iter < intervals.end(); iter++) {
        const Interval& I = *iter;
        antlr_int32_t a = I.a;
        antlr_int32_t b = I.b;
        if ( a==b ) {
            if ( a==-1 ) stream << "<EOF>";
            else if ( elemAreChar ) stream << "'" << (char)a << "'";
            else stream << a;
        }
        else {
            if ( elemAreChar ) stream << "'" << (char)a << "'..'" << (char)b << "'";
            else stream << a << ".." << b;
        }
        if ( (iter+1) != intervals.end() ) {
            stream << ", ";
        }
    }
    if ( this->size()>1 ) {
        stream << "}";
    }
    return stream.str();
}

std::string IntervalSet::toString(const std::vector<std::string>& tokenNames) const
{
    std::stringstream stream;
    if ( this->intervals.empty() ) {
        return "{}";
    }
    if ( this->size()>1 ) {
        stream << "{";
    }
    for (std::vector<Interval>::const_iterator iter = intervals.begin(); iter < intervals.end(); iter++) {
        const Interval& I = *iter;
        antlr_int32_t a = I.a;
        antlr_int32_t b = I.b;
        if ( a==b ) {
            stream << elementName(tokenNames, a);
        }
        else {
            for (antlr_int32_t i=a; i<=b; i++) {
                if ( i>a ) stream << ", ";
                stream << elementName(tokenNames, i);
            }
        }
        if ( (iter+1) != intervals.end() ) {
            stream << ", ";
        }
    }
    if ( this->size()>1 ) {
        stream << "}";
    }
    return stream.str();
}

std::string IntervalSet::elementName(const std::vector<std::string>& tokenNames, antlr_uint32_t a) const
{
    if ( a==(antlr_uint32_t)Token::EOF_ ) return "<EOF>";
    else if ( a==(antlr_uint32_t)Token::EPSILON ) return "<EPSILON>";
    else return tokenNames[a];
}

antlr_uint32_t IntervalSet::size() const
{
    antlr_uint32_t n = 0;
    antlr_uint32_t numIntervals = intervals.size();
    if ( numIntervals==1 ) {
        const Interval& firstInterval = this->intervals[0];
        return firstInterval.b-firstInterval.a+1;
    }
    for (antlr_uint32_t i = 0; i < numIntervals; i++) {
        const Interval& I = intervals[i];
        n += (I.b-I.a+1);
    }
    return n;
}

antlr_auto_ptr<IntegerList> IntervalSet::toIntegerList() const
{
    antlr_auto_ptr<IntegerList> values(new IntegerList(size()));
    antlr_uint32_t n = intervals.size();
    for (antlr_uint32_t i = 0; i < n; i++) {
        const Interval& I = intervals[i];
        antlr_int32_t a = I.a;
        antlr_int32_t b = I.b;
        for (antlr_int32_t v=a; v<=b; v++) {
            values->add(v);
        }
    }
    return values;
}

antlr_auto_ptr< std::list<antlr_int32_t> > IntervalSet::toList() const
{
    antlr_auto_ptr< std::list<antlr_int32_t> > values(new std::list<antlr_int32_t>());
    antlr_uint32_t n = intervals.size();
    for (antlr_uint32_t i = 0; i < n; i++) {
        const Interval& I = intervals[i];
        antlr_int32_t a = I.a;
        antlr_int32_t b = I.b;
        for (antlr_int32_t v=a; v<=b; v++) {
            values->push_back(v);
        }
    }
    return values;
}

antlr_auto_ptr< std::set<antlr_int32_t> > IntervalSet::toSet() const
{
    antlr_auto_ptr< std::set<antlr_int32_t> > s(new std::set<antlr_int32_t>());
    for (std::vector<Interval>::const_iterator it = intervals.begin(); it != intervals.end(); it++) {
        const Interval& I = *it;
        antlr_int32_t a = I.a;
        antlr_int32_t b = I.b;
        for (antlr_int32_t v=a; v<=b; v++) {
            s->insert(v);
        }
    }
    return s;
}

/** Get the ith element of ordered set.  Used only by RandomPhrase so
 *  don't bother to implement if you're not doing that for a new
 *  ANTLR code gen target.
 */
antlr_int32_t IntervalSet::get(antlr_uint32_t i) const
{
    antlr_uint32_t n = intervals.size();
    antlr_uint32_t index = 0;
    for (antlr_uint32_t j = 0; j < n; j++) {
        const Interval& I = intervals[j];
        antlr_int32_t a = I.a;
        antlr_int32_t b = I.b;
        for (antlr_int32_t v=a; v<=b; v++) {
            if ( index==i ) {
                return v;
            }
            index++;
        }
    }
    return -1;
}

antlr_auto_ptr< std::vector<antlr_int32_t> > IntervalSet::toArray() const
{
    return toIntegerList()->toArray();
}
    
void IntervalSet::remove(antlr_int32_t el)
{
    if ( readonly ) throw std::logic_error("can't alter readonly IntervalSet");
    antlr_uint32_t n = intervals.size();
    for (antlr_uint32_t i = 0; i < n; i++) {
        Interval& I = intervals[i];
        antlr_int32_t a = I.a;
        antlr_int32_t b = I.b;
        if ( el<a ) {
            break; // list is sorted and el is before this interval; not here
        }
        // if whole interval x..x, rm
        if ( el==a && el==b ) {
            intervals.erase(intervals.begin()+i);
            break;
        }
        // if on left edge x..b, adjust left
        if ( el==a ) {
            I.a++;
            break;
        }
        // if on right edge a..x, adjust right
        if ( el==b ) {
            I.b--;
            break;
        }
        // if in middle a..x..b, split interval
        if ( el>a && el<b ) { // found in this interval
            antlr_int32_t oldb = I.b;
            I.b = el-1;      // [a..x-1]
            add(el+1, oldb); // add [x+1..b]
        }
    }
}

bool IntervalSet::isReadonly() const
{
    return readonly;
}

void IntervalSet::setReadonly(bool readonly)
{
    this->readonly = readonly;
}

} /* namespace misc */
} /* namespace antlr4 */
