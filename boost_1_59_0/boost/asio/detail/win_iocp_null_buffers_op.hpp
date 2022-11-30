//
// detail/win_iocp_null_buffers_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/handler_work.hpp>
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
    : reactor_op(boost::system::error_code(),
        &win_iocp_null_buffers_op::do_perform,
        &win_iocp_null_buffers_op::do_complete),
      cancel_token_(cancel_token),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
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

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // Take ownership of the operation's outstanding work.
    handler_work<Handler, IoExecutor> w(
        BOOST_ASIO_MOVE_CAST2(handler_work<Handler, IoExecutor>)(
          o->work_));

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
  handler_work<Handler, IoExecutor> work_;
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