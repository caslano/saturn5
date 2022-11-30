//
// require_concept.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_REQUIRE_CONCEPT_HPP
#define BOOST_ASIO_REQUIRE_CONCEPT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/is_applicable_property.hpp>
#include <boost/asio/traits/require_concept_member.hpp>
#include <boost/asio/traits/require_concept_free.hpp>
#include <boost/asio/traits/static_require_concept.hpp>

#include <boost/asio/detail/push_options.hpp>

#if defined(GENERATING_DOCUMENTATION)

namespace boost {
namespace asio {

/// A customisation point that applies a concept-enforcing property to an
/// object.
/**
 * The name <tt>require_concept</tt> denotes a customization point object. The
 * expression <tt>boost::asio::require_concept(E, P)</tt> for some
 * subexpressions <tt>E</tt> and <tt>P</tt> (with types <tt>T =
 * decay_t<decltype(E)></tt> and <tt>Prop = decay_t<decltype(P)></tt>) is
 * expression-equivalent to:
 *
 * @li If <tt>is_applicable_property_v<T, Prop> &&
 *   Prop::is_requirable_concept</tt> is not a well-formed constant expression
 *   with value <tt>true</tt>, <tt>boost::asio::require_concept(E, P)</tt> is
 *   ill-formed.
 *
 * @li Otherwise, <tt>E</tt> if the expression <tt>Prop::template
 *   static_query_v<T> == Prop::value()</tt> is a well-formed constant
 *   expression with value <tt>true</tt>.
 *
 * @li Otherwise, <tt>(E).require_concept(P)</tt> if the expression
 *   <tt>(E).require_concept(P)</tt> is well-formed.
 *
 * @li Otherwise, <tt>require_concept(E, P)</tt> if the expression
 *   <tt>require_concept(E, P)</tt> is a valid expression with overload
 *   resolution performed in a context that does not include the declaration
 *   of the <tt>require_concept</tt> customization point object.
 *
 * @li Otherwise, <tt>boost::asio::require_concept(E, P)</tt> is ill-formed.
 */
inline constexpr unspecified require_concept = unspecified;

/// A type trait that determines whether a @c require_concept expression is
/// well-formed.
/**
 * Class template @c can_require_concept is a trait that is derived from
 * @c true_type if the expression
 * <tt>boost::asio::require_concept(std::declval<T>(),
 * std::declval<Property>())</tt> is well formed; otherwise @c false_type.
 */
template <typename T, typename Property>
struct can_require_concept :
  integral_constant<bool, automatically_determined>
{
};

/// A type trait that determines whether a @c require_concept expression will
/// not throw.
/**
 * Class template @c is_nothrow_require_concept is a trait that is derived from
 * @c true_type if the expression
 * <tt>boost::asio::require_concept(std::declval<T>(),
 * std::declval<Property>())</tt> is @c noexcept; otherwise @c false_type.
 */
template <typename T, typename Property>
struct is_nothrow_require_concept :
  integral_constant<bool, automatically_determined>
{
};

/// A type trait that determines the result type of a @c require_concept
/// expression.
/**
 * Class template @c require_concept_result is a trait that determines the
 * result type of the expression
 * <tt>boost::asio::require_concept(std::declval<T>(),
 * std::declval<Property>())</tt>.
 */
template <typename T, typename Property>
struct require_concept_result
{
  /// The result of the @c require_concept expression.
  typedef automatically_determined type;
};

} // namespace asio
} // namespace boost

#else // defined(GENERATING_DOCUMENTATION)

namespace boost_asio_require_concept_fn {

using boost::asio::conditional;
using boost::asio::decay;
using boost::asio::declval;
using boost::asio::enable_if;
using boost::asio::is_applicable_property;
using boost::asio::traits::require_concept_free;
using boost::asio::traits::require_concept_member;
using boost::asio::traits::static_require_concept;

void require_concept();

enum overload_type
{
  identity,
  call_member,
  call_free,
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
    decay<Property>::type::is_requirable_concept
  >::type,
  typename enable_if<
    static_require_concept<T, Property>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = identity);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef BOOST_ASIO_MOVE_ARG(T) result_type;
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
    decay<Property>::type::is_requirable_concept
  >::type,
  typename enable_if<
    !static_require_concept<T, Property>::is_valid
  >::type,
  typename enable_if<
    require_concept_member<
      typename Impl::template proxy<T>::type,
      Property
    >::is_valid
  >::type> :
  require_concept_member<
    typename Impl::template proxy<T>::type,
    Property
  >
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
    decay<Property>::type::is_requirable_concept
  >::type,
  typename enable_if<
    !static_require_concept<T, Property>::is_valid
  >::type,
  typename enable_if<
    !require_concept_member<
      typename Impl::template proxy<T>::type,
      Property
    >::is_valid
  >::type,
  typename enable_if<
    require_concept_free<T, Property>::is_valid
  >::type> :
  require_concept_free<T, Property>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_free);
};

struct impl
{
  template <typename T>
  struct proxy
  {
#if defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_CONCEPT_MEMBER_TRAIT)
    struct type
    {
      template <typename P>
      auto require_concept(BOOST_ASIO_MOVE_ARG(P) p)
        noexcept(
          noexcept(
            declval<typename conditional<true, T, P>::type>().require_concept(
              BOOST_ASIO_MOVE_CAST(P)(p))
          )
        )
        -> decltype(
          declval<typename conditional<true, T, P>::type>().require_concept(
            BOOST_ASIO_MOVE_CAST(P)(p))
        );
    };
#else // defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_CONCEPT_MEMBER_TRAIT)
    typedef T type;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_CONCEPT_MEMBER_TRAIT)
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
    return BOOST_ASIO_MOVE_CAST(T)(t).require_concept(
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
    return require_concept(
        BOOST_ASIO_MOVE_CAST(T)(t),
        BOOST_ASIO_MOVE_CAST(Property)(p));
  }
};

template <typename T = impl>
struct static_instance
{
  static const T instance;
};

template <typename T>
const T static_instance<T>::instance = {};

} // namespace boost_asio_require_concept_fn
namespace boost {
namespace asio {
namespace {

static BOOST_ASIO_CONSTEXPR const boost_asio_require_concept_fn::impl&
  require_concept = boost_asio_require_concept_fn::static_instance<>::instance;

} // namespace

typedef boost_asio_require_concept_fn::impl require_concept_t;

template <typename T, typename Property>
struct can_require_concept :
  integral_constant<bool,
    boost_asio_require_concept_fn::call_traits<
      require_concept_t, T, void(Property)>::overload !=
        boost_asio_require_concept_fn::ill_formed>
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T, typename Property>
constexpr bool can_require_concept_v
  = can_require_concept<T, Property>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T, typename Property>
struct is_nothrow_require_concept :
  integral_constant<bool,
    boost_asio_require_concept_fn::call_traits<
      require_concept_t, T, void(Property)>::is_noexcept>
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T, typename Property>
constexpr bool is_nothrow_require_concept_v
  = is_nothrow_require_concept<T, Property>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T, typename Property>
struct require_concept_result
{
  typedef typename boost_asio_require_concept_fn::call_traits<
      require_concept_t, T, void(Property)>::result_type type;
};

} // namespace asio
} // namespace boost

#endif // defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_REQUIRE_CONCEPT_HPP

/* require_concept.hpp
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
*/