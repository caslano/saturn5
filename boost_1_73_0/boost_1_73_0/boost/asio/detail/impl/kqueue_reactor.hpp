//
// detail/impl/kqueue_reactor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2005 Stefan Arentz (stefan at soze dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IMPL_KQUEUE_REACTOR_HPP
#define BOOST_ASIO_DETAIL_IMPL_KQUEUE_REACTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_KQUEUE)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Time_Traits>
void kqueue_reactor::add_timer_queue(timer_queue<Time_Traits>& queue)
{
  do_add_timer_queue(queue);
}

// Remove a timer queue from the reactor.
template <typename Time_Traits>
void kqueue_reactor::remove_timer_queue(timer_queue<Time_Traits>& queue)
{
  do_remove_timer_queue(queue);
}

template <typename Time_Traits>
void kqueue_reactor::schedule_timer(timer_queue<Time_Traits>& queue,
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
    interrupt();
}

template <typename Time_Traits>
std::size_t kqueue_reactor::cancel_timer(timer_queue<Time_Traits>& queue,
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
void kqueue_reactor::move_timer(timer_queue<Time_Traits>& queue,
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

#endif // defined(BOOST_ASIO_HAS_KQUEUE)

#endif // BOOST_ASIO_DETAIL_IMPL_KQUEUE_REACTOR_HPP

/* kqueue_reactor.hpp
UhrQr1tkJBXK4x7PrPQLtgH5R/pKKKy26s1nK0+2WwrX/FRU0C/bzAoxbTYywf6NB5P4ELgOWwregp5PTxC1z/N12LsfUEsDBAoAAAAIAC1nSlKkwb873gEAAEIDAAA5AAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvaGFwcHktZXllYmFsbHMtdGltZW91dC1tcy5kVVQFAAG2SCRgZVLbbtswDH3XVxB9no2srTMsGAYUaYoGaLeh6A/QFm0LlSVDopP570fJ8RCgL4Ztkofnwhfvuh30OI5zQTPVaG0s2AzkJy6GqB6ClH8MxloTqfFOx5/qmey4g3dpgtYHOP45baEmeSXgMBvXpV/36kFr0jv4Vlbfy43aI1Pnw7wDQXHUsPFOFUWhntNuWHeDiYAO0Eqv4X4A7pEBmWkYOQL7dTy91p77vEtGdOahUOtAMVLM1PSEtoiMzQf0PnL8AmOglkK4kNxCa0Lk3Ms9gZuGmgL4Vl0rLuHY5nKeuGyABp3zLMJXRqQTp7OwNm6hnXxMg07hlepVTZI6oKY0dUG//48uECMGcYRsCe9SzUTVFUrST0CirhamvWwXvITjHS3r5XuKpEulEkBA10mxhTh1nYzJgFTbycIJ7UTZeWsGI4USllAO
*/