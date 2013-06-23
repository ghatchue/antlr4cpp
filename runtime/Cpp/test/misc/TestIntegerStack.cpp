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

#include <BaseTest.h>
#include <misc/IntegerStack.h>
#include <stdexcept>

using namespace antlr4::misc;

class TestIntegerStack : public BaseTest
{
};

TEST_F(TestIntegerStack, testPush)
{
    IntegerStack stack;
    stack.push(2);
    stack.push(3);
    stack.push(4);
    EXPECT_EQ("[2, 3, 4]", stack.toString());
}

TEST_F(TestIntegerStack, testPushPop)
{
    IntegerStack stack;
    EXPECT_THROW(stack.pop(), std::out_of_range);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    EXPECT_EQ(4, stack.pop());
    EXPECT_EQ(3, stack.pop());
    EXPECT_EQ(2, stack.pop());
    EXPECT_THROW(stack.pop(), std::out_of_range);
}

TEST_F(TestIntegerStack, testPeek)
{
    IntegerStack stack;
    EXPECT_THROW(stack.peek(), std::out_of_range);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    EXPECT_EQ(4, stack.peek());
    EXPECT_EQ(4, stack.peek());
    EXPECT_EQ(4, stack.pop());
    EXPECT_EQ(3, stack.peek());
}
