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
epfv4T1gGJ+xkOWHuIy4NVyvAndyrR6y/BEfw3/qwbC/X+KTXE/9XJBvYug6/LZCKyHLR/EO/t4NLePvfWAJ1/O4x1qweo/Xb/FheCzfxWkbnP6LJxBeCK2FaiNx0DHI7dd44Eanb+NiwktI0+njGOT6rYQPgichu6/jtCp840Jun8dFVfCCFaDb93FNlb//4/oqrw/kk1XEkSfxhfw39KEs0jZxL+gU14oiCH8FaPlIrudvy0dyI3/fi0wD1Lyp1Wdy5mbKF7L8Ji/h77XgIfhqwB2b/X0n7yAvdv/JR+F/gGuN8B+FUvZS1sRlXt/qVzmPvy3fyr2Jt/wr5/H3GuJS8+EDI76Wd4E5hBtAP3/LR693+lwu4R4HSN/pe9nrdzl3C+nCtxa8BbL7YE47iS/hX3N/rpdx/QhYwX0tv8wnI7JgzlZ4i5Ef7/THvCuC8Fv+mLfv9ffJXLY10C+z8clcDY/ll7lub7Bv5v3wWf6Zj/B36ueTxU9z5g3IQrlzIK4tucHfb/OWG/x9Nxch4/bfXMG10Fzyg0wt4QZwIOEarh/l7wL+Tt1GviHLt3PJNvjB3fCs3eb181zPtZMT0AM8TPgYmFZNHvdynXAef9t9P5cQLgILaG/havSAr3cJZVdtfEGLj/V9hKdw/TBo9wudeqPTN3Qx4YfJWxOUsgtf6dASaAu0A3oAOggdh9K+kBzKg0qhtdB2qB7aDx2BQl9MDg2FSqC10HaoHjoIHYd6fwl5aCG0BdoNNUCHoVNQZh0+waFlUA20G9oPHYPS7kIWKoXCUC1UDx2AjkKpXyYeWgJVQTuhh6HD0Cko8yvoBlVA26F90BEotBu/2NAUqAyqhnZBDdARqPNXk0O5UCkUhmqheqgRaoZS97T7z27/tf/af/9ZvxRo3dn2/8d/Eevs4gKwDXwAPpkbMmfTl3VQRZK4C/AG9Iss5shDmCOoje6IMf7K1ZUrOKFdHsmHZZf8iNMuucoMCPXXc0ULJHwk1JP/H4OehXogV9nLnMWX78oWGNlJ7At312tJoVK5NpQrXd3fq0kavcHZwvPbUDqa/Qg6CHU1vJWhDPgiir4sfDPYb+7GWapu8M+MnEXSNJokDStvIfImZ5PU5n6J8OTC0Y37XdkzUuefyWQvJ52z/aNZu+4Z++xTDz37dMRmO72AMOlZ3wwYHvLOtUpzDqquDc9B+Z93aj+/FOv80jo5v9T90KXHr66Y/KkLnp65YkbKb65sP79knV96XcpN+7GOJzXQ+bImpHsHXOoF9gIHgH3ALDADHAJeDI7RMwfj9czBJD1bMEXPjCzTM0rlYA64XM9GrNazEWvAoeC14DBwPTgKrAJHg5v1Ph8Bx4PbwQJwp56J+CY4GXxaz8L8HFwIPqv5ewmcCb6s14/o9T/rGZG/6vU39HpRcpxrJo71EsdaiVkbqYJ0PcRvHSRo/cOseSyDWOdgjcOzvqFrG/Z1Dff6hWPtwr1mwXqFfZ3Cuz5xEnKvS3jXJLzrEbIOEaEis96gaw1mbcGsKayFaiCfdQTHGsIxUNcKdJ3ArBGwNgBF5t6gdz3AsRYQcw3APudnnm/m98eggHm9zun95vOx5/I6jw+aw5v5ey7knaP7zs/dc3OZl9eCA8ECyJp/10HuOfdJ8HAEIfvcugjqXWLm0cyf7XNn57w5p33e1/5r/7X/2n/tv//A3zs1/98Yvqayreb/P7LN/5s7mHM5oUxwGHh+IXvUg3iPd/uzv3rihPKVq1asX7mqxYaRfEu1sWqD+bZI5Xhjz9A1gKclnJ50g23+XxVy+l7sFbLk+pt5/VMSfivUhV3ijcy7D0DpLb73+EVKg5yQcIb66Ot5foQ=
*/