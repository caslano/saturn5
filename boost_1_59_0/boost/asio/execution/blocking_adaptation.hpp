//
// execution/blocking_adaptation.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_BLOCKING_ADAPTATION_HPP
#define BOOST_ASIO_EXECUTION_BLOCKING_ADAPTATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/event.hpp>
#include <boost/asio/detail/mutex.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution/execute.hpp>
#include <boost/asio/execution/executor.hpp>
#include <boost/asio/execution/scheduler.hpp>
#include <boost/asio/execution/sender.hpp>
#include <boost/asio/is_applicable_property.hpp>
#include <boost/asio/prefer.hpp>
#include <boost/asio/query.hpp>
#include <boost/asio/require.hpp>
#include <boost/asio/traits/prefer_member.hpp>
#include <boost/asio/traits/query_free.hpp>
#include <boost/asio/traits/query_member.hpp>
#include <boost/asio/traits/query_static_constexpr_member.hpp>
#include <boost/asio/traits/require_member.hpp>
#include <boost/asio/traits/static_query.hpp>
#include <boost/asio/traits/static_require.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if defined(GENERATING_DOCUMENTATION)

namespace execution {

/// A property to describe whether automatic adaptation of an executor is
/// allowed in order to apply the blocking_adaptation_t::allowed_t property.
struct blocking_adaptation_t
{
  /// The blocking_adaptation_t property applies to executors, senders, and
  /// schedulers.
  template <typename T>
  static constexpr bool is_applicable_property_v =
    is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

  /// The top-level blocking_adaptation_t property cannot be required.
  static constexpr bool is_requirable = false;

  /// The top-level blocking_adaptation_t property cannot be preferred.
  static constexpr bool is_preferable = false;

  /// The type returned by queries against an @c any_executor.
  typedef blocking_adaptation_t polymorphic_query_result_type;

  /// A sub-property that indicates that automatic adaptation is not allowed.
  struct disallowed_t
  {
    /// The blocking_adaptation_t::disallowed_t property applies to executors,
    /// senders, and schedulers.
    template <typename T>
    static constexpr bool is_applicable_property_v =
      is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

    /// The blocking_adaptation_t::disallowed_t property can be required.
    static constexpr bool is_requirable = true;

    /// The blocking_adaptation_t::disallowed_t property can be preferred.
    static constexpr bool is_preferable = true;

    /// The type returned by queries against an @c any_executor.
    typedef blocking_adaptation_t polymorphic_query_result_type;

    /// Default constructor.
    constexpr disallowed_t();

    /// Get the value associated with a property object.
    /**
     * @returns disallowed_t();
     */
    static constexpr blocking_adaptation_t value();
  };

  /// A sub-property that indicates that automatic adaptation is allowed.
  struct allowed_t
  {
    /// The blocking_adaptation_t::allowed_t property applies to executors,
    /// senders, and schedulers.
    template <typename T>
    static constexpr bool is_applicable_property_v =
      is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

    /// The blocking_adaptation_t::allowed_t property can be required.
    static constexpr bool is_requirable = true;

    /// The blocking_adaptation_t::allowed_t property can be preferred.
    static constexpr bool is_preferable = false;

    /// The type returned by queries against an @c any_executor.
    typedef blocking_adaptation_t polymorphic_query_result_type;

    /// Default constructor.
    constexpr allowed_t();

    /// Get the value associated with a property object.
    /**
     * @returns allowed_t();
     */
    static constexpr blocking_adaptation_t value();
  };

  /// A special value used for accessing the blocking_adaptation_t::disallowed_t
  /// property.
  static constexpr disallowed_t disallowed;

  /// A special value used for accessing the blocking_adaptation_t::allowed_t
  /// property.
  static constexpr allowed_t allowed;

  /// Default constructor.
  constexpr blocking_adaptation_t();

  /// Construct from a sub-property value.
  constexpr blocking_adaptation_t(disallowed_t);

