//
// thread_pool.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_THREAD_POOL_HPP
#define BOOST_ASIO_THREAD_POOL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/atomic_count.hpp>
#include <boost/asio/detail/scheduler.hpp>
#include <boost/asio/detail/thread_group.hpp>
#include <boost/asio/execution.hpp>
#include <boost/asio/execution_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {
  struct thread_pool_bits
  {
    BOOST_ASIO_STATIC_CONSTEXPR(unsigned int, blocking_never = 1);
    BOOST_ASIO_STATIC_CONSTEXPR(unsigned int, blocking_always = 2);
    BOOST_ASIO_STATIC_CONSTEXPR(unsigned int, blocking_mask = 3);
    BOOST_ASIO_STATIC_CONSTEXPR(unsigned int, relationship_continuation = 4);
    BOOST_ASIO_STATIC_CONSTEXPR(unsigned int, outstanding_work_tracked = 8);
  };
} // namespace detail

/// A simple fixed-size thread pool.
/**
 * The thread pool class is an execution context where functions are permitted
 * to run on one of a fixed number of threads.
 *
 * @par Submitting tasks to the pool
 *
 * To submit functions to the thread pool, use the @ref boost::asio::dispatch,
 * @ref boost::asio::post or @ref boost::asio::defer free functions.
 *
 * For example:
 *
 * @code void my_task()
 * {
 *   ...
 * }
 *
 * ...
 *
 * // Launch the pool with four threads.
 * boost::asio::thread_pool pool(4);
 *
 * // Submit a function to the pool.
 * boost::asio::post(pool, my_task);
 *
 * // Submit a lambda object to the pool.
 * boost::asio::post(pool,
 *     []()
 *     {
 *       ...
 *     });
 *
 * // Wait for all tasks in the pool to complete.
 * pool.join(); @endcode
 */
class thread_pool
  : public execution_context
{
public:
  template <typename Allocator, unsigned int Bits>
  class basic_executor_type;

  template <typename Allocator, unsigned int Bits>
  friend class basic_executor_type;

  /// Executor used to submit functions to a thread pool.
  typedef basic_executor_type<std::allocator<void>, 0> executor_type;

  /// Scheduler used to schedule receivers on a thread pool.
  typedef basic_executor_type<std::allocator<void>, 0> scheduler_type;

#if !defined(BOOST_ASIO_NO_TS_EXECUTORS)
  /// Constructs a pool with an automatically determined number of threads.
  BOOST_ASIO_DECL thread_pool();
#endif // !defined(BOOST_ASIO_NO_TS_EXECUTORS)

  /// Constructs a pool with a specified number of threads.
  BOOST_ASIO_DECL thread_pool(std::size_t num_threads);

  /// Destructor.
  /**
   * Automatically stops and joins the pool, if not explicitly done beforehand.
   */
  BOOST_ASIO_DECL ~thread_pool();

  /// Obtains the executor associated with the pool.
  executor_type get_executor() BOOST_ASIO_NOEXCEPT;

  /// Obtains the executor associated with the pool.
  executor_type executor() BOOST_ASIO_NOEXCEPT;

  /// Obtains the scheduler associated with the pool.
  scheduler_type scheduler() BOOST_ASIO_NOEXCEPT;

  /// Stops the threads.
  /**
   * This function stops the threads as soon as possible. As a result of calling
   * @c stop(), pending function objects may be never be invoked.
   */
  BOOST_ASIO_DECL void stop();

  /// Attaches the current thread to the pool.
  /**
   * This function attaches the current thread to the pool so that it may be
   * used for executing submitted function objects. Blocks the calling thread
   * until the pool is stopped or joined and has no outstanding work.
   */
  BOOST_ASIO_DECL void attach();

  /// Joins the threads.
  /**
   * This function blocks until the threads in the pool have completed. If @c
   * stop() is not called prior to @c join(), the @c join() call will wait
   * until the pool has no more outstanding work.
   */
  BOOST_ASIO_DECL void join();

  /// Waits for threads to complete.
  /**
   * This function blocks until the threads in the pool have completed. If @c
   * stop() is not called prior to @c wait(), the @c wait() call will wait
   * until the pool has no more outstanding work.
   */
  BOOST_ASIO_DECL void wait();

private:
  thread_pool(const thread_pool&) BOOST_ASIO_DELETED;
  thread_pool& operator=(const thread_pool&) BOOST_ASIO_DELETED;

  struct thread_function;

  // Helper function to create the underlying scheduler.
  BOOST_ASIO_DECL detail::scheduler& add_scheduler(detail::scheduler* s);

  // The underlying scheduler.
  detail::scheduler& scheduler_;

  // The threads in the pool.
  detail::thread_group threads_;

  // The current number of threads in the pool.
  detail::atomic_count num_threads_;
};

