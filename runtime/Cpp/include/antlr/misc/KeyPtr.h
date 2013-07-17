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

#ifndef KEY_PTR_H
#define KEY_PTR_H

#include <antlr/Definitions.h>
#include <antlr/misc/Key.h>
#include <antlr/misc/Traits.h>
#include <memory>
#include <stdexcept>

namespace antlr4 {
namespace misc {


template <typename T, bool isUsingHashKey = Traits::isBaseOf<Key<T>, T>::value>
class ANTLR_API KeyPtr;

template <typename T>
class ANTLR_API KeyPtr<T, true> : public Key< KeyPtr<T, true> >
{
public:

    ANTLR_OVERRIDE
    ~KeyPtr();
        
    ANTLR_OVERRIDE
    antlr_int32_t hashCode() const;

    KeyPtr();
    
    KeyPtr(T* ptr, bool hasOwnership = true);

    // Copy constructor
    KeyPtr(const KeyPtr<T, true>& other);
    
    // Equal operator
    KeyPtr<T, true>& operator=(const KeyPtr<T, true>& other);
    
    ANTLR_OVERRIDE
    KeyPtr<T, true>* clone() const;
    
    // Dereference object
    T& operator*() const;
    
    // Dereference object member
    T* operator->() const;

    
#if defined(HAVE_CXX11)
    
    // Move constructor
    KeyPtr(KeyPtr<T, true>&& other);
    
    // Move assignment operator
    KeyPtr<T, true>& operator=(KeyPtr<T, true>&& other);
    
#endif
    
    // Get pointer
    T* get() const;
    
    // Reset pointer
    void reset(T* ptr = NULL, bool hasOwnership = true);
    
    // Release pointer
    T* release();
    
protected:
    
    antlr_auto_ptr<T> ptr;
    
    // Indicates if the object should be deleted
    bool hasOwnership;
};

template <typename T>
KeyPtr<T, true>::~KeyPtr()
{
    if (hasOwnership) {
        ptr.reset();
    } else {
        ptr.release();
    }
}

template <typename T>
antlr_int32_t KeyPtr<T, true>::hashCode() const
{
    if (ptr.get() != NULL) {
        return ptr->hashCode();
    } else {
        throw std::logic_error("KeyPtr::hashCode null ptr");
    }
}

template <typename T>
KeyPtr<T, true>::KeyPtr()
    :   hasOwnership(true)
{
}

template <typename T>
KeyPtr<T, true>::KeyPtr(T* ptr, bool hasOwnership /* = true */)
    :   ptr(ptr),
        hasOwnership(hasOwnership)
{
}

// Copy constructor
template <typename T>
KeyPtr<T, true>::KeyPtr(const KeyPtr<T, true>& other)
    :   Key< KeyPtr<T, true> >(),
        hasOwnership(true)
{
    this->operator=(other);
}

// Equal operator
template <typename T>
KeyPtr<T, true>& KeyPtr<T, true>::operator=(const KeyPtr<T, true>& other)
{
    if (this != &other)
    {
        reset();
        hasOwnership = other.hasOwnership;
        if (other.hasOwnership && other.get() != NULL) {
            ptr.reset(other->clone());
        } else {
            ptr.reset(other.get());
        }
    }
    return *this;
}

template <typename T>
KeyPtr<T, true>* KeyPtr<T, true>::clone() const
{
    return new KeyPtr<T, true>(*this);
}


#if defined(HAVE_CXX11)

// Move constructor
template <typename T>
KeyPtr<T, true>::KeyPtr(KeyPtr<T, true>&& other)
    :   Key< KeyPtr<T, true> >()
{
    reset(other.release(), other.hasOwnership);
}

// Move assignment operator
template <typename T>
KeyPtr<T, true>& KeyPtr<T, true>::operator=(KeyPtr<T, true>&& other)
{
    if (this != &other)
    {
        reset(other.release(), other.hasOwnership);
    }
    return *this;
}

#endif

// Dereference object
template <typename T>
T& KeyPtr<T, true>::operator*() const
{
    return *ptr;
}

// Dereference object member
template <typename T>
T* KeyPtr<T, true>::operator->() const
{
    return ptr.get();
}

// Get pointer
template <typename T>
T* KeyPtr<T, true>::get() const
{
    return ptr.get();
}

// Reset pointer
template <typename T>
void KeyPtr<T, true>::reset(T* ptr /* = NULL */, bool hasOwnership /* = true */)
{
    if (this->hasOwnership) {
        this->ptr.reset(ptr);
    } else {
        this->ptr.release();
        this->ptr.reset(ptr);
    }   
    this->hasOwnership = hasOwnership;
}

// Release pointer
template <typename T>
T* KeyPtr<T, true>::release()
{
    hasOwnership = false;
    return ptr.release();
}


} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef KEY_PTR_H */
