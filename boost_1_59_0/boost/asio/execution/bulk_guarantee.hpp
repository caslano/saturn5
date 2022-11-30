//
// execution/bulk_guarantee.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_BULK_GUARANTEE_HPP
#define BOOST_ASIO_EXECUTION_BULK_GUARANTEE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution/executor.hpp>
#include <boost/asio/execution/scheduler.hpp>
#include <boost/asio/execution/sender.hpp>
#include <boost/asio/is_applicable_property.hpp>
#include <boost/asio/query.hpp>
#include <boost/asio/traits/query_free.hpp>
#include <boost/asio/traits/query_member.hpp>
#include <boost/asio/traits/query_static_constexpr_member.hpp>
#include <boost/asio/traits/static_query.hpp>
#include <boost/asio/traits/static_require.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if defined(GENERATING_DOCUMENTATION)

namespace execution {

/// A property to communicate the forward progress and ordering guarantees of
/// execution agents associated with the bulk execution.
struct bulk_guarantee_t
{
  /// The bulk_guarantee_t property applies to executors, senders, and
  /// schedulers.
  template <typename T>
  static constexpr bool is_applicable_property_v =
    is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

  /// The top-level bulk_guarantee_t property cannot be required.
  static constexpr bool is_requirable = false;

  /// The top-level bulk_guarantee_t property cannot be preferred.
  static constexpr bool is_preferable = false;

  /// The type returned by queries against an @c any_executor.
  typedef bulk_guarantee_t polymorphic_query_result_type;

  /// A sub-property that indicates that execution agents within the same bulk
  /// execution may be parallelised and vectorised.
  struct unsequenced_t
  {
    /// The bulk_guarantee_t::unsequenced_t property applies to executors,
    /// senders, and schedulers.
    template <typename T>
    static constexpr bool is_applicable_property_v =
      is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

    /// The bulk_guarantee_t::unsequenced_t property can be required.
    static constexpr bool is_requirable = true;

    /// The bulk_guarantee_t::unsequenced_t property can be preferred.
    static constexpr bool is_preferable = true;

    /// The type returned by queries against an @c any_executor.
    typedef bulk_guarantee_t polymorphic_query_result_type;

    /// Default constructor.
    constexpr unsequenced_t();

    /// Get the value associated with a property object.
    /**
     * @returns unsequenced_t();
     */
    static constexpr bulk_guarantee_t value();
  };

  /// A sub-property that indicates that execution agents within the same bulk
  /// execution may not be parallelised and vectorised.
  struct sequenced_t
  {
    /// The bulk_guarantee_t::sequenced_t property applies to executors,
    /// senders, and schedulers.
    template <typename T>
    static constexpr bool is_applicable_property_v =
      is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

    /// The bulk_guarantee_t::sequenced_t property can be required.
    static constexpr bool is_requirable = true;

    /// The bulk_guarantee_t::sequenced_t property can be preferred.
    static constexpr bool is_preferable = true;

    /// The type returned by queries against an @c any_executor.
    typedef bulk_guarantee_t polymorphic_query_result_type;

    /// Default constructor.
    constexpr sequenced_t();

    /// Get the value associated with a property object.
    /**
     * @returns sequenced_t();
     */
    static constexpr bulk_guarantee_t value();
  };

  /// A sub-property that indicates that execution agents within the same bulk
  /// execution may be parallelised.
  struct parallel_t
  {
    /// The bulk_guarantee_t::parallel_t property applies to executors,
    /// senders, and schedulers.
    template <typename T>
    static constexpr bool is_applicable_property_v =
      is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

    /// The bulk_guarantee_t::parallel_t property can be required.
    static constexpr bool is_requirable = true;

    /// The bulk_guarantee_t::parallel_t property can be preferred.
    static constexpr bool is_preferable = true;

    /// The type returned by queries against an @c any_executor.
    typedef bulk_guarantee_t polymorphic_query_result_type;

    /// Default constructor.
    constexpr parallel_t();

    /// Get the value associated with a property object.
    /**
     * @returns parallel_t();
     */
    static constexpr bulk_guarantee_t value();
  };

  /// A special value used for accessing the bulk_guarantee_t::unsequenced_t
  /// property.
  static constexpr unsequenced_t unsequenced;