/// Executor implementation type used to submit functions to a thread pool.
template <typename Allocator, unsigned int Bits>
class thread_pool::basic_executor_type : detail::thread_pool_bits
{
public:
  /// The sender type, when this type is used as a scheduler.
  typedef basic_executor_type sender_type;

  /// The bulk execution shape type.
  typedef std::size_t shape_type;

  /// The bulk execution index type.
  typedef std::size_t index_type;

#if defined(BOOST_ASIO_HAS_DEDUCED_EXECUTION_IS_TYPED_SENDER_TRAIT) \
  && defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)
  template <
      template <typename...> class Tuple,
      template <typename...> class Variant>
  using value_types = Variant<Tuple<>>;

  template <template <typename...> class Variant>
  using error_types = Variant<std::exception_ptr>;

  BOOST_ASIO_STATIC_CONSTEXPR(bool, sends_done = true);
#endif // defined(BOOST_ASIO_HAS_DEDUCED_EXECUTION_IS_TYPED_SENDER_TRAIT)
       //   && defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)

  /// Copy constructor.
  basic_executor_type(
      const basic_executor_type& other) BOOST_ASIO_NOEXCEPT
    : pool_(other.pool_),
      allocator_(other.allocator_),
      bits_(other.bits_)
  {
    if (Bits & outstanding_work_tracked)
      if (pool_)
        pool_->scheduler_.work_started();
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move constructor.
  basic_executor_type(basic_executor_type&& other) BOOST_ASIO_NOEXCEPT
    : pool_(other.pool_),
      allocator_(BOOST_ASIO_MOVE_CAST(Allocator)(other.allocator_)),
      bits_(other.bits_)
  {
    if (Bits & outstanding_work_tracked)
      other.pool_ = 0;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Destructor.
  ~basic_executor_type() BOOST_ASIO_NOEXCEPT
  {
    if (Bits & outstanding_work_tracked)
      if (pool_)
        pool_->scheduler_.work_finished();
  }

  /// Assignment operator.
  basic_executor_type& operator=(
      const basic_executor_type& other) BOOST_ASIO_NOEXCEPT;

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move assignment operator.
  basic_executor_type& operator=(
      basic_executor_type&& other) BOOST_ASIO_NOEXCEPT;
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

#if !defined(GENERATING_DOCUMENTATION)
private:
  friend struct boost_asio_require_fn::impl;
  friend struct boost_asio_prefer_fn::impl;
#endif // !defined(GENERATING_DOCUMENTATION)

  /// Obtain an executor with the @c blocking.possibly property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code auto ex1 = my_thread_pool.executor();
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::blocking.possibly); @endcode
   */
  BOOST_ASIO_CONSTEXPR basic_executor_type<Allocator,
      BOOST_ASIO_UNSPECIFIED(Bits & ~blocking_mask)>
  require(execution::blocking_t::possibly_t) const
  {
    return basic_executor_type<Allocator, Bits & ~blocking_mask>(
        pool_, allocator_, bits_ & ~blocking_mask);
  }

  /// Obtain an executor with the @c blocking.always property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code auto ex1 = my_thread_pool.executor();
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::blocking.always); @endcode
   */
  BOOST_ASIO_CONSTEXPR basic_executor_type<Allocator,
      BOOST_ASIO_UNSPECIFIED((Bits & ~blocking_mask) | blocking_always)>
  require(execution::blocking_t::always_t) const
  {
    return basic_executor_type<Allocator,
        BOOST_ASIO_UNSPECIFIED((Bits & ~blocking_mask) | blocking_always)>(
          pool_, allocator_, bits_ & ~blocking_mask);
  }

  /// Obtain an executor with the @c blocking.never property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code auto ex1 = my_thread_pool.executor();
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::blocking.never); @endcode
   */
  BOOST_ASIO_CONSTEXPR basic_executor_type<Allocator,
      BOOST_ASIO_UNSPECIFIED(Bits & ~blocking_mask)>
  require(execution::blocking_t::never_t) const
  {
    return basic_executor_type<Allocator, Bits & ~blocking_mask>(
        pool_, allocator_, (bits_ & ~blocking_mask) | blocking_never);
  }

  /// Obtain an executor with the @c relationship.fork property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code auto ex1 = my_thread_pool.executor();
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::relationship.fork); @endcode
   */
  BOOST_ASIO_CONSTEXPR basic_executor_type require(
      execution::relationship_t::fork_t) const
  {
    return basic_executor_type(pool_,
        allocator_, bits_ & ~relationship_continuation);
  }

  /// Obtain an executor with the @c relationship.continuation property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code auto ex1 = my_thread_pool.executor();
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::relationship.continuation); @endcode
   */
  BOOST_ASIO_CONSTEXPR basic_executor_type require(
      execution::relationship_t::continuation_t) const
  {
    return basic_executor_type(pool_,
        allocator_, bits_ | relationship_continuation);
  }

  /// Obtain an executor with the @c outstanding_work.tracked property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code auto ex1 = my_thread_pool.executor();
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::outstanding_work.tracked); @endcode
   */
  BOOST_ASIO_CONSTEXPR basic_executor_type<Allocator,
      BOOST_ASIO_UNSPECIFIED(Bits | outstanding_work_tracked)>
  require(execution::outstanding_work_t::tracked_t) const
  {
    return basic_executor_type<Allocator, Bits | outstanding_work_tracked>(
        pool_, allocator_, bits_);
  }

  /// Obtain an executor with the @c outstanding_work.untracked property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code auto ex1 = my_thread_pool.executor();
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::outstanding_work.untracked); @endcode
   */
  BOOST_ASIO_CONSTEXPR basic_executor_type<Allocator,
      BOOST_ASIO_UNSPECIFIED(Bits & ~outstanding_work_tracked)>
  require(execution::outstanding_work_t::untracked_t) const
  {
    return basic_executor_type<Allocator, Bits & ~outstanding_work_tracked>(
        pool_, allocator_, bits_);
  }

  /// Obtain an executor with the specified @c allocator property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code auto ex1 = my_thread_pool.executor();
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::allocator(my_allocator)); @endcode
   */
  template <typename OtherAllocator>
  BOOST_ASIO_CONSTEXPR basic_executor_type<OtherAllocator, Bits>
  require(execution::allocator_t<OtherAllocator> a) const
  {
    return basic_executor_type<OtherAllocator, Bits>(
        pool_, a.value(), bits_);
  }

  /// Obtain an executor with the default @c allocator property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code auto ex1 = my_thread_pool.executor();
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::allocator); @endcode
   */
  BOOST_ASIO_CONSTEXPR basic_executor_type<std::allocator<void>, Bits>
  require(execution::allocator_t<void>) const
  {
    return basic_executor_type<std::allocator<void>, Bits>(
        pool_, std::allocator<void>(), bits_);
  }

