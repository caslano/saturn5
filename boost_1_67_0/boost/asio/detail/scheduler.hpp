//
// detail/scheduler.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SCHEDULER_HPP
#define BOOST_ASIO_DETAIL_SCHEDULER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/system/error_code.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/detail/atomic_count.hpp>
#include <boost/asio/detail/conditionally_enabled_event.hpp>
#include <boost/asio/detail/conditionally_enabled_mutex.hpp>
#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/detail/reactor_fwd.hpp>
#include <boost/asio/detail/scheduler_operation.hpp>
#include <boost/asio/detail/thread.hpp>
#include <boost/asio/detail/thread_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

struct scheduler_thread_info;

class scheduler
  : public execution_context_service_base<scheduler>,
    public thread_context
{
public:
  typedef scheduler_operation operation;

  // Constructor. Specifies the number of concurrent threads that are likely to
  // run the scheduler. If set to 1 certain optimisation are performed.
  BOOST_ASIO_DECL scheduler(boost::asio::execution_context& ctx,
      int concurrency_hint = 0, bool own_thread = true);

  // Destructor.
  BOOST_ASIO_DECL ~scheduler();

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void shutdown();

  // Initialise the task, if required.
  BOOST_ASIO_DECL void init_task();

  // Run the event loop until interrupted or no more work.
  BOOST_ASIO_DECL std::size_t run(boost::system::error_code& ec);

  // Run until interrupted or one operation is performed.
  BOOST_ASIO_DECL std::size_t run_one(boost::system::error_code& ec);

  // Run until timeout, interrupted, or one operation is performed.
  BOOST_ASIO_DECL std::size_t wait_one(
      long usec, boost::system::error_code& ec);

  // Poll for operations without blocking.
  BOOST_ASIO_DECL std::size_t poll(boost::system::error_code& ec);

  // Poll for one operation without blocking.
  BOOST_ASIO_DECL std::size_t poll_one(boost::system::error_code& ec);

  // Interrupt the event processing loop.
  BOOST_ASIO_DECL void stop();

  // Determine whether the scheduler is stopped.
  BOOST_ASIO_DECL bool stopped() const;

  // Restart in preparation for a subsequent run invocation.
  BOOST_ASIO_DECL void restart();

  // Notify that some work has started.
  void work_started()
  {
    ++outstanding_work_;
  }

  // Used to compensate for a forthcoming work_finished call. Must be called
  // from within a scheduler-owned thread.
  BOOST_ASIO_DECL void compensating_work_started();

  // Notify that some work has finished.
  void work_finished()
  {
    if (--outstanding_work_ == 0)
      stop();
  }

  // Return whether a handler can be dispatched immediately.
  bool can_dispatch()
  {
    return thread_call_stack::contains(this) != 0;
  }

  // Request invocation of the given operation and return immediately. Assumes
  // that work_started() has not yet been called for the operation.
  BOOST_ASIO_DECL void post_immediate_completion(
      operation* op, bool is_continuation);

  // Request invocation of the given operation and return immediately. Assumes
  // that work_started() was previously called for the operation.
  BOOST_ASIO_DECL void post_deferred_completion(operation* op);

  // Request invocation of the given operations and return immediately. Assumes
  // that work_started() was previously called for each operation.
  BOOST_ASIO_DECL void post_deferred_completions(op_queue<operation>& ops);

  // Enqueue the given operation following a failed attempt to dispatch the
  // operation for immediate invocation.
  BOOST_ASIO_DECL void do_dispatch(operation* op);

  // Process unfinished operations as part of a shutdownoperation. Assumes that
  // work_started() was previously called for the operations.
  BOOST_ASIO_DECL void abandon_operations(op_queue<operation>& ops);

  // Get the concurrency hint that was used to initialise the scheduler.
  int concurrency_hint() const
  {
    return concurrency_hint_;
  }

private:
  // The mutex type used by this scheduler.
  typedef conditionally_enabled_mutex mutex;

  // The event type used by this scheduler.
  typedef conditionally_enabled_event event;

  // Structure containing thread-specific data.
  typedef scheduler_thread_info thread_info;

  // Run at most one operation. May block.
  BOOST_ASIO_DECL std::size_t do_run_one(mutex::scoped_lock& lock,
      thread_info& this_thread, const boost::system::error_code& ec);

  // Run at most one operation with a timeout. May block.
  BOOST_ASIO_DECL std::size_t do_wait_one(mutex::scoped_lock& lock,
      thread_info& this_thread, long usec, const boost::system::error_code& ec);

  // Poll for at most one operation.
  BOOST_ASIO_DECL std::size_t do_poll_one(mutex::scoped_lock& lock,
      thread_info& this_thread, const boost::system::error_code& ec);

  // Stop the task and all idle threads.
  BOOST_ASIO_DECL void stop_all_threads(mutex::scoped_lock& lock);

  // Wake a single idle thread, or the task, and always unlock the mutex.
  BOOST_ASIO_DECL void wake_one_thread_and_unlock(
      mutex::scoped_lock& lock);

  // Helper class to run the scheduler in its own thread.
  class thread_function;
  friend class thread_function;

  // Helper class to perform task-related operations on block exit.
  struct task_cleanup;
  friend struct task_cleanup;

  // Helper class to call work-related operations on block exit.
  struct work_cleanup;
  friend struct work_cleanup;

  // Whether to optimise for single-threaded use cases.
  const bool one_thread_;

  // Mutex to protect access to internal data.
  mutable mutex mutex_;

  // Event to wake up blocked threads.
  event wakeup_event_;

  // The task to be run by this service.
  reactor* task_;

  // Operation object to represent the position of the task in the queue.
  struct task_operation : operation
  {
    task_operation() : operation(0) {}
  } task_operation_;

  // Whether the task has been interrupted.
  bool task_interrupted_;

  // The count of unfinished work.
  atomic_count outstanding_work_;

  // The queue of handlers that are ready to be delivered.
  op_queue<operation> op_queue_;

  // Flag to indicate that the dispatcher has been stopped.
  bool stopped_;

  // Flag to indicate that the dispatcher has been shut down.
  bool shutdown_;

  // The concurrency hint used to initialise the scheduler.
  const int concurrency_hint_;

  // The thread that is running the scheduler.
  boost::asio::detail::thread* thread_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/scheduler.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_DETAIL_SCHEDULER_HPP

/* scheduler.hpp
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
*/