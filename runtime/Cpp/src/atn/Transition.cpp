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

#include <antlr/atn/Transition.h>
#include <antlr/atn/EpsilonTransition.h>
#include <antlr/atn/RangeTransition.h>
#include <antlr/atn/RuleTransition.h>
#include <antlr/atn/PredicateTransition.h>
#include <antlr/atn/AtomTransition.h>
#include <antlr/atn/ActionTransition.h>
#include <antlr/atn/SetTransition.h>
#include <antlr/atn/NotSetTransition.h>
#include <antlr/atn/WildcardTransition.h>
#include <antlr/misc/Utils.h>
#include <algorithm>
#include <stdexcept>


using namespace antlr4::misc;

namespace antlr4 {
namespace atn {


// constants for serialization
const antlr_int32_t Transition::EPSILON     = 1;
const antlr_int32_t Transition::RANGE       = 2;
const antlr_int32_t Transition::RULE        = 3;
const antlr_int32_t Transition::PREDICATE   = 4; // e.g., {isType(input.LT(1))}?
const antlr_int32_t Transition::ATOM        = 5;
const antlr_int32_t Transition::ACTION      = 6;
const antlr_int32_t Transition::SET         = 7; // ~(A|B) or ~atom, wildcard, which convert to next 2
const antlr_int32_t Transition::NOT_SET     = 8;
const antlr_int32_t Transition::WILDCARD    = 9;

const std::vector<std::string> Transition::serializationNames =
    Transition::getSerializationNames();

#if defined(HAVE_CX11)
const HashMap<std::size_t, antlr_int32_t> Transition::serializationTypes =
    Transition::getSerializationTypes();
#else
const std::vector<Transition::TypeInfo> Transition::serializationTypes =
    Transition::getSerializationTypes();
#endif

Transition::Transition(ANTLR_NOTNULL const ATNState* target)
    :   target(target)
{
    if (target == NULL) {
        throw std::logic_error("target cannot be null.");
    }
}

Transition::~Transition()
{
}

std::vector<std::string> Transition::getSerializationNames()
{
    const char* names[] = {
        "INVALID",
        "EPSILON",
        "RANGE",
        "RULE",
        "PREDICATE",
        "ATOM",
        "ACTION",
        "SET",
        "NOT_SET",
        "WILDCARD"
    };
    return std::vector<std::string>(names, names + sizeof(names)/sizeof(names[0]));
}

#if defined(HAVE_CX11)

antlr_int32_t Transition::getSerializationType(const std::type_info& type)
{
    antlr_int32_t* type = serializationTypes.get(type.hash_code());
    if (type == NULL) {
        throw std::logic_error("type not found");
    }
    return *type;
}

HashMap<std::size_t, antlr_int32_t> Transition::getSerializationTypes()
{
    HashMap<std::size_t, antlr_int32_t> types;
    types.put(typeid(EpsilonTransition).hash_code(), EPSILON);
    types.put(typeid(RangeTransition).hash_code(), RANGE);
    types.put(typeid(RuleTransition).hash_code(), RULE);
    types.put(typeid(PredicateTransition).hash_code(), PREDICATE);
    types.put(typeid(AtomTransition).hash_code(), ATOM);
    types.put(typeid(ActionTransition).hash_code(), ACTION);
    types.put(typeid(SetTransition).hash_code(), SET);
    types.put(typeid(NotSetTransition).hash_code(), NOT_SET);
    types.put(typeid(WildcardTransition).hash_code(), WILDCARD);
    return types;
}

#else /* HAVE_CX11 */

antlr_int32_t Transition::getSerializationType(const std::type_info& type)
{
    for (std::vector<TypeInfo>::const_iterator it = serializationTypes.begin();
            it != serializationTypes.end(); it++)
    {
        if (type == *it->first) {
            return it->second;
        }
    }
    throw std::logic_error("type not found");
}

std::vector<Transition::TypeInfo> Transition::getSerializationTypes()
{
    std::vector<TypeInfo> types;
    types.push_back(TypeInfo(&typeid(EpsilonTransition), EPSILON));
    types.push_back(TypeInfo(&typeid(RangeTransition), RANGE));
    types.push_back(TypeInfo(&typeid(RuleTransition), RULE));
    types.push_back(TypeInfo(&typeid(PredicateTransition), PREDICATE));
    types.push_back(TypeInfo(&typeid(AtomTransition), ATOM));
    types.push_back(TypeInfo(&typeid(ActionTransition), ACTION));
    types.push_back(TypeInfo(&typeid(SetTransition), SET));
    types.push_back(TypeInfo(&typeid(NotSetTransition), NOT_SET));
    types.push_back(TypeInfo(&typeid(WildcardTransition), WILDCARD));
    return types;
}

#endif

/** Are we epsilon, action, sempred? */
bool Transition::isEpsilon() const
{
    return false;
}

std::auto_ptr<IntervalSet> Transition::label() const
{
    return std::auto_ptr<IntervalSet>();
}

} /* namespace atn */
} /* namespace antlr4 */