#if !defined(GENERATING_DOCUMENTATION)
private:
  friend struct boost_asio_query_fn::impl;
  friend struct boost::asio::execution::detail::mapping_t<0>;
  friend struct boost::asio::execution::detail::outstanding_work_t<0>;
#endif // !defined(GENERATING_DOCUMENTATION)

  /// Query the current value of the @c bulk_guarantee property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::query customisation point.
   *
   * For example:
   * @code auto ex = my_thread_pool.executor();
   * if (boost::asio::query(ex, boost::asio::execution::bulk_guarantee)
   *       == boost::asio::execution::bulk_guarantee.parallel)
   *   ... @endcode
   */
  static BOOST_ASIO_CONSTEXPR execution::bulk_guarantee_t query(
      execution::bulk_guarantee_t) BOOST_ASIO_NOEXCEPT
  {
    return execution::bulk_guarantee.parallel;
  }

  /// Query the current value of the @c mapping property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::query customisation point.
   *
   * For example:
   * @code auto ex = my_thread_pool.executor();
   * if (boost::asio::query(ex, boost::asio::execution::mapping)
   *       == boost::asio::execution::mapping.thread)
   *   ... @endcode
   */
  static BOOST_ASIO_CONSTEXPR execution::mapping_t query(
      execution::mapping_t) BOOST_ASIO_NOEXCEPT
  {
    return execution::mapping.thread;
  }

  /// Query the current value of the @c context property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::query customisation point.
   *
   * For example:
   * @code auto ex = my_thread_pool.executor();
   * boost::asio::thread_pool& pool = boost::asio::query(
   *     ex, boost::asio::execution::context); @endcode
   */
  thread_pool& query(execution::context_t) const BOOST_ASIO_NOEXCEPT
  {
    return *pool_;
  }

  /// Query the current value of the @c blocking property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::query customisation point.
   *
   * For example:
   * @code auto ex = my_thread_pool.executor();
   * if (boost::asio::query(ex, boost::asio::execution::blocking)
   *       == boost::asio::execution::blocking.always)
   *   ... @endcode
   */
  BOOST_ASIO_CONSTEXPR execution::blocking_t query(
      execution::blocking_t) const BOOST_ASIO_NOEXCEPT
  {
    return (bits_ & blocking_never)
      ? execution::blocking_t(execution::blocking.never)
      : ((Bits & blocking_always)
          ? execution::blocking_t(execution::blocking.always)
          : execution::blocking_t(execution::blocking.possibly));
  }

  /// Query the current value of the @c relationship property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::query customisation point.
   *
   * For example:
   * @code auto ex = my_thread_pool.executor();
   * if (boost::asio::query(ex, boost::asio::execution::relationship)
   *       == boost::asio::execution::relationship.continuation)
   *   ... @endcode
   */
  BOOST_ASIO_CONSTEXPR execution::relationship_t query(
      execution::relationship_t) const BOOST_ASIO_NOEXCEPT
  {
    return (bits_ & relationship_continuation)
      ? execution::relationship_t(execution::relationship.continuation)
      : execution::relationship_t(execution::relationship.fork);
  }

  /// Query the current value of the @c outstanding_work property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::query customisation point.
   *
   * For example:
   * @code auto ex = my_thread_pool.executor();
   * if (boost::asio::query(ex, boost::asio::execution::outstanding_work)
   *       == boost::asio::execution::outstanding_work.tracked)
   *   ... @endcode
   */
  static BOOST_ASIO_CONSTEXPR execution::outstanding_work_t query(
      execution::outstanding_work_t) BOOST_ASIO_NOEXCEPT
  {
    return (Bits & outstanding_work_tracked)
      ? execution::outstanding_work_t(execution::outstanding_work.tracked)
      : execution::outstanding_work_t(execution::outstanding_work.untracked);
  }

  /// Query the current value of the @c allocator property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::query customisation point.
   *
   * For example:
   * @code auto ex = my_thread_pool.executor();
   * auto alloc = boost::asio::query(ex,
   *     boost::asio::execution::allocator); @endcode
   */
  template <typename OtherAllocator>
  BOOST_ASIO_CONSTEXPR Allocator query(
      execution::allocator_t<OtherAllocator>) const BOOST_ASIO_NOEXCEPT
  {
    return allocator_;
  }

  /// Query the current value of the @c allocator property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::query customisation point.
   *
   * For example:
   * @code auto ex = my_thread_pool.executor();
   * auto alloc = boost::asio::query(ex,
   *     boost::asio::execution::allocator); @endcode
   */
  BOOST_ASIO_CONSTEXPR Allocator query(
      execution::allocator_t<void>) const BOOST_ASIO_NOEXCEPT
  {
    return allocator_;
  }

  /// Query the occupancy (recommended number of work items) for the pool.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::query customisation point.
   *
   * For example:
   * @code auto ex = my_thread_pool.executor();
   * std::size_t occupancy = boost::asio::query(
   *     ex, boost::asio::execution::occupancy); @endcode
   */
  std::size_t query(execution::occupancy_t) const BOOST_ASIO_NOEXCEPT
  {
    return static_cast<std::size_t>(pool_->num_threads_);
  }

