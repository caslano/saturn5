//
// detail/impl/select_reactor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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

#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_io_context.hpp>
#else // defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/scheduler.hpp>
#endif // defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

inline void select_reactor::post_immediate_completion(
    reactor_op* op, bool is_continuation)
{
  scheduler_.post_immediate_completion(op, is_continuation);
}

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
void select_reactor::cancel_timer_by_key(timer_queue<Time_Traits>& queue,
    typename timer_queue<Time_Traits>::per_timer_data* timer,
    void* cancellation_key)
{
  mutex::scoped_lock lock(mutex_);
  op_queue<operation> ops;
  queue.cancel_timer_by_key(timer, ops, cancellation_key);
  lock.unlock();
  scheduler_.post_deferred_completions(ops);
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
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
*/