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
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR AS IS'' AND ANY EXPRESS OR
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

#ifndef TRANSITION_H
#define TRANSITION_H

#include <antlr/Definitions.h>
#include <antlr/misc/HashMap.h>
#include <antlr/misc/IntervalSet.h>
#include <memory>
#include <string>
#include <typeinfo>
#include <vector>


namespace antlr4 { namespace atn { class ATNState; } }

using namespace antlr4::misc;

namespace antlr4 {
namespace atn {

/** An ATN transition between any two ATN states.  Subclasses define
 *  atom, set, epsilon, action, predicate, rule transitions.
 * <p/>
 *  This is a one way link.  It emanates from a state (usually via a list of
 *  transitions) and has a target state.
 * <p/>
 *  Since we never have to change the ATN transitions once we construct it,
 *  we can fix these transitions as specific classes. The DFA transitions
 *  on the other hand need to update the labels as it adds transitions to
 *  the states. We'll use the term Edge for the DFA to distinguish them from
 *  ATN transitions.
 */
class ANTLR_API Transition
{
public:
    
    ~Transition();
    
    static antlr_int32_t getSerializationType(const std::type_info& type);

    virtual antlr_int32_t getSerializationType() const = 0;

    /** Are we epsilon, action, sempred? */
    virtual bool isEpsilon() const;

    ANTLR_NULLABLE
    virtual antlr_auto_ptr<IntervalSet> label() const;

    virtual bool matches(antlr_int32_t symbol, antlr_int32_t minVocabSymbol, antlr_int32_t maxVocabSymbol) const = 0;
    
    virtual std::string toString() const = 0;

protected:
    
    Transition(ANTLR_NOTNULL const ATNState* target);

private:
    
    static std::vector<std::string> getSerializationNames();

#if defined(HAVE_CX11)
    static HashMap<std::size_t, antlr_int32_t> getSerializationTypes();
    static const HashMap<std::size_t, antlr_int32_t> serializationTypes;    
#else
    typedef std::pair<const std::type_info*, antlr_int32_t> TypeInfo;
    static std::vector<TypeInfo> getSerializationTypes();
    static const std::vector<TypeInfo> serializationTypes;    
#endif
    
public:
    
    // constants for serialization
    static const antlr_int32_t EPSILON;
    static const antlr_int32_t RANGE;
    static const antlr_int32_t RULE;
    static const antlr_int32_t PREDICATE;
    static const antlr_int32_t ATOM;
    static const antlr_int32_t ACTION;
    static const antlr_int32_t SET;
    static const antlr_int32_t NOT_SET;
    static const antlr_int32_t WILDCARD;
    
    static const std::vector<std::string> serializationNames;
    
    /** The target of this transition. */
    ANTLR_NOTNULL
    const ATNState* target;

};


} /* namespace atn */
} /* namespace antlr4 */

#endif /* ifndef TRANSITION_H */
