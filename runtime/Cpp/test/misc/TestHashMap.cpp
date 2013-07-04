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
#include <misc/HashMap.h>
#include <misc/Utils.h>
#include <string>
#include "IntKey.h"
#include "StringKey.h"
#include "ZeroKey.h"

using namespace antlr4::misc;

class TestHashMap : public BaseTest
{
};

TEST_F(TestHashMap, testSize)
{
    HashMap<IntKey, IntKey> map;
    EXPECT_EQ(0u, map.size());
    map.put(1, 1);
    map.put(-2, -2);
    map.put(3, 3);
    EXPECT_EQ(3u, map.size());
    map.remove(-2);
    EXPECT_EQ(2u, map.size());
}

TEST_F(TestHashMap, testContains)
{
    HashMap<StringKey, IntKey> map;
    EXPECT_FALSE(map.contains("five"));
    map.put("five", 5);
    EXPECT_TRUE(map.contains("five"));
}

TEST_F(TestHashMap, testPut)
{
    HashMap<IntKey, std::string> map;
    const std::string* p1 = map.put(1, "one");
    const std::string* p3 = map.put(3, "three");
    EXPECT_EQ("one", *p1);
    EXPECT_EQ("three", *p3);
    EXPECT_EQ("one", *map.get(1));
    EXPECT_EQ("three", *map.get(3));
    map.put(1, "two");
    EXPECT_EQ("two", *map.get(1));
}

TEST_F(TestHashMap, testRemove)
{
    HashMap<IntKey, std::string> map;
    map.remove(5);
    map.put(1, "one");
    EXPECT_EQ("one", *map.get(1));
    map.remove(1);
    EXPECT_EQ(NULL, map.get(1));
}

TEST_F(TestHashMap, testGet)
{
    HashMap<IntKey, antlr_int32_t> map;
    EXPECT_EQ(NULL, map.get(1));
    map.put(1, 10);
    map.put(2, 20);
    map.put(3, 30);
    EXPECT_EQ(10, *map.get(1));
    EXPECT_EQ(20, *map.get(2));
    EXPECT_EQ(30, *map.get(3));
}

TEST_F(TestHashMap, testConstantKeyHash)
{
    HashMap<ZeroKey, antlr_int32_t> map;
    map.put(0, 10);
    map.put(1, 20);
    map.put(2, 30);
    map.put(2, 40);
    EXPECT_EQ(1u, map.size());
    EXPECT_EQ(40, *map.get(2));
}

TEST_F(TestHashMap, testPrimitiveIntHashMap)
{
    HashMap<antlr_int32_t, antlr_int32_t> map;
    map.put(0, 10);
    map.put(1, 20);
    map.put(1, 30);
    EXPECT_EQ(2u, map.size());
    EXPECT_EQ(10, *map.get(0));
    EXPECT_EQ(30, *map.get(1));
    map.put(-357, 123);
    EXPECT_EQ(3u, map.size());
    EXPECT_EQ(123, *map.get(-357));
}

TEST_F(TestHashMap, testCStringHashMap)
{
    HashMap<const char*, std::string> map;
    map.put("zero", "000");
    map.put("one", "111");
    map.put("one", "111111");
    map.put("onetwo", "111222");
    EXPECT_EQ(3u, map.size());
    EXPECT_EQ("000", *map.get("zero"));
    EXPECT_EQ("111111", *map.get("one"));
}

TEST_F(TestHashMap, testInsertionOperator)
{
    EXPECT_EQ("10", Utils::stringValueOf(IntKey(10)));
    EXPECT_EQ("ten", Utils::stringValueOf(StringKey("ten")));
    EXPECT_EQ("0", Utils::stringValueOf(ZeroKey()));
}
