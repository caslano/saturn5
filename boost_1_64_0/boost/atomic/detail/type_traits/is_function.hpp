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
oQsipDSzMDKb7fXDuJIhumHix8FuJX9MzASYiGF7tUOV6F0ZzEExBytZvb/p6cZed3pISqb7+lMR72Iuy67p3G9q0QfC1fULfeXvZcUyzhLGQkn26K1QzUKHQxQv0juNmMI4/DHN+O3RE8KLaT10bPBLfWvpnKI55qd9zdIKXLzd+IrVDNoQFwGb4Q2ryKL/Tf3EU1Rl/nog1mJ6QBVryIEG2wqZ0A8G5AUEbyXtPx6NO60w3xGlcjAKKrSIaZz+PhyIjYiMg4qkuEOjZtHjaV09U/X5xTgpmYpUKpQD4N23eDMoiJWeJhoooZEqIUKRby5O+Yp2xnIUS9A617arK+yDYA93kL6NU6KSBkn6Fjs31kYRlDftoKC3eM7UIEwL2PjS5qCXNoIU27ojuKaBNCr211lGNza8lGWgT0IDu9nyJrN3vroolL+NC2Ur4uAKTi32j09cpPKddEq14hwsrrRLFPdbVTte6uR4rzF/PNK9XTzs1HtdGQEne5ZNY7B8DI5drGfdwfZVH6BPJsedPDJpc8W05QxjciPWmyJOKgc9TSAni/kdm97i4Q==
*/