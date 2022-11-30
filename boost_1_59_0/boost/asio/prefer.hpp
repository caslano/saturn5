//
// prefer.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_PREFER_HPP
#define BOOST_ASIO_PREFER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/is_applicable_property.hpp>
#include <boost/asio/traits/prefer_free.hpp>
#include <boost/asio/traits/prefer_member.hpp>
#include <boost/asio/traits/require_free.hpp>
#include <boost/asio/traits/require_member.hpp>
#include <boost/asio/traits/static_require.hpp>

#include <boost/asio/detail/push_options.hpp>

#if defined(GENERATING_DOCUMENTATION)

namespace boost {
namespace asio {

/// A customisation point that attempts to apply a property to an object.
/**
 * The name <tt>prefer</tt> denotes a customisation point object. The
 * expression <tt>boost::asio::prefer(E, P0, Pn...)</tt> for some subexpressions
 * <tt>E</tt> and <tt>P0</tt>, and where <tt>Pn...</tt> represents <tt>N</tt>
 * subexpressions (where <tt>N</tt> is 0 or more, and with types <tt>T =
 * decay_t<decltype(E)></tt> and <tt>Prop0 = decay_t<decltype(P0)></tt>) is
 * expression-equivalent to:
 *
 * @li If <tt>is_applicable_property_v<T, Prop0> && Prop0::is_preferable</tt> is
 *   not a well-formed constant expression with value <tt>true</tt>,
 *   <tt>boost::asio::prefer(E, P0, Pn...)</tt> is ill-formed.
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
 * @li Otherwise, <tt>(E).prefer(P0)</tt> if <tt>N == 0</tt> and the expression
 *   <tt>(E).prefer(P0)</tt> is a valid expression.
 *
 * @li Otherwise, <tt>prefer(E, P0)</tt> if <tt>N == 0</tt> and the expression
 *   <tt>prefer(E, P0)</tt> is a valid expression with overload resolution
 *   performed in a context that does not include the declaration of the
 *   <tt>prefer</tt> customization point object.
 *
 * @li Otherwise, <tt>E</tt> if <tt>N == 0</tt>.
 *
 * @li Otherwise,
 *   <tt>boost::asio::prefer(boost::asio::prefer(E, P0), Pn...)</tt>
 *   if <tt>N > 0</tt> and the expression
 *   <tt>boost::asio::prefer(boost::asio::prefer(E, P0), Pn...)</tt>
 *   is a valid expression.
 *
 * @li Otherwise, <tt>boost::asio::prefer(E, P0, Pn...)</tt> is ill-formed.
 */
inline constexpr unspecified prefer = unspecified;

/// A type trait that determines whether a @c prefer expression is well-formed.
/**
 * Class template @c can_prefer is a trait that is derived from
 * @c true_type if the expression <tt>boost::asio::prefer(std::declval<T>(),
 * std::declval<Properties>()...)</tt> is well formed; otherwise @c false_type.
 */
template <typename T, typename... Properties>
struct can_prefer :
  integral_constant<bool, automatically_determined>
{
};

/// A type trait that determines whether a @c prefer expression will not throw.
/**
 * Class template @c is_nothrow_prefer is a trait that is derived from
 * @c true_type if the expression <tt>boost::asio::prefer(std::declval<T>(),
 * std::declval<Properties>()...)</tt> is @c noexcept; otherwise @c false_type.
 */
template <typename T, typename... Properties>
struct is_nothrow_prefer :
  integral_constant<bool, automatically_determined>
{
};

/// A type trait that determines the result type of a @c prefer expression.
/**
 * Class template @c prefer_result is a trait that determines the result
 * type of the expression <tt>boost::asio::prefer(std::declval<T>(),
 * std::declval<Properties>()...)</tt>.
 */
template <typename T, typename... Properties>
struct prefer_result
{
  /// The result of the @c prefer expression.
  typedef automatically_determined type;
};

} // namespace asio
} // namespace boost

#else // defined(GENERATING_DOCUMENTATION)

