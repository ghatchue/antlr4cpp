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

#include <Antlr4Definitions.h>
#include <misc/AbstractEqualityComparator.h>
#include <misc/HashMap.h>
#include <misc/Key.h>
#include <misc/Traits.h>
#include <misc/Utils.h>
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
class ANTLR_API FlexibleHashMap<K, V, B, true> : Key< FlexibleHashMap<K, V, B, true> >
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

//    ~FlexibleHashMap();
//    
//	FlexibleHashMap();
//
//	FlexibleHashMap(ANTLR_NULLABLE const AbstractEqualityComparator<B>* comparator);
//
//	FlexibleHashMap(ANTLR_NULLABLE const AbstractEqualityComparator<B>* comparator,
//            antlr_int32_t initialCapacity, antlr_int32_t initialBucketCapacity);
//    
//
//    ANTLR_OVERRIDE
//    const V* get(const K& key) const;
//
//    ANTLR_OVERRIDE
//    const V* put(const K& key, const V& value);
//
//    ANTLR_OVERRIDE
//    void remove(const K& key);
//
//    //ANTLR_OVERRIDE
//    //void putAll(Map<? extends K, ? extends V> m) {
//
//    //ANTLR_OVERRIDE
//    //Set<K> keySet() {
//
//    ANTLR_OVERRIDE
//    std::vector<const V*> values() const;
//
//    //ANTLR_OVERRIDE
//    //Set<Map.Entry<K, V>> entrySet() {
//
//    ANTLR_OVERRIDE
//    bool containsKey(const K& key) const;
//
//    ANTLR_OVERRIDE
//    bool containsValue(const V& value) const;
//
//    ANTLR_OVERRIDE
//    antlr_int32_t hashCode() const;
//
//    ANTLR_OVERRIDE
//    bool operator==(FlexibleHashMap<K, V, B, true>& other) const;
//
//    ANTLR_OVERRIDE
//    antlr_uint32_t size() const;
//
//    ANTLR_OVERRIDE
//    bool isEmpty() const;
//    
//    ANTLR_OVERRIDE
//    void clear();
//
//    ANTLR_OVERRIDE
//    std::string toString() const;
//
//    std::string toTableString() const;
//    
//
//protected:
//
//    antlr_int32_t getBucket(const K& key) const;
//    
//    void expand();    
//    
//    void initialize(ANTLR_NULLABLE const AbstractEqualityComparator<B>* comparator,
//        antlr_int32_t initialCapacity, antlr_int32_t initialBucketCapacity);
//    
//    /* De-allocate buckets */
//    void cleanup();
//    
//private:
//    
//    static std::list<Entry>* createEntryListArray(antlr_int32_t length);    

public:

	static const antlr_int32_t INITAL_CAPACITY;    // must be power of 2
	static const antlr_int32_t INITAL_BUCKET_CAPACITY;
	static const double LOAD_FACTOR;

protected:
    
	ANTLR_NOTNULL
    const AbstractEqualityComparator<B>* comparator;

	std::list<Entry>* buckets;
    
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

