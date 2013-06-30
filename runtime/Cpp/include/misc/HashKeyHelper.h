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

#ifndef HASH_KEY_HELPER_H
#define HASH_KEY_HELPER_H

#include <Antlr4Definitions.h>
#include <misc/Key.h>
#include <misc/StdHashMap.h>
#include <misc/Traits.h>
#include <stdexcept>


namespace antlr4 {
namespace misc {


template <typename K, bool isUsingHashKey = Traits::isBaseOf<Key<K>, K>::value>
class ANTLR_API HashKeyHelper;

// This specialization is for Key subclasses
template<typename K>
class ANTLR_API HashKeyHelper<K, true>
{
public:
    // Hash function
    size_t operator()(const K& key) const;

    // Comparison function. This is not always an equality comparison!!
    bool operator()(const K& left, const K& right) const;
    
    // Hash function to antlr_int32_t value
    antlr_int32_t hashCode(const K& key) const;
    
    // Indicates if two values are equal
    bool areEqual(const K& left, const K& right) const;

#if defined(ANTLR_USING_MSC_HASH_MAP)
    // Bucket size used by VC++ hash_map
    enum { bucket_size  = 4 };
#endif
};

// This specialization is for key types that don't derive
// from Key such as primitive types
template<typename K>
class ANTLR_API HashKeyHelper<K, false>
{
public:
    // Hash function
    size_t operator()(const K& key) const;

    // Comparison function. This is not always an equality comparison!!
    bool operator()(const K& left, const K& right) const;

    // Hash function to antlr_int32_t value
    antlr_int32_t hashCode(const K& key) const;
    
    // Indicates if two values are equal
    bool areEqual(const K& left, const K& right) const;
    
#if defined(ANTLR_USING_MSC_HASH_MAP)
    // Bucket size used by VC++ hash_map
    enum { bucket_size  = 4 };
#endif
};

// Hash function
template <typename K>
size_t HashKeyHelper<K, true>::operator()(const K& key) const
{
    return static_cast<size_t>(key.hashCode());
}

// Hash function
template <typename K>
size_t HashKeyHelper<K, false>::operator()(const K& key) const
{
#if defined(ANTLR_USING_MSC_HASH_MAP)
        antlr_hash_map_ns::hash_compare<K> hash;
        return hash(key);
#else
        antlr_hash_map_ns::hash<K> hash;
        return hash(key);
#endif
}

// Comparison function. This is not always an equality comparison!!
template <typename K>
bool HashKeyHelper<K, true>::operator()(const K& left, const K& right) const
{
#if defined(ANTLR_USING_MSC_HASH_MAP)
        // when using MS hash_map, this function indicates if left < right
        return left.hashCode() < right.hashCode();
#else
        return left.equals(right);
#endif
}

// Comparison function. This is not always an equality comparison!!
template <typename K>
bool HashKeyHelper<K, false>::operator()(const K& left, const K& right) const
{
#if defined(ANTLR_USING_MSC_HASH_MAP)
        antlr_hash_map_ns::hash_compare<K> cmp;
        return cmp(left, right);
#else
        std::equal_to<K> cmp;
        return cmp(left, right);
#endif
}

// Hash function to antlr_int32_t value
template <typename K>
antlr_int32_t HashKeyHelper<K, true>::hashCode(const K& key) const
{
    return static_cast<antlr_int32_t>(this->operator ()(key));
}

// Hash function to antlr_int32_t value
template <typename K>
antlr_int32_t HashKeyHelper<K, false>::hashCode(const K& key) const
{
    return static_cast<antlr_int32_t>(this->operator ()(key));
}

// Indicates if two values are equal
template <typename K>
bool HashKeyHelper<K, true>::areEqual(const K& left, const K& right) const
{
    return left.equals(right);
}

// Indicates if two values are equal
template <typename K>
bool HashKeyHelper<K, false>::areEqual(const K& left, const K& right) const
{
    std::equal_to<K> cmp;
    return cmp(left, right);
}


// Sanity checks
#if defined(ANTLR_USING_MSC_HASH_MAP) != defined(ANTLR_USING_MSC_HASH_SET)
#   error "MS hash_map/set inconsistency"
#endif

} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef HASH_KEY_HELPER_H */
