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

#ifndef MUTEX_H
#define MUTEX_H

#include <antlr/Definitions.h>
#if defined(HAVE_PTHREAD)
#   include <pthread.h>
#endif


namespace antlr4 {
namespace misc {

#if defined(HAVE_PTHREAD)

// MutexBase and Mutex implement mutex on pthreads-based platforms. They
// are used in conjunction with class MutexLock:
//
//   Mutex mutex;
//   ...
//   MutexLock lock(&mutex);  // Acquires the mutex and releases it at the end
//                            // of the current scope.
//
// MutexBase implements behavior for both statically and dynamically
// allocated mutexes.  Do not use MutexBase directly.  Instead, write
// the following to define a static mutex:
//
//   ANTLR_DEFINE_STATIC_MUTEX_(g_some_mutex);
//
// You can forward declare a static mutex like this:
//
//   ANTLR_DECLARE_STATIC_MUTEX_(g_some_mutex);
//
// To create a dynamic mutex, just define an object of type Mutex.
class ANTLR_API MutexBase
{
public:
    // Acquires this mutex.
    void lock();

    // Releases this mutex.
    void unlock();

    // Indicates if the current thread holds the mutex
    bool isHeld() const;

public:
    // A static mutex may be used before main() is entered.  It may even
    // be used before the dynamic initialization stage.  Therefore we
    // must be able to initialize a static mutex object at link time.
    // This means MutexBase has to be a POD and its member variables
    // have to be public.
    pthread_mutex_t mutex_;  // The underlying pthread mutex.
    pthread_t owner_;  // The thread holding the mutex; 0 means no one holds it.
};

// Forward-declares a static mutex.
# define ANTLR_DECLARE_STATIC_MUTEX_(mutex) \
    extern ::antlr::misc::MutexBase mutex

// Defines and statically (i.e. at link time) initializes a static mutex.
# define ANTLR_DEFINE_STATIC_MUTEX_(mutex) \
    ::antlr::misc::MutexBase mutex = { PTHREAD_MUTEX_INITIALIZER, 0 }

// The Mutex class can only be used for mutexes created at runtime. It
// shares its API with MutexBase otherwise.
class ANTLR_API Mutex : public MutexBase
{
public:
    Mutex();
    ~Mutex();
private:
    Mutex(const Mutex&);
    void operator=(const Mutex&);
};

#else /* HAVE_PTHREAD */

class ANTLR_API MutexBase
{
public:
    void lock();
    void unlock();
    bool isHeld() const;
};

class ANTLR_API Mutex
{
public:
    Mutex();
private:
    Mutex(const Mutex&);
    void operator=(const Mutex&);
};

// Forward-declares a static mutex.
# define ANTLR_DECLARE_STATIC_MUTEX_(mutex) \
    extern ::antlr::misc::Mutex mutex

// Defines and statically (i.e. at link time) initializes a static mutex.
# define ANTLR_DEFINE_STATIC_MUTEX_(mutex) \
    ::antlr::misc::Mutex mutex

#endif /* HAVE_PTHREAD */

} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef MUTEX_H */
