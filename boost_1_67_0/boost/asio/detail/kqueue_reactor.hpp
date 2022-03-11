//
// detail/kqueue_reactor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2005 Stefan Arentz (stefan at soze dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_KQUEUE_REACTOR_HPP
#define BOOST_ASIO_DETAIL_KQUEUE_REACTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_KQUEUE)

#include <cstddef>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <boost/asio/detail/limits.hpp>
#include <boost/asio/detail/mutex.hpp>
#include <boost/asio/detail/object_pool.hpp>
#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/detail/reactor_op.hpp>
#include <boost/asio/detail/select_interrupter.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/timer_queue_base.hpp>
#include <boost/asio/detail/timer_queue_set.hpp>
#include <boost/asio/detail/wait_op.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>

// Older versions of Mac OS X may not define EV_OOBAND.
#if !defined(EV_OOBAND)
# define EV_OOBAND EV_FLAG1
#endif // !defined(EV_OOBAND)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class scheduler;

class kqueue_reactor
  : public execution_context_service_base<kqueue_reactor>
{
private:
  // The mutex type used by this reactor.
  typedef conditionally_enabled_mutex mutex;

public:
  enum op_types { read_op = 0, write_op = 1,
    connect_op = 1, except_op = 2, max_ops = 3 };

  // Per-descriptor queues.
  struct descriptor_state
  {
    descriptor_state(bool locking) : mutex_(locking) {}

    friend class kqueue_reactor;
    friend class object_pool_access;

    descriptor_state* next_;
    descriptor_state* prev_;

    mutex mutex_;
    int descriptor_;
    int num_kevents_; // 1 == read only, 2 == read and write
    op_queue<reactor_op> op_queue_[max_ops];
    bool shutdown_;
  };

  // Per-descriptor data.
  typedef descriptor_state* per_descriptor_data;

  // Constructor.
  BOOST_ASIO_DECL kqueue_reactor(boost::asio::execution_context& ctx);

  // Destructor.
  BOOST_ASIO_DECL ~kqueue_reactor();

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

  // Run the kqueue loop.
  BOOST_ASIO_DECL void run(long usec, op_queue<operation>& ops);

  // Interrupt the kqueue loop.
  BOOST_ASIO_DECL void interrupt();

private:
  // Create the kqueue file descriptor. Throws an exception if the descriptor
  // cannot be created.
  BOOST_ASIO_DECL static int do_kqueue_create();

  // Allocate a new descriptor state object.
  BOOST_ASIO_DECL descriptor_state* allocate_descriptor_state();

  // Free an existing descriptor state object.
  BOOST_ASIO_DECL void free_descriptor_state(descriptor_state* s);

  // Helper function to add a new timer queue.
  BOOST_ASIO_DECL void do_add_timer_queue(timer_queue_base& queue);

  // Helper function to remove a timer queue.
  BOOST_ASIO_DECL void do_remove_timer_queue(timer_queue_base& queue);

  // Get the timeout value for the kevent call.
  BOOST_ASIO_DECL timespec* get_timeout(long usec, timespec& ts);

  // The scheduler used to post completions.
  scheduler& scheduler_;

  // Mutex to protect access to internal data.
  mutex mutex_;

  // The kqueue file descriptor.
  int kqueue_fd_;

  // The interrupter is used to break a blocking kevent call.
  select_interrupter interrupter_;

  // The timer queues.
  timer_queue_set timer_queues_;

  // Whether the service has been shut down.
  bool shutdown_;

  // Mutex to protect access to the registered descriptors.
  mutex registered_descriptors_mutex_;

  // Keep track of all registered descriptors.
  object_pool<descriptor_state> registered_descriptors_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/detail/impl/kqueue_reactor.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/kqueue_reactor.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_KQUEUE)

#endif // BOOST_ASIO_DETAIL_KQUEUE_REACTOR_HPP

/* kqueue_reactor.hpp
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
*/