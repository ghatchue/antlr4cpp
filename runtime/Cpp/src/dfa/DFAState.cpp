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

#include <antlr/dfa/DFAState.h>
#include <antlr/atn/SemanticContext.h>
#include <antlr/misc/MurmurHash.h>
#include <antlr/misc/Utils.h>
#include <sstream>

namespace antlr4 {
namespace dfa {


//DFAState::PredPrediction::PredPrediction(const SemanticContext* pred, antlr_int32_t alt)
//    :   pred(pred),
//        alt(alt)
//{
//}
//
//std::string DFAState::PredPrediction::toString() const
//{
//    return std::string("(")+Utils::stringValueOf(*pred)+", "+Utils::stringValueOf(alt)+ ")";
//}
//
//DFAState::~DFAState()
//{
//}
//
//DFAState::DFAState()
//    :   stateNumber(-1),
//        configs(new ATNConfigSet()),
//        edges(NULL),
//        numEdges(0),
//        isAcceptState(false),
//        prediction(0),
//        lexerRuleIndex(-1),
//        lexerActionIndex(-1),
//        requiresFullContext(false),
//        predicates(NULL),
//        numPredicates(0)
//{
//}
//
//DFAState::DFAState(antlr_int32_t stateNumber)
//    :   stateNumber(stateNumber),
//        configs(new ATNConfigSet()),
//        edges(NULL),
//        numEdges(0),
//        isAcceptState(false),
//        prediction(0),
//        lexerRuleIndex(-1),
//        lexerActionIndex(-1),
//        requiresFullContext(false),
//        predicates(NULL),
//        numPredicates(0)
//{
//}
//
//DFAState::DFAState(ANTLR_NOTNULL antlr_auto_ptr<ATNConfigSet> configs)
//    :   stateNumber(-1),
//        configs(configs),
//        edges(NULL),
//        numEdges(0),
//        isAcceptState(false),
//        prediction(0),
//        lexerRuleIndex(-1),
//        lexerActionIndex(-1),
//        requiresFullContext(false),
//        predicates(NULL),
//        numPredicates(0)
//{
//}
//
//DFAState::DFAState(const DFAState& other)
//    :   Key<DFAState>(),
//        stateNumber(-1),
//        configs(new ATNConfigSet()),
//        edges(NULL),
//        numEdges(0),
//        isAcceptState(false),
//        prediction(0),
//        lexerRuleIndex(-1),
//        lexerActionIndex(-1),
//        requiresFullContext(false),
//        predicates(NULL),
//        numPredicates(0)
//{
//    throw std::logic_error("DFAState:: copy constructor not impl");
//}
//
///** Get the set of all alts mentioned by all ATN configurations in this
// *  DFA state.
// */
//antlr_auto_ptr< HashSet<antlr_int32_t> > DFAState::getAltSet() const
//{
//    antlr_auto_ptr< HashSet<antlr_int32_t> > alts(new HashSet<antlr_int32_t>());
//    if ( configs!=NULL ) {
//        antlr_auto_ptr< std::vector<const ATNConfig*> > cfgs = configs->toPtrArray();
//        for ()
//        for (ATNConfig c : configs) {
//            alts.add(c.alt);
//        }
//    }
//    if ( alts->empty() ) return antlr_auto_ptr< HashSet<antlr_int32_t> >();
//    return alts;
//}
//
//antlr_int32_t DFAState::hashCode() const
//{
//    antlr_int32_t hash = MurmurHash::initialize(7);
//    hash = MurmurHash.update(hash, configs->hashCode());
//    hash = MurmurHash.finish(hash, 1);
//    return hash;
//}
//
///**
// * Two {@link DFAState} instances are equal if their ATN configuration sets
// * are the same. This method is used to see if a state already exists.
// * <p/>
// * Because the number of alternatives and number of ATN configurations are
// * finite, there is a finite number of DFA states that can be processed.
// * This is necessary to show that the algorithm terminates.
// * <p/>
// * Cannot test the DFA state numbers here because in
// * {@link ParserATNSimulator#addDFAState} we need to know if any other state
// * exists that has this exact set of ATN configurations. The
// * {@link #stateNumber} is irrelevant.
// */
//bool DFAState::operator==(const DFAState& other) const
//{
//    // TODO (sam): what to do when configs==null?
//    bool sameSet = this->configs->opetator==(other.configs);
//    // System.out.println("DFAState.equals: "+configs+(sameSet?"==":"!=")+other.configs);
//    return sameSet;
//}
//
//DFAState* DFAState::clone() const
//{
//    return new DFAState(*this);
//}
//
//std::string DFAState::toString() const
//{
//    std::stringstream buf;
//    buf << stateNumber << ":" << configs->toString();
//    if ( isAcceptState ) {
//        buf << "=>";
//        if ( predicates!=NULL ) {
//            buf << Utils::stringValueOfPtrArray(predicates, numPredicates);
//        }
//        else {
//            buf << prediction;
//        }
//    }
//    return buf.str();
//}

} /* namespace dfa */
} /* namespace antlr4 */
