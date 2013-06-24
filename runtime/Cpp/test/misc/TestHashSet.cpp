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
#include <misc/HashSet.h>
#include <misc/Key.h>
#include <misc/MurmurHash.h>
#include <string>

using namespace antlr4::misc;

class TestHashSet : public BaseTest
{
};

class IntKey : public virtual Key<IntKey>
{
public:
    
    IntKey(const IntKey& v) : Key<IntKey>(), value(v.value) { }
    IntKey(const antlr_int32_t& v) : value(v) { }
    
    ANTLR_OVERRIDE
    antlr_int32_t hashCode() const
    {
        return value;
    }
    
    ANTLR_OVERRIDE
    bool equals(const IntKey& other) const
    {
        return value == other.value;
    }

public:
    antlr_int32_t value;
};

class StringKey : public virtual Key<StringKey>
{
public:

    StringKey() { }
    StringKey(const StringKey& v) : Key<StringKey>(), value(v.value) { }
    StringKey(const std::string& v) : value(v) { }
    StringKey(const char* v) : value(v) { }

    ANTLR_OVERRIDE
    antlr_int32_t hashCode() const
    {
        antlr_int32_t hash = MurmurHash::initialize();
        antlr_uint32_t len = value.length();
        for (antlr_uint32_t i = 0; i < len; i++)
            hash = MurmurHash::update(hash, (antlr_int32_t)value[i]);
        hash = MurmurHash::finish(hash, len);
        return hash;
    }
    
    ANTLR_OVERRIDE
    bool equals(const StringKey& other) const
    {
        return value == other.value;
    }

public:
    std::string value;
};

class ZeroKey : public virtual Key<ZeroKey>
{
public:
    
    ZeroKey(const ZeroKey&) : Key<ZeroKey>() { }
    ZeroKey(const antlr_int32_t&) { }
    
    ANTLR_OVERRIDE
    antlr_int32_t hashCode() const
    {
        return 0;
    }
    
    ANTLR_OVERRIDE
    bool equals(const ZeroKey&) const
    {
        return true;
    }
};

TEST_F(TestHashSet, testSize)
{
    HashSet<IntKey> set;
    EXPECT_EQ(0u, set.size());
    set.add(1);
    set.add(-2);
    set.add(3);
    EXPECT_EQ(3u, set.size());
    set.remove(-2);
    EXPECT_EQ(2u, set.size());
}

TEST_F(TestHashSet, testContains)
{
    HashSet<StringKey> set;
    EXPECT_FALSE(set.contains("five"));
    set.add("five");
    EXPECT_TRUE(set.contains("five"));
}

TEST_F(TestHashSet, testAdd)
{
    HashSet<IntKey> set;
    EXPECT_TRUE(set.add(1));
    EXPECT_TRUE(set.add(3));
    EXPECT_FALSE(set.add(1));
    EXPECT_FALSE(set.add(3));
}

TEST_F(TestHashSet, testRemove)
{
    HashSet<IntKey> set;
    EXPECT_FALSE(set.remove(5));
    EXPECT_TRUE(set.add(1));
    EXPECT_TRUE(set.remove(1));
}

TEST_F(TestHashSet, testConstantKeyHash)
{
    HashSet<ZeroKey> set;
    set.add(0);
    set.add(1);
    set.add(2);
    set.add(2);
    EXPECT_EQ(1u, set.size());
    EXPECT_TRUE(set.remove(100));
    EXPECT_EQ(0u, set.size());
}

TEST_F(TestHashSet, testPrimitiveIntHashSet)
{
    HashSet<antlr_int32_t> set;
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

TEST_F(TestHashSet, testCStringHashSet)
{
    HashSet<const char*> set;
    set.add("zero");
    set.add("one");
    set.add("one");
    set.add("onetwo");
    EXPECT_EQ(3u, set.size());
    EXPECT_TRUE(set.contains("zero"));
    EXPECT_TRUE(set.contains("one"));
    EXPECT_FALSE(set.contains("three"));
}
