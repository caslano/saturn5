//
// execution/set_value.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_SET_VALUE_HPP
#define BOOST_ASIO_EXECUTION_SET_VALUE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/detail/variadic_templates.hpp>
#include <boost/asio/traits/set_value_member.hpp>
#include <boost/asio/traits/set_value_free.hpp>

#include <boost/asio/detail/push_options.hpp>

#if defined(GENERATING_DOCUMENTATION)

namespace boost {
namespace asio {
namespace execution {

/// A customisation point that delivers a value to a receiver.
/**
 * The name <tt>execution::set_value</tt> denotes a customisation point object.
 * The expression <tt>execution::set_value(R, Vs...)</tt> for some
 * subexpressions <tt>R</tt> and <tt>Vs...</tt> is expression-equivalent to:
 *
 * @li <tt>R.set_value(Vs...)</tt>, if that expression is valid. If the
 *   function selected does not send the value(s) <tt>Vs...</tt> to the receiver
 *   <tt>R</tt>'s value channel, the program is ill-formed with no diagnostic
 *   required.
 *
 * @li Otherwise, <tt>set_value(R, Vs...)</tt>, if that expression is valid,
 *   with overload resolution performed in a context that includes the
 *   declaration <tt>void set_value();</tt> and that does not include a
 *   declaration of <tt>execution::set_value</tt>. If the function selected by
 *   overload resolution does not send the value(s) <tt>Vs...</tt> to the
 *   receiver <tt>R</tt>'s value channel, the program is ill-formed with no
 *   diagnostic required.
 *
 * @li Otherwise, <tt>execution::set_value(R, Vs...)</tt> is ill-formed.
 */
inline constexpr unspecified set_value = unspecified;

/// A type trait that determines whether a @c set_value expression is
/// well-formed.
/**
 * Class template @c can_set_value is a trait that is derived from
 * @c true_type if the expression <tt>execution::set_value(std::declval<R>(),
 * std::declval<Vs>()...)</tt> is well formed; otherwise @c false_type.
 */
template <typename R, typename... Vs>
struct can_set_value :
  integral_constant<bool, automatically_determined>
{
};

} // namespace execution
} // namespace asio
} // namespace boost

#else // defined(GENERATING_DOCUMENTATION)

namespace boost_asio_execution_set_value_fn {

using boost::asio::decay;
using boost::asio::declval;
using boost::asio::enable_if;
using boost::asio::traits::set_value_free;
using boost::asio::traits::set_value_member;

void set_value();

enum overload_type
{
  call_member,
  call_free,
  ill_formed
};

template <typename R, typename Vs, typename = void, typename = void>
struct call_traits
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = ill_formed);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef void result_type;
};

template <typename R, typename Vs>
struct call_traits<R, Vs,
  typename enable_if<
    set_value_member<R, Vs>::is_valid
  >::type> :
  set_value_member<R, Vs>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_member);
};

template <typename R, typename Vs>
struct call_traits<R, Vs,
  typename enable_if<
    !set_value_member<R, Vs>::is_valid
  >::type,
  typename enable_if<
    set_value_free<R, Vs>::is_valid
  >::type> :
  set_value_free<R, Vs>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_free);
};

struct impl
{
#if defined(BOOST_ASIO_HAS_MOVE)

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename R, typename... Vs>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<R, void(Vs...)>::overload == call_member,
    typename call_traits<R, void(Vs...)>::result_type
  >::type
  operator()(R&& r, Vs&&... v) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<R, void(Vs...)>::is_noexcept))
  {
    return BOOST_ASIO_MOVE_CAST(R)(r).set_value(BOOST_ASIO_MOVE_CAST(Vs)(v)...);
  }

  template <typename R, typename... Vs>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<R, void(Vs...)>::overload == call_free,
    typename call_traits<R, void(Vs...)>::result_type
  >::type
  operator()(R&& r, Vs&&... v) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<R, void(Vs...)>::is_noexcept))
  {
    return set_value(BOOST_ASIO_MOVE_CAST(R)(r),
        BOOST_ASIO_MOVE_CAST(Vs)(v)...);
  }

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<R, void()>::overload == call_member,
    typename call_traits<R, void()>::result_type
  >::type
  operator()(R&& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<R, void()>::is_noexcept))
  {
    return BOOST_ASIO_MOVE_CAST(R)(r).set_value();
  }

  template <typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<R, void()>::overload == call_free,
    typename call_traits<R, void()>::result_type
  >::type
  operator()(R&& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<R, void()>::is_noexcept))
  {
    return set_value(BOOST_ASIO_MOVE_CAST(R)(r));
  }

