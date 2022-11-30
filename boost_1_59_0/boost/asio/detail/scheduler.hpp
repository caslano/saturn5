//
// detail/scheduler.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/scheduler_operation.hpp>
#include <boost/asio/detail/scheduler_task.hpp>
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

  // The type of a function used to obtain a task instance.
  typedef scheduler_task* (*get_task_func_type)(
      boost::asio::execution_context&);

  // Constructor. Specifies the number of concurrent threads that are likely to
  // run the scheduler. If set to 1 certain optimisation are performed.
  BOOST_ASIO_DECL scheduler(boost::asio::execution_context& ctx,
      int concurrency_hint = 0, bool own_thread = true,
      get_task_func_type get_task = &scheduler::get_default_task);

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
  BOOST_ASIO_DECL bool can_dispatch();

  /// Capture the current exception so it can be rethrown from a run function.
  BOOST_ASIO_DECL void capture_current_exception();

  // Request invocation of the given operation and return immediately. Assumes
  // that work_started() has not yet been called for the operation.
  BOOST_ASIO_DECL void post_immediate_completion(
      operation* op, bool is_continuation);

  // Request invocation of the given operations and return immediately. Assumes
  // that work_started() has not yet been called for the operations.
  BOOST_ASIO_DECL void post_immediate_completions(std::size_t n,
      op_queue<operation>& ops, bool is_continuation);

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

  // Get the default task.
  BOOST_ASIO_DECL static scheduler_task* get_default_task(
      boost::asio::execution_context& ctx);

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
  scheduler_task* task_;

  // The function used to get the task.
  get_task_func_type get_task_;

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