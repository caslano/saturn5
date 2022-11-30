//
// execution/bulk_execute.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_BULK_EXECUTE_HPP
#define BOOST_ASIO_EXECUTION_BULK_EXECUTE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution/bulk_guarantee.hpp>
#include <boost/asio/execution/detail/bulk_sender.hpp>
#include <boost/asio/execution/executor.hpp>
#include <boost/asio/execution/sender.hpp>
#include <boost/asio/traits/bulk_execute_member.hpp>
#include <boost/asio/traits/bulk_execute_free.hpp>

#include <boost/asio/detail/push_options.hpp>

#if defined(GENERATING_DOCUMENTATION)

namespace boost {
namespace asio {
namespace execution {

/// A customisation point that creates a bulk sender.
/**
 * The name <tt>execution::bulk_execute</tt> denotes a customisation point
 * object. If <tt>is_convertible_v<N, size_t></tt> is true, then the expression
 * <tt>execution::bulk_execute(S, F, N)</tt> for some subexpressions
 * <tt>S</tt>, <tt>F</tt>, and <tt>N</tt> is expression-equivalent to:
 *
 * @li <tt>S.bulk_execute(F, N)</tt>, if that expression is valid. If the
 *   function selected does not execute <tt>N</tt> invocations of the function
 *   object <tt>F</tt> on the executor <tt>S</tt> in bulk with forward progress
 *   guarantee <tt>boost::asio::query(S, execution::bulk_guarantee)</tt>, and
 *   the result of that function does not model <tt>sender<void></tt>, the
 *   program is ill-formed with no diagnostic required.
 *
 * @li Otherwise, <tt>bulk_execute(S, F, N)</tt>, if that expression is valid,
 *   with overload resolution performed in a context that includes the
 *   declaration <tt>void bulk_execute();</tt> and that does not include a
 *   declaration of <tt>execution::bulk_execute</tt>. If the function selected
 *   by overload resolution does not execute <tt>N</tt> invocations of the
 *   function object <tt>F</tt> on the executor <tt>S</tt> in bulk with forward
 *   progress guarantee <tt>boost::asio::query(E,
 *   execution::bulk_guarantee)</tt>, and the result of that function does not
 *   model <tt>sender<void></tt>, the program is ill-formed with no diagnostic
 *   required.
 *
 * @li Otherwise, if the types <tt>F</tt> and
 *   <tt>executor_index_t<remove_cvref_t<S>></tt> model <tt>invocable</tt> and
 *   if <tt>boost::asio::query(S, execution::bulk_guarantee)</tt> equals
 *   <tt>execution::bulk_guarantee.unsequenced</tt>, then
 *
 *    - Evaluates <tt>DECAY_COPY(std::forward<decltype(F)>(F))</tt> on the
 *      calling thread to create a function object <tt>cf</tt>. [Note:
 *      Additional copies of <tt>cf</tt> may subsequently be created. --end
 *      note.]
 *
 *    - For each value of <tt>i</tt> in <tt>N</tt>, <tt>cf(i)</tt> (or copy of
 *      <tt>cf</tt>)) will be invoked at most once by an execution agent that is
 *      unique for each value of <tt>i</tt>.
 *
 *    - May block pending completion of one or more invocations of <tt>cf</tt>.
 *
 *    - Synchronizes with (C++Std [intro.multithread]) the invocations of
 *      <tt>cf</tt>.
 *
 * @li Otherwise, <tt>execution::bulk_execute(S, F, N)</tt> is ill-formed.
 */
inline constexpr unspecified bulk_execute = unspecified;

/// A type trait that determines whether a @c bulk_execute expression is
/// well-formed.
/**
 * Class template @c can_bulk_execute is a trait that is derived from @c
 * true_type if the expression <tt>execution::bulk_execute(std::declval<S>(),
 * std::declval<F>(), std::declval<N>)</tt> is well formed; otherwise @c
 * false_type.
 */
template <typename S, typename F, typename N>
struct can_bulk_execute :
  integral_constant<bool, automatically_determined>
{
};

} // namespace execution
} // namespace asio
} // namespace boost

#else // defined(GENERATING_DOCUMENTATION)

