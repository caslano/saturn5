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