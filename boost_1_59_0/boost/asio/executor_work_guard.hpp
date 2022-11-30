//
// executor_work_guard.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTOR_WORK_GUARD_HPP
#define BOOST_ASIO_EXECUTOR_WORK_GUARD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/associated_executor.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution.hpp>
#include <boost/asio/is_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if !defined(BOOST_ASIO_EXECUTOR_WORK_GUARD_DECL)
#define BOOST_ASIO_EXECUTOR_WORK_GUARD_DECL

template <typename Executor, typename = void, typename = void>
class executor_work_guard;

#endif // !defined(BOOST_ASIO_EXECUTOR_WORK_GUARD_DECL)

#if defined(GENERATING_DOCUMENTATION)

/// An object of type @c executor_work_guard controls ownership of outstanding
/// executor work within a scope.
template <typename Executor>
class executor_work_guard
{
public:
  /// The underlying executor type.
  typedef Executor executor_type;

  /// Constructs a @c executor_work_guard object for the specified executor.
  /**
   * Stores a copy of @c e and calls <tt>on_work_started()</tt> on it.
   */
  explicit executor_work_guard(const executor_type& e) BOOST_ASIO_NOEXCEPT;

  /// Copy constructor.
  executor_work_guard(const executor_work_guard& other) BOOST_ASIO_NOEXCEPT;

  /// Move constructor.
  executor_work_guard(executor_work_guard&& other) BOOST_ASIO_NOEXCEPT;

  /// Destructor.
  /**
   * Unless the object has already been reset, or is in a moved-from state,
   * calls <tt>on_work_finished()</tt> on the stored executor.
   */
  ~executor_work_guard();

  /// Obtain the associated executor.
  executor_type get_executor() const BOOST_ASIO_NOEXCEPT;

  /// Whether the executor_work_guard object owns some outstanding work.
  bool owns_work() const BOOST_ASIO_NOEXCEPT;

  /// Indicate that the work is no longer outstanding.
  /**
   * Unless the object has already been reset, or is in a moved-from state,
   * calls <tt>on_work_finished()</tt> on the stored executor.
   */
  void reset() BOOST_ASIO_NOEXCEPT;
};

#endif // defined(GENERATING_DOCUMENTATION)

#if !defined(GENERATING_DOCUMENTATION)

#if !defined(BOOST_ASIO_NO_TS_EXECUTORS)

