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
WlK10NcZtX/pgkRrlSrQHzs/o6pekYWNZM2JP1wFsyzO5ooXIfl3S8Vw46rgWFKO2mQmorfn0IO9Y3+A51fnd/HVKP2+F5ti9/2AowkLbrxKRPKSqLv15cMP2LV8c0mE9mjU/tbvHo2uBkuFmfaqjUgeTj5LdPZWw88TE6MyS1B/32KzOvhjNUi0HNKr10HxoV9N6+RroNwz7HO0GBp/hokclz5YAw6fMq9DOJKH2sUDCkk1sGXFeo3p2xA99OUGEyfXwuItsakHWROQfH5qKrnVwrDMjSW9j5VZWN+b1zMLasHGffWwbFdUvmfXbj1mHczqcd+ymobuyze9vnWpDn5uOzR+pzbqj6LTZSe21cEIh9dzj5QhefZ+RqpVDyf2pWZ+m4fGP4m0wz/f1MPck8/e5stOYmGuHDs7hQYwMpr2c5wnkvdX1cwDHg2w9YZU0PAJqL/eKhdvr2yAo0uVZH49RvbW/I7TqusbofWSbPPkr2j8GDGJLveuEQ5v73KUVUXzqahrX8umNEF22I17mytRfzoWNua5fxMcUGCFKC9D9Y1+t/QKxgP66dLtAaloPHJIyI47woNW53w5v0eI/+WO7yyredCrPttJ9iDSZ2LKxE1zm4E7EHO49/AMFlZ79pCZdTOUzPj1sMpgGgvDFuxofYru6Sfl10mg/pUHbvPrm6Ev9MTtKB4PVP2Wb1mE3IS8r2PeNPHg+om5
*/