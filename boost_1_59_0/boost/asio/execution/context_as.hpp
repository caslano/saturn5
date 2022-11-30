//
// execution/context_as.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_CONTEXT_AS_HPP
#define BOOST_ASIO_EXECUTION_CONTEXT_AS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution/context.hpp>
#include <boost/asio/execution/executor.hpp>
#include <boost/asio/execution/scheduler.hpp>
#include <boost/asio/execution/sender.hpp>
#include <boost/asio/is_applicable_property.hpp>
#include <boost/asio/query.hpp>
#include <boost/asio/traits/query_static_constexpr_member.hpp>
#include <boost/asio/traits/static_query.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if defined(GENERATING_DOCUMENTATION)

namespace execution {

/// A property that is used to obtain the execution context that is associated
/// with an executor.
template <typename U>
struct context_as_t
{
  /// The context_as_t property applies to executors, senders, and schedulers.
  template <typename T>
  static constexpr bool is_applicable_property_v =
    is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

  /// The context_t property cannot be required.
  static constexpr bool is_requirable = false;

  /// The context_t property cannot be preferred.
  static constexpr bool is_preferable = false;

  /// The type returned by queries against an @c any_executor.
  typedef T polymorphic_query_result_type;
};

/// A special value used for accessing the context_as_t property.
template <typename U>
constexpr context_as_t context_as;

} // namespace execution

#else // defined(GENERATING_DOCUMENTATION)

namespace execution {

template <typename T>
struct context_as_t
{
#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)
  template <typename U>
  BOOST_ASIO_STATIC_CONSTEXPR(bool,
    is_applicable_property_v = (
      is_executor<U>::value
        || conditional<
            is_executor<U>::value,
            false_type,
            is_sender<U>
          >::type::value
        || conditional<
            is_executor<U>::value,
            false_type,
            is_scheduler<U>
          >::type::value));
#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_requirable = false);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_preferable = false);

  typedef T polymorphic_query_result_type;

  BOOST_ASIO_CONSTEXPR context_as_t()
  {
  }

  BOOST_ASIO_CONSTEXPR context_as_t(context_t)
  {
  }

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
  template <typename E>
  static BOOST_ASIO_CONSTEXPR
  typename context_t::query_static_constexpr_member<E>::result_type
  static_query()
    BOOST_ASIO_NOEXCEPT_IF((
      context_t::query_static_constexpr_member<E>::is_noexcept))
  {
    return context_t::query_static_constexpr_member<E>::value();
  }

  template <typename E, typename U = decltype(context_as_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const U static_query_v
    = context_as_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  template <typename Executor, typename U>
  friend BOOST_ASIO_CONSTEXPR U query(
      const Executor& ex, const context_as_t<U>&,
      typename enable_if<
        is_same<T, U>::value
      >::type* = 0,
      typename enable_if<
        can_query<const Executor&, const context_t&>::value
      >::type* = 0)
#if !defined(__clang__) // Clang crashes if noexcept is used here.
#if defined(BOOST_ASIO_MSVC) // Visual C++ wants the type to be qualified.
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, const context_t&>::value))
#else // defined(BOOST_ASIO_MSVC)
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, const context_t&>::value))
#endif // defined(BOOST_ASIO_MSVC)
#endif // !defined(__clang__)
  {
    return boost::asio::query(ex, context);
  }
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <typename T> template <typename E, typename U>
const U context_as_t<T>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

#if (defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES) \
    && defined(BOOST_ASIO_HAS_CONSTEXPR)) \
  || defined(GENERATING_DOCUMENTATION)
template <typename T>
constexpr context_as_t<T> context_as{};
#endif // (defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)
       //     && defined(BOOST_ASIO_HAS_CONSTEXPR))
       //   || defined(GENERATING_DOCUMENTATION)

} // namespace execution

#if !defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T, typename U>
struct is_applicable_property<T, execution::context_as_t<U> >
  : integral_constant<bool,
      execution::is_executor<T>::value
        || conditional<
            execution::is_executor<T>::value,
            false_type,
            execution::is_sender<T>
          >::type::value
        || conditional<
            execution::is_executor<T>::value,
            false_type,
            execution::is_scheduler<T>
          >::type::value>
{
};

#endif // !defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

namespace traits {

#if !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  || !defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

template <typename T, typename U>
struct static_query<T, execution::context_as_t<U>,
  typename enable_if<
    static_query<T, execution::context_t>::is_valid
  >::type> : static_query<T, execution::context_t>
{
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   || !defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

#if !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_FREE_TRAIT)

template <typename T, typename U>
struct query_free<T, execution::context_as_t<U>,
    typename enable_if<
      can_query<const T&, const execution::context_t&>::value
    >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    (is_nothrow_query<const T&, const execution::context_t&>::value));

  typedef U result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_FREE_TRAIT)

} // namespace traits

#endif // defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_CONTEXT_AS_HPP

/* context_as.hpp
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
*/