//
// execution/outstanding_work.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_OUTSTANDING_WORK_HPP
#define BOOST_ASIO_EXECUTION_OUTSTANDING_WORK_HPP

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

/// A property to describe whether task submission is likely in the future.
struct outstanding_work_t
{
  /// The outstanding_work_t property applies to executors, senders, and
  /// schedulers.
  template <typename T>
  static constexpr bool is_applicable_property_v =
    is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

  /// The top-level outstanding_work_t property cannot be required.
  static constexpr bool is_requirable = false;

  /// The top-level outstanding_work_t property cannot be preferred.
  static constexpr bool is_preferable = false;

  /// The type returned by queries against an @c any_executor.
  typedef outstanding_work_t polymorphic_query_result_type;

  /// A sub-property that indicates that the executor does not represent likely
  /// future submission of a function object.
  struct untracked_t
  {
    /// The outstanding_work_t::untracked_t property applies to executors,
    /// senders, and schedulers.
    template <typename T>
    static constexpr bool is_applicable_property_v =
      is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

    /// The outstanding_work_t::untracked_t property can be required.
    static constexpr bool is_requirable = true;

    /// The outstanding_work_t::untracked_t property can be preferred.
    static constexpr bool is_preferable = true;

    /// The type returned by queries against an @c any_executor.
    typedef outstanding_work_t polymorphic_query_result_type;

    /// Default constructor.
    constexpr untracked_t();

    /// Get the value associated with a property object.
    /**
     * @returns untracked_t();
     */
    static constexpr outstanding_work_t value();
  };

  /// A sub-property that indicates that the executor represents likely
  /// future submission of a function object.
  struct tracked_t
  {
    /// The outstanding_work_t::untracked_t property applies to executors,
    /// senders, and schedulers.
    template <typename T>
    static constexpr bool is_applicable_property_v =
      is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

    /// The outstanding_work_t::tracked_t property can be required.
    static constexpr bool is_requirable = true;

    /// The outstanding_work_t::tracked_t property can be preferred.
    static constexpr bool is_preferable = true;

    /// The type returned by queries against an @c any_executor.
    typedef outstanding_work_t polymorphic_query_result_type;

    /// Default constructor.
    constexpr tracked_t();

    /// Get the value associated with a property object.
    /**
     * @returns tracked_t();
     */
    static constexpr outstanding_work_t value();
  };

  /// A special value used for accessing the outstanding_work_t::untracked_t
  /// property.
  static constexpr untracked_t untracked;

  /// A special value used for accessing the outstanding_work_t::tracked_t
  /// property.
  static constexpr tracked_t tracked;

  /// Default constructor.
  constexpr outstanding_work_t();

  /// Construct from a sub-property value.
  constexpr outstanding_work_t(untracked_t);

  /// Construct from a sub-property value.
  constexpr outstanding_work_t(tracked_t);

  /// Compare property values for equality.
  friend constexpr bool operator==(
      const outstanding_work_t& a, const outstanding_work_t& b) noexcept;

  /// Compare property values for inequality.
  friend constexpr bool operator!=(
      const outstanding_work_t& a, const outstanding_work_t& b) noexcept;
};

/// A special value used for accessing the outstanding_work_t property.
constexpr outstanding_work_t outstanding_work;

} // namespace execution

#else // defined(GENERATING_DOCUMENTATION)

namespace execution {
namespace detail {
namespace outstanding_work {

template <int I> struct untracked_t;
template <int I> struct tracked_t;

} // namespace outstanding_work

template <int I = 0>
struct outstanding_work_t
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
  typedef outstanding_work_t polymorphic_query_result_type;

  typedef detail::outstanding_work::untracked_t<I> untracked_t;
  typedef detail::outstanding_work::tracked_t<I> tracked_t;

  BOOST_ASIO_CONSTEXPR outstanding_work_t()
    : value_(-1)
  {
  }

  BOOST_ASIO_CONSTEXPR outstanding_work_t(untracked_t)
    : value_(0)
  {
  }

  BOOST_ASIO_CONSTEXPR outstanding_work_t(tracked_t)
    : value_(1)
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
    traits::query_member<typename proxy<T>::type, outstanding_work_t> {};

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename static_proxy<T>::type, outstanding_work_t> {};

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
  typename traits::static_query<T, untracked_t>::result_type
  static_query(
      typename enable_if<
        !query_static_constexpr_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !query_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        traits::static_query<T, untracked_t>::is_valid
      >::type* = 0) BOOST_ASIO_NOEXCEPT
  {
    return traits::static_query<T, untracked_t>::value();
  }

  template <typename T>
  static BOOST_ASIO_CONSTEXPR
  typename traits::static_query<T, tracked_t>::result_type
  static_query(
      typename enable_if<
        !query_static_constexpr_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !query_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !traits::static_query<T, untracked_t>::is_valid
      >::type* = 0,
      typename enable_if<
        traits::static_query<T, tracked_t>::is_valid
      >::type* = 0) BOOST_ASIO_NOEXCEPT
  {
    return traits::static_query<T, tracked_t>::value();
  }

