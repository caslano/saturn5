//
// handler_continuation_hook.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_HANDLER_CONTINUATION_HOOK_HPP
#define BOOST_ASIO_HANDLER_CONTINUATION_HOOK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Default continuation function for handlers.
/**
 * Asynchronous operations may represent a continuation of the asynchronous
 * control flow associated with the current handler. The implementation can use
 * this knowledge to optimise scheduling of the handler.
 *
 * Implement asio_handler_is_continuation for your own handlers to indicate
 * when a handler represents a continuation.
 *
 * The default implementation of the continuation hook returns <tt>false</tt>.
 *
 * @par Example
 * @code
 * class my_handler;
 *
 * bool asio_handler_is_continuation(my_handler* context)
 * {
 *   return true;
 * }
 * @endcode
 */
inline bool asio_handler_is_continuation(...)
{
  return false;
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_HANDLER_CONTINUATION_HOOK_HPP

/* handler_continuation_hook.hpp
WrSu8aWnGgyhAj4UXmNqHt3dI5Z+v3jm7AhwvTg98ApyNRvDMzRam/anO2edhP8l3ygAaKM56OBHOzs4Q0gy387SByfyNABbgM9zDvHbDXtDpJt9GGPxAhIk0xDgy2NlYWpjL7LDgeaFKY0w5dW0SI64iggegVE8RLUEBRKW/n8YGgtpz2CzJ+xK0Ri/eGK2HNkZhz6oJn9YQVuApw3LDzgIAbf2oU4X0Fo8icN/owlEUplnWNsMyYYiuzt3hv2qsyw1C4HdWQba4rGLGOvq9W3w8epUfPJrDUSLw60jrwHPlkhYoHJ9hCo/e8BC4avpqZWAVY948ytV5vr/m3ON4KsSzLqRuSHpxzWYEvLGlDnHpCcfi8YmZJGo46sGQpghIhZ1XDgfhqN7gYi77Om5cGeRpEk99hZePTKaGiHjyTskgRcsiI71s42Y+G6eQzcxx4YLGDp/y4rB8lHR/RjadPvCMYhDwhFcqaxYsNIvGh0wolYdorc3dBVqPu9rVApytNfANblGaMxtM12RKy9wC8EWb+BPyrINVX8khpJmIhticl4ZOdii6+fNuA==
*/