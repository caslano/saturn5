//
// detail/win_iocp_wait_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
    : reactor_op(&win_iocp_wait_op::do_perform,
        &win_iocp_wait_op::do_complete),
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
      std::size_t /*bytes_transferred*/)
  {
    boost::system::error_code ec(result_ec);

    // Take ownership of the operation object.
    win_iocp_wait_op* o(static_cast<win_iocp_wait_op*>(base));
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
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_WAIT_OP_HPP

/* win_iocp_wait_op.hpp
2etTWL4C8mpOgNyGLYPEmTcJdIb+Ap80soH2hN9liEMFZ5ZNs4y0Nyyo9GlTKRcv/65OPJD3ON34d/6f52DRojmByBz8qjmqFtvjoTfMNjsP0s7O3ymjtPr/V8z1BP7X6OceM3jqVHAO8up0VOa6g8Gv0S9KFc0h2PUT9J/lW2oKknwiSWYV/eFK7KhXjg9+ZqVIboOXiD0H9yIroJu3nLAf7GIg8X/US60KhCaet3OwRTGKb1p3DQT4PkQJs9gW1hQrYHoZ3IheM/Jj4+Y4wA7Vv1zpMLC7VJOjaOC/ctD76GRUEUaJb8C1ETT8l+zjW32X8Derw2r6feSjbBW7E43lDnIsJj8V/dO436b2P2Zv6QPTbmrImaDKr45p8yBjjNs/Ju4bDbd+HGaik2udfJNjTkdtYnpKM0ptMykSgNRsSQcAEphmSx8ZxF9pDUy8Gjz3mIlxw3PyHGGHcE58EA4mF7oi8Zu8l+sGtBXn4/Ug0Pq4VYCCCcmCBz4KUASkeIo72GoHPqJUz7WKgk+x96SnAyFc6OIwy83tgnr03YZgeX1GkoYASppNsg==
*/