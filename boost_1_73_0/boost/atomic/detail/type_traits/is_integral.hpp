/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/is_integral.hpp
 *
 * This header defines \c is_integral type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_INTEGRAL_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_INTEGRAL_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
// Some versions of libstdc++ don't consider __int128 an integral type. Use Boost.TypeTraits because of that.
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_INT128)
#include <type_traits>
#else
#include <boost/type_traits/is_integral.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_INT128)
using std::is_integral;
#else
using boost::is_integral;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_INTEGRAL_HPP_INCLUDED_

/* is_integral.hpp
S0W33qBXF7urxe1fU9horlbDr/zDBM0BcbYVDK8Oa4YM3WCNIJihENGLHE7EcjiOTKu2t86hEsT5P/NBpqhhzCFr+5FO13Vx6ZAPCVgMg9ExazNii1HpNZDUV1hToS1Y+c7GatyQwILYu8I9iFtx+0PsO6mj1WEYNvCrBDM8mTnTfJn5xaHgENDqoJZbwnYkl2DSbiEYr9wAzcZEVRy6rc64gIRcHnbzQ5JrP3PVyKXuUxuU
*/