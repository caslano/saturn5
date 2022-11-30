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

#ifndef BOOST_BEAST_ZLIB_DETAIL_WINDOW_HPP
#define BOOST_BEAST_ZLIB_DETAIL_WINDOW_HPP

#include <boost/assert.hpp>
#include <boost/make_unique.hpp>
#include <cstdint>
#include <cstring>
#include <memory>

namespace boost {
namespace beast {
namespace zlib {
namespace detail {

class window
{
    std::unique_ptr<std::uint8_t[]> p_;
    std::uint16_t i_ = 0;
    std::uint16_t size_ = 0;
    std::uint16_t capacity_ = 0;
    std::uint8_t bits_ = 0;

public:
    int
    bits() const
    {
        return bits_;
    }

    unsigned
    capacity() const
    {
        return capacity_;
    }

    unsigned
    size() const
    {
        return size_;
    }

    void
    reset(int bits)
    {
        if(bits_ != bits)
        {
            p_.reset();
            bits_ = static_cast<std::uint8_t>(bits);
            capacity_ = 1U << bits_;
        }
        i_ = 0;
        size_ = 0;
    }

    void
    read(std::uint8_t* out, std::size_t pos, std::size_t n)
    {
        if(i_ >= size_)
        {
            // window is contiguous
            std::memcpy(out, &p_[i_ - pos], n);
            return;
        }
        auto i = ((i_ - pos) + capacity_) % capacity_;
        auto m = capacity_ - i;
        if(n <= m)
        {
            std::memcpy(out, &p_[i], n);
            return;
        }
        std::memcpy(out, &p_[i], m);
        out += m;
        std::memcpy(out, &p_[0], n - m);
    }

    void
    write(std::uint8_t const* in, std::size_t n)
    {
        if(! p_)
            p_ = boost::make_unique<
                std::uint8_t[]>(capacity_);
        if(n >= capacity_)
        {
            i_ = 0;
            size_ = capacity_;
            std::memcpy(&p_[0], in + (n - size_), size_);
            return;
        }
        if(i_ + n <= capacity_)
        {
            std::memcpy(&p_[i_], in, n);
            if(size_ >= capacity_ - n)
                size_ = capacity_;
            else
                size_ = static_cast<std::uint16_t>(size_ + n);

            i_ = static_cast<std::uint16_t>(
                (i_ + n) % capacity_);
            return;
        }
        auto m = capacity_ - i_;
        std::memcpy(&p_[i_], in, m);
        in += m;
        i_ = static_cast<std::uint16_t>(n - m);
        std::memcpy(&p_[0], in, i_);
        size_ = capacity_;
    }
};

} // detail
} // zlib
} // beast
} // boost

#endif

/* window.hpp
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
*/