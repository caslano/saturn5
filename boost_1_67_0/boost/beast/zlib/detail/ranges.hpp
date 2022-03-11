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