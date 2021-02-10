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
k9UZi3/+sz0C8M6OaPdO8f9PhMr6OBhaoxGW9ofCPh90bXwE2mG7N7atUUPYvU734tTuvW2Ik4ux6PXHomuf22OAjfsN2o3QbK4U/TNxbg077/C1fWJ37fEn3vfMHvewoTjDfm0xaA/Hduei2x4SlsHFcNAfWYK4OrVHnW7bPrdOIUe7h42F9d7qjcXoXbvbvZ/LPmOyxyPR6ffGQxtE94cjcWKB7PZJ11Ib9z5hgyHgicHyUwdCBLldTo1GA6tj4zNkZIG99vBTg4QEtCPrvy8Ah0lx2j5vvwW3tVU50fp1UYHCzsXQOicmIJzRxclobI8vxpZ42++fjgj3yBq+tzvW6JjWd/sjluLFyGpgn3GbtwcWiHB0TJ9PLkY2C9Puja3h8GIwtvs99rB3/Q+QFohtX5BuSfD9HrMNwfWHnwgvyYP10hAf3lkYH5KcWWptiINFAAF2xiYkdoU8xwa/ome97dpvrV7Hotk+Ifpgjyymoz20RwRjq80/tLHzBbNPCgRt6qNhzg1Ws7DPRPv0PdCcEhoND+MY2dqWWIKdd1oBFEzF62/wk3vYvx+evjo23b//l8albxSUHohISlwo3/6iEYlXaeb5UWv2ZnUo8C/Xx6jaXB2jEn2f/lkd1tLZ//zi4G83P94/59xM
*/