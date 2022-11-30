//
// execution/connect.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_CONNECT_HPP
#define BOOST_ASIO_EXECUTION_CONNECT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution/detail/as_invocable.hpp>
#include <boost/asio/execution/detail/as_operation.hpp>
#include <boost/asio/execution/detail/as_receiver.hpp>
#include <boost/asio/execution/executor.hpp>
#include <boost/asio/execution/operation_state.hpp>
#include <boost/asio/execution/receiver.hpp>
#include <boost/asio/execution/sender.hpp>
#include <boost/asio/traits/connect_member.hpp>
#include <boost/asio/traits/connect_free.hpp>

#include <boost/asio/detail/push_options.hpp>

#if defined(GENERATING_DOCUMENTATION)

namespace boost {
namespace asio {
namespace execution {

/// A customisation point that connects a sender to a receiver.
/**
 * The name <tt>execution::connect</tt> denotes a customisation point object.
 * For some subexpressions <tt>s</tt> and <tt>r</tt>, let <tt>S</tt> be a type
 * such that <tt>decltype((s))</tt> is <tt>S</tt> and let <tt>R</tt> be a type
 * such that <tt>decltype((r))</tt> is <tt>R</tt>. The expression
 * <tt>execution::connect(s, r)</tt> is expression-equivalent to:
 *
 * @li <tt>s.connect(r)</tt>, if that expression is valid, if its type
 *   satisfies <tt>operation_state</tt>, and if <tt>S</tt> satisfies
 *   <tt>sender</tt>.
 *
 * @li Otherwise, <tt>connect(s, r)</tt>, if that expression is valid, if its
 *   type satisfies <tt>operation_state</tt>, and if <tt>S</tt> satisfies
 *   <tt>sender</tt>, with overload resolution performed in a context that
 *   includes the declaration <tt>void connect();</tt> and that does not include
 *   a declaration of <tt>execution::connect</tt>.
 *
 * @li Otherwise, <tt>as_operation{s, r}</tt>, if <tt>r</tt> is not an instance
 *  of <tt>as_receiver<F, S></tt> for some type <tt>F</tt>, and if
 *  <tt>receiver_of<R> && executor_of<remove_cvref_t<S>,
 *  as_invocable<remove_cvref_t<R>, S>></tt> is <tt>true</tt>, where
 *  <tt>as_operation</tt> is an implementation-defined class equivalent to
 *  @code template <class S, class R>
 *  struct as_operation
 *  {
 *    remove_cvref_t<S> e_;
 *    remove_cvref_t<R> r_;
 *    void start() noexcept try {
 *      execution::execute(std::move(e_),
 *          as_invocable<remove_cvref_t<R>, S>{r_});
 *    } catch(...) {
 *      execution::set_error(std::move(r_), current_exception());
 *    }
 *  }; @endcode
 *  and <tt>as_invocable</tt> is a class template equivalent to the following:
 *  @code template<class R>
 *  struct as_invocable
 *  {
 *    R* r_;
 *    explicit as_invocable(R& r) noexcept
 *      : r_(std::addressof(r)) {}
 *    as_invocable(as_invocable && other) noexcept
 *      : r_(std::exchange(other.r_, nullptr)) {}
 *    ~as_invocable() {
 *      if(r_)
 *        execution::set_done(std::move(*r_));
 *    }
 *    void operator()() & noexcept try {
 *      execution::set_value(std::move(*r_));
 *      r_ = nullptr;
 *    } catch(...) {
 *      execution::set_error(std::move(*r_), current_exception());
 *      r_ = nullptr;
 *    }
 *  };
 *  @endcode
 *
 * @li Otherwise, <tt>execution::connect(s, r)</tt> is ill-formed.
 */
inline constexpr unspecified connect = unspecified;

/// A type trait that determines whether a @c connect expression is
/// well-formed.
/**
 * Class template @c can_connect is a trait that is derived from
 * @c true_type if the expression <tt>execution::connect(std::declval<S>(),
 * std::declval<R>())</tt> is well formed; otherwise @c false_type.
 */
template <typename S, typename R>
struct can_connect :
  integral_constant<bool, automatically_determined>
{
};

/// A type trait to determine the result of a @c connect expression.
template <typename S, typename R>
struct connect_result
{
  /// The type of the connect expression.
  /**
   * The type of the expression <tt>execution::connect(std::declval<S>(),
   * std::declval<R>())</tt>.
   */
  typedef automatically_determined type;
};

/// A type alis to determine the result of a @c connect expression.
template <typename S, typename R>
using connect_result_t = typename connect_result<S, R>::type;

} // namespace execution
} // namespace asio
} // namespace boost

