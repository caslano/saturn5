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
FT+QgSADWr0pZ4OKXxECdMpxrbq0keIEAsxfxDkCYi8XkHpdq8kInHQP6i0SubrFdAtkZQ2KYJnjmQPTONXCo2MKvqotHBvleHGSdGTH5tGkBuzAMZXIlh4JYnEK33XqpurPcq4RwHPKNgSPyevFbxxhz3MB4VXUlFc0rMtJuINkHp9QgoT0i0lrrD+ugrAXHqidv8UwRmUTbYBQXrN7LJXQXY9l2ItWZnP7CsQ2xI6tfksL1RSv3bJgHGiC9f+wDrndLPKCdECL2/qJ7wD0qNB6OYVvAX3n3AVLi27dWdA4hduBdl7ufyd4EUoTJAlDPk0YZ1f4iI7ip3ixAdlF219iF3CKQbOuIKVl1FX1CMYH6XbVt/9q4gWoyjV9RALLPdSwVu24swEL6JyeZCrbr5WNHp0qr8eRiar+9jIbC3W8nDiF1gL2WnoVG6qIN1O4ysFOUOOyZ9K03FbQkmAVAqy0jNMYINLnsjMsTzmotsGS+5cqfrNED+B1pv86HXsvXejSz0TbUz3T8RjUnMtXUIGp9rIh5SQtvNyPM/avdQ4Zn38zWitcHsTY0g==
*/