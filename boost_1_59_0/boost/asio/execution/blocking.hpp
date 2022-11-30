//
// execution/blocking.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_BLOCKING_HPP
#define BOOST_ASIO_EXECUTION_BLOCKING_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution/execute.hpp>
#include <boost/asio/execution/executor.hpp>
#include <boost/asio/execution/scheduler.hpp>
#include <boost/asio/execution/sender.hpp>
#include <boost/asio/is_applicable_property.hpp>
#include <boost/asio/prefer.hpp>
#include <boost/asio/query.hpp>
#include <boost/asio/require.hpp>
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

/// A property to describe what guarantees an executor makes about the blocking
/// behaviour of their execution functions.
struct blocking_t
{
  /// The blocking_t property applies to executors, senders, and schedulers.
  template <typename T>
  static constexpr bool is_applicable_property_v =
    is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

  /// The top-level blocking_t property cannot be required.
  static constexpr bool is_requirable = false;

  /// The top-level blocking_t property cannot be preferred.
  static constexpr bool is_preferable = false;

  /// The type returned by queries against an @c any_executor.
  typedef blocking_t polymorphic_query_result_type;

  /// A sub-property that indicates that invocation of an executor's execution
  /// function may block pending completion of one or more invocations of the
  /// submitted function object.
  struct possibly_t
  {
    /// The blocking_t::possibly_t property applies to executors, senders, and
    /// schedulers.
    template <typename T>
    static constexpr bool is_applicable_property_v =
      is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

    /// The blocking_t::possibly_t property can be required.
    static constexpr bool is_requirable = true;

    /// The blocking_t::possibly_t property can be preferred.
    static constexpr bool is_preferable = true;

    /// The type returned by queries against an @c any_executor.
    typedef blocking_t polymorphic_query_result_type;

    /// Default constructor.
    constexpr possibly_t();

    /// Get the value associated with a property object.
    /**
     * @returns possibly_t();
     */
    static constexpr blocking_t value();
  };

  /// A sub-property that indicates that invocation of an executor's execution
  /// function shall block until completion of all invocations of the submitted
  /// function object.
  struct always_t
  {
    /// The blocking_t::always_t property applies to executors, senders, and
    /// schedulers.
    template <typename T>
    static constexpr bool is_applicable_property_v =
      is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

    /// The blocking_t::always_t property can be required.
    static constexpr bool is_requirable = true;

    /// The blocking_t::always_t property can be preferred.
    static constexpr bool is_preferable = false;

    /// The type returned by queries against an @c any_executor.
    typedef blocking_t polymorphic_query_result_type;

    /// Default constructor.
    constexpr always_t();

    /// Get the value associated with a property object.
    /**
     * @returns always_t();
     */
    static constexpr blocking_t value();
  };

  /// A sub-property that indicates that invocation of an executor's execution
  /// function shall not block pending completion of the invocations of the
  /// submitted function object.
  struct never_t
  {
    /// The blocking_t::never_t property applies to executors, senders, and
    /// schedulers.
    template <typename T>
    static constexpr bool is_applicable_property_v =
      is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

    /// The blocking_t::never_t property can be required.
    static constexpr bool is_requirable = true;

    /// The blocking_t::never_t property can be preferred.
    static constexpr bool is_preferable = true;

    /// The type returned by queries against an @c any_executor.
    typedef blocking_t polymorphic_query_result_type;

    /// Default constructor.
    constexpr never_t();

    /// Get the value associated with a property object.
    /**
     * @returns never_t();
     */
    static constexpr blocking_t value();
  };

  /// A special value used for accessing the blocking_t::possibly_t property.
  static constexpr possibly_t possibly;

  /// A special value used for accessing the blocking_t::always_t property.
  static constexpr always_t always;

  /// A special value used for accessing the blocking_t::never_t property.
  static constexpr never_t never;

  /// Default constructor.
  constexpr blocking_t();

  /// Construct from a sub-property value.
  constexpr blocking_t(possibly_t);

  /// Construct from a sub-property value.
  constexpr blocking_t(always_t);

  /// Construct from a sub-property value.
  constexpr blocking_t(never_t);

  /// Compare property values for equality.
  friend constexpr bool operator==(
      const blocking_t& a, const blocking_t& b) noexcept;