  /// A special value used for accessing the bulk_guarantee_t::sequenced_t
  /// property.
  static constexpr sequenced_t sequenced;

  /// A special value used for accessing the bulk_guarantee_t::parallel_t
  /// property.
  static constexpr parallel_t parallel;

  /// Default constructor.
  constexpr bulk_guarantee_t();

  /// Construct from a sub-property value.
  constexpr bulk_guarantee_t(unsequenced_t);

  /// Construct from a sub-property value.
  constexpr bulk_guarantee_t(sequenced_t);

  /// Construct from a sub-property value.
  constexpr bulk_guarantee_t(parallel_t);

  /// Compare property values for equality.
  friend constexpr bool operator==(
      const bulk_guarantee_t& a, const bulk_guarantee_t& b) noexcept;

  /// Compare property values for inequality.
  friend constexpr bool operator!=(
      const bulk_guarantee_t& a, const bulk_guarantee_t& b) noexcept;
};

/// A special value used for accessing the bulk_guarantee_t property.
constexpr bulk_guarantee_t bulk_guarantee;

} // namespace execution

#else // defined(GENERATING_DOCUMENTATION)

namespace execution {
namespace detail {
namespace bulk_guarantee {

template <int I> struct unsequenced_t;
template <int I> struct sequenced_t;
template <int I> struct parallel_t;

} // namespace bulk_guarantee

template <int I = 0>
struct bulk_guarantee_t
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
  typedef bulk_guarantee_t polymorphic_query_result_type;

  typedef detail::bulk_guarantee::unsequenced_t<I> unsequenced_t;
  typedef detail::bulk_guarantee::sequenced_t<I> sequenced_t;
  typedef detail::bulk_guarantee::parallel_t<I> parallel_t;

  BOOST_ASIO_CONSTEXPR bulk_guarantee_t()
    : value_(-1)
  {
  }

  BOOST_ASIO_CONSTEXPR bulk_guarantee_t(unsequenced_t)
    : value_(0)
  {
  }

  BOOST_ASIO_CONSTEXPR bulk_guarantee_t(sequenced_t)
    : value_(1)
  {
  }

  BOOST_ASIO_CONSTEXPR bulk_guarantee_t(parallel_t)
    : value_(2)
  {
  }

  template <typename T>
  struct proxy
  {
#if defined(BOOST_ASIO_HAS_DEDUCED_QUERY_MEMBER_TRAIT)
    struct type
    {
      template <typename P>
      auto query(BOOST_ASIO_MOVE_ARG(P) p) const
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
  struct query_member :
    traits::query_member<typename proxy<T>::type, bulk_guarantee_t> {};

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename static_proxy<T>::type, bulk_guarantee_t> {};

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

  template <typename T>
  static BOOST_ASIO_CONSTEXPR
  typename traits::static_query<T, unsequenced_t>::result_type
  static_query(
      typename enable_if<
        !query_static_constexpr_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !query_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        traits::static_query<T, unsequenced_t>::is_valid
      >::type* = 0) BOOST_ASIO_NOEXCEPT
  {
    return traits::static_query<T, unsequenced_t>::value();
  }

  template <typename T>
  static BOOST_ASIO_CONSTEXPR
  typename traits::static_query<T, sequenced_t>::result_type
  static_query(
      typename enable_if<
        !query_static_constexpr_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !query_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !traits::static_query<T, unsequenced_t>::is_valid
      >::type* = 0,
      typename enable_if<
        traits::static_query<T, sequenced_t>::is_valid
      >::type* = 0) BOOST_ASIO_NOEXCEPT
  {
    return traits::static_query<T, sequenced_t>::value();
  }

  template <typename T>
  static BOOST_ASIO_CONSTEXPR
  typename traits::static_query<T, parallel_t>::result_type
  static_query(
      typename enable_if<
        !query_static_constexpr_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !query_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !traits::static_query<T, unsequenced_t>::is_valid
      >::type* = 0,
      typename enable_if<
        !traits::static_query<T, sequenced_t>::is_valid
      >::type* = 0,
      typename enable_if<
        traits::static_query<T, parallel_t>::is_valid
      >::type* = 0) BOOST_ASIO_NOEXCEPT
  {
    return traits::static_query<T, parallel_t>::value();
  }