  template <typename E,
      typename T = decltype(outstanding_work_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = outstanding_work_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const outstanding_work_t& a, const outstanding_work_t& b)
  {
    return a.value_ == b.value_;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const outstanding_work_t& a, const outstanding_work_t& b)
  {
    return a.value_ != b.value_;
  }

  struct convertible_from_outstanding_work_t
  {
    BOOST_ASIO_CONSTEXPR convertible_from_outstanding_work_t(outstanding_work_t)
    {
    }
  };

  template <typename Executor>
  friend BOOST_ASIO_CONSTEXPR outstanding_work_t query(
      const Executor& ex, convertible_from_outstanding_work_t,
      typename enable_if<
        can_query<const Executor&, untracked_t>::value
      >::type* = 0)
#if !defined(__clang__) // Clang crashes if noexcept is used here.
#if defined(BOOST_ASIO_MSVC) // Visual C++ wants the type to be qualified.
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&,
        outstanding_work_t<>::untracked_t>::value))
#else // defined(BOOST_ASIO_MSVC)
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, untracked_t>::value))
#endif // defined(BOOST_ASIO_MSVC)
#endif // !defined(__clang__)
  {
    return boost::asio::query(ex, untracked_t());
  }

  template <typename Executor>
  friend BOOST_ASIO_CONSTEXPR outstanding_work_t query(
      const Executor& ex, convertible_from_outstanding_work_t,
      typename enable_if<
        !can_query<const Executor&, untracked_t>::value
      >::type* = 0,
      typename enable_if<
        can_query<const Executor&, tracked_t>::value
      >::type* = 0)
#if !defined(__clang__) // Clang crashes if noexcept is used here.
#if defined(BOOST_ASIO_MSVC) // Visual C++ wants the type to be qualified.
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&,
        outstanding_work_t<>::tracked_t>::value))
#else // defined(BOOST_ASIO_MSVC)
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, tracked_t>::value))
#endif // defined(BOOST_ASIO_MSVC)
#endif // !defined(__clang__)
  {
    return boost::asio::query(ex, tracked_t());
  }

  BOOST_ASIO_STATIC_CONSTEXPR_DEFAULT_INIT(untracked_t, untracked);
  BOOST_ASIO_STATIC_CONSTEXPR_DEFAULT_INIT(tracked_t, tracked);

#if !defined(BOOST_ASIO_HAS_CONSTEXPR)
  static const outstanding_work_t instance;
#endif // !defined(BOOST_ASIO_HAS_CONSTEXPR)

private:
  int value_;
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <int I> template <typename E, typename T>
const T outstanding_work_t<I>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

#if !defined(BOOST_ASIO_HAS_CONSTEXPR)
template <int I>
const outstanding_work_t<I> outstanding_work_t<I>::instance;
#endif

template <int I>
const typename outstanding_work_t<I>::untracked_t
outstanding_work_t<I>::untracked;

template <int I>
const typename outstanding_work_t<I>::tracked_t
outstanding_work_t<I>::tracked;

namespace outstanding_work {

template <int I = 0>
struct untracked_t
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
  typedef outstanding_work_t<I> polymorphic_query_result_type;

  BOOST_ASIO_CONSTEXPR untracked_t()
  {
  }

  template <typename T>
  struct query_member :
    traits::query_member<
      typename outstanding_work_t<I>::template proxy<T>::type, untracked_t> {};

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename outstanding_work_t<I>::template static_proxy<T>::type,
        untracked_t> {};

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
  static BOOST_ASIO_CONSTEXPR untracked_t static_query(
      typename enable_if<
        !query_static_constexpr_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !query_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !traits::query_free<T, untracked_t>::is_valid
      >::type* = 0,
      typename enable_if<
        !can_query<T, tracked_t<I> >::value
      >::type* = 0) BOOST_ASIO_NOEXCEPT
  {
    return untracked_t();
  }

  template <typename E, typename T = decltype(untracked_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = untracked_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  static BOOST_ASIO_CONSTEXPR outstanding_work_t<I> value()
  {
    return untracked_t();
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const untracked_t&, const untracked_t&)
  {
    return true;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const untracked_t&, const untracked_t&)
  {
    return false;
  }
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <int I> template <typename E, typename T>
const T untracked_t<I>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

template <int I = 0>
struct tracked_t
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
  typedef outstanding_work_t<I> polymorphic_query_result_type;

  BOOST_ASIO_CONSTEXPR tracked_t()
  {
  }

  template <typename T>
  struct query_member :
    traits::query_member<
      typename outstanding_work_t<I>::template proxy<T>::type, tracked_t> {};

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename outstanding_work_t<I>::template static_proxy<T>::type,
        tracked_t> {};

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

  template <typename E, typename T = decltype(tracked_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = tracked_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  static BOOST_ASIO_CONSTEXPR outstanding_work_t<I> value()
  {
    return tracked_t();
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const tracked_t&, const tracked_t&)
  {
    return true;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const tracked_t&, const tracked_t&)
  {
    return false;
  }
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <int I> template <typename E, typename T>
const T tracked_t<I>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

} // namespace outstanding_work
} // namespace detail

typedef detail::outstanding_work_t<> outstanding_work_t;

#if defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
constexpr outstanding_work_t outstanding_work;
#else // defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
namespace { static const outstanding_work_t&
  outstanding_work = outstanding_work_t::instance; }
#endif

} // namespace execution

