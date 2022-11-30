//
// execution/mapping.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_MAPPING_HPP
#define BOOST_ASIO_EXECUTION_MAPPING_HPP

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

/// A property to describe what guarantees an executor makes about the mapping
/// of execution agents on to threads of execution.
struct mapping_t
{
  /// The mapping_t property applies to executors, senders, and schedulers.
  template <typename T>
  static constexpr bool is_applicable_property_v =
    is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

  /// The top-level mapping_t property cannot be required.
  static constexpr bool is_requirable = false;

  /// The top-level mapping_t property cannot be preferred.
  static constexpr bool is_preferable = false;

  /// The type returned by queries against an @c any_executor.
  typedef mapping_t polymorphic_query_result_type;

  /// A sub-property that indicates that execution agents are mapped on to
  /// threads of execution.
  struct thread_t
  {
    /// The mapping_t::thread_t property applies to executors, senders, and
    /// schedulers.
    template <typename T>
    static constexpr bool is_applicable_property_v =
      is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

    /// The mapping_t::thread_t property can be required.
    static constexpr bool is_requirable = true;

    /// The mapping_t::thread_t property can be preferred.
    static constexpr bool is_preferable = true;

    /// The type returned by queries against an @c any_executor.
    typedef mapping_t polymorphic_query_result_type;

    /// Default constructor.
    constexpr thread_t();

    /// Get the value associated with a property object.
    /**
     * @returns thread_t();
     */
    static constexpr mapping_t value();
  };

  /// A sub-property that indicates that execution agents are mapped on to
  /// new threads of execution.
  struct new_thread_t
  {
    /// The mapping_t::new_thread_t property applies to executors, senders, and
    /// schedulers.
    template <typename T>
    static constexpr bool is_applicable_property_v =
      is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

    /// The mapping_t::new_thread_t property can be required.
    static constexpr bool is_requirable = true;

    /// The mapping_t::new_thread_t property can be preferred.
    static constexpr bool is_preferable = true;

    /// The type returned by queries against an @c any_executor.
    typedef mapping_t polymorphic_query_result_type;

    /// Default constructor.
    constexpr new_thread_t();

    /// Get the value associated with a property object.
    /**
     * @returns new_thread_t();
     */
    static constexpr mapping_t value();
  };

  /// A sub-property that indicates that the mapping of execution agents is
  /// implementation-defined.
  struct other_t
  {
    /// The mapping_t::other_t property applies to executors, senders, and
    /// schedulers.
    template <typename T>
    static constexpr bool is_applicable_property_v =
      is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

    /// The mapping_t::other_t property can be required.
    static constexpr bool is_requirable = true;

    /// The mapping_t::other_t property can be preferred.
    static constexpr bool is_preferable = true;

    /// The type returned by queries against an @c any_executor.
    typedef mapping_t polymorphic_query_result_type;

    /// Default constructor.
    constexpr other_t();

    /// Get the value associated with a property object.
    /**
     * @returns other_t();
     */
    static constexpr mapping_t value();
  };

  /// A special value used for accessing the mapping_t::thread_t property.
  static constexpr thread_t thread;

  /// A special value used for accessing the mapping_t::new_thread_t property.
  static constexpr new_thread_t new_thread;

  /// A special value used for accessing the mapping_t::other_t property.
  static constexpr other_t other;

  /// Default constructor.
  constexpr mapping_t();

  /// Construct from a sub-property value.
  constexpr mapping_t(thread_t);

  /// Construct from a sub-property value.
  constexpr mapping_t(new_thread_t);

  /// Construct from a sub-property value.
  constexpr mapping_t(other_t);

  /// Compare property values for equality.
  friend constexpr bool operator==(
      const mapping_t& a, const mapping_t& b) noexcept;

  /// Compare property values for inequality.
  friend constexpr bool operator!=(
      const mapping_t& a, const mapping_t& b) noexcept;
};

