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
Y7peWYbrZbo/eew85YEY1xnu+77yKPwKjdPAvcn8CG+K8SrPQ17t875C6d9kPWeHw4ySms0VTuEP8c7hwX6bd3EO11NJ4Tnv48gfiZkq0Uo5Ynsd3F1wj6OGPY3rNkHdqUSQLUoG2cZAKzMU63fUy3tU5fsP56b8SBPXXp5rrmMOjn01UnMn3D6493AvxmC+SRmO3cfRg46fozt+AJ7keqiHEEesOaYqcns06pexOFY+XCVarLsxy+UUruaTaqKxjaE25ZcOEe43FM+rYqkcLS8uKaR44n7U9y/I+yGFwnRVqb6RcYrGuetVWtdlAPW2UGnU3u80vapMlLfJOrcfbcjWUK87pa0jpFqWu0ntKT6DKd+mqap8h6jGddXeISbhN79DpCu8Ld6hbcuQfQlfIc7GvonXsc34rvEothnfNe7ANmN/xVZsM75/bJLbBpG/SPoHeuelwLPJal6Kar6vcI15XgqVI1lf4pphG10z2e4h/7GN8t9HP2QDC0uKccIJzM9RN9Z82cHq3poJk8buLw6XRte4Gn6b5zC2GyrfKw6R/2KH4d6Q9dYbtD+Z/Dky/CCpCeH4Cn6stjRRCcC42V2mZ6tEfrZyk12woxfuhTLkxDVwO+AeVWLQPnRWtee0LLL7Ec/7n6rGe0Rk2Tve/HGI9+99qJ+yOmrPU6nugHC3U6xvFmCnF8FhFiLMbtKZW/dn7VnoS7a5jm0OIw3bk/HcciHEg6MhNRkPIeFWIT3x3+H9L/SCTQwmJsMfENI9JDUw3pkBQeIu8CWjZ8ARgA4Cl7tzD2cqrEKxJSggJCQwxNkBGsYhMAxxCotQZwB2h2N3sNvfe9Xu+k3+ip9JDderHfpkuP6zrItGfy3sdvGzrHZdjqsdMDq9OfXTUQoXyfWTdv7Jjk+xza5+0l+roEjt2XaxWTcQ9dNa6/pplF39tP44zs99BtU29/xW1ed5lbbV6O55o/bMt5Hm+bqXosHMc1nN3S5cgxnFy5fDRpY9P+bd6ufTbo2ynivucTV/rrjH1fL5y3ZzxZdHW88Vr3E1f644wjQ2hxn7Wz6H2Z+54lqa3DHmNH0Azz6ZJn11TWvfcB1sofNgiHN2mP9xxvE4zr5lsNIifl+gPam3jJ8shS0ug51iLcq8aJUDLM8n59A/bc4PhGl5GXzaJj9OWcQvSGguWsevrLSs8WuGcHLNkGtpvzA/f1XJEt2zqiEdc5qRDv11jeCyeC1tk+fxyf+6ThYaHcj/bJv0QXjELm0cJoLbbpPuCPa3XHcE5zPeY/w8hXMYrtnOzuY0XY405VmniWsO23KFcI3WHdjf8rrj6Yim6w7tPWpvnPcIKZymHnDBQmsnQOof6BPWmPYBh4m30zzg/XE8h572l5zP+3N4v17LcBr3D2Qpln9Spyfbpi9+vEV/Tw74B7LFuQ26edVdvQd+RxyX2Ubo5VjnxcwmtCA4XBep2/su+R9HTzTGe8DZ5BOH6yT14Q+R/0klE33hd8E1PE+VkAhBhPY9i+yeVrKpV4E1r+Txoo3Pv7KvfXYgacWjfyHZqBFBz1u9af+FWAk+XNcfyn29/Cz1MZ3jj0pf5OidcFInQbvGfK5sOlZHWo/lQZS9yfF4Tqa+vy6K8Xk3hm0q4zXtglyxTrAzy65fku1rYD/Fu07jflnfsU0E2zwXz32XTs8NUJs39avzsUhzZao4VkePR18u9TahXVknIXi16TnQ6/e/z/K6QF9Nghybsj3PomznSU0CKhc+ZftoAn/fxcHFz/mgW+gmBVqW7dxCHNTmGy+H6S/f0zq0ojWvVLt7YZIM01f2bbWnMBmq6R7gshxM+4erXIY5fIqx7qAyOl3uX6Zk474=
*/