#else // defined(GENERATING_DOCUMENTATION)

namespace boost_asio_execution_connect_fn {

using boost::asio::conditional;
using boost::asio::declval;
using boost::asio::enable_if;
using boost::asio::execution::detail::as_invocable;
using boost::asio::execution::detail::as_operation;
using boost::asio::execution::detail::is_as_receiver;
using boost::asio::execution::is_executor_of;
using boost::asio::execution::is_operation_state;
using boost::asio::execution::is_receiver;
using boost::asio::execution::is_sender;
using boost::asio::false_type;
using boost::asio::remove_cvref;
using boost::asio::traits::connect_free;
using boost::asio::traits::connect_member;

void connect();

enum overload_type
{
  call_member,
  call_free,
  adapter,
  ill_formed
};

template <typename S, typename R, typename = void,
   typename = void, typename = void, typename = void>
struct call_traits
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = ill_formed);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef void result_type;
};

template <typename S, typename R>
struct call_traits<S, void(R),
  typename enable_if<
    connect_member<S, R>::is_valid
  >::type,
  typename enable_if<
    is_operation_state<typename connect_member<S, R>::result_type>::value
  >::type,
  typename enable_if<
    is_sender<typename remove_cvref<S>::type>::value
  >::type> :
  connect_member<S, R>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_member);
};

template <typename S, typename R>
struct call_traits<S, void(R),
  typename enable_if<
    !connect_member<S, R>::is_valid
  >::type,
  typename enable_if<
    connect_free<S, R>::is_valid
  >::type,
  typename enable_if<
    is_operation_state<typename connect_free<S, R>::result_type>::value
  >::type,
  typename enable_if<
    is_sender<typename remove_cvref<S>::type>::value
  >::type> :
  connect_free<S, R>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_free);
};

template <typename S, typename R>
struct call_traits<S, void(R),
  typename enable_if<
    !connect_member<S, R>::is_valid
  >::type,
  typename enable_if<
    !connect_free<S, R>::is_valid
  >::type,
  typename enable_if<
    is_receiver<R>::value
  >::type,
  typename enable_if<
    conditional<
      !is_as_receiver<
        typename remove_cvref<R>::type
      >::value,
      is_executor_of<
        typename remove_cvref<S>::type,
        as_invocable<typename remove_cvref<R>::type, S>
      >,
      false_type
    >::type::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = adapter);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef as_operation<S, R> result_type;
};

struct impl
{
#if defined(BOOST_ASIO_HAS_MOVE)
  template <typename S, typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<S, void(R)>::overload == call_member,
    typename call_traits<S, void(R)>::result_type
  >::type
  operator()(S&& s, R&& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<S, void(R)>::is_noexcept))
  {
    return BOOST_ASIO_MOVE_CAST(S)(s).connect(BOOST_ASIO_MOVE_CAST(R)(r));
  }

  template <typename S, typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<S, void(R)>::overload == call_free,
    typename call_traits<S, void(R)>::result_type
  >::type
  operator()(S&& s, R&& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<S, void(R)>::is_noexcept))
  {
    return connect(BOOST_ASIO_MOVE_CAST(S)(s), BOOST_ASIO_MOVE_CAST(R)(r));
  }

  template <typename S, typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<S, void(R)>::overload == adapter,
    typename call_traits<S, void(R)>::result_type
  >::type
  operator()(S&& s, R&& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<S, void(R)>::is_noexcept))
  {
    return typename call_traits<S, void(R)>::result_type(
        BOOST_ASIO_MOVE_CAST(S)(s), BOOST_ASIO_MOVE_CAST(R)(r));
  }
