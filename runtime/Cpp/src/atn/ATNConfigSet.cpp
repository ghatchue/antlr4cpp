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

#include <antlr/atn/ATN.h>
#include <antlr/atn/ATNConfigSet.h>
#include <antlr/atn/ATNSimulator.h>
#include <antlr/atn/SemanticContext.h>
#include <antlr/misc/MurmurHash.h>
#include <antlr/misc/Utils.h>
#include <algorithm>
#include <stdexcept>
#include <sstream>


namespace antlr4 {
namespace atn {


const ATNConfigSet::ConfigEqualityComparator ATNConfigSet::ConfigEqualityComparator::INSTANCE = ATNConfigSet::ConfigEqualityComparator();

ATNConfigSet::AbstractConfigHashSet::AbstractConfigHashSet(const AbstractEqualityComparator<ATNConfig>* comparator)
    :   Array2DHashSet<ATNConfig>(comparator, 16, 2)
{
}

ATNConfigSet::AbstractConfigHashSet::AbstractConfigHashSet(const AbstractEqualityComparator<ATNConfig>* comparator,
                                                           antlr_int32_t initialCapacity, antlr_int32_t initialBucketCapacity)
    :   Array2DHashSet<ATNConfig>(comparator, initialCapacity, initialBucketCapacity)
{
}

ATNConfigSet::ConfigHashSet::ConfigHashSet()
    :   AbstractConfigHashSet(&ConfigEqualityComparator::INSTANCE)
{
}

ATNConfigSet::ConfigEqualityComparator::ConfigEqualityComparator()
{
}

antlr_int32_t ATNConfigSet::ConfigEqualityComparator::hashCode(const ATNConfig& o) const
{
    antlr_int32_t hashCode = 7;
    hashCode = 31 * hashCode + o.state->stateNumber;
    hashCode = 31 * hashCode + o.alt;
    hashCode = 31 * hashCode + o.semanticContext->hashCode();
    return hashCode;
}

bool ATNConfigSet::ConfigEqualityComparator::equals(const ATNConfig& a, const ATNConfig& b) const
{
    if ( a==b ) return true;
    //if ( a.get()==NULL || b.get()==NULL ) return false;
    return a.state->stateNumber==b.state->stateNumber
        && a.alt==b.alt
        && a.semanticContext->equals(b.semanticContext);
}

ATNConfigSet::ATNConfigSet()
    :   configLookup(new ConfigHashSet()),
        uniqueAlt(0),
        hasSemanticContext(false),
        dipsIntoOuterContext(false),
        fullCtx(true),
        readonly(false),
        cachedHashCode(-1)
{
    configs.reserve(7);
}

ATNConfigSet::ATNConfigSet(bool fullCtx)
    :   configLookup(new ConfigHashSet()),
        uniqueAlt(0),
        hasSemanticContext(false),
        dipsIntoOuterContext(false),
        fullCtx(fullCtx),
        readonly(false),
        cachedHashCode(-1)
{
    configs.reserve(7);
}

bool ATNConfigSet::add(const ATNConfig& config)
{
    return add(config, NULL);
}

/**
 * Adding a new config means merging contexts with existing configs for
 * {@code (s, i, pi, _)}, where {@code s} is the
 * {@link ATNConfig#state}, {@code i} is the {@link ATNConfig#alt}, and
 * {@code pi} is the {@link ATNConfig#semanticContext}. We use
 * {@code (s,i,pi)} as key.
 * <p/>
 * This method updates {@link #dipsIntoOuterContext} and
 * {@link #hasSemanticContext} when necessary.
 */
bool ATNConfigSet::add(const ATNConfig& config,
        ANTLR_NULLABLE DoubleKeyMap< KeyPtr<PredictionContext>,KeyPtr<PredictionContext>,KeyPtr<PredictionContext> >* mergeCache)
{
    if ( readonly ) throw std::logic_error("This set is readonly");
    if ( config.semanticContext->operator !=(SemanticContext::NONE) ) {
        hasSemanticContext = true;
    }
    if (config.reachesIntoOuterContext > 0) {
        dipsIntoOuterContext = true;
    }
    bool added = false;
    const ATNConfig* existing = configLookup->getOrAdd(config, added);
    if ( added ) { // we added this new one
        cachedHashCode = -1;
        configs.push_back(config);  // track order here
        return true;
    }
    // a previous (s,i,pi,_), merge with it and save result
    bool rootIsWildcard = !fullCtx;
    PredictionContext* merged =
        PredictionContext::merge(existing->context, config.context, rootIsWildcard, mergeCache);
    // no need to check for existing.context, config.context in cache
    // since only way to create new graphs is "call rule" and here. We
    // cache at both places.
    const_cast<ATNConfig*>(existing)->reachesIntoOuterContext =
        std::max(existing->reachesIntoOuterContext, config.reachesIntoOuterContext);
    const_cast<ATNConfig*>(existing)->context = merged; // replace context; no need to alt mapping
    return true;
}

/** Return a List holding list of configs */
const std::vector<ATNConfig>& ATNConfigSet::elements() const
{
    return configs;
}

antlr_auto_ptr< HashSet<ATNState> > ATNConfigSet::getStates() const
{
    antlr_auto_ptr< HashSet<ATNState> > states(new HashSet<ATNState>());
    for (std::vector<ATNConfig>::const_iterator it = configs.begin();
            it != configs.end(); it++) {
        states->add(*it->state);
    }
    return states;
}

antlr_auto_ptr< std::vector<const SemanticContext*> > ATNConfigSet::getPredicates() const
{
    antlr_auto_ptr< std::vector<const SemanticContext*> > preds(new std::vector<const SemanticContext*>());
    for (std::vector<ATNConfig>::const_iterator it = configs.begin();
            it != configs.end(); it++) {
        if (it->semanticContext->operator !=(SemanticContext::NONE)) {
            preds->push_back(it->semanticContext);
        }
    }
    return preds;
}

const ATNConfig& ATNConfigSet::get(antlr_int32_t i) const
{
    return configs.at(i);
}

void ATNConfigSet::optimizeConfigs(const ATNSimulator& interpreter)
{
    if ( readonly ) throw std::logic_error("This set is readonly");
    if ( configLookup->isEmpty() ) return;

    for (std::vector<ATNConfig>::iterator it = configs.begin();
            it != configs.end(); it++) {
        // int before = PredictionContext.getAllContextNodes(config.context).size();
            it->context = interpreter.getCachedContext(it->context);
        // int after = PredictionContext.getAllContextNodes(config.context).size();
        // System.out.println("configs "+before+"->"+after);
    }
}

ATNConfigSet* ATNConfigSet::clone() const
{
    throw std::logic_error("ATNConfigSet::clone not supported");
}

bool ATNConfigSet::equals(const Key<ATNConfigSet>* o) const
{
    const ATNConfigSet* other = dynamic_cast<const ATNConfigSet*>(o);
    if (other == NULL) {
        return false;
    }

    // System.out.print("equals " + this + ", " + o+" = ");
    bool same =
        configs == (other->configs) &&  // includes stack context
        this->fullCtx == other->fullCtx &&
        this->uniqueAlt == other->uniqueAlt &&
        Utils::equals(this->conflictingAlts, other->conflictingAlts) &&
        this->hasSemanticContext == other->hasSemanticContext &&
        this->dipsIntoOuterContext == other->dipsIntoOuterContext;

    // System.out.println(same);
    return same;
}

antlr_int32_t ATNConfigSet::hashCode() const
{
    if (isReadonly()) {
        if (cachedHashCode == -1) {
            const_cast<ATNConfigSet*>(this)->cachedHashCode = MurmurHash::hashCode(configs, 7);
        }

        return cachedHashCode;
    }

    return MurmurHash::hashCode(configs, 7);
}

antlr_uint32_t ATNConfigSet::size() const
{
    return static_cast<antlr_uint32_t>(configs.size());
}

bool ATNConfigSet::isEmpty() const
{
    return configs.empty();
}

bool ATNConfigSet::contains(const ATNConfig& o) const
{
    if (configLookup.get() == NULL) {
        throw std::logic_error("This method is not implemented for readonly sets.");
    }

    return configLookup->contains(o);
}

bool ATNConfigSet::containsFast(const ATNConfig& obj) const
{
    if (configLookup.get() == NULL) {
        throw std::logic_error("This method is not implemented for readonly sets.");
    }

    return configLookup->containsFast(&obj);
}

void ATNConfigSet::clear()
{
    if ( readonly ) throw std::logic_error("This set is readonly");
    configs.clear();
    cachedHashCode = -1;
    configLookup->clear();
}

bool ATNConfigSet::isReadonly() const
{
    return readonly;
}

void ATNConfigSet::setReadonly(bool readonly)
{
    this->readonly = readonly;
    configLookup.reset();   // can't mod, no need for lookup cache
}

std::string ATNConfigSet::toString() const
{
    std::stringstream buf;
    buf << Utils::stringValueOf(elements());
    if ( hasSemanticContext ) buf << std::boolalpha << ",hasSemanticContext=" << hasSemanticContext;
    if ( uniqueAlt!=ATN::INVALID_ALT_NUMBER ) buf << ",uniqueAlt=" << uniqueAlt;
    if ( conflictingAlts.get()!=NULL ) buf << ",conflictingAlts=" << Utils::stringValueOf(*conflictingAlts);
    if ( dipsIntoOuterContext ) buf << ",dipsIntoOuterContext";
    return buf.str();
}

antlr_auto_ptr< std::vector<const ATNConfig*> > ATNConfigSet::toPtrArray() const
{
    return configLookup->toPtrArray();
}

antlr_auto_ptr< std::vector<ATNConfig> > ATNConfigSet::toArray() const
{
    return configLookup->toArray();
}


} /* namespace atn */
} /* namespace antlr4 */
