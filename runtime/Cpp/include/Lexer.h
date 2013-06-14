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

#ifndef LEXER_H
#define LEXER_H

#include <Antlr4Definitions.h>

namespace antlr4 {

/** A lexer is recognizer that draws input symbols from a character stream.
 *  lexer grammars result in a subclass of this object. A Lexer object
 *  uses simplified match() and error recovery mechanisms in the interest
 *  of speed.
 */
class Lexer /* : Recognizer<Integer, LexerATNSimulator>,
                 TokenSource */
{
public:
    
    static const antlr_int32_t DEFAULT_MODE;
    static const antlr_int32_t MORE;
    static const antlr_int32_t SKIP;

    static const antlr_int32_t DEFAULT_TOKEN_CHANNEL;
    static const antlr_int32_t HIDDEN;
    static const antlr_int32_t MIN_CHAR_VALUE;
    static const antlr_int32_t MAX_CHAR_VALUE;
    
};

} /* namespace antlr4 */

#endif /* ifndef LEXER_H */
