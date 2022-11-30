//
// execution/submit.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_SUBMIT_HPP
#define BOOST_ASIO_EXECUTION_SUBMIT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution/detail/submit_receiver.hpp>
#include <boost/asio/execution/executor.hpp>
#include <boost/asio/execution/receiver.hpp>
#include <boost/asio/execution/sender.hpp>
#include <boost/asio/execution/start.hpp>
#include <boost/asio/traits/submit_member.hpp>
#include <boost/asio/traits/submit_free.hpp>

#include <boost/asio/detail/push_options.hpp>

#if defined(GENERATING_DOCUMENTATION)

namespace boost {
namespace asio {
namespace execution {

/// A customisation point that submits a sender to a receiver.
/**
 * The name <tt>execution::submit</tt> denotes a customisation point object. For
 * some subexpressions <tt>s</tt> and <tt>r</tt>, let <tt>S</tt> be a type such
 * that <tt>decltype((s))</tt> is <tt>S</tt> and let <tt>R</tt> be a type such
 * that <tt>decltype((r))</tt> is <tt>R</tt>. The expression
 * <tt>execution::submit(s, r)</tt> is ill-formed if <tt>sender_to<S, R></tt> is
 * not <tt>true</tt>. Otherwise, it is expression-equivalent to:
 *
 * @li <tt>s.submit(r)</tt>, if that expression is valid and <tt>S</tt> models
 *   <tt>sender</tt>. If the function selected does not submit the receiver
 *   object <tt>r</tt> via the sender <tt>s</tt>, the program is ill-formed with
 *   no diagnostic required.
 *
 * @li Otherwise, <tt>submit(s, r)</tt>, if that expression is valid and
 *   <tt>S</tt> models <tt>sender</tt>, with overload resolution performed in a
 *   context that includes the declaration <tt>void submit();</tt> and that does
 *   not include a declaration of <tt>execution::submit</tt>. If the function
 *   selected by overload resolution does not submit the receiver object
 *   <tt>r</tt> via the sender <tt>s</tt>, the program is ill-formed with no
 *   diagnostic required.
 *
 * @li Otherwise, <tt>execution::start((new submit_receiver<S,
 *   R>{s,r})->state_)</tt>, where <tt>submit_receiver</tt> is an
 *   implementation-defined class template equivalent to:
 *   @code template<class S, class R>
 *   struct submit_receiver {
 *     struct wrap {
 *       submit_receiver * p_;
 *       template<class...As>
 *         requires receiver_of<R, As...>
 *       void set_value(As&&... as) &&
 *         noexcept(is_nothrow_receiver_of_v<R, As...>) {
 *         execution::set_value(std::move(p_->r_), (As&&) as...);
 *         delete p_;
 *       }
 *       template<class E>
 *         requires receiver<R, E>
 *       void set_error(E&& e) && noexcept {
 *         execution::set_error(std::move(p_->r_), (E&&) e);
 *         delete p_;
 *       }
 *       void set_done() && noexcept {
 *         execution::set_done(std::move(p_->r_));
 *         delete p_;
 *       }
 *     };
 *     remove_cvref_t<R> r_;
 *     connect_result_t<S, wrap> state_;
 *     submit_receiver(S&& s, R&& r)
 *       : r_((R&&) r)
 *       , state_(execution::connect((S&&) s, wrap{this})) {}
 *   };
 *   @endcode
 */
inline constexpr unspecified submit = unspecified;

/// A type trait that determines whether a @c submit expression is
/// well-formed.
/**
 * Class template @c can_submit is a trait that is derived from
 * @c true_type if the expression <tt>execution::submit(std::declval<R>(),
 * std::declval<E>())</tt> is well formed; otherwise @c false_type.
 */
template <typename S, typename R>
struct can_submit :
  integral_constant<bool, automatically_determined>
{
};

} // namespace execution
} // namespace asio
} // namespace boost

#else // defined(GENERATING_DOCUMENTATION)