/// A special value used for accessing the mapping_t property.
constexpr mapping_t mapping;

} // namespace execution

#else // defined(GENERATING_DOCUMENTATION)

namespace execution {
namespace detail {
namespace mapping {

template <int I> struct thread_t;
template <int I> struct new_thread_t;
template <int I> struct other_t;

} // namespace mapping

template <int I = 0>
struct mapping_t
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
  typedef mapping_t polymorphic_query_result_type;

  typedef detail::mapping::thread_t<I> thread_t;
  typedef detail::mapping::new_thread_t<I> new_thread_t;
  typedef detail::mapping::other_t<I> other_t;

  BOOST_ASIO_CONSTEXPR mapping_t()
    : value_(-1)
  {
  }

  BOOST_ASIO_CONSTEXPR mapping_t(thread_t)
    : value_(0)
  {
  }

  BOOST_ASIO_CONSTEXPR mapping_t(new_thread_t)
    : value_(1)
  {
  }

  BOOST_ASIO_CONSTEXPR mapping_t(other_t)
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
    traits::query_member<typename proxy<T>::type, mapping_t> {};

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename static_proxy<T>::type, mapping_t> {};

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
  typename traits::static_query<T, thread_t>::result_type
  static_query(
      typename enable_if<
        !query_static_constexpr_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !query_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        traits::static_query<T, thread_t>::is_valid
      >::type* = 0) BOOST_ASIO_NOEXCEPT
  {
    return traits::static_query<T, thread_t>::value();
  }

  template <typename T>
  static BOOST_ASIO_CONSTEXPR
  typename traits::static_query<T, new_thread_t>::result_type
  static_query(
      typename enable_if<
        !query_static_constexpr_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !query_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !traits::static_query<T, thread_t>::is_valid
      >::type* = 0,
      typename enable_if<
        traits::static_query<T, new_thread_t>::is_valid
      >::type* = 0) BOOST_ASIO_NOEXCEPT
  {
    return traits::static_query<T, new_thread_t>::value();
  }

  template <typename T>
  static BOOST_ASIO_CONSTEXPR
  typename traits::static_query<T, other_t>::result_type
  static_query(
      typename enable_if<
        !query_static_constexpr_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !query_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !traits::static_query<T, thread_t>::is_valid
      >::type* = 0,
      typename enable_if<
        !traits::static_query<T, new_thread_t>::is_valid
      >::type* = 0,
      typename enable_if<
        traits::static_query<T, other_t>::is_valid
      >::type* = 0) BOOST_ASIO_NOEXCEPT
  {
    return traits::static_query<T, other_t>::value();
  }

  template <typename E, typename T = decltype(mapping_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = mapping_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const mapping_t& a, const mapping_t& b)
  {
    return a.value_ == b.value_;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const mapping_t& a, const mapping_t& b)
  {
    return a.value_ != b.value_;
  }

  struct convertible_from_mapping_t
  {
    BOOST_ASIO_CONSTEXPR convertible_from_mapping_t(mapping_t) {}
  };

  template <typename Executor>
  friend BOOST_ASIO_CONSTEXPR mapping_t query(
      const Executor& ex, convertible_from_mapping_t,
      typename enable_if<
        can_query<const Executor&, thread_t>::value
      >::type* = 0)
#if !defined(__clang__) // Clang crashes if noexcept is used here.
#if defined(BOOST_ASIO_MSVC) // Visual C++ wants the type to be qualified.
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, mapping_t<>::thread_t>::value))
#else // defined(BOOST_ASIO_MSVC)
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, thread_t>::value))
#endif // defined(BOOST_ASIO_MSVC)
#endif // !defined(__clang__)
  {
    return boost::asio::query(ex, thread_t());
  }

  template <typename Executor>
  friend BOOST_ASIO_CONSTEXPR mapping_t query(
      const Executor& ex, convertible_from_mapping_t,
      typename enable_if<
        !can_query<const Executor&, thread_t>::value
      >::type* = 0,
      typename enable_if<
        can_query<const Executor&, new_thread_t>::value
      >::type* = 0)