public:
  /// Determine whether the thread pool is running in the current thread.
  /**
   * @return @c true if the current thread is running the thread pool. Otherwise
   * returns @c false.
   */
  bool running_in_this_thread() const BOOST_ASIO_NOEXCEPT;

  /// Compare two executors for equality.
  /**
   * Two executors are equal if they refer to the same underlying thread pool.
   */
  friend bool operator==(const basic_executor_type& a,
      const basic_executor_type& b) BOOST_ASIO_NOEXCEPT
  {
    return a.pool_ == b.pool_
      && a.allocator_ == b.allocator_
      && a.bits_ == b.bits_;
  }

  /// Compare two executors for inequality.
  /**
   * Two executors are equal if they refer to the same underlying thread pool.
   */
  friend bool operator!=(const basic_executor_type& a,
      const basic_executor_type& b) BOOST_ASIO_NOEXCEPT
  {
    return a.pool_ != b.pool_
      || a.allocator_ != b.allocator_
      || a.bits_ != b.bits_;
  }

#if !defined(GENERATING_DOCUMENTATION)
private:
  friend struct boost_asio_execution_execute_fn::impl;
#endif // !defined(GENERATING_DOCUMENTATION)

  /// Execution function.
  /**
   * Do not call this function directly. It is intended for use with the
   * execution::execute customisation point.
   *
   * For example:
   * @code auto ex = my_thread_pool.executor();
   * execution::execute(ex, my_function_object); @endcode
   */
  template <typename Function>
  void execute(BOOST_ASIO_MOVE_ARG(Function) f) const
  {
    this->do_execute(BOOST_ASIO_MOVE_CAST(Function)(f),
        integral_constant<bool, (Bits & blocking_always) != 0>());
  }