  /// Compare property values for inequality.
  friend constexpr bool operator!=(
      const blocking_t& a, const blocking_t& b) noexcept;
};

/// A special value used for accessing the blocking_t property.
constexpr blocking_t blocking;

} // namespace execution

#else // defined(GENERATING_DOCUMENTATION)

namespace execution {
namespace detail {
namespace blocking {

template <int I> struct possibly_t;
template <int I> struct always_t;
template <int I> struct never_t;

} // namespace blocking
namespace blocking_adaptation {

template <int I> struct allowed_t;

template <typename Executor, typename Function>
void blocking_execute(
    BOOST_ASIO_MOVE_ARG(Executor) ex,
    BOOST_ASIO_MOVE_ARG(Function) func);

} // namespace blocking_adaptation

template <int I = 0>
struct blocking_t
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
  typedef blocking_t polymorphic_query_result_type;

  typedef detail::blocking::possibly_t<I> possibly_t;
  typedef detail::blocking::always_t<I> always_t;
  typedef detail::blocking::never_t<I> never_t;

  BOOST_ASIO_CONSTEXPR blocking_t()
    : value_(-1)
  {
  }

  BOOST_ASIO_CONSTEXPR blocking_t(possibly_t)
    : value_(0)
  {
  }

  BOOST_ASIO_CONSTEXPR blocking_t(always_t)
    : value_(1)
  {
  }

  BOOST_ASIO_CONSTEXPR blocking_t(never_t)
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
    traits::query_member<typename proxy<T>::type, blocking_t> {};

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename static_proxy<T>::type, blocking_t> {};

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
  typename traits::static_query<T, possibly_t>::result_type
  static_query(
      typename enable_if<
        !query_static_constexpr_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !query_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        traits::static_query<T, possibly_t>::is_valid
      >::type* = 0) BOOST_ASIO_NOEXCEPT
  {
    return traits::static_query<T, possibly_t>::value();
  }

  template <typename T>
  static BOOST_ASIO_CONSTEXPR
  typename traits::static_query<T, always_t>::result_type
  static_query(
      typename enable_if<
        !query_static_constexpr_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !query_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !traits::static_query<T, possibly_t>::is_valid
      >::type* = 0,
      typename enable_if<
        traits::static_query<T, always_t>::is_valid
      >::type* = 0) BOOST_ASIO_NOEXCEPT
  {
    return traits::static_query<T, always_t>::value();
  }

  template <typename T>
  static BOOST_ASIO_CONSTEXPR
  typename traits::static_query<T, never_t>::result_type
  static_query(
      typename enable_if<
        !query_static_constexpr_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !query_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !traits::static_query<T, possibly_t>::is_valid
      >::type* = 0,
      typename enable_if<
        !traits::static_query<T, always_t>::is_valid
      >::type* = 0,
      typename enable_if<
        traits::static_query<T, never_t>::is_valid
      >::type* = 0) BOOST_ASIO_NOEXCEPT
  {
    return traits::static_query<T, never_t>::value();
  }

  template <typename E, typename T = decltype(blocking_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = blocking_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const blocking_t& a, const blocking_t& b)
  {
    return a.value_ == b.value_;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const blocking_t& a, const blocking_t& b)
  {
    return a.value_ != b.value_;
  }

  struct convertible_from_blocking_t
  {
    BOOST_ASIO_CONSTEXPR convertible_from_blocking_t(blocking_t) {}
  };

  template <typename Executor>
  friend BOOST_ASIO_CONSTEXPR blocking_t query(
      const Executor& ex, convertible_from_blocking_t,
      typename enable_if<
        can_query<const Executor&, possibly_t>::value
      >::type* = 0)
#if !defined(__clang__) // Clang crashes if noexcept is used here.
#if defined(BOOST_ASIO_MSVC) // Visual C++ wants the type to be qualified.
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, blocking_t<>::possibly_t>::value))
#else // defined(BOOST_ASIO_MSVC)
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, possibly_t>::value))
#endif // defined(BOOST_ASIO_MSVC)
#endif // !defined(__clang__)
  {
    return boost::asio::query(ex, possibly_t());
  }

  template <typename Executor>
  friend BOOST_ASIO_CONSTEXPR blocking_t query(
      const Executor& ex, convertible_from_blocking_t,
      typename enable_if<
        !can_query<const Executor&, possibly_t>::value
      >::type* = 0,
      typename enable_if<
        can_query<const Executor&, always_t>::value
      >::type* = 0)
