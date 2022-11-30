//
// detail/win_iocp_wait_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_WAIT_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_WAIT_OP_HPP

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
#include <boost/asio/detail/reactor_op.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler, typename IoExecutor>
class win_iocp_wait_op : public reactor_op
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_wait_op);

  win_iocp_wait_op(socket_ops::weak_cancel_token_type cancel_token,
      Handler& handler, const IoExecutor& io_ex)
    : reactor_op(boost::system::error_code(),
        &win_iocp_wait_op::do_perform,
        &win_iocp_wait_op::do_complete),
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
      std::size_t /*bytes_transferred*/)
  {
    boost::system::error_code ec(result_ec);

    // Take ownership of the operation object.
    win_iocp_wait_op* o(static_cast<win_iocp_wait_op*>(base));
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
    detail::binder1<Handler, boost::system::error_code>
      handler(o->handler_, ec);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_));
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

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_WAIT_OP_HPP

/* win_iocp_wait_op.hpp
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
*/