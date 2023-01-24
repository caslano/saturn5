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
58sqiMoWdH8w1ePznjf1jhdYOA85jQxONOI+8OJuDVoS09dnP/g40Cwki6NcSEE0dnRB/Q0rA6/u3apHPQ+7lkijnp5YJAMrdnMrsm87BB5FW348kZuvbT+Eo46lSvljLqR//FErKhNrRDP9BjP/mf9J8A0eigLu1XincfJFZJM5HrTU+MOaCL+l/5TCUa0TqvkXwjQrhaC4kQIF+oQ/jHuYn9QwO+3vZuLmC9Ipp60IsqcSto21Z+uhjptel9fThHnQ4bFWv1tr1TIwWe+UUEuWCeYyKHLMf43ESxAbCmOcbKzUKyu2uAfh2Ri/LpGCyCflPakx4vHp1JcpshiWdRvjzs3JFvz3qRvhsla1Sb2RoBd7WpC3tHh2lVE7E4aUEaJlpYWxB/ZqWnY0xqKB+JMzK8XadoitKXCZ+cD8HIRaJlpsQbyEr1QU2Sg4+pGqyA6RQttGmxM4llR3D2Jf7Xmo1WxM06iRBBECB4mW3BpDGqpnNH2CO4IwamfPGA90QToJkyGjwun38QXxmSWdSFQET2Xl7LMWhcm68hXiZ9822+V1hPMZAFgF8Fr4DvPk+rtP86DMOAgq2Em4a9ki/JbxTtm8JWXwRjvsOHLW46KWXgfJPAh1TYzo+Y9h3AQ4OtuUvme4aLVCga9LHWcf0LbeXpcFxyZB4bRrAZblWM6hpEbuFAY1gnmlfe0g6LJCXAwSqam+zCMt/0B7
*/