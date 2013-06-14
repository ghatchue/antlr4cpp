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

#include <misc/IntervalSet.h>
#include <Lexer.h>

namespace antlr4 {
namespace misc {

const IntervalSet IntervalSet::COMPLETE_CHAR_SET = IntervalSet::of(0, Lexer::MAX_CHAR_VALUE);
const IntervalSet IntervalSet::EMPTY_SET = IntervalSet();

IntervalSet::IntervalSet(const std::list<Interval> intervals)
    : intervals(intervals.begin(), intervals.end()),
      readonly(false)
{
}

IntervalSet::IntervalSet(const IntervalSet& set)
    : intervals(set.intervals),
      readonly(set.readonly)
{
}

IntervalSet::IntervalSet(const IntervalSet* set)
    : intervals(2, Interval::INVALID),
      readonly(false)
{
    addAll(*set);
}

IntervalSet::IntervalSet()
    : intervals(2, Interval::INVALID),
      readonly(false)
{
}

IntervalSet::IntervalSet(antlr_int32_t el)
    : intervals(1, Interval::INVALID),
      readonly(false)
{
    add(el);
}

IntervalSet::IntervalSet(antlr_int32_t e1, antlr_int32_t e2)
    : intervals(2, Interval::INVALID),
      readonly(false)
{
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
}

/** Add a single element to the set.  An isolated element is stored
    *  as a range el..el.
    */
void IntervalSet::add(antlr_int32_t el)
{
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
}

// copy on write so we can cache a..a intervals and sets of that
void IntervalSet::add(const Interval& addition)
{
}

/** combine all sets in the array returned the or'd value */
IntervalSet IntervalSet::or_(const std::vector<IntervalSet>& sets)
{
	return IntervalSet();
}

IntervalSet* IntervalSet::addAll(const IntSet& set)
{
	return NULL;
}

IntervalSet* IntervalSet::complement(antlr_int32_t minElement, antlr_int32_t maxElement) const
{
	return NULL;
}

/** Given the set of possible values (rather than, say UNICODE or MAXINT),
    *  return a new set containing all elements in vocabulary, but not in
    *  this.  The computation is (vocabulary - this).
    *
    *  'this' is assumed to be either a subset or equal to vocabulary.
    */
IntervalSet* IntervalSet::complement(const IntSet& vocabulary) const
{
	return NULL;
}

/** Compute this-other via this&~other.
    *  Return a new set containing all elements in this but not in other.
    *  other is assumed to be a subset of this;
    *  anything that is in other but not in this will be ignored.
    */
IntervalSet* IntervalSet::subtract(const IntSet& other) const
{
	return NULL;
}

IntervalSet* IntervalSet::or_(const IntSet& a) const
{
	return NULL;
}

/** Return a new set with the intersection of this set with other.  Because
    *  the intervals are sorted, we can use an iterator for each list and
    *  just walk them together.  This is roughly O(min(n,m)) for interval
    *  list lengths n and m.
    */
IntervalSet* IntervalSet::and_(const IntSet& other) const
{
	return NULL;
}

/** Is el in any range of this set? */
bool IntervalSet::contains(antlr_int32_t el) const
{
	return false;
}

/** return true if this set has no members */
bool IntervalSet::isNil() const
{
	return false;
}

/** If this set is a single integer, return it otherwise Token.INVALID_TYPE */
antlr_int32_t IntervalSet::getSingleElement() const
{
	return -1;
}

antlr_int32_t IntervalSet::getMaxElement() const
{
	return -1;
}

/** Return minimum element >= 0 */
antlr_int32_t IntervalSet::getMinElement() const
{
	return -1;
}

/** Return a list of Interval objects. */
const std::vector<Interval>& IntervalSet::getIntervals() const
{
	return intervals;
}

antlr_int32_t IntervalSet::hashCode() const
{
	return -1;
}

/** Are two IntervalSets equal?  Because all intervals are sorted
    *  and disjoint, equals is a simple linear walk over both lists
    *  to make sure they are the same.  Interval.equals() is used
    *  by the List.equals() method to check the ranges.
    */
bool IntervalSet::operator==(const IntSet& other) const
{
	return false;
}

std::string IntervalSet::toString() const
{
	return std::string();
}

std::string IntervalSet::toString(bool elemAreChar) const
{
	return std::string();
}

std::string IntervalSet::toString(const std::vector<std::string>& tokenNames) const
{
	return std::string();
}

std::string IntervalSet::elementName(const std::vector<std::string>& tokenNames, antlr_uint32_t a) const
{
	return std::string();
}

antlr_uint32_t IntervalSet::size() const
{
	return 0;
}

std::list<antlr_int32_t> IntervalSet::toList() const
{
	return std::list<antlr_int32_t>();
}

std::set<antlr_int32_t> IntervalSet::toSet() const
{
	return std::set<antlr_int32_t>();
}

/** Get the ith element of ordered set.  Used only by RandomPhrase so
    *  don't bother to implement if you're not doing that for a new
    *  ANTLR code gen target.
    */
antlr_int32_t IntervalSet::get(antlr_uint32_t i) const
{
	return -1;
}

std::vector<antlr_int32_t> IntervalSet::toArray()
{
	return std::vector<antlr_int32_t>();
}
    
void IntervalSet::remove(antlr_int32_t el)
{
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
