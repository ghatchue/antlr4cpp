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

#ifndef FLEXIBLE_HASH_MAP_H
#define FLEXIBLE_HASH_MAP_H

#include <Antlr4Definitions.h>
#include <misc/HashMap.h>

namespace antlr4 {
namespace misc {

/** A limited map (many unsupported operations) that lets me use
 *  varying hashCode/equals.
 */
template <typename K, typename V>
class ANTLR_API FlexibleHashMap : public HashMap<K, V>
{
public:


public:

	static const antlr_int32_t INITAL_CAPACITY;    // must be power of 2
	static const antlr_int32_t INITAL_BUCKET_CAPACITY;
	static const double LOAD_FACTOR;

};


template <typename K, typename V>
const antlr_int32_t FlexibleHashMap<K, V>::INITAL_CAPACITY = 16;    // must be power of 2
template <typename K, typename V>
const antlr_int32_t FlexibleHashMap<K, V>::INITAL_BUCKET_CAPACITY = 8;
template <typename K, typename V>
const double FlexibleHashMap<K, V>::LOAD_FACTOR = 0.75;


} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef FLEXIBLE_HASH_MAP_H */