  template <typename E,
      typename T = decltype(bulk_guarantee_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = bulk_guarantee_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const bulk_guarantee_t& a, const bulk_guarantee_t& b)
  {
    return a.value_ == b.value_;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const bulk_guarantee_t& a, const bulk_guarantee_t& b)
  {
    return a.value_ != b.value_;
  }

  struct convertible_from_bulk_guarantee_t
  {
    BOOST_ASIO_CONSTEXPR convertible_from_bulk_guarantee_t(bulk_guarantee_t) {}
  };

  template <typename Executor>
  friend BOOST_ASIO_CONSTEXPR bulk_guarantee_t query(
      const Executor& ex, convertible_from_bulk_guarantee_t,
      typename enable_if<
        can_query<const Executor&, unsequenced_t>::value
      >::type* = 0)
#if !defined(__clang__) // Clang crashes if noexcept is used here.
#if defined(BOOST_ASIO_MSVC) // Visual C++ wants the type to be qualified.
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&,
        bulk_guarantee_t<>::unsequenced_t>::value))
#else // defined(BOOST_ASIO_MSVC)
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, unsequenced_t>::value))
#endif // defined(BOOST_ASIO_MSVC)
#endif // !defined(__clang__)
  {
    return boost::asio::query(ex, unsequenced_t());
  }

  template <typename Executor>
  friend BOOST_ASIO_CONSTEXPR bulk_guarantee_t query(
      const Executor& ex, convertible_from_bulk_guarantee_t,
      typename enable_if<
        !can_query<const Executor&, unsequenced_t>::value
      >::type* = 0,
      typename enable_if<
        can_query<const Executor&, sequenced_t>::value
      >::type* = 0)
#if !defined(__clang__) // Clang crashes if noexcept is used here.
#if defined(BOOST_ASIO_MSVC) // Visual C++ wants the type to be qualified.
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&,
        bulk_guarantee_t<>::sequenced_t>::value))
#else // defined(BOOST_ASIO_MSVC)
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, sequenced_t>::value))
#endif // defined(BOOST_ASIO_MSVC)
#endif // !defined(__clang__)
  {
    return boost::asio::query(ex, sequenced_t());
  }

  template <typename Executor>
  friend BOOST_ASIO_CONSTEXPR bulk_guarantee_t query(
      const Executor& ex, convertible_from_bulk_guarantee_t,
      typename enable_if<
        !can_query<const Executor&, unsequenced_t>::value
      >::type* = 0,
      typename enable_if<
        !can_query<const Executor&, sequenced_t>::value
      >::type* = 0,
      typename enable_if<
        can_query<const Executor&, parallel_t>::value
      >::type* = 0)
#if !defined(__clang__) // Clang crashes if noexcept is used here.
#if defined(BOOST_ASIO_MSVC) // Visual C++ wants the type to be qualified.
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, bulk_guarantee_t<>::parallel_t>::value))
#else // defined(BOOST_ASIO_MSVC)
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, parallel_t>::value))
#endif // defined(BOOST_ASIO_MSVC)
#endif // !defined(__clang__)
  {
    return boost::asio::query(ex, parallel_t());
  }

  BOOST_ASIO_STATIC_CONSTEXPR_DEFAULT_INIT(unsequenced_t, unsequenced);
  BOOST_ASIO_STATIC_CONSTEXPR_DEFAULT_INIT(sequenced_t, sequenced);
  BOOST_ASIO_STATIC_CONSTEXPR_DEFAULT_INIT(parallel_t, parallel);

#if !defined(BOOST_ASIO_HAS_CONSTEXPR)
  static const bulk_guarantee_t instance;
#endif // !defined(BOOST_ASIO_HAS_CONSTEXPR)

private:
  int value_;
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <int I> template <typename E, typename T>
const T bulk_guarantee_t<I>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

#if !defined(BOOST_ASIO_HAS_CONSTEXPR)
template <int I>
const bulk_guarantee_t<I> bulk_guarantee_t<I>::instance;
#endif

