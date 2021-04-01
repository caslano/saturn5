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
Ond4rJ1936IQ7h4Ncp0adP2KwiIHcKKhNI5XMv9CaMg1Mzmq5cyV2xAGWfjzwf9mvZZHyi/9kQ3TOsuk4drTxP0VKsXqKbb8cB9oH2h0aLdb+oOzhMe1F1BdgiTKHKcJ4CYf6tQmjmuIAEJvLs65Dvz1drZqD/vhJ4rUmPLX1NcnjhjVrW6Led6XoZ89wbPlWyf67mR/f56XAHKnKQztTJjxqnpZC69SdlInFAENh9D5ytv9iiwNdbXpmMuEAR8BRATeZGwfI4iSIiZaxRKjmgICQM1rXxl7rDBDemm9CWvyMonk0nuZXDtryPeUH8gPRWdXFGctB4o0uEaWZ6P/qmXMtKC8SHXLZkZ82hms0rIoIG1ZP5Zie8nft7jpTt5sCZjQi9+67c9OptAEY4t5Dc5SVqdV0rG/3M7ntafTNz9al8gXFDqemB4FDgj1dUeYLJy8K8Y3egPHLq2eA8NhNy/ACovadEIB/5yw9acndkiSkAOVI9ZhYdrxsLcGuPMiENbwlFBJ4ucxkg8pG6LeoG5B4Ek/LtSFbJ+rszaBRBHjyt1yOYDo2CeN7Q==
*/