//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_STATIC_STRING_HPP
#define BOOST_BEAST_DETAIL_STATIC_STRING_HPP

#include <boost/beast/core/string.hpp>
#include <boost/assert.hpp>
#include <iterator>
#include <type_traits>

namespace boost {
namespace beast {
namespace detail {

// Because k-ballo said so
template<class T>
using is_input_iterator =
    std::integral_constant<bool,
        ! std::is_integral<T>::value>;

template<class CharT, class Traits>
int
lexicographical_compare(
    CharT const* s1, std::size_t n1,
    CharT const* s2, std::size_t n2)
{
    if(n1 < n2)
        return Traits::compare(
            s1, s2, n1) <= 0 ? -1 : 1;
    if(n1 > n2)
        return Traits::compare(
            s1, s2, n2) >= 0 ? 1 : -1;
    return Traits::compare(s1, s2, n1);
}

template<class CharT, class Traits>
int
lexicographical_compare(
    basic_string_view<CharT, Traits> s1,
    CharT const* s2, std::size_t n2)
{
    return detail::lexicographical_compare<
        CharT, Traits>(s1.data(), s1.size(), s2, n2);
}

template<class CharT, class Traits>
int
lexicographical_compare(
    basic_string_view<CharT, Traits> s1,
    basic_string_view<CharT, Traits> s2)
{
    return detail::lexicographical_compare<CharT, Traits>(
        s1.data(), s1.size(), s2.data(), s2.size());
}

// Maximum number of characters in the decimal
// representation of a binary number. This includes
// the potential minus sign.
//
inline
std::size_t constexpr
max_digits(std::size_t bytes)
{
    return static_cast<std::size_t>(
        bytes * 2.41) + 1 + 1;
}

template<class CharT, class Integer, class Traits>
CharT*
raw_to_string(
    CharT* buf, Integer x, std::true_type)
{
    if(x == 0)
    {
        Traits::assign(*--buf, '0');
        return buf;
    }
    if(x < 0)
    {
        x = -x;
        for(;x > 0; x /= 10)
            Traits::assign(*--buf ,
                "0123456789"[x % 10]);
        Traits::assign(*--buf, '-');
        return buf;
    }
    for(;x > 0; x /= 10)
        Traits::assign(*--buf ,
            "0123456789"[x % 10]);
    return buf;
}

template<class CharT, class Integer, class Traits>
CharT*
raw_to_string(
    CharT* buf, Integer x, std::false_type)
{
    if(x == 0)
    {
        *--buf = '0';
        return buf;
    }
    for(;x > 0; x /= 10)
        Traits::assign(*--buf ,
            "0123456789"[x % 10]);
    return buf;
}

template<
    class CharT,
    class Integer,
    class Traits = std::char_traits<CharT>>
CharT*
raw_to_string(CharT* last, std::size_t size, Integer i)
{
    boost::ignore_unused(size);
    BOOST_ASSERT(size >= max_digits(sizeof(Integer)));
    return raw_to_string<CharT, Integer, Traits>(
        last, i, std::is_signed<Integer>{});
}

} // detail
} // beast
} // boost

#endif

/* static_string.hpp
7fwLiExOnuj4O7wqsQh0MGnuGeb/U9WjEX/ddtVbhxnX/JAVdWWOyxd6ppen4fUlSBWRZ/f92N21F0k3piMeezPbqB4W0Krh3Vs1i2hUi+4chgHRp0CC3/XmRSgMCXphBKD5zA/cZrrybCKPuKp8/o4fifLdzA/XEOwWHig5u+nnEBQvi37x+6ey3yev8HY13XyxxU3GF39m5Hn3E9MCMbbH8SC6pyD1Toc/6CfvJRmG2yoM+xMfX+Kf3KcbbcLCLfoDDo1hmzB24QDJYRsbS4B3Yswdy6pwkJvu02umEa1AVQ2uVX0I5pK4v2YctGWhA/tS/K3sN7/qX1fPXZxHPDYyQivyadnjXuOGVhnsJno/Jy2iTKFy4zEb4XpMkQpoFOqqU5e+E5u2zcN7e6Mun457D5VuViwy0PiKk2o+MVyYtkpeFWoQpcNLO5L+8kQQrvkoOlHp8om9CL1QO7FCExzWREIqgSSPMacllc5YjwLAqa/gPednE15yb7Jbw1vBy+akA+Lo7NHCZWhieIgSBUAgF5I3jF2wVL2UUGEUGXC5+fpMfgAGm1MFd2J+A/t07NwLXoOP35qmW2hvUTECgRIOuU9JdfcjK7CbTB6vLCYurfhtwxVCEHD4nLEGOxr4QU03MLKnFiLZ5Uq5A7kMvbxx+QnGhoAdNj/kpmYaOCFt0zt+0wHMCX86Sjzbka5U3rHy0S2OTND3Nwjl
*/