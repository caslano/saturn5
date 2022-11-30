//
// detail/win_iocp_socket_connect_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/handler_work.hpp>
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
    : reactor_op(boost::system::error_code(),
        &win_iocp_socket_connect_op_base::do_perform, complete_func),
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
      work_(handler_, io_ex)
  {
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

    if (owner)
    {
      if (o->connect_ex_)
        socket_ops::complete_iocp_connect(o->socket_, ec);
      else
        ec = o->ec_;
    }

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // Take ownership of the operation's outstanding work.
    handler_work<Handler, IoExecutor> w(
        BOOST_ASIO_MOVE_CAST2(handler_work<Handler, IoExecutor>)(
          o->work_));

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
  handler_work<Handler, IoExecutor> work_;
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