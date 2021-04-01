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
Lwqyz0Se8fRV27bWe4j8rQdwlK/kydm7/zYwM2XJVFBtTgsRnTFsZ695V3MIJUELx9Xqjb3UDAaMFJ941gkf1pE88ZbXkX+2KSa7aacDI8CEekAKectFMPE/6SJYFjY5jt3fk4mk/XWJNhiHmr4Ecc9iJg+nz5HdRTBokXv7Nks3fIaDc4IwherCG3FSBrQWUQid41I+ZVw2wEFJ96uoZDtE6l1Ps2Ds5QONPA1a2eX0CoJ6X8nZzqPMA933TvAvOoaFPpf67s3LGHp2HpzGz/knMZbkHRZH5YKKbo+4xZKXToYgBpEDnGeyLs33C5Xd+fYYVWDmaHKdVJ+5duDGXYiG8XcslA+nGy/9fB8ZtOnoyULUt4TVZYmR+qE/foThB2OWQ3Vm+0jtcaGUm9GB5gzvwjWtrKuz4y3L7iOv3+Q2BiGA7oJ5TcN8qKgivg51rdrhccNeZL7h47QTfSetKsa131/D6rag5tCiS5oj1xg8jLva4BlIzt7MiAJTRANdRoE8wJ4KPMWtSm35ey/Zpq5nNaRP86AF/DzyWp1r0aL2glYgEfNofbpioA==
*/