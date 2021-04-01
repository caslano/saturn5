/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/alignment_of.hpp
 *
 * This header defines \c alignment_of type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_ALIGNMENT_OF_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_ALIGNMENT_OF_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#if defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) ||\
    (defined(BOOST_GCC) && (BOOST_GCC+0) < 80100) ||\
    (defined(BOOST_CLANG) && !defined(__apple_build_version__) && (__clang_major__+0) < 8) ||\
    (defined(BOOST_CLANG) && defined(__apple_build_version__) && (__clang_major__+0) < 9)
// For some compilers std::alignment_of gives the wrong result for 64-bit types on 32-bit targets
#define BOOST_ATOMIC_DETAIL_NO_CXX11_STD_ALIGNMENT_OF
#endif

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_STD_ALIGNMENT_OF)
#include <type_traits>
#else
#include <boost/type_traits/alignment_of.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_STD_ALIGNMENT_OF)
using std::alignment_of;
#else
using boost::alignment_of;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_ALIGNMENT_OF_HPP_INCLUDED_

/* alignment_of.hpp
my2y0qbK0jfwJiD7SxwQXiIthYz6F2dqR0Om7WGimN7nVd6mqyBTEfi61AZwXjLy+Qmjzyyc0BMcfpcCywdkVl0m/dug1bGAGlpSIGt7hQ1QTFy0bQhCX2tWps3Z2WNQlmIfWvNUsEaFOa6hxiXg5ghtjaMHe8bkIghQmYrleALNO1KTck5g3UxE3rSwLTSRkHkVW5GNwlZoB6lOQP+ATyOi7AZb5pkYCWUbjgsjZ6y703MyRB8pZ9TsZ5AdO/8rjWO9B8Xo3BzWyvWWorkTDSrhzDEF/81FcJvAbCwIn8Xv5PpKV+M31j21TB2nxBA9P+5nF2wTyaVJmB1fdsN1mY/Kj0mjdeJClH0nZ8a6KUxYkaYPlog6/tJtOpU8g274DXOaAfY9Q3rpd3L9A140xcKwSHCVnCDUWoeXkk17h+aOFJXTYufcZUjYnMZcFy+H5gBGK6KQX6mor7T3dfCpIGdZ1y+ctoWCO1OePKodoKepnT4iYcH5zQOllBS4sm8pRwQzC5ZvL1unWXYzoKsRUaiTZsd0xbv6e6Fw6hjdg2aQ+ng0GMV5Zbxmdw==
*/