  /// Construct from a sub-property value.
  constexpr blocking_adaptation_t(allowed_t);

  /// Compare property values for equality.
  friend constexpr bool operator==(
      const blocking_adaptation_t& a, const blocking_adaptation_t& b) noexcept;

  /// Compare property values for inequality.
  friend constexpr bool operator!=(
      const blocking_adaptation_t& a, const blocking_adaptation_t& b) noexcept;
};

/// A special value used for accessing the blocking_adaptation_t property.
constexpr blocking_adaptation_t blocking_adaptation;

} // namespace execution

#else // defined(GENERATING_DOCUMENTATION)

namespace execution {
namespace detail {
namespace blocking_adaptation {

template <int I> struct disallowed_t;
template <int I> struct allowed_t;

} // namespace blocking_adaptation

template <int I = 0>
struct blocking_adaptation_t
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
  typedef blocking_adaptation_t polymorphic_query_result_type;

  typedef detail::blocking_adaptation::disallowed_t<I> disallowed_t;
  typedef detail::blocking_adaptation::allowed_t<I> allowed_t;

  BOOST_ASIO_CONSTEXPR blocking_adaptation_t()
    : value_(-1)
  {
  }

  BOOST_ASIO_CONSTEXPR blocking_adaptation_t(disallowed_t)
    : value_(0)
  {
  }

  BOOST_ASIO_CONSTEXPR blocking_adaptation_t(allowed_t)
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
    traits::query_member<typename proxy<T>::type, blocking_adaptation_t> {};

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename static_proxy<T>::type, blocking_adaptation_t> {};

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
  typename traits::static_query<T, disallowed_t>::result_type
  static_query(
      typename enable_if<
        !query_static_constexpr_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !query_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        traits::static_query<T, disallowed_t>::is_valid
      >::type* = 0) BOOST_ASIO_NOEXCEPT
  {
    return traits::static_query<T, disallowed_t>::value();
  }

  template <typename T>
  static BOOST_ASIO_CONSTEXPR
  typename traits::static_query<T, allowed_t>::result_type
  static_query(
      typename enable_if<
        !query_static_constexpr_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !query_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !traits::static_query<T, disallowed_t>::is_valid
      >::type* = 0,
      typename enable_if<
        traits::static_query<T, allowed_t>::is_valid
      >::type* = 0) BOOST_ASIO_NOEXCEPT
  {
    return traits::static_query<T, allowed_t>::value();
  }

  template <typename E,
      typename T = decltype(blocking_adaptation_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = blocking_adaptation_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const blocking_adaptation_t& a, const blocking_adaptation_t& b)
  {
    return a.value_ == b.value_;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const blocking_adaptation_t& a, const blocking_adaptation_t& b)
  {
    return a.value_ != b.value_;
  }

  struct convertible_from_blocking_adaptation_t
  {
    BOOST_ASIO_CONSTEXPR convertible_from_blocking_adaptation_t(
        blocking_adaptation_t)
    {
    }
  };

  template <typename Executor>
  friend BOOST_ASIO_CONSTEXPR blocking_adaptation_t query(
      const Executor& ex, convertible_from_blocking_adaptation_t,
      typename enable_if<
        can_query<const Executor&, disallowed_t>::value
      >::type* = 0)
#if !defined(__clang__) // Clang crashes if noexcept is used here.
#if defined(BOOST_ASIO_MSVC) // Visual C++ wants the type to be qualified.
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&,
        blocking_adaptation_t<>::disallowed_t>::value))
#else // defined(BOOST_ASIO_MSVC)
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, disallowed_t>::value))
#endif // defined(BOOST_ASIO_MSVC)
#endif // !defined(__clang__)
  {
    return boost::asio::query(ex, disallowed_t());
  }

  template <typename Executor>
  friend BOOST_ASIO_CONSTEXPR blocking_adaptation_t query(
      const Executor& ex, convertible_from_blocking_adaptation_t,
      typename enable_if<
        !can_query<const Executor&, disallowed_t>::value
      >::type* = 0,
      typename enable_if<
        can_query<const Executor&, allowed_t>::value
      >::type* = 0)