#if !defined(__clang__) // Clang crashes if noexcept is used here.
#if defined(BOOST_ASIO_MSVC) // Visual C++ wants the type to be qualified.
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, blocking_t<>::always_t>::value))
#else // defined(BOOST_ASIO_MSVC)
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, always_t>::value))
#endif // defined(BOOST_ASIO_MSVC)
#endif // !defined(__clang__)
  {
    return boost::asio::query(ex, always_t());
  }

  template <typename Executor>
  friend BOOST_ASIO_CONSTEXPR blocking_t query(
      const Executor& ex, convertible_from_blocking_t,
      typename enable_if<
        !can_query<const Executor&, possibly_t>::value
      >::type* = 0,
      typename enable_if<
        !can_query<const Executor&, always_t>::value
      >::type* = 0,
      typename enable_if<
        can_query<const Executor&, never_t>::value
      >::type* = 0)
#if !defined(__clang__) // Clang crashes if noexcept is used here.
#if defined(BOOST_ASIO_MSVC) // Visual C++ wants the type to be qualified.
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, blocking_t<>::never_t>::value))
#else // defined(BOOST_ASIO_MSVC)
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, never_t>::value))
#endif // defined(BOOST_ASIO_MSVC)
#endif // !defined(__clang__)
  {
    return boost::asio::query(ex, never_t());
  }

  BOOST_ASIO_STATIC_CONSTEXPR_DEFAULT_INIT(possibly_t, possibly);
  BOOST_ASIO_STATIC_CONSTEXPR_DEFAULT_INIT(always_t, always);
  BOOST_ASIO_STATIC_CONSTEXPR_DEFAULT_INIT(never_t, never);

#if !defined(BOOST_ASIO_HAS_CONSTEXPR)
  static const blocking_t instance;
#endif // !defined(BOOST_ASIO_HAS_CONSTEXPR)

private:
  int value_;
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <int I> template <typename E, typename T>
const T blocking_t<I>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

#if !defined(BOOST_ASIO_HAS_CONSTEXPR)
template <int I>
const blocking_t<I> blocking_t<I>::instance;
#endif

template <int I>
const typename blocking_t<I>::possibly_t blocking_t<I>::possibly;

template <int I>
const typename blocking_t<I>::always_t blocking_t<I>::always;

template <int I>
const typename blocking_t<I>::never_t blocking_t<I>::never;

namespace blocking {

template <int I = 0>
struct possibly_t
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
  typedef blocking_t<I> polymorphic_query_result_type;

  BOOST_ASIO_CONSTEXPR possibly_t()
  {
  }

  template <typename T>
  struct query_member :
    traits::query_member<
      typename blocking_t<I>::template proxy<T>::type, possibly_t> {};

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename blocking_t<I>::template static_proxy<T>::type, possibly_t> {};

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
  static BOOST_ASIO_CONSTEXPR possibly_t static_query(
      typename enable_if<
        !query_static_constexpr_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !query_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !traits::query_free<T, possibly_t>::is_valid
      >::type* = 0,
      typename enable_if<
        !can_query<T, always_t<I> >::value
      >::type* = 0,
      typename enable_if<
        !can_query<T, never_t<I> >::value
      >::type* = 0) BOOST_ASIO_NOEXCEPT
  {
    return possibly_t();
  }

