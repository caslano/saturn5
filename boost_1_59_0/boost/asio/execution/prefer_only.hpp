//
// execution/prefer_only.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_PREFER_ONLY_HPP
#define BOOST_ASIO_EXECUTION_PREFER_ONLY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/is_applicable_property.hpp>
#include <boost/asio/prefer.hpp>
#include <boost/asio/query.hpp>
#include <boost/asio/traits/static_query.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if defined(GENERATING_DOCUMENTATION)

namespace execution {

/// A property adapter that is used with the polymorphic executor wrapper
/// to mark properties as preferable, but not requirable.
template <typename Property>
struct prefer_only
{
  /// The prefer_only adapter applies to the same types as the nested property.
  template <typename T>
  static constexpr bool is_applicable_property_v =
    is_applicable_property<T, Property>::value;

  /// The context_t property cannot be required.
  static constexpr bool is_requirable = false;

  /// The context_t property can be preferred, it the underlying property can
  /// be preferred.
  /**
   * @c true if @c Property::is_preferable is @c true, otherwise @c false.
   */
  static constexpr bool is_preferable = automatically_determined;

  /// The type returned by queries against an @c any_executor.
  typedef typename Property::polymorphic_query_result_type
    polymorphic_query_result_type;
};

} // namespace execution

#else // defined(GENERATING_DOCUMENTATION)

namespace execution {
namespace detail {

template <typename InnerProperty, typename = void>
struct prefer_only_is_preferable
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_preferable = false);
};

template <typename InnerProperty>
struct prefer_only_is_preferable<InnerProperty,
    typename enable_if<
      InnerProperty::is_preferable
    >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_preferable = true);
};

template <typename InnerProperty, typename = void>
struct prefer_only_polymorphic_query_result_type
{
};

template <typename InnerProperty>
struct prefer_only_polymorphic_query_result_type<InnerProperty,
    typename void_type<
      typename InnerProperty::polymorphic_query_result_type
    >::type>
{
  typedef typename InnerProperty::polymorphic_query_result_type
    polymorphic_query_result_type;
};

template <typename InnerProperty, typename = void>
struct prefer_only_property
{
  InnerProperty property;

  prefer_only_property(const InnerProperty& p)
    : property(p)
  {
  }
};

#if defined(BOOST_ASIO_HAS_DECLTYPE) \
  && defined(BOOST_ASIO_HAS_WORKING_EXPRESSION_SFINAE)

template <typename InnerProperty>
struct prefer_only_property<InnerProperty,
    typename void_type<
      decltype(boost::asio::declval<const InnerProperty>().value())
    >::type>
{
  InnerProperty property;

  prefer_only_property(const InnerProperty& p)
    : property(p)
  {
  }

  BOOST_ASIO_CONSTEXPR auto value() const
    BOOST_ASIO_NOEXCEPT_IF((
      noexcept(boost::asio::declval<const InnerProperty>().value())))
    -> decltype(boost::asio::declval<const InnerProperty>().value())
  {
    return property.value();
  }
};

#else // defined(BOOST_ASIO_HAS_DECLTYPE)
      //   && defined(BOOST_ASIO_HAS_WORKING_EXPRESSION_SFINAE)

struct prefer_only_memfns_base
{
  void value();
};

template <typename T>
struct prefer_only_memfns_derived
  : T, prefer_only_memfns_base
{
};

template <typename T, T>
struct prefer_only_memfns_check
{
};

template <typename>
char (&prefer_only_value_memfn_helper(...))[2];

template <typename T>
char prefer_only_value_memfn_helper(
    prefer_only_memfns_check<
      void (prefer_only_memfns_base::*)(),
      &prefer_only_memfns_derived<T>::value>*);

template <typename InnerProperty>
struct prefer_only_property<InnerProperty,
    typename enable_if<
      sizeof(prefer_only_value_memfn_helper<InnerProperty>(0)) != 1
        && !is_same<typename InnerProperty::polymorphic_query_result_type,
          void>::value
    >::type>
{
  InnerProperty property;

  prefer_only_property(const InnerProperty& p)
    : property(p)
  {
  }

  BOOST_ASIO_CONSTEXPR typename InnerProperty::polymorphic_query_result_type
  value() const
  {
    return property.value();
  }
};

