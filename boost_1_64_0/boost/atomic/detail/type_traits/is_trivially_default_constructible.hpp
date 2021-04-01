/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/is_trivially_default_constructible.hpp
 *
 * This header defines \c is_trivially_default_constructible type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <type_traits>
#else
#include <boost/type_traits/has_trivial_constructor.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
using std::is_trivially_default_constructible;
#elif !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
template< typename T >
using is_trivially_default_constructible = boost::has_trivial_constructor< T >;
#else
template< typename T >
struct is_trivially_default_constructible : public boost::has_trivial_constructor< T > {};
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_HPP_INCLUDED_

/* is_trivially_default_constructible.hpp
LFBQ3bkvCoo+RCmMZR6HCsHQtcJkhuYsYyHqGF4D0DG9DxmG4gZw3iXUBauSrl/b61d7o0M5k1mcm4DsjYvhpKZFasFCWdI9sMWT0vMI0d8me+BE6CbGRjU+E4/WDcGP0sIqKcJ0clgowKMlIc9BYtS6dmqTfMOQD4RViadLpfnHfctPUGX1noX8T9OXgY+Ez+L1WD/aJQg8Qs6D/S23+GMSNX3WZbi8rWn22wjmsKMkKS1mYaQ/Qmv49TIQjm31p3r6wrv9Xs89hcalTE5IDcPUr8B/I6VYDwEWXKsFeJN4WU0KmAh983C3CpyyFcb+0DfCBz76d8SSdIqRse7CsasMqA60uVr/CsimaLY/Mbri4X58E5i8lNL+/7UbD64l7Wdd3Lr4aJGK8Cz73PVrCKlhObv2E6ifvSoW0ucfVAa3bz/lKLfhS77z8+f0ZaWsbcrX3BRiwANWakBn2DAALszrU6iIaBkHb8JG3XqDKBpcYnmLagwxD4W7jTUzECXGdhXwHN137i6en7Dz+56ZVG+72vQdnif1wD0FL2ErH3I/bPl6wtY49lVF0A==
*/