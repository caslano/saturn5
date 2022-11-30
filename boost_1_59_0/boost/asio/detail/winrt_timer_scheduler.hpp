//
// detail/winrt_timer_scheduler.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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