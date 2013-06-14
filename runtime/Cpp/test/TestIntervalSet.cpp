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
#include <Lexer.h>
#include <misc/IntervalSet.h>
#include <misc/Utils.h>
#include <memory>

using namespace antlr4;
using namespace antlr4::misc;

class TestIntervalSet : public BaseTest
{
};

TEST_F(TestIntervalSet, testSingleElement)
{
    IntervalSet s = IntervalSet::of(99);
    std::string expecting = "99";
    EXPECT_EQ(expecting, s.toString());
}

TEST_F(TestIntervalSet, testIsolatedElements)
{
    IntervalSet s = new IntervalSet();
    s.add(1);
    s.add('z');
    s.add(0xFFF0);
    std::string expecting = "{1, 122, 65520}";
    EXPECT_EQ(expecting, s.toString());
}

TEST_F(TestIntervalSet, testMixedRangesAndElements)
{
    IntervalSet s = new IntervalSet();
    s.add(1);
    s.add('a','z');
    s.add('0','9');
    std::string expecting = "{1, 48..57, 97..122}";
    EXPECT_EQ(expecting, s.toString());
}

TEST_F(TestIntervalSet, testSimpleAnd)
{
    IntervalSet s = IntervalSet::of(10,20);
    IntervalSet s2 = IntervalSet::of(13,15);
    std::string expecting = "{13..15}";
    antlr_auto_ptr<IntervalSet> s3(s.and_(&s2));
    std::string result = s3->toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testRangeAndIsolatedElement)
{
    IntervalSet s = IntervalSet::of('a','z');
    IntervalSet s2 = IntervalSet::of('d');
    std::string expecting = "100";
    antlr_auto_ptr<IntervalSet> s3(s.and_(&s2));
    std::string result = s3->toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testEmptyIntersection)
{
    IntervalSet s = IntervalSet::of('a','z');
    IntervalSet s2 = IntervalSet::of('0','9');
    std::string expecting = "{}";
    antlr_auto_ptr<IntervalSet> s3(s.and_(&s2));
    std::string result = s3->toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testEmptyIntersectionSingleElements)
{
    IntervalSet s = IntervalSet::of('a');
    IntervalSet s2 = IntervalSet::of('d');
    std::string expecting = "{}";
    antlr_auto_ptr<IntervalSet> s3(s.and_(&s2));
    std::string result = s3->toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testNotSingleElement)
{
    IntervalSet vocabulary = IntervalSet::of(1,1000);
    vocabulary.add(2000,3000);
    IntervalSet s = IntervalSet::of(50,50);
    std::string expecting = "{1..49, 51..1000, 2000..3000}";
    antlr_auto_ptr<IntervalSet> s2(s.complement(&vocabulary));
    std::string result = s2->toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testNotSet)
{
    IntervalSet vocabulary = IntervalSet::of(1,1000);
    IntervalSet s = IntervalSet::of(50,60);
    s.add(5);
    s.add(250,300);
    std::string expecting = "{1..4, 6..49, 61..249, 301..1000}";
    antlr_auto_ptr<IntervalSet> s2(s.complement(&vocabulary));
    std::string result = s2->toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testNotEqualSet)
{
    IntervalSet vocabulary = IntervalSet::of(1,1000);
    IntervalSet s = IntervalSet::of(1,1000);
    std::string expecting = "{}";
    antlr_auto_ptr<IntervalSet> s2(s.complement(&vocabulary));
    std::string result = s2->toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testNotSetEdgeElement)
{
    IntervalSet vocabulary = IntervalSet::of(1,2);
    IntervalSet s = IntervalSet::of(1);
    std::string expecting = "2";
    antlr_auto_ptr<IntervalSet> s2(s.complement(&vocabulary));
    std::string result = s2->toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testNotSetFragmentedVocabulary)
{
    IntervalSet vocabulary = IntervalSet::of(1,255);
    vocabulary.add(1000,2000);
    vocabulary.add(9999);
    IntervalSet s = IntervalSet::of(50,60);
    s.add(3);
    s.add(250,300);
    s.add(10000); // this is outside range of vocab and should be ignored
    std::string expecting = "{1..2, 4..49, 61..249, 1000..2000, 9999}";
    antlr_auto_ptr<IntervalSet> s2(s.complement(&vocabulary));
    std::string result = s2->toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testSubtractOfCompletelyContainedRange)
{
    IntervalSet s = IntervalSet::of(10,20);
    IntervalSet s2 = IntervalSet::of(12,15);
    std::string expecting = "{10..11, 16..20}";
    antlr_auto_ptr<IntervalSet> s3(s.subtract(&s2));
    std::string result = s3->toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testSubtractOfOverlappingRangeFromLeft)
{
    IntervalSet s = IntervalSet::of(10,20);
    IntervalSet s2 = IntervalSet::of(5,11);
    std::string expecting = "{12..20}";
    antlr_auto_ptr<IntervalSet> s4(s.subtract(&s2));
    std::string result = s4->toString();
    EXPECT_EQ(expecting, result);

    IntervalSet s3 = IntervalSet::of(5,10);
    expecting = "{11..20}";
    s4.reset(s.subtract(&s3));
    result = s4->toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testSubtractOfOverlappingRangeFromRight)
{
    IntervalSet s = IntervalSet::of(10,20);
    IntervalSet s2 = IntervalSet::of(15,25);
    std::string expecting = "{10..14}";
    antlr_auto_ptr<IntervalSet> s4(s.subtract(&s2));
    std::string result = s4->toString();
    EXPECT_EQ(expecting, result);

    IntervalSet s3 = IntervalSet::of(20,25);
    expecting = "{10..19}";
    s4.reset(s.subtract(&s3));
    result = s4->toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testSubtractOfCompletelyCoveredRange)
{
    IntervalSet s = IntervalSet::of(10,20);
    IntervalSet s2 = IntervalSet::of(1,25);
    std::string expecting = "{}";
    antlr_auto_ptr<IntervalSet> s3(s.subtract(&s2));
    std::string result = s3->toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testSubtractOfRangeSpanningMultipleRanges)
{
    IntervalSet s = IntervalSet::of(10,20);
    s.add(30,40);
    s.add(50,60); // s has 3 ranges now: 10..20, 30..40, 50..60
    IntervalSet s2 = IntervalSet::of(5,55); // covers one and touches 2nd range
    std::string expecting = "{56..60}";
    antlr_auto_ptr<IntervalSet> s4(s.subtract(&s2));
    std::string result = s4->toString();
    EXPECT_EQ(expecting, result);

    IntervalSet s3 = IntervalSet::of(15,55); // touches both
    expecting = "{10..14, 56..60}";
    s4.reset(s.subtract(&s3));
    result = s4->toString();
    EXPECT_EQ(expecting, result);
}

