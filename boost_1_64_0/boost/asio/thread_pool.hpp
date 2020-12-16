//
// thread_pool.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/scheduler.hpp>
#include <boost/asio/detail/thread_group.hpp>
#include <boost/asio/execution_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// A simple fixed-size thread pool.
/**
 * The thread pool class is an execution context where functions are permitted
 * to run on one of a fixed number of threads.
 *
 * @par Submitting tasks to the pool
 *
 * To submit functions to the thread_pool, use the @ref boost::asio::dispatch,
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
  class executor_type;

  /// Constructs a pool with an automatically determined number of threads.
  BOOST_ASIO_DECL thread_pool();

  /// Constructs a pool with a specified number of threads.
  BOOST_ASIO_DECL thread_pool(std::size_t num_threads);

  /// Destructor.
  /**
   * Automatically stops and joins the pool, if not explicitly done beforehand.
   */
  BOOST_ASIO_DECL ~thread_pool();

  /// Obtains the executor associated with the pool.
  executor_type get_executor() BOOST_ASIO_NOEXCEPT;

  /// Stops the threads.
  /**
   * This function stops the threads as soon as possible. As a result of calling
   * @c stop(), pending function objects may be never be invoked.
   */
  BOOST_ASIO_DECL void stop();

  /// Joins the threads.
  /**
   * This function blocks until the threads in the pool have completed. If @c
   * stop() is not called prior to @c join(), the @c join() call will wait
   * until the pool has no more outstanding work.
   */
  BOOST_ASIO_DECL void join();

private:
  friend class executor_type;
  struct thread_function;

  // Helper function to create the underlying scheduler.
  BOOST_ASIO_DECL detail::scheduler& add_scheduler(detail::scheduler* s);

  // The underlying scheduler.
  detail::scheduler& scheduler_;

  // The threads in the pool.
  detail::thread_group threads_;
};

