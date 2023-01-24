//
// associated_executor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_ASSOCIATED_EXECUTOR_HPP
#define BOOST_ASIO_ASSOCIATED_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/is_executor.hpp>
#include <boost/asio/system_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename>
struct associated_executor_check
{
  typedef void type;
};

template <typename T, typename E, typename = void>
struct associated_executor_impl
{
  typedef E type;

  static type get(const T&, const E& e) BOOST_ASIO_NOEXCEPT
  {
    return e;
  }
};

template <typename T, typename E>
struct associated_executor_impl<T, E,
  typename associated_executor_check<typename T::executor_type>::type>
{
  typedef typename T::executor_type type;

  static type get(const T& t, const E&) BOOST_ASIO_NOEXCEPT
  {
    return t.get_executor();
  }
};

} // namespace detail

/// Traits type used to obtain the executor associated with an object.
/**
 * A program may specialise this traits type if the @c T template parameter in
 * the specialisation is a user-defined type. The template parameter @c
 * Executor shall be a type meeting the Executor requirements.
 *
 * Specialisations shall meet the following requirements, where @c t is a const
 * reference to an object of type @c T, and @c e is an object of type @c
 * Executor.
 *
 * @li Provide a nested typedef @c type that identifies a type meeting the
 * Executor requirements.
 *
 * @li Provide a noexcept static member function named @c get, callable as @c
 * get(t) and with return type @c type.
 *
 * @li Provide a noexcept static member function named @c get, callable as @c
 * get(t,e) and with return type @c type.
 */
template <typename T, typename Executor = system_executor>
struct associated_executor
{
  /// If @c T has a nested type @c executor_type, <tt>T::executor_type</tt>.
  /// Otherwise @c Executor.
#if defined(GENERATING_DOCUMENTATION)
  typedef see_below type;
#else // defined(GENERATING_DOCUMENTATION)
  typedef typename detail::associated_executor_impl<T, Executor>::type type;
#endif // defined(GENERATING_DOCUMENTATION)

  /// If @c T has a nested type @c executor_type, returns
  /// <tt>t.get_executor()</tt>. Otherwise returns @c ex.
  static type get(const T& t,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return detail::associated_executor_impl<T, Executor>::get(t, ex);
  }
};

/// Helper function to obtain an object's associated executor.
/**
 * @returns <tt>associated_executor<T>::get(t)</tt>
 */
template <typename T>
inline typename associated_executor<T>::type
get_associated_executor(const T& t) BOOST_ASIO_NOEXCEPT
{
  return associated_executor<T>::get(t);
}

/// Helper function to obtain an object's associated executor.
/**
 * @returns <tt>associated_executor<T, Executor>::get(t, ex)</tt>
 */
template <typename T, typename Executor>
inline typename associated_executor<T, Executor>::type
get_associated_executor(const T& t, const Executor& ex,
    typename enable_if<is_executor<
      Executor>::value>::type* = 0) BOOST_ASIO_NOEXCEPT
{
  return associated_executor<T, Executor>::get(t, ex);
}

/// Helper function to obtain an object's associated executor.
/**
 * @returns <tt>associated_executor<T, typename
 * ExecutionContext::executor_type>::get(t, ctx.get_executor())</tt>
 */
template <typename T, typename ExecutionContext>
inline typename associated_executor<T,
  typename ExecutionContext::executor_type>::type
get_associated_executor(const T& t, ExecutionContext& ctx,
    typename enable_if<is_convertible<ExecutionContext&,
      execution_context&>::value>::type* = 0) BOOST_ASIO_NOEXCEPT
{
  return associated_executor<T,
    typename ExecutionContext::executor_type>::get(t, ctx.get_executor());
}

#if defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)

template <typename T, typename Executor = system_executor>
using associated_executor_t = typename associated_executor<T, Executor>::type;

#endif // defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_ASSOCIATED_EXECUTOR_HPP

/* associated_executor.hpp
m7Dh3/wY+w9dCyJEaCpUr9TTR9ZgEuqJL5qfAgAwcFM0Ph/G++v2k8X2EqA0o2z35WcBbyRchrSLe7bhRbunoZm0CcmBohRma8O3iZbKuFKmixwPPwz+UFxlXGDxEP1ZArC3eM8eWJzCeHa+zdz4H/jbOwzwKoVQqM2t6NrcwzpK4DCsjCMRaIi1zNpybKtTdMIkJmSA1H6cZkzUobMYNF4RDzNRBDuwgJUxAeD+EtoOAwzN21Y3rBNmkMcRVQK53PbNLFCQT0ykC5swPhRV3sYAKvZRX8/+N2CU7AC3RuP2Sf32IjVuxdClM9denHWJTjvMZIqVgYoUNeJaWj4sgVIbI14c/cWgIg3rxVuhFjkWZAFgqQP9m3NjvIfrsTemb1B7C3iY0HFt6DzK1aHxeOCcGxE6Au5zoWnIKp1gGeEYuQN4uae+GdZOIhMqksfAE0/nAjxkF66eunaAG2ZYnIIhOgRA9XUxXLWpJYA3PVE5bmkUk+TiAZBSFV8mIvivRhBcKIQ+iujs+zTkXoOo9sFjrOkJDKFrgb0K3TbSbKUhFjuhNWEWIvRJbMZPp90fDZ+WXRnnR8B2wqSFMtXcr+9DtAt9Ngrjt9syYY/vPsYw/Y/k8Wc0HsVUvrKiY1QcHCsFxtPZP4dp2TlmWkwwLflDFK9pQvNIvk3NhhnRf2dG5qqzqIhDWOMURgOaQB4b7TraMRO+poLwJW22
*/