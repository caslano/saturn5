/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/is_function.hpp
 *
 * This header defines \c is_function type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_FUNCTION_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_FUNCTION_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
#include <type_traits>
#else
#include <boost/type_traits/is_function.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
using std::is_function;
#else
using boost::is_function;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_FUNCTION_HPP_INCLUDED_

/* is_function.hpp
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
*/