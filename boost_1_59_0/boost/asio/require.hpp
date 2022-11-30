//
// require.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_REQUIRE_HPP
#define BOOST_ASIO_REQUIRE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/is_applicable_property.hpp>
#include <boost/asio/traits/require_member.hpp>
#include <boost/asio/traits/require_free.hpp>
#include <boost/asio/traits/static_require.hpp>

#include <boost/asio/detail/push_options.hpp>

#if defined(GENERATING_DOCUMENTATION)

namespace boost {
namespace asio {

/// A customisation point that applies a concept-preserving property to an
/// object.
/**
 * The name <tt>require</tt> denotes a customisation point object. The
 * expression <tt>boost::asio::require(E, P0, Pn...)</tt> for some
 * subexpressions <tt>E</tt> and <tt>P0</tt>, and where <tt>Pn...</tt>
 * represents <tt>N</tt> subexpressions (where <tt>N</tt> is 0 or more, and with
 * types <tt>T = decay_t<decltype(E)></tt> and <tt>Prop0 =
 * decay_t<decltype(P0)></tt>) is expression-equivalent to:
 *
 * @li If <tt>is_applicable_property_v<T, Prop0> && Prop0::is_requirable</tt> is
 *   not a well-formed constant expression with value <tt>true</tt>,
 *   <tt>boost::asio::require(E, P0, Pn...)</tt> is ill-formed.
 *
 * @li Otherwise, <tt>E</tt> if <tt>N == 0</tt> and the expression
 *   <tt>Prop0::template static_query_v<T> == Prop0::value()</tt> is a
 *   well-formed constant expression with value <tt>true</tt>.
 *
 * @li Otherwise, <tt>(E).require(P0)</tt> if <tt>N == 0</tt> and the expression
 *   <tt>(E).require(P0)</tt> is a valid expression.
 *
 * @li Otherwise, <tt>require(E, P0)</tt> if <tt>N == 0</tt> and the expression
 *   <tt>require(E, P0)</tt> is a valid expression with overload resolution
 *   performed in a context that does not include the declaration of the
 *   <tt>require</tt> customization point object.
 *
 * @li Otherwise,
 *   <tt>boost::asio::require(boost::asio::require(E, P0), Pn...)</tt>
 *   if <tt>N > 0</tt> and the expression
 *   <tt>boost::asio::require(boost::asio::require(E, P0), Pn...)</tt>
 *   is a valid expression.
 *
 * @li Otherwise, <tt>boost::asio::require(E, P0, Pn...)</tt> is ill-formed.
 */
inline constexpr unspecified require = unspecified;

/// A type trait that determines whether a @c require expression is well-formed.
/**
 * Class template @c can_require is a trait that is derived from
 * @c true_type if the expression <tt>boost::asio::require(std::declval<T>(),
 * std::declval<Properties>()...)</tt> is well formed; otherwise @c false_type.
 */
template <typename T, typename... Properties>
struct can_require :
  integral_constant<bool, automatically_determined>
{
};

/// A type trait that determines whether a @c require expression will not throw.
/**
 * Class template @c is_nothrow_require is a trait that is derived from
 * @c true_type if the expression <tt>boost::asio::require(std::declval<T>(),
 * std::declval<Properties>()...)</tt> is @c noexcept; otherwise @c false_type.
 */
template <typename T, typename... Properties>
struct is_nothrow_require :
  integral_constant<bool, automatically_determined>
{
};

/// A type trait that determines the result type of a @c require expression.
/**
 * Class template @c require_result is a trait that determines the result
 * type of the expression <tt>boost::asio::require(std::declval<T>(),
 * std::declval<Properties>()...)</tt>.
 */
template <typename T, typename... Properties>
struct require_result
{
  /// The result of the @c require expression.
  typedef automatically_determined type;
};

} // namespace asio
} // namespace boost

#else // defined(GENERATING_DOCUMENTATION)

