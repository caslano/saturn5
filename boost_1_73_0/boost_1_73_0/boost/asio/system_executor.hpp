//
// system_executor.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SYSTEM_EXECUTOR_HPP
#define BOOST_ASIO_SYSTEM_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

class system_context;

/// An executor that uses arbitrary threads.
/**
 * The system executor represents an execution context where functions are
 * permitted to run on arbitrary threads. The post() and defer() functions
 * schedule the function to run on an unspecified system thread pool, and
 * dispatch() invokes the function immediately.
 */
class system_executor
{
public:
  /// Obtain the underlying execution context.
  system_context& context() const BOOST_ASIO_NOEXCEPT;

  /// Inform the executor that it has some outstanding work to do.
  /**
   * For the system executor, this is a no-op.
   */
  void on_work_started() const BOOST_ASIO_NOEXCEPT
  {
  }

  /// Inform the executor that some work is no longer outstanding.
  /**
   * For the system executor, this is a no-op.
   */
  void on_work_finished() const BOOST_ASIO_NOEXCEPT
  {
  }

  /// Request the system executor to invoke the given function object.
  /**
   * This function is used to ask the executor to execute the given function
   * object. The function object will always be executed inside this function.
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

  /// Request the system executor to invoke the given function object.
  /**
   * This function is used to ask the executor to execute the given function
   * object. The function object will never be executed inside this function.
   * Instead, it will be scheduled to run on an unspecified system thread pool.
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

  /// Request the system executor to invoke the given function object.
  /**
   * This function is used to ask the executor to execute the given function
   * object. The function object will never be executed inside this function.
   * Instead, it will be scheduled to run on an unspecified system thread pool.
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

  /// Compare two executors for equality.
  /**
   * System executors always compare equal.
   */
  friend bool operator==(const system_executor&,
      const system_executor&) BOOST_ASIO_NOEXCEPT
  {
    return true;
  }

  /// Compare two executors for inequality.
  /**
   * System executors always compare equal.
   */
  friend bool operator!=(const system_executor&,
      const system_executor&) BOOST_ASIO_NOEXCEPT
  {
    return false;
  }
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/system_executor.hpp>

#endif // BOOST_ASIO_SYSTEM_EXECUTOR_HPP

/* system_executor.hpp
XlkGHIsrJlGXUr7C1uHuHxcP7aqEzEPM7XFfPV/f1HBSgubTv05QY4TV8mp5fQedvrgrdoYYPsmfrepPzsrbVzK/AVBLAwQKAAAACAAtZ0pSIoivpLwGAADlEwAAHAAJAGN1cmwtbWFzdGVyL2RvY3MvTWFrZWZpbGUuYW1VVAUAAbZIJGCtWG1v2kgQ/hz/irkU9eCEoc19uabNqQ6YYIXY1DZN0eXkM/aC92ps5F3yIvXH38zaHBClxUilamzW88zMzsyO5+HVbz/vo72Cg59A/Q/wg1cCjIv8XxbJl4WD4BuU/xB0h9cDJrqwRXwLWnAQ8Q2aChFUNj7QfRAcMHNHjtGfLgHvArrFFe0V4nr56qngi0RCs9eCt+/e/QE6nL05e9OGfphxloInWTZjxaINH2K18jEJHx87gv3ZBiYhTDtKkZ9wASKfy4ewYID3KY9YJlgMoYCYiajgM/zCM5AJgzlPGfSc8dSyr9rwkPAoQR1P+RpEkq/TGJLwnkHBIsbvSxWrsJCQzxGNumMuJOpbS55nHTTNQLJiKVAFGQ9TkUN4H/I0nKGZUEIi5Uqcd7vRukjR826cR6IbbbbeSeSy2sUUPViGT5CvJMgc1oK1geTasMxjPqcrhgIXV+tZykXS3rqChrK4mxcg
*/