#if !defined(__clang__) // Clang crashes if noexcept is used here.
#if defined(BOOST_ASIO_MSVC) // Visual C++ wants the type to be qualified.
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&,
        blocking_adaptation_t<>::allowed_t>::value))
#else // defined(BOOST_ASIO_MSVC)
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, allowed_t>::value))
#endif // defined(BOOST_ASIO_MSVC)
#endif // !defined(__clang__)
  {
    return boost::asio::query(ex, allowed_t());
  }

  BOOST_ASIO_STATIC_CONSTEXPR_DEFAULT_INIT(disallowed_t, disallowed);
  BOOST_ASIO_STATIC_CONSTEXPR_DEFAULT_INIT(allowed_t, allowed);

#if !defined(BOOST_ASIO_HAS_CONSTEXPR)
  static const blocking_adaptation_t instance;
#endif // !defined(BOOST_ASIO_HAS_CONSTEXPR)

private:
  int value_;
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <int I> template <typename E, typename T>
const T blocking_adaptation_t<I>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

#if !defined(BOOST_ASIO_HAS_CONSTEXPR)
template <int I>
const blocking_adaptation_t<I> blocking_adaptation_t<I>::instance;
#endif

template <int I>
const typename blocking_adaptation_t<I>::disallowed_t
blocking_adaptation_t<I>::disallowed;

template <int I>
const typename blocking_adaptation_t<I>::allowed_t
blocking_adaptation_t<I>::allowed;

namespace blocking_adaptation {

template <int I = 0>
struct disallowed_t
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
  typedef blocking_adaptation_t<I> polymorphic_query_result_type;

  BOOST_ASIO_CONSTEXPR disallowed_t()
  {
  }

  template <typename T>
  struct query_member :
    traits::query_member<
      typename blocking_adaptation_t<I>::template proxy<T>::type,
        disallowed_t> {};

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename blocking_adaptation_t<I>::template static_proxy<T>::type,
        disallowed_t> {};

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
  static BOOST_ASIO_CONSTEXPR disallowed_t static_query(
      typename enable_if<
        !query_static_constexpr_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !query_member<T>::is_valid
      >::type* = 0,
      typename enable_if<
        !traits::query_free<T, disallowed_t>::is_valid
      >::type* = 0,
      typename enable_if<
        !can_query<T, allowed_t<I> >::value
      >::type* = 0) BOOST_ASIO_NOEXCEPT
  {
    return disallowed_t();
  }

