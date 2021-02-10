/* Copyright 2003-2019 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_IS_FUNCTION_HPP
#define BOOST_MULTI_INDEX_DETAIL_IS_FUNCTION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/workaround.hpp>

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)||\
    BOOST_WORKAROUND(_LIBCPP_VERSION,<30700)||\
    BOOST_WORKAROUND(BOOST_LIBSTDCXX_VERSION,<40802)
/* libc++: std::is_function<void() const> fails,
 * https://bugs.llvm.org/show_bug.cgi?id=20084
 *
 * libstdc++-v3: std::is_function does not support ref-qualified function types,
 * https://github.com/gcc-mirror/gcc/commit/
 *   2fa630fb50ba29d8e891c52a75aaec261b07874e#
 *   diff-6547f965a8d66bf35a6388fcf404aaa3
 */

#include <boost/type_traits/is_function.hpp>

namespace boost{namespace multi_index{namespace detail{

template<typename T>
struct is_function:boost::is_function<T>{};

}}} /* namespace boost::multi_index::detail */

#else

#include <type_traits>

namespace boost{namespace multi_index{namespace detail{

template<typename T>
struct is_function:std::is_function<T>{};

}}} /* namespace boost::multi_index::detail */

#endif
#endif

/* is_function.hpp
Q1kJGj7Ui5g78WbQgx1Nv3WfnO9Cx689vf4sFDRwRc2NQ3daRqrv6BtBdusAxWkBJuVbAR6yLEMRe27zwoDPvB8Ko1U1VHMZQxuaU0WZv3TWIFhpTGPKoXQEMJc04q4nUYpM5Flx8FglRnlV3X6sOXrQ1Rg6I8MXdEV7Dde+eSqnLA254MazdAxP+8MP3X7Y7fcbq/4SAe38I9PLsmdFy6ygsLR5V+oSCP6p1JtqGg3dlU7Rd7wfXk7CT73Rh+G450On74oj49UgJsgIE73Nw1mve9IblQ7+U3PUGw/7nyiWA2ab9kX3y/FwMOgdT8Y+7D+FwlKTLoOTfm+8icn/4DE50hlG9J0o57sw3SR4NfdrileixnP+1u2ni75crzA/yJhJgs67Tnun/ZbXn1sXI1EOgduUVNu4fF7mQP8F6HylQt/ctN8U6q/DSYu/4a2AE8qr0JHe2dJnjuBbbNAJgE0prVCKNXdR5sZrlMTenIKDskeZkuQISindQH/lKCKkfM0yQ7j8YNG2F906bqm6EXdjEGcKMaTrytsgjjsuR2dlXJwoNPQhtpUd1h5r/wBQSwMECgAAAAgALWdKUi3uP9VNAwAARggAACMACQBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjE1
*/