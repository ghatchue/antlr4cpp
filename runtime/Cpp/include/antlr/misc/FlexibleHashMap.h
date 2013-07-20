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

#ifndef FLEXIBLE_HASH_MAP_H
#define FLEXIBLE_HASH_MAP_H

#include <antlr/Definitions.h>
#include <antlr/misc/AbstractEqualityComparator.h>
#include <antlr/misc/HashMap.h>
#include <antlr/misc/Key.h>
#include <antlr/misc/MurmurHash.h>
#include <antlr/misc/ObjectEqualityComparator.h>
#include <antlr/misc/Traits.h>
#include <antlr/misc/Utils.h>
#include <cassert>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <string>

namespace antlr4 {
namespace misc {


/** A limited map (many unsupported operations) that lets me use
 *  varying hashCode/equals.
 */
template <typename K, typename V, typename B = K, bool B_isBaseOf_K = Traits::super<B, K>::value>
class ANTLR_API FlexibleHashMap;


/** A limited map (many unsupported operations) that lets me use
 *  varying hashCode/equals.
 */
template <typename K, typename V, typename B>
class ANTLR_API FlexibleHashMap<K, V, B, true> : public virtual Key< FlexibleHashMap<K, V, B, true> >
{
public:
    
	class Entry
    {
    public:
        
		Entry(const K& key, const V& value);
		Entry(const Entry& other);

		ANTLR_OVERRIDE
        std::string toString() const;
        
    public:
		const K key;
		V value;
	};
    
public:

    ~FlexibleHashMap();
    
	FlexibleHashMap();

	FlexibleHashMap(ANTLR_NULLABLE const AbstractEqualityComparator<B>* comparator);

	FlexibleHashMap(ANTLR_NULLABLE const AbstractEqualityComparator<B>* comparator,
            antlr_int32_t initialCapacity, antlr_int32_t initialBucketCapacity);
    

    ANTLR_OVERRIDE
    const V* get(const K& key) const;

    ANTLR_OVERRIDE
    const V* put(const K& key, const V& value);

    ANTLR_OVERRIDE
    void remove(const K& key);

    //ANTLR_OVERRIDE
    //void putAll(Map<? extends K, ? extends V> m) {

    //ANTLR_OVERRIDE
    //Set<K> keySet() {

    ANTLR_OVERRIDE
    std::vector<const V*> values() const;

    //ANTLR_OVERRIDE
    //Set<Map.Entry<K, V>> entrySet() {

    ANTLR_OVERRIDE
    bool containsKey(const K& key) const;

    ANTLR_OVERRIDE
    bool containsValue(const V& value) const;

    ANTLR_OVERRIDE
    antlr_int32_t hashCode() const;

    ANTLR_OVERRIDE
    bool equals(const Key< FlexibleHashMap<K, V, B, true> >& other) const;
    
    ANTLR_OVERRIDE
    FlexibleHashMap<K, V, B, true>* clone() const;

    ANTLR_OVERRIDE
    antlr_uint32_t size() const;

    ANTLR_OVERRIDE
    bool isEmpty() const;
    
    ANTLR_OVERRIDE
    void clear();

    ANTLR_OVERRIDE
    std::string toString() const;

    std::string toTableString() const;
    

protected:

    antlr_int32_t getBucket(const K& key) const;
    
    void expand();    
    
    void initialize(ANTLR_NULLABLE const AbstractEqualityComparator<B>* comparator,
        antlr_int32_t initialCapacity, antlr_int32_t initialBucketCapacity);
    
    /* De-allocate buckets */
    void cleanup();
    
private:
    
    static std::list<Entry>** createEntryListArray(antlr_int32_t length);    

public:

	static const antlr_int32_t INITAL_CAPACITY;    // must be power of 2
	static const antlr_int32_t INITAL_BUCKET_CAPACITY;
	static const double LOAD_FACTOR;

protected:
    
	ANTLR_NOTNULL
    const AbstractEqualityComparator<B>* comparator;