  template <typename E, typename T = decltype(disallowed_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = disallowed_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  static BOOST_ASIO_CONSTEXPR blocking_adaptation_t<I> value()
  {
    return disallowed_t();
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const disallowed_t&, const disallowed_t&)
  {
    return true;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const disallowed_t&, const disallowed_t&)
  {
    return false;
  }
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <int I> template <typename E, typename T>
const T disallowed_t<I>::static_query_v;
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
  static BOOST_ASIO_CONSTEXPR allowed_t<I> query(
      blocking_adaptation_t<I>) BOOST_ASIO_NOEXCEPT
  {
    return allowed_t<I>();
  }

  template <int I>
  static BOOST_ASIO_CONSTEXPR allowed_t<I> query(
      allowed_t<I>) BOOST_ASIO_NOEXCEPT
  {
    return allowed_t<I>();
  }

  template <int I>
  static BOOST_ASIO_CONSTEXPR allowed_t<I> query(
      disallowed_t<I>) BOOST_ASIO_NOEXCEPT
  {
    return allowed_t<I>();
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
  Executor require(disallowed_t<I>) const BOOST_ASIO_NOEXCEPT
  {
    return executor_;
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
    execution::execute(executor_, BOOST_ASIO_MOVE_CAST(Function)(f));
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
struct allowed_t
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
  typedef blocking_adaptation_t<I> polymorphic_query_result_type;

  BOOST_ASIO_CONSTEXPR allowed_t()
  {
  }

  template <typename T>
  struct query_member :
    traits::query_member<
      typename blocking_adaptation_t<I>::template proxy<T>::type,
        allowed_t> {};

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename blocking_adaptation_t<I>::template static_proxy<T>::type,
        allowed_t> {};

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

  template <typename E, typename T = decltype(allowed_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = allowed_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  static BOOST_ASIO_CONSTEXPR blocking_adaptation_t<I> value()
  {
    return allowed_t();
  }

  friend BOOST_ASIO_CONSTEXPR bool operator==(
      const allowed_t&, const allowed_t&)
  {
    return true;
  }

  friend BOOST_ASIO_CONSTEXPR bool operator!=(
      const allowed_t&, const allowed_t&)
  {
    return false;
  }

  template <typename Executor>
  friend adapter<Executor> require(
      const Executor& e, const allowed_t&,
      typename enable_if<
        is_executor<Executor>::value
      >::type* = 0)
  {
    return adapter<Executor>(0, e);
  }
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <int I> template <typename E, typename T>
const T allowed_t<I>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

template <typename Function>
class blocking_execute_state
{
public:
  template <typename F>
  blocking_execute_state(BOOST_ASIO_MOVE_ARG(F) f)
    : func_(BOOST_ASIO_MOVE_CAST(F)(f)),
      is_complete_(false)
  {
  }

  template <typename Executor>
  void execute_and_wait(BOOST_ASIO_MOVE_ARG(Executor) ex)
  {
    handler h = { this };
    execution::execute(BOOST_ASIO_MOVE_CAST(Executor)(ex), h);
    boost::asio::detail::mutex::scoped_lock lock(mutex_);
    while (!is_complete_)
      event_.wait(lock);
  }

  struct cleanup
  {
    ~cleanup()
    {
      boost::asio::detail::mutex::scoped_lock lock(state_->mutex_);
      state_->is_complete_ = true;
      state_->event_.unlock_and_signal_one_for_destruction(lock);
    }

    blocking_execute_state* state_;
  };

  struct handler
  {
    void operator()()
    {
      cleanup c = { state_ };
      state_->func_();
    }

    blocking_execute_state* state_;
  };

  Function func_;
  boost::asio::detail::mutex mutex_;
  boost::asio::detail::event event_;
  bool is_complete_;
};

template <typename Executor, typename Function>
void blocking_execute(
    BOOST_ASIO_MOVE_ARG(Executor) ex,
    BOOST_ASIO_MOVE_ARG(Function) func)
{
  typedef typename decay<Function>::type func_t;
  blocking_execute_state<func_t> state(BOOST_ASIO_MOVE_CAST(Function)(func));
  state.execute_and_wait(ex);
}

} // namespace blocking_adaptation
} // namespace detail

typedef detail::blocking_adaptation_t<> blocking_adaptation_t;

#if defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
constexpr blocking_adaptation_t blocking_adaptation;
#else // defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
namespace { static const blocking_adaptation_t&
  blocking_adaptation = blocking_adaptation_t::instance; }
#endif

} // namespace execution

#if !defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T>
struct is_applicable_property<T, execution::blocking_adaptation_t>
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
struct is_applicable_property<T, execution::blocking_adaptation_t::disallowed_t>
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
struct is_applicable_property<T, execution::blocking_adaptation_t::allowed_t>
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
struct query_free_default<T, execution::blocking_adaptation_t,
  typename enable_if<
    can_query<T, execution::blocking_adaptation_t::disallowed_t>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = (is_nothrow_query<T,
      execution::blocking_adaptation_t::disallowed_t>::value));

  typedef execution::blocking_adaptation_t result_type;
};

