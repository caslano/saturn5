//
// execution/schedule.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_SCHEDULE_HPP
#define BOOST_ASIO_EXECUTION_SCHEDULE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution/executor.hpp>
#include <boost/asio/traits/schedule_member.hpp>
#include <boost/asio/traits/schedule_free.hpp>

#include <boost/asio/detail/push_options.hpp>

#if defined(GENERATING_DOCUMENTATION)

namespace boost {
namespace asio {
namespace execution {

/// A customisation point that is used to obtain a sender from a scheduler.
/**
 * The name <tt>execution::schedule</tt> denotes a customisation point object.
 * For some subexpression <tt>s</tt>, let <tt>S</tt> be a type such that
 * <tt>decltype((s))</tt> is <tt>S</tt>. The expression
 * <tt>execution::schedule(s)</tt> is expression-equivalent to:
 *
 * @li <tt>s.schedule()</tt>, if that expression is valid and its type models
 *   <tt>sender</tt>.
 *
 * @li Otherwise, <tt>schedule(s)</tt>, if that expression is valid and its
 *   type models <tt>sender</tt> with overload resolution performed in a context
 *   that includes the declaration <tt>void schedule();</tt> and that does not
 *   include a declaration of <tt>execution::schedule</tt>.
 *
 * @li Otherwise, <tt>S</tt> if <tt>S</tt> satisfies <tt>executor</tt>.
 *
 * @li Otherwise, <tt>execution::schedule(s)</tt> is ill-formed.
 */
inline constexpr unspecified schedule = unspecified;

/// A type trait that determines whether a @c schedule expression is
/// well-formed.
/**
 * Class template @c can_schedule is a trait that is derived from @c true_type
 * if the expression <tt>execution::schedule(std::declval<S>())</tt> is well
 * formed; otherwise @c false_type.
 */
template <typename S>
struct can_schedule :
  integral_constant<bool, automatically_determined>
{
};

} // namespace execution
} // namespace asio
} // namespace boost

#else // defined(GENERATING_DOCUMENTATION)

namespace boost_asio_execution_schedule_fn {

using boost::asio::decay;
using boost::asio::declval;
using boost::asio::enable_if;
using boost::asio::execution::is_executor;
using boost::asio::traits::schedule_free;
using boost::asio::traits::schedule_member;

void schedule();

enum overload_type
{
  identity,
  call_member,
  call_free,
  ill_formed
};

template <typename S, typename = void, typename = void, typename = void>
struct call_traits
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = ill_formed);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef void result_type;
};

template <typename S>
struct call_traits<S,
  typename enable_if<
    schedule_member<S>::is_valid
  >::type> :
  schedule_member<S>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_member);
};

template <typename S>
struct call_traits<S,
  typename enable_if<
    !schedule_member<S>::is_valid
  >::type,
  typename enable_if<
    schedule_free<S>::is_valid
  >::type> :
  schedule_free<S>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_free);
};

template <typename S>
struct call_traits<S,
  typename enable_if<
    !schedule_member<S>::is_valid
  >::type,
  typename enable_if<
    !schedule_free<S>::is_valid
  >::type,
  typename enable_if<
    is_executor<typename decay<S>::type>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = identity);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

#if defined(BOOST_ASIO_HAS_MOVE)
  typedef BOOST_ASIO_MOVE_ARG(S) result_type;
#else // defined(BOOST_ASIO_HAS_MOVE)
  typedef BOOST_ASIO_MOVE_ARG(typename decay<S>::type) result_type;
#endif // defined(BOOST_ASIO_HAS_MOVE)
};

struct impl
{
  template <typename S>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<S>::overload == identity,
    typename call_traits<S>::result_type
  >::type
  operator()(BOOST_ASIO_MOVE_ARG(S) s) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<S>::is_noexcept))
  {
    return BOOST_ASIO_MOVE_CAST(S)(s);
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  template <typename S>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<S>::overload == call_member,
    typename call_traits<S>::result_type
  >::type
  operator()(S&& s) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<S>::is_noexcept))
  {
    return BOOST_ASIO_MOVE_CAST(S)(s).schedule();
  }

  template <typename S>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<S>::overload == call_free,
    typename call_traits<S>::result_type
  >::type
  operator()(S&& s) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<S>::is_noexcept))
  {
    return schedule(BOOST_ASIO_MOVE_CAST(S)(s));
  }
#else // defined(BOOST_ASIO_HAS_MOVE)
  template <typename S>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<S&>::overload == call_member,
    typename call_traits<S&>::result_type
  >::type
  operator()(S& s) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<S&>::is_noexcept))
  {
    return s.schedule();
  }

  template <typename S>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<const S&>::overload == call_member,
    typename call_traits<const S&>::result_type
  >::type
  operator()(const S& s) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<const S&>::is_noexcept))
  {
    return s.schedule();
  }

  template <typename S>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<S&>::overload == call_free,
    typename call_traits<S&>::result_type
  >::type
  operator()(S& s) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<S&>::is_noexcept))
  {
    return schedule(s);
  }

  template <typename S>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<const S&>::overload == call_free,
    typename call_traits<const S&>::result_type
  >::type
  operator()(const S& s) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<const S&>::is_noexcept))
  {
    return schedule(s);
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

} // namespace boost_asio_execution_schedule_fn
namespace boost {
namespace asio {
namespace execution {
namespace {

static BOOST_ASIO_CONSTEXPR const boost_asio_execution_schedule_fn::impl&
  schedule = boost_asio_execution_schedule_fn::static_instance<>::instance;

} // namespace

template <typename S>
struct can_schedule :
  integral_constant<bool,
    boost_asio_execution_schedule_fn::call_traits<S>::overload !=
      boost_asio_execution_schedule_fn::ill_formed>
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename S>
constexpr bool can_schedule_v = can_schedule<S>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename S>
struct is_nothrow_schedule :
  integral_constant<bool,
    boost_asio_execution_schedule_fn::call_traits<S>::is_noexcept>
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename S>
constexpr bool is_nothrow_schedule_v
  = is_nothrow_schedule<S>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

} // namespace execution
} // namespace asio
} // namespace boost

#endif // defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_SCHEDULE_HPP

/* schedule.hpp
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
*/