namespace boost_asio_execution_submit_fn {

using boost::asio::declval;
using boost::asio::enable_if;
using boost::asio::execution::is_sender_to;
using boost::asio::traits::submit_free;
using boost::asio::traits::submit_member;

void submit();

enum overload_type
{
  call_member,
  call_free,
  adapter,
  ill_formed
};

template <typename S, typename R, typename = void,
    typename = void, typename = void>
struct call_traits
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = ill_formed);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef void result_type;
};

template <typename S, typename R>
struct call_traits<S, void(R),
  typename enable_if<
    submit_member<S, R>::is_valid
  >::type,
  typename enable_if<
    is_sender_to<S, R>::value
  >::type> :
  submit_member<S, R>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_member);
};

template <typename S, typename R>
struct call_traits<S, void(R),
  typename enable_if<
    !submit_member<S, R>::is_valid
  >::type,
  typename enable_if<
    submit_free<S, R>::is_valid
  >::type,
  typename enable_if<
    is_sender_to<S, R>::value
  >::type> :
  submit_free<S, R>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_free);
};

template <typename S, typename R>
struct call_traits<S, void(R),
  typename enable_if<
    !submit_member<S, R>::is_valid
  >::type,
  typename enable_if<
    !submit_free<S, R>::is_valid
  >::type,
  typename enable_if<
    is_sender_to<S, R>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = adapter);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef void result_type;
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
    return BOOST_ASIO_MOVE_CAST(S)(s).submit(BOOST_ASIO_MOVE_CAST(R)(r));
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
    return submit(BOOST_ASIO_MOVE_CAST(S)(s), BOOST_ASIO_MOVE_CAST(R)(r));
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
    return boost::asio::execution::start(
        (new boost::asio::execution::detail::submit_receiver<S, R>(
          BOOST_ASIO_MOVE_CAST(S)(s), BOOST_ASIO_MOVE_CAST(R)(r)))->state_);
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
    return s.submit(r);
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
    return s.submit(r);
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
    return submit(s, r);
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
    return submit(s, r);
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
    return boost::asio::execution::start(
        (new boost::asio::execution::detail::submit_receiver<
          S&, R&>(s, r))->state_);
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
    boost::asio::execution::start(
        (new boost::asio::execution::detail::submit_receiver<
          const S&, R&>(s, r))->state_);
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
    return s.submit(r);
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
    return s.submit(r);
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
    return submit(s, r);
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
    return submit(s, r);
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
    boost::asio::execution::start(
        (new boost::asio::execution::detail::submit_receiver<
          S&, const R&>(s, r))->state_);
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
    boost::asio::execution::start(
        (new boost::asio::execution::detail::submit_receiver<
          const S&, const R&>(s, r))->state_);
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

} // namespace boost_asio_execution_submit_fn
namespace boost {
namespace asio {
namespace execution {
namespace {

static BOOST_ASIO_CONSTEXPR const boost_asio_execution_submit_fn::impl&
  submit = boost_asio_execution_submit_fn::static_instance<>::instance;

} // namespace

template <typename S, typename R>
struct can_submit :
  integral_constant<bool,
    boost_asio_execution_submit_fn::call_traits<S, void(R)>::overload !=
      boost_asio_execution_submit_fn::ill_formed>
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename S, typename R>
constexpr bool can_submit_v = can_submit<S, R>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename S, typename R>
struct is_nothrow_submit :
  integral_constant<bool,
    boost_asio_execution_submit_fn::call_traits<S, void(R)>::is_noexcept>
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename S, typename R>
constexpr bool is_nothrow_submit_v
  = is_nothrow_submit<S, R>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename S, typename R>
struct submit_result
{
  typedef typename boost_asio_execution_submit_fn::call_traits<
      S, void(R)>::result_type type;
};

namespace detail {

template <typename S, typename R>
void submit_helper(BOOST_ASIO_MOVE_ARG(S) s, BOOST_ASIO_MOVE_ARG(R) r)
{
  execution::submit(BOOST_ASIO_MOVE_CAST(S)(s), BOOST_ASIO_MOVE_CAST(R)(r));
}

} // namespace detail
} // namespace execution
} // namespace asio
} // namespace boost

#endif // defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_SUBMIT_HPP

/* submit.hpp
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
*/