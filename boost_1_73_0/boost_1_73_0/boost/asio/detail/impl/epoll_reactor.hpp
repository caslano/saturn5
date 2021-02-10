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
sXWH+3c8RcZyc1K2xloS8SyeQAVO1DUaHjIcpunYsKDQ35UMPXJVQg+ydPrjz5fJbWcaUEGsXa7R3FxlTX577wEmG+90HdjamDOxNylTvSfhOi/C7ssOKmUsqFIenPuxfEDNcmkG7ta7u2BAwwfOJ5EN9n8xt8V+Fzs8fv2++XvX+hyvVV260hsVTKDxQnUA4XTrkkssZl2Ytsnm1MpY3YlmbGtd2Uvks0m1JL1Q5Z2+r6wSVxrgZH/HTVaooWembdMbPPEiZaZOjUmpNPNvBBfSIL5fy4UWspz+AVBLAwQKAAAACAAtZ0pSzqveDgcBAACMAQAAJwAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2dsb2JvZmYuZFVUBQABtkgkYEWQwU7DMAyG73mKXzvTPcCucABp4jCYOEw7pKnbRMriErugCvHuOEWCQ6LEsb/vV45cpgOmzD2Po3uJXNWu7pHyfMBDEt9nwvl0hND7QiWQwJcB1ZfJjoukMuHre6tdru7eK01c1wPCUrPrus69xiTgWRMXyGfSEG3OXNBI2DVyk/eNM/sqVHd7vEUqWHkxqVrfH+DOtWLwRpoppHFtycQ6vCJwUZ/Khs2kSlUs2OUKc0ZeFNF/NIm939CTHV0q1jVX
*/