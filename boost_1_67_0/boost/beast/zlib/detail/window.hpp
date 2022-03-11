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