#if !defined(__clang__) // Clang crashes if noexcept is used here.
#if defined(BOOST_ASIO_MSVC) // Visual C++ wants the type to be qualified.
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, mapping_t<>::new_thread_t>::value))
#else // defined(BOOST_ASIO_MSVC)
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, new_thread_t>::value))
#endif // defined(BOOST_ASIO_MSVC)
#endif // !defined(__clang__)
  {
    return boost::asio::query(ex, new_thread_t());
  }

  template <typename Executor>
  friend BOOST_ASIO_CONSTEXPR mapping_t query(
      const Executor& ex, convertible_from_mapping_t,
      typename enable_if<
        !can_query<const Executor&, thread_t>::value
      >::type* = 0,
      typename enable_if<
        !can_query<const Executor&, new_thread_t>::value
      >::type* = 0,
      typename enable_if<
        can_query<const Executor&, other_t>::value
      >::type* = 0)
#if !defined(__clang__) // Clang crashes if noexcept is used here.
#if defined(BOOST_ASIO_MSVC) // Visual C++ wants the type to be qualified.
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, mapping_t<>::other_t>::value))
#else // defined(BOOST_ASIO_MSVC)
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, other_t>::value))
#endif // defined(BOOST_ASIO_MSVC)
#endif // !defined(__clang__)
  {
    return boost::asio::query(ex, other_t());
  }

  BOOST_ASIO_STATIC_CONSTEXPR_DEFAULT_INIT(thread_t, thread);
  BOOST_ASIO_STATIC_CONSTEXPR_DEFAULT_INIT(new_thread_t, new_thread);
  BOOST_ASIO_STATIC_CONSTEXPR_DEFAULT_INIT(other_t, other);

#if !defined(BOOST_ASIO_HAS_CONSTEXPR)
  static const mapping_t instance;
#endif // !defined(BOOST_ASIO_HAS_CONSTEXPR)

private:
  int value_;
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <int I> template <typename E, typename T>
const T mapping_t<I>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

#if !defined(BOOST_ASIO_HAS_CONSTEXPR)
template <int I>
const mapping_t<I> mapping_t<I>::instance;
#endif

template <int I>
const typename mapping_t<I>::thread_t mapping_t<I>::thread;

template <int I>
const typename mapping_t<I>::new_thread_t mapping_t<I>::new_thread;

template <int I>
const typename mapping_t<I>::other_t mapping_t<I>::other;

namespace mapping {

template <int I = 0>
struct thread_t
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
  typedef mapping_t<I> polymorphic_query_result_type;

  BOOST_ASIO_CONSTEXPR thread_t()
  {
  }

  template <typename T>
  struct query_member :
    traits::query_member<
      typename mapping_t<I>::template proxy<T>::type, thread_t> {};

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename mapping_t<I>::template static_proxy<T>::type, thread_t> {};

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
  static BOOST_ASIO_CONSTEXPR thread_t static_query(
      typename enable_if<
        !query_static_constexpr_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !query_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !traits::query_free<T, thread_t>::is_valid
      >::type* = 0,
      typename enable_if<
        !can_query<T, new_thread_t<I> >::value
      >::type* = 0,
      typename enable_if<
        !can_query<T, other_t<I> >::value
      >::type* = 0) BOOST_ASIO_NOEXCEPT
  {
    return thread_t();
  }