/// Executor used to submit functions to a thread pool.
class thread_pool::executor_type
{
public:
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
  template <typename Function, typename Allocator>
  void dispatch(BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const;

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
  template <typename Function, typename Allocator>
  void post(BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const;

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
  template <typename Function, typename Allocator>
  void defer(BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const;

  /// Determine whether the thread pool is running in the current thread.
  /**
   * @return @c true if the current thread belongs to the pool. Otherwise
   * returns @c false.
   */
  bool running_in_this_thread() const BOOST_ASIO_NOEXCEPT;

  /// Compare two executors for equality.
  /**
   * Two executors are equal if they refer to the same underlying thread pool.
   */
  friend bool operator==(const executor_type& a,
      const executor_type& b) BOOST_ASIO_NOEXCEPT
  {
    return &a.pool_ == &b.pool_;
  }

  /// Compare two executors for inequality.
  /**
   * Two executors are equal if they refer to the same underlying thread pool.
   */
  friend bool operator!=(const executor_type& a,
      const executor_type& b) BOOST_ASIO_NOEXCEPT
  {
    return &a.pool_ != &b.pool_;
  }

private:
  friend class thread_pool;

  // Constructor.
  explicit executor_type(thread_pool& p) : pool_(p) {}

  // The underlying thread pool.
  thread_pool& pool_;
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/thread_pool.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/impl/thread_pool.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_THREAD_POOL_HPP

/* thread_pool.hpp
HOgBQesvU2UwTKT1URarf+fmBB0HulXlrWEHp/6l1ydoPyg6osrQsOp+Lmdqm/PRDqCcylvDnmHbvAHtACqovBnmnafb+KY34swElLxc5acwf3Wt+OYeStCHQWepvDTsmbXp9mHMZ9AulbfC/OTt59fbB6W3/e4JuJsP/f8x4JM92bDZvjaO/U92KkKnAcug3zI57e2ys5N09kSCXoE4bb3wL9+j/Ch4r2lyjwZCWfOAm/dkDij+THao8r7FYSH4Kl9Cpt4ibr+XgEDdtnMVjb0lQQ+D1rxd9MkRUTpiagF8BC2kholF0JUstsJ/C8q+XVvPED4dJ0d+vmTAgTAN5KLiPFlgeNS1U9qZmX4ee+xXZio+4tC/ceFHqvPNCXoN6ClVB4YJWTAnZEGWxpdd0doa+BcLWv3jJov1X56gd4G2Xam1D8Nnykf2l/5+yLZ3JuhLoFIlT2KYTO/jjp19lt1vv8WMcYzxlBI+WNNvgm4S1HeVKodjen78LQqpt1V3zWOW7rZ8Y4LeehO+XcuXY8YrY/TK4aDl9/JkjOGjUQa+w58dsP0rfOscEWjt7Qm0GqsD0rfOYD3N/DZBZ9zTD5y0y+v+cIKuAmWvrnwDw0Rf+4xrwJ7iNPCZF/Q22LbsRfV2uVwbtt8C/c2OBO3W83fFyYHNSifN+5O/RXxHgn4FGnyHXgeOe8jr2RR4K2TwAebzXNiM9f+XvWsBk+yYwn/P9s709PS7e177mtlHsk/J2EwiWDJWErFCZjcdQhZjDTaxGGv4gmC8g2BtIoJgEkEQrBWsd1uDIGQkG4Jg5BuvTzBiEMTjv7dv9al75t7t27Ob4Pt8356vd/66dapuVd2qU6dOnXOA+ibStTXeUJjny2Wbp6s2cqMTA486sOxo9Z47PsL9HGnmtdY3znQwHYHpUJgXV29v7TRadLvlVtc3Q+5jbXgU6dyLbf/ECRd7FWmXwUmCKX0NeSGIF+KhafRrVrVd788qu3Xx1TG2nzoe0ozUQWFev6lno/R/36fbcBZp6HUWH4WHxmLmnNCx0fhkMHFGW6t2Rp9pwydI177OagOmISiNpLHYQxJ4SBSfTvMc/4HrwDY3qv+g2B3zfQ4tdO0ncpU2PJR04euXwafLHK7i7yRdbNKAACwJkB/ID8wH5kMQXzTLczrdtPtG73sZabLiBKeqdh4H23AFqfcN9hldFfs+qd/gJIV535VXtyBeiLvpOm1e/bAqjlX9Rv7S6YeX7br7nLR2ppWYVsTym6tp7loAhNzfaiBvFBv4pQ3GJFW6oFB7zZ9zXiH96hLrezwqOHxY3fh86p2j+LEa+GkbXkm68o1SpmAR5a9GYlvWsXmaynJtyqWw4U1SH4V55370OcN3WrxRndNz/c7lUziLNCI8fFhd3wPuOM5xvGXdGN9Gr1Q3zY3Vk8cKpq/g2rBir4rV48z1v2kD7uT+981SN8Eixp+X9q57fzlwzJs2HLbtCbwx7fjMLlfv/+3p4PzUmcL1UlcfVrevQ8ejTzaVdX2itXoH5q/cn/yNup89Uq6N1bUDqdseWjdpxa+b8uLXDar4dd747C2l8HLShNRNYd73HPHZ7jUJc/Y8aUqeWy7n7FgK+0ib3iK8FBbQ1xHiS4W0VZRYS5VECsnWFG6z6qSx2CrabnAMr+IYXiW+aS27Gt7bSKbwB9KSvcJHMKtNIz4bOh/a8bTKKX6jAfG0nHsT3Sl8nXSdVYbGuKaLnzaf7jTrxneaXJRCy+IUZoWHxmSfVva+BcaIEntHT3e0JIWTSCdfKnwEC/V3OGK/zySfjS1NYUx4KCz4u4gyX4/1pPAF0u3C28Kizdf7elP4Pan3MuEh2H92vp4=
*/