//
// detail/win_iocp_socket_connect_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_CONNECT_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_CONNECT_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/bind_handler.hpp>
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

class win_iocp_socket_connect_op_base : public reactor_op
{
public:
  win_iocp_socket_connect_op_base(socket_type socket, func_type complete_func)
    : reactor_op(&win_iocp_socket_connect_op_base::do_perform, complete_func),
      socket_(socket),
      connect_ex_(false)
  {
  }

  static status do_perform(reactor_op* base)
  {
    win_iocp_socket_connect_op_base* o(
        static_cast<win_iocp_socket_connect_op_base*>(base));

    return socket_ops::non_blocking_connect(
        o->socket_, o->ec_) ? done : not_done;
  }

  socket_type socket_;
  bool connect_ex_;
};

template <typename Handler, typename IoExecutor>
class win_iocp_socket_connect_op : public win_iocp_socket_connect_op_base
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_socket_connect_op);

  win_iocp_socket_connect_op(socket_type socket,
      Handler& handler, const IoExecutor& io_ex)
    : win_iocp_socket_connect_op_base(socket,
        &win_iocp_socket_connect_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& result_ec,
      std::size_t /*bytes_transferred*/)
  {
    boost::system::error_code ec(result_ec);

    // Take ownership of the operation object.
    win_iocp_socket_connect_op* o(
        static_cast<win_iocp_socket_connect_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    if (owner)
    {
      if (o->connect_ex_)
        socket_ops::complete_iocp_connect(o->socket_, ec);
      else
        ec = o->ec_;
    }

    BOOST_ASIO_HANDLER_COMPLETION((*o));

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
  Handler handler_;
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_CONNECT_OP_HPP

/* win_iocp_socket_connect_op.hpp
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
*/