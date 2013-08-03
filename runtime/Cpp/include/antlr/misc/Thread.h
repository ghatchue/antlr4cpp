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

#ifndef THREAD_WITH_PARAM_H
#define THREAD_WITH_PARAM_H

#include <antlr/Definitions.h>
#if defined(HAVE_PTHREAD) || defined(_MSC_VER)

#if defined(HAVE_PTHREAD)
#   include <pthread.h>
#endif

namespace antlr4 {
namespace misc {

// As a C-function, ThreadFuncWithCLinkage cannot be templated itself.
// Consequently, it cannot select a correct instantiation of ThreadWithParam
// in order to call its Run(). Introducing RunnableThread as a
// non-templated base class for ThreadWithParam allows us to bypass this
// problem.
class ANTLR_API RunnableThread
{
public:
    virtual ~RunnableThread();
    virtual void run() = 0;
};

// pthread_create() accepts a pointer to a function type with the C linkage.
// According to the Standard (7.5/1), function types with different linkages
// are different even if they are otherwise identical.  Some compilers (for
// example, SunStudio) treat them as different types.  Since class methods
// cannot be defined with C-linkage we need to define a free C-function to
// pass into pthread_create().
extern "C" inline void* ThreadFuncWithCLinkage(void* thread);


class ANTLR_API ThreadBase : public RunnableThread
{
public:
    ThreadBase();
    ~ThreadBase();
  
    void start();
    void join();

private:
    // When non-NULL, used to block execution until the controller thread
    // notifies.
    bool finished_;  // true if we know that the thread function has finished.
#if defined(HAVE_PTHREAD)
    pthread_t thread_;  // The native thread object.
#endif
};

class ANTLR_API Thread : public ThreadBase
{
public:
    typedef void (*UserThreadFunc)();

    Thread(UserThreadFunc func);

    ANTLR_OVERRIDE
    void run();
    
private:
    Thread(const Thread&);
    void operator=(const Thread&);

private:
    const UserThreadFunc func_;  // User-supplied thread function.
};

template <typename T>
class ANTLR_API ThreadWithParam : public ThreadBase
{
public:
    typedef void (*UserThreadFunc)(T);

    ThreadWithParam(UserThreadFunc func, T param);

    ANTLR_OVERRIDE
    void run();
    
private:
    ThreadWithParam(const ThreadWithParam<T>&);
    void operator=(const ThreadWithParam<T>&);

private:
    const UserThreadFunc func_;  // User-supplied thread function.
    const T param_;  // User-supplied parameter to the thread function.
};

template<typename T>
ThreadWithParam<T>::ThreadWithParam(typename ThreadWithParam<T>::UserThreadFunc func, T param)
    :   func_(func),
        param_(param)
{
}

template<typename T>
void ThreadWithParam<T>::run()
{
    func_(param_);
}

} /* namespace misc */
} /* namespace antlr4 */

#endif /* defined(HAVE_PTHREAD) || defined(_MSC_VER) */
#endif /* ifndef THREAD_WITH_PARAM_H */
