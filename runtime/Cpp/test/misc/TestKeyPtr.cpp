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
#include <misc/HashKeyHelper.h>
#include <misc/KeyPtr.h>
#include <gmock/gmock.h>

using namespace antlr4::misc;
using namespace testing;

class MyHashKey : public antlr4::misc::Key<MyHashKey>
{
public:
    
    MOCK_METHOD0(Die, void());
    ~MyHashKey() { Die(); }
    
    MOCK_CONST_METHOD0(hashCode, antlr_int32_t());
};

class TestKeyPtr : public BaseTest
{
};

TEST_F(TestKeyPtr, testDestructorCalled)
{
    KeyPtr<MyHashKey> p(new MyHashKey());
    EXPECT_CALL(*p, Die())
        .Times(1);
}

TEST_F(TestKeyPtr, testDestructorNotCalled)
{
    MyHashKey* key = new MyHashKey();
    KeyPtr<MyHashKey> p(key, false);
    EXPECT_CALL(*p, Die())
        .Times(0);
    ASSERT_TRUE(Mock::VerifyAndClear(key));
    delete key;
}

TEST_F(TestKeyPtr, testTransferConstructorWithOwnership)
{
    MyHashKey* key = new MyHashKey();
    EXPECT_CALL(*key, Die())
        .Times(0);
    KeyPtr<MyHashKey> p1(key);
    KeyPtr<MyHashKey> p2(p1);
    EXPECT_EQ(NULL, p1.get());
    EXPECT_EQ(key, p2.get());
    ASSERT_TRUE(Mock::VerifyAndClear(key));
}

TEST_F(TestKeyPtr, testTransferConstructorWithoutOwnership)
{
    MyHashKey* key = new MyHashKey();
    EXPECT_CALL(*key, Die())
        .Times(0);
    KeyPtr<MyHashKey> p1(key, false);
    KeyPtr<MyHashKey> p2(p1);
    EXPECT_EQ(NULL, p1.get());
    EXPECT_EQ(key, p2.get());
    ASSERT_TRUE(Mock::VerifyAndClear(key));
    delete key;
}

TEST_F(TestKeyPtr, testResetToPtrWithOwnership)
{
    MyHashKey* key = new MyHashKey();
    KeyPtr<MyHashKey> p(new MyHashKey());
    EXPECT_CALL(*p, Die());
    p.reset(key);
    EXPECT_CALL(*p, Die());
}

TEST_F(TestKeyPtr, testResetToNullWithOwnership)
{
    KeyPtr<MyHashKey> p(new MyHashKey());
    EXPECT_CALL(*p, Die());
    p.reset();
}

TEST_F(TestKeyPtr, testResetToPtrWithoutOwnership)
{
    MyHashKey* key = new MyHashKey();
    KeyPtr<MyHashKey> p(key, false);
    EXPECT_CALL(*p, Die())
        .Times(0);
    p.reset(new MyHashKey());
    EXPECT_CALL(*p, Die());
    p.reset();
    ASSERT_TRUE(Mock::VerifyAndClear(key));
    delete key;
}

TEST_F(TestKeyPtr, testResetToNullWithoutOwnership)
{
    MyHashKey* key = new MyHashKey();
    KeyPtr<MyHashKey> p(key, false);
    EXPECT_CALL(*p, Die())
        .Times(0);
    p.reset();
    ASSERT_TRUE(Mock::VerifyAndClear(key));
    delete key;
}

TEST_F(TestKeyPtr, testHashCode)
{
    KeyPtr<MyHashKey> p(new MyHashKey());
    EXPECT_CALL(*p, hashCode())
        .Times(2);
    HashKeyHelper< KeyPtr<MyHashKey>, true > hk;
    EXPECT_TRUE(hk.areEqual(p, p));
}

TEST_F(TestKeyPtr, testHashCodeThrowsExceptionForNullPtr)
{
    KeyPtr<MyHashKey> p(new MyHashKey());
    HashKeyHelper< KeyPtr<MyHashKey>, true > hk;
    KeyPtr<MyHashKey> p2;
    EXPECT_CALL(*p, hashCode())
        .WillOnce(Throw(std::logic_error("")));
    EXPECT_THROW(hk.areEqual(p, p2), std::logic_error);
}
