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
#include <misc/FlexibleHashMap.h>
#include <misc/Utils.h>
#include <algorithm>
#include <string>
#include "IntKey.h"
#include "StringKey.h"
#include "ZeroKey.h"

using namespace antlr4::misc;

class TestFlexibleHashMap : public BaseTest
{
};


TEST_F(TestFlexibleHashMap, testSize)
{
    FlexibleHashMap<IntKey, IntKey> map;
    EXPECT_EQ(0u, map.size());
    map.put(1, 1);
    map.put(-2, -2);
    map.put(3, 3);
    EXPECT_EQ(3u, map.size());
    map.remove(-2);
    EXPECT_EQ(2u, map.size());
}

TEST_F(TestFlexibleHashMap, testIsEmpty)
{
    FlexibleHashMap<IntKey, IntKey> map;
    EXPECT_TRUE(map.isEmpty());
    map.put(1, 1);
    map.put(-2, -2);
    EXPECT_FALSE(map.isEmpty());
    map.clear();
    EXPECT_TRUE(map.isEmpty());
}

TEST_F(TestFlexibleHashMap, testContainsKey)
{
    FlexibleHashMap<StringKey, IntKey> map;
    EXPECT_FALSE(map.containsKey("five"));
    map.put("five", 5);
    EXPECT_TRUE(map.containsKey("five"));
}

TEST_F(TestFlexibleHashMap, testContainsValue)
{
    FlexibleHashMap<StringKey, IntKey> map;
    EXPECT_THROW(map.containsValue(5), std::logic_error);
}

TEST_F(TestFlexibleHashMap, testGet)
{
    FlexibleHashMap<IntKey, antlr_int32_t> map;
    EXPECT_EQ(NULL, map.get(1));
    map.put(1, 10);
    map.put(2, 20);
    map.put(3, 30);
    EXPECT_EQ(10, *map.get(1));
    EXPECT_EQ(20, *map.get(2));
    EXPECT_EQ(30, *map.get(3));
}

TEST_F(TestFlexibleHashMap, testPut)
{
    FlexibleHashMap<IntKey, std::string> map;
    const std::string* p1 = map.put(1, "one");
    const std::string* p3 = map.put(3, "three");
    EXPECT_EQ("one", *p1);
    EXPECT_EQ("three", *p3);
    EXPECT_EQ("one", *map.get(1));
    EXPECT_EQ("three", *map.get(3));
    map.put(1, "two");
    EXPECT_EQ("two", *map.get(1));
}

TEST_F(TestFlexibleHashMap, testRemove)
{
    FlexibleHashMap<IntKey, std::string> map;
    map.remove(5);
    map.put(1, "one");
    EXPECT_EQ("one", *map.get(1));
    map.remove(1);
    EXPECT_EQ(NULL, map.get(1));
}

TEST_F(TestFlexibleHashMap, testClear)
{
    FlexibleHashMap<IntKey, std::string> map;
    map.put(1, "one");
    map.put(2, "two");
    map.clear();
    EXPECT_EQ("{}", map.toString());
}

TEST_F(TestFlexibleHashMap, testToString)
{
    FlexibleHashMap<IntKey, std::string> map;
    EXPECT_EQ("{}", map.toString());
    map.put(1, "one");
    map.put(2, "two");
    EXPECT_EQ("{1:one, 2:two}", map.toString());
}

TEST_F(TestFlexibleHashMap, testConstantKeyHash)
{
    FlexibleHashMap<ZeroKey, antlr_int32_t> map;
    map.put(0, 10);
    map.put(1, 20);
    map.put(2, 30);
    map.put(2, 40);
    EXPECT_EQ(1u, map.size());
    EXPECT_EQ(40, *map.get(2));
}

TEST_F(TestFlexibleHashMap, testValues)
{
    FlexibleHashMap<antlr_int32_t, antlr_int32_t> map;
    for (antlr_int32_t i = -3; i < 4; i++)
        map.put(i, i);
    std::vector<const antlr_int32_t*> v = map.values();
    std::vector<antlr_int32_t> v2;
    for (std::vector<const antlr_int32_t*>::const_iterator it = v.begin(); it != v.end(); it++)
        v2.push_back(**it);
    std::sort(v2.begin(), v2.end());
    EXPECT_EQ("[-3, -2, -1, 0, 1, 2, 3]", Utils::stringValueOf(v2));
}

TEST_F(TestFlexibleHashMap, testToTableString)
{
    FlexibleHashMap<StringKey, antlr_int32_t> map;
    map.put("hi", 1);
    map.put("mom", 2);
    map.put("foo", 3);
    map.put("ach", 4);
    map.put("cbba", 5);
    map.put("d", 6);
    map.put("edf", 7);
    map.put("mom", 8);
    map.put("hi", 9);
    EXPECT_EQ(
        "[d:6 edf:7]\n"
        "null\n"
        "null\n"
        "null\n"
        "[cbba:5]\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n"
        "[ach:4]\n"
        "[mom:8]\n"
        "[hi:9]\n"
        "[foo:3]\n"
        "null\n",
        map.toTableString());
}
