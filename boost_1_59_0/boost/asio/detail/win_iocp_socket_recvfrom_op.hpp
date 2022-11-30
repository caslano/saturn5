//
// detail/win_iocp_socket_recvfrom_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/handler_work.hpp>
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
      work_(handler_, io_ex)
  {
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

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // Take ownership of the operation's outstanding work.
    handler_work<Handler, IoExecutor> w(
        BOOST_ASIO_MOVE_CAST2(handler_work<Handler, IoExecutor>)(
          o->work_));

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
  handler_work<Handler, IoExecutor> work_;
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