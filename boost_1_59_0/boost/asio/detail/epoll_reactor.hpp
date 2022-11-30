//
// detail/epoll_reactor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_EPOLL_REACTOR_HPP
#define BOOST_ASIO_DETAIL_EPOLL_REACTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_EPOLL)

#include <boost/asio/detail/atomic_count.hpp>
#include <boost/asio/detail/conditionally_enabled_mutex.hpp>
#include <boost/asio/detail/limits.hpp>
#include <boost/asio/detail/object_pool.hpp>
#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/detail/reactor_op.hpp>
#include <boost/asio/detail/scheduler_task.hpp>
#include <boost/asio/detail/select_interrupter.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/timer_queue_base.hpp>
#include <boost/asio/detail/timer_queue_set.hpp>
#include <boost/asio/detail/wait_op.hpp>
#include <boost/asio/execution_context.hpp>

#if defined(BOOST_ASIO_HAS_TIMERFD)
# include <sys/timerfd.h>
#endif // defined(BOOST_ASIO_HAS_TIMERFD)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class epoll_reactor
  : public execution_context_service_base<epoll_reactor>,
    public scheduler_task
{
private:
  // The mutex type used by this reactor.
  typedef conditionally_enabled_mutex mutex;

public:
  enum op_types { read_op = 0, write_op = 1,
    connect_op = 1, except_op = 2, max_ops = 3 };

  // Per-descriptor queues.
  class descriptor_state : operation
  {
    friend class epoll_reactor;
    friend class object_pool_access;

    descriptor_state* next_;
    descriptor_state* prev_;

    mutex mutex_;
    epoll_reactor* reactor_;
    int descriptor_;
    uint32_t registered_events_;
    op_queue<reactor_op> op_queue_[max_ops];
    bool try_speculative_[max_ops];
    bool shutdown_;

    BOOST_ASIO_DECL descriptor_state(bool locking);
    void set_ready_events(uint32_t events) { task_result_ = events; }
    void add_ready_events(uint32_t events) { task_result_ |= events; }
    BOOST_ASIO_DECL operation* perform_io(uint32_t events);
    BOOST_ASIO_DECL static void do_complete(
        void* owner, operation* base,
        const boost::system::error_code& ec, std::size_t bytes_transferred);
  };

  // Per-descriptor data.
  typedef descriptor_state* per_descriptor_data;

  // Constructor.
  BOOST_ASIO_DECL epoll_reactor(boost::asio::execution_context& ctx);

  // Destructor.
  BOOST_ASIO_DECL ~epoll_reactor();

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void shutdown();

  // Recreate internal descriptors following a fork.
  BOOST_ASIO_DECL void notify_fork(
      boost::asio::execution_context::fork_event fork_ev);

  // Initialise the task.
  BOOST_ASIO_DECL void init_task();

  // Register a socket with the reactor. Returns 0 on success, system error
  // code on failure.
  BOOST_ASIO_DECL int register_descriptor(socket_type descriptor,
      per_descriptor_data& descriptor_data);

  // Register a descriptor with an associated single operation. Returns 0 on
  // success, system error code on failure.
  BOOST_ASIO_DECL int register_internal_descriptor(
      int op_type, socket_type descriptor,
      per_descriptor_data& descriptor_data, reactor_op* op);

  // Move descriptor registration from one descriptor_data object to another.
  BOOST_ASIO_DECL void move_descriptor(socket_type descriptor,
      per_descriptor_data& target_descriptor_data,
      per_descriptor_data& source_descriptor_data);

  // Post a reactor operation for immediate completion.
  void post_immediate_completion(operation* op, bool is_continuation);

  // Start a new operation. The reactor operation will be performed when the
  // given descriptor is flagged as ready, or an error has occurred.
  BOOST_ASIO_DECL void start_op(int op_type, socket_type descriptor,
      per_descriptor_data& descriptor_data, reactor_op* op,
      bool is_continuation, bool allow_speculative);

  // Cancel all operations associated with the given descriptor. The
  // handlers associated with the descriptor will be invoked with the
  // operation_aborted error.
  BOOST_ASIO_DECL void cancel_ops(socket_type descriptor,
      per_descriptor_data& descriptor_data);

  // Cancel all operations associated with the given descriptor and key. The
  // handlers associated with the descriptor will be invoked with the
  // operation_aborted error.
  BOOST_ASIO_DECL void cancel_ops_by_key(socket_type descriptor,
      per_descriptor_data& descriptor_data,
      int op_type, void* cancellation_key);

  // Cancel any operations that are running against the descriptor and remove
  // its registration from the reactor. The reactor resources associated with
  // the descriptor must be released by calling cleanup_descriptor_data.
  BOOST_ASIO_DECL void deregister_descriptor(socket_type descriptor,
      per_descriptor_data& descriptor_data, bool closing);

  // Remove the descriptor's registration from the reactor. The reactor
  // resources associated with the descriptor must be released by calling
  // cleanup_descriptor_data.
  BOOST_ASIO_DECL void deregister_internal_descriptor(
      socket_type descriptor, per_descriptor_data& descriptor_data);

  // Perform any post-deregistration cleanup tasks associated with the
  // descriptor data.
  BOOST_ASIO_DECL void cleanup_descriptor_data(
      per_descriptor_data& descriptor_data);

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

  // Run epoll once until interrupted or events are ready to be dispatched.
  BOOST_ASIO_DECL void run(long usec, op_queue<operation>& ops);

  // Interrupt the select loop.
  BOOST_ASIO_DECL void interrupt();

private:
  // The hint to pass to epoll_create to size its data structures.
  enum { epoll_size = 20000 };

  // Create the epoll file descriptor. Throws an exception if the descriptor
  // cannot be created.
  BOOST_ASIO_DECL static int do_epoll_create();

  // Create the timerfd file descriptor. Does not throw.
  BOOST_ASIO_DECL static int do_timerfd_create();

  // Allocate a new descriptor state object.
  BOOST_ASIO_DECL descriptor_state* allocate_descriptor_state();

  // Free an existing descriptor state object.
  BOOST_ASIO_DECL void free_descriptor_state(descriptor_state* s);

  // Helper function to add a new timer queue.
  BOOST_ASIO_DECL void do_add_timer_queue(timer_queue_base& queue);

  // Helper function to remove a timer queue.
  BOOST_ASIO_DECL void do_remove_timer_queue(timer_queue_base& queue);

  // Called to recalculate and update the timeout.
  BOOST_ASIO_DECL void update_timeout();

  // Get the timeout value for the epoll_wait call. The timeout value is
  // returned as a number of milliseconds. A return value of -1 indicates
  // that epoll_wait should block indefinitely.
  BOOST_ASIO_DECL int get_timeout(int msec);

#if defined(BOOST_ASIO_HAS_TIMERFD)
  // Get the timeout value for the timer descriptor. The return value is the
  // flag argument to be used when calling timerfd_settime.
  BOOST_ASIO_DECL int get_timeout(itimerspec& ts);
#endif // defined(BOOST_ASIO_HAS_TIMERFD)

  // The scheduler implementation used to post completions.
  scheduler& scheduler_;

  // Mutex to protect access to internal data.
  mutex mutex_;

  // The interrupter is used to break a blocking epoll_wait call.
  select_interrupter interrupter_;

  // The epoll file descriptor.
  int epoll_fd_;

  // The timer file descriptor.
  int timer_fd_;

  // The timer queues.
  timer_queue_set timer_queues_;

  // Whether the service has been shut down.
  bool shutdown_;

  // Mutex to protect access to the registered descriptors.
  mutex registered_descriptors_mutex_;

  // Keep track of all registered descriptors.
  object_pool<descriptor_state> registered_descriptors_;

  // Helper class to do post-perform_io cleanup.
  struct perform_io_cleanup_on_block_exit;
  friend struct perform_io_cleanup_on_block_exit;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/detail/impl/epoll_reactor.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/epoll_reactor.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_EPOLL)

#endif // BOOST_ASIO_DETAIL_EPOLL_REACTOR_HPP

/* epoll_reactor.hpp
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
*/