template <typename T>
struct query_free_default<T, execution::blocking_adaptation_t,
  typename enable_if<
    !can_query<T, execution::blocking_adaptation_t::disallowed_t>::value
      && can_query<T, execution::blocking_adaptation_t::allowed_t>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    (is_nothrow_query<T, execution::blocking_adaptation_t::allowed_t>::value));

  typedef execution::blocking_adaptation_t result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_FREE_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  || !defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

template <typename T>
struct static_query<T, execution::blocking_adaptation_t,
  typename enable_if<
    execution::detail::blocking_adaptation_t<0>::
      query_static_constexpr_member<T>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename execution::detail::blocking_adaptation_t<0>::
    query_static_constexpr_member<T>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return execution::detail::blocking_adaptation_t<0>::
      query_static_constexpr_member<T>::value();
  }
};

template <typename T>
struct static_query<T, execution::blocking_adaptation_t,
  typename enable_if<
    !execution::detail::blocking_adaptation_t<0>::
        query_static_constexpr_member<T>::is_valid
      && !execution::detail::blocking_adaptation_t<0>::
        query_member<T>::is_valid
      && traits::static_query<T,
        execution::blocking_adaptation_t::disallowed_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename traits::static_query<T,
    execution::blocking_adaptation_t::disallowed_t>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return traits::static_query<T,
        execution::blocking_adaptation_t::disallowed_t>::value();
  }
};

template <typename T>
struct static_query<T, execution::blocking_adaptation_t,
  typename enable_if<
    !execution::detail::blocking_adaptation_t<0>::
        query_static_constexpr_member<T>::is_valid
      && !execution::detail::blocking_adaptation_t<0>::
        query_member<T>::is_valid
      && !traits::static_query<T,
        execution::blocking_adaptation_t::disallowed_t>::is_valid
      && traits::static_query<T,
        execution::blocking_adaptation_t::allowed_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename traits::static_query<T,
    execution::blocking_adaptation_t::allowed_t>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return traits::static_query<T,
        execution::blocking_adaptation_t::allowed_t>::value();
  }
};

template <typename T>
struct static_query<T, execution::blocking_adaptation_t::disallowed_t,
  typename enable_if<
    execution::detail::blocking_adaptation::disallowed_t<0>::
      query_static_constexpr_member<T>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename execution::detail::blocking_adaptation::disallowed_t<0>::
    query_static_constexpr_member<T>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return execution::detail::blocking_adaptation::disallowed_t<0>::
      query_static_constexpr_member<T>::value();
  }
};

template <typename T>
struct static_query<T, execution::blocking_adaptation_t::disallowed_t,
  typename enable_if<
    !execution::detail::blocking_adaptation::disallowed_t<0>::
        query_static_constexpr_member<T>::is_valid
      && !execution::detail::blocking_adaptation::disallowed_t<0>::
        query_member<T>::is_valid
      && !traits::query_free<T,
        execution::blocking_adaptation_t::disallowed_t>::is_valid
      && !can_query<T, execution::blocking_adaptation_t::allowed_t>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef execution::blocking_adaptation_t::disallowed_t result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return result_type();
  }
};

template <typename T>
struct static_query<T, execution::blocking_adaptation_t::allowed_t,
  typename enable_if<
    execution::detail::blocking_adaptation::allowed_t<0>::
      query_static_constexpr_member<T>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename execution::detail::blocking_adaptation::allowed_t<0>::
    query_static_constexpr_member<T>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return execution::detail::blocking_adaptation::allowed_t<0>::
      query_static_constexpr_member<T>::value();
  }
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   || !defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

#if !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_REQUIRE_TRAIT)

template <typename T>
struct static_require<T, execution::blocking_adaptation_t::disallowed_t,
  typename enable_if<
    static_query<T, execution::blocking_adaptation_t::disallowed_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid =
    (is_same<typename static_query<T,
      execution::blocking_adaptation_t::disallowed_t>::result_type,
        execution::blocking_adaptation_t::disallowed_t>::value));
};

