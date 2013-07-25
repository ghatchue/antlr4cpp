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

#ifndef ATN_CONFIG_SET_H
#define ATN_CONFIG_SET_H

#include <antlr/Definitions.h>
#include <antlr/atn/ATNConfig.h>
#include <antlr/atn/ATNState.h>
#include <antlr/atn/PredictionContext.h>
#include <antlr/misc/Array2DHashSet.h>
#include <antlr/misc/DoubleKeyMap.h>
#include <antlr/misc/HashSet.h>
#include <antlr/misc/Key.h>
#include <antlr/misc/KeyPtr.h>
#include <memory>
#include <vector>



namespace antlr4 { namespace atn { class ATNSimulator; } }

using namespace antlr4::misc;

namespace antlr4 {
namespace atn {

/** Specialized OrderedHashSet that can track info about the set.
 *  Might be able to optimize later w/o affecting code that uses this set.

 histogram of lexer DFA configset size:

 206 30  <- 206 sets with size 30
  47 1
  17 31
  12 2
  10 3
   7 32
   4 4
   3 35
   2 9
   2 6
   2 5
   2 34
   1 7
   1 33
   1 29
   1 12
   1 119 <- max size

 322 set size for SLL parser java.* in DFA states:

 888 1
 411 54
 365 88
 304 56
 206 80
 182 16
 167 86
 166 78
 158 84
 131 2
 121 20
 120 8
 119 112
  82 10
  73 6
  53 174
  47 90
  45 4
  39 12
  38 122
 37 89
 37 62
 34 3
 34 18
 32 81
 31 87
 28 45
 27 144
 25 41
 24 132
 22 91
 22 7
 21 82
 21 28
 21 27
 17 9
 16 29
 16 155
 15 51
 15 118
 14 146
 14 114
 13 5
 13 38
 12 48
 11 64
 11 50
 11 22
 11 134
 11 131
 10 79
 10 76
 10 59
 10 58
 10 55
 10 39
 10 116
  9 74
  9 47
  9 310
   ...

 javalr, java.* configs with # preds histogram:

 4569 0
   57 1
   27 27
    5 76
    4 28
    3 72
    3 38
    3 30
    2 6
    2 32
    1 9
    1 2

 javalr, java.* all atnconfigsets; max size = 322, num sets = 269088

 114186 1    <-- optimize
 35712 6
 28081 78
 15252 54
 14171 56
 13159 12
 11810 88
 6873 86
 6158 80
 5169 4
 3773 118
 2350 16
 1002 112
  915 28
  898 44
  734 2
  632 62
  575 8
  566 59
  474 20
  388 84
  343 48
  333 55
  328 47
  311 41
  306 38
  277 81
  263 79
  255 66
  245 90
  245 87
  234 50
  224 10
  220 60
  194 64
  186 32
  184 82
  150 18
  125 7
  121 132
  116 30
  103 51
   95 114
   84 36
   82 40
   78 22
   77 89
   55 9
   53 174
   48 152
   44 67
   44 5
   42 115
   41 58
   38 122
   37 134
   34 13
   34 116
   29 45
   29 3
   29 24
   27 144
   26 146
   25 91
   24 113
   20 27
   ...

 number with 1-9 elements:

 114186 1
 35712 6
 5169 4
  734 2
  575 8
  125 7
   55 9
   44 5
   29 3

 Can cover 60% of sizes with size up to 6
 Can cover 44% of sizes with size up to 4
 Can cover 42% of sizes with size up to 1
 */
class ANTLR_API ATNConfigSet : public virtual Key<ATNConfigSet>
{
public:
    
    class AbstractConfigHashSet : public Array2DHashSet<ATNConfig>
    {
    public:
        
        AbstractConfigHashSet(const AbstractEqualityComparator<ATNConfig>* comparator);

        AbstractConfigHashSet(const AbstractEqualityComparator<ATNConfig>* comparator,
            antlr_int32_t initialCapacity, antlr_int32_t initialBucketCapacity);
    };
    
    /*
    The reason that we need this is because we don't want the hash map to use
    the standard hash code and equals. We need all configurations with the same
    (s,i,_,semctx) to be equal. Unfortunately, this key effectively doubles
    the number of objects associated with ATNConfigs. The other solution is to
    use a hash table that lets us specify the equals/hashcode operation.
     */
    class ConfigHashSet : public AbstractConfigHashSet
    {
    public:
        
        ConfigHashSet();
    };
    
    class ConfigEqualityComparator : public AbstractEqualityComparator<ATNConfig>
    {
    public:
        
