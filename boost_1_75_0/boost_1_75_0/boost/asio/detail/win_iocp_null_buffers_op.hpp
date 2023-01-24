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
ycy51n4FM4SuWeqJW+OhdgC50CsKOsQro/PTFKHzHGwMcCXqTC1CU2AQBDHo4JlIVAdjPVBatrVgyobUBF1rfQTx/Kb4RNNMrKd9AhKzJ8w3JKgtN+Z+aGZHZr9EuTARIloM44VqVzA97E36K06Z9wvD06bFtWm0fDUCv2p/TxVz4qkU5cWwAygjz35DHAHVOTAAsCfOC/utZ9TiVrmRus1x/jUYue0QwoqkeuoTDyBrTszpoxopt0/aHUsZLNwM4vwAtKFkdaUPaQR4K1Rje6jQJvUoagkZMH18Vk3IabD9fLtRMVqLE7F7/bxU6dopXBNpxcr1wGY8GcoiT2DLDxgBCrUvUXSS/Ypn90bWMf2R4zv0PoOaQvoN7fDSN/zr6wNdfgJ7Z0huAnvMMxab8JFg6a7sn8QigKzf10VhnrCvAnH391sHZL90FXi1aQj6qB/Ddu0QKdNivxbHjRCHkZNYXJERPjK/L9RHUBN4xIrojNoXN5QFjb8j664jHtB8J/ov0jUL/CZxPfCiRRwiZvEnPxaNZS16sUdBqV1fEJ1GX+7FMDGxQJjR/KbQru8QHdbjK5ZvJWDX/vmSrdtmgtg5GGlvJ3aBRd9TKfrhjQY3De/3HkMca+2lEYtpAyaxVK/5yYzcz+YdgkcZ+hG3fS2+NkTMjcjLCm1Y4XSXi7+Rstw0MRJxjVUJwpoiRpjhPwQWcrxf5O7/5K7G
*/