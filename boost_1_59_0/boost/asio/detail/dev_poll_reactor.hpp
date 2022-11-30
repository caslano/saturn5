//
// detail/dev_poll_reactor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_DEV_POLL_REACTOR_HPP
#define BOOST_ASIO_DETAIL_DEV_POLL_REACTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_DEV_POLL)

#include <cstddef>
#include <vector>
#include <sys/devpoll.h>
#include <boost/asio/detail/hash_map.hpp>
#include <boost/asio/detail/limits.hpp>
#include <boost/asio/detail/mutex.hpp>
#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/detail/reactor_op.hpp>
#include <boost/asio/detail/reactor_op_queue.hpp>
#include <boost/asio/detail/scheduler_task.hpp>
#include <boost/asio/detail/select_interrupter.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/timer_queue_base.hpp>
#include <boost/asio/detail/timer_queue_set.hpp>
#include <boost/asio/detail/wait_op.hpp>
#include <boost/asio/execution_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class dev_poll_reactor
  : public execution_context_service_base<dev_poll_reactor>,
    public scheduler_task
{
public:
  enum op_types { read_op = 0, write_op = 1,
    connect_op = 1, except_op = 2, max_ops = 3 };

  // Per-descriptor data.
  struct per_descriptor_data
  {
  };

  // Constructor.
  BOOST_ASIO_DECL dev_poll_reactor(boost::asio::execution_context& ctx);

  // Destructor.
  BOOST_ASIO_DECL ~dev_poll_reactor();

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void shutdown();

  // Recreate internal descriptors following a fork.
  BOOST_ASIO_DECL void notify_fork(
      boost::asio::execution_context::fork_event fork_ev);

  // Initialise the task.
  BOOST_ASIO_DECL void init_task();

  // Register a socket with the reactor. Returns 0 on success, system error
  // code on failure.
  BOOST_ASIO_DECL int register_descriptor(socket_type, per_descriptor_data&);

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
  void post_immediate_completion(reactor_op* op, bool is_continuation);

  // Start a new operation. The reactor operation will be performed when the
  // given descriptor is flagged as ready, or an error has occurred.
  BOOST_ASIO_DECL void start_op(int op_type, socket_type descriptor,
      per_descriptor_data&, reactor_op* op,
      bool is_continuation, bool allow_speculative);

  // Cancel all operations associated with the given descriptor. The
  // handlers associated with the descriptor will be invoked with the
  // operation_aborted error.
  BOOST_ASIO_DECL void cancel_ops(socket_type descriptor, per_descriptor_data&);

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
      per_descriptor_data&, bool closing);

  // Remove the descriptor's registration from the reactor. The reactor
  // resources associated with the descriptor must be released by calling
  // cleanup_descriptor_data.
  BOOST_ASIO_DECL void deregister_internal_descriptor(
      socket_type descriptor, per_descriptor_data&);

  // Perform any post-deregistration cleanup tasks associated with the
  // descriptor data.
  BOOST_ASIO_DECL void cleanup_descriptor_data(per_descriptor_data&);

  // Add a new timer queue to the reactor.
  template <typename Time_Traits>
  void add_timer_queue(timer_queue<Time_Traits>& queue);

  // Remove a timer queue from the reactor.
  template <typename Time_Traits>
  void remove_timer_queue(timer_queue<Time_Traits>& queue);

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

  // Run /dev/poll once until interrupted or events are ready to be dispatched.
  BOOST_ASIO_DECL void run(long usec, op_queue<operation>& ops);

  // Interrupt the select loop.
  BOOST_ASIO_DECL void interrupt();

private:
  // Create the /dev/poll file descriptor. Throws an exception if the descriptor
  // cannot be created.
  BOOST_ASIO_DECL static int do_dev_poll_create();

  // Helper function to add a new timer queue.
  BOOST_ASIO_DECL void do_add_timer_queue(timer_queue_base& queue);

  // Helper function to remove a timer queue.
  BOOST_ASIO_DECL void do_remove_timer_queue(timer_queue_base& queue);

  // Get the timeout value for the /dev/poll DP_POLL operation. The timeout
  // value is returned as a number of milliseconds. A return value of -1
  // indicates that the poll should block indefinitely.
  BOOST_ASIO_DECL int get_timeout(int msec);

  // Cancel all operations associated with the given descriptor. The do_cancel
  // function of the handler objects will be invoked. This function does not
  // acquire the dev_poll_reactor's mutex.
  BOOST_ASIO_DECL void cancel_ops_unlocked(socket_type descriptor,
      const boost::system::error_code& ec);

  // Add a pending event entry for the given descriptor.
  BOOST_ASIO_DECL ::pollfd& add_pending_event_change(int descriptor);

  // The scheduler implementation used to post completions.
  scheduler& scheduler_;

  // Mutex to protect access to internal data.
  boost::asio::detail::mutex mutex_;

  // The /dev/poll file descriptor.
  int dev_poll_fd_;

  // Vector of /dev/poll events waiting to be written to the descriptor.
  std::vector< ::pollfd> pending_event_changes_;

  // Hash map to associate a descriptor with a pending event change index.
  hash_map<int, std::size_t> pending_event_change_index_;

  // The interrupter is used to break a blocking DP_POLL operation.
  select_interrupter interrupter_;

  // The queues of read, write and except operations.
  reactor_op_queue<socket_type> op_queue_[max_ops];

  // The timer queues.
  timer_queue_set timer_queues_;

  // Whether the service has been shut down.
  bool shutdown_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/detail/impl/dev_poll_reactor.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/dev_poll_reactor.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_DEV_POLL)

#endif // BOOST_ASIO_DETAIL_DEV_POLL_REACTOR_HPP

/* dev_poll_reactor.hpp
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
*/