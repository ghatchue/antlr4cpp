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

#ifndef HASH_RANGE_KEY_H
#define	HASH_RANGE_KEY_H

#include <antlr/misc/Key.h>
#include <sstream>

using namespace antlr4::misc;

class HashRangeKey : public virtual Key<HashRangeKey>
{
public:
    
    HashRangeKey() : value(0), maxHash(10) { }
    HashRangeKey(const HashRangeKey& other) : Key<HashRangeKey>(), value(other.value), maxHash(other.maxHash) { }
    HashRangeKey(const antlr_int32_t& value) : value(value), maxHash(10) { }
    
    ANTLR_OVERRIDE
    antlr_int32_t hashCode() const { return value % maxHash; }
    
    ANTLR_OVERRIDE
    bool equals(const Key<HashRangeKey>* o) const
    {
        const HashRangeKey* other = dynamic_cast<const HashRangeKey*>(o);
        if (other == NULL) {
            return false;
        }
        return value == other->value;
    }
    
    ANTLR_OVERRIDE
    HashRangeKey* clone() const { return new HashRangeKey(*this); }

public:
    antlr_int32_t value;
    antlr_int32_t maxHash;
};

namespace std {
    static ostream& operator<< (ostream& os, const HashRangeKey& v)
    {
        os << v.value;
        return os;
    }
}


#endif /* ifndef HASH_RANGE_KEY_H */
