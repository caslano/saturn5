//
// detail/select_reactor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SELECT_REACTOR_HPP
#define BOOST_ASIO_DETAIL_SELECT_REACTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP) \
  || (!defined(BOOST_ASIO_HAS_DEV_POLL) \
      && !defined(BOOST_ASIO_HAS_EPOLL) \
      && !defined(BOOST_ASIO_HAS_KQUEUE) \
      && !defined(BOOST_ASIO_WINDOWS_RUNTIME))

#include <cstddef>
#include <boost/asio/detail/fd_set_adapter.hpp>
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

#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/thread.hpp>
#endif // defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class select_reactor
  : public execution_context_service_base<select_reactor>
{
public:
#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
  enum op_types { read_op = 0, write_op = 1, except_op = 2,
    max_select_ops = 3, connect_op = 3, max_ops = 4 };
#else // defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
  enum op_types { read_op = 0, write_op = 1, except_op = 2,
    max_select_ops = 3, connect_op = 1, max_ops = 3 };
#endif // defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)

  // Per-descriptor data.
  struct per_descriptor_data
  {
  };

  // Constructor.
  BOOST_ASIO_DECL select_reactor(boost::asio::execution_context& ctx);

  // Destructor.
  BOOST_ASIO_DECL ~select_reactor();

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void shutdown();

  // Recreate internal descriptors following a fork.
  BOOST_ASIO_DECL void notify_fork(
      boost::asio::execution_context::fork_event fork_ev);

  // Initialise the task, but only if the reactor is not in its own thread.
  BOOST_ASIO_DECL void init_task();

  // Register a socket with the reactor. Returns 0 on success, system error
  // code on failure.
  BOOST_ASIO_DECL int register_descriptor(socket_type, per_descriptor_data&);

  // Register a descriptor with an associated single operation. Returns 0 on
  // success, system error code on failure.
  BOOST_ASIO_DECL int register_internal_descriptor(
      int op_type, socket_type descriptor,
      per_descriptor_data& descriptor_data, reactor_op* op);

  // Post a reactor operation for immediate completion.
  void post_immediate_completion(reactor_op* op, bool is_continuation)
  {
    scheduler_.post_immediate_completion(op, is_continuation);
  }

  // Start a new operation. The reactor operation will be performed when the
  // given descriptor is flagged as ready, or an error has occurred.
  BOOST_ASIO_DECL void start_op(int op_type, socket_type descriptor,
      per_descriptor_data&, reactor_op* op, bool is_continuation, bool);

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

  // Move descriptor registration from one descriptor_data object to another.
  BOOST_ASIO_DECL void move_descriptor(socket_type descriptor,
      per_descriptor_data& target_descriptor_data,
      per_descriptor_data& source_descriptor_data);

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

  // Run select once until interrupted or events are ready to be dispatched.
  BOOST_ASIO_DECL void run(long usec, op_queue<operation>& ops);

  // Interrupt the select loop.
  BOOST_ASIO_DECL void interrupt();

private:
#if defined(BOOST_ASIO_HAS_IOCP)
  // Run the select loop in the thread.
  BOOST_ASIO_DECL void run_thread();
#endif // defined(BOOST_ASIO_HAS_IOCP)

  // Helper function to add a new timer queue.
  BOOST_ASIO_DECL void do_add_timer_queue(timer_queue_base& queue);

  // Helper function to remove a timer queue.
  BOOST_ASIO_DECL void do_remove_timer_queue(timer_queue_base& queue);

  // Get the timeout value for the select call.
  BOOST_ASIO_DECL timeval* get_timeout(long usec, timeval& tv);

  // Cancel all operations associated with the given descriptor. This function
  // does not acquire the select_reactor's mutex.
  BOOST_ASIO_DECL void cancel_ops_unlocked(socket_type descriptor,
      const boost::system::error_code& ec);

  // The scheduler implementation used to post completions.
# if defined(BOOST_ASIO_HAS_IOCP)
  typedef class win_iocp_io_context scheduler_type;
# else // defined(BOOST_ASIO_HAS_IOCP)
  typedef class scheduler scheduler_type;
# endif // defined(BOOST_ASIO_HAS_IOCP)
  scheduler_type& scheduler_;

  // Mutex to protect access to internal data.
  boost::asio::detail::mutex mutex_;

  // The interrupter is used to break a blocking select call.
  select_interrupter interrupter_;

  // The queues of read, write and except operations.
  reactor_op_queue<socket_type> op_queue_[max_ops];

  // The file descriptor sets to be passed to the select system call.
  fd_set_adapter fd_sets_[max_select_ops];

  // The timer queues.
  timer_queue_set timer_queues_;

#if defined(BOOST_ASIO_HAS_IOCP)
  // Helper class to run the reactor loop in a thread.
  class thread_function;
  friend class thread_function;

  // Does the reactor loop thread need to stop.
  bool stop_thread_;

  // The thread that is running the reactor loop.
  boost::asio::detail::thread* thread_;
#endif // defined(BOOST_ASIO_HAS_IOCP)

  // Whether the service has been shut down.
  bool shutdown_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/detail/impl/select_reactor.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/select_reactor.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_IOCP)
       //   || (!defined(BOOST_ASIO_HAS_DEV_POLL)
       //       && !defined(BOOST_ASIO_HAS_EPOLL)
       //       && !defined(BOOST_ASIO_HAS_KQUEUE)
       //       && !defined(BOOST_ASIO_WINDOWS_RUNTIME))

#endif // BOOST_ASIO_DETAIL_SELECT_REACTOR_HPP

/* select_reactor.hpp
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
*/