public:
  /// Bulk execution function.
  template <typename Function>
  void bulk_execute(BOOST_ASIO_MOVE_ARG(Function) f, std::size_t n) const
  {
    this->do_bulk_execute(BOOST_ASIO_MOVE_CAST(Function)(f), n,
        integral_constant<bool, (Bits & blocking_always) != 0>());
  }

  /// Schedule function.
  /**
   * Do not call this function directly. It is intended for use with the
   * execution::schedule customisation point.
   *
   * @return An object that satisfies the sender concept.
   */
  sender_type schedule() const BOOST_ASIO_NOEXCEPT
  {
    return *this;
  }

  /// Connect function.
  /**
   * Do not call this function directly. It is intended for use with the
   * execution::connect customisation point.
   *
   * @return An object of an unspecified type that satisfies the @c
   * operation_state concept.
   */
  template <BOOST_ASIO_EXECUTION_RECEIVER_OF_0 Receiver>
#if defined(GENERATING_DOCUMENTATION)
  unspecified
#else // defined(GENERATING_DOCUMENTATION)
  execution::detail::as_operation<basic_executor_type, Receiver>
#endif // defined(GENERATING_DOCUMENTATION)
  connect(BOOST_ASIO_MOVE_ARG(Receiver) r) const
  {
    return execution::detail::as_operation<basic_executor_type, Receiver>(
        *this, BOOST_ASIO_MOVE_CAST(Receiver)(r));
  }

