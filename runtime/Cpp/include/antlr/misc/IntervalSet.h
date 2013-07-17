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

#ifndef INTERVAL_SET_H
#define INTERVAL_SET_H

#include <antlr/Definitions.h>
#include <antlr/misc/IntegerList.h>
#include <antlr/misc/Interval.h>
#include <antlr/misc/IntSet.h>
#include <set>
#include <string>
#include <vector>

namespace antlr4 {
namespace misc {

/** A set of integers that relies on ranges being common to do
 *  "run-length-encoded" like compression (if you view an IntSet like
 *  a BitSet with runs of 0s and 1s).  Only ranges are recorded so that
 *  a few ints up near value 1000 don't cause massive bitsets, just two
 *  integer intervals.
 *
 *  element values may be negative.  Useful for sets of EPSILON and EOF.
 *
 *  0..9 char range is index pair ['\u0030','\u0039'].
 *  Multiple ranges are encoded with multiple index pairs.  Isolated
 *  elements are encoded with an index pair where both intervals are the same.
 *
 *  The ranges are ordered and disjoint so that 2..6 appears before 101..103.
 */
class ANTLR_API IntervalSet : public IntSet
{
public:

    IntervalSet(const std::list<Interval>& intervals);

    IntervalSet(const IntervalSet& set);
    
    IntervalSet(const IntervalSet* set);

    IntervalSet();

    IntervalSet(antlr_int32_t el);

    IntervalSet(antlr_int32_t e1, antlr_int32_t e2);

    /** Create a set with a single element, el. */
    ANTLR_NOTNULL
    static IntervalSet of(antlr_int32_t a);

    /** Create a set with all ints within range [a..b] (inclusive) */
    ANTLR_NOTNULL
    static IntervalSet of(antlr_int32_t a, antlr_int32_t b);

    void clear();

    /** Add a single element to the set.  An isolated element is stored
     *  as a range el..el.
     */
    ANTLR_OVERRIDE
    void add(antlr_int32_t el);

    /** Add interval; i.e., add all integers from a to b to set.
     *  If b<a, do nothing.
     *  Keep list in sorted order (by left range value).
     *  If overlap, combine ranges.  For example,
     *  If this is {1..5, 10..20}, adding 6..7 yields
     *  {1..5, 6..7, 10..20}.  Adding 4..8 yields {1..8, 10..20}.
     */
    void add(antlr_int32_t a, antlr_int32_t b);


    /** combine all sets in the array returned the or'd value */
    static IntervalSet or_(const std::vector<IntervalSet>& sets);

    ANTLR_OVERRIDE
    IntervalSet* addAll(const IntSet* set);

    IntervalSet* complement(antlr_int32_t minElement, antlr_int32_t maxElement) const;

    /** Given the set of possible values (rather than, say UNICODE or MAXINT),
     *  return a new set containing all elements in vocabulary, but not in
     *  this.  The computation is (vocabulary - this).
     *
     *  'this' is assumed to be either a subset or equal to vocabulary.
     */
    ANTLR_OVERRIDE
    IntervalSet* complement(const IntSet* vocabulary) const;

    /** Compute this-other via this&~other.
     *  Return a new set containing all elements in this but not in other.
     *  other is assumed to be a subset of this;
     *  anything that is in other but not in this will be ignored.
     */
    ANTLR_OVERRIDE
    IntervalSet* subtract(const IntSet* other) const;

    ANTLR_OVERRIDE
    IntervalSet* or_(const IntSet* a) const;

    /** Return a new set with the intersection of this set with other.  Because
     *  the intervals are sorted, we can use an iterator for each list and
     *  just walk them together.  This is roughly O(min(n,m)) for interval
     *  list lengths n and m.
     */
    ANTLR_OVERRIDE
    IntervalSet* and_(const IntSet* other) const;

    /** Is el in any range of this set? */
    ANTLR_OVERRIDE
    bool contains(antlr_int32_t el) const;

    /** return true if this set has no members */
    ANTLR_OVERRIDE
    bool isNil() const;

    /** If this set is a single integer, return it otherwise Token.INVALID_TYPE */
    ANTLR_OVERRIDE
    antlr_int32_t getSingleElement() const;

    antlr_int32_t getMaxElement() const;

    /** Return minimum element >= 0 */
    antlr_int32_t getMinElement() const;

    /** Return a list of Interval objects. */
    const std::vector<Interval>& getIntervals() const;

    ANTLR_OVERRIDE
    antlr_int32_t hashCode() const;

    /** Are two IntervalSets equal?  Because all intervals are sorted
     *  and disjoint, equals is a simple linear walk over both lists
     *  to make sure they are the same.  Interval.equals() is used
     *  by the List.equals() method to check the ranges.
     */
    ANTLR_OVERRIDE
    bool operator==(const IntSet& other) const;

    ANTLR_OVERRIDE
    IntSet* clone() const;

    ANTLR_OVERRIDE
    std::string toString() const;

    std::string toString(bool elemAreChar) const;

    std::string toString(const std::vector<std::string>& tokenNames) const;

    ANTLR_OVERRIDE
    antlr_uint32_t size() const;
    
    antlr_auto_ptr<IntegerList> toIntegerList() const;

    ANTLR_OVERRIDE
    antlr_auto_ptr< std::list<antlr_int32_t> > toList() const;

    antlr_auto_ptr< std::set<antlr_int32_t> > toSet() const;

    /** Get the ith element of ordered set.  Used only by RandomPhrase so
     *  don't bother to implement if you're not doing that for a new
     *  ANTLR code gen target.
     */
    antlr_int32_t get(antlr_uint32_t i) const;

    antlr_auto_ptr< std::vector<antlr_int32_t> > toArray() const;
    
    ANTLR_OVERRIDE
    void remove(antlr_int32_t el);

    bool isReadonly() const;

    void setReadonly(bool readonly);

    
protected:
    
    // copy on write so we can cache a..a intervals and sets of that
    void add(const Interval& addition);

    std::string elementName(const std::vector<std::string>& tokenNames,
        antlr_uint32_t a) const;
    

public:

    static const IntervalSet COMPLETE_CHAR_SET;
    static const IntervalSet EMPTY_SET;

protected:

    /** The list of sorted, disjoint intervals. */
    std::vector<Interval> intervals;

    bool readonly;

};

} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef INTERVAL_SET_H */
