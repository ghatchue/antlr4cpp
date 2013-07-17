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

#ifndef PAIR_H
#define PAIR_H

#include <antlr/Definitions.h>


namespace antlr4 {
namespace misc {

template <typename A, typename B>
class ANTLR_API Pair
{
public:

    Pair(const A& a, const B& b);
    
    template <typename T1, typename T2>
    Pair(const Pair<T1, T2>& other);
    
    bool operator==(const Pair<A, B>& other) const;

public:
    
    const A a;
    const B b;
};


template<typename A, typename B>
Pair<A, B>::Pair(const A& a, const B& b)
    :   a(a), b(b)
{
}

template<typename A, typename B>
template<typename T1, typename T2>
Pair<A, B>::Pair(const Pair<T1, T2>& other)
    :   a(other.a), b(other.b)
{
}

template<typename A, typename B>
bool Pair<A, B>::operator==(const Pair<A, B>& other) const
{
    return a==other.a && b==other.b;
}


} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef PAIR_H */
