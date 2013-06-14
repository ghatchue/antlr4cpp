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

#ifndef ANTLR4_DEFINITIONS_H
#define ANTLR4_DEFINITIONS_H

/* config.h */
#ifdef HAVE_CONFIG_H
#    include "config.h"
#endif

/* C++11 support for VS2012 C++ compiler */
#if _MSC_VER >= 1700
#    define HAVE_CXX11
#endif


/* ANTLR_API */
#if (defined _WIN32 || defined __CYGWIN__) && !defined __GNUC__
#    if defined ANTLR4_SHARED
#        if defined ANTLR4_EXPORTS
#            define ANTLR_API __declspec(dllexport)
#        else
#            define ANTLR_API __declspec(dllimport)
#        endif
#    else
#        define ANTLR_API
#    endif
#else
#    define ANTLR_API
#endif


/* Integer data types */
#ifdef HAVE_INTTYPES_H
#   include <inttypes.h>
    typedef int32_t antlr_int32_t;
    typedef uint32_t antlr_uint32_t;
#else /* HAVE_INTTYPES_H */
    typedef int antlr_int32_t;
    typedef unsigned int antlr_uint32_t;
#endif /* HAVE_INTTYPES_H */

/* Attributes */
#define ANTLR_OVERRIDE
#define ANTLR_NOTNULL

/* Auto ptr */
#ifdef HAVE_CXX11
#   define antlr_auto_ptr std::unique_ptr
#else
#   define antlr_auto_ptr std::auto_ptr
#endif
    
#endif /* ANTLR4_DEFINITIONS_H */
