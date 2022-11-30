//
// execution/relationship.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_RELATIONSHIP_HPP
#define BOOST_ASIO_EXECUTION_RELATIONSHIP_HPP

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

/// A property to describe whether submitted tasks represent continuations of
/// the calling context.
struct relationship_t
{
  /// The relationship_t property applies to executors, senders, and schedulers.
  template <typename T>
  static constexpr bool is_applicable_property_v =
    is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

  /// The top-level relationship_t property cannot be required.
  static constexpr bool is_requirable = false;

  /// The top-level relationship_t property cannot be preferred.
  static constexpr bool is_preferable = false;

  /// The type returned by queries against an @c any_executor.
  typedef relationship_t polymorphic_query_result_type;

  /// A sub-property that indicates that the executor does not represent a
  /// continuation of the calling context.
  struct fork_t
  {
    /// The relationship_t::fork_t property applies to executors, senders, and
    /// schedulers.
    template <typename T>
    static constexpr bool is_applicable_property_v =
      is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

    /// The relationship_t::fork_t property can be required.
    static constexpr bool is_requirable = true;

    /// The relationship_t::fork_t property can be preferred.
    static constexpr bool is_preferable = true;

    /// The type returned by queries against an @c any_executor.
    typedef relationship_t polymorphic_query_result_type;

    /// Default constructor.
    constexpr fork_t();

    /// Get the value associated with a property object.
    /**
     * @returns fork_t();
     */
    static constexpr relationship_t value();
  };

  /// A sub-property that indicates that the executor represents a continuation
  /// of the calling context.
  struct continuation_t
  {
    /// The relationship_t::continuation_t property applies to executors,
    /// senders, and schedulers.
    template <typename T>
    static constexpr bool is_applicable_property_v =
      is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

    /// The relationship_t::continuation_t property can be required.
    static constexpr bool is_requirable = true;

    /// The relationship_t::continuation_t property can be preferred.
    static constexpr bool is_preferable = true;

    /// The type returned by queries against an @c any_executor.
    typedef relationship_t polymorphic_query_result_type;

    /// Default constructor.
    constexpr continuation_t();

    /// Get the value associated with a property object.
    /**
     * @returns continuation_t();
     */
    static constexpr relationship_t value();
  };

  /// A special value used for accessing the relationship_t::fork_t property.
  static constexpr fork_t fork;

  /// A special value used for accessing the relationship_t::continuation_t
  /// property.
  static constexpr continuation_t continuation;

  /// Default constructor.
  constexpr relationship_t();

  /// Construct from a sub-property value.
  constexpr relationship_t(fork_t);

  /// Construct from a sub-property value.
  constexpr relationship_t(continuation_t);

  /// Compare property values for equality.
  friend constexpr bool operator==(
      const relationship_t& a, const relationship_t& b) noexcept;

  /// Compare property values for inequality.
  friend constexpr bool operator!=(
      const relationship_t& a, const relationship_t& b) noexcept;
};

/// A special value used for accessing the relationship_t property.
constexpr relationship_t relationship;

} // namespace execution

#else // defined(GENERATING_DOCUMENTATION)

namespace execution {
namespace detail {
namespace relationship {

template <int I> struct fork_t;
template <int I> struct continuation_t;

} // namespace relationship

template <int I = 0>
struct relationship_t
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
  typedef relationship_t polymorphic_query_result_type;

  typedef detail::relationship::fork_t<I> fork_t;
  typedef detail::relationship::continuation_t<I> continuation_t;

  BOOST_ASIO_CONSTEXPR relationship_t()
    : value_(-1)
  {
  }

  BOOST_ASIO_CONSTEXPR relationship_t(fork_t)
    : value_(0)
  {
  }

  BOOST_ASIO_CONSTEXPR relationship_t(continuation_t)
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
    traits::query_member<typename proxy<T>::type, relationship_t> {};

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename static_proxy<T>::type, relationship_t> {};

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
  typename traits::static_query<T, fork_t>::result_type
  static_query(
      typename enable_if<
        !query_static_constexpr_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !query_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        traits::static_query<T, fork_t>::is_valid
      >::type* = 0) BOOST_ASIO_NOEXCEPT
  {
    return traits::static_query<T, fork_t>::value();
  }

  template <typename T>
  static BOOST_ASIO_CONSTEXPR
  typename traits::static_query<T, continuation_t>::result_type
  static_query(
      typename enable_if<
        !query_static_constexpr_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !query_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !traits::static_query<T, fork_t>::is_valid
      >::type* = 0,
      typename enable_if<
        traits::static_query<T, continuation_t>::is_valid
      >::type* = 0) BOOST_ASIO_NOEXCEPT
  {
    return traits::static_query<T, continuation_t>::value();
  }

