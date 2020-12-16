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
sF49oZsle9p0jeLlMH/i5vyJ0W7X2LTvtUCjTfEsNz2vcpSEoX2QboNu86hnhjXovoH6Ythn+iwy1gPCGvXZTCJbCUvXcyciMz1/Uvsvmj+xn09o/7yK/TzDv2e+5SKZb/m4R97hJ5Xde1XMA33fG3HWNTc7zVf8ffMnHTlPkqX4HOLzsQ4/QviMVEY8vz+dxHNbJvO8lylAg2aatjfA8YTPjDqzvQHOs4zg/ow9uT9jb863lHK+xc35lhWcb7mY8ysPAgfyHJ1Ufjc/BPg751OCXJ7wSGA6MAY4HBgP7AdMBI4ETvkPzZN05vyIz7xIh8+JOMyHdOpcyN81D9IhcyCdNP8xB/Mf7sAcSOAKXP+7q1P0f5B31Pr/lW3Q/2ve17rs3rhzq/r/Oe+b9X+md9T/Ge+s/zPeXv+/EHFm/X99f7zTxHee/v8Rz7s/hPr/LGCPNNSHVWYt6f+kHaP3S4R8YPjTXA76P+kztJ3CoA+Ynjp7srxfxtBOYbPeT3ky/Qitb/8h/okukb+ibk/6Uk2fpr+z+FX8WS7mT/3dbNOQaagzu5Uy2/6uALUu+05S9i912nSftCIntptQ6tvednaZpD1NzkOPYeX+JGmvYRiIFNKJPPrZ2viLBXaXfJJdzfFidVHiy11IL/FjXXbt7xWJi6DfxXvFqQy0xzDq9UZ7vCm62SZjPu0xHoO+t4nx/aNab7PGngjkb9kTkWvThvNsdHyez27W8Xk+u1XHd5POrOMv03smpO5Muruz7muv07f/LGJ7HdpJ9+04HbejdNZnRVfOn+b6Ydepe049/+LnZ77T85pfnOcS7OcGnOcA7HVcZ53YXodu/xyJ/dyM0xxA+3Xu9s7xOMzZUHfnM4TPtiQf3X0idfcp1N2nUnefRt09m7r7Wj02yXgv+Rjjx0NwinsjBlF3HwPsw7NZ+5rOmp1C3X0B90aUUXev4t6IY6nDX8W9EddRh7+DNsxe4LcVL9Nm2bfcI7GJeyOC+G1FDL+lyOQeiFzugZgFnEAdHzp8q3p+QMcP6PgBHd9Xx0d66PdNAR0/cAWuwNXZ+n9Z6QJR/ztA/z/RpP934fl/s+B6wu0OdzZeVhrWWe2uF1Z6Tlnx2Wev97L/JPSj8B6jz4BiHvHUwaw6Le7F+CH0u9SOL8HPsyOC9TlozWvXW4R+FzUc/6nXMo9Y0OwVdTdoV7ng8GIXHp6o7bWfBH6D1IwoQ9dKUrbXnt75gXSbveKZWmeS8ut5BJTRvLapZZrGbyqyOacyCa4GDOe+ZJXpAtR1fuki4be0p5Yp5Ud68NYHvIWinjbDnYc7hPUIS+vaPTw8JDw8Jho8Bht8I/yaaHF+Om8016UPk/ySVLgKlXmVjaBVqgj0k4TvgyV+mKRfJd8YFBrHTkr6bBfj8cYahfStyHOSWZ7gjfK0yukFyimDZ5gMo5zqfOVUWlWJKCc5kT5DdOnB7SyPYZN/g6TH9xNDrfM8v3Ke53D2jXLD4UejT/kW4luB7rpshfr8gbB6gy5PhSPPaZAZy8v0CaY0CyQuR8fFqVi2+VDJo0DF4P8MFex4ZsEYoQvVcxIHij9MtVZHERaZFIo/U/sXiHwyJC/0v6FK/HO13+e8yBDqVqzP8ZTXyno/eeW7CyuMxlVUUakssqOMmGairYwY11J979lW3p504OUyvuYNcXnqvh/wFKPufXlZ6j7cxIxpfKxaqpRuo0yXoOs17GXPWW3Xo07fVS5T2y6uWLpE6TYUKnThrmtRt29zbM3R+cXJuPdCCMrbleNeRD+/cS+WNKtBcxrCgsd0DQoP6WWJe80bt7w5rg/jNiPuVCOu5qmwaYjerpcn3/ach2HMY23/inU=
*/