  template <typename E, typename T = decltype(possibly_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = possibly_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  static BOOST_ASIO_CONSTEXPR blocking_t<I> value()
  {
    return possibly_t();
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const possibly_t&, const possibly_t&)
  {
    return true;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const possibly_t&, const possibly_t&)
  {
    return false;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const possibly_t&, const always_t<I>&)
  {
    return false;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const possibly_t&, const always_t<I>&)
  {
    return true;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const possibly_t&, const never_t<I>&)
  {
    return false;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const possibly_t&, const never_t<I>&)
  {
    return true;
  }
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <int I> template <typename E, typename T>
const T possibly_t<I>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

template <typename Executor>
class adapter
{
public:
  adapter(int, const Executor& e) BOOST_ASIO_NOEXCEPT
    : executor_(e)
  {
  }

  adapter(const adapter& other) BOOST_ASIO_NOEXCEPT
    : executor_(other.executor_)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  adapter(adapter&& other) BOOST_ASIO_NOEXCEPT
    : executor_(BOOST_ASIO_MOVE_CAST(Executor)(other.executor_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  template <int I>
  static BOOST_ASIO_CONSTEXPR always_t<I> query(
      blocking_t<I>) BOOST_ASIO_NOEXCEPT
  {
    return always_t<I>();
  }

  template <int I>
  static BOOST_ASIO_CONSTEXPR always_t<I> query(
      possibly_t<I>) BOOST_ASIO_NOEXCEPT
  {
    return always_t<I>();
  }

  template <int I>
  static BOOST_ASIO_CONSTEXPR always_t<I> query(
      always_t<I>) BOOST_ASIO_NOEXCEPT
  {
    return always_t<I>();
  }

  template <int I>
  static BOOST_ASIO_CONSTEXPR always_t<I> query(
      never_t<I>) BOOST_ASIO_NOEXCEPT
  {
    return always_t<I>();
  }

  template <typename Property>
  typename enable_if<
    can_query<const Executor&, Property>::value,
    typename query_result<const Executor&, Property>::type
  >::type query(const Property& p) const
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, Property>::value))
  {
    return boost::asio::query(executor_, p);
  }

  template <int I>
  typename enable_if<
    can_require<const Executor&, possibly_t<I> >::value,
    typename require_result<const Executor&, possibly_t<I> >::type
  >::type require(possibly_t<I>) const BOOST_ASIO_NOEXCEPT
  {
    return boost::asio::require(executor_, possibly_t<I>());
  }

  template <int I>
  typename enable_if<
    can_require<const Executor&, never_t<I> >::value,
    typename require_result<const Executor&, never_t<I> >::type
  >::type require(never_t<I>) const BOOST_ASIO_NOEXCEPT
  {
    return boost::asio::require(executor_, never_t<I>());
  }

  template <typename Property>
  typename enable_if<
    can_require<const Executor&, Property>::value,
    adapter<typename decay<
      typename require_result<const Executor&, Property>::type
    >::type>
  >::type require(const Property& p) const
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_require<const Executor&, Property>::value))
  {
    return adapter<typename decay<
      typename require_result<const Executor&, Property>::type
        >::type>(0, boost::asio::require(executor_, p));
  }

  template <typename Property>
  typename enable_if<
    can_prefer<const Executor&, Property>::value,
    adapter<typename decay<
      typename prefer_result<const Executor&, Property>::type
    >::type>
  >::type prefer(const Property& p) const
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_prefer<const Executor&, Property>::value))
  {
    return adapter<typename decay<
      typename prefer_result<const Executor&, Property>::type
        >::type>(0, boost::asio::prefer(executor_, p));
  }

  template <typename Function>
  typename enable_if<
    execution::can_execute<const Executor&, Function>::value
  >::type execute(BOOST_ASIO_MOVE_ARG(Function) f) const
  {
    blocking_adaptation::blocking_execute(
        executor_, BOOST_ASIO_MOVE_CAST(Function)(f));
  }

  friend bool operator==(const adapter& a, const adapter& b) BOOST_ASIO_NOEXCEPT
  {
    return a.executor_ == b.executor_;
  }

  friend bool operator!=(const adapter& a, const adapter& b) BOOST_ASIO_NOEXCEPT
  {
    return a.executor_ != b.executor_;
  }

private:
  Executor executor_;
};