namespace boost_asio_require_fn {

using boost::asio::conditional;
using boost::asio::decay;
using boost::asio::declval;
using boost::asio::enable_if;
using boost::asio::is_applicable_property;
using boost::asio::traits::require_free;
using boost::asio::traits::require_member;
using boost::asio::traits::static_require;

void require();

enum overload_type
{
  identity,
  call_member,
  call_free,
  two_props,
  n_props,
  ill_formed
};

template <typename Impl, typename T, typename Properties, typename = void,
    typename = void, typename = void, typename = void, typename = void>
struct call_traits
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = ill_formed);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef void result_type;
};

template <typename Impl, typename T, typename Property>
struct call_traits<Impl, T, void(Property),
  typename enable_if<
    is_applicable_property<
      typename decay<T>::type,
      typename decay<Property>::type
    >::value
  >::type,
  typename enable_if<
    decay<Property>::type::is_requirable
  >::type,
  typename enable_if<
    static_require<T, Property>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = identity);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

#if defined(BOOST_ASIO_HAS_MOVE)
  typedef BOOST_ASIO_MOVE_ARG(T) result_type;
#else // defined(BOOST_ASIO_HAS_MOVE)
  typedef BOOST_ASIO_MOVE_ARG(typename decay<T>::type) result_type;
#endif // defined(BOOST_ASIO_HAS_MOVE)
};

template <typename Impl, typename T, typename Property>
struct call_traits<Impl, T, void(Property),
  typename enable_if<
    is_applicable_property<
      typename decay<T>::type,
      typename decay<Property>::type
    >::value
  >::type,
  typename enable_if<
    decay<Property>::type::is_requirable
  >::type,
  typename enable_if<
    !static_require<T, Property>::is_valid
  >::type,
  typename enable_if<
    require_member<typename Impl::template proxy<T>::type, Property>::is_valid
  >::type> :
  require_member<typename Impl::template proxy<T>::type, Property>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_member);
};

template <typename Impl, typename T, typename Property>
struct call_traits<Impl, T, void(Property),
  typename enable_if<
    is_applicable_property<
      typename decay<T>::type,
      typename decay<Property>::type
    >::value
  >::type,
  typename enable_if<
    decay<Property>::type::is_requirable
  >::type,
  typename enable_if<
    !static_require<T, Property>::is_valid
  >::type,
  typename enable_if<
    !require_member<typename Impl::template proxy<T>::type, Property>::is_valid
  >::type,
  typename enable_if<
    require_free<T, Property>::is_valid
  >::type> :
  require_free<T, Property>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_free);
};

template <typename Impl, typename T, typename P0, typename P1>
struct call_traits<Impl, T, void(P0, P1),
  typename enable_if<
    call_traits<Impl, T, void(P0)>::overload != ill_formed
  >::type,
  typename enable_if<
    call_traits<
      Impl,
      typename call_traits<Impl, T, void(P0)>::result_type,
      void(P1)
    >::overload != ill_formed
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = two_props);

  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    (
      call_traits<Impl, T, void(P0)>::is_noexcept
      &&
      call_traits<
        Impl,
        typename call_traits<Impl, T, void(P0)>::result_type,
        void(P1)
      >::is_noexcept
    ));

  typedef typename decay<
    typename call_traits<
      Impl,
      typename call_traits<Impl, T, void(P0)>::result_type,
      void(P1)
    >::result_type
  >::type result_type;
};

template <typename Impl, typename T, typename P0,
    typename P1, typename BOOST_ASIO_ELLIPSIS PN>
struct call_traits<Impl, T, void(P0, P1, PN BOOST_ASIO_ELLIPSIS),
  typename enable_if<
    call_traits<Impl, T, void(P0)>::overload != ill_formed
  >::type,
  typename enable_if<
    call_traits<
      Impl,
      typename call_traits<Impl, T, void(P0)>::result_type,
      void(P1, PN BOOST_ASIO_ELLIPSIS)
    >::overload != ill_formed
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = n_props);

  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    (
      call_traits<Impl, T, void(P0)>::is_noexcept
      &&
      call_traits<
        Impl,
        typename call_traits<Impl, T, void(P0)>::result_type,
        void(P1, PN BOOST_ASIO_ELLIPSIS)
      >::is_noexcept
    ));

  typedef typename decay<
    typename call_traits<
      Impl,
      typename call_traits<Impl, T, void(P0)>::result_type,
      void(P1, PN BOOST_ASIO_ELLIPSIS)
    >::result_type
  >::type result_type;
};

