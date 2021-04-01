// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_WINDOWS_ASYNC_HANDLER_HPP_
#define BOOST_PROCESS_WINDOWS_ASYNC_HANDLER_HPP_

#include <boost/process/detail/windows/handler.hpp>
#include <type_traits>

namespace boost { namespace process { namespace detail { namespace windows {

struct require_io_context {};

struct async_handler : handler_base_ext, require_io_context
{
};

template<typename T>
struct is_async_handler :  std::is_base_of<async_handler, T> {};
template<typename T>
struct is_async_handler<T&> :  std::is_base_of<async_handler, T> {};
template<typename T>
struct is_async_handler<const T&> :  std::is_base_of<async_handler, T> {};

template<typename T>
struct does_require_io_context : std::is_base_of<require_io_context, T> {};

template<typename T>
struct does_require_io_context<T&> : std::is_base_of<require_io_context, T> {};

template<typename T>
struct does_require_io_context<const T&> : std::is_base_of<require_io_context, T> {};


}}}}

#endif /* BOOST_PROCESS_WINDOWS_ASYNC_HANDLER_HPP_ */

/* async_handler.hpp
ZZrjGRr4oX72iVIwKR4hKwIFanVfhpL9a4RJrvuWxehNgI8roiF9A9ubt2dIzij2VDTsLtHX3Yp7rqZEXhocP10xzR5jjsHQ4d0ODq3DxrGc0ZnBCZk+08zCuzo7VKi6xj6a4GyeT1V8AAJ49hvz4HHOJwOyHVj2M2dSG3bbW562cnVfy6lbNerlNy38ebpjFBNY1H0at/H95HrtRX0VnlYAtT1+q7R08q6dy9ZbpzIU53nl5LrIuqIT6/nv86JCh9LT7YSSLyEW+oNKnZilWeo5ELKOA/L0qa95ICuOOxwQQKK+ra5bibeG5kmHMbXRgiHQv5IqqSv8YAVh0gm/xUgI4JPiWKjUT3PilK2c+wNa87AyKZFHyEcxpyfGuvfdT/jz+u1UE1Kxz9zkaAwFN1r2DSo3w5KvUR3FBkGyPKJaGlJZ+VZFk3JDu60Te3UizgXgrGF+FNrZRwbk6mjU7Ic4du4cYmxgQL/YMyhmNnVAhD50iBcsaKq4QKz7IqXEpH/vfKBmmhtrWUauDppRBChzTcsPcsEDMI8jFd8/dqNOwHB/FYHQNmaRSg==
*/