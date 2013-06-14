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

#ifndef TOKEN_H
#define TOKEN_H

#include <Antlr4Definitions.h>
#include <string>

namespace antlr4 {

class TokenSource;
class CharStream;

/** A token has properties: text, type, line, character position in the line
 *  (so we can ignore tabs), token channel, index, and source from which
 *  we obtained this token.
 */
class ANTLR_API Token
{
public:
    
    virtual ~Token();

    /** Get the text of the token */
    virtual std::string getText() const = 0;

    /** Get the token type of the token */
    virtual antlr_int32_t getType() const = 0;

    /** The line number on which the 1st character of this token was matched,
     *  line=1..n
     */
    virtual antlr_int32_t getLine() const = 0;

    /** The index of the first character of this token relative to the
     *  beginning of the line at which it occurs, 0..n-1
     */
    virtual antlr_int32_t getCharPositionInLine() const = 0;

    /** Return the channel this token. Each token can arrive at the parser
     *  on a different channel, but the parser only "tunes" to a single channel.
     *  The parser ignores everything not on DEFAULT_CHANNEL.
     */
    virtual antlr_int32_t getChannel() const = 0;

    /** An index from 0..n-1 of the token object in the input stream.
     *  This must be valid in order to print token streams and
     *  use TokenRewriteStream.
     *
     *  Return -1 to indicate that this token was conjured up since
     *  it doesn't have a valid index.
     */
    virtual antlr_int32_t getTokenIndex() const = 0;

    /** The starting character index of the token
     *  This method is optional; return -1 if not implemented.
     */
    virtual antlr_int32_t getStartIndex() const = 0;

    /** The last character index of the token.
     *  This method is optional; return -1 if not implemented.
     */
    virtual antlr_int32_t getStopIndex() const = 0;

    /** Gets the {@link TokenSource} which created this token.
     */
    virtual TokenSource* getTokenSource() const = 0;

    /**
     * Gets the {@link CharStream} from which this token was derived.
     */
    virtual CharStream* getInputStream() const = 0;


public:
    
    static const antlr_int32_t INVALID_TYPE;

    /** During lookahead operations, this "token" signifies we hit rule end ATN state
     *  and did not follow it despite needing to.
     */
    static const antlr_int32_t EPSILON;

    static const antlr_int32_t MIN_USER_TOKEN_TYPE;

    static const antlr_int32_t EOF_;

    /** All tokens go to the parser (unless skip() is called in that rule)
     *  on a particular "channel".  The parser tunes to a particular channel
     *  so that whitespace etc... can go to the parser on a "hidden" channel.
     */
    static const antlr_int32_t DEFAULT_CHANNEL;

    /** Anything on different channel than DEFAULT_CHANNEL is not parsed
     *  by parser.
     */
    static const antlr_int32_t HIDDEN_CHANNEL;
    
};

} /* namespace antlr4 */

#endif /* ifndef TOKEN_H */