template <int I = 0>
struct always_t
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
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_preferable = false);
  typedef blocking_t<I> polymorphic_query_result_type;

  BOOST_ASIO_CONSTEXPR always_t()
  {
  }

  template <typename T>
  struct query_member :
    traits::query_member<
      typename blocking_t<I>::template proxy<T>::type, always_t> {};

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename blocking_t<I>::template static_proxy<T>::type, always_t> {};

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

  template <typename E, typename T = decltype(always_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = always_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  static BOOST_ASIO_CONSTEXPR blocking_t<I> value()
  {
    return always_t();
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const always_t&, const always_t&)
  {
    return true;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const always_t&, const always_t&)
  {
    return false;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const always_t&, const possibly_t<I>&)
  {
    return false;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const always_t&, const possibly_t<I>&)
  {
    return true;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const always_t&, const never_t<I>&)
  {
    return false;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const always_t&, const never_t<I>&)
  {
    return true;
  }

  template <typename Executor>
  friend adapter<Executor> require(
      const Executor& e, const always_t&,
      typename enable_if<
        is_executor<Executor>::value
      >::type* = 0,
      typename enable_if<
        traits::static_require<
          const Executor&,
          blocking_adaptation::allowed_t<0>
        >::is_valid
      >::type* = 0)
  {
    return adapter<Executor>(0, e);
  }
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <int I> template <typename E, typename T>
const T always_t<I>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

template <int I>
struct never_t
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
  typedef blocking_t<I> polymorphic_query_result_type;

  BOOST_ASIO_CONSTEXPR never_t()
  {
  }

  template <typename T>
  struct query_member :
    traits::query_member<
      typename blocking_t<I>::template proxy<T>::type, never_t> {};

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename blocking_t<I>::template static_proxy<T>::type, never_t> {};

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

  template <typename E, typename T = decltype(never_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = never_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  static BOOST_ASIO_CONSTEXPR blocking_t<I> value()
  {
    return never_t();
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const never_t&, const never_t&)
  {
    return true;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const never_t&, const never_t&)
  {
    return false;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const never_t&, const possibly_t<I>&)
  {
    return false;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const never_t&, const possibly_t<I>&)
  {
    return true;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const never_t&, const always_t<I>&)
  {
    return false;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const never_t&, const always_t<I>&)
  {
    return true;
  }
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <int I> template <typename E, typename T>
const T never_t<I>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

} // namespace blocking
} // namespace detail

typedef detail::blocking_t<> blocking_t;

#if defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
constexpr blocking_t blocking;
#else // defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
namespace { static const blocking_t& blocking = blocking_t::instance; }
#endif

} // namespace execution

#if !defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T>
struct is_applicable_property<T, execution::blocking_t>
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
struct is_applicable_property<T, execution::blocking_t::possibly_t>
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
struct is_applicable_property<T, execution::blocking_t::always_t>
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
struct is_applicable_property<T, execution::blocking_t::never_t>
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
struct query_free_default<T, execution::blocking_t,
  typename enable_if<
    can_query<T, execution::blocking_t::possibly_t>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    (is_nothrow_query<T, execution::blocking_t::possibly_t>::value));

  typedef execution::blocking_t result_type;
};

template <typename T>
struct query_free_default<T, execution::blocking_t,
  typename enable_if<
    !can_query<T, execution::blocking_t::possibly_t>::value
      && can_query<T, execution::blocking_t::always_t>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    (is_nothrow_query<T, execution::blocking_t::always_t>::value));

  typedef execution::blocking_t result_type;
};

template <typename T>
struct query_free_default<T, execution::blocking_t,
  typename enable_if<
    !can_query<T, execution::blocking_t::possibly_t>::value
      && !can_query<T, execution::blocking_t::always_t>::value
      && can_query<T, execution::blocking_t::never_t>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    (is_nothrow_query<T, execution::blocking_t::never_t>::value));

  typedef execution::blocking_t result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_FREE_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  || !defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

template <typename T>
struct static_query<T, execution::blocking_t,
  typename enable_if<
    execution::detail::blocking_t<0>::
      query_static_constexpr_member<T>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename execution::detail::blocking_t<0>::
    query_static_constexpr_member<T>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return execution::blocking_t::query_static_constexpr_member<T>::value();
  }
};

template <typename T>
struct static_query<T, execution::blocking_t,
  typename enable_if<
    !execution::detail::blocking_t<0>::
        query_static_constexpr_member<T>::is_valid
      && !execution::detail::blocking_t<0>::
        query_member<T>::is_valid
      && traits::static_query<T, execution::blocking_t::possibly_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename traits::static_query<T,
    execution::blocking_t::possibly_t>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return traits::static_query<T, execution::blocking_t::possibly_t>::value();
  }
};

