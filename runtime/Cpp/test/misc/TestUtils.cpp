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
#include <antlr/misc/Utils.h>

using namespace antlr4::misc;

class TestUtils : public BaseTest
{
};

class MyClass
{
public:
    
    MyClass(const std::string& s) : s(s) { }
    std::string toString() const { return s + ":" + s; }
    bool operator==(const MyClass& o) const { return s == o.s; }
    
public:
    std::string s;
};

TEST_F(TestUtils, testStringValueOfInt)
{
    EXPECT_EQ("123", Utils::stringValueOf(123));
}

TEST_F(TestUtils, testStringValueOfFloat)
{
    EXPECT_EQ("123.35", Utils::stringValueOf(123.35f));
}

TEST_F(TestUtils, testStringValueOfString)
{
    EXPECT_EQ("hello world", Utils::stringValueOf("hello world"));
}

TEST_F(TestUtils, testStringValueOfIntList)
{
    std::list<antlr_int32_t> items;
    EXPECT_EQ("[]", Utils::stringValueOf(items));
    
    items.push_back(13);
    items.push_back(67);
    items.push_back(43);
    EXPECT_EQ("[13, 67, 43]", Utils::stringValueOf(items));
}

TEST_F(TestUtils, testStringValueOfIntVector)
{
    std::vector<antlr_int32_t> items;
    EXPECT_EQ("[]", Utils::stringValueOf(items));
    
    items.push_back(13);
    items.push_back(67);
    items.push_back(43);
    EXPECT_EQ("[13, 67, 43]", Utils::stringValueOf(items));
}

TEST_F(TestUtils, testBinarySearch)
{
    antlr_int32_t ints[] = { 5, 7, 10 };
    std::vector<antlr_int32_t> items(ints, ints + 3);
    EXPECT_EQ(-1, Utils::binarySearch(items.begin(), items.end(), 4));
    EXPECT_EQ( 0, Utils::binarySearch(items.begin(), items.end(), 5));
    EXPECT_EQ(-2, Utils::binarySearch(items.begin(), items.end(), 6));
    EXPECT_EQ( 1, Utils::binarySearch(items.begin(), items.end(), 7));
    EXPECT_EQ(-3, Utils::binarySearch(items.begin(), items.end(), 9));
    EXPECT_EQ( 2, Utils::binarySearch(items.begin(), items.end(), 10));
    EXPECT_EQ(-4, Utils::binarySearch(items.begin(), items.end(), 15));
}

TEST_F(TestUtils, testStringValueOfPtrArray)
{
    MyClass** a = new MyClass*[5];
    for (antlr_int32_t i = 0; i < 5; i++)
        a[i] = new MyClass(std::string("n") + Utils::stringValueOf(i));
    EXPECT_EQ("[n0:n0, n1:n1, n2:n2, n3:n3, n4:n4]", Utils::stringValueOfPtrArray(
            const_cast<const MyClass**>(a), 5u));
    for (antlr_int32_t i = 0; i < 5; i++)
        delete a[i];
    delete[] a;
}

TEST_F(TestUtils, testStringValueOfPtr)
{
    MyClass a("one");
    MyClass* p = NULL;
    EXPECT_EQ("one:one", Utils::String<MyClass>::valueOf(&a));
    EXPECT_EQ("null", Utils::String<MyClass>::valueOf(p));
}

TEST_F(TestUtils, testAutoPtrEquals)
{
    antlr_auto_ptr<MyClass> a(new MyClass("one"));
    antlr_auto_ptr<MyClass> b(new MyClass("one"));
    antlr_auto_ptr<MyClass> c(new MyClass("two"));
    EXPECT_TRUE(Utils::equals(a, a));
    EXPECT_TRUE(Utils::equals(a, b));
    EXPECT_FALSE(Utils::equals(a, c));
    a.reset();
    c.reset();
    EXPECT_TRUE(Utils::equals(a, c));
    EXPECT_FALSE(Utils::equals(a, b));
}
