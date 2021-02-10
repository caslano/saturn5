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
VD96KAu9xtoEj0cPxgG09BoXgWog4Sn2vv1tsxDorAAud1DVIVogsCVypfHqMR4Zf+I0W/DUlhFFk10Fk0/9gPWDwK2VjHCzorHIuCpWCyOHrSy1C7P01rr71jhKHljnsJBIZGtemBRb00nuRuPB5I7NJzfB8I+hzRzjeyW+pLmRrjTBwTI1pWLFiU/vctuaLqf966FjKLAz0crs9z6pmNzO93DsBBoPRyjGo8jALibjeX80Hk4day1iLcfeoLOfYNHZsUmjcSOLamcqim8hpHWRqQin2yTSq5fwpPo3g8UMQleco7zyXGLk+3fjXxdr2Qds7Wakf4PHCqtCsS9WvAYIgdr16oDFwWlzD8lCW71QZQrVBoYTg8nTtD4Yk2zY79/sEzHEJ/4Eebu/R3yquM1f7//GmPWD2dA3denCmw/ogr0g2JYrmcjYaYdc/oq3guEwP9osR9Xhv3M3mvJueuP9C1BLAwQKAAAACAAtZ0pSkqpPEqgUAADiQQAAIQAJAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvY3VybHguY1VUBQABtkgkYO1be3PbOJL/X58C0dbEki3Jj9lc1cZJamWZTjgjSzpJzmNnpri0CFkcUySHpKz4dvzd79cNkIQefiSbbNVVnXc2
*/