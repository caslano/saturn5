//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//
// This is a derivative work based on Zlib, copyright below:
/*
    Copyright (C) 1995-2013 Jean-loup Gailly and Mark Adler

    This software is provided 'as-is', without any express or implied
    warranty.  In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would be
       appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.

    Jean-loup Gailly        Mark Adler
    jloup@gzip.org          madler@alumni.caltech.edu

    The data format used by the zlib library is described by RFCs (Request for
    Comments) 1950 to 1952 in the files http://tools.ietf.org/html/rfc1950
    (zlib format), rfc1951 (deflate format) and rfc1952 (gzip format).
*/

#ifndef BOOST_BEAST_ZLIB_DETAIL_BITSTREAM_HPP
#define BOOST_BEAST_ZLIB_DETAIL_BITSTREAM_HPP

#include <boost/assert.hpp>
#include <cstdint>
#include <iterator>

namespace boost {
namespace beast {
namespace zlib {
namespace detail {

class bitstream
{
    using value_type = std::uint32_t;

    value_type v_ = 0;
    unsigned n_ = 0;

public:
    // returns the number of bits in the reservoir
    unsigned
    size() const
    {
        return n_;
    }

    // discard n bits
    void
    drop(std::size_t n)
    {
        BOOST_ASSERT(n <= n_);
        n_ -= static_cast<unsigned>(n);
        v_ >>= n;
    }

    // flush everything
    void
    flush()
    {
        n_ = 0;
        v_ = 0;
    }

    // flush to the next byte boundary
    void
    flush_byte()
    {
        drop(n_ % 8);
    }

    // ensure at least n bits
    template<class FwdIt>
    bool
    fill(std::size_t n, FwdIt& first, FwdIt const& last);

    // fill 8 bits, unchecked
    template<class FwdIt>
    void
    fill_8(FwdIt& it);

    // fill 16 bits, unchecked
    template<class FwdIt>
    void
    fill_16(FwdIt& it);

    // return n bits
    template<class Unsigned>
    void
    peek(Unsigned& value, std::size_t n);

    // return everything in the reservoir
    value_type
    peek_fast() const
    {
        return v_;
    }

    // return n bits, and consume
    template<class Unsigned>
    void
    read(Unsigned& value, std::size_t n);

    // rewind by the number of whole bytes stored (unchecked)
    template<class BidirIt>
    void
    rewind(BidirIt& it);
};

template<class FwdIt>
bool
bitstream::
fill(std::size_t n, FwdIt& first, FwdIt const& last)
{
    while(n_ < n)
    {
        if(first == last)
            return false;
        v_ += static_cast<value_type>(*first++) << n_;
        n_ += 8;
    }
    return true;
}

template<class FwdIt>
void
bitstream::
fill_8(FwdIt& it)
{
    v_ += static_cast<value_type>(*it++) << n_;
    n_ += 8;
}

template<class FwdIt>
void
bitstream::
fill_16(FwdIt& it)
{
    v_ += static_cast<value_type>(*it++) << n_;
    n_ += 8;
    v_ += static_cast<value_type>(*it++) << n_;
    n_ += 8;
}

template<class Unsigned>
void
bitstream::
peek(Unsigned& value, std::size_t n)
{
    BOOST_ASSERT(n <= sizeof(value)*8);
    BOOST_ASSERT(n <= n_);
    value = static_cast<Unsigned>(
        v_ & ((1ULL << n) - 1));
}

template<class Unsigned>
void
bitstream::
read(Unsigned& value, std::size_t n)
{
    BOOST_ASSERT(n < sizeof(v_)*8);
    BOOST_ASSERT(n <= n_);
    value = static_cast<Unsigned>(
        v_ & ((1ULL << n) - 1));
    v_ >>= n;
    n_ -= static_cast<unsigned>(n);
}

template<class BidirIt>
void
bitstream::
rewind(BidirIt& it)
{
    auto len = n_ >> 3;
    it = std::prev(it, len);
    n_ &= 7;
    v_ &= (1U << n_) - 1;
}

} // detail
} // zlib
} // beast
} // boost

#endif

/* bitstream.hpp
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
*/