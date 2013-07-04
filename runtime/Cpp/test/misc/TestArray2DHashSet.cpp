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
#include <misc/Array2DHashSet.h>
#include <misc/Utils.h>
#include <algorithm>
#include "HashRangeKey.h"
#include "IntKey.h"
#include "StringKey.h"
#include "ZeroKey.h"

using namespace antlr4::misc;

class TestArray2DHashSet : public BaseTest
{
};


TEST_F(TestArray2DHashSet, testSize)
{
    Array2DHashSet<antlr_int32_t> set;
    EXPECT_EQ(0u, set.size());
    set.add(-3);
    set.add(1);
    set.add(2);
    set.add(5);
    EXPECT_EQ(4u, set.size());
    set.remove(1);
    set.remove(5);
    EXPECT_EQ(2u, set.size());
}

TEST_F(TestArray2DHashSet, testIsEmpty)
{
    Array2DHashSet<antlr_int32_t> set;
    EXPECT_TRUE(set.isEmpty());
    set.add(-3);
    set.add(1);
    EXPECT_FALSE(set.isEmpty());
    set.clear();
    EXPECT_TRUE(set.isEmpty());
}

TEST_F(TestArray2DHashSet, testContains)
{
    Array2DHashSet<StringKey> set;
    EXPECT_FALSE(set.contains("five"));
    set.add("five");
    EXPECT_TRUE(set.contains("five"));
}

TEST_F(TestArray2DHashSet, testContainsFast)
{
    Array2DHashSet<StringKey> set;
    StringKey v("five");
    EXPECT_FALSE(set.containsFast(&v));
    set.add(v);
    EXPECT_TRUE(set.containsFast(&v));
    EXPECT_FALSE(set.containsFast(NULL));
}


TEST_F(TestArray2DHashSet, testAdd)
{
    Array2DHashSet<IntKey> set;
    EXPECT_TRUE(set.add(1));
    EXPECT_TRUE(set.add(3));
    EXPECT_FALSE(set.add(1));
    EXPECT_FALSE(set.add(3));
    EXPECT_EQ("{1, 3}", set.toString());
}

TEST_F(TestArray2DHashSet, testGetOrAdd)
{
    Array2DHashSet<IntKey> set;
    const IntKey* v1 = set.getOrAdd(1);
    const IntKey* v3 = set.getOrAdd(3);
    EXPECT_EQ(1, v1->value);
    EXPECT_EQ(3, v3->value);
    EXPECT_EQ(v1, set.getOrAdd(1));
    EXPECT_EQ(v3, set.getOrAdd(3));
    EXPECT_EQ(2u, set.size());
}

TEST_F(TestArray2DHashSet, testGet)
{
    Array2DHashSet<IntKey> set;
    EXPECT_EQ(NULL, set.get(1));
    EXPECT_EQ(NULL, set.get(-18));
    EXPECT_TRUE(set.add(1));
    EXPECT_TRUE(set.add(-18));
    EXPECT_EQ(1, set.get(1)->value);
    EXPECT_EQ(-18, set.get(-18)->value);
}

TEST_F(TestArray2DHashSet, testHashCode)
{
    Array2DHashSet<IntKey> a;
    Array2DHashSet<IntKey> b;
    for (antlr_int32_t i = 0; i < 200; i++) {
        a.add(i);
        b.add(200-i-1);
    }
    EXPECT_EQ(200u, a.size());
    EXPECT_EQ(200u, b.size());
    EXPECT_EQ(a.hashCode(), b.hashCode());
    a.remove(100);
    EXPECT_NE(a.hashCode(), b.hashCode());
    b.remove(100);
    EXPECT_EQ(a.hashCode(), b.hashCode());
}

TEST_F(TestArray2DHashSet, testEqualOperator)
{
    Array2DHashSet<IntKey> a;
    Array2DHashSet<IntKey> b;
    for (antlr_int32_t i = 0; i < 200; i++) {
        a.add(i);
        b.add(200-i-1);
    }
    EXPECT_EQ(200u, a.size());
    EXPECT_EQ(200u, b.size());
    EXPECT_TRUE(a == b);
    a.remove(100);
    EXPECT_FALSE(a == b);
    b.remove(100);
    EXPECT_TRUE(a == b);
    a.remove(99);
    b.remove(98);
    EXPECT_FALSE(a == b);
}