template <int I>
const typename bulk_guarantee_t<I>::unsequenced_t
bulk_guarantee_t<I>::unsequenced;

template <int I>
const typename bulk_guarantee_t<I>::sequenced_t
bulk_guarantee_t<I>::sequenced;

template <int I>
const typename bulk_guarantee_t<I>::parallel_t
bulk_guarantee_t<I>::parallel;

namespace bulk_guarantee {

template <int I = 0>
struct unsequenced_t
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

  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_requirable = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_preferable = true);
  typedef bulk_guarantee_t<I> polymorphic_query_result_type;

  BOOST_ASIO_CONSTEXPR unsequenced_t()
  {
  }

  template <typename T>
  struct query_member :
    traits::query_member<
      typename bulk_guarantee_t<I>::template proxy<T>::type,
        unsequenced_t> {};

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename bulk_guarantee_t<I>::template static_proxy<T>::type,
        unsequenced_t> {};

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

  template <typename T>
  static BOOST_ASIO_CONSTEXPR unsequenced_t static_query(
      typename enable_if<
        !query_static_constexpr_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !query_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !traits::query_free<T, unsequenced_t>::is_valid
      >::type* = 0,
      typename enable_if<
        !can_query<T, sequenced_t<I> >::value
      >::type* = 0,
      typename enable_if<
        !can_query<T, parallel_t<I> >::value
      >::type* = 0) BOOST_ASIO_NOEXCEPT
  {
    return unsequenced_t();
  }

  template <typename E, typename T = decltype(unsequenced_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = unsequenced_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  static BOOST_ASIO_CONSTEXPR bulk_guarantee_t<I> value()
  {
    return unsequenced_t();
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const unsequenced_t&, const unsequenced_t&)
  {
    return true;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const unsequenced_t&, const unsequenced_t&)
  {
    return false;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const unsequenced_t&, const sequenced_t<I>&)
  {
    return false;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const unsequenced_t&, const sequenced_t<I>&)
  {
    return true;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const unsequenced_t&, const parallel_t<I>&)
  {
    return false;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const unsequenced_t&, const parallel_t<I>&)
  {
    return true;
  }
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <int I> template <typename E, typename T>
const T unsequenced_t<I>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

template <int I = 0>
struct sequenced_t
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

  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_requirable = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_preferable = true);
  typedef bulk_guarantee_t<I> polymorphic_query_result_type;

  BOOST_ASIO_CONSTEXPR sequenced_t()
  {
  }

  template <typename T>
  struct query_member :
    traits::query_member<
      typename bulk_guarantee_t<I>::template proxy<T>::type,
        sequenced_t> {};

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename bulk_guarantee_t<I>::template static_proxy<T>::type,
        sequenced_t> {};

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

  template <typename E, typename T = decltype(sequenced_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = sequenced_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  static BOOST_ASIO_CONSTEXPR bulk_guarantee_t<I> value()
  {
    return sequenced_t();
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const sequenced_t&, const sequenced_t&)
  {
    return true;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const sequenced_t&, const sequenced_t&)
  {
    return false;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const sequenced_t&, const unsequenced_t<I>&)
  {
    return false;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const sequenced_t&, const unsequenced_t<I>&)
  {
    return true;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const sequenced_t&, const parallel_t<I>&)
  {
    return false;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const sequenced_t&, const parallel_t<I>&)
  {
    return true;
  }
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <int I> template <typename E, typename T>
const T sequenced_t<I>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

template <int I>
struct parallel_t
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

  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_requirable = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_preferable = true);
  typedef bulk_guarantee_t<I> polymorphic_query_result_type;

  BOOST_ASIO_CONSTEXPR parallel_t()
  {
  }

  template <typename T>
  struct query_member :
    traits::query_member<
      typename bulk_guarantee_t<I>::template proxy<T>::type,
        parallel_t> {};

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename bulk_guarantee_t<I>::template static_proxy<T>::type,
        parallel_t> {};

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

  template <typename E, typename T = decltype(parallel_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = parallel_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  static BOOST_ASIO_CONSTEXPR bulk_guarantee_t<I> value()
  {
    return parallel_t();
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const parallel_t&, const parallel_t&)
  {
    return true;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const parallel_t&, const parallel_t&)
  {
    return false;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const parallel_t&, const unsequenced_t<I>&)
  {
    return false;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const parallel_t&, const unsequenced_t<I>&)
  {
    return true;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const parallel_t&, const sequenced_t<I>&)
  {
    return false;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const parallel_t&, const sequenced_t<I>&)
  {
    return true;
  }
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <int I> template <typename E, typename T>
const T parallel_t<I>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

} // namespace bulk_guarantee
} // namespace detail

