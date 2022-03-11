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
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
*/