//
// detail/kqueue_reactor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
  : public execution_context_service_base<kqueue_reactor>,
    public scheduler_task
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