#if !defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T>
struct is_applicable_property<T, execution::outstanding_work_t>
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
struct is_applicable_property<T, execution::outstanding_work_t::untracked_t>
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
struct is_applicable_property<T, execution::outstanding_work_t::tracked_t>
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
struct query_free_default<T, execution::outstanding_work_t,
  typename enable_if<
    can_query<T, execution::outstanding_work_t::untracked_t>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    (is_nothrow_query<T, execution::outstanding_work_t::untracked_t>::value));

  typedef execution::outstanding_work_t result_type;
};

template <typename T>
struct query_free_default<T, execution::outstanding_work_t,
  typename enable_if<
    !can_query<T, execution::outstanding_work_t::untracked_t>::value
      && can_query<T, execution::outstanding_work_t::tracked_t>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    (is_nothrow_query<T, execution::outstanding_work_t::tracked_t>::value));

  typedef execution::outstanding_work_t result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_FREE_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  || !defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

template <typename T>
struct static_query<T, execution::outstanding_work_t,
  typename enable_if<
    execution::detail::outstanding_work_t<0>::
      query_static_constexpr_member<T>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename execution::detail::outstanding_work_t<0>::
    query_static_constexpr_member<T>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return execution::detail::outstanding_work_t<0>::
      query_static_constexpr_member<T>::value();
  }
};

template <typename T>
struct static_query<T, execution::outstanding_work_t,
  typename enable_if<
    !execution::detail::outstanding_work_t<0>::
        query_static_constexpr_member<T>::is_valid
      && !execution::detail::outstanding_work_t<0>::
        query_member<T>::is_valid
      && traits::static_query<T,
        execution::outstanding_work_t::untracked_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename traits::static_query<T,
    execution::outstanding_work_t::untracked_t>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return traits::static_query<T,
        execution::outstanding_work_t::untracked_t>::value();
  }
};

template <typename T>
struct static_query<T, execution::outstanding_work_t,
  typename enable_if<
    !execution::detail::outstanding_work_t<0>::
        query_static_constexpr_member<T>::is_valid
      && !execution::detail::outstanding_work_t<0>::
        query_member<T>::is_valid
      && !traits::static_query<T,
        execution::outstanding_work_t::untracked_t>::is_valid
      && traits::static_query<T,
        execution::outstanding_work_t::tracked_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename traits::static_query<T,
    execution::outstanding_work_t::tracked_t>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return traits::static_query<T,
        execution::outstanding_work_t::tracked_t>::value();
  }
};

template <typename T>
struct static_query<T, execution::outstanding_work_t::untracked_t,
  typename enable_if<
    execution::detail::outstanding_work::untracked_t<0>::
      query_static_constexpr_member<T>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename execution::detail::outstanding_work::untracked_t<0>::
    query_static_constexpr_member<T>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return execution::detail::outstanding_work::untracked_t<0>::
      query_static_constexpr_member<T>::value();
  }
};

template <typename T>
struct static_query<T, execution::outstanding_work_t::untracked_t,
  typename enable_if<
    !execution::detail::outstanding_work::untracked_t<0>::
        query_static_constexpr_member<T>::is_valid
      && !execution::detail::outstanding_work::untracked_t<0>::
          query_member<T>::is_valid
      && !traits::query_free<T,
        execution::outstanding_work_t::untracked_t>::is_valid
      && !can_query<T, execution::outstanding_work_t::tracked_t>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef execution::outstanding_work_t::untracked_t result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return result_type();
  }
};

template <typename T>
struct static_query<T, execution::outstanding_work_t::tracked_t,
  typename enable_if<
    execution::detail::outstanding_work::tracked_t<0>::
      query_static_constexpr_member<T>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename execution::detail::outstanding_work::tracked_t<0>::
    query_static_constexpr_member<T>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return execution::detail::outstanding_work::tracked_t<0>::
      query_static_constexpr_member<T>::value();
  }
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   || !defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

#if !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_REQUIRE_TRAIT)

template <typename T>
struct static_require<T, execution::outstanding_work_t::untracked_t,
  typename enable_if<
    static_query<T, execution::outstanding_work_t::untracked_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid =
    (is_same<typename static_query<T,
      execution::outstanding_work_t::untracked_t>::result_type,
        execution::outstanding_work_t::untracked_t>::value));
};

template <typename T>
struct static_require<T, execution::outstanding_work_t::tracked_t,
  typename enable_if<
    static_query<T, execution::outstanding_work_t::tracked_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid =
    (is_same<typename static_query<T,
      execution::outstanding_work_t::tracked_t>::result_type,
        execution::outstanding_work_t::tracked_t>::value));
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_REQUIRE_TRAIT)

} // namespace traits

#endif // defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_OUTSTANDING_WORK_HPP

/* outstanding_work.hpp
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
*/