typedef detail::bulk_guarantee_t<> bulk_guarantee_t;

#if defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
constexpr bulk_guarantee_t bulk_guarantee;
#else // defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
namespace { static const bulk_guarantee_t&
  bulk_guarantee = bulk_guarantee_t::instance; }
#endif

} // namespace execution

#if !defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T>
struct is_applicable_property<T, execution::bulk_guarantee_t>
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

template <typename T>
struct is_applicable_property<T, execution::bulk_guarantee_t::unsequenced_t>
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

template <typename T>
struct is_applicable_property<T, execution::bulk_guarantee_t::sequenced_t>
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

template <typename T>
struct is_applicable_property<T, execution::bulk_guarantee_t::parallel_t>
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

#if !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_FREE_TRAIT)

template <typename T>
struct query_free_default<T, execution::bulk_guarantee_t,
  typename enable_if<
    can_query<T, execution::bulk_guarantee_t::unsequenced_t>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    (is_nothrow_query<T, execution::bulk_guarantee_t::unsequenced_t>::value));

  typedef execution::bulk_guarantee_t result_type;
};

template <typename T>
struct query_free_default<T, execution::bulk_guarantee_t,
  typename enable_if<
    !can_query<T, execution::bulk_guarantee_t::unsequenced_t>::value
      && can_query<T, execution::bulk_guarantee_t::sequenced_t>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    (is_nothrow_query<T, execution::bulk_guarantee_t::sequenced_t>::value));

  typedef execution::bulk_guarantee_t result_type;
};

template <typename T>
struct query_free_default<T, execution::bulk_guarantee_t,
  typename enable_if<
    !can_query<T, execution::bulk_guarantee_t::unsequenced_t>::value
      && !can_query<T, execution::bulk_guarantee_t::sequenced_t>::value
      && can_query<T, execution::bulk_guarantee_t::parallel_t>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    (is_nothrow_query<T, execution::bulk_guarantee_t::parallel_t>::value));

  typedef execution::bulk_guarantee_t result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_FREE_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  || !defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

template <typename T>
struct static_query<T, execution::bulk_guarantee_t,
  typename enable_if<
    execution::detail::bulk_guarantee_t<0>::
      query_static_constexpr_member<T>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename execution::detail::bulk_guarantee_t<0>::
    query_static_constexpr_member<T>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return execution::detail::bulk_guarantee_t<0>::
      query_static_constexpr_member<T>::value();
  }
};

template <typename T>
struct static_query<T, execution::bulk_guarantee_t,
  typename enable_if<
    !execution::detail::bulk_guarantee_t<0>::
        query_static_constexpr_member<T>::is_valid
      && !execution::detail::bulk_guarantee_t<0>::
        query_member<T>::is_valid
      && traits::static_query<T,
        execution::bulk_guarantee_t::unsequenced_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename traits::static_query<T,
    execution::bulk_guarantee_t::unsequenced_t>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return traits::static_query<T,
        execution::bulk_guarantee_t::unsequenced_t>::value();
  }
};

template <typename T>
struct static_query<T, execution::bulk_guarantee_t,
  typename enable_if<
    !execution::detail::bulk_guarantee_t<0>::
        query_static_constexpr_member<T>::is_valid
      && !execution::detail::bulk_guarantee_t<0>::
        query_member<T>::is_valid
      && !traits::static_query<T,
        execution::bulk_guarantee_t::unsequenced_t>::is_valid
      && traits::static_query<T,
        execution::bulk_guarantee_t::sequenced_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename traits::static_query<T,
    execution::bulk_guarantee_t::sequenced_t>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return traits::static_query<T,
        execution::bulk_guarantee_t::sequenced_t>::value();
  }
};