namespace boost_asio_prefer_fn {

using boost::asio::conditional;
using boost::asio::decay;
using boost::asio::declval;
using boost::asio::enable_if;
using boost::asio::is_applicable_property;
using boost::asio::traits::prefer_free;
using boost::asio::traits::prefer_member;
using boost::asio::traits::require_free;
using boost::asio::traits::require_member;
using boost::asio::traits::static_require;

void prefer();
void require();

enum overload_type
{
  identity,
  call_require_member,
  call_require_free,
  call_prefer_member,
  call_prefer_free,
  two_props,
  n_props,
  ill_formed
};

template <typename Impl, typename T, typename Properties,
    typename = void, typename = void, typename = void, typename = void,
    typename = void, typename = void, typename = void>
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
    decay<Property>::type::is_preferable
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
    decay<Property>::type::is_preferable
  >::type,
  typename enable_if<
    !static_require<T, Property>::is_valid
  >::type,
  typename enable_if<
    require_member<typename Impl::template proxy<T>::type, Property>::is_valid
  >::type> :
  require_member<typename Impl::template proxy<T>::type, Property>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_require_member);
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
    decay<Property>::type::is_preferable
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
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_require_free);
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
    decay<Property>::type::is_preferable
  >::type,
  typename enable_if<
    !static_require<T, Property>::is_valid
  >::type,
  typename enable_if<
    !require_member<typename Impl::template proxy<T>::type, Property>::is_valid
  >::type,
  typename enable_if<
    !require_free<T, Property>::is_valid
  >::type,
  typename enable_if<
    prefer_member<typename Impl::template proxy<T>::type, Property>::is_valid
  >::type> :
  prefer_member<typename Impl::template proxy<T>::type, Property>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_prefer_member);
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
    decay<Property>::type::is_preferable
  >::type,
  typename enable_if<
    !static_require<T, Property>::is_valid
  >::type,
  typename enable_if<
    !require_member<typename Impl::template proxy<T>::type, Property>::is_valid
  >::type,
  typename enable_if<
    !require_free<T, Property>::is_valid
  >::type,
  typename enable_if<
    !prefer_member<typename Impl::template proxy<T>::type, Property>::is_valid
  >::type,
  typename enable_if<
    prefer_free<T, Property>::is_valid
  >::type> :
  prefer_free<T, Property>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_prefer_free);
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
    decay<Property>::type::is_preferable
  >::type,
  typename enable_if<
    !static_require<T, Property>::is_valid
  >::type,
  typename enable_if<
    !require_member<typename Impl::template proxy<T>::type, Property>::is_valid
  >::type,
  typename enable_if<
    !require_free<T, Property>::is_valid
  >::type,
  typename enable_if<
    !prefer_member<typename Impl::template proxy<T>::type, Property>::is_valid
  >::type,
  typename enable_if<
    !prefer_free<T, Property>::is_valid
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
#if defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_MEMBER_TRAIT) \
  && defined(BOOST_ASIO_HAS_DEDUCED_PREFER_MEMBER_TRAIT)
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

      template <typename P>
      auto prefer(BOOST_ASIO_MOVE_ARG(P) p)
        noexcept(
          noexcept(
            declval<typename conditional<true, T, P>::type>().prefer(
              BOOST_ASIO_MOVE_CAST(P)(p))
          )
        )
        -> decltype(
          declval<typename conditional<true, T, P>::type>().prefer(
            BOOST_ASIO_MOVE_CAST(P)(p))
        );
    };
