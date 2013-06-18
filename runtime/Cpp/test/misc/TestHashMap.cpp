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
#include <string>

using namespace antlr4::misc;

class TestHashMap : public BaseTest
{
};

TEST_F(TestHashMap, testSize)
{
    HashMap<antlr_int32_t, antlr_int32_t> map;
	EXPECT_EQ(0, map.size());
	map.put(1, 1);
	map.put(2, 2);
	map.put(3, 3);
	EXPECT_EQ(3, map.size());
	map.remove(2);
	EXPECT_EQ(2, map.size());
}

TEST_F(TestHashMap, testContains)
{
    HashMap<std::string, antlr_int32_t> map;
	EXPECT_FALSE(map.contains("five"));
	map.put("five", 5);
	EXPECT_TRUE(map.contains("five"));
}

TEST_F(TestHashMap, testPut)
{
    HashMap<antlr_int32_t, std::string> map;
	map.put(1, "one");
	map.put(3, "three");
	EXPECT_EQ("one", *map.get(1));
	EXPECT_EQ("three", *map.get(3));
	map.put(1, "two");
	EXPECT_EQ("two", *map.get(1));
}

TEST_F(TestHashMap, testRemove)
{
    HashMap<antlr_int32_t, std::string> map;
	map.remove(5);
	map.put(1, "one");
	EXPECT_EQ("one", *map.get(1));
	map.remove(1);
	EXPECT_EQ(NULL, map.get(1));
}

TEST_F(TestHashMap, testGet)
{
    HashMap<antlr_int32_t, antlr_int32_t> map;
	EXPECT_EQ(NULL, map.get(1));
	map.put(1, 10);
	map.put(2, 20);
	map.put(3, 30);
	EXPECT_EQ(10, *map.get(1));
	EXPECT_EQ(20, *map.get(2));
	EXPECT_EQ(30, *map.get(3));
}

TEST_F(TestHashMap, testCustomKeyType)
{
	struct MyKey
	{
		MyKey(const antlr_uint32_t& a) : a(a) { }
		operator size_t() const { return (size_t)a; }
		bool operator<(const MyKey& other) const { return (size_t)*this < (size_t)other; }
		antlr_uint32_t a;
	};
    HashMap<MyKey, antlr_uint32_t> map;
	EXPECT_EQ(NULL, map.get(1));
	map.put(1, 10);
	map.put(2, 20);
	map.put(3, 30);
	map.put(3, 40);
	EXPECT_EQ(10, *map.get(1));
	EXPECT_EQ(20, *map.get(2));
	EXPECT_EQ(40, *map.get(3));
}

//TEST_F(TestHashMap, testCustomKeyTypePointer)
//{
//	struct MyKey
//	{
//		MyKey(const antlr_uint32_t& a) { }
//		operator size_t() const { return 0; }	// always returns the same hash
//		bool operator<(const MyKey*& other) const { return true; }
//	};
//	MyKey keys[4] = {0, 1, 2, 3};
//    HashMap<MyKey*, antlr_uint32_t> map;
//	map.put(&keys[0], 10);
//	map.put(&keys[1], 20);
//	map.put(&keys[2], 30);
//	map.put(&keys[2], 40);
//	EXPECT_EQ(1, map.size());
//	EXPECT_EQ(40, *map.get(&keys[3]));
//}
