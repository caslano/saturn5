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

#ifndef BOOST_BEAST_ZLIB_DETAIL_RANGES_HPP
#define BOOST_BEAST_ZLIB_DETAIL_RANGES_HPP

#include <cstdint>
#include <type_traits>

namespace boost {
namespace beast {
namespace zlib {
namespace detail {

struct ranges
{
    template<bool isConst>
    struct range
    {
        using iter_t =
            typename std::conditional<isConst,
                std::uint8_t const*,
                std::uint8_t*>::type;

        iter_t first;
        iter_t last;
        iter_t next;

        // total bytes in range
        std::size_t
        size() const
        {
            return last - first;
        }

        // bytes consumed
        std::size_t
        used() const
        {
            return next - first;
        }

        // bytes remaining
        std::size_t
        avail() const
        {
            return last - next;
        }
    };

    range<true> in;
    range<false> out;
};

// Clamp u to v where u and v are different types
template<class U, class V>
U clamp(U u, V v)
{
    if(u > v)
        u = static_cast<U>(v);
    return u;
}

} // detail
} // zlib
} // beast
} // boost

#endif

/* ranges.hpp
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
*/