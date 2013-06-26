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

#ifndef ARRAY_2D_HASH_SET_H
#define ARRAY_2D_HASH_SET_H

#include <Antlr4Definitions.h>
#include <misc/AbstractEqualityComparator.h>
#include <misc/Key.h>
#include <misc/Traits.h>

namespace antlr4 {
namespace misc {

template <typename T, typename K = T,
          bool K_isBaseOf_T = Traits::isSame<K, T>::value || Traits::isBaseOf<K, T>::value>
class ANTLR_API Array2DHashSet;

template <typename T, typename K>
class ANTLR_API Array2DHashSet<T, K, true> : Key< Array2DHashSet<T, K, true> >
{
public:

    class SetIterator
    {
    };

    Array2DHashSet();
    
    Array2DHashSet(ANTLR_NULLABLE const AbstractEqualityComparator<K>* comparator);
    
    Array2DHashSet(ANTLR_NULLABLE AbstractEqualityComparator<K>* comparator,
            antlr_int32_t initialCapacity, antlr_int32_t initialBucketCapacity);

    /**
     * Add {@code o} to set if not there; return existing value if already
     * there. This method performs the same operation as {@link #add} aside from
     * the return value.
     */
    const T* getOrAdd(const T& o);
        
    const T* get(const T& o) const;

    ANTLR_OVERRIDE
    antlr_int32_t hashCode() const;

    ANTLR_OVERRIDE
    bool operator==(Array2DHashSet<T, K, true>& other) const;

    ANTLR_OVERRIDE
    bool add(const T& t);

    ANTLR_OVERRIDE
    antlr_uint32_t size() const;

    ANTLR_OVERRIDE
    bool isEmpty() const;

    ANTLR_OVERRIDE
    bool contains(const T& o) const;

    bool containsFast(ANTLR_NULLABLE const T* obj) const;

    ANTLR_OVERRIDE
    SetIterator iterator();

    ANTLR_OVERRIDE
    std::vector<T> toArray() const;

    //ANTLR_OVERRIDE
    template <typename U>
    std::vector<U>& toArray(std::vector<U>& a) const;

    ANTLR_OVERRIDE
    bool remove(const T& o);

    bool removeFast(ANTLR_NULLABLE const T* obj);

    ANTLR_OVERRIDE
    bool containsAll(Array2DHashSet<T, K, true>& other) const;

    //ANTLR_OVERRIDE
    //boolean addAll(Collection<? extends T> c);

    //ANTLR_OVERRIDE
    //boolean retainAll(Collection<?> c);

    //ANTLR_OVERRIDE
    //boolean removeAll(Collection<?> c);

    ANTLR_OVERRIDE
    void clear();

    ANTLR_OVERRIDE
    std::string toString();

    std::string toTableString();

protected:
        
    const T* getOrAddImpl(const T& o);

    antlr_int32_t getBucket(const T& o) const;

    void expand();

    /**
     * Return an array of {@code T[]} with length {@code capacity}.
     *
     * @param capacity the length of the array to return
     * @return the newly constructed array
     */
    T** createBuckets(antlr_int32_t capacity) const;

    /**
     * Return an array of {@code T} with length {@code capacity}.
     *
     * @param capacity the length of the array to return
     * @return the newly constructed array
     */
    T* createBucket(antlr_int32_t capacity) const;


public:
        
	static const antlr_int32_t INITAL_CAPACITY; // must be power of 2
	static const antlr_int32_t INITAL_BUCKET_CAPACITY;
	static const double LOAD_FACTOR;

protected:
    
    ANTLR_NOTNULL
    const AbstractEqualityComparator<K>* comparator;

    T** buckets;

    /** How many elements in set */
    antlr_uint32_t n;
    
    antlr_int32_t threshold; // when to expand

