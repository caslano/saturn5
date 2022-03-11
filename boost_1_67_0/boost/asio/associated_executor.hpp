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
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
*/