template <typename T>
struct static_query<T, execution::blocking_t,
  typename enable_if<
    !execution::detail::blocking_t<0>::
        query_static_constexpr_member<T>::is_valid
      && !execution::detail::blocking_t<0>::
        query_member<T>::is_valid
      && !traits::static_query<T, execution::blocking_t::possibly_t>::is_valid
      && traits::static_query<T, execution::blocking_t::always_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename traits::static_query<T,
    execution::blocking_t::always_t>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return traits::static_query<T, execution::blocking_t::always_t>::value();
  }
};

template <typename T>
struct static_query<T, execution::blocking_t,
  typename enable_if<
    !execution::detail::blocking_t<0>::
        query_static_constexpr_member<T>::is_valid
      && !execution::detail::blocking_t<0>::
        query_member<T>::is_valid
      && !traits::static_query<T, execution::blocking_t::possibly_t>::is_valid
      && !traits::static_query<T, execution::blocking_t::always_t>::is_valid
      && traits::static_query<T, execution::blocking_t::never_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename traits::static_query<T,
    execution::blocking_t::never_t>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return traits::static_query<T, execution::blocking_t::never_t>::value();
  }
};

template <typename T>
struct static_query<T, execution::blocking_t::possibly_t,
  typename enable_if<
    execution::detail::blocking::possibly_t<0>::
      query_static_constexpr_member<T>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename execution::detail::blocking::possibly_t<0>::
    query_static_constexpr_member<T>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return execution::detail::blocking::possibly_t<0>::
      query_static_constexpr_member<T>::value();
  }
};

template <typename T>
struct static_query<T, execution::blocking_t::possibly_t,
  typename enable_if<
    !execution::detail::blocking::possibly_t<0>::
        query_static_constexpr_member<T>::is_valid
      && !execution::detail::blocking::possibly_t<0>::
        query_member<T>::is_valid
      && !traits::query_free<T, execution::blocking_t::possibly_t>::is_valid
      && !can_query<T, execution::blocking_t::always_t>::value
      && !can_query<T, execution::blocking_t::never_t>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef execution::blocking_t::possibly_t result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return result_type();
  }
};

template <typename T>
struct static_query<T, execution::blocking_t::always_t,
  typename enable_if<
    execution::detail::blocking::always_t<0>::
      query_static_constexpr_member<T>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename execution::detail::blocking::always_t<0>::
    query_static_constexpr_member<T>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return execution::detail::blocking::always_t<0>::
      query_static_constexpr_member<T>::value();
  }
};

template <typename T>
struct static_query<T, execution::blocking_t::never_t,
  typename enable_if<
    execution::detail::blocking::never_t<0>::
      query_static_constexpr_member<T>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename execution::detail::blocking::never_t<0>::
    query_static_constexpr_member<T>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return execution::detail::blocking::never_t<0>::
      query_static_constexpr_member<T>::value();
  }
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   || !defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

#if !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_REQUIRE_TRAIT)

template <typename T>
struct static_require<T, execution::blocking_t::possibly_t,
  typename enable_if<
    static_query<T, execution::blocking_t::possibly_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid =
    (is_same<typename static_query<T,
      execution::blocking_t::possibly_t>::result_type,
        execution::blocking_t::possibly_t>::value));
};

template <typename T>
struct static_require<T, execution::blocking_t::always_t,
  typename enable_if<
    static_query<T, execution::blocking_t::always_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid =
    (is_same<typename static_query<T,
      execution::blocking_t::always_t>::result_type,
        execution::blocking_t::always_t>::value));
};

template <typename T>
struct static_require<T, execution::blocking_t::never_t,
  typename enable_if<
    static_query<T, execution::blocking_t::never_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid =
    (is_same<typename static_query<T,
      execution::blocking_t::never_t>::result_type,
        execution::blocking_t::never_t>::value));
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_REQUIRE_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_FREE_TRAIT)

template <typename T>
struct require_free_default<T, execution::blocking_t::always_t,
  typename enable_if<
    is_same<T, typename decay<T>::type>::value
      && execution::is_executor<T>::value
      && traits::static_require<
          const T&,
          execution::detail::blocking_adaptation::allowed_t<0>
        >::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef execution::detail::blocking::adapter<T> result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_FREE_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_EQUALITY_COMPARABLE_TRAIT)

