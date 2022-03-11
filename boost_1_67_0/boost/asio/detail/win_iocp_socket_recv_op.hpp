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
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
*/