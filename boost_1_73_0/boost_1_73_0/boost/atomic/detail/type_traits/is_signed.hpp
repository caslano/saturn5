/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/is_signed.hpp
 *
 * This header defines \c is_signed type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_SIGNED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_SIGNED_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
// Some versions of libstdc++ don't consider __int128 an integral type. Use Boost.TypeTraits because of that.
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_INT128)
#include <type_traits>
#else
#include <boost/type_traits/is_signed.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_INT128)
using std::is_signed;
#else
using boost::is_signed;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_SIGNED_HPP_INCLUDED_

/* is_signed.hpp
b7fPKsFtnwtmbjrbPhVdkjLT7ZMySe6ZuInvp3H7jKrst89drksznyCDwUQlpaJlQkkU0oPJDLnKLvc6HG5H/PLb63+h5K/yl5eqC4JS9Cr9Naw2aEI048MjGhH5T1Nkviu4zyByGBnexG6aFnBNpIw3fhKFlGqIGxd1zSXAlzDMmSr/Q1UNEyokSTeofaqMihodhGoZJV6OnTKpVQowEmOQaaihPIrBnaw34XlTdxFkAiYFkHw9fMxcjvV+aC7/YyHTbHW1X7APakOo2WDtYtjNMzduJyTszPRVw3Jv5PNLxdC2PCfHPUeJmt3GMkfeFOc40gQPEU7PzVyKEPKzeGm2cPYzLIRi53ETtCe3aicsMGG8m0kqmjlPD63W1LiTiYwzoknRY1Kj5liJObO52BV1TML2TQrABwkMo1CalKRpKRnulvXZ3QRJkdpTkpNujLft9v7IblPzZBZ5DSFbVy0lkPapc/q+M+J9PacgCIGFN+pddLuVu2NuLlVa+8r22dzj9LZFvwu7/viRrUibimhC6ZcRODIp1btVDK1uMGuKeGOSzDyXFTfTdNfrg+STgquWf1jDvkOEU1nm3kS+J2J/cn1LvcAY5oxiw02oc5DyCb2cIVSDAf8qVM1EXhpHfki9TUIhpotQWWw+
*/