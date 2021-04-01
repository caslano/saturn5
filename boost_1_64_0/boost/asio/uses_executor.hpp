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
aiXnAson+qceHpZLCQSn7l8115a4n1AuhQRP3ryLaswG2iwi+wqdi1n6sYaZGFjg6aZ7il2ZzFgPuhm2TDoTDr3MTl9EAgdqK0QgOpMgo81qpwYkkc/2kJkroeUpWqSIGzqu+df1BmTJ0MWvGyvZpzotNPZkdPu/oqMA1II66NOroboukA3FFW0lavx+IHqFgJ8N/HNsgaserLcZF30jIppkEWt1aRbUBJPAYCQylK7Jb7KcNvYNVUJ/5UqBKEAOSvGEKCwjx5LwKCw6kyRG8H4GFjsoWNIZNGpuwX3jOnL3L0DYYlonCk2EgdSeT1eKoCQTW7ioRQsSSOOi/EGH3yG7nTk8tY7KH17YaI5tAn13XWq13Y5dj46B7oxf3lhPo4mvBMQje9OcDv9xMb5onYy6zHStVgihYbndx3pyGN+CBNAAWqu1JLQSD6IWnmueo8vI09Z/euGcFJagMKwkBouX8jP9gLF1ZHkIATmDF091ZvNzcOzGZixLQPWR9l+kUBP6qZvA90pMncoYFbQ3IHl6JMiEA0ft/2g0Avy8ES/SkAVsKnmyROMaMg==
*/