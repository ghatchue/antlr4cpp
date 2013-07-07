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

#include <dfa/DFA.h>
#include <atn/DecisionState.h>
#include <dfa/DFASerializer.h>
#include <dfa/LexerDFASerializer.h>
#include <algorithm>

namespace antlr4 {
namespace dfa {


DFA::DFA(ANTLR_NOTNULL const DecisionState* atnStartState)
    :   states(new StateHashMap()),
        s0(NULL),
        decision(0),
        atnStartState(atnStartState)
{
}

DFA::DFA(ANTLR_NOTNULL const DecisionState* atnStartState, antlr_int32_t decision)
    :   states(new StateHashMap()),
        s0(NULL),
        decision(decision),
        atnStartState(atnStartState)
{
}

bool DFA::compareStatesForSort (const DFAState* o1, const DFAState* o2)
{
    return o1->stateNumber < o2->stateNumber;
}

/**
 * Return a list of all states in this DFA, ordered by state number.
 */
std::vector<const DFAState*> DFA::getStates() const
{
    std::vector<const DFAState*> result;
    for (StateHashMap::const_iterator it = states->begin(); it != states->end(); it++)
        result.push_back(it->first.get());
    std::sort(result.begin(), result.end(), compareStatesForSort);
    return result;
}

std::string DFA::toString() const
{
    return toString(NULL);
}

std::string DFA::toString(ANTLR_NULLABLE const std::vector<std::string>* tokenNames) const
{
    if ( s0==NULL ) return "";
    antlr_auto_ptr<DFASerializer> serializer(new DFASerializer(this,tokenNames));
    return serializer->toString();
}

std::string DFA::toLexerString() const
{
    if ( s0==NULL ) return "";
    antlr_auto_ptr<DFASerializer> serializer(new LexerDFASerializer(this));
    return serializer->toString();
}


} /* namespace dfa */
} /* namespace antlr4 */