template <typename T>
struct static_query<T, execution::bulk_guarantee_t,
  typename enable_if<
    !execution::detail::bulk_guarantee_t<0>::
        query_static_constexpr_member<T>::is_valid
      && !execution::detail::bulk_guarantee_t<0>::
        query_member<T>::is_valid
      && !traits::static_query<T,
        execution::bulk_guarantee_t::unsequenced_t>::is_valid
      && !traits::static_query<T,
        execution::bulk_guarantee_t::sequenced_t>::is_valid
      && traits::static_query<T,
        execution::bulk_guarantee_t::parallel_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename traits::static_query<T,
    execution::bulk_guarantee_t::parallel_t>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return traits::static_query<T,
        execution::bulk_guarantee_t::parallel_t>::value();
  }
};

template <typename T>
struct static_query<T, execution::bulk_guarantee_t::unsequenced_t,
  typename enable_if<
    execution::detail::bulk_guarantee::unsequenced_t<0>::
      query_static_constexpr_member<T>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename execution::detail::bulk_guarantee::unsequenced_t<0>::
    query_static_constexpr_member<T>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return execution::detail::bulk_guarantee::unsequenced_t<0>::
      query_static_constexpr_member<T>::value();
  }
};

template <typename T>
struct static_query<T, execution::bulk_guarantee_t::unsequenced_t,
  typename enable_if<
    !execution::detail::bulk_guarantee::unsequenced_t<0>::
        query_static_constexpr_member<T>::is_valid
      && !execution::detail::bulk_guarantee::unsequenced_t<0>::
        query_member<T>::is_valid
      && !traits::query_free<T,
        execution::bulk_guarantee_t::unsequenced_t>::is_valid
      && !can_query<T, execution::bulk_guarantee_t::sequenced_t>::value
      && !can_query<T, execution::bulk_guarantee_t::parallel_t>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef execution::bulk_guarantee_t::unsequenced_t result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return result_type();
  }
};

template <typename T>
struct static_query<T, execution::bulk_guarantee_t::sequenced_t,
  typename enable_if<
    execution::detail::bulk_guarantee::sequenced_t<0>::
      query_static_constexpr_member<T>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename execution::detail::bulk_guarantee::sequenced_t<0>::
    query_static_constexpr_member<T>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return execution::detail::bulk_guarantee::sequenced_t<0>::
      query_static_constexpr_member<T>::value();
  }
};

template <typename T>
struct static_query<T, execution::bulk_guarantee_t::parallel_t,
  typename enable_if<
    execution::detail::bulk_guarantee::parallel_t<0>::
      query_static_constexpr_member<T>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename execution::detail::bulk_guarantee::parallel_t<0>::
    query_static_constexpr_member<T>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return execution::detail::bulk_guarantee::parallel_t<0>::
      query_static_constexpr_member<T>::value();
  }
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   || !defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

#if !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_REQUIRE_TRAIT)

template <typename T>
struct static_require<T, execution::bulk_guarantee_t::unsequenced_t,
  typename enable_if<
    static_query<T, execution::bulk_guarantee_t::unsequenced_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid =
    (is_same<typename static_query<T,
      execution::bulk_guarantee_t::unsequenced_t>::result_type,
        execution::bulk_guarantee_t::unsequenced_t>::value));
};

template <typename T>
struct static_require<T, execution::bulk_guarantee_t::sequenced_t,
  typename enable_if<
    static_query<T, execution::bulk_guarantee_t::sequenced_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid =
    (is_same<typename static_query<T,
      execution::bulk_guarantee_t::sequenced_t>::result_type,
        execution::bulk_guarantee_t::sequenced_t>::value));
};

template <typename T>
struct static_require<T, execution::bulk_guarantee_t::parallel_t,
  typename enable_if<
    static_query<T, execution::bulk_guarantee_t::parallel_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid =
    (is_same<typename static_query<T,
      execution::bulk_guarantee_t::parallel_t>::result_type,
        execution::bulk_guarantee_t::parallel_t>::value));
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_REQUIRE_TRAIT)

} // namespace traits

#endif // defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_BULK_GUARANTEE_HPP

/* bulk_guarantee.hpp
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
*/