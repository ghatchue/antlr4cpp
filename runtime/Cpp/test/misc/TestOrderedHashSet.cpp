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
#include <misc/OrderedHashSet.h>
#include <misc/Utils.h>
#include <memory>
#include <stdexcept>
#include <string>

using namespace antlr4::misc;

class TestOrderedHashSet : public BaseTest
{
};

TEST_F(TestOrderedHashSet, testSize)
{
    OrderedHashSet<antlr_int32_t> set;
    set.add(-5);
    set.add(10);
    set.add(15);
    set.add(15);
    EXPECT_EQ(3u, set.size());
}

TEST_F(TestOrderedHashSet, testGet)
{
    OrderedHashSet<antlr_int32_t> set;
    set.add(-5);
    set.add(10);
    set.add(15);
    set.add(15);
    EXPECT_EQ(-5, *set.get(0));
    EXPECT_EQ(10, *set.get(1));
    EXPECT_EQ(15, *set.get(2));
}

TEST_F(TestOrderedHashSet, testOutOfRangeException)
{
    OrderedHashSet<antlr_int32_t> set;
    EXPECT_THROW(set.get(0), std::out_of_range);
    EXPECT_THROW(set.set(0, 1), std::out_of_range);
    EXPECT_THROW(set.remove(0u), std::out_of_range);
}

TEST_F(TestOrderedHashSet, testRemoveByValueNotImplemented)
{
    OrderedHashSet<antlr_int32_t> set;
    EXPECT_THROW(set.remove(0), std::logic_error);
}

TEST_F(TestOrderedHashSet, testSet)
{
    OrderedHashSet<antlr_int32_t> set;
    set.add(-5);
    set.add(10);
    set.add(15);
    set.add(16);
    EXPECT_EQ(37, *set.set(1, 37));
    EXPECT_EQ(-54, *set.set(3, -54));
    EXPECT_EQ("[-5, 37, 15, -54]", set.toString());
}

TEST_F(TestOrderedHashSet, testRemoveByIndex)
{
    OrderedHashSet<antlr_int32_t> set;
    set.add(-5);
    set.add(10);
    set.add(15);
    set.add(16);
    EXPECT_TRUE(set.remove(0u));
    EXPECT_TRUE(set.remove(2u));
    EXPECT_EQ("[10, 15]", set.toString());
}

TEST_F(TestOrderedHashSet, testAdd)
{
    OrderedHashSet<const char*> set;
    EXPECT_TRUE(set.add("one"));
    EXPECT_FALSE(set.add("one"));
    EXPECT_TRUE(set.add("two"));
    EXPECT_TRUE(set.add("three"));
    EXPECT_EQ("[one, two, three]", set.toString());
}

TEST_F(TestOrderedHashSet, testClear)
{
    OrderedHashSet<antlr_int32_t> set;
    set.add(-5);
    set.add(10);
    set.add(15);
    set.add(16);
    set.clear();
    EXPECT_EQ(0u, set.size());
    EXPECT_EQ("[]", set.toString());
}

TEST_F(TestOrderedHashSet, testHashCode)
{
    OrderedHashSet<antlr_int32_t> a, b;
    a.add(-5); b.add(-5);
    a.add(10); b.add(10);
    a.add(15); b.add(15);
    a.add(16); b.add(16);
    EXPECT_EQ(a.hashCode(), b.hashCode());
}

TEST_F(TestOrderedHashSet, testEqualOperator)
{
    OrderedHashSet<antlr_int32_t> a, b;
    a.add(-5); b.add(-5);
    a.add(10); b.add(10);
    a.add(15); b.add(15);
    a.add(16); b.add(16);
    EXPECT_TRUE(a == b);
}

TEST_F(TestOrderedHashSet, testClone)
{
    OrderedHashSet<antlr_int32_t> a;
    antlr_auto_ptr<OrderedHashSet<antlr_int32_t> > b;
    a.add(-5);
    a.add(10);
    a.add(15);
    a.add(16);
    b.reset(a.clone());
    EXPECT_EQ(a.toString(), b->toString());
}

TEST_F(TestOrderedHashSet, testCopyConstructor)
{
    OrderedHashSet<antlr_int32_t> a;
    a.add(-5);
    a.add(10);
    a.add(15);
    a.add(16);
    OrderedHashSet<antlr_int32_t> b(a);
    EXPECT_EQ(a.toString(), b.toString());
}

TEST_F(TestOrderedHashSet, testConstIterator)
{
    OrderedHashSet<antlr_int32_t> set;
    antlr_int32_t exp[] = {-5, 10, 15, 16};
    set.add(-5);
    set.add(10);
    set.add(15);
    set.add(16);
    antlr_uint32_t i = 0;
    for (OrderedHashSet<antlr_int32_t>::const_iterator it = set.begin(); it != set.end(); it++, i++)
        EXPECT_EQ(exp[i], *it);
}

TEST_F(TestOrderedHashSet, testToArray)
{
    OrderedHashSet<antlr_int32_t> set;
    set.add(-5);
    set.add(10);
    set.add(15);
    set.add(16);
    EXPECT_EQ("[-5, 10, 15, 16]", Utils::stringValueOf(*set.toArray()));
}

TEST_F(TestOrderedHashSet, testToPtrArray)
{
    OrderedHashSet<antlr_int32_t> set;
    set.add(-5);
    set.add(10);
    set.add(15);
    set.add(16);
    antlr_auto_ptr< std::vector<const antlr_int32_t*> > v = set.toPtrArray();
    std::vector<antlr_int32_t> v2;
    for (std::vector<const antlr_int32_t*>::const_iterator it = v->begin(); it != v->end(); it++)
        v2.push_back(**it);
    EXPECT_EQ("[-5, 10, 15, 16]", Utils::stringValueOf(v2));
}
