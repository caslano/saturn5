//
// detail/winrt_timer_scheduler.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WINRT_TIMER_SCHEDULER_HPP
#define BOOST_ASIO_DETAIL_WINRT_TIMER_SCHEDULER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <cstddef>
#include <boost/asio/detail/event.hpp>
#include <boost/asio/detail/limits.hpp>
#include <boost/asio/detail/mutex.hpp>
#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/detail/thread.hpp>
#include <boost/asio/detail/timer_queue_base.hpp>
#include <boost/asio/detail/timer_queue_set.hpp>
#include <boost/asio/detail/wait_op.hpp>
#include <boost/asio/execution_context.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_io_context.hpp>
#else // defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/scheduler.hpp>
#endif // defined(BOOST_ASIO_HAS_IOCP)

#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/thread.hpp>
#endif // defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class winrt_timer_scheduler
  : public execution_context_service_base<winrt_timer_scheduler>
{
public:
  // Constructor.
  BOOST_ASIO_DECL winrt_timer_scheduler(execution_context& context);

  // Destructor.
  BOOST_ASIO_DECL ~winrt_timer_scheduler();

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void shutdown();

  // Recreate internal descriptors following a fork.
  BOOST_ASIO_DECL void notify_fork(execution_context::fork_event fork_ev);

  // Initialise the task. No effect as this class uses its own thread.
  BOOST_ASIO_DECL void init_task();

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
      typename timer_queue<Time_Traits>::per_timer_data& to,
      typename timer_queue<Time_Traits>::per_timer_data& from);

private:
  // Run the select loop in the thread.
  BOOST_ASIO_DECL void run_thread();

  // Entry point for the select loop thread.
  BOOST_ASIO_DECL static void call_run_thread(winrt_timer_scheduler* reactor);

  // Helper function to add a new timer queue.
  BOOST_ASIO_DECL void do_add_timer_queue(timer_queue_base& queue);

  // Helper function to remove a timer queue.
  BOOST_ASIO_DECL void do_remove_timer_queue(timer_queue_base& queue);

  // The scheduler implementation used to post completions.
#if defined(BOOST_ASIO_HAS_IOCP)
  typedef class win_iocp_io_context scheduler_impl;
#else
  typedef class scheduler scheduler_impl;
#endif
  scheduler_impl& scheduler_;

  // Mutex used to protect internal variables.
  boost::asio::detail::mutex mutex_;

  // Event used to wake up background thread.
  boost::asio::detail::event event_;

  // The timer queues.
  timer_queue_set timer_queues_;

  // The background thread that is waiting for timers to expire.
  boost::asio::detail::thread* thread_;

  // Does the background thread need to stop.
  bool stop_thread_;

  // Whether the service has been shut down.
  bool shutdown_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/detail/impl/winrt_timer_scheduler.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/winrt_timer_scheduler.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_WINRT_TIMER_SCHEDULER_HPP

/* winrt_timer_scheduler.hpp
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
*/