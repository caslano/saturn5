//
// detail/impl/dev_poll_reactor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IMPL_DEV_POLL_REACTOR_HPP
#define BOOST_ASIO_DETAIL_IMPL_DEV_POLL_REACTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_DEV_POLL)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Time_Traits>
void dev_poll_reactor::add_timer_queue(timer_queue<Time_Traits>& queue)
{
  do_add_timer_queue(queue);
}

template <typename Time_Traits>
void dev_poll_reactor::remove_timer_queue(timer_queue<Time_Traits>& queue)
{
  do_remove_timer_queue(queue);
}

template <typename Time_Traits>
void dev_poll_reactor::schedule_timer(timer_queue<Time_Traits>& queue,
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
    interrupter_.interrupt();
}

template <typename Time_Traits>
std::size_t dev_poll_reactor::cancel_timer(timer_queue<Time_Traits>& queue,
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
void dev_poll_reactor::move_timer(timer_queue<Time_Traits>& queue,
    typename timer_queue<Time_Traits>::per_timer_data& target,
    typename timer_queue<Time_Traits>::per_timer_data& source)
{
  boost::asio::detail::mutex::scoped_lock lock(mutex_);
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

#endif // defined(BOOST_ASIO_HAS_DEV_POLL)

#endif // BOOST_ASIO_DETAIL_IMPL_DEV_POLL_REACTOR_HPP

/* dev_poll_reactor.hpp
8KiCl4wcpTTY8EyGfxh9zejcpgctcpRCza24cKWrtK/NuXlDzOSp4KKf3eVHHqVfDnw8avI6eUrJXqeifGkIPch+ymuF2/LUSMGyIdUjjtFT+t7VXlcjT3UKEoUGaIbRAXPHhO/U70h1fOVF7RWF0vr95vpZuHak1s8NU5l5MJTOYOffjtSeyVl7ooZcpYf2XE4/eNuRuq2yTu+I3mXay/lT7cY+CtS1692C+y0Jo1Pcred9dFag9lzoPenOhEv0HpmPXloXFai5HoW3yz8up11nZY+qr1CghO7tzy78OkFrZs0I3W+gSL2VSdHS6nOc/nRkwpmSFYrUow+iuGFPD9KlYYOtq+4oUhOc6538G7fRozZrh977pkjRhh3PRrtcpt8lZYabmytRt1xb9HJqj9M2s95c8NuhRA3MOjzkx/31dIjost/hRCXq+dDTjmZrztDLqhZtc+vcieKfijy9feBxeqGB1QPZuZ2oh/O91gasDKCZn1vmrj7fidprmn5kc88g+m7e/NALtZ2oE7rGr9z0L9Gt2jaRl0yVqXvyxyOGalykJy1uq9u0S5nKfO3cqajdm86Nmx7SO0OZetj5vsm9tV702dm7X5/p0Zm646SUc6gsgJ6e4zD0m3tnakWPIx5Gq93plSFfX+k97Uw9DH07SsnzKL1tv8I0YwUV6rqC5bXdl73pvVfaXnV3VKHuHIkrsJ0fTO8eUSpb
*/