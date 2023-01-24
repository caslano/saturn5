//
// detail/win_iocp_socket_recvmsg_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECVMSG_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECVMSG_OP_HPP

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
#include <boost/asio/socket_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename MutableBufferSequence, typename Handler, typename IoExecutor>
class win_iocp_socket_recvmsg_op : public operation
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_socket_recvmsg_op);

  win_iocp_socket_recvmsg_op(
      socket_ops::weak_cancel_token_type cancel_token,
      const MutableBufferSequence& buffers,
      socket_base::message_flags& out_flags,
      Handler& handler, const IoExecutor& io_ex)
    : operation(&win_iocp_socket_recvmsg_op::do_complete),
      cancel_token_(cancel_token),
      buffers_(buffers),
      out_flags_(out_flags),
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
    win_iocp_socket_recvmsg_op* o(
        static_cast<win_iocp_socket_recvmsg_op*>(base));
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

    socket_ops::complete_iocp_recvmsg(o->cancel_token_, ec);
    o->out_flags_ = 0;

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
  socket_ops::weak_cancel_token_type cancel_token_;
  MutableBufferSequence buffers_;
  socket_base::message_flags& out_flags_;
  Handler handler_;
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECVMSG_OP_HPP

/* win_iocp_socket_recvmsg_op.hpp
qW2ryh/fkx6eOwfRCdqTAvXuqYwGjzqXR/+Ms4vKU+vVL3sVAyotoNIZ7jNQ7dBN5SkegcHiQdOSZpNMQz/nmXg7s5AjL2BCn/eU+SH05FeofPb2hOd6EHvOKxEph2j3CWQFYfI8SbqC58a3bwY/vgpg9Ohod1vdsw+7Jorq9spO9zwmHFYx3zj+M5JzcRXmRE6wN/nFB5+0Lf+YmWWv1idLrXtQtyfTxod+AxGtPJTuSLkLlDbjcg/RBeOyxIi/3CyBEwcWm8kUcQRd/X5ut9KUTXHgP+JIIt3THkvdLWyTbWnH4ouab7rRwNYQJe8O7HXq4bgWrs8aLyV4IlDH05JLIlLqg6AmcPuvsSM/BBItpe4C3roJlx2tuVPci2mDxjKeA7Y6gY4XxfNYXL/VL5vdQ7aM7sKNG5Idot98Q+XXpqmQTbS3Vvrisy5M2V6e7ip+hGk7jeegsLkhHfwDCk1bAYQ1n7Ga4hQQ/QP55FHycCOw5ZIv3PzLhFlI66MBEb8E+EjZu0y7u4WIqfpYPz7BOeKbjW6S2ekKBuXZmDXpOO3WyIrYs8e9OvMh/0BUh+Qbz4F18NPXNIUsqLjA7jf9J8bJZrJ0SUyIW9/i693YdEcJhtr1u0S58CzovJulQsiaGW4/G3QlmTMrl2RG5Mqu3zUm3XRJZ7xexTite8HW2pUZN01F3620jmifRSmeNqxl/9O1kpFrRwXR
*/