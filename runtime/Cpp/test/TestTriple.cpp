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
#include <misc/Triple.h>
#include <string>

using namespace antlr4::misc;

class TestTriple : public BaseTest
{
};

TEST_F(TestTriple, testConstructorInt)
{
    Triple<antlr_int32_t, antlr_int32_t, antlr_int32_t> t(5, 15, 25);
    EXPECT_EQ(5, t.a);
    EXPECT_EQ(15, t.b);
    EXPECT_EQ(25, t.c);
}

TEST_F(TestTriple, testConstructorString)
{
    Triple<std::string, std::string, std::string> t("one", "two", "three");
    EXPECT_EQ("one", t.a);
    EXPECT_EQ("two", t.b);
    EXPECT_EQ("three", t.c);
}

TEST_F(TestTriple, testCopyConstructor)
{
    Triple<antlr_int32_t, antlr_int32_t, antlr_int32_t> t1(10, 30, 45);
    Triple<antlr_int32_t, antlr_int32_t, antlr_int32_t> t(t1);
    EXPECT_EQ(10, t.a);
    EXPECT_EQ(30, t.b);
    EXPECT_EQ(45, t.c);
}

TEST_F(TestTriple, testCopyConstructorDifferentTypes)
{
    Triple<antlr_int32_t, antlr_int32_t, antlr_int32_t> t1(10, 30, 45);
    Triple<antlr_uint32_t, antlr_uint32_t, antlr_uint32_t> t(t1);
    EXPECT_EQ(10u, t.a);
    EXPECT_EQ(30u, t.b);
    EXPECT_EQ(45u, t.c);
}

TEST_F(TestTriple, testEqualOperator)
{
    Triple<std::string, std::string, std::string> p1("one", "two", "three");
    Triple<std::string, std::string, std::string> p2("one", "two", "four");
    Triple<std::string, std::string, std::string> p3("one", "two", "three");
    EXPECT_TRUE(p1==p3);
    EXPECT_FALSE(p1==p2);
}

