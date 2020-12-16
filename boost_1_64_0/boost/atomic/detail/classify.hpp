/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/classify.hpp
 *
 * This header contains type traits for type classification.
 */

#ifndef BOOST_ATOMIC_DETAIL_CLASSIFY_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CLASSIFY_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/type_traits/is_integral.hpp>
#include <boost/atomic/detail/type_traits/is_function.hpp>
#include <boost/atomic/detail/type_traits/is_floating_point.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename T, bool IsFunction = atomics::detail::is_function< T >::value >
struct classify_pointer
{
    typedef void* type;
};

template< typename T >
struct classify_pointer< T, true >
{
    typedef void type;
};

template< typename T, bool IsInt = atomics::detail::is_integral< T >::value, bool IsFloat = atomics::detail::is_floating_point< T >::value >
struct classify
{
    typedef void type;
};

template< typename T >
struct classify< T, true, false > { typedef int type; };

#if !defined(BOOST_ATOMIC_NO_FLOATING_POINT)
template< typename T >
struct classify< T, false, true > { typedef float type; };
#endif

template< typename T >
struct classify< T*, false, false > { typedef typename classify_pointer< T >::type type; };

template< >
struct classify< void*, false, false > { typedef void type; };

template< >
struct classify< const void*, false, false > { typedef void type; };

template< >
struct classify< volatile void*, false, false > { typedef void type; };

template< >
struct classify< const volatile void*, false, false > { typedef void type; };

template< typename T, typename U >
struct classify< T U::*, false, false > { typedef void type; };

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_CLASSIFY_HPP_INCLUDED_

/* classify.hpp
0PdhXFnH5t4SsyzjJ4nvb/hRe975xX68lanzA9aKvIsUljYLQ9wgf13kZZZP/E3MqNUy3CTmvuB+z9QhdBv2dY9Sf/R+kp9qVmy+gZNfEXuWb49vPs7w1gDye2j4PeYKpY3MD7Ja8S3eOf+jOMF8Yzff/i7uRp0KhL9wSOGCOXack00bVa/lJuimi9g1yf1erd9rg3aZLY5ptA8bFyBsLfOEh7w6LK77Na6nWaHvzV8jrts0rkUL5hBf4mrKrImruslqdXzwL/GR+qbXT9cxpgHU71yYAO3r7Q9cvz54L863v+Pq92FfgtY3MxdA3RPKBusqrz1+QjloXs+0ziQOs90u0XoX9DtV65SH9wZ5pniTrGXeyHqndUz9DBR5AfKfRG5UmZkzI2y5l5Vp7mN9WcX52kbjpsqEMVbGe9jX2FFfKwotR3wPDJe5MJ7gtf8p8ZsQM75cD9UwJBjGhfg5Jteqwg+y8bPVu8464gn5WVlgaZ6uwk+cuHndm+aZ7HRTGHTTGaaLm195j1lNDjeNQ8SNzmHxiJtXvD2paY5wBgfdyLdxcXPYO8uT7kk2bsqtrjofaInk51zKTprVEV+5VgfsAvViktiNstph2wnbfB0n0HwY7JxX9Kbkw2orU+RQPsRZ53sdcQvEX+/TP8TPn7119NTs+RAbsSsUfw84/Qx1XmfmcG3jdL7EvBGBMtZV511kif9nvUUenzXWO9Xa5u1oOfLP5E02/Ktc/7g3z2rnTJd9H0z4fxE3dfhBdtzfTGuBs0wUWI7xn2Rxswg/yI68yLZKJJ0WKl/MHvE6yuYQy/HMGizp7GHeK9pJOj/nTIspL7XYvy/xfNN7KqXeEWaBs7zfLtc83zw7E+UaTZ7ZVgenn8GW4/l0lbj5nYnHTyWMgZb9/nAggTKSEnx/2LSQF4jAu4XaLQ/ZnRppt97YbXwr0m5HyO7JoF1rzkuqh76E8GcYbPYM2xjxDMvGbItpx017EtaevqpjoXYZ6wZ7weF2e1oU3p5W1ojfZu2ptu3qPs/k5+siL4r1Xq3ue4m8EPm3Ik+TNmGqtMG1dbXlldp+Bt0PMnMa3xJ5hKMNuSBQJrQtyh8p9clpP8RZloeL/THLYW/KRw4cKPYHrGTzfuO3sjWt7cXuHPpVPt5ncky5ixPzZNvcvDu9XxQya6/vaZeJuyyTVyttWd/H5iMfEz8+86y4VuyvlneiTC0c48WsnZhV6XvSWDFLsCLaZzO/aJbYpzrtTZuQDdeIfWJkm2ueP2XN7C8w/jvDArF/0Onf5Hk1/peK/XAzz/KIpLM+5J4y0rgq5H6kuO/uvN5QZ3g9xD5OzgnJSsWiAyHY9SthU5EvM+V0OhqpyTp/qa+6GRB0492UmOpLTknEUUJcamInmJgW7naxuqVf8nqqLzElGTfJcSlLExJS4+JS4xKdbjebcDc+m5KAw3aJTJ+KS8VtYqLV+v5HXpS6XhDe3zPvsNQTzKSehNXpfXqVhzTwH6DH2PPeR4XX6araE9Zp3If3Aa8T+ftWjD6gun+oxfc77WeRzpb7WbqXXswx0Ad62OY33jDs/klH7//muLnrXvjj8+eOiDXWGWtstO1j0ydrb7y2ntXxnn4/R8mzJAf2R9fob3tc70L93Y/fR+FKS79jwOu1f5GMXqrhZHkDe/+fAvvAbnAg7A6Hq7wIngarYS94GewDr4R94TaV9awE/R4g3yG4XthZCTJ+44MHYQH8GRwCH4NL4ONwA/wpvF3t7T7kYXge/I1+V99tad8VHtF0ZaJv0uu8ibve8D1YBP8Gl8L3YRP8AK6FH8JLYDzx3wQT4GaYBK+G7eDXYDK8BabBO2B7uA+mwx/CDPg=
*/