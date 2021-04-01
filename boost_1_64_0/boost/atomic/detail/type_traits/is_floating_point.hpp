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
e2pwBFSPYWEavPsWhv6JgiRbwoIxFSU5Oz56TmI4z8lMpCpln9WyqoubUVIYEQcIFzHHnEIziUx4OZs/M7idivRrK5X0j2YU5MKwznSFpTjDrxMWkFmpBCZdkQwfN7JPE93khNGLbeeJ8TXEf64ZPWp0DMzZRunX0DYsn15q1avAxsExAEtF8x/ILOur9jjzUoHzkWSjGpm2W21EwQTda67rLwFSY+c83CbB9b/ZLyq0tEoLUXrezLl0miO5zUFIeA46RO9H5dBkNJs/AZMAh+YxIfu7GSboXJroshnWso67teEhGyW91fnkbbESaKheHDRiHy5sGb2fV0up8qhiJeIkIRkMPqzLR4Z7PGgt8i+k7yy5URVyqjRp7XA5fW+k39Z9pWZ1tmP080bhvY4Ma0I0YSu0ezEa1nQWij9gCS19GUrZmJAR6v7HPmzvuNlpVS1eE05e9BA12HpFm8H/7+lPtgC0IiUdTGjQM7yY1Y5Ary8a//6uK1ceQgidezEiR55y1PMitXqly+gWigZEkBpfIaUu+J0rVM6w3Bs7V8n65YYrReLKvd7UVA==
*/