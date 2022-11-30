//
// execution/set_done.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_SET_DONE_HPP
#define BOOST_ASIO_EXECUTION_SET_DONE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/traits/set_done_member.hpp>
#include <boost/asio/traits/set_done_free.hpp>

#include <boost/asio/detail/push_options.hpp>

#if defined(GENERATING_DOCUMENTATION)

namespace boost {
namespace asio {
namespace execution {

/// A customisation point that delivers a done notification to a receiver.
/**
 * The name <tt>execution::set_done</tt> denotes a customisation point object.
 * The expression <tt>execution::set_done(R)</tt> for some subexpression
 * <tt>R</tt> is expression-equivalent to:
 *
 * @li <tt>R.set_done()</tt>, if that expression is valid. If the function
 *   selected does not signal the receiver <tt>R</tt>'s done channel, the
 *   program is ill-formed with no diagnostic required.
 *
 * @li Otherwise, <tt>set_done(R)</tt>, if that expression is valid, with
 * overload resolution performed in a context that includes the declaration
 * <tt>void set_done();</tt> and that does not include a declaration of
 * <tt>execution::set_done</tt>. If the function selected by overload
 * resolution does not signal the receiver <tt>R</tt>'s done channel, the
 * program is ill-formed with no diagnostic required.
 *
 * @li Otherwise, <tt>execution::set_done(R)</tt> is ill-formed.
 */
inline constexpr unspecified set_done = unspecified;

/// A type trait that determines whether a @c set_done expression is
/// well-formed.
/**
 * Class template @c can_set_done is a trait that is derived from
 * @c true_type if the expression <tt>execution::set_done(std::declval<R>(),
 * std::declval<E>())</tt> is well formed; otherwise @c false_type.
 */
template <typename R>
struct can_set_done :
  integral_constant<bool, automatically_determined>
{
};

} // namespace execution
} // namespace asio
} // namespace boost

#else // defined(GENERATING_DOCUMENTATION)

namespace boost_asio_execution_set_done_fn {

using boost::asio::decay;
using boost::asio::declval;
using boost::asio::enable_if;
using boost::asio::traits::set_done_free;
using boost::asio::traits::set_done_member;

void set_done();

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
    set_done_member<R>::is_valid
  >::type> :
  set_done_member<R>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_member);
};

template <typename R>
struct call_traits<R,
  typename enable_if<
    !set_done_member<R>::is_valid
  >::type,
  typename enable_if<
    set_done_free<R>::is_valid
  >::type> :
  set_done_free<R>
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
    return BOOST_ASIO_MOVE_CAST(R)(r).set_done();
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
    return set_done(BOOST_ASIO_MOVE_CAST(R)(r));
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
    return r.set_done();
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
    return r.set_done();
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
    return set_done(r);
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
    return set_done(r);
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

} // namespace boost_asio_execution_set_done_fn
namespace boost {
namespace asio {
namespace execution {
namespace {

static BOOST_ASIO_CONSTEXPR const boost_asio_execution_set_done_fn::impl&
  set_done = boost_asio_execution_set_done_fn::static_instance<>::instance;

} // namespace

template <typename R>
struct can_set_done :
  integral_constant<bool,
    boost_asio_execution_set_done_fn::call_traits<R>::overload !=
      boost_asio_execution_set_done_fn::ill_formed>
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename R>
constexpr bool can_set_done_v = can_set_done<R>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename R>
struct is_nothrow_set_done :
  integral_constant<bool,
    boost_asio_execution_set_done_fn::call_traits<R>::is_noexcept>
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename R>
constexpr bool is_nothrow_set_done_v
  = is_nothrow_set_done<R>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

} // namespace execution
} // namespace asio
} // namespace boost

#endif // defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_SET_DONE_HPP

/* set_done.hpp
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
*/