//
// detail/impl/epoll_reactor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IMPL_EPOLL_REACTOR_HPP
#define BOOST_ASIO_DETAIL_IMPL_EPOLL_REACTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#if defined(BOOST_ASIO_HAS_EPOLL)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Time_Traits>
void epoll_reactor::add_timer_queue(timer_queue<Time_Traits>& queue)
{
  do_add_timer_queue(queue);
}

template <typename Time_Traits>
void epoll_reactor::remove_timer_queue(timer_queue<Time_Traits>& queue)
{
  do_remove_timer_queue(queue);
}

template <typename Time_Traits>
void epoll_reactor::schedule_timer(timer_queue<Time_Traits>& queue,
    const typename Time_Traits::time_type& time,
    typename timer_queue<Time_Traits>::per_timer_data& timer, wait_op* op)
{
  mutex::scoped_lock lock(mutex_);

  if (shutdown_)
  {
    scheduler_.post_immediate_completion(op, false);
    return;
  }

  bool earliest = queue.enqueue_timer(time, timer, op);
  scheduler_.work_started();
  if (earliest)
    update_timeout();
}

template <typename Time_Traits>
std::size_t epoll_reactor::cancel_timer(timer_queue<Time_Traits>& queue,
    typename timer_queue<Time_Traits>::per_timer_data& timer,
    std::size_t max_cancelled)
{
  mutex::scoped_lock lock(mutex_);
  op_queue<operation> ops;
  std::size_t n = queue.cancel_timer(timer, ops, max_cancelled);
  lock.unlock();
  scheduler_.post_deferred_completions(ops);
  return n;
}

template <typename Time_Traits>
void epoll_reactor::move_timer(timer_queue<Time_Traits>& queue,
    typename timer_queue<Time_Traits>::per_timer_data& target,
    typename timer_queue<Time_Traits>::per_timer_data& source)
{
  mutex::scoped_lock lock(mutex_);
  op_queue<operation> ops;
  queue.cancel_timer(target, ops);
  queue.move_timer(target, source);
  lock.unlock();
  scheduler_.post_deferred_completions(ops);
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_EPOLL)

#endif // BOOST_ASIO_DETAIL_IMPL_EPOLL_REACTOR_HPP

/* epoll_reactor.hpp
fVOFOnJymo7Xs1P04jPbTE/+UKHy9o1xkXviTTdCYM1QW1VqwFSlIwPXHaZLQq5cun9FlVLUuzUuJiGYHjh/yZderarUl905w28uO0DzJq5dsMlWjTqXeXjm2P2b6eKQ875x19V+y70Ef5/FFeuBvxJanVyXpF4WOfZW5CTxx2M1dakS9ohmnNr8VPGHPXzRXoQ/3LcFBdFU8z9CsVdMJaONiACriBVZ72uFgSlxZbKB7AYip8W/zAc9hPOLWTUyH6NveTMKGRgf19qxXq0aH5CN4heh7Uezqm8F5qA40K7CKZpfyL7SfYnWiQa0TuwsD4wTZwNbovu22Ny5Z73Zxk3t10/x12ycksXa3Tguj/zhmzaxuMuLh4JXiJdcL9VoFAW+AQlfICVIwPchUb8py+4bIqw33CKx4jfcTWjz8SJBHM9GtJXaWcbuPzYq4W+mqqMiYx2vfHfykMhqa7GLFnbh1gMQz68iEM+jIrBj58tvsI2dF7+BeP77BuJ5rg7E81kdiOetekhn56d6EM9D9SCeb76DeF75Dn7s/NEA4nmiAXaz80Ejkb8awZsd302wlx3HTdCFHa/NIB6XzVDFjr8WEI+zFljEjqdWEI+bVpjMjo82EI+DHyDu7z9A3K9/gjPbf3/CS7af/gJxf2z/vf/Irq2Qf9FBBJ10Xu4JkheB/9dWvzmKImBi5rf2VBZBQ5nq5woVEWg8N1pw
*/