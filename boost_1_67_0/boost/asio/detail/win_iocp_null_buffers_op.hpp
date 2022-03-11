//
// detail/win_iocp_null_buffers_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_NULL_BUFFERS_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_NULL_BUFFERS_OP_HPP

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
#include <boost/asio/detail/reactor_op.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler, typename IoExecutor>
class win_iocp_null_buffers_op : public reactor_op
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_null_buffers_op);

  win_iocp_null_buffers_op(socket_ops::weak_cancel_token_type cancel_token,
      Handler& handler, const IoExecutor& io_ex)
    : reactor_op(&win_iocp_null_buffers_op::do_perform,
        &win_iocp_null_buffers_op::do_complete),
      cancel_token_(cancel_token),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static status do_perform(reactor_op*)
  {
    return done;
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& result_ec,
      std::size_t bytes_transferred)
  {
    boost::system::error_code ec(result_ec);

    // Take ownership of the operation object.
    win_iocp_null_buffers_op* o(static_cast<win_iocp_null_buffers_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // The reactor may have stored a result in the operation object.
    if (o->ec_)
      ec = o->ec_;

    // Map non-portable errors to their portable counterparts.
    if (ec.value() == ERROR_NETNAME_DELETED)
    {
      if (o->cancel_token_.expired())
        ec = boost::asio::error::operation_aborted;
      else
        ec = boost::asio::error::connection_reset;
    }
    else if (ec.value() == ERROR_PORT_UNREACHABLE)
    {
      ec = boost::asio::error::connection_refused;
    }

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
  Handler handler_;
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_NULL_BUFFERS_OP_HPP

/* win_iocp_null_buffers_op.hpp
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
*/