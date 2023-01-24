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
ubjRSrmdDfBEWzO0JaqtgD/LhkIWKmsc/cTl11lsUoidztKNUmo2tnHQQQuywFA4MZT5C6SBqr+gY2eHsYPk2cF03pn1uJyTx/VfZY+bbKbkAaFynwDsRJvRa0HcDvtUzY0WknAqgN0VO4xNn4hTQYM0ocpSN2cvWIJc3TS0TJ0OweNABZ8SPFNdF/aBhKk6GshCjyOWWBYiUc9GbD7zeoLuwmAyxCj6r/hi+CcEimigkzgg2BzV3wJu/APtp7mBImwAg5X1semMGJ4V0KwWgw5miY7WuNU/8nMPTSglzErGbYUYplDSFNFVL8e1yiMxb/fBIFOhRr4X2xMEfKIc3dUQTO3RjWap6GgpFXVFN0aedMycTd33xwUv51Ze2mA3RZnqTKbg+Arg9gQ4/ahHdSuZOzZIE7DCtte+GNb+3ivQBKy09fkd8qpqp/B+6MTXuEqLPqdyXzHEARuhr32hD87mB0CVEyWcJW3mGtcT3GZLbl78zMteRYv+F3nuu8zGPP3laGiNaVsDnWqhQ3jW81AQwXSteiYEKghCMjJO9EqaCQ8ZExWWkvsHBoQmYpMpPaaIxuStlzRmr0KoOI+bEOvn7P94jHIjj5UbWM1QbuTxiVIUS+UG4KKC4Jm6Kd6uj3nVPDpJNntrpTORXPwxLZe/DYu9jeTzIpZrZTYuV7FVKNw0Ve7QnfqvLVNpxQorAOf8Os0qs9BtxAp8
*/