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

#ifndef STD_HASH_SET_H
#define STD_HASH_SET_H

#include <antlr/Antlr4Definitions.h>


#if defined(HAVE_CXX11)
#   include <unordered_set>
#   define antlr_hash_set_ns std
#   define antlr_hash_set_base antlr_hash_set_ns::unordered_set
#elif defined(HAVE_TR1_UNORDERED_SET)
#   include <tr1/unordered_set>
#   define antlr_hash_set_ns std::tr1
#   define antlr_hash_set_base antlr_hash_set_ns::unordered_set
#elif defined (HAVE_STD_EXT_HASH_SET)
#   include <ext/hash_set>
#   define antlr_hash_set_ns std
#   define antlr_hash_set_base antlr_hash_set_ns::hash_set
#elif defined (HAVE_GNU_EXT_HASH_SET)
#   include <ext/hash_set>
#   define antlr_hash_set_ns __gnu_cxx
#   define antlr_hash_set_base antlr_hash_set_ns::hash_set
#elif defined (HAVE_GLOBAL_HASH_SET)
#   include <hash_set>
#   define antlr_hash_set_ns
#   define antlr_hash_set_base antlr_hash_set_ns::hash_set
#elif _MSC_VER >= 1600
#   include <unordered_set>
#   define antlr_hash_set_ns std
#   define antlr_hash_set_base antlr_hash_set_ns::unordered_set
#elif _MSC_VER >= 1500
#   include <unordered_set>
#   define antlr_hash_set_ns std::tr1
#   define antlr_hash_set_base antlr_hash_set_ns::unordered_set
#elif _MSC_VER >= 1300
#   include <hash_set>
#   define antlr_hash_set_ns stdext
#   define antlr_hash_set_base antlr_hash_set_ns::hash_set
#   define ANTLR_USING_MSC_HASH_SET
#else
#   error "hash_set not found"
#endif

#endif /* ifndef STD_HASH_SET_H */
