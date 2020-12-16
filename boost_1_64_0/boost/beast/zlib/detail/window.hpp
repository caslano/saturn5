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
t2lwqE9FHS6oHXYv9JBzCzzOElzMc1LCnmP9999rHzfV23vL7p8fFqaUpnYtScCs1YJ9CFNmSJhoVFSFyZSl1+NM38ri+doDQeGSu3i7r8dUYz49YiR/r0L2I9pr32ln2H09Sozu7IgehO885CUkjTZH/YCzj5E5Q9CwALmzMf/DFomM6SPvITObHX7vguAa3/R2VWt847WXAXEijRQn9VXc3E7zADqFlpldSrd4edwMKQ2mW7I73ZZ6lpnwtpnSTm7jjzhPw9pWNk8TFCgiYfJ0BlJG2PLDwmbDdPD5B7a9uNK4yWItQYzC6fiT4BmPsda+pe0LW2HMY1lPEGXbKgGPtspqoxcjMydlGHNd2+68Nu7I250eZye40kv7qxr/TZvAmO/CrLy2a7w3RPqt5fZbm33s1gZ7rz32X+OdZdZgD/yyS+fJX6y84NaRM1p8UOfCs6mDZu30M1dlff3MS8WN8wb+bft95U1XkZ7JwfvX3Pn7h/c8eeqBM+O2NO0e8+V4v7XQ/muqbzJrqstb/fzzcyb+fsbPuk27Kja97pt+a9T91qL7rS33W2Nf/bX01V3rXm7itebGy198a0dKyjk7Jp1e/MsbPvBbo+63trz6a+C917T7r7E3a3Gdvmn15W+DccgVgdC1uOfD7vACOA6uhRPg7+Bkrb2dDS+EZ8N18BzZXwAvgpfBCngrvARug7+Cu+Cv4XPwN3A/vFRrjC6DLSD+aE6Z+mQh2UV4Q+eUER8zV+smhftmmARvgR1k7iqz1k6oX5R0Mv6FrJ0wa1PMexrWgvGwAWwOnTlfSXI/3bgPnfP1Fc/R2jDj/hvYAH4LG8PvYAv4PUyEPyicAbOWBsC+MBIOgVFwBIyGObAWnAZru9eSHCI+9RSf+opPAxMfdOF+xWGD3HeU+xhknNx3kvvOct9F7rvCxrAbbAG7w0TYA3aAPaHNP/nf0iP/MuR/f/l/gvwfYPxHT/4PsuFVPwQ82yO8V2ht3ZWwI/wD7AavhynwatgXXgOXwWvhCtnbNbht7ZpE/A+dw/yk8vcpGA13ueYUbpC7LsZd6JzCe+XuAVgX/lHh3Ao7wz9Bu8b0EM9/WP48oudvt8/XbxTY0OP5r8rda3L3VxgD/6by+bqtH2q/g7oe5ek9+fO+/PlA/nzoCn+s3Md4hL+d3CfDOrC9y13SIdx1krvOctfFukPkLtrDXR+5S4dRsK/cJdk2qGnTGnftTP1Xoxy9eDgW9oDjYSqcACfClXASXAVPhrmwCE6Ci+FkuBROgb+GU+FGubtZ7u6BM+BDcBZ8FM6Gu+HJ8DN4JvxW7r6Xu7qEsQA2hHNgIzhX781C2A4Wwa5wHuwF58Pj4QKYAUvhTFgOS+EyeA48Ha6Bq2z6qr0J4z3St7vStwdsZvTtmh+17wiLcRe65idD7+v+el8PUH0dCLvAIUrvTNgfZsGBMBsOh4hZkzAS5so8BY6AM3R/CwF9VPNh/ebCfsu8vqQdMWZO7EZkHPNgS5C1iNf82OhBlXNkO0CvebIlh5gr22BwcL4sAjMHV3/e7K7B+I20YJ5sBjId+Yz7K2FwLu06GD6f9lHNqX0TboTRmaFza3tk+s+vXecxx3ZbJnHN9JhrOxRJYX4pnIwcat7tOu5tQq7j/xegMwf3wFDvebhrNBd3Z/CenZOLZB16Xm4P7J25uZlZ6CHOHN2VWaHzdNdj3og483V3ZoXO2U3PPvy83c9cc3e7QGf+bilcj2xGwufyflDN+byZrjm9JditQzYhuxCPOb5UhKp5vhlIvub7bgib87sZ8wH4WpCIe/5v01HOHGD85v9ZSLnmAq+Hm5AK/s+mHhUia5HNyGtI9E7KATI=
*/