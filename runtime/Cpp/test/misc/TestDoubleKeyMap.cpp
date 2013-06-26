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
#include <misc/DoubleKeyMap.h>
#include <string>

using namespace antlr4::misc;

class TestDoubleKeyMap : public BaseTest
{
};


TEST_F(TestDoubleKeyMap, testSize)
{
    DoubleKeyMap<antlr_int32_t, antlr_int32_t, std::string> map;
    map.put(0, 0, "zero");
    map.put(1, 2, "twelve");
    map.put(1, 5, "fifteen");
    EXPECT_EQ(3u, map.size());
}

TEST_F(TestDoubleKeyMap, testPut)
{
    DoubleKeyMap<antlr_int32_t, antlr_int32_t, std::string> map;
    const std::string* p1 = map.put(1, 1, "one");
    const std::string* p3 = map.put(3, 3, "three");
    EXPECT_EQ("one", *p1);
    EXPECT_EQ("three", *p3);
    EXPECT_EQ("one", *map.get(1, 1));
    EXPECT_EQ("three", *map.get(3, 3));
    map.put(2, 2, "two");
    EXPECT_EQ("two", *map.get(2, 2));
}

TEST_F(TestDoubleKeyMap, testGet)
{
    DoubleKeyMap<antlr_int32_t, antlr_int32_t, antlr_int32_t> map;
    EXPECT_EQ(NULL, map.get(1, 1));
    map.put(1, 1, 10);
    map.put(2, 2, 20);
    map.put(3, 3, 30);
    EXPECT_EQ(10, *map.get(1, 1));
    EXPECT_EQ(20, *map.get(2, 2));
    EXPECT_EQ(30, *map.get(3, 3));
}