template <typename Executor>
class executor_work_guard<Executor,
    typename enable_if<
      is_executor<Executor>::value
    >::type>
{
public:
  typedef Executor executor_type;

  explicit executor_work_guard(const executor_type& e) BOOST_ASIO_NOEXCEPT
    : executor_(e),
      owns_(true)
  {
    executor_.on_work_started();
  }

  executor_work_guard(const executor_work_guard& other) BOOST_ASIO_NOEXCEPT
    : executor_(other.executor_),
      owns_(other.owns_)
  {
    if (owns_)
      executor_.on_work_started();
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  executor_work_guard(executor_work_guard&& other) BOOST_ASIO_NOEXCEPT
    : executor_(BOOST_ASIO_MOVE_CAST(Executor)(other.executor_)),
      owns_(other.owns_)
  {
    other.owns_ = false;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  ~executor_work_guard()
  {
    if (owns_)
      executor_.on_work_finished();
  }

  executor_type get_executor() const BOOST_ASIO_NOEXCEPT
  {
    return executor_;
  }

  bool owns_work() const BOOST_ASIO_NOEXCEPT
  {
    return owns_;
  }

  void reset() BOOST_ASIO_NOEXCEPT
  {
    if (owns_)
    {
      executor_.on_work_finished();
      owns_ = false;
    }
  }

private:
  // Disallow assignment.
  executor_work_guard& operator=(const executor_work_guard&);

  executor_type executor_;
  bool owns_;
};

#endif // !defined(BOOST_ASIO_NO_TS_EXECUTORS)

template <typename Executor>
class executor_work_guard<Executor,
    typename enable_if<
      !is_executor<Executor>::value
    >::type,
    typename enable_if<
      execution::is_executor<Executor>::value
    >::type>
{
public:
  typedef Executor executor_type;

  explicit executor_work_guard(const executor_type& e) BOOST_ASIO_NOEXCEPT
    : executor_(e),
      owns_(true)
  {
    new (&work_) work_type(boost::asio::prefer(executor_,
          execution::outstanding_work.tracked));
  }

  executor_work_guard(const executor_work_guard& other) BOOST_ASIO_NOEXCEPT
    : executor_(other.executor_),
      owns_(other.owns_)
  {
    if (owns_)
    {
      new (&work_) work_type(boost::asio::prefer(executor_,
            execution::outstanding_work.tracked));
    }
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  executor_work_guard(executor_work_guard&& other) BOOST_ASIO_NOEXCEPT
    : executor_(BOOST_ASIO_MOVE_CAST(Executor)(other.executor_)),
      owns_(other.owns_)
  {
    if (owns_)
    {
      new (&work_) work_type(
          BOOST_ASIO_MOVE_CAST(work_type)(
            *static_cast<work_type*>(
              static_cast<void*>(&other.work_))));
      other.owns_ = false;
    }
  }
#endif //  defined(BOOST_ASIO_HAS_MOVE)

  ~executor_work_guard()
  {
    if (owns_)
      static_cast<work_type*>(static_cast<void*>(&work_))->~work_type();
  }

  executor_type get_executor() const BOOST_ASIO_NOEXCEPT
  {
    return executor_;
  }

  bool owns_work() const BOOST_ASIO_NOEXCEPT
  {
    return owns_;
  }

  void reset() BOOST_ASIO_NOEXCEPT
  {
    if (owns_)
    {
      static_cast<work_type*>(static_cast<void*>(&work_))->~work_type();
      owns_ = false;
    }
  }

private:
  // Disallow assignment.
  executor_work_guard& operator=(const executor_work_guard&);

  typedef typename decay<
      typename prefer_result<
        const executor_type&,
        execution::outstanding_work_t::tracked_t
      >::type
    >::type work_type;

  executor_type executor_;
  typename aligned_storage<sizeof(work_type),
      alignment_of<work_type>::value>::type work_;
  bool owns_;
};

#endif // !defined(GENERATING_DOCUMENTATION)

/// Create an @ref executor_work_guard object.
/**
 * @param ex An executor.
 *
 * @returns A work guard constructed with the specified executor.
 */
template <typename Executor>
BOOST_ASIO_NODISCARD inline executor_work_guard<Executor>
make_work_guard(const Executor& ex,
    typename constraint<
      is_executor<Executor>::value || execution::is_executor<Executor>::value
    >::type = 0)
{
  return executor_work_guard<Executor>(ex);
}

/// Create an @ref executor_work_guard object.
/**
 * @param ctx An execution context, from which an executor will be obtained.
 *
 * @returns A work guard constructed with the execution context's executor,
 * obtained by performing <tt>ctx.get_executor()</tt>.
 */
template <typename ExecutionContext>
BOOST_ASIO_NODISCARD inline
executor_work_guard<typename ExecutionContext::executor_type>
make_work_guard(ExecutionContext& ctx,
    typename constraint<
      is_convertible<ExecutionContext&, execution_context&>::value
    >::type = 0)
{
  return executor_work_guard<typename ExecutionContext::executor_type>(
      ctx.get_executor());
}

/// Create an @ref executor_work_guard object.
/**
 * @param t An arbitrary object, such as a completion handler, for which the
 * associated executor will be obtained.
 *
 * @returns A work guard constructed with the associated executor of the object
 * @c t, which is obtained as if by calling <tt>get_associated_executor(t)</tt>.
 */
template <typename T>
BOOST_ASIO_NODISCARD inline
executor_work_guard<typename associated_executor<T>::type>
make_work_guard(const T& t,
    typename constraint<
      !is_executor<T>::value
    >::type = 0,
    typename constraint<
      !execution::is_executor<T>::value
    >::type = 0,
    typename constraint<
      !is_convertible<T&, execution_context&>::value
    >::type = 0)
{
  return executor_work_guard<typename associated_executor<T>::type>(
      associated_executor<T>::get(t));
}

/// Create an @ref executor_work_guard object.
/**
 * @param t An arbitrary object, such as a completion handler, for which the
 * associated executor will be obtained.
 *
 * @param ex An executor to be used as the candidate object when determining the
 * associated executor.
 *
 * @returns A work guard constructed with the associated executor of the object
 * @c t, which is obtained as if by calling <tt>get_associated_executor(t,
 * ex)</tt>.
 */
template <typename T, typename Executor>
BOOST_ASIO_NODISCARD inline
executor_work_guard<typename associated_executor<T, Executor>::type>
make_work_guard(const T& t, const Executor& ex,
    typename constraint<
      is_executor<Executor>::value || execution::is_executor<Executor>::value
    >::type = 0)
{
  return executor_work_guard<typename associated_executor<T, Executor>::type>(
      associated_executor<T, Executor>::get(t, ex));
}

/// Create an @ref executor_work_guard object.
/**
 * @param t An arbitrary object, such as a completion handler, for which the
 * associated executor will be obtained.
 *
 * @param ctx An execution context, from which an executor is obtained to use as
 * the candidate object for determining the associated executor.
 *
 * @returns A work guard constructed with the associated executor of the object
 * @c t, which is obtained as if by calling <tt>get_associated_executor(t,
 * ctx.get_executor())</tt>.
 */
template <typename T, typename ExecutionContext>
BOOST_ASIO_NODISCARD inline executor_work_guard<typename associated_executor<T,
  typename ExecutionContext::executor_type>::type>
make_work_guard(const T& t, ExecutionContext& ctx,
    typename constraint<
      !is_executor<T>::value
    >::type = 0,
    typename constraint<
      !execution::is_executor<T>::value
    >::type = 0,
    typename constraint<
      !is_convertible<T&, execution_context&>::value
    >::type = 0,
    typename constraint<
      is_convertible<ExecutionContext&, execution_context&>::value
    >::type = 0)
{
  return executor_work_guard<typename associated_executor<T,
    typename ExecutionContext::executor_type>::type>(
      associated_executor<T, typename ExecutionContext::executor_type>::get(
        t, ctx.get_executor()));
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTOR_WORK_GUARD_HPP

/* executor_work_guard.hpp
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
*/