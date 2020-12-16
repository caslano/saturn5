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
/9FQPhp+TNcAUtJkLk8aM8WnXQ/heYaw+OPX+7R+57Rf4tP5J3m00pGMpus6whXCUx4ayixkCPZv9kVSoAzvIK3UDoM7dUhN6dita7ecyB+cQ/GWk64pPC/6ZWk4KXRCwsnCv0nS1vLR8nhW4rPFns4Q1iDO4Vo5910Gze3fgsuhd/UGE/AHmCPfnpE3vVZi1h80ffUHmCJ8YYddg7UpeqYTfc4D/whl0XbysgLazqp10nas8k/S8te2o3JDjJ+6yyT8HHUp9W7VpeTxXRL3oq2uaA7lrWXW0/AkS7gv4Ssl/Iy2I0tG86Dt9f3Cc7/whIUnknGtO20nnxCeT4dGUQ9duL60t9QF1PJ3zyypA62TxOqDcqGcNU9aH+TVU/aZHVuEx+i32TnQ4MLIoUyfsn/vqip1jillSRr2dTuV6aPhpNAeCZ9jvsWe0Sv2t9i6dqX53+L0DdDRaWN7GJRNXhv88roxel4bXHl9RfMaYOND+UcZXT7dP3FdAux7sH5wrui3W9pJ6/dbA6A/p/PfENEv0npomBfkcyVo3FTegd7+r225g8T3k7z7Zz3L2GDq7OzX7euInnXEs79e+GVZL/zjhKsf+/yd37784ptPPT93/5sdgtYLg9Y1///WESPfQWoDl2dqGXycOZf1xZ3We4K+r/AtlfBuV/7zGcrO0/W/wbr+N0e/bVyt64Yf1nXDW/XbqJ26PrhH1wfvAXPBp3Rd8de6rvgb5f+LfnvFeTb6P+mBE/RsFffUZxh9TvPXQ85267czmr+p4ChdL5wOQvLNWhH4Xv32bitYouuU88Bd+q3dXeAM8FFdh3wenAW+pt/w/RFcoPkpDVlju+gi+TlH+PRbppB+y6Rn7fpp/vpHxDQ8XNdjc+S69c2Yjqs6pq9xfTN2rt43Te/bC5Qz4mC2rgMP0+t6Px3/ZAylzp33OwSf9e1BB/AFvf+LYF/wMDhAv0Uoa19v/Y9bb+W8Vvua61lac+W801lZd93Fuuvj0DGo917O7extX4f9d87//8XetQBWWZbhM842xnaAswuHbYwxYMCAIQMRxtVxlcuAAQOGUdtgg00HO+7CRUdOI6UinYZFRjWLBO9T0VDJsDDxlkvITMlWkWFRTdMio8tz3j3/t/96djbovqMvz77/e9/vf7/r/33f//7fW4V58cVa/x/NRBraOTlhxnVEOugHeOnWOpDv/3lejG5ajnvxHBg1Lyc/pB3m4Ywf06V5OO4VbB6uzknN72HNyynkJSvVmpfq2nVXla6vKdxcvAn2DPZ5gpzK01HJk3CrPCHekKchSV3P01HJk6RvOIMrw23NU+pkrIRt8gRf6tXllZtt8+JnXuIQFyf7L+TW7cH4Tfl5IoQzuMz58TE/uAfCvEf3GuQ/ypbhNVmbXPbRV0b/PPKhz33d98eF+zc83b/blkFvy1AAkjGLfa/edA7FUFyS/giM41ojgWuLJK450rjmSOd1kISZPsYP5/QHMP0Upj+Q6acx/VSmP4jppzF9hFX6/iDpxzP9BKbfj+knMn0f0+8v6XMNwHBDiHNs2E7DRjr4XDvvbvP3Hxd33l139//G3JvfVNjOwV+/O7R5ePiB4LYPWQf+uXPxogOhzcdD+bYh1Hl544GO5+aHDvzz5udOc/OWA/bz8/cPhD5Hz8ecfBuosXtu3v3r/nX/un//8t+/av2PleFFs/9/AOuLeVxfnurBvXbQQJ4B9rdsrNO87evLJTMXzy2cuyR/+ZrC9VWlga8A1m0vXLJgjvY+63y2rI1LdWeMUj5Nvcs9KuEy9f4f/OUlau2p8Y/RxcuXBurd7XGJL5VwmUo/Q/jD28503V5TWq3e0X5X4ldIeJk=
*/