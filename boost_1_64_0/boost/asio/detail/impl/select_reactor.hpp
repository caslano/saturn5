//
// detail/impl/select_reactor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IMPL_SELECT_REACTOR_HPP
#define BOOST_ASIO_DETAIL_IMPL_SELECT_REACTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP) \
  || (!defined(BOOST_ASIO_HAS_DEV_POLL) \
      && !defined(BOOST_ASIO_HAS_EPOLL) \
      && !defined(BOOST_ASIO_HAS_KQUEUE) \
      && !defined(BOOST_ASIO_WINDOWS_RUNTIME))

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Time_Traits>
void select_reactor::add_timer_queue(timer_queue<Time_Traits>& queue)
{
  do_add_timer_queue(queue);
}

// Remove a timer queue from the reactor.
template <typename Time_Traits>
void select_reactor::remove_timer_queue(timer_queue<Time_Traits>& queue)
{
  do_remove_timer_queue(queue);
}

template <typename Time_Traits>
void select_reactor::schedule_timer(timer_queue<Time_Traits>& queue,
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
std::size_t select_reactor::cancel_timer(timer_queue<Time_Traits>& queue,
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
void select_reactor::move_timer(timer_queue<Time_Traits>& queue,
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

#endif // defined(BOOST_ASIO_HAS_IOCP)
       //   || (!defined(BOOST_ASIO_HAS_DEV_POLL)
       //       && !defined(BOOST_ASIO_HAS_EPOLL)
       //       && !defined(BOOST_ASIO_HAS_KQUEUE)
       //       && !defined(BOOST_ASIO_WINDOWS_RUNTIME))

#endif // BOOST_ASIO_DETAIL_IMPL_SELECT_REACTOR_HPP

/* select_reactor.hpp
YDF8TX75svlkKHKer4c/IZsh85358vpkqE/xtxmSNs0nXwn6ZGg+FmwPcqDHTwA4iXrzSzcxnwzkwZWWj03+d3FerHSa+YbOmZ62iU6TnGUPf/B3dCY+8Ds64k//O7pOkxL/js7S/6iP/kvRv2aa+a7Dq7+37cEf4xuVaaf/bUdRzO9tzhVdHj7He+5sfF/a8TTr3NmMxZfkly9ZWjrbcbY+p6/nzJnKZOg46znPSPzpn2ckPc+ZM9JwnGc8Lr52z/6Zs0R9Gfy3nyHzPxMWdLYs+CzUc3LmbO853770luce+lb5nvuvf/q7kwuDzoolfubsf/VsWeQMmfYRecfYnyQ++OWdZCc4OCTvFeZv9UWr70Xyrkec0xftMN2DHglCEh6t4QJwNDgTzAUXgWPBcjAfXAuO1z3nCWANeCF4KzgR/Bg4ye77e2rw2ZEh9j2dqcF7g4NtfGlRzo6cb/igafHdrzROvpo4+WSc0zF1v4uPeqtpSG7Zq6nfmRzTn+2Z+Jw4E3+1Xl+1been9t7pbeef9nR900b3SRufP9pgP7TvjA9a9h3Ybzg9v7Mtewyn52+21dfsmfmZjXffoHbC6fnY8PqXjd+37EH65klo4J3IQRXQLdDXoAN3tq+bt//af+2/9l/7r/3X/mv/tf/af+2/9l/7r/333/p7Z/z/LV/bFv7/Ivv6B3K5h+UvRb8tWqXrk6XQMNbWw9myj3PJ7CWLZ81gD2dx6YJ55Rsr37tO96Sm93Ps0yr/cLPX/hkJFxK2bNyFr1m1Vfd0DH+22Uu/Q8IzhP+w7Hddu9JuD7dW4i+UcKmRzzI2ui7tTSnovlBRjH2uUpD8y95wOuEyYxdP8ijXKrhGPrhGPlz7eKzPy2+B2veeDGVTZs0+ZabWALXMHPt4yj/IlFmPoR67gEb/bhI3TMvPkh1g1x/bgLH9e6mvJdV/ua9dwDmqZ5nuSS/VtlEMjUDP0qGiZ+mCWYsnlc9bvPjy2ZeVz7ikuHzx7MvmYdhpZeV7V22s0v2+XKlLcTJjdNkq8llaDtb9RtrqXg4ZGF2Jd/jT2yzhHOHP6mTaiinHjRKfp23Fks8W/k2dzH6waXthiS+Q8KXC72xbTcM575KA77RcaTeis1wrMW1J9DI2h8m71b5MOyR/vvZnD+k+/W1aF9XQSOqiQfJq+cIxhS+61vmU/e+Fv8yUfUOMsm9wlf2rEq4ILPtXJH6NKfuGGGXfJPFhLXuLH7uplH2y+oH4foLlX9eG5W/1+Ubdu5+ovntGQKMp/5phzvJfU1UVLl93deV6bf9jxkk/XlG1xex3q0w/UwZ3SjiTsGUvOizGA606+4zEZ7Tu72tY26eUT+aw2Od9rD1x8oSOkie5VmBsQ0u6pt3ZD6RsgAbrWDATgUaX3vpo8PPvp7z5En4X4aThYmM96Nmg/GONn5W3JDzT+2zQNnlc4qdrm7Pkh5ryeSY3/mdDBUj+zbNhjc+zIRzl2dCs5bUOyoYWQ2NoJxXDveVVTg0ElJny55kyqLWV2ad7RXhF2JQZ/I5++mEJT3KUQd8Eng9aBqb/kCZhSdPpF6qr9xmxkLbU3KqvWPrTgUny38dnXOo3wvFMQD76uNTs0jdjRPRnQi/izTPByAePS2nwm2eC8DufCQdzExuT+rThmGSV/dFu3rIfF2lrknfL59OljmfCqxO9Zf9RV9kjH1z2Eu9qazHK/mZn2SMfvexrnGUPv7Psn0+w7F+d2PZln6l+9q7Wsr8YemkSY4+z7B3j4vo+jj4Or/Od+YSEJwaNi/A735n/KuFpge/MzRI/vnVcdJXjLxIYF0vB9X1O/525s/q/K9V35iIov5Bwjqu8dFwMKDM=
*/