template <typename T>
struct static_require<T, execution::blocking_adaptation_t::allowed_t,
  typename enable_if<
    static_query<T, execution::blocking_adaptation_t::allowed_t>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid =
    (is_same<typename static_query<T,
      execution::blocking_adaptation_t::allowed_t>::result_type,
        execution::blocking_adaptation_t::allowed_t>::value));
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_REQUIRE_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_FREE_TRAIT)

template <typename T>
struct require_free_default<T, execution::blocking_adaptation_t::allowed_t,
  typename enable_if<
    is_same<T, typename decay<T>::type>::value
      && execution::is_executor<T>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef execution::detail::blocking_adaptation::adapter<T> result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_FREE_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_EQUALITY_COMPARABLE_TRAIT)

template <typename Executor>
struct equality_comparable<
  execution::detail::blocking_adaptation::adapter<Executor> >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_EQUALITY_COMPARABLE_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_EXECUTE_MEMBER_TRAIT)

template <typename Executor, typename Function>
struct execute_member<
  execution::detail::blocking_adaptation::adapter<Executor>, Function>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef void result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_EXECUTE_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_STATIC_CONSTEXPR_MEMBER_TRAIT)

template <typename Executor, int I>
struct query_static_constexpr_member<
  execution::detail::blocking_adaptation::adapter<Executor>,
  execution::detail::blocking_adaptation_t<I> >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef execution::blocking_adaptation_t::allowed_t result_type;

  static BOOST_ASIO_CONSTEXPR result_type value() BOOST_ASIO_NOEXCEPT
  {
    return result_type();
  }
};

template <typename Executor, int I>
struct query_static_constexpr_member<
  execution::detail::blocking_adaptation::adapter<Executor>,
  execution::detail::blocking_adaptation::allowed_t<I> >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef execution::blocking_adaptation_t::allowed_t result_type;

  static BOOST_ASIO_CONSTEXPR result_type value() BOOST_ASIO_NOEXCEPT
  {
    return result_type();
  }
};

template <typename Executor, int I>
struct query_static_constexpr_member<
  execution::detail::blocking_adaptation::adapter<Executor>,
  execution::detail::blocking_adaptation::disallowed_t<I> >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef execution::blocking_adaptation_t::allowed_t result_type;

  static BOOST_ASIO_CONSTEXPR result_type value() BOOST_ASIO_NOEXCEPT
  {
    return result_type();
  }
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_STATIC_CONSTEXPR_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_MEMBER_TRAIT)

template <typename Executor, typename Property>
struct query_member<
  execution::detail::blocking_adaptation::adapter<Executor>, Property,
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
  execution::detail::blocking_adaptation::adapter<Executor>,
  execution::detail::blocking_adaptation::disallowed_t<I> >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef Executor result_type;
};

template <typename Executor, typename Property>
struct require_member<
  execution::detail::blocking_adaptation::adapter<Executor>, Property,
  typename enable_if<
    can_require<const Executor&, Property>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
      (is_nothrow_require<Executor, Property>::value));
  typedef execution::detail::blocking_adaptation::adapter<typename decay<
    typename require_result<Executor, Property>::type
      >::type> result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_PREFER_MEMBER_TRAIT)

template <typename Executor, typename Property>
struct prefer_member<
  execution::detail::blocking_adaptation::adapter<Executor>, Property,
  typename enable_if<
    can_prefer<const Executor&, Property>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
      (is_nothrow_prefer<Executor, Property>::value));
  typedef execution::detail::blocking_adaptation::adapter<typename decay<
    typename prefer_result<Executor, Property>::type
      >::type> result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_PREFER_MEMBER_TRAIT)

} // namespace traits

#endif // defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_BLOCKING_ADAPTATION_HPP

/* blocking_adaptation.hpp
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
*/