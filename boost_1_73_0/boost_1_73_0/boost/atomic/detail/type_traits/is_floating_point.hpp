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
wmOhMz8+yB5c4REfmit05x1r1zBh9atfCLdfxZE21kec51uh3/5Y/Wod/fMG9TNlz72qrt7hWTN51li6rVLoSsp5ZTlRUldbSYwJ7EUuhvodxw5Bbt2F7vSdPKe1Tl+qrdOHR6RnTeW8BpYYGbzOsmTG88VnMijwOOV2t3om74GwF4RQi028g00Q4rwAdGnMqRDeDyEOVB8Qcl70QfUsFQv9LGFMDmYlNo+xJYwtZ2wjY5sZa2LsAcawMySxoKE=
*/