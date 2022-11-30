//
// detail/strand_executor_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution.hpp>
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
  template <typename Executor, typename Function>
  static void execute(const implementation_type& impl, Executor& ex,
      BOOST_ASIO_MOVE_ARG(Function) function,
      typename enable_if<
        can_query<Executor, execution::allocator_t<void> >::value
      >::type* = 0);

  // Request invocation of the given function.
  template <typename Executor, typename Function>
  static void execute(const implementation_type& impl, Executor& ex,
      BOOST_ASIO_MOVE_ARG(Function) function,
      typename enable_if<
        !can_query<Executor, execution::allocator_t<void> >::value
      >::type* = 0);

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
  template <typename F, typename Allocator> class allocator_binder;
  template <typename Executor, typename = void> class invoker;

  // Adds a function to the strand. Returns true if it acquires the lock.
  BOOST_ASIO_DECL static bool enqueue(const implementation_type& impl,
      scheduler_operation* op);

  // Transfers waiting handlers to the ready queue. Returns true if one or more
  // handlers were transferred.
  BOOST_ASIO_DECL static bool push_waiting_to_ready(implementation_type& impl);

  // Invokes all ready-to-run handlers.
  BOOST_ASIO_DECL static void run_ready_handlers(implementation_type& impl);

  // Helper function to request invocation of the given function.
  template <typename Executor, typename Function, typename Allocator>
  static void do_execute(const implementation_type& impl, Executor& ex,
      BOOST_ASIO_MOVE_ARG(Function) function, const Allocator& a);

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