  template <typename E,
      typename T = decltype(relationship_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = relationship_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const relationship_t& a, const relationship_t& b)
  {
    return a.value_ == b.value_;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const relationship_t& a, const relationship_t& b)
  {
    return a.value_ != b.value_;
  }

  struct convertible_from_relationship_t
  {
    BOOST_ASIO_CONSTEXPR convertible_from_relationship_t(relationship_t)
    {
    }
  };

  template <typename Executor>
  friend BOOST_ASIO_CONSTEXPR relationship_t query(
      const Executor& ex, convertible_from_relationship_t,
      typename enable_if<
        can_query<const Executor&, fork_t>::value
      >::type* = 0)
#if !defined(__clang__) // Clang crashes if noexcept is used here.
#if defined(BOOST_ASIO_MSVC) // Visual C++ wants the type to be qualified.
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, relationship_t<>::fork_t>::value))
#else // defined(BOOST_ASIO_MSVC)
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, fork_t>::value))
#endif // defined(BOOST_ASIO_MSVC)
#endif // !defined(__clang__)
  {
    return boost::asio::query(ex, fork_t());
  }

  template <typename Executor>
  friend BOOST_ASIO_CONSTEXPR relationship_t query(
      const Executor& ex, convertible_from_relationship_t,
      typename enable_if<
        !can_query<const Executor&, fork_t>::value
      >::type* = 0,
      typename enable_if<
        can_query<const Executor&, continuation_t>::value
      >::type* = 0)
#if !defined(__clang__) // Clang crashes if noexcept is used here.
#if defined(BOOST_ASIO_MSVC) // Visual C++ wants the type to be qualified.
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&,
        relationship_t<>::continuation_t>::value))
#else // defined(BOOST_ASIO_MSVC)
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, continuation_t>::value))
#endif // defined(BOOST_ASIO_MSVC)
#endif // !defined(__clang__)
  {
    return boost::asio::query(ex, continuation_t());
  }

  BOOST_ASIO_STATIC_CONSTEXPR_DEFAULT_INIT(fork_t, fork);
  BOOST_ASIO_STATIC_CONSTEXPR_DEFAULT_INIT(continuation_t, continuation);

#if !defined(BOOST_ASIO_HAS_CONSTEXPR)
  static const relationship_t instance;
#endif // !defined(BOOST_ASIO_HAS_CONSTEXPR)

private:
  int value_;
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <int I> template <typename E, typename T>
const T relationship_t<I>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

#if !defined(BOOST_ASIO_HAS_CONSTEXPR)
template <int I>
const relationship_t<I> relationship_t<I>::instance;
#endif

template <int I>
const typename relationship_t<I>::fork_t
relationship_t<I>::fork;

template <int I>
const typename relationship_t<I>::continuation_t
relationship_t<I>::continuation;

namespace relationship {

template <int I = 0>
struct fork_t
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
  typedef relationship_t<I> polymorphic_query_result_type;

  BOOST_ASIO_CONSTEXPR fork_t()
  {
  }

  template <typename T>
  struct query_member :
    traits::query_member<
      typename relationship_t<I>::template proxy<T>::type, fork_t> {};

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename relationship_t<I>::template static_proxy<T>::type, fork_t> {};

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
  static BOOST_ASIO_CONSTEXPR fork_t static_query(
      typename enable_if<
        !query_static_constexpr_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !query_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !traits::query_free<T, fork_t>::is_valid
      >::type* = 0,
      typename enable_if<
        !can_query<T, continuation_t<I> >::value
      >::type* = 0) BOOST_ASIO_NOEXCEPT
  {
    return fork_t();
  }

  template <typename E, typename T = decltype(fork_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = fork_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  static BOOST_ASIO_CONSTEXPR relationship_t<I> value()
  {
    return fork_t();
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const fork_t&, const fork_t&)
  {
    return true;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const fork_t&, const fork_t&)
  {
    return false;
  }
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <int I> template <typename E, typename T>
const T fork_t<I>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

template <int I = 0>
struct continuation_t
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
  typedef relationship_t<I> polymorphic_query_result_type;

  BOOST_ASIO_CONSTEXPR continuation_t()
  {
  }

  template <typename T>
  struct query_member :
    traits::query_member<
      typename relationship_t<I>::template proxy<T>::type, continuation_t> {};

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename relationship_t<I>::template static_proxy<T>::type,
        continuation_t> {};

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

  template <typename E,
      typename T = decltype(continuation_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = continuation_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  static BOOST_ASIO_CONSTEXPR relationship_t<I> value()
  {
    return continuation_t();
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const continuation_t&, const continuation_t&)
  {
    return true;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const continuation_t&, const continuation_t&)
  {
    return false;
  }
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <int I> template <typename E, typename T>
const T continuation_t<I>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

} // namespace relationship
} // namespace detail

typedef detail::relationship_t<> relationship_t;

#if defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
constexpr relationship_t relationship;
#else // defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
namespace { static const relationship_t&
  relationship = relationship_t::instance; }
#endif

} // namespace execution

