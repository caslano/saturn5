//
// detail/impl/win_iocp_io_context.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
  post_deferred_completions(ops);
  return n;
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