#if !defined(BOOST_ASIO_NO_TS_EXECUTORS)
  /// Obtain the underlying execution context.
  thread_pool& context() const BOOST_ASIO_NOEXCEPT;

  /// Inform the thread pool that it has some outstanding work to do.
  /**
   * This function is used to inform the thread pool that some work has begun.
   * This ensures that the thread pool's join() function will not return while
   * the work is underway.
   */
  void on_work_started() const BOOST_ASIO_NOEXCEPT;

  /// Inform the thread pool that some work is no longer outstanding.
  /**
   * This function is used to inform the thread pool that some work has
   * finished. Once the count of unfinished work reaches zero, the thread
   * pool's join() function is permitted to exit.
   */
  void on_work_finished() const BOOST_ASIO_NOEXCEPT;

  /// Request the thread pool to invoke the given function object.
  /**
   * This function is used to ask the thread pool to execute the given function
   * object. If the current thread belongs to the pool, @c dispatch() executes
   * the function before returning. Otherwise, the function will be scheduled
   * to run on the thread pool.
   *
   * @param f The function object to be called. The executor will make
   * a copy of the handler object as required. The function signature of the
   * function object must be: @code void function(); @endcode
   *
   * @param a An allocator that may be used by the executor to allocate the
   * internal storage needed for function invocation.
   */
  template <typename Function, typename OtherAllocator>
  void dispatch(BOOST_ASIO_MOVE_ARG(Function) f,
      const OtherAllocator& a) const;

  /// Request the thread pool to invoke the given function object.
  /**
   * This function is used to ask the thread pool to execute the given function
   * object. The function object will never be executed inside @c post().
   * Instead, it will be scheduled to run on the thread pool.
   *
   * @param f The function object to be called. The executor will make
   * a copy of the handler object as required. The function signature of the
   * function object must be: @code void function(); @endcode
   *
   * @param a An allocator that may be used by the executor to allocate the
   * internal storage needed for function invocation.
   */
  template <typename Function, typename OtherAllocator>
  void post(BOOST_ASIO_MOVE_ARG(Function) f,
      const OtherAllocator& a) const;

  /// Request the thread pool to invoke the given function object.
  /**
   * This function is used to ask the thread pool to execute the given function
   * object. The function object will never be executed inside @c defer().
   * Instead, it will be scheduled to run on the thread pool.
   *
   * If the current thread belongs to the thread pool, @c defer() will delay
   * scheduling the function object until the current thread returns control to
   * the pool.
   *
   * @param f The function object to be called. The executor will make
   * a copy of the handler object as required. The function signature of the
   * function object must be: @code void function(); @endcode
   *
   * @param a An allocator that may be used by the executor to allocate the
   * internal storage needed for function invocation.
   */
  template <typename Function, typename OtherAllocator>
  void defer(BOOST_ASIO_MOVE_ARG(Function) f,
      const OtherAllocator& a) const;
#endif // !defined(BOOST_ASIO_NO_TS_EXECUTORS)

private:
  friend class thread_pool;
  template <typename, unsigned int> friend class basic_executor_type;

  // Constructor used by thread_pool::get_executor().
  explicit basic_executor_type(thread_pool& p) BOOST_ASIO_NOEXCEPT
    : pool_(&p),
      allocator_(),
      bits_(0)
  {
    if (Bits & outstanding_work_tracked)
      pool_->scheduler_.work_started();
  }

  // Constructor used by require().
  basic_executor_type(thread_pool* p,
      const Allocator& a, unsigned int bits) BOOST_ASIO_NOEXCEPT
    : pool_(p),
      allocator_(a),
      bits_(bits)
  {
    if (Bits & outstanding_work_tracked)
      if (pool_)
        pool_->scheduler_.work_started();
  }

  /// Execution helper implementation for possibly and never blocking.
  template <typename Function>
  void do_execute(BOOST_ASIO_MOVE_ARG(Function) f, false_type) const;

  /// Execution helper implementation for always blocking.
  template <typename Function>
  void do_execute(BOOST_ASIO_MOVE_ARG(Function) f, true_type) const;

  /// Bulk execution helper implementation for possibly and never blocking.
  template <typename Function>
  void do_bulk_execute(BOOST_ASIO_MOVE_ARG(Function) f,
      std::size_t n, false_type) const;

  /// Bulk execution helper implementation for always blocking.
  template <typename Function>
  void do_bulk_execute(BOOST_ASIO_MOVE_ARG(Function) f,
      std::size_t n, true_type) const;

  // The underlying thread pool.
  thread_pool* pool_;

  // The allocator used for execution functions.
  Allocator allocator_;

  // The runtime-switched properties of the thread pool executor.
  unsigned int bits_;
};

#if !defined(GENERATING_DOCUMENTATION)

