//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_BASE64_HPP
#define BOOST_BEAST_DETAIL_BASE64_HPP

#include <boost/beast/core/string.hpp>
#include <cctype>
#include <utility>

namespace boost {
namespace beast {
namespace detail {

namespace base64 {

BOOST_BEAST_DECL
char const*
get_alphabet();

BOOST_BEAST_DECL
signed char const*
get_inverse();

/// Returns max chars needed to encode a base64 string
BOOST_BEAST_DECL
std::size_t constexpr
encoded_size(std::size_t n)
{
    return 4 * ((n + 2) / 3);
}

/// Returns max bytes needed to decode a base64 string
inline
std::size_t constexpr
decoded_size(std::size_t n)
{
    return n / 4 * 3; // requires n&3==0, smaller
}

/** Encode a series of octets as a padded, base64 string.

    The resulting string will not be null terminated.

    @par Requires

    The memory pointed to by `out` points to valid memory
    of at least `encoded_size(len)` bytes.

    @return The number of characters written to `out`. This
    will exclude any null termination.
*/
BOOST_BEAST_DECL
std::size_t
encode(void* dest, void const* src, std::size_t len);

/** Decode a padded base64 string into a series of octets.

    @par Requires

    The memory pointed to by `out` points to valid memory
    of at least `decoded_size(len)` bytes.

    @return The number of octets written to `out`, and
    the number of characters read from the input string,
    expressed as a pair.
*/
BOOST_BEAST_DECL
std::pair<std::size_t, std::size_t>
decode(void* dest, char const* src, std::size_t len);

} // base64

} // detail
} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/core/detail/base64.ipp>
#endif

#endif

/* base64.hpp
WWqdcT8kgdihipd5FU8F+IgeO0M1yu08KnIkhjPeiP95j7j9iBppKYjifmm6d65QX/nLhCH2lrRrv+O26g1QuPbduHGzQFwnCrFijPqFMKMsFfV5Ks3EJECUA+kkQnF31y9EWKQ5yljUmYDPkBNfvA1iP/4DSGY8WLWJcJE+FokU1q2TPuj8Y0D+9JIod6a0A2g3ZWnkG8POIIImOZkSJFODUnymw4MM5jk5JYNUum9+f+xlJA1P0xSP98998Bir73jwuS+AelR9S09gjmpQRvuhaTUFFl7Q5S2Qgz6vhdMXtnRecVDjiwe4PnNDb1kZfIxczyE76rm/lEzcGzxr0VErdmgnIwQpUI5pb9NcbmXHqXNisSsd1oYB7gIARu5NfgP4gXRuHkhcpX6LYTtFYFy61xHfPBNK9UwcHmRqUAWwmTI/qVerP81zriv8Z6aA3XBNJgN64n8MBmyMHWMSsj2FGRl7TFYrQI47l1pOV/Wpdv8JIuSLl237gKaEuyAkhnF//TtS0+4ZD/Te34RnWDSN4rxi+dZion0FZ2WqASkMgI4w5l6UviPGBg==
*/