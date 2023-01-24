//
// detail/win_iocp_socket_send_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_SEND_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_SEND_OP_HPP

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

template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
class win_iocp_socket_send_op : public operation
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_socket_send_op);

  win_iocp_socket_send_op(socket_ops::weak_cancel_token_type cancel_token,
      const ConstBufferSequence& buffers, Handler& handler,
      const IoExecutor& io_ex)
    : operation(&win_iocp_socket_send_op::do_complete),
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
    win_iocp_socket_send_op* o(static_cast<win_iocp_socket_send_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

#if defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)
    // Check whether buffers are still valid.
    if (owner)
    {
      buffer_sequence_adapter<boost::asio::const_buffer,
          ConstBufferSequence>::validate(o->buffers_);
    }
#endif // defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)

    socket_ops::complete_iocp_send(o->cancel_token_, ec);

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
  ConstBufferSequence buffers_;
  Handler handler_;
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_SEND_OP_HPP

/* win_iocp_socket_send_op.hpp
AiH47agowCC8mOQw/w5L/ccZYXykDX0izzE6LmIDIO6zruhDyLziq9a4rSVPThzTkCTKdpXxcWzXzg8bDHIzmrKdNrD9g+hWoTO/GlKNXnnYpBJMnaDOlNs0r3Tq1RQeZc9Dj5jGR6/uozezS9W1o6ZIzoAVbCgw4MRG/ku4SSNZY+lH93eNd7XZD8lEZuysX7p2Qg+eA/c+XBJSqHw6pjubB0q8ldKkSy/jhqXwaFbEWSpL8DrJzUOEXfbysDAMs0aaSBxYGXa1ZEBV/r/sDtekTcDEaVw3Wr24X38zF33JgrqQEVHQtx1CCrEc4YqtBOoyn+1sP/oufPeRgpYzfxMgnW3rpXEKFAn1Hv1laPZHW3RF418bxWEerhpft1mDdXInloS6EXA+fN1EP+Xh2OSPeTm4mO69oDd7NYjXFrzNcctMIFWELuzQxfHqWYm9fxR3hRKZ+c8+/pM778aniPLY1cHtxWQ2bUs8np7EKmQc7fab4zgdaZwQozOJZ30HBa2IXA3t2Ls6+kju0rX517NtjQzGP4PCQQsqJSofIknkS16UP5QPb3lWkeZwvApsTfgu137uf6i4xp0Pl0iTusWFNvwqkcr6wgDdbC7/UsuwxII4GqpnVMTHeVLj9KBgWYFLmqJEIjjageacOpFS3C6/L5lCOGyP2l5LgUpUyouycJkS4yuAISaP8aYG5HxjyinXzczX0BG6N/qt
*/