namespace traits {

#if !defined(BOOST_ASIO_HAS_DEDUCED_EQUALITY_COMPARABLE_TRAIT)

template <typename Allocator, unsigned int Bits>
struct equality_comparable<
    boost::asio::thread_pool::basic_executor_type<Allocator, Bits>
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_EQUALITY_COMPARABLE_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_EXECUTE_MEMBER_TRAIT)

template <typename Allocator, unsigned int Bits, typename Function>
struct execute_member<
    boost::asio::thread_pool::basic_executor_type<Allocator, Bits>,
    Function
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef void result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_EXECUTE_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_SCHEDULE_MEMBER_TRAIT)

template <typename Allocator, unsigned int Bits>
struct schedule_member<
    const boost::asio::thread_pool::basic_executor_type<Allocator, Bits>
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::thread_pool::basic_executor_type<
      Allocator, Bits> result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_SCHEDULE_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_CONNECT_MEMBER_TRAIT)

template <typename Allocator, unsigned int Bits, typename Receiver>
struct connect_member<
    const boost::asio::thread_pool::basic_executor_type<Allocator, Bits>,
    Receiver
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::execution::detail::as_operation<
      boost::asio::thread_pool::basic_executor_type<Allocator, Bits>,
      Receiver> result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_CONNECT_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_MEMBER_TRAIT)

template <typename Allocator, unsigned int Bits>
struct require_member<
    boost::asio::thread_pool::basic_executor_type<Allocator, Bits>,
    boost::asio::execution::blocking_t::possibly_t
  > : boost::asio::detail::thread_pool_bits
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef boost::asio::thread_pool::basic_executor_type<
      Allocator, Bits & ~blocking_mask> result_type;
};

template <typename Allocator, unsigned int Bits>
struct require_member<
    boost::asio::thread_pool::basic_executor_type<Allocator, Bits>,
    boost::asio::execution::blocking_t::always_t
  > : boost::asio::detail::thread_pool_bits
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::thread_pool::basic_executor_type<Allocator,
      (Bits & ~blocking_mask) | blocking_always> result_type;
};

template <typename Allocator, unsigned int Bits>
struct require_member<
    boost::asio::thread_pool::basic_executor_type<Allocator, Bits>,
    boost::asio::execution::blocking_t::never_t
  > : boost::asio::detail::thread_pool_bits
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::thread_pool::basic_executor_type<
      Allocator, Bits & ~blocking_mask> result_type;
};

template <typename Allocator, unsigned int Bits>
struct require_member<
    boost::asio::thread_pool::basic_executor_type<Allocator, Bits>,
    boost::asio::execution::relationship_t::fork_t
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::thread_pool::basic_executor_type<
      Allocator, Bits> result_type;
};

template <typename Allocator, unsigned int Bits>
struct require_member<
    boost::asio::thread_pool::basic_executor_type<Allocator, Bits>,
    boost::asio::execution::relationship_t::continuation_t
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::thread_pool::basic_executor_type<
      Allocator, Bits> result_type;
};

template <typename Allocator, unsigned int Bits>
struct require_member<
    boost::asio::thread_pool::basic_executor_type<Allocator, Bits>,
    boost::asio::execution::outstanding_work_t::tracked_t
  > : boost::asio::detail::thread_pool_bits
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::thread_pool::basic_executor_type<
      Allocator, Bits | outstanding_work_tracked> result_type;
};

template <typename Allocator, unsigned int Bits>
struct require_member<
    boost::asio::thread_pool::basic_executor_type<Allocator, Bits>,
    boost::asio::execution::outstanding_work_t::untracked_t
  > : boost::asio::detail::thread_pool_bits
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::thread_pool::basic_executor_type<
      Allocator, Bits & ~outstanding_work_tracked> result_type;
};

template <typename Allocator, unsigned int Bits>
struct require_member<
    boost::asio::thread_pool::basic_executor_type<Allocator, Bits>,
    boost::asio::execution::allocator_t<void>
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::thread_pool::basic_executor_type<
      std::allocator<void>, Bits> result_type;
};

template <unsigned int Bits,
    typename Allocator, typename OtherAllocator>
struct require_member<
    boost::asio::thread_pool::basic_executor_type<Allocator, Bits>,
    boost::asio::execution::allocator_t<OtherAllocator>
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::thread_pool::basic_executor_type<
      OtherAllocator, Bits> result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_STATIC_CONSTEXPR_MEMBER_TRAIT)

