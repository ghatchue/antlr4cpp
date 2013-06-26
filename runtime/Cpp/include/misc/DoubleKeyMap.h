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

#ifndef DOUBLE_KEY_MAP_H
#define DOUBLE_KEY_MAP_H

#include <Antlr4Definitions.h>
#include <misc/HashMap.h>

namespace antlr4 {
namespace misc {

#define DoubleKeyMapBase HashMap<Key1, HashMap<Key2, Value> >
    
/** Sometimes we need to map a key to a value but key is two pieces of data.
 *  This nested hash table saves creating a single key each time we access
 *  map; avoids mem creation.
 */
template <typename Key1, typename Key2, typename Value>
class ANTLR_API DoubleKeyMap : public DoubleKeyMapBase
{
public:
    
    // Insert an element, and return a pointer to the inserted value
    // (Unlike the Java equivalent which returns the old value))
    const Value* put(const Key1& k1, const Key2& k2, const Value& v);

    const Value* get(const Key1& k1, const Key2& k2) const;
    
    antlr_uint32_t size() const;
    
};


template <typename Key1, typename Key2, typename Value>
const Value* DoubleKeyMap<Key1, Key2, Value>::put(const Key1& k1, const Key2& k2, const Value& v)
{
    const HashMap<Key2, Value>* cdata2 = DoubleKeyMapBase::get(k1);
    if (cdata2 == NULL) {
        cdata2 = DoubleKeyMapBase::put(k1, HashMap<Key2, Value>());
    }
    HashMap<Key2, Value>* data2 = const_cast<HashMap<Key2, Value>*>(cdata2);
    return data2->put(k2, v);
}

template <typename Key1, typename Key2, typename Value>
const Value* DoubleKeyMap<Key1, Key2, Value>::get(const Key1& k1, const Key2& k2) const
{
    const HashMap<Key2, Value>* data2 = DoubleKeyMapBase::get(k1);
    if ( data2==NULL ) return NULL;
    return data2->get(k2);
}

template <typename Key1, typename Key2, typename Value>
antlr_uint32_t DoubleKeyMap<Key1, Key2, Value>::size() const
{
    antlr_uint32_t size = 0;
    for (typename DoubleKeyMapBase::const_iterator it = DoubleKeyMapBase::begin();
            it != DoubleKeyMapBase::end(); it++)
    {
        size += it->second.size();
    }
    return size;
}

} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef DOUBLE_KEY_MAP_H */
