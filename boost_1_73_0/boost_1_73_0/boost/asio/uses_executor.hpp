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
LmL4vKD9cOADj2YJosAAZQYqBFFFwm9qKttCjebOo2mo4hrFzMcUQb+Uu96CB/mzlIi1WxirtqNNW3Vd9EtAmkwtmZwzPeT08nTFgqhwZHgyGmtSp8xZRy8pDCeYiaSJJXGRZB9ezz8ivGgnO5rAOoKqSTpigyYG6iGbiLXV9xEyiqXo/kJbzcmA5/1XJlyIpm0sM6wK1Pje2f9isMu7//nTkNIc//7u3bqulTXOVD7070zkwgn5vFuCfSjWl5+rL0Oaxj8zCtX2e1JhXYbhgR+gdwAJs7w5GxZu/DZj/xOTFJdDoNcwlm7oJw6czw439CZzT8jIRenpy4zdKrMg0u+hr5ngkfAK9+NW6e9hE6zAcrzcvsJJj1EwKXfmNZvd5lfArDbEJLyPd48i3BNI8Qghq6nLWwNt4s60fmYEYCBELYXgnzzT94eOxynEIvx4JoKzLydrsIjEHeQMxN0y3zXkOF1RR4zGVtZRVTDb+XHEHsidEH/9wgkD8RmhgYQlmf4lj4thh+xBpnlHqVSmlFtFKbENNmTZ3uSIQ56G28f7EAEDSk7BBwQvIY/QG1Q4QiRbE8Sn+Z3lOOtMLtgL2AsK+MiLQjPs++IfaR8Y/KQglxXFdNrOSjPy8pNkazEQQNkoJ+afXJOv0+95
*/