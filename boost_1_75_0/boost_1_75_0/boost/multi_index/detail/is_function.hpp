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
SXVUHokyAZRzquG6p8+JzOxvd9SP/WnUAAzsgEb/exnvHbU0g/dCMRKe+DWTd/dXv+u7OxVjvYkMWnsUO6qR0JuvFDm9rMAgC+bCOyX2cTWXRWDZz6LsCy6LxLJtomwBl1mx7GtRNofLorDsfVFWzGU2LHtRlN3DZW2w7AlRlstlMVg2UZRdz2XtsWykKEvmsg5Yli3KOnFZRyy7UpSZuKwTlvUQZb9aqMyBZW1EWS2XdcGyvyxctpbLumHZQVG2mMu6Y9k3ouxVLuuBZctFWRmX9cSyd0RZEZf1wrLnRFk+lyVi2QxR5uGyC7HsPlGWzmUXYdkIUZbEZUlY5hJl8VzWG8suE2WIdqDsEizrKsoULuuDZVZR9i2XJWMZkg9YVs5lfbFsnyhbxGWXYtkGUTafy1Kw7EtRVsJl/bDsDVFWyGWXYVlAlI3issuxbJook7jsCiwbL8r6c9mVWDZMlCVy2QVYdoMoi+WyVCzrK8rqTVR2MZY5RNlPXNYVy8yirIbLOmPZb0xsln7FZQlYtluULTQJR64dynpR9CJXi8eyz0TZE1yGvJvybyrzToL7aLx/hu/vWhEpEFIi0E1BRF5F7dljG+ecK11vrPRGw0qc/tnbRY8Zd/0A70lgVyOmRKaVC1s4xCOpAo+UTWKuKJfT0yOmINyReRtK2RhvlBzW8UYmxYgsJ46TY7PJe5CURmparlEdXSUM6exN
*/