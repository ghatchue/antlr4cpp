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

#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H

#include <Antlr4Definitions.h>
#include <string>

namespace antlr4 {
namespace misc {


struct Traits
{
    // Check if B is a base class of D
    template <typename B, typename D>
    struct isBaseOf
    {
        typedef char (&yes)[1];
        typedef char (&no)[2];

        template <typename B1, typename D1>
        struct Host
        {
            operator B1*() const;
            operator D1*();
        };
    
        template <typename T> 
        static yes check(D*, T);
        static no check(B*, antlr_int32_t);

        static const bool value = sizeof(check(Host<B,D>(), antlr_int32_t())) == sizeof(yes);
    };
    
    // Check if T1 and T2 are the same type
    template< typename T1, typename T2 >
    struct isSame { static const bool value = false; };
    template< typename T>
    struct isSame<T,T> { static const bool value = true; };
    
    // Indicates if B is a superclass of D
    template <typename B, typename D>
    struct super
    {
        static const bool value = isSame<B, D>::value || isBaseOf<B, D>::value;
    };

    // Indicates if D extends B
    template <typename D, typename B>
    struct extends
    {
        static const bool value = isSame<B, D>::value || isBaseOf<B, D>::value;
    };
    
    // Check if T has a toString member function
    template<typename T, typename RESULT = std::string>
    class hasToString
    {
        template <typename U, std::string (U::*)() const> struct Check;
        template <typename U> static char func(Check<U, &U::toString> *);
        template <typename U> static int func(...);
      public:
        enum { value = sizeof(func<T>(0)) == sizeof(char) };
    };
};


} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef TYPE_TRAITS_H */
