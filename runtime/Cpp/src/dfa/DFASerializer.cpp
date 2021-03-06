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

#include <antlr/dfa/DFASerializer.h>
#include <antlr/dfa/DFA.h>
#include <antlr/dfa/DFAState.h>
#include <antlr/misc/Utils.h>
#include <sstream>

namespace antlr4 {
namespace dfa {

DFASerializer::DFASerializer(ANTLR_NOTNULL const DFA* dfa,
        ANTLR_NULLABLE const std::vector<std::string>* tokenNames)
    :   dfa(dfa),
        tokenNames(tokenNames)
{
}

std::string DFASerializer::toString() const
{
    if ( dfa->s0==NULL ) return "";
    std::stringstream buf;
    antlr_auto_ptr< std::vector<const DFAState*> > states = dfa->getStates();
    for (std::vector<const DFAState*>::const_iterator it = states->begin();
            it != states->end(); it++)
    {
        const DFAState& s = **it;
        antlr_uint32_t n = 0;
        if ( s.edges!=NULL ) n = s.numEdges;
        for (antlr_uint32_t i=0; i<n; i++) {
            const DFAState* t = s.edges[i];
            if ( t!=NULL && t->stateNumber != ANTLR_INT32_MAX ) {
                buf << getStateString(s);
                std::string label = getEdgeLabel(i);
                buf << "-" << label << "->" << getStateString(*t) << "\n";
            }
        }
    }

    //return Utils.sortLinesInString(output);
    return buf.str();
}

std::string DFASerializer::getEdgeLabel(antlr_uint32_t i) const
{
    std::string label;
    if ( i==0 ) return "EOF";
    if ( tokenNames!=NULL ) label = (*tokenNames)[i-1];
    else label = Utils::stringValueOf(i-1);
    return label;
}

std::string DFASerializer::getStateString(const DFAState& s) const
{
    antlr_int32_t n = s.stateNumber;
    std::string baseStateStr = std::string(s.isAcceptState ? ":" : "") + "s" + Utils::stringValueOf(n) + (s.requiresFullContext ? "^" : "");
    if ( s.isAcceptState ) {
        if ( s.predicates!=NULL ) {
            baseStateStr += "=>" + Utils::stringValueOfPtrArray(s.predicates, s.numPredicates);
        }
        else {
            baseStateStr += "=>" + s.prediction;
        }
    }
    return baseStateStr;
}
    
} /* namespace dfa */
} /* namespace antlr4 */
