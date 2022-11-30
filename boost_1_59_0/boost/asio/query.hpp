//
// query.hpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_QUERY_HPP
#define BOOST_ASIO_QUERY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/is_applicable_property.hpp>
#include <boost/asio/traits/query_member.hpp>
#include <boost/asio/traits/query_free.hpp>
#include <boost/asio/traits/static_query.hpp>

#include <boost/asio/detail/push_options.hpp>

#if defined(GENERATING_DOCUMENTATION)

namespace boost {
namespace asio {

/// A customisation point that queries the value of a property.
/**
 * The name <tt>query</tt> denotes a customization point object. The
 * expression <tt>boost::asio::query(E, P)</tt> for some
 * subexpressions <tt>E</tt> and <tt>P</tt> (with types <tt>T =
 * decay_t<decltype(E)></tt> and <tt>Prop = decay_t<decltype(P)></tt>) is
 * expression-equivalent to:
 *
 * @li If <tt>is_applicable_property_v<T, Prop></tt> is not a well-formed
 *   constant expression with value <tt>true</tt>, <tt>boost::asio::query(E,
 *   P)</tt> is ill-formed.
 *
 * @li Otherwise, <tt>Prop::template static_query_v<T></tt> if the expression
 *   <tt>Prop::template static_query_v<T></tt> is a well-formed constant
 *   expression.
 *
 * @li Otherwise, <tt>(E).query(P)</tt> if the expression
 *   <tt>(E).query(P)</tt> is well-formed.
 *
 * @li Otherwise, <tt>query(E, P)</tt> if the expression
 *   <tt>query(E, P)</tt> is a valid expression with overload
 *   resolution performed in a context that does not include the declaration
 *   of the <tt>query</tt> customization point object.
 *
 * @li Otherwise, <tt>boost::asio::query(E, P)</tt> is ill-formed.
 */
inline constexpr unspecified query = unspecified;

/// A type trait that determines whether a @c query expression is well-formed.
/**
 * Class template @c can_query is a trait that is derived from
 * @c true_type if the expression <tt>boost::asio::query(std::declval<T>(),
 * std::declval<Property>())</tt> is well formed; otherwise @c false_type.
 */
template <typename T, typename Property>
struct can_query :
  integral_constant<bool, automatically_determined>
{
};

/// A type trait that determines whether a @c query expression will
/// not throw.
/**
 * Class template @c is_nothrow_query is a trait that is derived from
 * @c true_type if the expression <tt>boost::asio::query(std::declval<T>(),
 * std::declval<Property>())</tt> is @c noexcept; otherwise @c false_type.
 */
template <typename T, typename Property>
struct is_nothrow_query :
  integral_constant<bool, automatically_determined>
{
};

/// A type trait that determines the result type of a @c query expression.
/**
 * Class template @c query_result is a trait that determines the result
 * type of the expression <tt>boost::asio::query(std::declval<T>(),
 * std::declval<Property>())</tt>.
 */
template <typename T, typename Property>
struct query_result
{
  /// The result of the @c query expression.
  typedef automatically_determined type;
};

} // namespace asio
} // namespace boost

#else // defined(GENERATING_DOCUMENTATION)

namespace boost_asio_query_fn {

using boost::asio::conditional;
using boost::asio::decay;
using boost::asio::declval;
using boost::asio::enable_if;
using boost::asio::is_applicable_property;
using boost::asio::traits::query_free;
using boost::asio::traits::query_member;
using boost::asio::traits::static_query;

void query();

enum overload_type
{
  static_value,
  call_member,
  call_free,
  ill_formed
};

template <typename Impl, typename T, typename Properties,
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
    static_query<T, Property>::is_valid
  >::type> :
  static_query<T, Property>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = static_value);
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
    !static_query<T, Property>::is_valid
  >::type,
  typename enable_if<
    query_member<typename Impl::template proxy<T>::type, Property>::is_valid
  >::type> :
  query_member<typename Impl::template proxy<T>::type, Property>
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
    !static_query<T, Property>::is_valid
  >::type,
  typename enable_if<
    !query_member<typename Impl::template proxy<T>::type, Property>::is_valid
  >::type,
  typename enable_if<
    query_free<T, Property>::is_valid
  >::type> :
  query_free<T, Property>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_free);
};

struct impl
{
  template <typename T>
  struct proxy
  {
#if defined(BOOST_ASIO_HAS_DEDUCED_QUERY_MEMBER_TRAIT)
    struct type
    {
      template <typename P>
      auto query(BOOST_ASIO_MOVE_ARG(P) p)
        noexcept(
          noexcept(
            declval<typename conditional<true, T, P>::type>().query(
              BOOST_ASIO_MOVE_CAST(P)(p))
          )
        )
        -> decltype(
          declval<typename conditional<true, T, P>::type>().query(
            BOOST_ASIO_MOVE_CAST(P)(p))
        );
    };
#else // defined(BOOST_ASIO_HAS_DEDUCED_QUERY_MEMBER_TRAIT)
    typedef T type;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_QUERY_MEMBER_TRAIT)
  };

  template <typename T, typename Property>
  BOOST_ASIO_NODISCARD BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<impl, T, void(Property)>::overload == static_value,
    typename call_traits<impl, T, void(Property)>::result_type
  >::type
  operator()(
      BOOST_ASIO_MOVE_ARG(T),
      BOOST_ASIO_MOVE_ARG(Property)) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<impl, T, void(Property)>::is_noexcept))
  {
    return static_query<
      typename decay<T>::type,
      typename decay<Property>::type
    >::value();
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
    return BOOST_ASIO_MOVE_CAST(T)(t).query(BOOST_ASIO_MOVE_CAST(Property)(p));
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
    return query(BOOST_ASIO_MOVE_CAST(T)(t), BOOST_ASIO_MOVE_CAST(Property)(p));
  }
};

template <typename T = impl>
struct static_instance
{
  static const T instance;
};

template <typename T>
const T static_instance<T>::instance = {};

} // namespace boost_asio_query_fn
namespace boost {
namespace asio {
namespace {

static BOOST_ASIO_CONSTEXPR const boost_asio_query_fn::impl&
  query = boost_asio_query_fn::static_instance<>::instance;

} // namespace

typedef boost_asio_query_fn::impl query_t;

template <typename T, typename Property>
struct can_query :
  integral_constant<bool,
    boost_asio_query_fn::call_traits<query_t, T, void(Property)>::overload !=
      boost_asio_query_fn::ill_formed>
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T, typename Property>
constexpr bool can_query_v
  = can_query<T, Property>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T, typename Property>
struct is_nothrow_query :
  integral_constant<bool,
    boost_asio_query_fn::call_traits<query_t, T, void(Property)>::is_noexcept>
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T, typename Property>
constexpr bool is_nothrow_query_v
  = is_nothrow_query<T, Property>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T, typename Property>
struct query_result
{
  typedef typename boost_asio_query_fn::call_traits<
      query_t, T, void(Property)>::result_type type;
};

} // namespace asio
} // namespace boost

#endif // defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_QUERY_HPP

/* query.hpp
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
*/