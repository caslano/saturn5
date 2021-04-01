/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/integral_constant.hpp
 *
 * This header defines \c integral_constant wrapper
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
#include <type_traits>
#else
#include <boost/type_traits/integral_constant.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
using std::integral_constant;
using std::true_type;
using std::false_type;
#else
using boost::integral_constant;
using boost::true_type;
using boost::false_type;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP_INCLUDED_

/* integral_constant.hpp
6n9UQhjbIpwcIUw/7v1ocK8oE7DfsLzJO5VvCXrI98NaBtzDFcuEuz13WzuLCNcUfbiyDWQh2tHyxQ+C6njNRAaZxqMxPYqcBqbHLrLk8KQLuPnMfwjgKMOsr9vG9y+rqzhQNKdPJf59R4SyAQ4AmoPqru4O7QEe1Iuvu6JznlAsbq8PY5rJrUl/1hU4RsVmRvfbPjaMdvPYgNKXRRFG0kvF5sXnjnWqmGgWx3h6W6F24zd+UKFiJDbuHmpaP8CHoiVxXu6TbppbxJGFpN8VuAILBMvLQvbE5vwNC98ArIn9NKdyV+wN3PxcvHFBScZLWynb49/zirWVuVDgdn6+1Oa1pdP+gXlUsnzsssOpt8SmScpmxa5Q6/8AkSPdarn9w4WMbFoY5MhftTG3aC397idWhUSn7KMXQtdeEU9q3dIDa91ZCQ6/PIlDkPRfcZjDm4cWhCvqdUWWUSMViXDKWDhAdT2/fyqMoZ68RZmOVMXlDpz8YQiADtFKOORoaPzNvdJQ1deL5A55MyzGukom3Hd2A2dIiWJKv+kXuHHkvwosqOl4mvQyYQ3aMA==
*/