#endif // defined(BOOST_ASIO_HAS_DECLTYPE)
       //   && defined(BOOST_ASIO_HAS_WORKING_EXPRESSION_SFINAE)

} // namespace detail

template <typename InnerProperty>
struct prefer_only :
  detail::prefer_only_is_preferable<InnerProperty>,
  detail::prefer_only_polymorphic_query_result_type<InnerProperty>,
  detail::prefer_only_property<InnerProperty>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_requirable = false);

  BOOST_ASIO_CONSTEXPR prefer_only(const InnerProperty& p)
    : detail::prefer_only_property<InnerProperty>(p)
  {
  }

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
  template <typename T>
  static BOOST_ASIO_CONSTEXPR
  typename traits::static_query<T, InnerProperty>::result_type
  static_query()
    BOOST_ASIO_NOEXCEPT_IF((
      traits::static_query<T, InnerProperty>::is_noexcept))
  {
    return traits::static_query<T, InnerProperty>::value();
  }

  template <typename E, typename T = decltype(prefer_only::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = prefer_only::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  template <typename Executor, typename Property>
  friend BOOST_ASIO_CONSTEXPR
  typename prefer_result<const Executor&, const InnerProperty&>::type
  prefer(const Executor& ex, const prefer_only<Property>& p,
      typename enable_if<
        is_same<Property, InnerProperty>::value
      >::type* = 0,
      typename enable_if<
        can_prefer<const Executor&, const InnerProperty&>::value
      >::type* = 0)
#if !defined(BOOST_ASIO_MSVC) \
  && !defined(__clang__) // Clang crashes if noexcept is used here.
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_prefer<const Executor&, const InnerProperty&>::value))
#endif // !defined(BOOST_ASIO_MSVC)
       //   && !defined(__clang__)
  {
    return boost::asio::prefer(ex, p.property);
  }

  template <typename Executor, typename Property>
  friend BOOST_ASIO_CONSTEXPR
  typename query_result<const Executor&, const InnerProperty&>::type
  query(const Executor& ex, const prefer_only<Property>& p,
      typename enable_if<
        is_same<Property, InnerProperty>::value
      >::type* = 0,
      typename enable_if<
        can_query<const Executor&, const InnerProperty&>::value
      >::type* = 0)
#if !defined(BOOST_ASIO_MSVC) \
  && !defined(__clang__) // Clang crashes if noexcept is used here.
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, const InnerProperty&>::value))
#endif // !defined(BOOST_ASIO_MSVC)
       //   && !defined(__clang__)
  {
    return boost::asio::query(ex, p.property);
  }
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <typename InnerProperty> template <typename E, typename T>
const T prefer_only<InnerProperty>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

} // namespace execution

template <typename T, typename InnerProperty>
struct is_applicable_property<T, execution::prefer_only<InnerProperty> >
  : is_applicable_property<T, InnerProperty>
{
};

namespace traits {

#if !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  || !defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

template <typename T, typename InnerProperty>
struct static_query<T, execution::prefer_only<InnerProperty> > :
  static_query<T, const InnerProperty&>
{
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   || !defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

#if !defined(BOOST_ASIO_HAS_DEDUCED_PREFER_FREE_TRAIT)

template <typename T, typename InnerProperty>
struct prefer_free_default<T, execution::prefer_only<InnerProperty>,
    typename enable_if<
      can_prefer<const T&, const InnerProperty&>::value
    >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    (is_nothrow_prefer<const T&, const InnerProperty&>::value));

  typedef typename prefer_result<const T&,
      const InnerProperty&>::type result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_PREFER_FREE_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_FREE_TRAIT)

template <typename T, typename InnerProperty>
struct query_free<T, execution::prefer_only<InnerProperty>,
    typename enable_if<
      can_query<const T&, const InnerProperty&>::value
    >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    (is_nothrow_query<const T&, const InnerProperty&>::value));

  typedef typename query_result<const T&,
      const InnerProperty&>::type result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_FREE_TRAIT)

} // namespace traits

#endif // defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_PREFER_ONLY_HPP

/* prefer_only.hpp
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
*/