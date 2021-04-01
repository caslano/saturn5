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
ZpbTNcjs5LgYgAe4miL79Ck69fZoVrK2+zac7DDik83m8Cq8voqMZYWEcY5W0PLn/CLaUm84FkNT6vMi3bYnw1IdvHpI0ATvaKuP+DvQ/Yk4igph8QuCnEYMWLP0/6DDZwOxcQ2vMrZKHnoBtCl8OjOUAhtP0whwVFxPGK0oQVoRD10/7FwBKxAh0N3Y4m1q1noKwxnJOB/4WdlYLCUcNKQLJC2SCHmq7wJ8yvxY6+bzGV0viB+02y5rgb7p88IJLiRLlxuuLdRmMhOcMCTTPWDUGhXgOy1dz0D8VOv643rg7V3jFHqcZwvlQnPZ7UyRMCu5SqTwdfDE3OuSOMTLq8rZ8SB0SH39FuIJskZ5e4nvnG6/LIjw7OOOd3qZpTarjpmPYtzEpACqcPPtrZXun3wVgBTYlXWRkUv6ZB65lUHkUHc/UWTTvKETMfkjDa7JvbBxKf8upsEZEVP6VlEZOWOgzH4GgFBUfW57bVGeiJlt0chtdUHSynahVGhc67UZZ++8NmK2D8H8Re15O/WEVhyDf0xd2VWMDoKFjSz+OyRzyGa/a//PvBhZsw==
*/