  template <typename E, typename T = decltype(thread_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = thread_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  static BOOST_ASIO_CONSTEXPR mapping_t<I> value()
  {
    return thread_t();
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const thread_t&, const thread_t&)
  {
    return true;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const thread_t&, const thread_t&)
  {
    return false;
  }
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <int I> template <typename E, typename T>
const T thread_t<I>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

template <int I = 0>
struct new_thread_t
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
  typedef mapping_t<I> polymorphic_query_result_type;

  BOOST_ASIO_CONSTEXPR new_thread_t()
  {
  }

  template <typename T>
  struct query_member :
    traits::query_member<
      typename mapping_t<I>::template proxy<T>::type, new_thread_t> {};

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename mapping_t<I>::template static_proxy<T>::type, new_thread_t> {};

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

  template <typename E, typename T = decltype(new_thread_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = new_thread_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  static BOOST_ASIO_CONSTEXPR mapping_t<I> value()
  {
    return new_thread_t();
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const new_thread_t&, const new_thread_t&)
  {
    return true;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const new_thread_t&, const new_thread_t&)
  {
    return false;
  }
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <int I> template <typename E, typename T>
const T new_thread_t<I>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

template <int I>
struct other_t
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
  typedef mapping_t<I> polymorphic_query_result_type;

  BOOST_ASIO_CONSTEXPR other_t()
  {
  }

  template <typename T>
  struct query_member :
    traits::query_member<
      typename mapping_t<I>::template proxy<T>::type, other_t> {};

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename mapping_t<I>::template static_proxy<T>::type, other_t> {};

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

  template <typename E, typename T = decltype(other_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = other_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  static BOOST_ASIO_CONSTEXPR mapping_t<I> value()
  {
    return other_t();
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const other_t&, const other_t&)
  {
    return true;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const other_t&, const other_t&)
  {
    return false;
  }
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <int I> template <typename E, typename T>
const T other_t<I>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

} // namespace mapping
} // namespace detail

typedef detail::mapping_t<> mapping_t;

#if defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
constexpr mapping_t mapping;
#else // defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
namespace { static const mapping_t& mapping = mapping_t::instance; }
#endif

} // namespace execution

#if !defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T>
struct is_applicable_property<T, execution::mapping_t>
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
struct is_applicable_property<T, execution::mapping_t::thread_t>
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
struct is_applicable_property<T, execution::mapping_t::new_thread_t>
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
struct is_applicable_property<T, execution::mapping_t::other_t>
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
struct query_free_default<T, execution::mapping_t,
  typename enable_if<
    can_query<T, execution::mapping_t::thread_t>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    (is_nothrow_query<T, execution::mapping_t::thread_t>::value));

  typedef execution::mapping_t result_type;
};

template <typename T>
struct query_free_default<T, execution::mapping_t,
  typename enable_if<
    !can_query<T, execution::mapping_t::thread_t>::value
      && can_query<T, execution::mapping_t::new_thread_t>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    (is_nothrow_query<T, execution::mapping_t::new_thread_t>::value));

  typedef execution::mapping_t result_type;
};

template <typename T>
struct query_free_default<T, execution::mapping_t,
  typename enable_if<
    !can_query<T, execution::mapping_t::thread_t>::value
      && !can_query<T, execution::mapping_t::new_thread_t>::value
      && can_query<T, execution::mapping_t::other_t>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    (is_nothrow_query<T, execution::mapping_t::other_t>::value));

  typedef execution::mapping_t result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_FREE_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  || !defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

template <typename T>
struct static_query<T, execution::mapping_t,
  typename enable_if<
    execution::detail::mapping_t<0>::
      query_static_constexpr_member<T>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename execution::detail::mapping_t<0>::
    query_static_constexpr_member<T>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return execution::detail::mapping_t<0>::
      query_static_constexpr_member<T>::value();
  }
};

template <typename T>
struct static_query<T, execution::mapping_t,
  typename enable_if<
    !execution::detail::mapping_t<0>::
        query_static_constexpr_member<T>::is_valid
      && !execution::detail::mapping_t<0>::
        query_member<T>::is_valid
      && traits::static_query<T, execution::mapping_t::thread_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename traits::static_query<T,
    execution::mapping_t::thread_t>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return traits::static_query<T, execution::mapping_t::thread_t>::value();
  }
};

