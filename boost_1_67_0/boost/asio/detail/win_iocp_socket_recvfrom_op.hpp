//
// detail/win_iocp_socket_recvfrom_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECVFROM_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECVFROM_OP_HPP

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

template <typename MutableBufferSequence, typename Endpoint,
    typename Handler, typename IoExecutor>
class win_iocp_socket_recvfrom_op : public operation
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_socket_recvfrom_op);

  win_iocp_socket_recvfrom_op(Endpoint& endpoint,
      socket_ops::weak_cancel_token_type cancel_token,
      const MutableBufferSequence& buffers, Handler& handler,
      const IoExecutor& io_ex)
    : operation(&win_iocp_socket_recvfrom_op::do_complete),
      endpoint_(endpoint),
      endpoint_size_(static_cast<int>(endpoint.capacity())),
      cancel_token_(cancel_token),
      buffers_(buffers),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  int& endpoint_size()
  {
    return endpoint_size_;
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& result_ec,
      std::size_t bytes_transferred)
  {
    boost::system::error_code ec(result_ec);

    // Take ownership of the operation object.
    win_iocp_socket_recvfrom_op* o(
        static_cast<win_iocp_socket_recvfrom_op*>(base));
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

    socket_ops::complete_iocp_recvfrom(o->cancel_token_, ec);

    // Record the size of the endpoint returned by the operation.
    o->endpoint_.resize(o->endpoint_size_);

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
  Endpoint& endpoint_;
  int endpoint_size_;
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

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECVFROM_OP_HPP

/* win_iocp_socket_recvfrom_op.hpp
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
*/