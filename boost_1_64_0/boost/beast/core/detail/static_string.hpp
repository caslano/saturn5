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
q1Y2EIB1ggtYfPxtdp4aqzGE3ksXLs9CjnV7nn2ZZ1dyOemyunsirU256QqFfmOdIvCoZsbYgIMh/JSEBAtKREPvFctOiTcrasBOAA5Jhs91IzJfuvALqGm/ZJ00Lm0sAqhMDo9trq/6+oQBt1POkcc9Nki7loiFOw1Y/Dqs2wDnumXLfr81kyQFuRsx7C3bBJF2QNKt2MyPIJ9dxrzspwY3GvoqjC0YR5MVENmw0xcuiRfwlml8zoE0LKB70w0qlPDvAEbssccSHultsfnll0Hqzuch/1v08PgSGvnqczuI2OwDL7/C4q5ZnU4UAGX8gXk9KUxAH5OUB4xIR71Y2zTWvLwiAfPjK5HMqsTLLeZLpi7qH5O/Yq1dHj9zYuOHAbNpLLs3SsEWGe0uQhmeM0rv8NOvgKCr3PF3q7UpAg68AWnhY45Jngq6hQyYerpnCKgG6R6MzLeYLkb+gBV+fUqJiJYpmCQCvFnC62ypCBx2DSZJEIGW71lP1hjOBpOU0FQVEbaqWm2ml+4z6NwmH21lKm2MopRm1k84YQQNdLD9izClofjsyHkshg==
*/