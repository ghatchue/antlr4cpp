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

#include <antlr/Token.h>
#include <antlr/IntStream.h>

namespace antlr4 {

const antlr_int32_t Token::INVALID_TYPE = 0;

/** During lookahead operations, this "token" signifies we hit rule end ATN state
 *  and did not follow it despite needing to.
 */
const antlr_int32_t Token::EPSILON = -2;

const antlr_int32_t Token::MIN_USER_TOKEN_TYPE = 1;

const antlr_int32_t Token::EOF_ = IntStream::EOF_;

/** All tokens go to the parser (unless skip() is called in that rule)
 *  on a particular "channel".  The parser tunes to a particular channel
 *  so that whitespace etc... can go to the parser on a "hidden" channel.
 */
const antlr_int32_t Token::DEFAULT_CHANNEL = 0;

/** Anything on different channel than DEFAULT_CHANNEL is not parsed
 *  by parser.
 */
const antlr_int32_t Token::HIDDEN_CHANNEL = 1;


Token::~Token()
{
}

} /* namespace antlr4 */
