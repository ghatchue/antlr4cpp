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

#ifndef ATN_CONFIG_H
#define ATN_CONFIG_H

#include <antlr/Definitions.h>
#include <antlr/misc/Key.h>


namespace antlr4 { namespace atn { class ATNState; } }
namespace antlr4 { namespace atn { class PredictionContext; } }
namespace antlr4 { namespace atn { class SemanticContext; } }

using namespace antlr4::atn;
using namespace antlr4::misc;

namespace antlr4 {
namespace atn {

/** A tuple: (ATN state, predicted alt, syntactic, semantic context).
 *  The syntactic context is a graph-structured stack node whose
 *  path(s) to the root is the rule invocation(s)
 *  chain used to arrive at the state.  The semantic context is
 *  the tree of semantic predicates encountered before reaching
 *  an ATN state.
 */
class ANTLR_API ATNConfig : public virtual Key<ATNConfig>
{
public:
    
//    ATNConfig(const ATNConfig& old);
//
//    ATNConfig(ANTLR_NOTNULL const ATNState* state,antlr_int32_t alt,
//              ANTLR_NULLABLE const PredictionContext* context);
//
//    ATNConfig(ANTLR_NOTNULL const ATNState* state,
//              antlr_int32_t alt,
//              ANTLR_NULLABLE const PredictionContext* context,
//              ANTLR_NOTNULL const SemanticContext* semanticContext);
//
//    ATNConfig(ANTLR_NOTNULL const ATNConfig* c, ANTLR_NOTNULL const ATNState* state);
//
//    ATNConfig(ANTLR_NOTNULL const ATNConfig* c, ANTLR_NOTNULL const ATNState* state,
//              ANTLR_NOTNULL const SemanticContext* semanticContext);
//
//    ATNConfig(ANTLR_NOTNULL const ATNConfig* c,
//              ANTLR_NOTNULL const SemanticContext* semanticContext);
//
//    ATNConfig(ANTLR_NOTNULL const ATNConfig* c, ANTLR_NOTNULL const ATNState* state,
//              ANTLR_NULLABLE const PredictionContext* context);
//
//    ATNConfig(ANTLR_NOTNULL const ATNConfig* c, ANTLR_NOTNULL const ATNState* state,
//              ANTLR_NULLABLE const PredictionContext* context,
//              ANTLR_NOTNULL const SemanticContext* semanticContext);
//
//    /** An ATN configuration is equal to another if both have
//     *  the same state, they predict the same alternative, and
//     *  syntactic/semantic contexts are the same.
//     */
//    ANTLR_OVERRIDE
//    bool equals(const Key<ATNConfig>& o) const;
//
//    ANTLR_OVERRIDE
//    public int hashCode() {
//        int hashCode = MurmurHash.initialize(7);
//        hashCode = MurmurHash.update(hashCode, state.stateNumber);
//        hashCode = MurmurHash.update(hashCode, alt);
//        hashCode = MurmurHash.update(hashCode, context);
//        hashCode = MurmurHash.update(hashCode, semanticContext);
//        hashCode = MurmurHash.finish(hashCode, 4);
//        return hashCode;
//    }
//
//    ANTLR_OVERRIDE
//    public String toString() {
//        return toString(null, true);
//    }
//
//    public String toString(ANTLR_NULLABLE Recognizer<?, ?> recog, boolean showAlt) {
//        StringBuilder buf = new StringBuilder();
////        if ( state.ruleIndex>=0 ) {
////            if ( recog!=null ) buf.append(recog.getRuleNames()[state.ruleIndex]+":");
////            else buf.append(state.ruleIndex+":");
////        }
//        buf.append('(');
//        buf.append(state);
//        if ( showAlt ) {
//            buf.append(",");
//            buf.append(alt);
//        }
//        if ( context!=null ) {
//            buf.append(",[");
//            buf.append(context.toString());
//            buf.append("]");
//        }
//        if ( semanticContext!=null && semanticContext != SemanticContext.NONE ) {
//            buf.append(",");
//            buf.append(semanticContext);
//        }
//        if ( reachesIntoOuterContext>0 ) {
//            buf.append(",up=").append(reachesIntoOuterContext);
//        }
//        buf.append(')');
//        return buf.toString();
//    }
//
//public:
//    
//    /** The ATN state associated with this configuration */
//    ANTLR_NOTNULL
//    public final ATNState state;
//
//    /** What alt (or lexer rule) is predicted by this configuration */
//    public final int alt;
//
//    /** The stack of invoking states leading to the rule/states associated
//     *  with this config.  We track only those contexts pushed during
//     *  execution of the ATN simulator.
//     */
//    ANTLR_NULLABLE
//    public PredictionContext context;
//
//    /**
//     * We cannot execute predicates dependent upon local context unless
//     * we know for sure we are in the correct context. Because there is
//     * no way to do this efficiently, we simply cannot evaluate
//     * dependent predicates unless we are in the rule that initially
//     * invokes the ATN simulator.
//     *
//     * closure() tracks the depth of how far we dip into the
//     * outer context: depth > 0.  Note that it may not be totally
//     * accurate depth since I don't ever decrement. TODO: make it a boolean then
//     */
//    public int reachesIntoOuterContext;
//
//    ANTLR_NOTNULL
//    public final SemanticContext semanticContext;
    
};


} /* namespace atn */
} /* namespace antlr4 */

#endif /* ifndef ATN_CONFIG_H */