//template <typename K, typename V, typename B>
//~FlexibleHashMap<K, V, B, true>::FlexibleHashMap()
//{
//    cleanup();
//}
//
//template <typename K, typename V, typename B>
//FlexibleHashMap<K, V, B, true>::FlexibleHashMap()
//    :   comparator(NULL),
//        buckets(NULL),
//        numBuckets(0),
//        n(0),
//        threshold((antlr_uint32_t)(INITAL_CAPACITY * LOAD_FACTOR)),
//        currentPrime(1),
//        initialBucketCapacity(INITAL_BUCKET_CAPACITY)
//{
//    initialize(NULL, INITAL_CAPACITY, INITAL_BUCKET_CAPACITY);
//}
//
//
//template <typename K, typename V, typename B>
//FlexibleHashMap<K, V, B, true>::FlexibleHashMap(ANTLR_NULLABLE const AbstractEqualityComparator<B>* comparator)
//    :   comparator(NULL),
//        buckets(NULL),
//        numBuckets(0),
//        n(0),
//        threshold((antlr_uint32_t)(INITAL_CAPACITY * LOAD_FACTOR)),
//        currentPrime(1),
//        initialBucketCapacity(INITAL_BUCKET_CAPACITY)
//{
//    initialize(comparator, INITAL_CAPACITY, INITAL_BUCKET_CAPACITY);
//}
//
//template <typename K, typename V, typename B>
//FlexibleHashMap<K, V, B, true>::FlexibleHashMap(ANTLR_NULLABLE const AbstractEqualityComparator<B>* comparator,
//        antlr_int32_t initialCapacity, antlr_int32_t initialBucketCapacity)
//    :   comparator(NULL),
//        buckets(NULL),
//        numBuckets(0),
//        n(0),
//        threshold((antlr_uint32_t)(INITAL_CAPACITY * LOAD_FACTOR)),
//        currentPrime(1),
//        initialBucketCapacity(INITAL_BUCKET_CAPACITY)
//{
//    initialize(comparator, initialCapacity, initialBucketCapacity);
//}
//
//template <typename K, typename V, typename B>
//const V* FlexibleHashMap<K, V, B, true>::get(const K& key) const
//{
//    antlr_int32_t b = getBucket(key);
//    std::list<Entry>& bucket = buckets[b];
//    if ( bucket==null ) return null; // no bucket
//    for (Entry<K, V> e : bucket) {
//        if ( comparator.equals(e.key, typedKey) ) {
//            return e.value;
//        }
//    }
//    return null;
//}
//
//template <typename K, typename V, typename B>
//const V* FlexibleHashMap<K, V, B, true>::put(const K& key, const V& value);
//
//template <typename K, typename V, typename B>
//void FlexibleHashMap<K, V, B, true>::remove(const K& key);
//
//template <typename K, typename V, typename B>
//std::vector<const V*> FlexibleHashMap<K, V, B, true>::values() const;
//
//template <typename K, typename V, typename B>
//bool FlexibleHashMap<K, V, B, true>::containsKey(const K& key) const;
//
//template <typename K, typename V, typename B>
//bool FlexibleHashMap<K, V, B, true>::containsValue(const V& value) const;
//
//template <typename K, typename V, typename B>
//antlr_int32_t FlexibleHashMap<K, V, B, true>::hashCode() const;
//
//template <typename K, typename V, typename B>
//bool FlexibleHashMap<K, V, B, true>::operator==(FlexibleHashMap<K, V, B, true>& other) const;
//
//template <typename K, typename V, typename B>
//antlr_uint32_t FlexibleHashMap<K, V, B, true>::size() const;
//
//template <typename K, typename V, typename B>
//bool FlexibleHashMap<K, V, B, true>::isEmpty() const;
//
//template <typename K, typename V, typename B>
//void FlexibleHashMap<K, V, B, true>::clear();
//
//template <typename K, typename V, typename B>
//std::string FlexibleHashMap<K, V, B, true>::toString() const;
//
//template <typename K, typename V, typename B>
//std::string FlexibleHashMap<K, V, B, true>::toTableString() const;
//
//template <typename K, typename V, typename B>
//antlr_int32_t FlexibleHashMap<K, V, B, true>::getBucket(const K& key) const;
//
//template <typename K, typename V, typename B>
//void FlexibleHashMap<K, V, B, true>::expand();    
//
//template <typename K, typename V, typename B>
//void FlexibleHashMap<K, V, B, true>::initialize(ANTLR_NULLABLE const AbstractEqualityComparator<B>* comparator,
//    antlr_int32_t initialCapacity, antlr_int32_t initialBucketCapacity);
//
///* De-allocate buckets */
//template <typename K, typename V, typename B>
//void FlexibleHashMap<K, V, B, true>::cleanup();
//
//template <typename K, typename V, typename B>
//std::list<Entry>* FlexibleHashMap<K, V, B, true>::createEntryListArray(antlr_int32_t length);    


} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef FLEXIBLE_HASH_MAP_H */
