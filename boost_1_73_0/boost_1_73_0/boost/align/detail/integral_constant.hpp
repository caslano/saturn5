/*
Copyright 2014-2016 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_INTEGRAL_CONSTANT_HPP
#define BOOST_ALIGN_DETAIL_INTEGRAL_CONSTANT_HPP

#include <boost/config.hpp>

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <type_traits>
#endif

namespace boost {
namespace alignment {
namespace detail {

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
using std::integral_constant;
using std::true_type;
using std::false_type;
#else
template<class T, T Value>
struct integral_constant {
    typedef T value_type;
    typedef integral_constant type;

    BOOST_CONSTEXPR operator value_type() const BOOST_NOEXCEPT {
        return Value;
    }

    BOOST_CONSTEXPR value_type operator()() const BOOST_NOEXCEPT {
        return Value;
    }

    BOOST_STATIC_CONSTEXPR T value = Value;
};

template<class T, T Value>
BOOST_CONSTEXPR_OR_CONST T integral_constant<T, Value>::value;

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;
#endif

} /* detail */
} /* alignment */
} /* boost */

#endif

/* integral_constant.hpp
s8/j5pMOBOPPRXbLrzUY1rb0+Th8bZ+8IZ5c6B//DN9qMnb2uaLRb5LP2/IfxYeO/8SPv//ND8x7H6XSJXCo8Oe3OFldz5G9tsuMg8+XXTNIJw5/AM0ng0yfAhrshdH+eX/NKJiJX7Pf8ROBG9/v7e4BqAAI8srug9/tYdZk92Bai+Hv7bLKWwrHPcw9r6e7ybcDfZRL+XVc3K+z/b10SSJjpG/t9XbG6abL9e6v0mf+Egb+m8hkhJ4P3xs6S1fwu/DMA4/cG1e29ih97vvkd+P194f7Xmnek5jFQudzJO5aVpy6itHNr1PPoKboTFFMp9poQpw2VOwPZ9fT9WpagDyZcK4xKOb2Tsowf0BQ/gf5Ti7q7p6LAlVUIktvh5w8biL77p7KXsa+PLSPZDE+DHuJjKyWNCq3c3grV3RjqUHYpH2q9f2e7HhOjQqhq8VArY65rguFMarUm+auLcSwMzmhS93YIz0Yq2Lvr8gJfSvUpobtSVZbijZliZt0D1dPHruvJHbIhkSMHqFdiJLilpH/nc9906AKNuUznfI+hQTI/dPz48OX/NDDn3XyOOskFmwBr6DpOhBHz4zqkWdSzJen6n0HE9iyXDB85rKgDbBr9lx/PDGBpRqsTa51PqEKoAqDumh3ohBplCFH
*/