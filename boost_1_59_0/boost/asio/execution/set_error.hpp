//
// execution/set_error.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_SET_ERROR_HPP
#define BOOST_ASIO_EXECUTION_SET_ERROR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/traits/set_error_member.hpp>
#include <boost/asio/traits/set_error_free.hpp>

#include <boost/asio/detail/push_options.hpp>

#if defined(GENERATING_DOCUMENTATION)

namespace boost {
namespace asio {
namespace execution {

/// A customisation point that delivers an error notification to a receiver.
/**
 * The name <tt>execution::set_error</tt> denotes a customisation point object.
 * The expression <tt>execution::set_error(R, E)</tt> for some subexpressions
 * <tt>R</tt> and <tt>E</tt> are expression-equivalent to:
 *
 * @li <tt>R.set_error(E)</tt>, if that expression is valid. If the function
 *   selected does not send the error <tt>E</tt> to the receiver <tt>R</tt>'s
 *   error channel, the program is ill-formed with no diagnostic required.
 *
 * @li Otherwise, <tt>set_error(R, E)</tt>, if that expression is valid, with
 *   overload resolution performed in a context that includes the declaration
 *   <tt>void set_error();</tt> and that does not include a declaration of
 *   <tt>execution::set_error</tt>. If the function selected by overload
 *   resolution does not send the error <tt>E</tt> to the receiver <tt>R</tt>'s
 *   error channel, the program is ill-formed with no diagnostic required.
 *
 * @li Otherwise, <tt>execution::set_error(R, E)</tt> is ill-formed.
 */
inline constexpr unspecified set_error = unspecified;

/// A type trait that determines whether a @c set_error expression is
/// well-formed.
/**
 * Class template @c can_set_error is a trait that is derived from
 * @c true_type if the expression <tt>execution::set_error(std::declval<R>(),
 * std::declval<E>())</tt> is well formed; otherwise @c false_type.
 */
template <typename R, typename E>
struct can_set_error :
  integral_constant<bool, automatically_determined>
{
};

} // namespace execution
} // namespace asio
} // namespace boost

#else // defined(GENERATING_DOCUMENTATION)

namespace boost_asio_execution_set_error_fn {

using boost::asio::decay;
using boost::asio::declval;
using boost::asio::enable_if;
using boost::asio::traits::set_error_free;
using boost::asio::traits::set_error_member;

void set_error();

enum overload_type
{
  call_member,
  call_free,
  ill_formed
};

template <typename R, typename E, typename = void, typename = void>
struct call_traits
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = ill_formed);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef void result_type;
};

template <typename R, typename E>
struct call_traits<R, void(E),
  typename enable_if<
    set_error_member<R, E>::is_valid
  >::type> :
  set_error_member<R, E>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_member);
};

template <typename R, typename E>
struct call_traits<R, void(E),
  typename enable_if<
    !set_error_member<R, E>::is_valid
  >::type,
  typename enable_if<
    set_error_free<R, E>::is_valid
  >::type> :
  set_error_free<R, E>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_free);
};

struct impl
{
#if defined(BOOST_ASIO_HAS_MOVE)
  template <typename R, typename E>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<R, void(E)>::overload == call_member,
    typename call_traits<R, void(E)>::result_type
  >::type
  operator()(R&& r, E&& e) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<R, void(E)>::is_noexcept))
  {
    return BOOST_ASIO_MOVE_CAST(R)(r).set_error(BOOST_ASIO_MOVE_CAST(E)(e));
  }

  template <typename R, typename E>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<R, void(E)>::overload == call_free,
    typename call_traits<R, void(E)>::result_type
  >::type
  operator()(R&& r, E&& e) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<R, void(E)>::is_noexcept))
  {
    return set_error(BOOST_ASIO_MOVE_CAST(R)(r), BOOST_ASIO_MOVE_CAST(E)(e));
  }
#else // defined(BOOST_ASIO_HAS_MOVE)
  template <typename R, typename E>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<R&, void(const E&)>::overload == call_member,
    typename call_traits<R&, void(const E&)>::result_type
  >::type
  operator()(R& r, const E& e) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<R&, void(const E&)>::is_noexcept))
  {
    return r.set_error(e);
  }

  template <typename R, typename E>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<const R&, void(const E&)>::overload == call_member,
    typename call_traits<const R&, void(const E&)>::result_type
  >::type
  operator()(const R& r, const E& e) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<const R&, void(const E&)>::is_noexcept))
  {
    return r.set_error(e);
  }

  template <typename R, typename E>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<R&, void(const E&)>::overload == call_free,
    typename call_traits<R&, void(const E&)>::result_type
  >::type
  operator()(R& r, const E& e) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<R&, void(const E&)>::is_noexcept))
  {
    return set_error(r, e);
  }

  template <typename R, typename E>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<const R&, void(const E&)>::overload == call_free,
    typename call_traits<const R&, void(const E&)>::result_type
  >::type
  operator()(const R& r, const E& e) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<const R&, void(const E&)>::is_noexcept))
  {
    return set_error(r, e);
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

} // namespace boost_asio_execution_set_error_fn
namespace boost {
namespace asio {
namespace execution {
namespace {

static BOOST_ASIO_CONSTEXPR const boost_asio_execution_set_error_fn::impl&
  set_error = boost_asio_execution_set_error_fn::static_instance<>::instance;

} // namespace

template <typename R, typename E>
struct can_set_error :
  integral_constant<bool,
    boost_asio_execution_set_error_fn::call_traits<R, void(E)>::overload !=
      boost_asio_execution_set_error_fn::ill_formed>
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename R, typename E>
constexpr bool can_set_error_v = can_set_error<R, E>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename R, typename E>
struct is_nothrow_set_error :
  integral_constant<bool,
    boost_asio_execution_set_error_fn::call_traits<R, void(E)>::is_noexcept>
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename R, typename E>
constexpr bool is_nothrow_set_error_v
  = is_nothrow_set_error<R, E>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

} // namespace execution
} // namespace asio
} // namespace boost

#endif // defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_SET_ERROR_HPP

/* set_error.hpp
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
*/