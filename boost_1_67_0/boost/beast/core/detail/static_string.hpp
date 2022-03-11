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
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
*/