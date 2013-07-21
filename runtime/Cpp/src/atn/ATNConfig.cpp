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

#include <antlr/atn/ATNConfig.h>

namespace antlr4 {
namespace atn {

ATNConfig::ATNConfig(const ATNConfig& old)
    :   Key<ATNConfig>(),
        state(old.state),
        alt(old.alt),
        context(old.context),
        reachesIntoOuterContext(old.reachesIntoOuterContext),
        semanticContext(old.semanticContext)
{
}

ATNConfig::ATNConfig(ANTLR_NOTNULL const ATNState* state,antlr_int32_t alt,
                     ANTLR_NULLABLE const PredictionContext* context)
    :   state(state),
        alt(alt),
        context(context),
        reachesIntoOuterContext(0),
        semanticContext(NULL)
{
}

ATNConfig::ATNConfig(ANTLR_NOTNULL const ATNState* state,
                     antlr_int32_t alt,
                     ANTLR_NULLABLE const PredictionContext* context,
                     ANTLR_NOTNULL const SemanticContext* semanticContext)
    :   state(state),
        alt(alt),
        context(context),
        reachesIntoOuterContext(0),
        semanticContext(semanticContext)
{
}

ATNConfig::ATNConfig(ANTLR_NOTNULL const ATNConfig* c, ANTLR_NOTNULL const ATNState* state)
    :   state(state),
        alt(c->alt),
        context(c->context),
        reachesIntoOuterContext(c->reachesIntoOuterContext),
        semanticContext(c->semanticContext)
{
}

ATNConfig::ATNConfig(ANTLR_NOTNULL const ATNConfig* c, ANTLR_NOTNULL const ATNState* state,
                     ANTLR_NOTNULL const SemanticContext* semanticContext)
    :   state(state),
        alt(c->alt),
        context(c->context),
        reachesIntoOuterContext(c->reachesIntoOuterContext),
        semanticContext(semanticContext)
{
}

ATNConfig::ATNConfig(ANTLR_NOTNULL const ATNConfig* c,
                     ANTLR_NOTNULL const SemanticContext* semanticContext)
    :   state(c->state),
        alt(c->alt),
        context(c->context),
        reachesIntoOuterContext(c->reachesIntoOuterContext),
        semanticContext(semanticContext)
{
}

ATNConfig::ATNConfig(ANTLR_NOTNULL const ATNConfig* c, ANTLR_NOTNULL const ATNState* state,
                     ANTLR_NULLABLE const PredictionContext* context)
    :   state(state),
        alt(c->alt),
        context(context),
        reachesIntoOuterContext(c->reachesIntoOuterContext),
        semanticContext(c->semanticContext)
{
}

ATNConfig::ATNConfig(ANTLR_NOTNULL const ATNConfig* c, ANTLR_NOTNULL const ATNState* state,
                     ANTLR_NULLABLE const PredictionContext* context,
                     ANTLR_NOTNULL const SemanticContext* semanticContext)
    :   state(state),
        alt(c->alt),
        context(context),
        reachesIntoOuterContext(c->reachesIntoOuterContext),
        semanticContext(semanticContext)
{
}

/** An ATN configuration is equal to another if both have
 *  the same state, they predict the same alternative, and
 *  syntactic/semantic contexts are the same.
 */
bool ATNConfig::equals(const Key<ATNConfig>* o) const
{
    return false;
//    const ATNConfig* other = dynamic_cast<const ATNConfig*>(&o);
//    if (other == NULL) {
//        return false;
//    }
//    return this->state->stateNumber==other->state->stateNumber
//        && this->alt==other.alt
//        && (this->context==other->context || (this.context != NULL && this->context->equals(other.context)))
//        && this->semanticContext.equals(other.semanticContext);
}

antlr_int32_t ATNConfig::hashCode() const
{
    return 0;
}

ATNConfig* ATNConfig::clone() const
{
    return new ATNConfig(*this);
}

std::string ATNConfig::toString() const
{
    return std::string();
}

template <typename Symbol, typename ATNInterpreter>
std::string ATNConfig::toString(ANTLR_NULLABLE const Recognizer<Symbol, ATNInterpreter>* recog, bool showAlt) const
{
    return std::string();
}


} /* namespace atn */
} /* namespace antlr4 */
