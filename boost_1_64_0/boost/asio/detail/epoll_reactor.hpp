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
Y6JwlYt/P9uSwItcJjdrnouBznUz8J1czQpHriCvso5u50QkR5Tbzgu7YBqU8rhc+yRe6nKdtJvfW+eLeDpHfvc6mqqzKlqLVrNYruLmNXZAZqZOvu/ERleUq6Y1D9zwqGl3PjgBUtPWvIAJu3tQ5/jKsd7l4XXuhFvWuyK+FK4JR46NZYLX4D54ehncJlHOprJlsbHFSbGchbieXd2ElwYSbk69WAOLiq/L4JLOUuwEOwo3loKl+cLwklEnUbOWLwkrTH/B0M4DG1QsLn6tCy9BdRQEOZIO3YJE98mVBMXJSn5t2Pi6miW/VpkrcE0Q/4zFVDQnXZFLu6OWHX4MfQEXqYYwLQs4qWVoQytgGLaK61W1rfU4b0cZznOdZTjwZYXwtQyMfvEbHHqh2dCkJtYmjn0iRulDW4Gu2PAIuPXcezMpxLhYOHQHGyNRz3BGn2IeZyFt6WyqMpNqhTsPBo/bIIkbG/wszlhhLzHSiQAdCrWH5W0KBrcow87oH05eFVzNTFuBB2SSs3gpNYZR08X/sXcVsdIUQRg44BDCBQkHjhxxuWGLBIeHyyK7wMIP+3izizuB4BI0QIImENzdPbi7c+GAhoRw5NuuqvmmunqAK8l0/vfvfF9191TrdPX0dE8nh1smk53fKK2k8BTU9yymymtw8LDvEifzp4c04HS+QSAh8fbkqQDJqILObzPa/g5bb7VOutzA9XZAWWcHSkz3flr+GJj+bttsZjEhbSkBGcR2MjlTpSwgCzJD6IIWHTZeqMkjB4c24z7Wd8tkJWYv2Ki/2dzcruk9HOpSk9oDG5tttTfJLbfd2l6KOyb4QA1RAoMR7FLIMKQQyBFZqNmyN6zgZUhPI3QgfQx74GXkzj0GJ4ewGcOAtqcbtgXUfd102XibmDcoCUft4XjLXXuY9ejzDW1gD9MCDxLEH7hyxKgbQqZy7sm7bM+MMh+Ip0nsSg0DTRWrKEPEkYyxU83IYrKqQeeFGwX+lqViRpOWx/jo4BQ93sSk05kpXkfFvvwhMB7T6xN0kHxIO2l1FGI75KD5IJlO6FsemaND8ZrXswuLGmhhiM8ZRrhViUsTahTwfVjGDXn/IFoQIimTDjtSuhF3nVpm4SGTWstZZyr7TTUImXkkTnOPhPIJohD2uBMkOS6aUOnKhFPN0+ZzEOhQ3q5RL/iSECYEKUZLzl7sHnQ0sgXKITbKQhZSFPMKbF7+lnTmn34li495FVc24pOF+mRjHnBXQBJWQmR8za1cKmJ8rMbJW+MyVBRWMleIclAcU+4sTAGTMbZRxb+51LCFtNfLuYXI3iYKkJ+BZq8C3oaK6UWfUK6SOWMAyOqEwnkEjduoUJaqlcc0C8hWta90iQc1dOEHKTvjSaCnbEUaSYxkSqCcLM/8IUaYJqLnXXbfbHsGyDgEIpMFjOvUI48ISiwjgRm5885YjlL7JMU4yUVfEteuO+21t0xzJCXTFz67bbvTjhJHuxjRtQsZs9zSIiOD8A6nIGnfYH11JAC1JV3ImxC5HB6LBimXh44WyclWAlFf0iahet5PInXFPDwKxCeBi/SqGk4H42bM1SFQ82i9xmdXeqWx6skQJPNb6XKDdC3TDXrfLdZ138oAZ5/KgEFDqq/dVzPA7nqch7Q9FnC9/uyv/oQG15RtizmQLfH1Ga/0+wvi9Cwh5Ncb5PTtlpvpSQ8PzyAeTviIDxL00N9ps97O/fSCTtpBIKM/qSjgZj3AOlZbhNlttxAZuCwuMHlUe22y3jq2Xc7w+JpyJ8U5wWyNAVbUgJBzp+ViEV5pY8iDEjo0I45OmOfXETFmt58gMK/q1DiFSHgNdQ3Qgm0sQU7qL7EctkkPjDU=
*/