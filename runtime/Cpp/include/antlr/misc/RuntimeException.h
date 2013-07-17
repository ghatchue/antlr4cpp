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

#ifndef RUNTIME_EXCEPTION_H
#define RUNTIME_EXCEPTION_H

#include <antlr/Antlr4Definitions.h>
#include <memory>
#include <stdexcept>
#include <string>

namespace antlr4 {
namespace misc {


class ANTLR_API RuntimeException : public std::runtime_error
{
public:
    
    ANTLR_OVERRIDE
    ~RuntimeException() throw();

    RuntimeException();
            
    RuntimeException(const std::string& message, RuntimeException* cause = NULL);
    
    RuntimeException(const RuntimeException& other);

    RuntimeException(RuntimeException* cause);

    const RuntimeException* getCause() const;
    
    RuntimeException* releaseCause();
    
    void resetCause(RuntimeException* cause = NULL);
    
protected:
    
    virtual RuntimeException* clone() const = 0;
    
private:
    
    antlr_auto_ptr<RuntimeException> cause;
};

} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef RUNTIME_EXCEPTION_H */
