//
// detail/impl/winrt_timer_scheduler.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IMPL_WINRT_TIMER_SCHEDULER_HPP
#define BOOST_ASIO_DETAIL_IMPL_WINRT_TIMER_SCHEDULER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Time_Traits>
void winrt_timer_scheduler::add_timer_queue(timer_queue<Time_Traits>& queue)
{
  do_add_timer_queue(queue);
}

// Remove a timer queue from the reactor.
template <typename Time_Traits>
void winrt_timer_scheduler::remove_timer_queue(timer_queue<Time_Traits>& queue)
{
  do_remove_timer_queue(queue);
}

template <typename Time_Traits>
void winrt_timer_scheduler::schedule_timer(timer_queue<Time_Traits>& queue,
    const typename Time_Traits::time_type& time,
    typename timer_queue<Time_Traits>::per_timer_data& timer, wait_op* op)
{
  boost::asio::detail::mutex::scoped_lock lock(mutex_);

  if (shutdown_)
  {
    scheduler_.post_immediate_completion(op, false);
    return;
  }

  bool earliest = queue.enqueue_timer(time, timer, op);
  scheduler_.work_started();
  if (earliest)
    event_.signal(lock);
}

template <typename Time_Traits>
std::size_t winrt_timer_scheduler::cancel_timer(timer_queue<Time_Traits>& queue,
    typename timer_queue<Time_Traits>::per_timer_data& timer,
    std::size_t max_cancelled)
{
  boost::asio::detail::mutex::scoped_lock lock(mutex_);
  op_queue<operation> ops;
  std::size_t n = queue.cancel_timer(timer, ops, max_cancelled);
  lock.unlock();
  scheduler_.post_deferred_completions(ops);
  return n;
}

template <typename Time_Traits>
void winrt_timer_scheduler::move_timer(timer_queue<Time_Traits>& queue,
    typename timer_queue<Time_Traits>::per_timer_data& to,
    typename timer_queue<Time_Traits>::per_timer_data& from)
{
  boost::asio::detail::mutex::scoped_lock lock(mutex_);
  op_queue<operation> ops;
  queue.cancel_timer(to, ops);
  queue.move_timer(to, from);
  lock.unlock();
  scheduler_.post_deferred_completions(ops);
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_IMPL_WINRT_TIMER_SCHEDULER_HPP

/* winrt_timer_scheduler.hpp
HTaE+fTr347qizc0urJjBmx/PjdTOx3Xn0f+ucMZsOFO9bFJT1QtqZAuS9o0MkH5xL3DpWZo/VP/edvpQiZ4eRTF9N+G8ueyc7Zl1yx4d3Ro3cpzSH4I6/DK6HQW7P3mG9LwEfFDjm1y7JMNVEi3Dx/vo/XLs7QPPzQbVpyoa9rhhdYXodLEBZ2EsMtgTv8Fq1F917aZ86cI4YVmVNTRVag/3ug7b/heIdyrZ3a8XILyF7lKd/0LIYyIMzk47T0q743czJJ2IfDPfWtUHYn6u0987DAekrei+1nr0Sg/ISt7nNyaA6ELjftuqUP93/GOydbHObAzoN3VKhvVR+QY7VJRDrxV7dx/qCOSn6ZY26gOyIWWPlcM1Xdqo/g0rrm65oJmj85De4aj9b54vGD9qVzYYn7+zsrRSD7gK2+KK8gFRlEt9s2HMag/PLv+sHMejCh+0iP0CBrP/2m++mu+Y9FOEkW1LyWwjC+Jgj6SGBZbIoH8RZJoKyuJejeLJbBsriQathdJoMt9STzlLIlCNUnkJxRK4I2tkigcLomenwokUP26JBoul0Ref0kUvsuXQJdrkrhitSQ2G0miT0OeBPKjJZHyl8TmWZLo000SPStzJbDsgSQW75TEKbMkMVJXEsNQ//wb9yVIoucJSXRcKYmRIIlhmpJIvRdKYHG8JFqESqK6lyR6TpVEwQBJPEVJYtmjbAnkr5NEvcGS
*/