#define BOOST_ASIO_PRIVATE_SET_VALUE_CALL_DEF(n) \
  template <typename R, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  BOOST_ASIO_CONSTEXPR typename enable_if< \
    call_traits<R, \
      void(BOOST_ASIO_VARIADIC_TARGS(n))>::overload == call_member, \
    typename call_traits<R, void(BOOST_ASIO_VARIADIC_TARGS(n))>::result_type \
  >::type \
  operator()(R&& r, BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) const \
    BOOST_ASIO_NOEXCEPT_IF(( \
      call_traits<R, void(BOOST_ASIO_VARIADIC_TARGS(n))>::is_noexcept)) \
  { \
    return BOOST_ASIO_MOVE_CAST(R)(r).set_value( \
        BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  \
  template <typename R, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  BOOST_ASIO_CONSTEXPR typename enable_if< \
    call_traits<R, void(BOOST_ASIO_VARIADIC_TARGS(n))>::overload == call_free, \
    typename call_traits<R, void(BOOST_ASIO_VARIADIC_TARGS(n))>::result_type \
  >::type \
  operator()(R&& r, BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) const \
    BOOST_ASIO_NOEXCEPT_IF(( \
      call_traits<R, void(BOOST_ASIO_VARIADIC_TARGS(n))>::is_noexcept)) \
  { \
    return set_value(BOOST_ASIO_MOVE_CAST(R)(r), \
        BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  /**/
BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_SET_VALUE_CALL_DEF)
#undef BOOST_ASIO_PRIVATE_SET_VALUE_CALL_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

#else // defined(BOOST_ASIO_HAS_MOVE)

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename R, typename... Vs>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<R&, void(const Vs&...)>::overload == call_member,
    typename call_traits<R&, void(const Vs&...)>::result_type
  >::type
  operator()(R& r, const Vs&... v) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<R&, void(const Vs&...)>::is_noexcept))
  {
    return r.set_value(v...);
  }

  template <typename R, typename... Vs>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<const R&, void(const Vs&...)>::overload == call_member,
    typename call_traits<const R&, void(const Vs&...)>::result_type
  >::type
  operator()(const R& r, const Vs&... v) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<const R&, void(const Vs&...)>::is_noexcept))
  {
    return r.set_value(v...);
  }

  template <typename R, typename... Vs>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<R&, void(const Vs&...)>::overload == call_free,
    typename call_traits<R&, void(const Vs&...)>::result_type
  >::type
  operator()(R& r, const Vs&... v) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<R&, void(const Vs&...)>::is_noexcept))
  {
    return set_value(r, v...);
  }

  template <typename R, typename... Vs>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<const R&, void(const Vs&...)>::overload == call_free,
    typename call_traits<const R&, void(const Vs&...)>::result_type
  >::type
  operator()(const R& r, const Vs&... v) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<const R&, void(const Vs&...)>::is_noexcept))
  {
    return set_value(r, v...);
  }

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<R&, void()>::overload == call_member,
    typename call_traits<R&, void()>::result_type
  >::type
  operator()(R& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<R&, void()>::is_noexcept))
  {
    return r.set_value();
  }

  template <typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<const R&, void()>::overload == call_member,
    typename call_traits<const R&, void()>::result_type
  >::type
  operator()(const R& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<const R&, void()>::is_noexcept))
  {
    return r.set_value();
  }

  template <typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<R&, void()>::overload == call_free,
    typename call_traits<R&, void()>::result_type
  >::type
  operator()(R& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<R&, void()>::is_noexcept))
  {
    return set_value(r);
  }

  template <typename R>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<const R&, void()>::overload == call_free,
    typename call_traits<const R&, void()>::result_type
  >::type
  operator()(const R& r) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<const R&, void()>::is_noexcept))
  {
    return set_value(r);
  }

