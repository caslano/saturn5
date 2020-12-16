//
// detail/win_iocp_socket_recv_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECV_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECV_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/operation.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename MutableBufferSequence, typename Handler, typename IoExecutor>
class win_iocp_socket_recv_op : public operation
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_socket_recv_op);

  win_iocp_socket_recv_op(socket_ops::state_type state,
      socket_ops::weak_cancel_token_type cancel_token,
      const MutableBufferSequence& buffers, Handler& handler,
      const IoExecutor& io_ex)
    : operation(&win_iocp_socket_recv_op::do_complete),
      state_(state),
      cancel_token_(cancel_token),
      buffers_(buffers),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& result_ec,
      std::size_t bytes_transferred)
  {
    boost::system::error_code ec(result_ec);

    // Take ownership of the operation object.
    win_iocp_socket_recv_op* o(static_cast<win_iocp_socket_recv_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

#if defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)
    // Check whether buffers are still valid.
    if (owner)
    {
      buffer_sequence_adapter<boost::asio::mutable_buffer,
          MutableBufferSequence>::validate(o->buffers_);
    }
#endif // defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)

    socket_ops::complete_iocp_recv(o->state_, o->cancel_token_,
        buffer_sequence_adapter<boost::asio::mutable_buffer,
          MutableBufferSequence>::all_empty(o->buffers_),
        ec, bytes_transferred);

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, std::size_t>
      handler(o->handler_, ec, bytes_transferred);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, handler.arg2_));
      w.complete(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

private:
  socket_ops::state_type state_;
  socket_ops::weak_cancel_token_type cancel_token_;
  MutableBufferSequence buffers_;
  Handler handler_;
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECV_OP_HPP

/* win_iocp_socket_recv_op.hpp
2/oFyHwWWhOeMtDyWzdewcHH+4RksiJljE3i9+q4377DlnyY3etK/UQjqVa67oPQhnIoXOUqB2PLNF/WHdeccszraJgOxpbzcvG/ZbUVywMBh23HORg7VHvTJlwRtubSdT0suxfIsVQzR0SYRfP4kaa2EC6X879jTC3ZGqr6BiUmrrZ6v4wNBXO/3pDzi/DbdqUlKcau/RY5v4057SS5Z9Uci6eM/pkl+wCsjNwHIA1/PP5D3Iu/6j15L4r7YttwpSy5L1qW9pyVsQlJOemxPDOPJeUQNo94OM49R5fCIOrW673W9xuzxfW2W7zXw55Aaj+Oe13PLGr3tylAOLOmnVrpXtMuMvVf0841XWvauU7kmnYz57ndY91+n5B+w/Xha9qnTh85cdzksVMi1+1f2cqdR8KaPB70Wbd/+CTyyDVdeeQ6jjzG5j695j7LZO4zdei273U72HN/507N3n8zddTk2Nzn/9Lcp7Yf6cMrdR34Z47fj+s86EfI2PNT8hyHs9zzU2KzM8SWsIX602Aa7AjTYRZsAwfCDDgGtoUzYTt4BB629HkFA7quHBnrgF6nh9pc7A17wGzYC06Cw2AfeCbsC8fDfnCKnp8FB8AieBq8Cg6EK+FgeAMcAm+BufABOBQ+DIfBbXA4fAyOgD+CebAajoTPwtHwRTgGvgzPhq/DfPgmHAf/DCfCD6BzHbk8m6TMOFjLOvK9UcrRd/rOt31E0F2x+bbYfNt/6XxbbK7tv2uu7VTNs5UsiLNW4Tbj9uKOLfjPmU/78r7/xWZcaADgpL//7+ljGZtoQf2GCX3zpSgbhXRrV7jt/81ZVFxUUWx52f5T+Vxjx2+Z+FsG9loD5V3/wGkheVvfVd/1TbgcYwuvXPztAr+3+rm+efXbVsP0kDCl+EvEnxV41+oVaTNQZNLgTJE5LbDHmm508rtfLdfGj4zxT7O/7c1eS859ln4i8TRx7b/Wml/fk3NvWiusgkjbgmbPh0KRyQ78vCYdHDPpcNsH1PGDr0iYQYEugQZm/GRtA/bklz0D8117Btoy25G5X/YCzHXZD8xQmQO2TNzFYj/wEv7XZjswKY53ZNkjoiLSdqCRyUZmo6Stclvk/hBm/AeZTWI3sPKo7/gPMptr4nnaz/7gBmQelDGiFW1d8eDnNPYExbYgNgWj26fNaVMwTW0KUn/xm/or35sF7rEIY1dzpX47j9Z1AcNx7UPjale725XsE1JTTaQOtBVdYTln6s0RrSMdnXuFyLFUv71C9Hym7x4gCd8U3XLZA6Sp2U+kgh3xLHv/EKlvKfH8ID8Ph8o5eYD7vqtMVoLe96atPfcFyfMvd1Oe5J3y1LxzbIZzXxCVyzT7gkhaw/aIK01UHU1cC+WfkM37prvcdahC250pczNGdp6EGWDKmzjCxjRX4bfHNFclkP9Euy528BuvpA7WbbySdNnloeOVapdP9dF/o/32XniUj64qj3wy0hXWZ6dp/h4T2acCqfwfaOqVHUcr6Qe7DLP4K15WMat8zsKyxWYv1rNWyt41gXCbq6Ok7fxBwt8WiOzPtA/V83Ml/jzSlCTxF5Vd5rClmnlNSGY6MqOb2+sqHpVwLa0MORaQY7vl2MOBTEpnRqC9PmvsNM+hHBab694jae6KDH7u33C5Rkf8SRIu63hexXioHe4dCdfGhEuScGdTQpnWYO5rkFCzuAmt+Ch9pI84+X2vciu0z23DPZdy4n4og31Sz5brWFnzlywmK7welC0pt3QP1eF6bnbR3Jq77O671G/0/sPGuy/UvfXO0/6pANc7NLZ3jafdX2f9MX1S42uRRSu5r6k7Gp7U231vSRrPEPJclnbiOq97ZJr0O20=
*/