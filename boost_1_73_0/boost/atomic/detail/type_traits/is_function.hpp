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
Tnl+ZxK6jQ7GL/V3DonmfB7c1iwOCn+5IbMSgqzrtuqLg/rzGQypRB2EI/EvOS+o+bIwitsYHk5uKBI7IPc1p3nPk3n1TfjP5sEs4hmjtlYVfbWH7AENzr5lcaHqTacziPo86QK2KA9VUeYK9MVFblSjCcOq84L/QzcKC+rBnCO7KYILkpRXnemuA2ManR4/UubvfIxbul3S/BtVHTjXr7oKwipSHo7dm4pDEcaVzkBh0bmT
*/