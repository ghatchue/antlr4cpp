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

#ifndef INTERVAL_H
#define INTERVAL_H

#include <Antlr4Definitions.h>
#include <string>

namespace antlr4 {
namespace misc {

/** An immutable inclusive interval a..b */
class Interval
{
public:

    Interval(antlr_int32_t a, antlr_int32_t b);

    Interval(const Interval& other);

    /** Interval objects are used readonly so share all with the
     *  same single value a==b up to some max size.  Use an array as a perfect hash.
     *  Return shared object for 0..INTERVAL_POOL_MAX_VALUE or a new
     *  Interval object with a..a in it.  On Java.g4, 218623 IntervalSets
     *  have a..a (set with 1 element).
     */
    static Interval of(antlr_int32_t a, antlr_int32_t b);

    /** return number of elements between a and b inclusively. x..x is length 1.
     *  if b < a, then length is 0.  9..10 has length 2.
     */
    antlr_int32_t length() const;

    bool operator==(const Interval& other) const;

    /** Does this start completely before other? Disjoint */
    bool startsBeforeDisjoint(const Interval& other) const;

    /** Does this start at or before other? Nondisjoint */
    bool startsBeforeNonDisjoint(const Interval& other) const;

    /** Does this.a start after other.b? May or may not be disjoint */
    bool startsAfter(const Interval& other) const;

    /** Does this start completely after other? Disjoint */
    bool startsAfterDisjoint(const Interval& other) const;

    /** Does this start after other? NonDisjoint */
    bool startsAfterNonDisjoint(const Interval& other) const;

    /** Are both ranges disjoint? I.e., no overlap? */
    bool disjoint(const Interval& other) const;

    /** Are two intervals adjacent such as 0..41 and 42..42? */
    bool adjacent(const Interval& other) const;

    bool properlyContains(const Interval& other) const;

    /** Return the interval computed from combining this and other */
    Interval union_(const Interval& other) const;

    /** Return the interval in common between this and o */
    Interval intersection(const Interval& other) const;

    /** Return the interval with elements from this not in other;
     *  other must not be totally enclosed (properly contained)
     *  within this, which would result in two disjoint intervals
     *  instead of the single one returned by this method.
     */
    Interval differenceNotProperlyContained(const Interval& other) const;

    std::string toString() const;


public:

    static const Interval INVALID;

    antlr_int32_t a;
    antlr_int32_t b;

};

} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef INTERVAL_H */