#define BOOST_ASIO_PRIVATE_SET_VALUE_CALL_DEF(n) \
  template <typename R, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  BOOST_ASIO_CONSTEXPR typename enable_if< \
    call_traits<R&, \
      void(BOOST_ASIO_VARIADIC_TARGS(n))>::overload == call_member, \
    typename call_traits<R&, void(BOOST_ASIO_VARIADIC_TARGS(n))>::result_type \
  >::type \
  operator()(R& r, BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) const \
    BOOST_ASIO_NOEXCEPT_IF(( \
      call_traits<R&, void(BOOST_ASIO_VARIADIC_TARGS(n))>::is_noexcept)) \
  { \
    return r.set_value(BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  \
  template <typename R, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  BOOST_ASIO_CONSTEXPR typename enable_if< \
    call_traits<const R&, \
      void(BOOST_ASIO_VARIADIC_TARGS(n))>::overload == call_member, \
    typename call_traits<const R&, \
      void(BOOST_ASIO_VARIADIC_TARGS(n))>::result_type \
  >::type \
  operator()(const R& r, BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) const \
    BOOST_ASIO_NOEXCEPT_IF(( \
      call_traits<const R&, void(BOOST_ASIO_VARIADIC_TARGS(n))>::is_noexcept)) \
  { \
    return r.set_value(BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  \
  template <typename R, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  BOOST_ASIO_CONSTEXPR typename enable_if< \
    call_traits<R&, \
      void(BOOST_ASIO_VARIADIC_TARGS(n))>::overload == call_free, \
    typename call_traits<R&, void(BOOST_ASIO_VARIADIC_TARGS(n))>::result_type \
  >::type \
  operator()(R& r, BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) const \
    BOOST_ASIO_NOEXCEPT_IF(( \
      call_traits<R&, void(BOOST_ASIO_VARIADIC_TARGS(n))>::is_noexcept)) \
  { \
    return set_value(r, BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  \
  template <typename R, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  BOOST_ASIO_CONSTEXPR typename enable_if< \
    call_traits<const R&, \
      void(BOOST_ASIO_VARIADIC_TARGS(n))>::overload == call_free, \
    typename call_traits<const R&, \
      void(BOOST_ASIO_VARIADIC_TARGS(n))>::result_type \
  >::type \
  operator()(const R& r, BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) const \
    BOOST_ASIO_NOEXCEPT_IF(( \
      call_traits<const R&, void(BOOST_ASIO_VARIADIC_TARGS(n))>::is_noexcept)) \
  { \
    return set_value(r, BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  /**/
BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_SET_VALUE_CALL_DEF)
#undef BOOST_ASIO_PRIVATE_SET_VALUE_CALL_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

#endif // defined(BOOST_ASIO_HAS_MOVE)
};

template <typename T = impl>
struct static_instance
{
  static const T instance;
};

template <typename T>
const T static_instance<T>::instance = {};

} // namespace boost_asio_execution_set_value_fn
namespace boost {
namespace asio {
namespace execution {
namespace {

static BOOST_ASIO_CONSTEXPR const boost_asio_execution_set_value_fn::impl&
  set_value = boost_asio_execution_set_value_fn::static_instance<>::instance;

} // namespace

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename R, typename... Vs>
struct can_set_value :
  integral_constant<bool,
    boost_asio_execution_set_value_fn::call_traits<R, void(Vs...)>::overload !=
      boost_asio_execution_set_value_fn::ill_formed>
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename R, typename... Vs>
constexpr bool can_set_value_v = can_set_value<R, Vs...>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename R, typename... Vs>
struct is_nothrow_set_value :
  integral_constant<bool,
    boost_asio_execution_set_value_fn::call_traits<R, void(Vs...)>::is_noexcept>
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename R, typename... Vs>
constexpr bool is_nothrow_set_value_v
  = is_nothrow_set_value<R, Vs...>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename R, typename = void,
    typename = void, typename = void, typename = void, typename = void,
    typename = void, typename = void, typename = void, typename = void>
struct can_set_value;

template <typename R, typename = void,
    typename = void, typename = void, typename = void, typename = void,
    typename = void, typename = void, typename = void, typename = void>
struct is_nothrow_set_value;

template <typename R>
struct can_set_value<R> :
  integral_constant<bool,
    boost_asio_execution_set_value_fn::call_traits<R, void()>::overload !=
      boost_asio_execution_set_value_fn::ill_formed>
{
};

template <typename R>
struct is_nothrow_set_value<R> :
  integral_constant<bool,
    boost_asio_execution_set_value_fn::call_traits<R, void()>::is_noexcept>
{
};

#define BOOST_ASIO_PRIVATE_SET_VALUE_TRAITS_DEF(n) \
  template <typename R, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  struct can_set_value<R, BOOST_ASIO_VARIADIC_TARGS(n)> : \
    integral_constant<bool, \
      boost_asio_execution_set_value_fn::call_traits<R, \
        void(BOOST_ASIO_VARIADIC_TARGS(n))>::overload != \
          boost_asio_execution_set_value_fn::ill_formed> \
  { \
  }; \
  \
  template <typename R, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  struct is_nothrow_set_value<R, BOOST_ASIO_VARIADIC_TARGS(n)> : \
    integral_constant<bool, \
      boost_asio_execution_set_value_fn::call_traits<R, \
        void(BOOST_ASIO_VARIADIC_TARGS(n))>::is_noexcept> \
  { \
  }; \
  /**/
BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_SET_VALUE_TRAITS_DEF)
#undef BOOST_ASIO_PRIVATE_SET_VALUE_TRAITS_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

} // namespace execution
} // namespace asio
} // namespace boost

#endif // defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_SET_VALUE_HPP

/* set_value.hpp
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
*/