template <typename T>
struct static_query<T, execution::mapping_t,
  typename enable_if<
    !execution::detail::mapping_t<0>::
        query_static_constexpr_member<T>::is_valid
      && !execution::detail::mapping_t<0>::
        query_member<T>::is_valid
      && !traits::static_query<T, execution::mapping_t::thread_t>::is_valid
      && traits::static_query<T, execution::mapping_t::new_thread_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename traits::static_query<T,
    execution::mapping_t::new_thread_t>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return traits::static_query<T, execution::mapping_t::new_thread_t>::value();
  }
};

template <typename T>
struct static_query<T, execution::mapping_t,
  typename enable_if<
    !execution::detail::mapping_t<0>::
        query_static_constexpr_member<T>::is_valid
      && !execution::detail::mapping_t<0>::
        query_member<T>::is_valid
      && !traits::static_query<T, execution::mapping_t::thread_t>::is_valid
      && !traits::static_query<T, execution::mapping_t::new_thread_t>::is_valid
      && traits::static_query<T, execution::mapping_t::other_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename traits::static_query<T,
    execution::mapping_t::other_t>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return traits::static_query<T, execution::mapping_t::other_t>::value();
  }
};

template <typename T>
struct static_query<T, execution::mapping_t::thread_t,
  typename enable_if<
    execution::detail::mapping::thread_t<0>::
      query_static_constexpr_member<T>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename execution::detail::mapping::thread_t<0>::
    query_static_constexpr_member<T>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return execution::detail::mapping::thread_t<0>::
      query_static_constexpr_member<T>::value();
  }
};

template <typename T>
struct static_query<T, execution::mapping_t::thread_t,
  typename enable_if<
    !execution::detail::mapping::thread_t<0>::
        query_static_constexpr_member<T>::is_valid
      && !execution::detail::mapping::thread_t<0>::
        query_member<T>::is_valid
      && !traits::query_free<T, execution::mapping_t::thread_t>::is_valid
      && !can_query<T, execution::mapping_t::new_thread_t>::value
      && !can_query<T, execution::mapping_t::other_t>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef execution::mapping_t::thread_t result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return result_type();
  }
};

template <typename T>
struct static_query<T, execution::mapping_t::new_thread_t,
  typename enable_if<
    execution::detail::mapping::new_thread_t<0>::
      query_static_constexpr_member<T>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename execution::detail::mapping::new_thread_t<0>::
    query_static_constexpr_member<T>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return execution::detail::mapping::new_thread_t<0>::
      query_static_constexpr_member<T>::value();
  }
};

template <typename T>
struct static_query<T, execution::mapping_t::other_t,
  typename enable_if<
    execution::detail::mapping::other_t<0>::
      query_static_constexpr_member<T>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename execution::detail::mapping::other_t<0>::
    query_static_constexpr_member<T>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return execution::detail::mapping::other_t<0>::
      query_static_constexpr_member<T>::value();
  }
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   || !defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

#if !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_REQUIRE_TRAIT)

template <typename T>
struct static_require<T, execution::mapping_t::thread_t,
  typename enable_if<
    static_query<T, execution::mapping_t::thread_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid =
    (is_same<typename static_query<T,
      execution::mapping_t::thread_t>::result_type,
        execution::mapping_t::thread_t>::value));
};

template <typename T>
struct static_require<T, execution::mapping_t::new_thread_t,
  typename enable_if<
    static_query<T, execution::mapping_t::new_thread_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid =
    (is_same<typename static_query<T,
      execution::mapping_t::new_thread_t>::result_type,
        execution::mapping_t::new_thread_t>::value));
};

template <typename T>
struct static_require<T, execution::mapping_t::other_t,
  typename enable_if<
    static_query<T, execution::mapping_t::other_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid =
    (is_same<typename static_query<T,
      execution::mapping_t::other_t>::result_type,
        execution::mapping_t::other_t>::value));
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_REQUIRE_TRAIT)

} // namespace traits

#endif // defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_MAPPING_HPP

/* mapping.hpp
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
*/