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

#ifndef SEMANTIC_CONTEXT_H
#define SEMANTIC_CONTEXT_H

#include <antlr/Definitions.h>
#include <antlr/misc/Key.h>
#include <string>


using namespace antlr4::misc;

namespace antlr4 {
namespace atn {

class ANTLR_API SemanticContext : public virtual Key<SemanticContext>
{
public:

    SemanticContext() { }
    
    SemanticContext(const SemanticContext&) : Key<SemanticContext>() { }
    
    ANTLR_OVERRIDE
    antlr_int32_t hashCode() const { return 0; }
    
    ANTLR_OVERRIDE
    bool equals(const Key<SemanticContext>*) const { return false; }
    
    ANTLR_OVERRIDE
    SemanticContext* clone() const { return NULL; }

    ANTLR_OVERRIDE
    std::string toString() const { return std::string(); }
    
    class Predicate
    {
    public:
        Predicate(int, int, bool) { }
    };

public:

    static const SemanticContext NONE;
};


} /* namespace atn */
} /* namespace antlr4 */

#endif /* ifndef SEMANTIC_CONTEXT_H */
