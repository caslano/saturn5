//
// uses_executor.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_USES_EXECUTOR_HPP
#define BOOST_ASIO_USES_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// A special type, similar to std::nothrow_t, used to disambiguate
/// constructors that accept executor arguments.
/**
 * The executor_arg_t struct is an empty structure type used as a unique type
 * to disambiguate constructor and function overloading. Specifically, some
 * types have constructors with executor_arg_t as the first argument,
 * immediately followed by an argument of a type that satisfies the Executor
 * type requirements.
 */
struct executor_arg_t
{
  /// Constructor.
  BOOST_ASIO_CONSTEXPR executor_arg_t() BOOST_ASIO_NOEXCEPT
  {
  }
};

/// A special value, similar to std::nothrow, used to disambiguate constructors
/// that accept executor arguments.
/**
 * See boost::asio::executor_arg_t and boost::asio::uses_executor
 * for more information.
 */
#if defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
constexpr executor_arg_t executor_arg;
#elif defined(BOOST_ASIO_MSVC)
__declspec(selectany) executor_arg_t executor_arg;
#endif

/// The uses_executor trait detects whether a type T has an associated executor
/// that is convertible from type Executor.
/**
 * Meets the BinaryTypeTrait requirements. The Asio library provides a
 * definition that is derived from false_type. A program may specialize this
 * template to derive from true_type for a user-defined type T that can be
 * constructed with an executor, where the first argument of a constructor has
 * type executor_arg_t and the second argument is convertible from type
 * Executor.
 */
template <typename T, typename Executor>
struct uses_executor : false_type {};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_USES_EXECUTOR_HPP

/* uses_executor.hpp
Mlc0kq1b6CLZt4oukqHS3EZESqT7tzDzdnOuFAa/c8UoeHTvDoMF8/MfWTDbFWLvah0Ernx6i3wOjkqeONJji2pHJwFoLuc831q0s93n+i2PI2deUUt7yqW3u+jNzS8tZXK+BhS2Sl+vgtJ0b5apKMeUW27tPnFBmdXMObyZBhueT/JmGjEcewPTwa5wysa1n2yE3p1SI6n6tRVdlXiaBih2vhJBNEybcNyICcAj3CsNHJ/lzaqdDdbgZmYYXk+TSFlrbWgDb2LvrjZvt/pdARv8acJ/zuI/p/GfX/Gfkzay5GUUhQOow5xtr7S8LIedU8VyJYPWQhpfVlBALSvZYlp3clqIS04WBBSlu9QW5JsVzDWRBTD9ZHdiciK71/sZzMVsu43ZSZLfHQgIsxhSXGFAqkvxrszl4zH75BC3vyd/NQCrgWER2w5aSGZQgMksWojbtr7vyNSXkcp81ZIHP+IuLqDHYOmDGOH1FKPfiryMT5kGr6eCPj5FH41eTxV9LKCPJslTS39YvB5CvWCZsdQTaCO7DuLUxwN2IqVyekCW+bz6r2Ba0wW4yaK4cbcEhATy6ksqcoqXU+TIo3nkJRwNmLy1XgoukoxsIN5wAXKGIXJ6InL6kVlqj75/kKkvqch4g1z7EkXGixdFBt4apUHGY+dDkLHs/CWQ8Y8DMjLMhcn0nkymb5qXd4ELDZ1gzLaMig+F/wqdTNvc
*/