/** The following was broken:
    {0..113, 115..65534}-{0..115, 117..65534}=116..65534
    */
TEST_F(TestIntervalSet, testSubtractOfWackyRange)
{
    IntervalSet s = IntervalSet::of(0,113);
    s.add(115,200);
    IntervalSet s2 = IntervalSet::of(0,115);
    s2.add(117,200);
    std::string expecting = "116";
    antlr_auto_ptr<IntervalSet> s3(s.subtract(&s2));
    std::string result = s3->toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testSimpleEquals)
{
    IntervalSet s = IntervalSet::of(10,20);
    IntervalSet s2 = IntervalSet::of(10,20);
    EXPECT_EQ(s, s2);

    IntervalSet s3 = IntervalSet::of(15,55);
    EXPECT_FALSE(s == s3);
}

TEST_F(TestIntervalSet, testEquals)
{
    IntervalSet s = IntervalSet::of(10,20);
    s.add(2);
    s.add(499,501);
    IntervalSet s2 = IntervalSet::of(10,20);
    s2.add(2);
    s2.add(499,501);
    EXPECT_EQ(s, s2);

    IntervalSet s3 = IntervalSet::of(10,20);
    s3.add(2);
    EXPECT_FALSE(s == s3);
}

TEST_F(TestIntervalSet, testSingleElementMinusDisjointSet)
{
    IntervalSet s = IntervalSet::of(15,15);
    IntervalSet s2 = IntervalSet::of(1,5);
    s2.add(10,20);
    std::string expecting = "{}"; // 15 - {1..5, 10..20} = {}
    antlr_auto_ptr<IntervalSet> s3(s.subtract(&s2));
    std::string result = s3->toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testMembership)
{
    IntervalSet s = IntervalSet::of(15,15);
    s.add(50,60);
    EXPECT_TRUE(!s.contains(0));
    EXPECT_TRUE(!s.contains(20));
    EXPECT_TRUE(!s.contains(100));
    EXPECT_TRUE(s.contains(15));
    EXPECT_TRUE(s.contains(55));
    EXPECT_TRUE(s.contains(50));
    EXPECT_TRUE(s.contains(60));
}

