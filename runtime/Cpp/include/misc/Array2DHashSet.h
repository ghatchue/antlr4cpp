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

    bool containsFast(ANTLR_NULLABLE const T* obj);

//    ANTLR_OVERRIDE
//    Iterator<T> iterator();
//
//    ANTLR_OVERRIDE
//    T[] toArray();
//
//    ANTLR_OVERRIDE
//    <U> U[] toArray(U[] a);
//
//    ANTLR_OVERRIDE
//    final boolean remove(Object o);
//
//    boolean removeFast(ANTLR_NULLABLE T obj);
//
//    ANTLR_OVERRIDE
//    boolean containsAll(Collection<?> collection);
//
//    ANTLR_OVERRIDE
//    boolean addAll(Collection<? extends T> c);
//
//    ANTLR_OVERRIDE
//    boolean retainAll(Collection<?> c);
//
//    ANTLR_OVERRIDE
//    boolean removeAll(Collection<?> c);
//
//    ANTLR_OVERRIDE
//    void clear();
//
//    ANTLR_OVERRIDE
//    String toString();
//
//    String toTableString();
//
//
//protected:
//        
//    protected T getOrAddImpl(T o);
//
//    protected final int getBucket(T o);
//   
//    protected void expand()
//        
//    /**
//     * Return {@code o} as an instance of the element type {@code T}. If
//     * {@code o} is non-null but known to not be an instance of {@code T}, this
//     * method returns {@code null}. The base implementation does not perform any
//     * type checks; override this method to provide strong type checks for the
//     * {@link #contains} and {@link #remove} methods to ensure the arguments to
//     * the {@link EqualityComparator} for the set always have the expected
//     * types.
//     *
//     * @param o the object to try and cast to the element type of the set
//     * @return {@code o} if it could be an instance of {@code T}, otherwise
//     * {@code null}.
//     */
//    @SuppressWarnings("unchecked")
//    protected T asElementType(Object o);
//
//    /**
//     * Return an array of {@code T[]} with length {@code capacity}.
//     *
//     * @param capacity the length of the array to return
//     * @return the newly constructed array
//     */
//    @SuppressWarnings("unchecked")
//    protected T[][] createBuckets(int capacity);
//
//    /**
//     * Return an array of {@code T} with length {@code capacity}.
//     *
//     * @param capacity the length of the array to return
//     * @return the newly constructed array
//     */
//    @SuppressWarnings("unchecked")
//    protected T[] createBucket(int capacity);
//
//    protected class SetIterator implements Iterator<T> {
//        final T[] data;
//        int nextIndex = 0;
//        boolean removed = true;
//
//        SetIterator(T[] data) {
//            this.data = data;
//        }
//
//        ANTLR_OVERRIDE
//        boolean hasNext() {
//            return nextIndex < data.length;
//        }
//
//        ANTLR_OVERRIDE
//        T next() {
//            if (!hasNext()) {
//                throw new NoSuchElementException();
//            }
//
//            removed = false;
//            return data[nextIndex++];
//        }
//
//        ANTLR_OVERRIDE
//        void remove() {
//            if (removed) {
//                throw new IllegalStateException();
//            }
//
//            Array2DHashSet.this.remove(data[nextIndex - 1]);
//            removed = true;
//        }
//    };

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




} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef ARRAY_2D_HASH_SET_H */
