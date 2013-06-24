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

#ifndef HASH_SET_H
#define HASH_SET_H

#include <Antlr4Definitions.h>
#include <misc/HashKeyHelper.h>
#include <misc/Key.h>
#include <misc/StdHashSet.h>
#include <misc/TypeTraits.h>


namespace antlr4 {
namespace misc {

#if defined(ANTLR_USING_MSC_HASH_SET)
#   define HashSetBase antlr_hash_set_base<K, HashKeyHelper<K, Traits::isBaseOf<Key<K>, K>::value> >
#else
#   define HashSetBase antlr_hash_set_base<K, HashKeyHelper<K, Traits::isBaseOf<Key<K>, K>::value>, HashKeyHelper<K, Traits::isBaseOf<Key<K>, K>::value> >
#endif

template <typename K>
class ANTLR_API HashSet : public HashSetBase
{
public:

    bool contains(const K& key) const;

    bool add(const K& key);

    bool remove(const K& key);
};


template <typename K>
bool HashSet<K>::contains(const K& key) const
{
    return HashSetBase::find(key) != HashSetBase::end();
}

template <typename K>
bool HashSet<K>::add(const K& key)
{
    std::pair<typename HashSetBase::iterator, bool> result = insert(key);
    return result.second;
}

template <typename K>
bool HashSet<K>::remove(const K& key)
{
    return HashSetBase::erase(key) > 0;
}

} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef HASH_SET_H */