struct impl
{
  template <typename T>
  struct proxy
  {
#if defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_MEMBER_TRAIT)
    struct type
    {
      template <typename P>
      auto require(BOOST_ASIO_MOVE_ARG(P) p)
        noexcept(
          noexcept(
            declval<typename conditional<true, T, P>::type>().require(
              BOOST_ASIO_MOVE_CAST(P)(p))
          )
        )
        -> decltype(
          declval<typename conditional<true, T, P>::type>().require(
            BOOST_ASIO_MOVE_CAST(P)(p))
        );
    };
#else // defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_MEMBER_TRAIT)
    typedef T type;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_MEMBER_TRAIT)
  };

  template <typename T, typename Property>
  BOOST_ASIO_NODISCARD BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<impl, T, void(Property)>::overload == identity,
    typename call_traits<impl, T, void(Property)>::result_type
  >::type
  operator()(
      BOOST_ASIO_MOVE_ARG(T) t,
      BOOST_ASIO_MOVE_ARG(Property)) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<impl, T, void(Property)>::is_noexcept))
  {
    return BOOST_ASIO_MOVE_CAST(T)(t);
  }

  template <typename T, typename Property>
  BOOST_ASIO_NODISCARD BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<impl, T, void(Property)>::overload == call_member,
    typename call_traits<impl, T, void(Property)>::result_type
  >::type
  operator()(
      BOOST_ASIO_MOVE_ARG(T) t,
      BOOST_ASIO_MOVE_ARG(Property) p) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<impl, T, void(Property)>::is_noexcept))
  {
    return BOOST_ASIO_MOVE_CAST(T)(t).require(
        BOOST_ASIO_MOVE_CAST(Property)(p));
  }

  template <typename T, typename Property>
  BOOST_ASIO_NODISCARD BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<impl, T, void(Property)>::overload == call_free,
    typename call_traits<impl, T, void(Property)>::result_type
  >::type
  operator()(
      BOOST_ASIO_MOVE_ARG(T) t,
      BOOST_ASIO_MOVE_ARG(Property) p) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<impl, T, void(Property)>::is_noexcept))
  {
    return require(
        BOOST_ASIO_MOVE_CAST(T)(t),
        BOOST_ASIO_MOVE_CAST(Property)(p));
  }

  template <typename T, typename P0, typename P1>
  BOOST_ASIO_NODISCARD BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<impl, T, void(P0, P1)>::overload == two_props,
    typename call_traits<impl, T, void(P0, P1)>::result_type
  >::type
  operator()(
      BOOST_ASIO_MOVE_ARG(T) t,
      BOOST_ASIO_MOVE_ARG(P0) p0,
      BOOST_ASIO_MOVE_ARG(P1) p1) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<impl, T, void(P0, P1)>::is_noexcept))
  {
    return (*this)(
        (*this)(
          BOOST_ASIO_MOVE_CAST(T)(t),
          BOOST_ASIO_MOVE_CAST(P0)(p0)),
        BOOST_ASIO_MOVE_CAST(P1)(p1));
  }

  template <typename T, typename P0, typename P1,
    typename BOOST_ASIO_ELLIPSIS PN>
  BOOST_ASIO_NODISCARD BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<impl, T,
      void(P0, P1, PN BOOST_ASIO_ELLIPSIS)>::overload == n_props,
    typename call_traits<impl, T,
      void(P0, P1, PN BOOST_ASIO_ELLIPSIS)>::result_type
  >::type
  operator()(
      BOOST_ASIO_MOVE_ARG(T) t,
      BOOST_ASIO_MOVE_ARG(P0) p0,
      BOOST_ASIO_MOVE_ARG(P1) p1,
      BOOST_ASIO_MOVE_ARG(PN) BOOST_ASIO_ELLIPSIS pn) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<impl, T, void(P0, P1, PN BOOST_ASIO_ELLIPSIS)>::is_noexcept))
  {
    return (*this)(
        (*this)(
          BOOST_ASIO_MOVE_CAST(T)(t),
          BOOST_ASIO_MOVE_CAST(P0)(p0)),
        BOOST_ASIO_MOVE_CAST(P1)(p1),
        BOOST_ASIO_MOVE_CAST(PN)(pn) BOOST_ASIO_ELLIPSIS);
  }
};

