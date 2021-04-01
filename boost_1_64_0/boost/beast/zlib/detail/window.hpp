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
WNFxJxpRsHbiCOZKQ0YIUcGCdTDUDgDud+OepkCa48U6oK5K8wRVL+EI+q4nBH1bcM8fwYDoyD928PCZI+vAtF2Ub6ctUYhvjRZ/oJdIpbLkvo2uLAbOIBPpSO6eBpLKwNhWDP5Zazb+wnAj6BQdh20AflPVKL1+Z9lF8yPAOergOLI2pB6AJ0MhphSN1m4mb0AofqcIO4KfHokLQ5JQ7UtKWYxNZ0oOA7BdCzhcfmQM7HgHd49v+mtJzZ/QlUbXJJBv4NLcED0Yc62mgEaXHkdp+ZPIGK6U2rY3EegfbMxwmvDvbk3vse1ywbwDjzcaTzPw9hJX3Nk8DE8pGG01BJ2u35ScR944kiu79rn5LNvPCc6eJr6muiqZoYf2/B66riJeuJVnSz7TFtjNibvBDrz2qGP8BcBSCEpoRMaC6XEHuLIqBzhLw4typ/8kVNHQMNi4e+JAaIDyJAbMPFylkfFWyVEmvNzXjJ3yUD0zt8/MgG2lE2ybVzw2TDlQhdAf106ARMbA+FPqP0DD8pPV1DRN09ZeKgLow0C75iKhRqb7ivGAiUUfpktt7w==
*/