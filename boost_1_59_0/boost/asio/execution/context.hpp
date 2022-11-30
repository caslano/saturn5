//
// execution/context.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_CONTEXT2_HPP
#define BOOST_ASIO_EXECUTION_CONTEXT2_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution/executor.hpp>
#include <boost/asio/execution/scheduler.hpp>
#include <boost/asio/execution/sender.hpp>
#include <boost/asio/is_applicable_property.hpp>
#include <boost/asio/traits/query_static_constexpr_member.hpp>
#include <boost/asio/traits/static_query.hpp>

#if defined(BOOST_ASIO_HAS_STD_ANY)
# include <any>
#endif // defined(BOOST_ASIO_HAS_STD_ANY)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if defined(GENERATING_DOCUMENTATION)

namespace execution {

/// A property that is used to obtain the execution context that is associated
/// with an executor.
struct context_t
{
  /// The context_t property applies to executors, senders, and schedulers.
  template <typename T>
  static constexpr bool is_applicable_property_v =
    is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

  /// The context_t property cannot be required.
  static constexpr bool is_requirable = false;

  /// The context_t property cannot be preferred.
  static constexpr bool is_preferable = false;

  /// The type returned by queries against an @c any_executor.
  typedef std::any polymorphic_query_result_type;
};

/// A special value used for accessing the context_t property.
constexpr context_t context;

} // namespace execution

#else // defined(GENERATING_DOCUMENTATION)

namespace execution {
namespace detail {

template <int I = 0>
struct context_t
{
#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)
  template <typename T>
  BOOST_ASIO_STATIC_CONSTEXPR(bool,
    is_applicable_property_v = (
      is_executor<T>::value
        || conditional<
            is_executor<T>::value,
            false_type,
            is_sender<T>
          >::type::value
        || conditional<
            is_executor<T>::value,
            false_type,
            is_scheduler<T>
          >::type::value));
#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_requirable = false);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_preferable = false);

#if defined(BOOST_ASIO_HAS_STD_ANY)
  typedef std::any polymorphic_query_result_type;
#endif // defined(BOOST_ASIO_HAS_STD_ANY)

  BOOST_ASIO_CONSTEXPR context_t()
  {
  }

  template <typename T>
  struct static_proxy
  {
#if defined(BOOST_ASIO_HAS_DEDUCED_QUERY_STATIC_CONSTEXPR_MEMBER_TRAIT)
    struct type
    {
      template <typename P>
      static constexpr auto query(BOOST_ASIO_MOVE_ARG(P) p)
        noexcept(
          noexcept(
            conditional<true, T, P>::type::query(BOOST_ASIO_MOVE_CAST(P)(p))
          )
        )
        -> decltype(
          conditional<true, T, P>::type::query(BOOST_ASIO_MOVE_CAST(P)(p))
        )
      {
        return T::query(BOOST_ASIO_MOVE_CAST(P)(p));
      }
    };
#else // defined(BOOST_ASIO_HAS_DEDUCED_QUERY_STATIC_CONSTEXPR_MEMBER_TRAIT)
    typedef T type;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_QUERY_STATIC_CONSTEXPR_MEMBER_TRAIT)
  };

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename static_proxy<T>::type, context_t> {};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
  template <typename T>
  static BOOST_ASIO_CONSTEXPR
  typename query_static_constexpr_member<T>::result_type
  static_query()
    BOOST_ASIO_NOEXCEPT_IF((
      query_static_constexpr_member<T>::is_noexcept))
  {
    return query_static_constexpr_member<T>::value();
  }

  template <typename E, typename T = decltype(context_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = context_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

#if !defined(BOOST_ASIO_HAS_CONSTEXPR)
  static const context_t instance;
#endif // !defined(BOOST_ASIO_HAS_CONSTEXPR)
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <int I> template <typename E, typename T>
const T context_t<I>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

#if !defined(BOOST_ASIO_HAS_CONSTEXPR)
template <int I>
const context_t<I> context_t<I>::instance;
#endif

} // namespace detail

typedef detail::context_t<> context_t;

#if defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
constexpr context_t context;
#else // defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
namespace { static const context_t& context = context_t::instance; }
#endif

} // namespace execution

#if !defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T>
struct is_applicable_property<T, execution::context_t>
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

template <typename T>
struct static_query<T, execution::context_t,
  typename enable_if<
    execution::detail::context_t<0>::
      query_static_constexpr_member<T>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename execution::detail::context_t<0>::
    query_static_constexpr_member<T>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return execution::detail::context_t<0>::
      query_static_constexpr_member<T>::value();
  }
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   || !defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

} // namespace traits

#endif // defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_CONTEXT2_HPP

/* context.hpp
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
*/