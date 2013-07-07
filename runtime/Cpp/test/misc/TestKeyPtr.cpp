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

class KeyMock : public NiceMock< antlr4::misc::Key<KeyMock> >
{
public:
    
    KeyMock() { }
    KeyMock(const KeyMock&) : NiceMock< antlr4::misc::Key<KeyMock> >() { }
    
    MOCK_METHOD0(dieMock, void());
    ~KeyMock() { dieMock(); }

    ANTLR_OVERRIDE
    KeyMock* clone() const { cloneMock(); return new KeyMock(*this); }
    MOCK_CONST_METHOD0(cloneMock, KeyMock*());
    
    
    MOCK_CONST_METHOD0(hashCode, antlr_int32_t());
};

class TestKeyPtr : public BaseTest
{
};

TEST_F(TestKeyPtr, testDestructorCalled)
{
    KeyPtr<KeyMock> p(new KeyMock());
    EXPECT_CALL(*p, dieMock())
        .Times(1);
}

TEST_F(TestKeyPtr, testDestructorNotCalled)
{
    KeyMock* key = new KeyMock();
    KeyPtr<KeyMock> p(key, false);
    EXPECT_CALL(*p, dieMock())
        .Times(0);
    p.reset();
    EXPECT_TRUE(Mock::VerifyAndClear(key));
    delete key;
}

TEST_F(TestKeyPtr, testCopyConstructorWithOwnership)
{
    KeyMock* key = new KeyMock();
    KeyPtr<KeyMock> p1(key);
    KeyPtr<KeyMock> p2(p1);
    EXPECT_NE((KeyMock*)NULL, p1.get());
    EXPECT_NE((KeyMock*)NULL, p2.get());
    EXPECT_NE(p1.get(), p2.get());
    EXPECT_CALL(*p1, dieMock());
    EXPECT_CALL(*p2, dieMock());
    p1.reset();
    p2.reset();
    EXPECT_TRUE(Mock::VerifyAndClear(p1.get()));
    EXPECT_TRUE(Mock::VerifyAndClear(p2.get()));
}

TEST_F(TestKeyPtr, testCopyConstructorWithoutOwnership)
{
    KeyMock* key = new KeyMock();
    KeyPtr<KeyMock> p1(key, false);
    KeyPtr<KeyMock> p2(p1);
    EXPECT_NE((KeyMock*)NULL, p1.get());
    EXPECT_NE((KeyMock*)NULL, p2.get());
    EXPECT_EQ(p1.get(), p2.get());
    EXPECT_CALL(*key, dieMock())
        .Times(0);
    p1.reset();
    p2.reset();
    EXPECT_TRUE(Mock::VerifyAndClear(key));
    delete key;
}

TEST_F(TestKeyPtr, testCopyConstructorNullPtr)
{
    KeyPtr<KeyMock> p1;
    KeyPtr<KeyMock> p2(p1);
    EXPECT_EQ((KeyMock*)NULL, p1.get());
    EXPECT_EQ((KeyMock*)NULL, p2.get());
}


TEST_F(TestKeyPtr, testResetToPtrWithOwnership)
{
    KeyMock* key = new KeyMock();
    KeyPtr<KeyMock> p(new KeyMock());
    EXPECT_CALL(*p, dieMock());
    p.reset(key);
    EXPECT_CALL(*p, dieMock());
}

TEST_F(TestKeyPtr, testResetToNullWithOwnership)
{
    KeyPtr<KeyMock> p(new KeyMock());
    EXPECT_CALL(*p, dieMock());
    p.reset();
}

TEST_F(TestKeyPtr, testResetToPtrWithoutOwnership)
{
    KeyMock* key = new KeyMock();
    KeyPtr<KeyMock> p(key, false);
    EXPECT_CALL(*p, dieMock())
        .Times(0);
    p.reset(new KeyMock());
    EXPECT_CALL(*p, dieMock());
    p.reset();
    EXPECT_TRUE(Mock::VerifyAndClear(key));
    delete key;
}

TEST_F(TestKeyPtr, testResetToNullWithoutOwnership)
{
    KeyMock* key = new KeyMock();
    KeyPtr<KeyMock> p(key, false);
    EXPECT_CALL(*p, dieMock())
        .Times(0);
    p.reset();
    EXPECT_TRUE(Mock::VerifyAndClear(key));
    delete key;
}

TEST_F(TestKeyPtr, testHashCode)
{
    KeyPtr<KeyMock> p(new KeyMock());
    EXPECT_CALL(*p, hashCode())
        .Times(2);
    HashKeyHelper< KeyPtr<KeyMock> > hk;
    EXPECT_TRUE(hk.areEqual(p, p));
}

TEST_F(TestKeyPtr, testHashCodeThrowsExceptionForNullPtr)
{
    KeyPtr<KeyMock> p(new KeyMock());
    HashKeyHelper< KeyPtr<KeyMock> > hk;
    KeyPtr<KeyMock> p2;
    EXPECT_CALL(*p, hashCode())
        .WillOnce(Throw(std::logic_error("")));
    EXPECT_THROW(hk.areEqual(p, p2), std::logic_error);
}

TEST_F(TestKeyPtr, testCloneNullPtr)
{
    KeyPtr<KeyMock> p;
    KeyPtr<KeyMock>* p2 = p.clone();
    EXPECT_EQ((KeyMock*)NULL, p2->get());
}

TEST_F(TestKeyPtr, testCloneKeyPtr)
{
    KeyPtr<KeyMock> p(new KeyMock());
    EXPECT_CALL(*p, cloneMock());
    delete p.clone();
}
