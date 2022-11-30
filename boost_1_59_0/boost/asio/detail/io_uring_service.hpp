//
// detail/io_uring_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IO_URING_SERVICE_HPP
#define BOOST_ASIO_DETAIL_IO_URING_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IO_URING)

#include <liburing.h>
#include <boost/asio/detail/atomic_count.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/conditionally_enabled_mutex.hpp>
#include <boost/asio/detail/io_uring_operation.hpp>
#include <boost/asio/detail/limits.hpp>
#include <boost/asio/detail/object_pool.hpp>
#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/detail/reactor.hpp>
#include <boost/asio/detail/scheduler_task.hpp>
#include <boost/asio/detail/timer_queue_base.hpp>
#include <boost/asio/detail/timer_queue_set.hpp>
#include <boost/asio/detail/wait_op.hpp>
#include <boost/asio/execution_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class io_uring_service
  : public execution_context_service_base<io_uring_service>,
    public scheduler_task
{
private:
  // The mutex type used by this reactor.
  typedef conditionally_enabled_mutex mutex;

public:
  enum op_types { read_op = 0, write_op = 1, except_op = 2, max_ops = 3 };

  class io_object;

  // An I/O queue stores operations that must run serially.
  class io_queue : operation
  {
    friend class io_uring_service;

    io_object* io_object_;
    op_queue<io_uring_operation> op_queue_;
    bool cancel_requested_;

    BOOST_ASIO_DECL io_queue();
    void set_result(int r) { task_result_ = static_cast<unsigned>(r); }
    BOOST_ASIO_DECL operation* perform_io(int result);
    BOOST_ASIO_DECL static void do_complete(void* owner, operation* base,
        const boost::system::error_code& ec, std::size_t bytes_transferred);
  };

  // Per I/O object state.
  class io_object
  {
    friend class io_uring_service;
    friend class object_pool_access;

    io_object* next_;
    io_object* prev_;

    mutex mutex_;
    io_uring_service* service_;
    io_queue queues_[max_ops];
    bool shutdown_;

    BOOST_ASIO_DECL io_object(bool locking);
  };

  // Per I/O object data.
  typedef io_object* per_io_object_data;

  // Constructor.
  BOOST_ASIO_DECL io_uring_service(boost::asio::execution_context& ctx);

  // Destructor.
  BOOST_ASIO_DECL ~io_uring_service();

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void shutdown();

  // Recreate internal state following a fork.
  BOOST_ASIO_DECL void notify_fork(
      boost::asio::execution_context::fork_event fork_ev);

  // Initialise the task.
  BOOST_ASIO_DECL void init_task();

  // Register an I/O object with io_uring.
  BOOST_ASIO_DECL void register_io_object(io_object*& io_obj);

  // Register an internal I/O object with io_uring.
  BOOST_ASIO_DECL void register_internal_io_object(
      io_object*& io_obj, int op_type, io_uring_operation* op);

  // Register buffers with io_uring.
  BOOST_ASIO_DECL void register_buffers(const ::iovec* v, unsigned n);

  // Unregister buffers from io_uring.
  BOOST_ASIO_DECL void unregister_buffers();

  // Post an operation for immediate completion.
  void post_immediate_completion(operation* op, bool is_continuation);

  // Start a new operation. The operation will be prepared and submitted to the
  // io_uring when it is at the head of its I/O operation queue.
  BOOST_ASIO_DECL void start_op(int op_type, per_io_object_data& io_obj,
      io_uring_operation* op, bool is_continuation);

  // Cancel all operations associated with the given I/O object. The handlers
  // associated with the I/O object will be invoked with the operation_aborted
  // error.
  BOOST_ASIO_DECL void cancel_ops(per_io_object_data& io_obj);

  // Cancel all operations associated with the given I/O object and key. The
  // handlers associated with the object and key will be invoked with the
  // operation_aborted error.
  BOOST_ASIO_DECL void cancel_ops_by_key(per_io_object_data& io_obj,
      int op_type, void* cancellation_key);

  // Cancel any operations that are running against the I/O object and remove
  // its registration from the service. The service resources associated with
  // the I/O object must be released by calling cleanup_io_object.
  BOOST_ASIO_DECL void deregister_io_object(per_io_object_data& io_obj);

  // Perform any post-deregistration cleanup tasks associated with the I/O
  // object.
  BOOST_ASIO_DECL void cleanup_io_object(per_io_object_data& io_obj);

  // Add a new timer queue to the reactor.
  template <typename Time_Traits>
  void add_timer_queue(timer_queue<Time_Traits>& timer_queue);

  // Remove a timer queue from the reactor.
  template <typename Time_Traits>
  void remove_timer_queue(timer_queue<Time_Traits>& timer_queue);

  // Schedule a new operation in the given timer queue to expire at the
  // specified absolute time.
  template <typename Time_Traits>
  void schedule_timer(timer_queue<Time_Traits>& queue,
      const typename Time_Traits::time_type& time,
      typename timer_queue<Time_Traits>::per_timer_data& timer, wait_op* op);

  // Cancel the timer operations associated with the given token. Returns the
  // number of operations that have been posted or dispatched.
  template <typename Time_Traits>
  std::size_t cancel_timer(timer_queue<Time_Traits>& queue,
      typename timer_queue<Time_Traits>::per_timer_data& timer,
      std::size_t max_cancelled = (std::numeric_limits<std::size_t>::max)());

  // Cancel the timer operations associated with the given key.
  template <typename Time_Traits>
  void cancel_timer_by_key(timer_queue<Time_Traits>& queue,
      typename timer_queue<Time_Traits>::per_timer_data* timer,
      void* cancellation_key);

  // Move the timer operations associated with the given timer.
  template <typename Time_Traits>
  void move_timer(timer_queue<Time_Traits>& queue,
      typename timer_queue<Time_Traits>::per_timer_data& target,
      typename timer_queue<Time_Traits>::per_timer_data& source);

  // Wait on io_uring once until interrupted or events are ready to be
  // dispatched.
  BOOST_ASIO_DECL void run(long usec, op_queue<operation>& ops);

  // Interrupt the io_uring wait.
  BOOST_ASIO_DECL void interrupt();

private:
  // The hint to pass to io_uring_queue_init to size its data structures.
  enum { ring_size = 16384 };

  // The number of operations to submit in a batch.
  enum { submit_batch_size = 128 };

  // The number of operations to complete in a batch.
  enum { complete_batch_size = 128 };

  // The type used for processing eventfd readiness notifications.
  class event_fd_read_op;

  // Initialise the ring.
  BOOST_ASIO_DECL void init_ring();

  // Register the eventfd descriptor for readiness notifications.
  BOOST_ASIO_DECL void register_with_reactor();

  // Allocate a new I/O object.
  BOOST_ASIO_DECL io_object* allocate_io_object();

  // Free an existing I/O object.
  BOOST_ASIO_DECL void free_io_object(io_object* s);

  // Helper function to cancel all operations associated with the given I/O
  // object. This function does not acquire the I/O object's mutex.
  BOOST_ASIO_DECL void do_cancel_ops(
      per_io_object_data& io_obj, op_queue<operation>& ops);

  // Helper function to add a new timer queue.
  BOOST_ASIO_DECL void do_add_timer_queue(timer_queue_base& queue);

  // Helper function to remove a timer queue.
  BOOST_ASIO_DECL void do_remove_timer_queue(timer_queue_base& queue);

  // Called to recalculate and update the timeout.
  BOOST_ASIO_DECL void update_timeout();

  // Get the current timeout value.
  BOOST_ASIO_DECL __kernel_timespec get_timeout() const;

  // Get a new submission queue entry, flushing the queue if necessary.
  BOOST_ASIO_DECL ::io_uring_sqe* get_sqe();

  // Submit pending submission queue entries.
  BOOST_ASIO_DECL void submit_sqes();

  // Post an operation to submit the pending submission queue entries.
  BOOST_ASIO_DECL void post_submit_sqes_op(mutex::scoped_lock& lock);

  // Push an operation to submit the pending submission queue entries.
  BOOST_ASIO_DECL void push_submit_sqes_op(op_queue<operation>& ops);

  // Helper operation to submit pending submission queue entries.
  class submit_sqes_op : operation
  {
    friend class io_uring_service;

    io_uring_service* service_;

    BOOST_ASIO_DECL submit_sqes_op(io_uring_service* s);
    BOOST_ASIO_DECL static void do_complete(void* owner, operation* base,
        const boost::system::error_code& ec, std::size_t bytes_transferred);
  };

  // The scheduler implementation used to post completions.
  scheduler& scheduler_;

  // Mutex to protect access to internal data.
  mutex mutex_;

  // The ring.
  ::io_uring ring_;

  // The count of unfinished work.
  atomic_count outstanding_work_;

  // The operation used to submit the pending submission queue entries.
  submit_sqes_op submit_sqes_op_;

  // The number of pending submission queue entries_.
  int pending_sqes_;

  // Whether there is a pending submission operation.
  bool pending_submit_sqes_op_;

  // Whether the service has been shut down.
  bool shutdown_;

  // The timer queues.
  timer_queue_set timer_queues_;

  // The timespec for the pending timeout operation. Must remain valid while the
  // operation is outstanding.
  __kernel_timespec timeout_;

  // Mutex to protect access to the registered I/O objects.
  mutex registration_mutex_;

  // Keep track of all registered I/O objects.
  object_pool<io_object> registered_io_objects_;

  // Helper class to do post-perform_io cleanup.
  struct perform_io_cleanup_on_block_exit;
  friend struct perform_io_cleanup_on_block_exit;

  // The reactor used to register for eventfd readiness.
  reactor& reactor_;

  // The per-descriptor reactor data used for the eventfd.
  reactor::per_descriptor_data reactor_data_;

  // The eventfd descriptor used to wait for readiness.
  int event_fd_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/detail/impl/io_uring_service.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/io_uring_service.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_IO_URING)

#endif // BOOST_ASIO_DETAIL_IO_URING_SERVICE_HPP

/* io_uring_service.hpp
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
*/