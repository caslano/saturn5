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
loBGo9/obsD7uxUhJosk+NyaCNFeZLMoSV+KgcxkIka3wY1M8akhfpJu2By4i0CcyyTwwwqWjWd+KvCfKwI/ywIp4iS6Sty5yCLhyXkUplniZlJkMykWqXslRTSldU3hhiJNA+GHfua7gZ+6mR+FYuIGwaU7uRapzDI/vALiRQoyruUtVngiSxZpdummMiWaozmBTJNoDrj4epIeHompH0jeYJHyerWNG8eBP1nbAzROfSB1xcXQBiVEJaGVSeZPCZrYkakMM+kJb5EQPkKG3VNCBLm4lyB9NgdIq1LZ3a/s74pXp9ao86Yidk0BpMQGeBejURd0A+PnrCCkIRL5x8LHVqIfyxAgtPrVfo5ovwK8NNSJ4tvEv5plojapi6ODgx/B59HB0QH0IHmtdeN7MpxIMUii3+Uka0GhQSB4USqImeRGei0gI3xD6fmgz79csGBIwEQmJJFGiwRYaOTSD93kVkyjZJ42xNLPZiJK+He0yAjLPPKUuICjIdwEUpPJHOYAqcEciCIobuZmbAXTKAiiJYkSYvB8WpQSFlo3l9lLTdpha426lKSnyZpEHoBhCeAoc5XihHsZ3dCUFhEhwU8YZf5ENgABK4WuMkJT7txYowk7TgLXn8PeNQK2OsBEwApJBLmKeAK/pXsr
*/