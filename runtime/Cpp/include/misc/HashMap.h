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

#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <Antlr4Definitions.h>
#include <misc/HashKeyHelper.h>
#include <misc/Key.h>


namespace antlr4 {
namespace misc {

#if defined(ANTLR_USING_MSC_HASH_MAP)
#   define HashMapBase antlr_hash_map_base<K, T, HashKeyHelper<K, isBaseOf<Key<K>, K>::value> >
#else
#   define HashMapBase antlr_hash_map_base<K, T, HashKeyHelper<K, isBaseOf<Key<K>, K>::value>, HashKeyHelper<K, isBaseOf<Key<K>, K>::value> >
#endif

template <typename K, typename T>
class ANTLR_API HashMap : public HashMapBase
{
public:

    bool contains(const K& key) const;

    // Insert an element, and return a pointer to the inserted value
    // (Unlike the Java equivalent which returns the old value))
    T* put(const K& key, const T& value);

    void remove(const K& key);

    T* get(const K& key);
};


template <typename K, typename T>
bool HashMap<K, T>::contains(const K& key) const
{
    return find(key) != HashMapBase::end();
}

template <typename K, typename T>
T* HashMap<K, T>::put(const K& key, const T& value)
{
    std::pair<typename HashMapBase::iterator, bool> result =
        insert(std::pair<K, T>(key, value));
    if (!result.second)
        result.first->second = value;
    return &result.first->second;
}

template <typename K, typename T>
void HashMap<K, T>::remove(const K& key)
{
    HashMapBase::erase(key);
}

template <typename K, typename T>
T* HashMap<K, T>::get(const K& key)
{
    T* value = NULL;
    typename HashMapBase::iterator it = find(key);
    if (it != HashMapBase::end())
        value = &it->second;
    return value;
}

} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef HASH_MAP_H */