#if !defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T>
struct is_applicable_property<T, execution::relationship_t>
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
struct is_applicable_property<T, execution::relationship_t::fork_t>
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
struct is_applicable_property<T, execution::relationship_t::continuation_t>
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
struct query_free_default<T, execution::relationship_t,
  typename enable_if<
    can_query<T, execution::relationship_t::fork_t>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    (is_nothrow_query<T, execution::relationship_t::fork_t>::value));

  typedef execution::relationship_t result_type;
};

template <typename T>
struct query_free_default<T, execution::relationship_t,
  typename enable_if<
    !can_query<T, execution::relationship_t::fork_t>::value
      && can_query<T, execution::relationship_t::continuation_t>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    (is_nothrow_query<T, execution::relationship_t::continuation_t>::value));

  typedef execution::relationship_t result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_FREE_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  || !defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

template <typename T>
struct static_query<T, execution::relationship_t,
  typename enable_if<
    execution::detail::relationship_t<0>::
      query_static_constexpr_member<T>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename execution::detail::relationship_t<0>::
    query_static_constexpr_member<T>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return execution::detail::relationship_t<0>::
      query_static_constexpr_member<T>::value();
  }
};

template <typename T>
struct static_query<T, execution::relationship_t,
  typename enable_if<
    !execution::detail::relationship_t<0>::
        query_static_constexpr_member<T>::is_valid
      && !execution::detail::relationship_t<0>::
        query_member<T>::is_valid
      && traits::static_query<T,
        execution::relationship_t::fork_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename traits::static_query<T,
    execution::relationship_t::fork_t>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return traits::static_query<T,
        execution::relationship_t::fork_t>::value();
  }
};

template <typename T>
struct static_query<T, execution::relationship_t,
  typename enable_if<
    !execution::detail::relationship_t<0>::
        query_static_constexpr_member<T>::is_valid
      && !execution::detail::relationship_t<0>::
        query_member<T>::is_valid
      && !traits::static_query<T,
        execution::relationship_t::fork_t>::is_valid
      && traits::static_query<T,
        execution::relationship_t::continuation_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename traits::static_query<T,
    execution::relationship_t::continuation_t>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return traits::static_query<T,
        execution::relationship_t::continuation_t>::value();
  }
};

template <typename T>
struct static_query<T, execution::relationship_t::fork_t,
  typename enable_if<
    execution::detail::relationship::fork_t<0>::
      query_static_constexpr_member<T>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename execution::detail::relationship::fork_t<0>::
    query_static_constexpr_member<T>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return execution::detail::relationship::fork_t<0>::
      query_static_constexpr_member<T>::value();
  }
};

template <typename T>
struct static_query<T, execution::relationship_t::fork_t,
  typename enable_if<
    !execution::detail::relationship::fork_t<0>::
        query_static_constexpr_member<T>::is_valid
      && !execution::detail::relationship::fork_t<0>::
        query_member<T>::is_valid
      && !traits::query_free<T,
        execution::relationship_t::fork_t>::is_valid
      && !can_query<T, execution::relationship_t::continuation_t>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef execution::relationship_t::fork_t result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return result_type();
  }
};

template <typename T>
struct static_query<T, execution::relationship_t::continuation_t,
  typename enable_if<
    execution::detail::relationship::continuation_t<0>::
      query_static_constexpr_member<T>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename execution::detail::relationship::continuation_t<0>::
    query_static_constexpr_member<T>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return execution::detail::relationship::continuation_t<0>::
      query_static_constexpr_member<T>::value();
  }
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   || !defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

#if !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_REQUIRE_TRAIT)

template <typename T>
struct static_require<T, execution::relationship_t::fork_t,
  typename enable_if<
    static_query<T, execution::relationship_t::fork_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid =
    (is_same<typename static_query<T,
      execution::relationship_t::fork_t>::result_type,
        execution::relationship_t::fork_t>::value));
};

template <typename T>
struct static_require<T, execution::relationship_t::continuation_t,
  typename enable_if<
    static_query<T, execution::relationship_t::continuation_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid =
    (is_same<typename static_query<T,
      execution::relationship_t::continuation_t>::result_type,
        execution::relationship_t::continuation_t>::value));
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_REQUIRE_TRAIT)

} // namespace traits

#endif // defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_RELATIONSHIP_HPP

/* relationship.hpp
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
*/