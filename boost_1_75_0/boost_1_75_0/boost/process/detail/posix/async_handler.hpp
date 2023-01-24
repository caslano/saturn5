// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_POSIX_ASYNC_HANDLER_HPP_
#define BOOST_PROCESS_POSIX_ASYNC_HANDLER_HPP_

#include <boost/process/detail/posix/handler.hpp>
#include <type_traits>

namespace boost { namespace process { namespace detail { namespace posix {

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
iXU8B/rXn21mZNG7FeQ5nXf8beJElrUzo/r5429uXQbqiqe3biuPRGc9bd0kcFvUd8oXefkYca/PxhqrzpyfSfN8JNtwtiGnslyzeAMCN72NFvp2rbnTCZ4PDOw0MhFBY/j4ck1T6jOeRPjVb5Pb74kh70cuEaZMR+Q1odnytpH0vMuLND7OkqQBqzwYdtNH+rBCo98YUZWdBJjzWQMIXCQnTkzD17BwfUHmMhYqrY2yleW0AJ/KcOBf3zgl7PUO5bO+tzwQHdcu4DzJDfpJfbDjWyrNlSKE1daNXgCwxEd2YqPMWzzSXfFX6B/eqDgC3t1idn5Id3cI3NLRhP0+130ssrScoqJrYMXe8M2zHq08HK0qPfuJJf0IZYFQIjNRmpULXMFgzmtW0zH/uFx5VBWIEf2g/af7C0DNQjBIDQFBP/+/3F9U/5nkYvsn0DI3kXa0MzN3+XcfipO+lvfXzNO4j7aHmZ7c5WACIX/S5aqPboAo1ZWkDm0AQi0FJlGCS3V3skPDeuV2t60OIpoW7AIH5i8nuLLUsel5ZcUsSCX2cGUgM/5pSSIO0mMSRHhLcHZPkMR8qgT7WgCY31OLUceQqhkQjHaSD85znbkIzHvI9/Xo/Shdqv1aXhLskXOdN9aVdjxmsPb+Abj9ASSQQH/6smDJmNA6CcgKKJxXCSa4bFluNcV3afHmr4PSRqyCqoHQhNaC0oJ0vHvH
*/