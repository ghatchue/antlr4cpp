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

#ifndef INTEGER_LIST_H
#define INTEGER_LIST_H

#include <antlr/Definitions.h>
#include <antlr/misc/Key.h>
#include <list>
#include <memory>
#include <string>
#include <vector>

namespace antlr4 {
namespace misc {


/**
 *
 * @author Sam Harwell
 */
class ANTLR_API IntegerList : public virtual Key<IntegerList>
{
public:

    IntegerList();

    IntegerList(antlr_uint32_t capacity);

    IntegerList(ANTLR_NOTNULL const IntegerList& list);

    IntegerList(ANTLR_NOTNULL const std::list<antlr_int32_t> list);

    void add(antlr_int32_t value);

    void addAll(antlr_int32_t array[], antlr_uint32_t size);

    void addAll(const IntegerList& list);

    void addAll(const std::list<antlr_int32_t>& list);

    antlr_int32_t get(antlr_uint32_t index) const;

    bool contains(antlr_int32_t value) const;

    antlr_int32_t set(antlr_uint32_t index, antlr_int32_t value);

    antlr_int32_t removeAt(antlr_uint32_t index);

    void removeRange(antlr_uint32_t fromIndex, antlr_uint32_t toIndex);

    bool isEmpty() const;

    antlr_uint32_t size() const;

    antlr_uint32_t capacity() const;
    
    void trimToSize();

    void clear();

    antlr_auto_ptr< std::vector<antlr_int32_t> > toArray() const;

    void sort();

    /**
     * Compares the specified object with this list for equality.  Returns
     * {@code true} if and only if the specified object is also an {@link IntegerList},
     * both lists have the same size, and all corresponding pairs of elements in
     * the two lists are equal.  In other words, two lists are defined to be
     * equal if they contain the same elements in the same order.
     * <p>
     * This implementation first checks if the specified object is this
     * list. If so, it returns {@code true}; if not, it checks if the
     * specified object is an {@link IntegerList}. If not, it returns {@code false};
     * if so, it checks the size of both lists. If the lists are not the same size,
     * it returns {@code false}; otherwise it iterates over both lists, comparing
     * corresponding pairs of elements.  If any comparison returns {@code false},
     * this method returns {@code false}.
     *
     * @param o the object to be compared for equality with this list
     * @return {@code true} if the specified object is equal to this list
     */
    ANTLR_OVERRIDE
    bool operator==(const IntegerList& other) const;
    
    ANTLR_OVERRIDE
    IntegerList* clone() const;

    /**
     * Returns the hash code value for this list.
     * <p/>
     * This implementation uses exactly the code that is used to define the
     * list hash function in the documentation for the {@link List#hashCode}
     * method.
     *
     * @return the hash code value for this list
     */
    ANTLR_OVERRIDE
    antlr_int32_t hashCode() const;

    /**
     * Returns a string representation of this list.
     */
    ANTLR_OVERRIDE
    std::string toString() const;

    antlr_int32_t binarySearch(antlr_int32_t key) const;

    antlr_int32_t binarySearch(antlr_uint32_t fromIndex, antlr_uint32_t toIndex, antlr_int32_t key) const;

    void ensureCapacity(antlr_uint32_t capacity);
    
    
private:
    
    static bool compareForSort (antlr_int32_t a, antlr_int32_t b);
    
    
private:
    
    static const antlr_uint32_t INITIAL_SIZE;
    
    ANTLR_NOTNULL
    std::vector<antlr_int32_t> _data;

};


} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef INTEGER_LIST_H */
