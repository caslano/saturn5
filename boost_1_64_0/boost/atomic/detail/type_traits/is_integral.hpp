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
nHVKTBDAhWMoW7/E+1hjHuoHyr6+zPTaHh0ppa3QwGaAYc/Kqvc4gaBW+Dkl4Zc0Xd2OzWHtdHmQ297peY7BJYsUN5v0JOQWQzTMockmqrEtCnCY77SpIEBql7hEJRw1tE4vDajKmG7ItAZs7gkhOcRLdzXr0oSJMOkbYHqZddMzbgPSYD/BGf+De2ucOKPS2rk1Ca6affDIXxNs3bRgCBKfDynamwTyXmx/D4ej2ZXZ5BWlpx1Xt0RSTavMtfWMZdqq/HnSWK8Dz2ThUZUHKBo5tuooIyjZTMNt/HCPMLL+61PRRo8/HLVQhLIxEB4VqbwFVDDJg1TvQZtuF7cpW0poIKzPSOUcZe7Q+7oz9aFJF4zWza9FIvh0Np89p2zHsHYVuN2fxCrsQ80CHind0Q4khxGIWhTak5OIJHCkYoiCgZjolJpverr4R1bJbqYRAO/ZvW6AotEqikQKveRNNRmvstTKXt6AHkeoEng4wyDH07EImFljU5i4CuPlQqajovaiKYpw6f9CxKiF9uMN8RV2K99c/ABC62dpLfILPgz4qRTxY5PGG0G9iQ==
*/