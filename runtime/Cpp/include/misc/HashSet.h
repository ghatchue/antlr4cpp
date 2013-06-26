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


namespace antlr4 {
namespace misc {

#if defined(ANTLR_USING_MSC_HASH_SET)
#   define HashSetBase antlr_hash_set_base<T, HashKeyHelper<T> >
#else
#   define HashSetBase antlr_hash_set_base<T, HashKeyHelper<T>, HashKeyHelper<T> >
#endif

template <typename T>
class ANTLR_API HashSet : public HashSetBase
{
public:

    virtual ~HashSet();

    virtual bool contains(const T& value) const;

    virtual bool add(const T& value);

    virtual bool remove(const T& value);
};

template <typename T>
HashSet<T>::~HashSet()
{
}

template <typename T>
bool HashSet<T>::contains(const T& value) const
{
    return HashSetBase::find(value) != HashSetBase::end();
}

template <typename T>
bool HashSet<T>::add(const T& value)
{
    std::pair<typename HashSetBase::iterator, bool> result = insert(value);
    return result.second;
}

template <typename T>
bool HashSet<T>::remove(const T& value)
{
    return HashSetBase::erase(value) > 0;
}

} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef HASH_SET_H */