template <typename Allocator, unsigned int Bits, typename Property>
struct query_static_constexpr_member<
    boost::asio::thread_pool::basic_executor_type<Allocator, Bits>,
    Property,
    typename boost::asio::enable_if<
      boost::asio::is_convertible<
        Property,
        boost::asio::execution::bulk_guarantee_t
      >::value
    >::type
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef boost::asio::execution::bulk_guarantee_t::parallel_t result_type;

  static BOOST_ASIO_CONSTEXPR result_type value() BOOST_ASIO_NOEXCEPT
  {
    return result_type();
  }
};

template <typename Allocator, unsigned int Bits, typename Property>
struct query_static_constexpr_member<
    boost::asio::thread_pool::basic_executor_type<Allocator, Bits>,
    Property,
    typename boost::asio::enable_if<
      boost::asio::is_convertible<
        Property,
        boost::asio::execution::outstanding_work_t
      >::value
    >::type
  > : boost::asio::detail::thread_pool_bits
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef boost::asio::execution::outstanding_work_t result_type;

  static BOOST_ASIO_CONSTEXPR result_type value() BOOST_ASIO_NOEXCEPT
  {
    return (Bits & outstanding_work_tracked)
      ? execution::outstanding_work_t(execution::outstanding_work.tracked)
      : execution::outstanding_work_t(execution::outstanding_work.untracked);
  }
};

template <typename Allocator, unsigned int Bits, typename Property>
struct query_static_constexpr_member<
    boost::asio::thread_pool::basic_executor_type<Allocator, Bits>,
    Property,
    typename boost::asio::enable_if<
      boost::asio::is_convertible<
        Property,
        boost::asio::execution::mapping_t
      >::value
    >::type
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef boost::asio::execution::mapping_t::thread_t result_type;

  static BOOST_ASIO_CONSTEXPR result_type value() BOOST_ASIO_NOEXCEPT
  {
    return result_type();
  }
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_STATIC_CONSTEXPR_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_MEMBER_TRAIT)

template <typename Allocator, unsigned int Bits, typename Property>
struct query_member<
    boost::asio::thread_pool::basic_executor_type<Allocator, Bits>,
    Property,
    typename boost::asio::enable_if<
      boost::asio::is_convertible<
        Property,
        boost::asio::execution::blocking_t
      >::value
    >::type
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef boost::asio::execution::blocking_t result_type;
};

template <typename Allocator, unsigned int Bits, typename Property>
struct query_member<
    boost::asio::thread_pool::basic_executor_type<Allocator, Bits>,
    Property,
    typename boost::asio::enable_if<
      boost::asio::is_convertible<
        Property,
        boost::asio::execution::relationship_t
      >::value
    >::type
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef boost::asio::execution::relationship_t result_type;
};

template <typename Allocator, unsigned int Bits>
struct query_member<
    boost::asio::thread_pool::basic_executor_type<Allocator, Bits>,
    boost::asio::execution::occupancy_t
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef std::size_t result_type;
};

template <typename Allocator, unsigned int Bits>
struct query_member<
    boost::asio::thread_pool::basic_executor_type<Allocator, Bits>,
    boost::asio::execution::context_t
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef boost::asio::thread_pool& result_type;
};

template <typename Allocator, unsigned int Bits>
struct query_member<
    boost::asio::thread_pool::basic_executor_type<Allocator, Bits>,
    boost::asio::execution::allocator_t<void>
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef Allocator result_type;
};

template <typename Allocator, unsigned int Bits, typename OtherAllocator>
struct query_member<
    boost::asio::thread_pool::basic_executor_type<Allocator, Bits>,
    boost::asio::execution::allocator_t<OtherAllocator>
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef Allocator result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_MEMBER_TRAIT)

} // namespace traits

namespace execution {

template <>
struct is_executor<thread_pool> : false_type
{
};

} // namespace execution

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/thread_pool.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/impl/thread_pool.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_THREAD_POOL_HPP

/* thread_pool.hpp
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
*/