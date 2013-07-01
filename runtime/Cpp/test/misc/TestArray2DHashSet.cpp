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

TEST_F(TestArray2DHashSet, testContains)
{
    Array2DHashSet<StringKey> set;
    EXPECT_FALSE(set.contains("five"));
    set.add("five");
    EXPECT_TRUE(set.contains("five"));
}

TEST_F(TestArray2DHashSet, testAdd)
{
    Array2DHashSet<IntKey> set;
    EXPECT_TRUE(set.add(1));
    EXPECT_TRUE(set.add(3));
    EXPECT_FALSE(set.add(1));
    EXPECT_FALSE(set.add(3));
}

TEST_F(TestArray2DHashSet, testRemove)
{
    Array2DHashSet<IntKey> set;
    EXPECT_FALSE(set.remove(5));
    EXPECT_TRUE(set.add(1));
    EXPECT_TRUE(set.remove(1));
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
