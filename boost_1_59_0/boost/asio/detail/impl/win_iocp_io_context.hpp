//
// detail/impl/win_iocp_io_context.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IMPL_WIN_IOCP_IO_CONTEXT_HPP
#define BOOST_ASIO_DETAIL_IMPL_WIN_IOCP_IO_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/completion_handler.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/memory.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Time_Traits>
void win_iocp_io_context::add_timer_queue(
    timer_queue<Time_Traits>& queue)
{
  do_add_timer_queue(queue);
}

template <typename Time_Traits>
void win_iocp_io_context::remove_timer_queue(
    timer_queue<Time_Traits>& queue)
{
  do_remove_timer_queue(queue);
}

template <typename Time_Traits>
void win_iocp_io_context::schedule_timer(timer_queue<Time_Traits>& queue,
    const typename Time_Traits::time_type& time,
    typename timer_queue<Time_Traits>::per_timer_data& timer, wait_op* op)
{
  // If the service has been shut down we silently discard the timer.
  if (::InterlockedExchangeAdd(&shutdown_, 0) != 0)
  {
    post_immediate_completion(op, false);
    return;
  }

  mutex::scoped_lock lock(dispatch_mutex_);

  bool earliest = queue.enqueue_timer(time, timer, op);
  work_started();
  if (earliest)
    update_timeout();
}

template <typename Time_Traits>
std::size_t win_iocp_io_context::cancel_timer(timer_queue<Time_Traits>& queue,
    typename timer_queue<Time_Traits>::per_timer_data& timer,
    std::size_t max_cancelled)
{
  // If the service has been shut down we silently ignore the cancellation.
  if (::InterlockedExchangeAdd(&shutdown_, 0) != 0)
    return 0;

  mutex::scoped_lock lock(dispatch_mutex_);
  op_queue<win_iocp_operation> ops;
  std::size_t n = queue.cancel_timer(timer, ops, max_cancelled);
  lock.unlock();
  post_deferred_completions(ops);
  return n;
}

template <typename Time_Traits>
void win_iocp_io_context::cancel_timer_by_key(timer_queue<Time_Traits>& queue,
    typename timer_queue<Time_Traits>::per_timer_data* timer,
    void* cancellation_key)
{
  // If the service has been shut down we silently ignore the cancellation.
  if (::InterlockedExchangeAdd(&shutdown_, 0) != 0)
    return;

  mutex::scoped_lock lock(dispatch_mutex_);
  op_queue<win_iocp_operation> ops;
  queue.cancel_timer_by_key(timer, ops, cancellation_key);
  lock.unlock();
  post_deferred_completions(ops);
}

template <typename Time_Traits>
void win_iocp_io_context::move_timer(timer_queue<Time_Traits>& queue,
    typename timer_queue<Time_Traits>::per_timer_data& to,
    typename timer_queue<Time_Traits>::per_timer_data& from)
{
  boost::asio::detail::mutex::scoped_lock lock(dispatch_mutex_);
  op_queue<operation> ops;
  queue.cancel_timer(to, ops);
  queue.move_timer(to, from);
  lock.unlock();
  post_deferred_completions(ops);
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_IMPL_WIN_IOCP_IO_CONTEXT_HPP

/* win_iocp_io_context.hpp
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
*/