#else // defined(BOOST_ASIO_HAS_MOVE)
  template <typename S, typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<S&, void(R&)>::overload == call_member,
    typename call_traits<S&, void(R&)>::result_type
  >::type
  operator()(S& s, R& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<S&, void(R&)>::is_noexcept))
  {
    return s.connect(r);
  }

  template <typename S, typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<const S&, void(R&)>::overload == call_member,
    typename call_traits<const S&, void(R&)>::result_type
  >::type
  operator()(const S& s, R& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<const S&, void(R&)>::is_noexcept))
  {
    return s.connect(r);
  }

  template <typename S, typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<S&, void(R&)>::overload == call_free,
    typename call_traits<S&, void(R&)>::result_type
  >::type
  operator()(S& s, R& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<S&, void(R&)>::is_noexcept))
  {
    return connect(s, r);
  }

  template <typename S, typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<const S&, void(R&)>::overload == call_free,
    typename call_traits<const S&, void(R&)>::result_type
  >::type
  operator()(const S& s, R& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<const S&, void(R&)>::is_noexcept))
  {
    return connect(s, r);
  }

  template <typename S, typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<S&, void(R&)>::overload == adapter,
    typename call_traits<S&, void(R&)>::result_type
  >::type
  operator()(S& s, R& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<S&, void(R&)>::is_noexcept))
  {
    return typename call_traits<S&, void(R&)>::result_type(s, r);
  }

  template <typename S, typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<const S&, void(R&)>::overload == adapter,
    typename call_traits<const S&, void(R&)>::result_type
  >::type
  operator()(const S& s, R& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<const S&, void(R&)>::is_noexcept))
  {
    return typename call_traits<const S&, void(R&)>::result_type(s, r);
  }

  template <typename S, typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<S&, void(const R&)>::overload == call_member,
    typename call_traits<S&, void(const R&)>::result_type
  >::type
  operator()(S& s, const R& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<S&, void(const R&)>::is_noexcept))
  {
    return s.connect(r);
  }

  template <typename S, typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<const S&, void(const R&)>::overload == call_member,
    typename call_traits<const S&, void(const R&)>::result_type
  >::type
  operator()(const S& s, const R& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<const S&, void(const R&)>::is_noexcept))
  {
    return s.connect(r);
  }

  template <typename S, typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<S&, void(const R&)>::overload == call_free,
    typename call_traits<S&, void(const R&)>::result_type
  >::type
  operator()(S& s, const R& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<S&, void(const R&)>::is_noexcept))
  {
    return connect(s, r);
  }

  template <typename S, typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<const S&, void(const R&)>::overload == call_free,
    typename call_traits<const S&, void(const R&)>::result_type
  >::type
  operator()(const S& s, const R& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<const S&, void(const R&)>::is_noexcept))
  {
    return connect(s, r);
  }

  template <typename S, typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<S&, void(const R&)>::overload == adapter,
    typename call_traits<S&, void(const R&)>::result_type
  >::type
  operator()(S& s, const R& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<S&, void(const R&)>::is_noexcept))
  {
    return typename call_traits<S&, void(const R&)>::result_type(s, r);
  }

  template <typename S, typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<const S&, void(const R&)>::overload == adapter,
    typename call_traits<const S&, void(const R&)>::result_type
  >::type
  operator()(const S& s, const R& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<const S&, void(const R&)>::is_noexcept))
  {
    return typename call_traits<const S&, void(const R&)>::result_type(s, r);
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

} // namespace boost_asio_execution_connect_fn
namespace boost {
namespace asio {
namespace execution {
namespace {

static BOOST_ASIO_CONSTEXPR const boost_asio_execution_connect_fn::impl&
  connect = boost_asio_execution_connect_fn::static_instance<>::instance;

} // namespace

template <typename S, typename R>
struct can_connect :
  integral_constant<bool,
    boost_asio_execution_connect_fn::call_traits<S, void(R)>::overload !=
      boost_asio_execution_connect_fn::ill_formed>
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename S, typename R>
constexpr bool can_connect_v = can_connect<S, R>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename S, typename R>
struct is_nothrow_connect :
  integral_constant<bool,
    boost_asio_execution_connect_fn::call_traits<S, void(R)>::is_noexcept>
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename S, typename R>
constexpr bool is_nothrow_connect_v
  = is_nothrow_connect<S, R>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename S, typename R>
struct connect_result
{
  typedef typename boost_asio_execution_connect_fn::call_traits<
      S, void(R)>::result_type type;
};

#if defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)

template <typename S, typename R>
using connect_result_t = typename connect_result<S, R>::type;

#endif // defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)

} // namespace execution
} // namespace asio
} // namespace boost

#endif // defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_CONNECT_HPP

/* connect.hpp
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
*/