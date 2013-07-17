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

#include <antlr/misc/IntegerList.h>
#include <antlr/misc/Utils.h>
#include <stdexcept>
#include <algorithm>

namespace antlr4 {
namespace misc {

const antlr_uint32_t IntegerList::INITIAL_SIZE = 4;

IntegerList::IntegerList()
{
}

IntegerList::IntegerList(antlr_uint32_t capacity)
{
    _data.reserve(capacity);
}

IntegerList::IntegerList(ANTLR_NOTNULL const IntegerList& list)
    :   Key<IntegerList>(),
        _data(list._data)
{
}

IntegerList::IntegerList(ANTLR_NOTNULL const std::list<antlr_int32_t> list)
{
    _data.reserve(list.size());
    for (std::list<antlr_int32_t>::const_iterator it = list.begin(); it != list.end(); it++) {
        _data.push_back(*it);
    }
}

void IntegerList::add(antlr_int32_t value)
{
    _data.push_back(value);
}

void IntegerList::addAll(antlr_int32_t array[], antlr_uint32_t size)
{
    _data.reserve(_data.size() + size);
    for (antlr_uint32_t i = 0; i < size; i++) {
        _data.push_back(array[i]);
    }
}

void IntegerList::addAll(const IntegerList& list)
{
    antlr_uint32_t size = static_cast<antlr_uint32_t>(list._data.size());
    _data.reserve(_data.size() + size);
    for (antlr_uint32_t i = 0; i < size; i++) {
        _data.push_back(list._data[i]);
    }
}

void IntegerList::addAll(const std::list<antlr_int32_t>& list)
{
    antlr_uint32_t size = static_cast<antlr_uint32_t>(list.size());
    _data.reserve(_data.size() + size);
    for (std::list<antlr_int32_t>::const_iterator it = list.begin(); it != list.end(); it++) {
        _data.push_back(*it);
    }
}

antlr_int32_t IntegerList::get(antlr_uint32_t index) const
{
    if (index >= _data.size()) {
        throw std::out_of_range("IntegerList::get index out of range");
    }
    return _data[index];
}

bool IntegerList::contains(antlr_int32_t value) const
{
    return std::find(_data.begin(), _data.end(), value) != _data.end();
}

antlr_int32_t IntegerList::set(antlr_uint32_t index, antlr_int32_t value)
{
    if (index >= _data.size()) {
        throw std::out_of_range("IntegerList::set index out of range");
    }
    
    antlr_int32_t previous = _data[index];
    _data[index] = value;
    return previous;    
}

antlr_int32_t IntegerList::removeAt(antlr_uint32_t index)
{
    antlr_int32_t value = get(index);
    _data.erase(_data.begin() + index);
    return value;
}

void IntegerList::removeRange(antlr_uint32_t fromIndex, antlr_uint32_t toIndex)
{
    antlr_uint32_t size = static_cast<antlr_uint32_t>(_data.size());
    if (fromIndex > size || toIndex > size) {
        throw std::out_of_range("IntegerList::removeRange index out of range");
    }
    if (fromIndex > toIndex) {
        throw std::invalid_argument("IntegerList::removeRange fromIndex > toIndex");
    }
    _data.erase(_data.begin() + fromIndex, _data.begin() + toIndex + 1);
}

bool IntegerList::isEmpty() const
{
    return _data.empty();
}

antlr_uint32_t IntegerList::size() const
{
    return static_cast<antlr_uint32_t>(_data.size());
}

antlr_uint32_t IntegerList::capacity() const
{
    return static_cast<antlr_uint32_t>(_data.capacity());
}

void IntegerList::trimToSize()
{
#if defined(HAVE_CXX11)
    _data.shrink_to_fit();
#else
    std::vector<antlr_int32_t> tmp(_data.begin(), _data.end());
    _data.swap(tmp);
#endif
}

void IntegerList::clear()
{
    _data.clear();
}

antlr_auto_ptr< std::vector<antlr_int32_t> > IntegerList::toArray() const
{
    return antlr_auto_ptr< std::vector<antlr_int32_t> >(new std::vector<antlr_int32_t>(_data));
}

bool IntegerList::compareForSort(antlr_int32_t a, antlr_int32_t b)
{
    return a < b;
}

void IntegerList::sort()
{
    std::sort(_data.begin(), _data.end(), compareForSort);
}

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
bool IntegerList::operator==(const IntegerList& other) const
{
    return _data == other._data;
}

IntegerList* IntegerList::clone() const
{
    return new IntegerList(*this);
}

/**
 * Returns the hash code value for this list.
 * <p/>
 * This implementation uses exactly the code that is used to define the
 * list hash function in the documentation for the {@link List#hashCode}
 * method.
 *
 * @return the hash code value for this list
 */
antlr_int32_t IntegerList::hashCode() const
{
    antlr_int32_t hashCode = 1;
    antlr_uint32_t size = static_cast<antlr_uint32_t>(_data.size());
    for (antlr_uint32_t i = 0; i < size; i++) {
        hashCode = 31*hashCode + _data[i];
    }
    return hashCode;
}

/**
 * Returns a string representation of this list.
 */
std::string IntegerList::toString() const
{
    return Utils::stringValueOf(_data);
}

antlr_int32_t IntegerList::binarySearch(antlr_int32_t key) const
{
    return Utils::binarySearch(_data.begin(), _data.end(), key);
}

antlr_int32_t IntegerList::binarySearch(antlr_uint32_t fromIndex, antlr_uint32_t toIndex, antlr_int32_t key) const
{
    return Utils::binarySearch(_data.begin() + fromIndex, _data.begin() + toIndex + 1, key);
}

void IntegerList::ensureCapacity(antlr_uint32_t capacity)
{
    _data.reserve(capacity);
}

} /* namespace misc */
} /* namespace antlr4 */