template <typename Executor>
struct equality_comparable<
  execution::detail::blocking::adapter<Executor> >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_EQUALITY_COMPARABLE_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_EXECUTE_MEMBER_TRAIT)

template <typename Executor, typename Function>
struct execute_member<
  execution::detail::blocking::adapter<Executor>, Function>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef void result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_EXECUTE_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_STATIC_CONSTEXPR_MEMBER_TRAIT)

template <typename Executor, int I>
struct query_static_constexpr_member<
  execution::detail::blocking::adapter<Executor>,
  execution::detail::blocking_t<I> >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef execution::blocking_t::always_t result_type;

  static BOOST_ASIO_CONSTEXPR result_type value() BOOST_ASIO_NOEXCEPT
  {
    return result_type();
  }
};

template <typename Executor, int I>
struct query_static_constexpr_member<
  execution::detail::blocking::adapter<Executor>,
  execution::detail::blocking::always_t<I> >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef execution::blocking_t::always_t result_type;

  static BOOST_ASIO_CONSTEXPR result_type value() BOOST_ASIO_NOEXCEPT
  {
    return result_type();
  }
};

template <typename Executor, int I>
struct query_static_constexpr_member<
  execution::detail::blocking::adapter<Executor>,
  execution::detail::blocking::possibly_t<I> >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef execution::blocking_t::always_t result_type;

  static BOOST_ASIO_CONSTEXPR result_type value() BOOST_ASIO_NOEXCEPT
  {
    return result_type();
  }
};

template <typename Executor, int I>
struct query_static_constexpr_member<
  execution::detail::blocking::adapter<Executor>,
  execution::detail::blocking::never_t<I> >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef execution::blocking_t::always_t result_type;

  static BOOST_ASIO_CONSTEXPR result_type value() BOOST_ASIO_NOEXCEPT
  {
    return result_type();
  }
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_STATIC_CONSTEXPR_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_MEMBER_TRAIT)

template <typename Executor, typename Property>
struct query_member<
  execution::detail::blocking::adapter<Executor>, Property,
  typename enable_if<
    can_query<const Executor&, Property>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
      (is_nothrow_query<Executor, Property>::value));
  typedef typename query_result<Executor, Property>::type result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_MEMBER_TRAIT)

template <typename Executor, int I>
struct require_member<
  execution::detail::blocking::adapter<Executor>,
  execution::detail::blocking::possibly_t<I>,
  typename enable_if<
    can_require<
      const Executor&,
      execution::detail::blocking::possibly_t<I>
    >::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
      (is_nothrow_require<const Executor&,
        execution::detail::blocking::possibly_t<I> >::value));
  typedef typename require_result<const Executor&,
    execution::detail::blocking::possibly_t<I> >::type result_type;
};

template <typename Executor, int I>
struct require_member<
  execution::detail::blocking::adapter<Executor>,
  execution::detail::blocking::never_t<I>,
  typename enable_if<
    can_require<
      const Executor&,
      execution::detail::blocking::never_t<I>
    >::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
      (is_nothrow_require<const Executor&,
        execution::detail::blocking::never_t<I> >::value));
  typedef typename require_result<const Executor&,
    execution::detail::blocking::never_t<I> >::type result_type;
};

template <typename Executor, typename Property>
struct require_member<
  execution::detail::blocking::adapter<Executor>, Property,
  typename enable_if<
    can_require<const Executor&, Property>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
      (is_nothrow_require<Executor, Property>::value));
  typedef execution::detail::blocking::adapter<typename decay<
    typename require_result<Executor, Property>::type
      >::type> result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_PREFER_MEMBER_TRAIT)

template <typename Executor, typename Property>
struct prefer_member<
  execution::detail::blocking::adapter<Executor>, Property,
  typename enable_if<
    can_prefer<const Executor&, Property>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
      (is_nothrow_prefer<Executor, Property>::value));
  typedef execution::detail::blocking::adapter<typename decay<
    typename prefer_result<Executor, Property>::type
      >::type> result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_PREFER_MEMBER_TRAIT)

} // namespace traits

#endif // defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_BLOCKING_HPP

/* blocking.hpp
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
*/