TEST_F(TestArray2DHashSet, testRemove)
{
    Array2DHashSet<IntKey> set;
    EXPECT_FALSE(set.remove(5));
    for (antlr_int32_t i = 0; i < 200; i++)
        EXPECT_TRUE(set.add(i));
    for (antlr_int32_t i = 0; i < 200; i++)
        EXPECT_TRUE(set.remove  (i));
    EXPECT_EQ(0u, set.size());
}

TEST_F(TestArray2DHashSet, testRemoveFast)
{
    Array2DHashSet<IntKey> set;
    IntKey v(1);
    EXPECT_FALSE(set.removeFast(NULL));
    EXPECT_FALSE(set.removeFast(&v));
    EXPECT_TRUE(set.add(v));
    EXPECT_TRUE(set.removeFast(&v));
    EXPECT_EQ(0u, set.size());
}

TEST_F(TestArray2DHashSet, testRemoveWithHashRangeKey)
{
    Array2DHashSet<HashRangeKey> set;
    for (antlr_int32_t i = 0; i < 20; i++)
        set.add(i);
    EXPECT_EQ(
        "[0 10 _ _ _ _ _ _]\n"
        "[1 11 _ _ _ _ _ _]\n"
        "[2 12 _ _ _ _ _ _]\n"
        "[3 13 _ _ _ _ _ _]\n"
        "[4 14 _ _ _ _ _ _]\n"
        "[5 15 _ _ _ _ _ _]\n"
        "[6 16 _ _ _ _ _ _]\n"
        "[7 17 _ _ _ _ _ _]\n"
        "[8 18 _ _ _ _ _ _]\n"
        "[9 19 _ _ _ _ _ _]\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n",
        set.toTableString());
}

TEST_F(TestArray2DHashSet, testConstantKeyHash)
{
    Array2DHashSet<ZeroKey> set;
    set.add(0);
    set.add(1);
    set.add(2);
    set.add(2);
    EXPECT_EQ(1u, set.size());
    EXPECT_TRUE(set.remove(100));
    EXPECT_EQ(0u, set.size());
}

TEST_F(TestArray2DHashSet, testPrimitiveIntHashSet)
{
    Array2DHashSet<antlr_int32_t> set;
    set.add(0);
    set.add(1);
    set.add(1);
    EXPECT_EQ(2u, set.size());
    EXPECT_TRUE(set.contains(0));
    EXPECT_TRUE(set.contains(1));
    set.add(-357);
    EXPECT_EQ(3u, set.size());
    EXPECT_TRUE(set.contains(-357));
    EXPECT_FALSE(set.contains(456));
}

TEST_F(TestArray2DHashSet, testCStringHashSet)
{
    Array2DHashSet<const char*> set;
    set.add("zero");
    set.add("one");
    set.add("one");
    set.add("onetwo");
    EXPECT_EQ(3u, set.size());
    EXPECT_TRUE(set.contains("zero"));
    EXPECT_TRUE(set.contains("one"));
    EXPECT_FALSE(set.contains("three"));
}

TEST_F(TestArray2DHashSet, testToArray)
{
    Array2DHashSet<antlr_int32_t> set;
    for (antlr_int32_t i = -3; i < 4; i++)
        set.add(i);
    std::vector<antlr_int32_t> v = set.toArray();
    std::sort(v.begin(), v.end());
    EXPECT_EQ("[-3, -2, -1, 0, 1, 2, 3]", Utils::stringValueOf(v));
}

TEST_F(TestArray2DHashSet, testToPtrArray)
{
    Array2DHashSet<antlr_int32_t> set;
    for (antlr_int32_t i = -3; i < 4; i++)
        set.add(i);
    std::vector<const antlr_int32_t*> v = set.toPtrArray();
    std::vector<antlr_int32_t> v2;
    for (std::vector<const antlr_int32_t*>::const_iterator it = v.begin(); it != v.end(); it++)
        v2.push_back(**it);
    std::sort(v2.begin(), v2.end());
    EXPECT_EQ("[-3, -2, -1, 0, 1, 2, 3]", Utils::stringValueOf(v2));
}

TEST_F(TestArray2DHashSet, testToCustomArray)
{
    Array2DHashSet<antlr_int32_t> set;
    for (antlr_int32_t i = -3; i < 4; i++)
        set.add(i);
    std::vector<double> v;
    set.toArray(v);
    std::sort(v.begin(), v.end());
    EXPECT_EQ("[-3, -2, -1, 0, 1, 2, 3]", Utils::stringValueOf(v));
}
