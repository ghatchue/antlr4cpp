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

#include <antlr/misc/Mutex.h>
#include <stdexcept>

namespace antlr4 {
namespace misc {

#if defined(HAVE_PTHREAD)

// Acquires this mutex.
void MutexBase::lock()
{
    antlr_int32_t status = pthread_mutex_lock(&mutex_);
    if (status != 0) {
        throw std::runtime_error("pthread_mutex_lock failed");
    }
    owner_ = pthread_self();
}

// Releases this mutex.
void MutexBase::unlock()
{
    // We don't protect writing to owner_ here, as it's the caller's
    // responsibility to ensure that the current thread holds the
    // mutex when this is called.
    owner_ = 0;
    antlr_int32_t status = pthread_mutex_unlock(&mutex_);
    if (status != 0) {
        throw std::runtime_error("pthread_mutex_unlock failed");
    }
}

// Indicates if the current thread holds the mutex
bool MutexBase::isHeld() const
{
    return owner_ == pthread_self();
}

Mutex::Mutex()
{
    antlr_int32_t status = pthread_mutex_init(&mutex_, NULL);
    if (status != 0) {
        throw std::runtime_error("pthread_mutex_init failed");
    }
    owner_ = 0;
}

Mutex::~Mutex()
{
    antlr_int32_t status = pthread_mutex_destroy(&mutex_);
    if (status != 0) {
        throw std::runtime_error("pthread_mutex_destroy failed");
    }
}

#else /* HAVE_PTHREAD */

void MutexBase::lock()
{
}

void MutexBase::unlock()
{
}

bool MutexBase::isHeld() const
{
    return true;
}

Mutex::Mutex()
{
}

#endif /* HAVE_PTHREAD */


} /* namespace misc */
} /* namespace antlr4 */
