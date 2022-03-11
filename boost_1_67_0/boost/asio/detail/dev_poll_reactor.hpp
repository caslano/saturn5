//
// detail/dev_poll_reactor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
  : public execution_context_service_base<dev_poll_reactor>
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
  void post_immediate_completion(reactor_op* op, bool is_continuation)
  {
    scheduler_.post_immediate_completion(op, is_continuation);
  }

  // Start a new operation. The reactor operation will be performed when the
  // given descriptor is flagged as ready, or an error has occurred.
  BOOST_ASIO_DECL void start_op(int op_type, socket_type descriptor,
      per_descriptor_data&, reactor_op* op,
      bool is_continuation, bool allow_speculative);

  // Cancel all operations associated with the given descriptor. The
  // handlers associated with the descriptor will be invoked with the
  // operation_aborted error.
  BOOST_ASIO_DECL void cancel_ops(socket_type descriptor, per_descriptor_data&);

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