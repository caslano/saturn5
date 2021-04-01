/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/is_iec559.hpp
 *
 * This header defines \c is_iec559 type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_IEC559_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_IEC559_HPP_INCLUDED_

#include <limits>
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename T >
struct is_iec559
{
    static BOOST_CONSTEXPR_OR_CONST bool value = !!std::numeric_limits< T >::is_iec559;
};

#if defined(BOOST_HAS_FLOAT128)
// libstdc++ does not specialize numeric_limits for __float128
template< >
struct is_iec559< boost::float128_type >
{
    static BOOST_CONSTEXPR_OR_CONST bool value = true;
};
#endif // defined(BOOST_HAS_FLOAT128)

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_IEC559_HPP_INCLUDED_

/* is_iec559.hpp
+vxn0oGt4hHh3aF6EtxSxKI77rU5LU2/DY1wR7Y+4F9Pgik6d21bWA+ZML6n0jpR7V8X8MgeP0P752Q5FNmld+MiAPddhm02M+GGjglJvLPsbMiv9pPgatJkM2DgA+TxnJ1NUQrsautuiRDHM3m70QCoSZJgc3JdGHghCXiedlGfmJHXaEl0Er3OtjPRIB4OGMLx3OJ7l3ZnQQqK4uWNCBHrNEOUSPpAoYK0Ogzxwmr0j1rW9TibxCi044x9DnXuaIzSwpb6AUR5FLgl//nkyETRbHZCdtbwpfTqHFW+5ty98CCEF834csaWD+1AHnis4Ax/kphIWb+xlOXvAh64PSDuqFUtzeWHebxUHs4wIVheMaCt5cWoFa8MTG5q7yhR+efKSmR+erWG4BF4aj8DRpQXZJt5+yXOBXntnAELo4R33XXoWGHe/FzXuy1NZLUwwmxOEyDX+5fuJ3gwJOOo8+vAfODc+JNLCicBkrhGz4GEypjrrpE3u85iCJ5DxUV2LPXEMqVTQDV0W+d6cch5XXoiN/9c8J8UZ/IA0qSrhyPqObh1LQhog6ayXQ==
*/