#else // defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_MEMBER_TRAIT)
      //   && defined(BOOST_ASIO_HAS_DEDUCED_PREFER_MEMBER_TRAIT)
    typedef T type;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_MEMBER_TRAIT)
       //   && defined(BOOST_ASIO_HAS_DEDUCED_PREFER_MEMBER_TRAIT)
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
    call_traits<impl, T, void(Property)>::overload == call_require_member,
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
    call_traits<impl, T, void(Property)>::overload == call_require_free,
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

  template <typename T, typename Property>
  BOOST_ASIO_NODISCARD BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<impl, T, void(Property)>::overload == call_prefer_member,
    typename call_traits<impl, T, void(Property)>::result_type
  >::type
  operator()(
      BOOST_ASIO_MOVE_ARG(T) t,
      BOOST_ASIO_MOVE_ARG(Property) p) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<impl, T, void(Property)>::is_noexcept))
  {
    return BOOST_ASIO_MOVE_CAST(T)(t).prefer(
        BOOST_ASIO_MOVE_CAST(Property)(p));
  }

  template <typename T, typename Property>
  BOOST_ASIO_NODISCARD BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<impl, T, void(Property)>::overload == call_prefer_free,
    typename call_traits<impl, T, void(Property)>::result_type
  >::type
  operator()(
      BOOST_ASIO_MOVE_ARG(T) t,
      BOOST_ASIO_MOVE_ARG(Property) p) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<impl, T, void(Property)>::is_noexcept))
  {
    return prefer(
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

} // namespace boost_asio_prefer_fn
namespace boost {
namespace asio {
namespace {

static BOOST_ASIO_CONSTEXPR const boost_asio_prefer_fn::impl&
  prefer = boost_asio_prefer_fn::static_instance<>::instance;

} // namespace

typedef boost_asio_prefer_fn::impl prefer_t;

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T, typename... Properties>
struct can_prefer :
  integral_constant<bool,
    boost_asio_prefer_fn::call_traits<
      prefer_t, T, void(Properties...)>::overload
        != boost_asio_prefer_fn::ill_formed>
{
};

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T, typename P0 = void,
    typename P1 = void, typename P2 = void>
struct can_prefer :
  integral_constant<bool,
    boost_asio_prefer_fn::call_traits<
      prefer_t, T, void(P0, P1, P2)>::overload
        != boost_asio_prefer_fn::ill_formed>
{
};

template <typename T, typename P0, typename P1>
struct can_prefer<T, P0, P1> :
  integral_constant<bool,
    boost_asio_prefer_fn::call_traits<
      prefer_t, T, void(P0, P1)>::overload
        != boost_asio_prefer_fn::ill_formed>
{
};

template <typename T, typename P0>
struct can_prefer<T, P0> :
  integral_constant<bool,
    boost_asio_prefer_fn::call_traits<
      prefer_t, T, void(P0)>::overload
        != boost_asio_prefer_fn::ill_formed>
{
};

template <typename T>
struct can_prefer<T> :
  false_type
{
};

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T, typename BOOST_ASIO_ELLIPSIS Properties>
constexpr bool can_prefer_v
  = can_prefer<T, Properties BOOST_ASIO_ELLIPSIS>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T, typename... Properties>
struct is_nothrow_prefer :
  integral_constant<bool,
    boost_asio_prefer_fn::call_traits<
      prefer_t, T, void(Properties...)>::is_noexcept>
{
};

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T, typename P0 = void,
    typename P1 = void, typename P2 = void>
struct is_nothrow_prefer :
  integral_constant<bool,
    boost_asio_prefer_fn::call_traits<
      prefer_t, T, void(P0, P1, P2)>::is_noexcept>
{
};

template <typename T, typename P0, typename P1>
struct is_nothrow_prefer<T, P0, P1> :
  integral_constant<bool,
    boost_asio_prefer_fn::call_traits<
      prefer_t, T, void(P0, P1)>::is_noexcept>
{
};

template <typename T, typename P0>
struct is_nothrow_prefer<T, P0> :
  integral_constant<bool,
    boost_asio_prefer_fn::call_traits<
      prefer_t, T, void(P0)>::is_noexcept>
{
};

template <typename T>
struct is_nothrow_prefer<T> :
  false_type
{
};

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T, typename BOOST_ASIO_ELLIPSIS Properties>
constexpr bool is_nothrow_prefer_v
  = is_nothrow_prefer<T, Properties BOOST_ASIO_ELLIPSIS>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T, typename... Properties>
struct prefer_result
{
  typedef typename boost_asio_prefer_fn::call_traits<
      prefer_t, T, void(Properties...)>::result_type type;
};

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T, typename P0 = void,
    typename P1 = void, typename P2 = void>
struct prefer_result
{
  typedef typename boost_asio_prefer_fn::call_traits<
      prefer_t, T, void(P0, P1, P2)>::result_type type;
};

template <typename T, typename P0, typename P1>
struct prefer_result<T, P0, P1>
{
  typedef typename boost_asio_prefer_fn::call_traits<
      prefer_t, T, void(P0, P1)>::result_type type;
};

template <typename T, typename P0>
struct prefer_result<T, P0>
{
  typedef typename boost_asio_prefer_fn::call_traits<
      prefer_t, T, void(P0)>::result_type type;
};

template <typename T>
struct prefer_result<T>
{
};

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

} // namespace asio
} // namespace boost

#endif // defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_PREFER_HPP

/* prefer.hpp
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
*/