	std::list<Entry>** buckets;
    
    antlr_int32_t numBuckets;

	/** How many elements in set */
	antlr_uint32_t n;

	antlr_uint32_t threshold;    // when to expand

	antlr_int32_t currentPrime; // jump by 4 primes each expand or whatever
	antlr_int32_t initialBucketCapacity;
};


template <typename K, typename V, typename B>
const antlr_int32_t FlexibleHashMap<K, V, B, true>::INITAL_CAPACITY = 16;    // must be power of 2
template <typename K, typename V, typename B>
const antlr_int32_t FlexibleHashMap<K, V, B, true>::INITAL_BUCKET_CAPACITY = 8;
template <typename K, typename V, typename B>
const double FlexibleHashMap<K, V, B, true>::LOAD_FACTOR = 0.75;

template <typename K, typename V, typename B>
FlexibleHashMap<K, V, B, true>::Entry::Entry(const K& key, const V& value)
    :   key(key),
        value(value)
{
}

template <typename K, typename V, typename B>
FlexibleHashMap<K, V, B, true>::Entry::Entry(const Entry& other)
    :   key(other.key),
        value(other.value)
{
}

template <typename K, typename V, typename B>
std::string FlexibleHashMap<K, V, B, true>::Entry::toString() const
{
    return Utils::stringValueOf(key)+":"+Utils::stringValueOf(value);
}

template <typename K, typename V, typename B>
FlexibleHashMap<K, V, B, true>::~FlexibleHashMap()
{
    cleanup();
}

template <typename K, typename V, typename B>
FlexibleHashMap<K, V, B, true>::FlexibleHashMap()
    :   comparator(NULL),
        buckets(NULL),
        numBuckets(0),
        n(0),
        threshold((antlr_uint32_t)(INITAL_CAPACITY * LOAD_FACTOR)),
        currentPrime(1),
        initialBucketCapacity(INITAL_BUCKET_CAPACITY)
{
    initialize(NULL, INITAL_CAPACITY, INITAL_BUCKET_CAPACITY);
}


template <typename K, typename V, typename B>
FlexibleHashMap<K, V, B, true>::FlexibleHashMap(ANTLR_NULLABLE const AbstractEqualityComparator<B>* comparator)
    :   comparator(NULL),
        buckets(NULL),
        numBuckets(0),
        n(0),
        threshold((antlr_uint32_t)(INITAL_CAPACITY * LOAD_FACTOR)),
        currentPrime(1),
        initialBucketCapacity(INITAL_BUCKET_CAPACITY)
{
    initialize(comparator, INITAL_CAPACITY, INITAL_BUCKET_CAPACITY);
}

template <typename K, typename V, typename B>
FlexibleHashMap<K, V, B, true>::FlexibleHashMap(ANTLR_NULLABLE const AbstractEqualityComparator<B>* comparator,
        antlr_int32_t initialCapacity, antlr_int32_t initialBucketCapacity)
    :   comparator(NULL),
        buckets(NULL),
        numBuckets(0),
        n(0),
        threshold((antlr_uint32_t)(INITAL_CAPACITY * LOAD_FACTOR)),
        currentPrime(1),
        initialBucketCapacity(INITAL_BUCKET_CAPACITY)
{
    initialize(comparator, initialCapacity, initialBucketCapacity);
}

template <typename K, typename V, typename B>
const V* FlexibleHashMap<K, V, B, true>::get(const K& key) const
{
    antlr_int32_t b = getBucket(key);
    std::list<Entry>* bucket = buckets[b];
    if ( bucket==NULL ) return NULL; // no bucket
    for (typename std::list<Entry>::const_iterator it = bucket->begin(); it != bucket->end(); it++) {
        const Entry& e = *it;
        if ( comparator->equals(e.key, key) ) {
            return &e.value;
        }
    }
    return NULL;
}

template <typename K, typename V, typename B>
const V* FlexibleHashMap<K, V, B, true>::put(const K& key, const V& value)
{
    if ( n > threshold ) expand();
    antlr_int32_t b = getBucket(key);
    std::list<Entry>* bucket = buckets[b];
    if ( bucket==NULL ) {
        bucket = (buckets[b] = new std::list<Entry>());
    }
    for (typename std::list<Entry>::iterator it = bucket->begin(); it != bucket->end(); it++) {
        Entry& e = *it;
        if ( comparator->equals(e.key, key) ) {
            e.value = value;
            return &e.value;
        }    
    }
    // not there
    bucket->push_back(Entry(key, value));
    n++;
    return &bucket->back().value;
}

template <typename K, typename V, typename B>
void FlexibleHashMap<K, V, B, true>::remove(const K& key)
{
    antlr_int32_t b = getBucket(key);
    std::list<Entry>* bucket = buckets[b];
    if ( bucket==NULL ) return; // no bucket
    for (typename std::list<Entry>::iterator it = bucket->begin(); it != bucket->end(); it++) {
        if ( comparator->equals(it->key, key) ) {
            bucket->erase(it);
            n--;
            return;
        }
    }
}

template <typename K, typename V, typename B>
std::vector<const V*> FlexibleHashMap<K, V, B, true>::values() const
{
    std::vector<const V*> a;
    a.reserve(size());
    for (antlr_int32_t i = 0; i < numBuckets; i++) {
        const std::list<Entry>* bucket = buckets[i];
        if ( bucket==NULL ) continue;
        for (typename std::list<Entry>::const_iterator it = bucket->begin(); it != bucket->end(); it++) {
            const Entry& e = *it;
            a.push_back(&e.value);
        }
    }
    return a;
}

template <typename K, typename V, typename B>
bool FlexibleHashMap<K, V, B, true>::containsKey(const K& key) const
{
    return get(key)!=NULL;
}

template <typename K, typename V, typename B>
bool FlexibleHashMap<K, V, B, true>::containsValue(const V&) const
{
    throw std::logic_error("FlexibleHashMap::containsValue not supported");
}

template <typename K, typename V, typename B>
antlr_int32_t FlexibleHashMap<K, V, B, true>::hashCode() const
{
    antlr_int32_t hash = MurmurHash::initialize();
    for (antlr_int32_t i = 0; i < numBuckets; i++) {
        const std::list<Entry>* bucket = buckets[i];
        if ( bucket==NULL ) continue;
        for (typename std::list<Entry>::const_iterator it = bucket->begin(); it != bucket->end(); it++) {
            const Entry& e = *it;
            hash = MurmurHash::update(hash, comparator->hashCode(e.key));
        }
    }
    hash = MurmurHash::finish(hash, size());
    return hash;
}

template <typename K, typename V, typename B>
bool FlexibleHashMap<K, V, B, true>::equals(const Key< FlexibleHashMap<K, V, B, true> >&) const
{
    throw std::logic_error("FlexibleHashMap::equals not supported");
}

template <typename K, typename V, typename B>
FlexibleHashMap<K, V, B, true>* FlexibleHashMap<K, V, B, true>::clone() const
{
    throw std::logic_error("FlexibleHashMap::clone not supported");
}

template <typename K, typename V, typename B>
antlr_uint32_t FlexibleHashMap<K, V, B, true>::size() const
{
    return n;
}

template <typename K, typename V, typename B>
bool FlexibleHashMap<K, V, B, true>::isEmpty() const
{
    return n==0;
}

template <typename K, typename V, typename B>
void FlexibleHashMap<K, V, B, true>::clear()
{
    cleanup();
    numBuckets = INITAL_CAPACITY;
    buckets = createEntryListArray(INITAL_CAPACITY);
    n = 0;
}

template <typename K, typename V, typename B>
std::string FlexibleHashMap<K, V, B, true>::toString() const
{
    if ( size()==0 ) return "{}";

    std::stringstream buf;
    buf << "{";
    bool first = true;
    for (antlr_int32_t i = 0; i < numBuckets; i++) {
        const std::list<Entry>* bucket = buckets[i];
        if ( bucket==NULL ) continue;
        for (typename std::list<Entry>::const_iterator it = bucket->begin(); it != bucket->end(); it++) {
            const Entry& e = *it;
            if ( first ) first=false;
            else buf << ", ";
            buf << e.toString();
        }
    }
    buf << "}";
    return buf.str();
}

template <typename K, typename V, typename B>
std::string FlexibleHashMap<K, V, B, true>::toTableString() const
{
    std::stringstream buf;
    for (antlr_int32_t i = 0; i < numBuckets; i++) {
        const std::list<Entry>* bucket = buckets[i];
        if ( bucket==NULL ) {
            buf << "null\n";
            continue;
        }
        buf << "[";
        bool first = true;
        for (typename std::list<Entry>::const_iterator it = bucket->begin(); it != bucket->end(); it++) {
            const Entry& e = *it;
            if ( first ) first=false;
            else buf << " ";
            buf << e.toString();
        }
        buf << "]\n";
    }
    return buf.str();
}

template <typename K, typename V, typename B>
antlr_int32_t FlexibleHashMap<K, V, B, true>::getBucket(const K& key) const
{
    antlr_int32_t hash = comparator->hashCode(key);
    antlr_int32_t b = hash & (numBuckets-1); // assumes len is power of 2
    return b;
}

template <typename K, typename V, typename B>
void FlexibleHashMap<K, V, B, true>::expand()
{
    std::list<Entry>** old = buckets;
    antlr_int32_t oldNumBuckets = numBuckets;
    currentPrime += 4;
    antlr_int32_t newCapacity = numBuckets * 2;
    numBuckets = newCapacity;
    std::list<Entry>** newTable = createEntryListArray(newCapacity);
    buckets = newTable;
    threshold = (antlr_uint32_t)(newCapacity * LOAD_FACTOR);
    //System.out.println("new size="+newCapacity+calc", thres="+threshold);
    // rehash all existing entries
    antlr_uint32_t oldSize = size();
    n = 0;
    for (antlr_int32_t i = 0; i < oldNumBuckets; i++) {
        const std::list<Entry>* bucket = old[i];
        if ( bucket==NULL ) continue;
        for (typename std::list<Entry>::const_iterator it = bucket->begin(); it != bucket->end(); it++) {
            const Entry& e = *it;
            put(e.key, e.value);
        }
        delete bucket;
    }
    delete[] old;
    assert(n == oldSize);
}

template <typename K, typename V, typename B>
void FlexibleHashMap<K, V, B, true>::initialize(ANTLR_NULLABLE const AbstractEqualityComparator<B>* comparator,
    antlr_int32_t initialCapacity, antlr_int32_t initialBucketCapacity)
{
    if (comparator == NULL) {
        comparator = &ObjectEqualityComparator<B>::INSTANCE;
    }

    this->comparator = comparator;
    this->numBuckets = initialCapacity;
    this->buckets = createEntryListArray(initialCapacity);
    this->initialBucketCapacity = initialBucketCapacity;
}

/* De-allocate buckets */
template <typename K, typename V, typename B>
void FlexibleHashMap<K, V, B, true>::cleanup()
{
    for (antlr_int32_t i = 0; i < numBuckets; i++) {
        delete buckets[i];
    }
    delete[] buckets;
    buckets = NULL;
    numBuckets = 0;
    n = 0;
}

template <typename K, typename V, typename B>
std::list<typename FlexibleHashMap<K, V, B, true>::Entry>** FlexibleHashMap<K, V, B, true>::createEntryListArray(antlr_int32_t length)
{
    std::list<Entry>** result = new std::list<Entry>*[length];
    memset(result, 0, sizeof(std::list<Entry>*) * length);
    return result;
}


} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef FLEXIBLE_HASH_MAP_H */