// {2,15,18} & 10..20
TEST_F(TestIntervalSet, testIntersectionWithTwoContainedElements)
{
    IntervalSet s = IntervalSet::of(10,20);
    IntervalSet s2 = IntervalSet::of(2,2);
    s2.add(15);
    s2.add(18);
    std::string expecting = "{15, 18}";
    antlr_auto_ptr<IntervalSet> s3(s.and_(&s2));
    std::string result = s3->toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testIntersectionWithTwoContainedElementsReversed)
{
    IntervalSet s = IntervalSet::of(10,20);
    IntervalSet s2 = IntervalSet::of(2,2);
    s2.add(15);
    s2.add(18);
    std::string expecting = "{15, 18}";
    antlr_auto_ptr<IntervalSet> s3(s2.and_(&s));
    std::string result = s3->toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testComplement)
{
    IntervalSet s = IntervalSet::of(100,100);
    s.add(101,101);
    IntervalSet s2 = IntervalSet::of(100,102);
    std::string expecting = "102";
    antlr_auto_ptr<IntervalSet> s3(s.complement(&s2));
    std::string result = s3->toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testComplement2)
{
    IntervalSet s = IntervalSet::of(100,101);
    IntervalSet s2 = IntervalSet::of(100,102);
    std::string expecting = "102";
    antlr_auto_ptr<IntervalSet> s3(s.complement(&s2));
    std::string result = s3->toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testComplement3)
{
    IntervalSet s = IntervalSet::of(1,96);
    s.add(99, Lexer::MAX_CHAR_VALUE);
    std::string expecting = "{97..98}";
    antlr_auto_ptr<IntervalSet> s2(s.complement(1, Lexer::MAX_CHAR_VALUE));
    std::string result = s2->toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testMergeOfRangesAndSingleValues)
{
    // {0..41, 42, 43..65534}
    IntervalSet s = IntervalSet::of(0,41);
    s.add(42);
    s.add(43,65534);
    std::string expecting = "{0..65534}";
    std::string result = s.toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testMergeOfRangesAndSingleValuesReverse)
{
    IntervalSet s = IntervalSet::of(43,65534);
    s.add(42);
    s.add(0,41);
    std::string expecting = "{0..65534}";
    std::string result = s.toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testMergeWhereAdditionMergesTwoExistingIntervals)
{
    // 42, 10, {0..9, 11..41, 43..65534}
    IntervalSet s = IntervalSet::of(42);
    s.add(10);
    s.add(0,9);
    s.add(43,65534);
    s.add(11,41);
    std::string expecting = "{0..65534}";
    std::string result = s.toString();
    EXPECT_EQ(expecting, result);
}

/**
    * This case is responsible for antlr/antlr4#153.
    * https://github.com/antlr/antlr4/issues/153
    */
TEST_F(TestIntervalSet, testMergeWhereAdditionMergesThreeExistingIntervals)
{
    IntervalSet s = new IntervalSet();
    s.add(0);
    s.add(3);
    s.add(5);
    s.add(0, 7);
    std::string expecting = "{0..7}";
    std::string result = s.toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testMergeWithDoubleOverlap)
{
    IntervalSet s = IntervalSet::of(1,10);
    s.add(20,30);
    s.add(5,25); // overlaps two!
    std::string expecting = "{1..30}";
    std::string result = s.toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testSize)
{
    IntervalSet s = IntervalSet::of(20,30);
    s.add(50,55);
    s.add(5,19);
    std::string expecting = "32";
    std::string result = Utils::stringValueOf(s.size());
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testToList)
{
    IntervalSet s = IntervalSet::of(20,25);
    s.add(50,55);
    s.add(5,5);
    std::string expecting = "[5, 20, 21, 22, 23, 24, 25, 50, 51, 52, 53, 54, 55]";
    std::list<antlr_int32_t> list = s.toList();
    std::string result = Utils::stringValueOf(list);
    EXPECT_EQ(expecting, result);
}

/** The following was broken:
    {'\u0000'..'s', 'u'..'\uFFFE'} & {'\u0000'..'q', 's'..'\uFFFE'}=
    {'\u0000'..'q', 's'}!!!! broken...
    'q' is 113 ascii
    'u' is 117
*/
TEST_F(TestIntervalSet, testNotRIntersectionNotT)
{
    IntervalSet s = IntervalSet::of(0,'s');
    s.add('u',200);
    IntervalSet s2 = IntervalSet::of(0,'q');
    s2.add('s',200);
    std::string expecting = "{0..113, 115, 117..200}";
    antlr_auto_ptr<IntervalSet> s3(s.and_(&s2));
    std::string result = s3->toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testRmSingleElement)
{
    IntervalSet s = IntervalSet::of(1,10);
    s.add(-3,-3);
    s.remove(-3);
    std::string expecting = "{1..10}";
    std::string result = s.toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testRmLeftSide)
{
    IntervalSet s = IntervalSet::of(1,10);
    s.add(-3,-3);
    s.remove(1);
    std::string expecting = "{-3, 2..10}";
    std::string result = s.toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testRmRightSide)
{
    IntervalSet s = IntervalSet::of(1,10);
    s.add(-3,-3);
    s.remove(10);
    std::string expecting = "{-3, 1..9}";
    std::string result = s.toString();
    EXPECT_EQ(expecting, result);
}

TEST_F(TestIntervalSet, testRmMiddleRange)
{
    IntervalSet s = IntervalSet::of(1,10);
    s.add(-3,-3);
    s.remove(5);
    std::string expecting = "{-3, 1..4, 6..10}";
    std::string result = s.toString();
    EXPECT_EQ(expecting, result);
}
