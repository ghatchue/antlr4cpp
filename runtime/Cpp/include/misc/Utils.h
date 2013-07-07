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

#ifndef UTILS_H
#define UTILS_H

#include <Antlr4Definitions.h>
#include <misc/Traits.h>
#include <algorithm>
#include <list>
#include <sstream>
#include <string>
#include <vector>

namespace antlr4 {
namespace misc {

class ANTLR_API Utils
{
public:

    template <typename T>
    static std::string stringValueOfList(const T& list);

    template <typename T>
    static std::string stringValueOf(const std::list<T>& list);

    template <typename T>
    static std::string stringValueOf(const std::vector<T>& list);

    template <typename T>
    static std::string stringValueOfPtrArray(const T** array, antlr_uint32_t num);

    template <typename T>
    static std::string stringValueOf(const T& value);
    
    template <typename T, bool hasToString = Traits::hasToString<T>::value>
    struct String;
    
    template <typename T>
    struct String<T, true>
    {
        static std::string valueOf(const T& value);
    };
    
    template <typename T>
    struct String<T, false>
    {
        static std::string valueOf(const T& value);
    };
        
    template <typename Iter, typename T>
    static antlr_int32_t binarySearch(Iter begin, Iter end, const T& value);
};


template<typename T>
std::string Utils::stringValueOfList(const T& list)
{
    std::stringstream stream;
    stream << "[";
    for (typename T::const_iterator it = list.begin(); it != list.end();)
    {
        stream << Utils::stringValueOf(*it);
        if (++it != list.end())
            stream << ", ";
    }
    stream << "]";
    return stream.str();
}

template<typename T>
std::string Utils::stringValueOf(const std::list<T>& list)
{
    return stringValueOfList(list);
}

template<typename T>
std::string Utils::stringValueOf(const std::vector<T>& list)
{
    return stringValueOfList(list);
}

template <typename T>
std::string Utils::stringValueOfPtrArray(const T** array, antlr_uint32_t num)
{
    std::stringstream stream;
    if (array == NULL) return "null";
    else {
        stream << "[";
        for (antlr_uint32_t i = 0; i < num; i++) {
            stream << Utils::stringValueOf<T>(*array[i]);
            if (i+1 < num) stream << ", ";
        }
        stream << "]";
    }
    return stream.str();
}

template <typename T>
std::string Utils::stringValueOf(const T& value)
{
    return String<T>::valueOf(value);
}

template<typename T>
std::string Utils::String<T, true>::valueOf(const T& value)
{
    std::stringstream stream;
    stream << value.toString();
    return stream.str();
}

template<typename T>
std::string Utils::String<T, false>::valueOf(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}

template <typename Iter, typename T>
antlr_int32_t Utils::binarySearch(Iter begin, Iter end, const T& value)
{
    antlr_int32_t result;
    Iter it = std::upper_bound(begin, end, value);
    if (it == begin) {
        result = -1;
    } else {
        if (*(it-1) == value) {
            // value was found
            result = it-1 - begin;
        } else {
            // value was not found
            result = -(it - begin) - 1;
        }
    }
    return result;
}

} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef UTILS_H */
