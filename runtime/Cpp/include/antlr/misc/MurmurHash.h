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

#ifndef MURMUR_HASH_H
#define MURMUR_HASH_H

#include <antlr/Definitions.h>
#include <antlr/misc/Key.h>
#include <vector>

namespace antlr4 {
namespace misc {

/**
 *
 * @author Sam Harwell
 */
class ANTLR_API MurmurHash
{
public:

    /**
     * Initialize the hash using the default seed value.
     *
     * @return the intermediate hash value
     */
    static antlr_int32_t initialize();

    /**
     * Initialize the hash using the specified {@code seed}.
     *
     * @param seed the seed
     * @return the intermediate hash value
     */
    static antlr_int32_t initialize(antlr_int32_t seed);

    /**
     * Update the intermediate hash value for the next input {@code value}.
     *
     * @param hash the intermediate hash value
     * @param value the value to add to the current hash
     * @return the updated intermediate hash value
     */
    static antlr_int32_t update(antlr_int32_t hash, antlr_int32_t value);

	/**
	 * Update the intermediate hash value for the next input {@code value}.
	 *
	 * @param hash the intermediate hash value
	 * @param value the value to add to the current hash
	 * @return the updated intermediate hash value
	 */
    template <typename T>
	static antlr_int32_t update(antlr_int32_t hash, const Key<T>* value);
    
    /**
     * Apply the final computation steps to the intermediate value {@code hash}
     * to form the final result of the MurmurHash 3 hash function.
     *
     * @param hash the intermediate hash value
     * @param numberOfWords the number of integer values added to the hash
     * @return the final hash result
     */
    static antlr_int32_t finish(antlr_int32_t hash, antlr_int32_t numberOfWords);

    /**
     * Utility function to compute the hash code of an array using the
     * MurmurHash algorithm.
     *
     * @param <T> the array element type
     * @param data the array data
     * @param seed the seed for the MurmurHash algorithm
     * @return the hash code of the data
     */
    //template <typename T>
    //static antlr_int32_t hashCode(std::vector<T> data, antlr_int32_t seed);

private:

    MurmurHash();
    
    static const antlr_int32_t DEFAULT_SEED;
};


template <typename T>
static antlr_int32_t MurmurHash::update(antlr_int32_t hash, const Key<T>* value)
{
    return update(hash, value != NULL ? value->hashCode() : 0);
}


//template<typename T>
//antlr_int32_t MurmurHash::hashCode(std::vector<T> data, antlr_int32_t seed)
//{
//    antlr_int32_t hash = initialize(seed);
//    for (typename std::list<T>::const_iterator it = data.begin(); it != list.end(); it++) {
//        hash = update(hash, value);
//    }
//    hash = finish(hash, data.length);
//    return hash;
//}

} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef MURMUR_HASH_H */
