//
// detail/epoll_reactor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
  : public execution_context_service_base<epoll_reactor>
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
  void post_immediate_completion(reactor_op* op, bool is_continuation)
  {
    scheduler_.post_immediate_completion(op, is_continuation);
  }

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