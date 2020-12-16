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
1V/nHyckf+/rcB1Whu6Cunfo1GpDwmYHNBO8QPJcqD5urHs/jCWgi2wy6ypX2nzFvC08pRq2ZM4XvwZHaE+nyNPPRoo9g5dTk9digCfAto/yD6VBNMKPHRvWGbp7bZspXwl8+zLh6/XBTm47JjMJn0s43I975WLXcjTj/xhBQ1tJ4yT3uQHMJW4MNBZ6Mg1KYG6qfqNM+/T57j/Y9oV5bkmbkrG/RuqA/lAYknC9Ces7ivahFH1xmKx9lUea9KFa04eYLK+O3o96RvIk/EO0X1ny5xo7jo9KuGOQnQblz9Wwxd81yJ6K8udr2PAH9jPpTw45wi65EttaW8g2Jn9ZeLpo2MjIHDqHMWg7L115Mt8dZtrZaznx+WQ4G/VvtwE8UG3JPwFlQvdDWyPrSSWmfnX1obxy48ZNqzaUX7u8asUaz/tLhuhuyW0IjeJNszg01NjMeUGuL+LqRI8vQ61jlc3mXrquJOFdhDuFpkPudYwMa11J+HaHBvH/XEjbgN4vy2PDVvxvzmuxvdZR15UISR6tNrVc2v17V62zjZHTRaanhrF2JOFuMgZ1hr+GftFzFPWcsgmDr6kpI/nf1waY8u+GPx1+7BTe4hp/jA2Wp4k/v5/iGc5j3T4Vi7zrJOYdsEntsH8+iXQVbyfh+nmmXfBarm1iY/D7LPxqO0nt10l4a9J1/O+ul0iRvyLxa5KWMNrYbc+l67jxy/myhsgTb7Kxo/kLkalKkj7dUm9iM9aycdxHZCYmpdK2bg7da+yEDp5v1aeRY5sjZPy7Ncl9r0m6KnQO12S9i592B9MuNH3GsnR91r4q4VVJS2ldnuexttn9kna1sX/cLDKX8U40IPgZLTL0A9WrWcJT9Rls3WNJ0rBQL+Z/3+QbvlnaZzTftnu9Kby9TB/qLvealjSAt/7vk68emq8cud7frClwH7Z9GIBs67M7hafEJx+pko9Q0lSxwZtFOXytP8+9SJtPHoV/UKzNzY1ig1dlGpF5KiLTtSg1mb89z2rlO07ceLE5VvMds1bp4smkXV8gtpFq6jw2UpWnZEDLuwS5y4zY8+tcHD1/4QHmXSLP711iOOHOhJ9Bh8mjW+hraayrpkfeC/QdIY53AbXV45nXlZnnw/sc6wuHBnrfs9/P2N6wwHmujnmp9LUHxznnGvAFn6cz8YHn6Yg//fN0D447/fN0h87z6v0B9G526617R9Zc66ZC1xw2hv7NMfRvPgP9bypMXH9rfnVwkFf/m7lf1kKn/jrHIn+6nmh0V95g3YmPqjvxp6/77RNPR/eW59bhwS037EWiAxV3cL+86aI7S1zltg2bwOeW8mebvZHFEm4OvcD/AeuvKjPZPAeukfCh0KPkMHBN1sgVmOfOGgm/yDfCKVyz3pVaHrVSBjpHqxC+V0JP6LvnpeZeeYHj/osS38U8j49IuJz3tSxjU7ZRrpXwZnOBew5n3p++Ljw7sbbeXXjezpS0Is9deVdmHBPb+odoi7UECiJjbkp2akfCVpv4Q46Ozcr3AHyFEb60awzPop5OnkPw7M2Fp8sVhucLyjNIeVIH6zMmpebmyEMmpSjY/r7mEfv/+ozpVlOXmtwzFPQ+tiaDmSl0H+05X+0WVsQYs2t83sdu9VlHr/Wso6t9UvPuZm8DPaWMKXeuS7k7+sEDQ1w29HQ9snmavR/ocmRwP1D+Ec71SG1LIWkDA037h9exrnebrtcUJLiH10PnLLpW6Ximbcn2jm0nSaB0ofN8MWO7714ZfMHniiX+9M8Vd4zzjHTxUK8O/0CgxqODPp8CznjUxNCl5gx0IS1/XVzPmtRhXl0+FJk/unTRZ43vmmZ9DD3qz0CP9YF14lznyBs=
*/