namespace boost_asio_execution_bulk_execute_fn {

using boost::asio::declval;
using boost::asio::enable_if;
using boost::asio::execution::bulk_guarantee_t;
using boost::asio::execution::detail::bulk_sender;
using boost::asio::execution::executor_index;
using boost::asio::execution::is_sender;
using boost::asio::is_convertible;
using boost::asio::is_same;
using boost::asio::remove_cvref;
using boost::asio::result_of;
using boost::asio::traits::bulk_execute_free;
using boost::asio::traits::bulk_execute_member;
using boost::asio::traits::static_require;

void bulk_execute();

enum overload_type
{
  call_member,
  call_free,
  adapter,
  ill_formed
};

template <typename S, typename Args, typename = void, typename = void,
    typename = void, typename = void, typename = void, typename = void>
struct call_traits
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = ill_formed);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef void result_type;
};

template <typename S, typename F, typename N>
struct call_traits<S, void(F, N),
  typename enable_if<
    is_convertible<N, std::size_t>::value
  >::type,
  typename enable_if<
    bulk_execute_member<S, F, N>::is_valid
  >::type,
  typename enable_if<
    is_sender<
      typename bulk_execute_member<S, F, N>::result_type
    >::value
  >::type> :
  bulk_execute_member<S, F, N>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_member);
};

template <typename S, typename F, typename N>
struct call_traits<S, void(F, N),
  typename enable_if<
    is_convertible<N, std::size_t>::value
  >::type,
  typename enable_if<
    !bulk_execute_member<S, F, N>::is_valid
  >::type,
  typename enable_if<
    bulk_execute_free<S, F, N>::is_valid
  >::type,
  typename enable_if<
    is_sender<
      typename bulk_execute_free<S, F, N>::result_type
    >::value
  >::type> :
  bulk_execute_free<S, F, N>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_free);
};

template <typename S, typename F, typename N>
struct call_traits<S, void(F, N),
  typename enable_if<
    is_convertible<N, std::size_t>::value
  >::type,
  typename enable_if<
    !bulk_execute_member<S, F, N>::is_valid
  >::type,
  typename enable_if<
    !bulk_execute_free<S, F, N>::is_valid
  >::type,
  typename enable_if<
    is_sender<S>::value
  >::type,
  typename enable_if<
    is_same<
      typename result_of<
        F(typename executor_index<typename remove_cvref<S>::type>::type)
      >::type,
      typename result_of<
        F(typename executor_index<typename remove_cvref<S>::type>::type)
      >::type
    >::value
  >::type,
  typename enable_if<
    static_require<S, bulk_guarantee_t::unsequenced_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = adapter);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef bulk_sender<S, F, N> result_type;
};

struct impl
{
#if defined(BOOST_ASIO_HAS_MOVE)
  template <typename S, typename F, typename N>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<S, void(F, N)>::overload == call_member,
    typename call_traits<S, void(F, N)>::result_type
  >::type
  operator()(S&& s, F&& f, N&& n) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<S, void(F, N)>::is_noexcept))
  {
    return BOOST_ASIO_MOVE_CAST(S)(s).bulk_execute(
        BOOST_ASIO_MOVE_CAST(F)(f), BOOST_ASIO_MOVE_CAST(N)(n));
  }

  template <typename S, typename F, typename N>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<S, void(F, N)>::overload == call_free,
    typename call_traits<S, void(F, N)>::result_type
  >::type
  operator()(S&& s, F&& f, N&& n) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<S, void(F, N)>::is_noexcept))
  {
    return bulk_execute(BOOST_ASIO_MOVE_CAST(S)(s),
        BOOST_ASIO_MOVE_CAST(F)(f), BOOST_ASIO_MOVE_CAST(N)(n));
  }

  template <typename S, typename F, typename N>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<S, void(F, N)>::overload == adapter,
    typename call_traits<S, void(F, N)>::result_type
  >::type
  operator()(S&& s, F&& f, N&& n) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<S, void(F, N)>::is_noexcept))
  {
    return typename call_traits<S, void(F, N)>::result_type(
        BOOST_ASIO_MOVE_CAST(S)(s), BOOST_ASIO_MOVE_CAST(F)(f),
        BOOST_ASIO_MOVE_CAST(N)(n));
  }