        ANTLR_OVERRIDE
        antlr_int32_t hashCode(const ATNConfig& o) const;

        ANTLR_OVERRIDE
        bool equals(const ATNConfig& a, const ATNConfig& b) const;
        
    private:
        
        ConfigEqualityComparator();

    public:
        
        static const ConfigEqualityComparator INSTANCE;
    };

    
public:
    
    ATNConfigSet();

    ATNConfigSet(bool fullCtx);

    //ATNConfigSet(const ATNConfigSet& old);

    ANTLR_OVERRIDE
    bool add(const ATNConfig& config);

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
    bool add(const ATNConfig& config,
        ANTLR_NULLABLE DoubleKeyMap< KeyPtr<PredictionContext>,KeyPtr<PredictionContext>,KeyPtr<PredictionContext> >* mergeCache);

    /** Return a List holding list of configs */
    const std::vector<ATNConfig>& elements() const;

    antlr_auto_ptr< HashSet<ATNState> > getStates() const;

    antlr_auto_ptr< std::vector<const SemanticContext*> > getPredicates() const;

    const ATNConfig& get(antlr_int32_t i) const;

    void optimizeConfigs(const ATNSimulator& interpreter);

    //ANTLR_OVERRIDE
    //bool addAll(Collection<? extends ATNConfig> coll);

    ANTLR_OVERRIDE
    ATNConfigSet* clone() const;
    
    ANTLR_OVERRIDE
    bool equals(const Key<ATNConfigSet>& o) const;

    ANTLR_OVERRIDE
    antlr_int32_t hashCode() const;

    ANTLR_OVERRIDE
    antlr_uint32_t size() const;

    ANTLR_OVERRIDE
    bool isEmpty() const;

    ANTLR_OVERRIDE
    bool contains(const ATNConfig& o) const;

    bool containsFast(const ATNConfig& obj) const;

    //ANTLR_OVERRIDE
    //Iterator<ATNConfig> iterator();

    ANTLR_OVERRIDE
    void clear();

    bool isReadonly() const;

    void setReadonly(bool readonly);

    ANTLR_OVERRIDE
    std::string toString() const;

    ANTLR_OVERRIDE
    antlr_auto_ptr< std::vector<const ATNConfig*> > toPtrArray() const;

    ANTLR_OVERRIDE
    antlr_auto_ptr< std::vector<ATNConfig> > toArray() const;

    //ANTLR_OVERRIDE
    template <typename U>
    std::vector<U>& toArray(std::vector<U>& a) const;

    //ANTLR_OVERRIDE
    //bool remove(const ATNConfig& o);

    //ANTLR_OVERRIDE
    //boolean containsAll(Collection<?> c);

    //ANTLR_OVERRIDE
    //boolean retainAll(Collection<?> c);

    //ANTLR_OVERRIDE
    //boolean removeAll(Collection<?> c);
    
    
    
    
public:

    /** All configs but hashed by (s, i, _, pi) not incl context.  Wiped out
     *  when we go readonly as this set becomes a DFA state.
     */
    antlr_auto_ptr<AbstractConfigHashSet> configLookup;

    /** Track the elements as they are added to the set; supports get(i) */
    std::vector<ATNConfig> configs;

    // TODO: these fields make me pretty uncomfortable but nice to pack up info together, saves recomputation
    // TODO: can we track conflicts as they are added to save scanning configs later?
    antlr_int32_t uniqueAlt;

    // Used in parser and lexer. In lexer, it indicates we hit a pred
    // while computing a closure operation.  Don't make a DFA state from this.
    bool hasSemanticContext;
    bool dipsIntoOuterContext;

    /** Indicates that this configuration set is part of a full context
     *  LL prediction. It will be used to determine how to merge $. With SLL
     *  it's a wildcard whereas it is not for LL context merge.
     */
    const bool fullCtx;

    
protected:

    /** Indicates that the set of configurations is read-only. Do not
     *  allow any code to manipulate the set; DFA states will point at
     *  the sets and they must not change. This does not protect the other
     *  fields; in particular, conflictingAlts is set after
     *  we've made this readonly.
      */
    bool readonly;

    antlr_auto_ptr< std::vector<bool> > conflictingAlts;

private:

    antlr_int32_t cachedHashCode;
};

template <typename U>
std::vector<U>& ATNConfigSet::toArray(std::vector<U>& a) const
{
    return configLookup->toArray(a);
}


} /* namespace atn */
} /* namespace antlr4 */

#endif /* ifndef ATN_CONFIG_SET_H */
