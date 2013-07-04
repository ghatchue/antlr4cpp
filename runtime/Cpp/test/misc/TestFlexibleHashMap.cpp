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
#include <misc/FlexibleHashMap.h>
#include <misc/Utils.h>
#include <string>
#include "IntKey.h"
#include "StringKey.h"

using namespace antlr4::misc;

class TestFlexibleHashMap : public BaseTest
{
};


TEST_F(TestFlexibleHashMap, testSize)
{
    FlexibleHashMap<antlr_int32_t, std::string> map;
    EXPECT_EQ(0u, map.size());
}

TEST_F(TestFlexibleHashMap, testToTableString)
{
    FlexibleHashMap<StringKey, antlr_int32_t> map;
    map.put("hi", 1);
    map.put("mom", 2);
    map.put("foo", 3);
    map.put("ach", 4);
    map.put("cbba", 5);
    map.put("d", 6);
    map.put("edf", 7);
    map.put("mom", 8);
    map.put("hi", 9);
    EXPECT_EQ(
        "[d:6 edf:7]\n"
        "null\n"
        "null\n"
        "null\n"
        "[cbba:5]\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n"
        "null\n"
        "[ach:4]\n"
        "[mom:8]\n"
        "[hi:9]\n"
        "[foo:3]\n"
        "null\n",
        map.toTableString());
}