#else // defined(BOOST_ASIO_HAS_MOVE)
  template <typename S, typename F, typename N>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<S, void(const F&, const N&)>::overload == call_member,
    typename call_traits<S, void(const F&, const N&)>::result_type
  >::type
  operator()(S& s, const F& f, const N& n) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<S, void(const F&, const N&)>::is_noexcept))
  {
    return s.bulk_execute(BOOST_ASIO_MOVE_CAST(F)(f),
        BOOST_ASIO_MOVE_CAST(N)(n));
  }

  template <typename S, typename F, typename N>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<S, void(const F&, const N&)>::overload == call_member,
    typename call_traits<S, void(const F&, const N&)>::result_type
  >::type
  operator()(const S& s, const F& f, const N& n) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<S, void(const F&, const N&)>::is_noexcept))
  {
    return s.bulk_execute(BOOST_ASIO_MOVE_CAST(F)(f),
        BOOST_ASIO_MOVE_CAST(N)(n));
  }

  template <typename S, typename F, typename N>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<S, void(const F&, const N&)>::overload == call_free,
    typename call_traits<S, void(const F&, const N&)>::result_type
  >::type
  operator()(S& s, const F& f, const N& n) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<S, void(const F&, const N&)>::is_noexcept))
  {
    return bulk_execute(s, BOOST_ASIO_MOVE_CAST(F)(f),
        BOOST_ASIO_MOVE_CAST(N)(n));
  }

  template <typename S, typename F, typename N>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<S, void(const F&, const N&)>::overload == call_free,
    typename call_traits<S, void(const F&, const N&)>::result_type
  >::type
  operator()(const S& s, const F& f, const N& n) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<S, void(const F&, const N&)>::is_noexcept))
  {
    return bulk_execute(s, BOOST_ASIO_MOVE_CAST(F)(f),
        BOOST_ASIO_MOVE_CAST(N)(n));
  }

  template <typename S, typename F, typename N>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<S, void(const F&, const N&)>::overload == adapter,
    typename call_traits<S, void(const F&, const N&)>::result_type
  >::type
  operator()(S& s, const F& f, const N& n) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<S, void(const F&, const N&)>::is_noexcept))
  {
    return typename call_traits<S, void(const F&, const N&)>::result_type(
        s, BOOST_ASIO_MOVE_CAST(F)(f), BOOST_ASIO_MOVE_CAST(N)(n));
  }

  template <typename S, typename F, typename N>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<S, void(const F&, const N&)>::overload == adapter,
    typename call_traits<S, void(const F&, const N&)>::result_type
  >::type
  operator()(const S& s, const F& f, const N& n) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<S, void(const F&, const N&)>::is_noexcept))
  {
    return typename call_traits<S, void(const F&, const N&)>::result_type(
        s, BOOST_ASIO_MOVE_CAST(F)(f), BOOST_ASIO_MOVE_CAST(N)(n));
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

} // namespace boost_asio_execution_bulk_execute_fn
namespace boost {
namespace asio {
namespace execution {
namespace {

static BOOST_ASIO_CONSTEXPR
  const boost_asio_execution_bulk_execute_fn::impl& bulk_execute =
    boost_asio_execution_bulk_execute_fn::static_instance<>::instance;

} // namespace

template <typename S, typename F, typename N>
struct can_bulk_execute :
  integral_constant<bool,
    boost_asio_execution_bulk_execute_fn::call_traits<
      S, void(F, N)>::overload !=
        boost_asio_execution_bulk_execute_fn::ill_formed>
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename S, typename F, typename N>
constexpr bool can_bulk_execute_v = can_bulk_execute<S, F, N>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename S, typename F, typename N>
struct is_nothrow_bulk_execute :
  integral_constant<bool,
    boost_asio_execution_bulk_execute_fn::call_traits<
      S, void(F, N)>::is_noexcept>
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename S, typename F, typename N>
constexpr bool is_nothrow_bulk_execute_v
  = is_nothrow_bulk_execute<S, F, N>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename S, typename F, typename N>
struct bulk_execute_result
{
  typedef typename boost_asio_execution_bulk_execute_fn::call_traits<
      S, void(F, N)>::result_type type;
};

} // namespace execution
} // namespace asio
} // namespace boost

#endif // defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_BULK_EXECUTE_HPP

/* bulk_execute.hpp
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
*/