template <typename T = impl>
struct static_instance
{
  static const T instance;
};

template <typename T>
const T static_instance<T>::instance = {};

} // namespace boost_asio_require_fn
namespace boost {
namespace asio {
namespace {

static BOOST_ASIO_CONSTEXPR const boost_asio_require_fn::impl&
  require = boost_asio_require_fn::static_instance<>::instance;

} // namespace

typedef boost_asio_require_fn::impl require_t;

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T, typename... Properties>
struct can_require :
  integral_constant<bool,
    boost_asio_require_fn::call_traits<
      require_t, T, void(Properties...)>::overload
        != boost_asio_require_fn::ill_formed>
{
};

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T, typename P0 = void,
    typename P1 = void, typename P2 = void>
struct can_require :
  integral_constant<bool,
    boost_asio_require_fn::call_traits<require_t, T, void(P0, P1, P2)>::overload
      != boost_asio_require_fn::ill_formed>
{
};

template <typename T, typename P0, typename P1>
struct can_require<T, P0, P1> :
  integral_constant<bool,
    boost_asio_require_fn::call_traits<require_t, T, void(P0, P1)>::overload
      != boost_asio_require_fn::ill_formed>
{
};

template <typename T, typename P0>
struct can_require<T, P0> :
  integral_constant<bool,
    boost_asio_require_fn::call_traits<require_t, T, void(P0)>::overload
      != boost_asio_require_fn::ill_formed>
{
};

template <typename T>
struct can_require<T> :
  false_type
{
};

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T, typename BOOST_ASIO_ELLIPSIS Properties>
constexpr bool can_require_v
  = can_require<T, Properties BOOST_ASIO_ELLIPSIS>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T, typename... Properties>
struct is_nothrow_require :
  integral_constant<bool,
    boost_asio_require_fn::call_traits<
      require_t, T, void(Properties...)>::is_noexcept>
{
};

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T, typename P0 = void,
    typename P1 = void, typename P2 = void>
struct is_nothrow_require :
  integral_constant<bool,
    boost_asio_require_fn::call_traits<
      require_t, T, void(P0, P1, P2)>::is_noexcept>
{
};

template <typename T, typename P0, typename P1>
struct is_nothrow_require<T, P0, P1> :
  integral_constant<bool,
    boost_asio_require_fn::call_traits<
      require_t, T, void(P0, P1)>::is_noexcept>
{
};

template <typename T, typename P0>
struct is_nothrow_require<T, P0> :
  integral_constant<bool,
    boost_asio_require_fn::call_traits<
      require_t, T, void(P0)>::is_noexcept>
{
};

template <typename T>
struct is_nothrow_require<T> :
  false_type
{
};

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T, typename BOOST_ASIO_ELLIPSIS Properties>
constexpr bool is_nothrow_require_v
  = is_nothrow_require<T, Properties BOOST_ASIO_ELLIPSIS>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T, typename... Properties>
struct require_result
{
  typedef typename boost_asio_require_fn::call_traits<
      require_t, T, void(Properties...)>::result_type type;
};

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T, typename P0 = void,
    typename P1 = void, typename P2 = void>
struct require_result
{
  typedef typename boost_asio_require_fn::call_traits<
      require_t, T, void(P0, P1, P2)>::result_type type;
};

template <typename T, typename P0, typename P1>
struct require_result<T, P0, P1>
{
  typedef typename boost_asio_require_fn::call_traits<
      require_t, T, void(P0, P1)>::result_type type;
};

template <typename T, typename P0>
struct require_result<T, P0>
{
  typedef typename boost_asio_require_fn::call_traits<
      require_t, T, void(P0)>::result_type type;
};

template <typename T>
struct require_result<T>
{
};

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

} // namespace asio
} // namespace boost

#endif // defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_REQUIRE_HPP

/* require.hpp
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
*/