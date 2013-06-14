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

#include <misc/Interval.h>
#include <algorithm>
#include <sstream>

namespace antlr4 {
namespace misc {

const Interval Interval::INVALID = Interval(-1, -2);

Interval::Interval(antlr_int32_t a, antlr_int32_t b)
	: a(a),
	  b(b)
{
}

Interval::Interval(const Interval& other)
	: a(other.a),
	  b(other.b)
{
}

/** Interval objects are used readonly so share all with the
	*  same single value a==b up to some max size.  Use an array as a perfect hash.
	*  Return shared object for 0..INTERVAL_POOL_MAX_VALUE or a new
	*  Interval object with a..a in it.  On Java.g4, 218623 IntervalSets
	*  have a..a (set with 1 element).
	*/
Interval Interval::of(antlr_int32_t a, antlr_int32_t b)
{
	return Interval(a, b);
}

/** return number of elements between a and b inclusively. x..x is length 1.
	*  if b < a, then length is 0.  9..10 has length 2.
	*/
antlr_int32_t Interval::length() const
{
	if ( b<a ) return 0;
	return b-a+1;
}

bool Interval::operator==(const Interval& other) const
{
	return this->a==other.a && this->b==other.b;
}

/** Does this start completely before other? Disjoint */
bool Interval::startsBeforeDisjoint(const Interval& other) const
{
	return this->a<other.a && this->b<other.a;
}

/** Does this start at or before other? Nondisjoint */
bool Interval::startsBeforeNonDisjoint(const Interval& other) const
{
	return this->a<=other.a && this->b>=other.a;
}

/** Does this->a start after other.b? May or may not be disjoint */
bool Interval::startsAfter(const Interval& other) const
{
	return this->a>other.a;
}

/** Does this start completely after other? Disjoint */
bool Interval::startsAfterDisjoint(const Interval& other) const
{
	return this->a>other.b;
}

/** Does this start after other? NonDisjoint */
bool Interval::startsAfterNonDisjoint(const Interval& other) const
{
	return this->a>other.a && this->a<=other.b; // this->b>=other.b implied
}

/** Are both ranges disjoint? I.e., no overlap? */
bool Interval::disjoint(const Interval& other) const
{
	return startsBeforeDisjoint(other) || startsAfterDisjoint(other);
}

/** Are two intervals adjacent such as 0..41 and 42..42? */
bool Interval::adjacent(const Interval& other) const
{
	return this->a == other.b+1 || this->b == other.a-1;
}

bool Interval::properlyContains(const Interval& other) const
{
	return other.a >= this->a && other.b <= this->b;
}

/** Return the interval computed from combining this and other */
Interval Interval::union_(const Interval& other) const
{
	return Interval::of(std::min(a, other.a), std::max(b, other.b));
}

/** Return the interval in common between this and o */
Interval Interval::intersection(const Interval& other) const
{
	return Interval::of(std::max(a, other.a), std::min(b, other.b));
}

/** Return the interval with elements from this not in other;
	*  other must not be totally enclosed (properly contained)
	*  within this, which would result in two disjoint intervals
	*  instead of the single one returned by this method.
	*/
Interval Interval::differenceNotProperlyContained(const Interval& other) const
{
	// other.a to left of this->a (or same)
	antlr_int32_t val1 = INVALID.a;
	antlr_int32_t val2 = INVALID.b;

	if ( other.startsBeforeNonDisjoint(*this) ) {
		val1 = std::max(this->a, other.b + 1);
		val2 = this->b;
	}

	// other.a to right of this->a
	else if ( other.startsAfterNonDisjoint(*this) ) {
		val1 = this->a;
		val2 = other.a - 1;
	}
	return Interval(val1, val2);
}

std::string Interval::toString() const
{
	std::stringstream stream;
	stream << a << ".." << b;
	return stream.str();
}

} /* namespace misc */
} /* namespace antlr4 */
