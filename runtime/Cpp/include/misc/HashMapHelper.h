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

#ifndef HASH_MAP_HELPER_H
#define HASH_MAP_HELPER_H

#include <Antlr4Definitions.h>
#include <misc/HashKey.h>
#include <misc/StdHashMap.h>
#include <misc/TypeTraits.h>


namespace antlr4 {
namespace misc {


template <typename Key>
class ANTLR_API HashKeyHelper
{
public:

    enum { bucket_size  = 4 };

    size_t operator()(const Key& key) const;

    bool operator()(const Key& left, const Key& right) const;
};


template <typename Key>
size_t HashKeyHelper<Key>::operator()(const Key& key) const
{
    if (is_base_of<HashKey<Key>, Key>::value)
    {
        const HashKey<Key>* k = reinterpret_cast<const HashKey<Key>* >(&key);
        return static_cast<size_t>(k->hashCode());
    }
    else
    {
#if defined(ANTLR_USING_MSC_HASH_MAP)
        antlr_hash_map_ns::hash_compare<Key> cmp;
        return cmp.operator()(key);
#else
#   error Not implemented
#endif
    }
}

template <typename Key>
bool HashKeyHelper<Key>::operator()(const Key& left, const Key& right) const
{
    if (is_base_of<HashKey<Key>, Key>::value)
    {
        const HashKey<Key>* l = reinterpret_cast<const HashKey<Key>* >(&left);
        const HashKey<Key>* r = reinterpret_cast<const HashKey<Key>* >(&right);
        return l->hashCode() < r->hashCode();
    }
    else
    {
#if defined(ANTLR_USING_MSC_HASH_MAP)
        antlr_hash_map_ns::hash_compare<Key> cmp;
        return cmp.operator()(left, right);
#else
#   error Not implemented
#endif
    }
}


} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef HASH_MAP_HELPER_H */
