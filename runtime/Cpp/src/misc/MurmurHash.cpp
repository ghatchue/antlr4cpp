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

#include <misc/MurmurHash.h>

namespace antlr4 {
namespace misc {


const antlr_int32_t MurmurHash::DEFAULT_SEED = 0;

MurmurHash::MurmurHash()
{
}

/**
 * Initialize the hash using the default seed value.
 *
 * @return the intermediate hash value
 */
antlr_int32_t MurmurHash::initialize()
{
	return initialize(DEFAULT_SEED);
}

/**
 * Initialize the hash using the specified {@code seed}.
 *
 * @param seed the seed
 * @return the intermediate hash value
 */
antlr_int32_t MurmurHash::initialize(antlr_int32_t seed)
{
	return seed;
}

/**
 * Update the intermediate hash value for the next input {@code value}.
 *
 * @param hash the intermediate hash value
 * @param value the value to add to the current hash
 * @return the updated intermediate hash value
 */
antlr_int32_t MurmurHash::update(antlr_int32_t hash, antlr_int32_t value)
{
	const antlr_int32_t c1 = 0xCC9E2D51;
	const antlr_int32_t c2 = 0x1B873593;
	const antlr_int32_t r1 = 15;
	const antlr_int32_t r2 = 13;
	const antlr_int32_t m = 5;
	const antlr_int32_t n = 0xE6546B64;

	antlr_int32_t k = value;
	k = k * c1;
	k = (k << r1) | ((antlr_uint32_t)k >> (32 - r1));
	k = k * c2;

	hash = hash ^ k;
	hash = (hash << r2) | ((antlr_uint32_t)hash >> (32 - r2));
	hash = hash * m + n;

	return hash;
}

/**
 * Apply the final computation steps to the intermediate value {@code hash}
 * to form the final result of the MurmurHash 3 hash function.
 *
 * @param hash the intermediate hash value
 * @param numberOfWords the number of integer values added to the hash
 * @return the final hash result
 */
antlr_int32_t MurmurHash::finish(antlr_int32_t hash, antlr_int32_t numberOfWords)
{
	hash = hash ^ (numberOfWords * 4);
	hash = hash ^ ((antlr_uint32_t)hash >> 16);
	hash = hash * 0x85EBCA6B;
	hash = hash ^ ((antlr_uint32_t)hash >> 13);
	hash = hash * 0xC2B2AE35;
	hash = hash ^ ((antlr_uint32_t)hash >> 16);
	return hash;
}


} /* namespace misc */
} /* namespace antlr4 */
