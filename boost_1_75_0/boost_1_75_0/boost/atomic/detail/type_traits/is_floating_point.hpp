/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/is_floating_point.hpp
 *
 * This header defines \c is_floating_point type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_FLOATING_POINT_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_FLOATING_POINT_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
// Some versions of libstdc++ don't consider __float128 a floating point type. Use Boost.TypeTraits because of that.
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_FLOAT128)
#include <type_traits>
#else
#include <boost/type_traits/is_floating_point.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_FLOAT128)
using std::is_floating_point;
#else
using boost::is_floating_point;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_FLOATING_POINT_HPP_INCLUDED_

/* is_floating_point.hpp
zS2ufqZ1RB9Yza8b49H0UdvyrHkfL7qPNl+l9yb2oxUAyPux3IATdVDwlip3sCgSxjpE6NXjBnYDqKS1Iro+fnNzGF2uUNrbDxpEeiIvosg9TU8CRV1z0aF8Okn09z7WELweu9lSHRB/2dNfovBu/nPZjU/7jvsx5lfUCPR66qellgHq+yvxTi9i5IOhhSRSCiflDklHhG2GJ8Ffh1x3zYIiQwxRzjLHeyRojRfauvhpc6iQoovgBcp5O8jT2ZtmLP+HkKYg+Y1mvyfsWGRIv5PxXwZ2yWmFIUd7fWTM8Lt4h5DP21oC91ftG9noSFvNo67fdUjkrBdzU5dHwIKxvPmB+GAInsoisgf1L7ZedDfTw/2LrTn/f1sL/ndby3v9m60T/2FrhSqTeqwV3uSir5R63Sm1JdnV3gNrJitKrvofPmWnyLlFOzh0rakfZ2SUM4U1daaUApex7JXhL9KkV75+LyViZZpYkMZZQtjZentxKTcUXwb16tl2e5yt/s3W4zlLQafKcab351YL3QqpM7Ts+UINJdrbFSSU1pUM5uVnQg1Ln2tFHxuvtdKDX7x96/LLnxbvYleEBysNRQnVJtT9fcRgJvcv45JnuwMAz5q0xrZw5uviF+vcCZ+8MflLS7S/m119prvT1RmGl+l4lJEvVIc47/lYQvHoRoFx2ib0XhpfIpO4FAPoWoUJE40NSADYO8P410JJbpnQ
*/