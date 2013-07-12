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
#include <misc/IntegerList.h>
#include <misc/Utils.h>
#include <stdexcept>

using namespace antlr4::misc;

class TestIntegerList : public BaseTest
{
};

TEST_F(TestIntegerList, testAdd)
{
    IntegerList list;
    list.add(-14);
    list.add(4);
    list.add(-3);
    list.add(16);
    EXPECT_EQ("[-14, 4, -3, 16]", list.toString());
}

TEST_F(TestIntegerList, testAddAll)
{
    antlr_int32_t ints[] = { -14, 4, -3, 16 };
    IntegerList list;
    list.addAll(ints, sizeof(ints)/sizeof(ints[0]));
    EXPECT_EQ("[-14, 4, -3, 16]", list.toString());
    
    IntegerList list2;
    EXPECT_EQ("[]", list2.toString());
    list2.addAll(list);
    EXPECT_EQ("[-14, 4, -3, 16]", list.toString());
}

TEST_F(TestIntegerList, testGet)
{
    IntegerList list;
    list.add(-14);
    list.add(4);
    EXPECT_EQ(-14, list.get(0));
    EXPECT_EQ(4, list.get(1));
}

TEST_F(TestIntegerList, testIndexOutOfRange)
{
    IntegerList list;
    list.add(5);
    EXPECT_THROW(list.get(1), std::out_of_range);
    EXPECT_THROW(list.set(1, 10), std::out_of_range);
    EXPECT_THROW(list.removeAt(1), std::out_of_range);
    EXPECT_THROW(list.removeRange(0, 2), std::out_of_range);    
}

TEST_F(TestIntegerList, testContains)
{
    IntegerList list;
    EXPECT_FALSE(list.contains(5));
    list.add(6);
    EXPECT_FALSE(list.contains(5));
    list.add(5);
    EXPECT_TRUE(list.contains(5));
}

TEST_F(TestIntegerList, testSet)
{
    IntegerList list;
    list.add(-14);
    list.add(4);
    list.add(40);
    list.set(0, -5);
    list.set(2, 100);
    EXPECT_EQ("[-5, 4, 100]", list.toString());
}

TEST_F(TestIntegerList, testRemoveAt)
{
    IntegerList list;
    list.add(-14);
    list.add(4);
    list.add(-3);
    list.add(16);
    list.removeAt(2);
    EXPECT_EQ("[-14, 4, 16]", list.toString());
}

TEST_F(TestIntegerList, testRemoveRangeInvalidArgument)
{
    IntegerList list;
    list.add(4);
    list.add(5);
    EXPECT_THROW(list.removeRange(1, 0), std::invalid_argument);    
}

TEST_F(TestIntegerList, testRemoveRange)
{
    IntegerList list;
    list.add(-14);
    list.add(4);
    list.add(-3);
    list.add(16);
    list.removeRange(0, 2);
    EXPECT_EQ("[16]", list.toString());
}

TEST_F(TestIntegerList, testRemoveRangeSingleItem)
{
    IntegerList list;
    list.add(4);
    list.removeRange(0, 0);
    EXPECT_EQ("[]", list.toString());
}

TEST_F(TestIntegerList, testEmpty)
{
    IntegerList list;
    EXPECT_TRUE(list.isEmpty());
    list.add(4);
    EXPECT_FALSE(list.isEmpty());
}

TEST_F(TestIntegerList, testSize)
{
    IntegerList list;
    EXPECT_EQ(0u, list.size());
    list.add(4);
    list.add(4);
    list.add(4);
    EXPECT_EQ(3u, list.size());
}

TEST_F(TestIntegerList, testCapacity)
{
    IntegerList list(6);
    EXPECT_GE(6u, list.capacity());
    list.add(4);
    list.add(4);
    list.add(4);
    list.trimToSize();
    EXPECT_EQ(3u, list.capacity());
}

TEST_F(TestIntegerList, testClear)
{
    IntegerList list;
    list.add(4);
    list.add(4);
    list.add(4);
    list.clear();
    EXPECT_EQ("[]", list.toString());
}

TEST_F(TestIntegerList, testToArray)
{
    IntegerList list;
    list.add(-14);
    list.add(4);
    list.add(-3);
    list.add(16);
    EXPECT_EQ("[-14, 4, -3, 16]", Utils::stringValueOf(*list.toArray()));
}

TEST_F(TestIntegerList, testSort)
{
    IntegerList list;
    list.add(16);
    list.add(-14);
    list.add(-3);
    list.add(4);
    list.sort();
    EXPECT_EQ("[-14, -3, 4, 16]", list.toString());
}

TEST_F(TestIntegerList, testBinarySearch)
{
    IntegerList list;
    list.add(5);
    list.add(7);
    list.add(10);
    EXPECT_EQ(-1, list.binarySearch(0, 2, 4));
    EXPECT_EQ( 0, list.binarySearch(0, 2, 5));
    EXPECT_EQ(-2, list.binarySearch(0, 2, 6));
    EXPECT_EQ( 1, list.binarySearch(0, 2, 7));
    EXPECT_EQ(-3, list.binarySearch(0, 2, 9));
    EXPECT_EQ( 2, list.binarySearch(0, 2, 10));
    EXPECT_EQ(-4, list.binarySearch(0, 2, 15));
}
