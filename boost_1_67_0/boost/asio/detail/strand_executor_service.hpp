//
// detail/strand_executor_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STRAND_EXECUTOR_SERVICE_HPP
#define BOOST_ASIO_DETAIL_STRAND_EXECUTOR_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/atomic_count.hpp>
#include <boost/asio/detail/executor_op.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/mutex.hpp>
#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/detail/scheduler_operation.hpp>
#include <boost/asio/detail/scoped_ptr.hpp>
#include <boost/asio/execution_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Default service implementation for a strand.
class strand_executor_service
  : public execution_context_service_base<strand_executor_service>
{
public:
  // The underlying implementation of a strand.
  class strand_impl
  {
  public:
    BOOST_ASIO_DECL ~strand_impl();

  private:
    friend class strand_executor_service;

    // Mutex to protect access to internal data.
    mutex* mutex_;

    // Indicates whether the strand is currently "locked" by a handler. This
    // means that there is a handler upcall in progress, or that the strand
    // itself has been scheduled in order to invoke some pending handlers.
    bool locked_;

    // Indicates that the strand has been shut down and will accept no further
    // handlers.
    bool shutdown_;

    // The handlers that are waiting on the strand but should not be run until
    // after the next time the strand is scheduled. This queue must only be
    // modified while the mutex is locked.
    op_queue<scheduler_operation> waiting_queue_;

    // The handlers that are ready to be run. Logically speaking, these are the
    // handlers that hold the strand's lock. The ready queue is only modified
    // from within the strand and so may be accessed without locking the mutex.
    op_queue<scheduler_operation> ready_queue_;

    // Pointers to adjacent handle implementations in linked list.
    strand_impl* next_;
    strand_impl* prev_;

    // The strand service in where the implementation is held.
    strand_executor_service* service_;
  };

  typedef shared_ptr<strand_impl> implementation_type;

  // Construct a new strand service for the specified context.
  BOOST_ASIO_DECL explicit strand_executor_service(execution_context& context);

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void shutdown();

  // Create a new strand_executor implementation.
  BOOST_ASIO_DECL implementation_type create_implementation();

  // Request invocation of the given function.
  template <typename Executor, typename Function, typename Allocator>
  static void dispatch(const implementation_type& impl, Executor& ex,
      BOOST_ASIO_MOVE_ARG(Function) function, const Allocator& a);

  // Request invocation of the given function and return immediately.
  template <typename Executor, typename Function, typename Allocator>
  static void post(const implementation_type& impl, Executor& ex,
      BOOST_ASIO_MOVE_ARG(Function) function, const Allocator& a);

  // Request invocation of the given function and return immediately.
  template <typename Executor, typename Function, typename Allocator>
  static void defer(const implementation_type& impl, Executor& ex,
      BOOST_ASIO_MOVE_ARG(Function) function, const Allocator& a);

  // Determine whether the strand is running in the current thread.
  BOOST_ASIO_DECL static bool running_in_this_thread(
      const implementation_type& impl);

private:
  friend class strand_impl;
  template <typename Executor> class invoker;

  // Adds a function to the strand. Returns true if it acquires the lock.
  BOOST_ASIO_DECL static bool enqueue(const implementation_type& impl,
      scheduler_operation* op);

  // Mutex to protect access to the service-wide state.
  mutex mutex_;

  // Number of mutexes shared between all strand objects.
  enum { num_mutexes = 193 };

  // Pool of mutexes.
  scoped_ptr<mutex> mutexes_[num_mutexes];

  // Extra value used when hashing to prevent recycled memory locations from
  // getting the same mutex.
  std::size_t salt_;

  // The head of a linked list of all implementations.
  strand_impl* impl_list_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/detail/impl/strand_executor_service.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/strand_executor_service.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_DETAIL_STRAND_EXECUTOR_SERVICE_HPP

/* strand_executor_service.hpp
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
*/