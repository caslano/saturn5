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
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
*/