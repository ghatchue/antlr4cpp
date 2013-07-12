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

#ifndef DFA_H
#define DFA_H

#include <Antlr4Definitions.h>
#include <dfa/DFAState.h>
#include <misc/HashMap.h>
#include <misc/KeyPtr.h>
#include <memory>
#include <string>
#include <vector>

namespace antlr4 { namespace atn { class DecisionState; } }

using namespace antlr4::atn;
using namespace antlr4::misc;

namespace antlr4 {
namespace dfa {

class ANTLR_API DFA
{
public:
    
    DFA(ANTLR_NOTNULL const DecisionState* atnStartState);

    DFA(ANTLR_NOTNULL const DecisionState* atnStartState, antlr_int32_t decision);

    /**
     * Return a list of all states in this DFA, ordered by state number.
     */
    antlr_auto_ptr< std::vector<const DFAState*> > getStates() const;

    ANTLR_OVERRIDE
    std::string toString() const;

    std::string toString(ANTLR_NULLABLE const std::vector<std::string>* tokenNames) const;

    std::string toLexerString() const;
    
protected:
    
    static bool compareStatesForSort (const DFAState* o1, const DFAState* o2);
    
public:

    typedef HashMap<KeyPtr<DFAState>, DFAState*> StateHashMap;
    
    /** A set of all DFA states. Use {@link Map} so we can get old state back
     *  ({@link Set} only allows you to see if it's there).
     */
    ANTLR_NOTNULL
    antlr_auto_ptr< StateHashMap > states;
    
    ANTLR_NULLABLE
    const DFAState* s0;

    const antlr_int32_t decision;

    /** From which ATN state did we create this DFA? */
    ANTLR_NOTNULL
    const DecisionState* atnStartState;

    /** Set of configs for a DFA state with at least one conflict? Mainly used as "return value"
     *  from {@link ParserATNSimulator#predictATN} for retry.
     */
    //	public OrderedHashSet<ATNConfig> conflictSet;
    
};


} /* namespace dfa */
} /* namespace antlr4 */

#endif /* ifndef DFA_H */
