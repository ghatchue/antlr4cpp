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

#include <antlr/misc/Thread.h>
#include <stdexcept>

#if defined(HAVE_PTHREAD) || defined(_MSC_VER)

namespace antlr4 {
namespace misc {

RunnableThread::~RunnableThread()
{
}

void* ThreadFuncWithCLinkage(void* thread)
{
  static_cast<RunnableThread*>(thread)->run();
  return NULL;
}

ThreadBase::ThreadBase()
    :   finished_(false)
{
}

ThreadBase::~ThreadBase()
{
    join();
}

void ThreadBase::start()
{
    RunnableThread* const base = this;
    // The thread can be created only after all fields except thread_
    // have been initialized.
    antlr_int32_t status = pthread_create(&thread_, 0, &ThreadFuncWithCLinkage, base);
    if (status != 0) {
        throw std::runtime_error("pthread_create failed");
    }
}

void ThreadBase::join() {
    if (!finished_) {
        antlr_int32_t status = pthread_join(thread_, 0);
        finished_ = true;
        if (status != 0) {
            throw std::runtime_error("pthread_join failed");
        }
    }
}

Thread::Thread(Thread::UserThreadFunc func)
    :   func_(func)
{
}

void Thread::run()
{
    func_();
}


} /* namespace misc */
} /* namespace antlr4 */

#endif /* defined(HAVE_PTHREAD) || defined(_MSC_VER) */