    antlr_int32_t currentPrime; // jump by 4 primes each expand or whatever
    antlr_int32_t initialBucketCapacity;
};


template <typename T, typename K>
const antlr_int32_t Array2DHashSet<T, K, true>::INITAL_CAPACITY = 16; // must be power of 2

template <typename T, typename K>
const antlr_int32_t Array2DHashSet<T, K, true>::INITAL_BUCKET_CAPACITY = 8;

template <typename T, typename K>
const double Array2DHashSet<T, K, true>::LOAD_FACTOR = 0.75;

template <typename T, typename K>
Array2DHashSet<T, K, true>::Array2DHashSet()
{
}

template <typename T, typename K>
Array2DHashSet<T, K, true>::Array2DHashSet(ANTLR_NULLABLE const AbstractEqualityComparator<K>* comparator)
{
}

template <typename T, typename K>
Array2DHashSet<T, K, true>::Array2DHashSet(ANTLR_NULLABLE AbstractEqualityComparator<K>* comparator,
        antlr_int32_t initialCapacity, antlr_int32_t initialBucketCapacity)
{
}

/**
    * Add {@code o} to set if not there; return existing value if already
    * there. This method performs the same operation as {@link #add} aside from
    * the return value.
    */
template <typename T, typename K>
const T* Array2DHashSet<T, K, true>::getOrAdd(const T& o)
{
    return NULL;
}
        
template <typename T, typename K>
const T* Array2DHashSet<T, K, true>::get(const T& o) const
{
    return NULL;
}

template <typename T, typename K>
antlr_int32_t Array2DHashSet<T, K, true>::hashCode() const
{
    return 0;
}

template <typename T, typename K>
bool Array2DHashSet<T, K, true>::operator==(Array2DHashSet<T, K, true>& other) const
{
    return false;
}

template <typename T, typename K>
bool Array2DHashSet<T, K, true>::add(const T& t)
{
    return false;
}

template <typename T, typename K>
antlr_uint32_t Array2DHashSet<T, K, true>::size() const
{
    return 0;
}

template <typename T, typename K>
bool Array2DHashSet<T, K, true>::isEmpty() const
{
    return false;
}

template <typename T, typename K>
bool Array2DHashSet<T, K, true>::contains(const T& o) const
{
    return false;
}

template <typename T, typename K>
bool Array2DHashSet<T, K, true>::containsFast(ANTLR_NULLABLE const T* obj) const
{
    return false;
}

template <typename T, typename K>
typename Array2DHashSet<T, K, true>::SetIterator Array2DHashSet<T, K, true>::iterator()
{
    return typename Array2DHashSet<T, K, true>::SetIterator();
}

template <typename T, typename K>
std::vector<T> Array2DHashSet<T, K, true>::toArray() const
{
    return std::vector<T>();
}

template <typename T, typename K>
template <typename U>
std::vector<U>& Array2DHashSet<T, K, true>::toArray(std::vector<U>& a) const
{
    return a;
}

template <typename T, typename K>
bool Array2DHashSet<T, K, true>::remove(const T& o)
{
    return false;
}

template <typename T, typename K>
bool Array2DHashSet<T, K, true>::removeFast(ANTLR_NULLABLE const T* obj)
{
    return false;
}

template <typename T, typename K>
bool Array2DHashSet<T, K, true>::containsAll(Array2DHashSet<T, K, true>& other) const
{
    return false;
}

template <typename T, typename K>
void Array2DHashSet<T, K, true>::clear()
{
}

template <typename T, typename K>
std::string Array2DHashSet<T, K, true>::toString()
{
    return std::string();
}

template <typename T, typename K>
std::string Array2DHashSet<T, K, true>::toTableString()
{
    return std::string();
}

template <typename T, typename K>
const T* Array2DHashSet<T, K, true>::getOrAddImpl(const T& o)
{
    return NULL;
}

template <typename T, typename K>
antlr_int32_t Array2DHashSet<T, K, true>::getBucket(const T& o) const
{
    return 0;
}

template <typename T, typename K>
void Array2DHashSet<T, K, true>::expand()
{
}

/**
    * Return an array of {@code T[]} with length {@code capacity}.
    *
    * @param capacity the length of the array to return
    * @return the newly constructed array
    */
template <typename T, typename K>
T** Array2DHashSet<T, K, true>::createBuckets(antlr_int32_t capacity) const
{
    return NULL;
}

/**
    * Return an array of {@code T} with length {@code capacity}.
    *
    * @param capacity the length of the array to return
    * @return the newly constructed array
    */
template <typename T, typename K>
T* Array2DHashSet<T, K, true>::createBucket(antlr_int32_t capacity) const
{
    return NULL;
}

} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef ARRAY_2D_HASH_SET_H */
