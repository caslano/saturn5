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
KHiXJYEuFySRmi+JIb0k0aQwUwIFJyXR1kkSy3pKoktlhgSKrkii5xpJpIZJIr8pXQIpwR/Ep+x8GsQX5NiyWJqIVU2O7PO6Ztb+jZV2vUS6SNDDFgnp+Gyg+jfxOcTuYtTWQxgojMKn6fAHYfgoeuUc31b26xn+exEVBcCqkuJw9Lz6Tur+Zbv8BTIG+OMgsgJZrLGKxM4opXz0XytKcsM7hXq16ndYT2XyjRULs8nZhxbx3TvsJa2pdewtRE4GLg2snxZyOWoeQqw0wgcNi8Tfr5+PBcadrUTxZC4+0ee1Gt+4Yoe/bLJCoiaSEmXU5idyhY4CZ9RDx+Ibcdjg3n24Y4EyOJIB5KMlKh4N2OzPUfwdD2+WWJyNFVCeDWKVVHL9X69xm6wz5+9bpSgItLB7VDrpB3Sd+/hZxOo6hpL6mTz7cWXTsW1wYExEcMjiQJgflD7fxvkYOFZQQ1oaTsPRDt1uyESHwdvyq6Eany9DhdEOa3+t63D/m1LhTZNbADdsuhaMuwsGfqI4Q/1wsOhmO9HsUgRork+ca9LrIVya+jbH6tAj+NRwYAr/12O4rW/QSWvlUwidsseie3YkiScagujbee8OPgOe5aTe76pjwLCX6u24sbEwzHeS/4kgBg4kXnN/7iGA5118RdYacXDNNrV3zcM4iN2+OO+RfTxEhiUdflIfD707TwtoDEmA0W2Vu3YaJUIvs/cK
*/