//
// execution/start.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_START_HPP
#define BOOST_ASIO_EXECUTION_START_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/traits/start_member.hpp>
#include <boost/asio/traits/start_free.hpp>

#include <boost/asio/detail/push_options.hpp>

#if defined(GENERATING_DOCUMENTATION)

namespace boost {
namespace asio {
namespace execution {

/// A customisation point that notifies an operation state object to start
/// its associated operation.
/**
 * The name <tt>execution::start</tt> denotes a customisation point object.
 * The expression <tt>execution::start(R)</tt> for some subexpression
 * <tt>R</tt> is expression-equivalent to:
 *
 * @li <tt>R.start()</tt>, if that expression is valid.
 *
 * @li Otherwise, <tt>start(R)</tt>, if that expression is valid, with
 * overload resolution performed in a context that includes the declaration
 * <tt>void start();</tt> and that does not include a declaration of
 * <tt>execution::start</tt>.
 *
 * @li Otherwise, <tt>execution::start(R)</tt> is ill-formed.
 */
inline constexpr unspecified start = unspecified;

/// A type trait that determines whether a @c start expression is
/// well-formed.
/**
 * Class template @c can_start is a trait that is derived from
 * @c true_type if the expression <tt>execution::start(std::declval<R>(),
 * std::declval<E>())</tt> is well formed; otherwise @c false_type.
 */
template <typename R>
struct can_start :
  integral_constant<bool, automatically_determined>
{
};

} // namespace execution
} // namespace asio
} // namespace boost

#else // defined(GENERATING_DOCUMENTATION)

namespace boost_asio_execution_start_fn {

using boost::asio::decay;
using boost::asio::declval;
using boost::asio::enable_if;
using boost::asio::traits::start_free;
using boost::asio::traits::start_member;

void start();

enum overload_type
{
  call_member,
  call_free,
  ill_formed
};

template <typename R, typename = void, typename = void>
struct call_traits
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = ill_formed);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef void result_type;
};

template <typename R>
struct call_traits<R,
  typename enable_if<
    start_member<R>::is_valid
  >::type> :
  start_member<R>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_member);
};

template <typename R>
struct call_traits<R,
  typename enable_if<
    !start_member<R>::is_valid
  >::type,
  typename enable_if<
    start_free<R>::is_valid
  >::type> :
  start_free<R>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_free);
};

struct impl
{
#if defined(BOOST_ASIO_HAS_MOVE)
  template <typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<R>::overload == call_member,
    typename call_traits<R>::result_type
  >::type
  operator()(R&& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<R>::is_noexcept))
  {
    return BOOST_ASIO_MOVE_CAST(R)(r).start();
  }

  template <typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<R>::overload == call_free,
    typename call_traits<R>::result_type
  >::type
  operator()(R&& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<R>::is_noexcept))
  {
    return start(BOOST_ASIO_MOVE_CAST(R)(r));
  }
#else // defined(BOOST_ASIO_HAS_MOVE)
  template <typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<R&>::overload == call_member,
    typename call_traits<R&>::result_type
  >::type
  operator()(R& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<R&>::is_noexcept))
  {
    return r.start();
  }

  template <typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<const R&>::overload == call_member,
    typename call_traits<const R&>::result_type
  >::type
  operator()(const R& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<const R&>::is_noexcept))
  {
    return r.start();
  }

  template <typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<R&>::overload == call_free,
    typename call_traits<R&>::result_type
  >::type
  operator()(R& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<R&>::is_noexcept))
  {
    return start(r);
  }

  template <typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<const R&>::overload == call_free,
    typename call_traits<const R&>::result_type
  >::type
  operator()(const R& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<const R&>::is_noexcept))
  {
    return start(r);
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)
};

template <typename T = impl>
struct static_instance
{
  static const T instance;
};

template <typename T>
const T static_instance<T>::instance = {};

} // namespace boost_asio_execution_start_fn
namespace boost {
namespace asio {
namespace execution {
namespace {

static BOOST_ASIO_CONSTEXPR const boost_asio_execution_start_fn::impl&
  start = boost_asio_execution_start_fn::static_instance<>::instance;

} // namespace

template <typename R>
struct can_start :
  integral_constant<bool,
    boost_asio_execution_start_fn::call_traits<R>::overload !=
      boost_asio_execution_start_fn::ill_formed>
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename R>
constexpr bool can_start_v = can_start<R>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename R>
struct is_nothrow_start :
  integral_constant<bool,
    boost_asio_execution_start_fn::call_traits<R>::is_noexcept>
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename R>
constexpr bool is_nothrow_start_v
  = is_nothrow_start<R>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

} // namespace execution
} // namespace asio
} // namespace boost

#endif // defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_START_HPP

/* start.hpp
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
*/