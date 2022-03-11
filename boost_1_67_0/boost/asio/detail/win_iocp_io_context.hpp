//
// detail/win_iocp_io_context.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_IO_CONTEXT_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_IO_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/limits.hpp>
#include <boost/asio/detail/mutex.hpp>
#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/detail/scoped_ptr.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/thread.hpp>
#include <boost/asio/detail/thread_context.hpp>
#include <boost/asio/detail/timer_queue_base.hpp>
#include <boost/asio/detail/timer_queue_set.hpp>
#include <boost/asio/detail/wait_op.hpp>
#include <boost/asio/detail/win_iocp_operation.hpp>
#include <boost/asio/detail/win_iocp_thread_info.hpp>
#include <boost/asio/execution_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class wait_op;

class win_iocp_io_context
  : public execution_context_service_base<win_iocp_io_context>,
    public thread_context
{
public:
  // Constructor. Specifies a concurrency hint that is passed through to the
  // underlying I/O completion port.
  BOOST_ASIO_DECL win_iocp_io_context(boost::asio::execution_context& ctx,
      int concurrency_hint = -1, bool own_thread = true);

  // Destructor.
  BOOST_ASIO_DECL ~win_iocp_io_context();

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void shutdown();

  // Initialise the task. Nothing to do here.
  void init_task()
  {
  }

  // Register a handle with the IO completion port.
  BOOST_ASIO_DECL boost::system::error_code register_handle(
      HANDLE handle, boost::system::error_code& ec);

  // Run the event loop until stopped or no more work.
  BOOST_ASIO_DECL size_t run(boost::system::error_code& ec);

  // Run until stopped or one operation is performed.
  BOOST_ASIO_DECL size_t run_one(boost::system::error_code& ec);

  // Run until timeout, interrupted, or one operation is performed.
  BOOST_ASIO_DECL size_t wait_one(long usec, boost::system::error_code& ec);

  // Poll for operations without blocking.
  BOOST_ASIO_DECL size_t poll(boost::system::error_code& ec);

  // Poll for one operation without blocking.
  BOOST_ASIO_DECL size_t poll_one(boost::system::error_code& ec);

  // Stop the event processing loop.
  BOOST_ASIO_DECL void stop();

  // Determine whether the io_context is stopped.
  bool stopped() const
  {
    return ::InterlockedExchangeAdd(&stopped_, 0) != 0;
  }

  // Restart in preparation for a subsequent run invocation.
  void restart()
  {
    ::InterlockedExchange(&stopped_, 0);
  }

  // Notify that some work has started.
  void work_started()
  {
    ::InterlockedIncrement(&outstanding_work_);
  }

  // Notify that some work has finished.
  void work_finished()
  {
    if (::InterlockedDecrement(&outstanding_work_) == 0)
      stop();
  }

  // Return whether a handler can be dispatched immediately.
  bool can_dispatch()
  {
    return thread_call_stack::contains(this) != 0;
  }

  // Request invocation of the given operation and return immediately. Assumes
  // that work_started() has not yet been called for the operation.
  void post_immediate_completion(win_iocp_operation* op, bool)
  {
    work_started();
    post_deferred_completion(op);
  }

  // Request invocation of the given operation and return immediately. Assumes
  // that work_started() was previously called for the operation.
  BOOST_ASIO_DECL void post_deferred_completion(win_iocp_operation* op);

  // Request invocation of the given operation and return immediately. Assumes
  // that work_started() was previously called for the operations.
  BOOST_ASIO_DECL void post_deferred_completions(
      op_queue<win_iocp_operation>& ops);

  // Request invocation of the given operation using the thread-private queue
  // and return immediately. Assumes that work_started() has not yet been
  // called for the operation.
  void post_private_immediate_completion(win_iocp_operation* op)
  {
    post_immediate_completion(op, false);
  }

  // Request invocation of the given operation using the thread-private queue
  // and return immediately. Assumes that work_started() was previously called
  // for the operation.
  void post_private_deferred_completion(win_iocp_operation* op)
  {
    post_deferred_completion(op);
  }

  // Enqueue the given operation following a failed attempt to dispatch the
  // operation for immediate invocation.
  void do_dispatch(operation* op)
  {
    post_immediate_completion(op, false);
  }

  // Process unfinished operations as part of a shutdown operation. Assumes
  // that work_started() was previously called for the operations.
  BOOST_ASIO_DECL void abandon_operations(op_queue<operation>& ops);

  // Called after starting an overlapped I/O operation that did not complete
  // immediately. The caller must have already called work_started() prior to
  // starting the operation.
  BOOST_ASIO_DECL void on_pending(win_iocp_operation* op);

  // Called after starting an overlapped I/O operation that completed
  // immediately. The caller must have already called work_started() prior to
  // starting the operation.
  BOOST_ASIO_DECL void on_completion(win_iocp_operation* op,
      DWORD last_error = 0, DWORD bytes_transferred = 0);

  // Called after starting an overlapped I/O operation that completed
  // immediately. The caller must have already called work_started() prior to
  // starting the operation.
  BOOST_ASIO_DECL void on_completion(win_iocp_operation* op,
      const boost::system::error_code& ec, DWORD bytes_transferred = 0);

  // Add a new timer queue to the service.
  template <typename Time_Traits>
  void add_timer_queue(timer_queue<Time_Traits>& timer_queue);

  // Remove a timer queue from the service.
  template <typename Time_Traits>
  void remove_timer_queue(timer_queue<Time_Traits>& timer_queue);

  // Schedule a new operation in the given timer queue to expire at the
  // specified absolute time.
  template <typename Time_Traits>
  void schedule_timer(timer_queue<Time_Traits>& queue,
      const typename Time_Traits::time_type& time,
      typename timer_queue<Time_Traits>::per_timer_data& timer, wait_op* op);

  // Cancel the timer associated with the given token. Returns the number of
  // handlers that have been posted or dispatched.
  template <typename Time_Traits>
  std::size_t cancel_timer(timer_queue<Time_Traits>& queue,
      typename timer_queue<Time_Traits>::per_timer_data& timer,
      std::size_t max_cancelled = (std::numeric_limits<std::size_t>::max)());

  // Move the timer operations associated with the given timer.
  template <typename Time_Traits>
  void move_timer(timer_queue<Time_Traits>& queue,
      typename timer_queue<Time_Traits>::per_timer_data& to,
      typename timer_queue<Time_Traits>::per_timer_data& from);

  // Get the concurrency hint that was used to initialise the io_context.
  int concurrency_hint() const
  {
    return concurrency_hint_;
  }

private:
#if defined(WINVER) && (WINVER < 0x0500)
  typedef DWORD dword_ptr_t;
  typedef ULONG ulong_ptr_t;
#else // defined(WINVER) && (WINVER < 0x0500)
  typedef DWORD_PTR dword_ptr_t;
  typedef ULONG_PTR ulong_ptr_t;
#endif // defined(WINVER) && (WINVER < 0x0500)

  // Dequeues at most one operation from the I/O completion port, and then
  // executes it. Returns the number of operations that were dequeued (i.e.
  // either 0 or 1).
  BOOST_ASIO_DECL size_t do_one(DWORD msec, boost::system::error_code& ec);

  // Helper to calculate the GetQueuedCompletionStatus timeout.
  BOOST_ASIO_DECL static DWORD get_gqcs_timeout();

  // Helper function to add a new timer queue.
  BOOST_ASIO_DECL void do_add_timer_queue(timer_queue_base& queue);

  // Helper function to remove a timer queue.
  BOOST_ASIO_DECL void do_remove_timer_queue(timer_queue_base& queue);

  // Called to recalculate and update the timeout.
  BOOST_ASIO_DECL void update_timeout();

  // Helper class to call work_finished() on block exit.
  struct work_finished_on_block_exit;

  // Helper class for managing a HANDLE.
  struct auto_handle
  {
    HANDLE handle;
    auto_handle() : handle(0) {}
    ~auto_handle() { if (handle) ::CloseHandle(handle); }
  };

  // The IO completion port used for queueing operations.
  auto_handle iocp_;

  // The count of unfinished work.
  long outstanding_work_;

  // Flag to indicate whether the event loop has been stopped.
  mutable long stopped_;

  // Flag to indicate whether there is an in-flight stop event. Every event
  // posted using PostQueuedCompletionStatus consumes non-paged pool, so to
  // avoid exhausting this resouce we limit the number of outstanding events.
  long stop_event_posted_;

  // Flag to indicate whether the service has been shut down.
  long shutdown_;

  enum
  {
    // Timeout to use with GetQueuedCompletionStatus on older versions of
    // Windows. Some versions of windows have a "bug" where a call to
    // GetQueuedCompletionStatus can appear stuck even though there are events
    // waiting on the queue. Using a timeout helps to work around the issue.
    default_gqcs_timeout = 500,

    // Maximum waitable timer timeout, in milliseconds.
    max_timeout_msec = 5 * 60 * 1000,

    // Maximum waitable timer timeout, in microseconds.
    max_timeout_usec = max_timeout_msec * 1000,

    // Completion key value used to wake up a thread to dispatch timers or
    // completed operations.
    wake_for_dispatch = 1,

    // Completion key value to indicate that an operation has posted with the
    // original last_error and bytes_transferred values stored in the fields of
    // the OVERLAPPED structure.
    overlapped_contains_result = 2
  };

  // Timeout to use with GetQueuedCompletionStatus.
  const DWORD gqcs_timeout_;

  // Helper class to run the scheduler in its own thread.
  struct thread_function;
  friend struct thread_function;

  // Function object for processing timeouts in a background thread.
  struct timer_thread_function;
  friend struct timer_thread_function;

  // Background thread used for processing timeouts.
  scoped_ptr<thread> timer_thread_;

  // A waitable timer object used for waiting for timeouts.
  auto_handle waitable_timer_;

  // Non-zero if timers or completed operations need to be dispatched.
  long dispatch_required_;

  // Mutex for protecting access to the timer queues and completed operations.
  mutex dispatch_mutex_;

  // The timer queues.
  timer_queue_set timer_queues_;

  // The operations that are ready to dispatch.
  op_queue<win_iocp_operation> completed_ops_;

  // The concurrency hint used to initialise the io_context.
  const int concurrency_hint_;

  // The thread that is running the io_context.
  scoped_ptr<thread> thread_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/detail/impl/win_iocp_io_context.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/win_iocp_io_context.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_IO_CONTEXT_HPP

/* win_iocp_io_context.hpp
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
*/