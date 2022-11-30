//
// detail/win_iocp_socket_accept_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_ACCEPT_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_ACCEPT_OP_HPP

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
#include <boost/asio/detail/operation.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/detail/win_iocp_socket_service_base.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Socket, typename Protocol,
    typename Handler, typename IoExecutor>
class win_iocp_socket_accept_op : public operation
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_socket_accept_op);

  win_iocp_socket_accept_op(win_iocp_socket_service_base& socket_service,
      socket_type socket, Socket& peer, const Protocol& protocol,
      typename Protocol::endpoint* peer_endpoint,
      bool enable_connection_aborted, Handler& handler, const IoExecutor& io_ex)
    : operation(&win_iocp_socket_accept_op::do_complete),
      socket_service_(socket_service),
      socket_(socket),
      peer_(peer),
      protocol_(protocol),
      peer_endpoint_(peer_endpoint),
      enable_connection_aborted_(enable_connection_aborted),
      proxy_op_(0),
      cancel_requested_(0),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  socket_holder& new_socket()
  {
    return new_socket_;
  }

  void* output_buffer()
  {
    return output_buffer_;
  }

  DWORD address_length()
  {
    return sizeof(sockaddr_storage_type) + 16;
  }

  void enable_cancellation(long* cancel_requested, operation* proxy_op)
  {
    cancel_requested_ = cancel_requested;
    proxy_op_ = proxy_op;
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& result_ec,
      std::size_t /*bytes_transferred*/)
  {
    boost::system::error_code ec(result_ec);

    // Take ownership of the operation object.
    win_iocp_socket_accept_op* o(static_cast<win_iocp_socket_accept_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    if (owner)
    {
      typename Protocol::endpoint peer_endpoint;
      std::size_t addr_len = peer_endpoint.capacity();
      socket_ops::complete_iocp_accept(o->socket_,
          o->output_buffer(), o->address_length(),
          peer_endpoint.data(), &addr_len,
          o->new_socket_.get(), ec);

      // Restart the accept operation if we got the connection_aborted error
      // and the enable_connection_aborted socket option is not set.
      if (ec == boost::asio::error::connection_aborted
          && !o->enable_connection_aborted_)
      {
        o->reset();
        if (o->proxy_op_)
          o->proxy_op_->reset();
        o->socket_service_.restart_accept_op(o->socket_,
            o->new_socket_, o->protocol_.family(),
            o->protocol_.type(), o->protocol_.protocol(),
            o->output_buffer(), o->address_length(),
            o->cancel_requested_, o->proxy_op_ ? o->proxy_op_ : o);
        p.v = p.p = 0;
        return;
      }

      // If the socket was successfully accepted, transfer ownership of the
      // socket to the peer object.
      if (!ec)
      {
        o->peer_.assign(o->protocol_,
            typename Socket::native_handle_type(
              o->new_socket_.get(), peer_endpoint), ec);
        if (!ec)
          o->new_socket_.release();
      }

      // Pass endpoint back to caller.
      if (o->peer_endpoint_)
        *o->peer_endpoint_ = peer_endpoint;
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
  win_iocp_socket_service_base& socket_service_;
  socket_type socket_;
  socket_holder new_socket_;
  Socket& peer_;
  Protocol protocol_;
  typename Protocol::endpoint* peer_endpoint_;
  unsigned char output_buffer_[(sizeof(sockaddr_storage_type) + 16) * 2];
  bool enable_connection_aborted_;
  operation* proxy_op_;
  long* cancel_requested_;
  Handler handler_;
  handler_work<Handler, IoExecutor> work_;
};

#if defined(BOOST_ASIO_HAS_MOVE)

template <typename Protocol, typename PeerIoExecutor,
    typename Handler, typename IoExecutor>
class win_iocp_socket_move_accept_op : public operation
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_socket_move_accept_op);

  win_iocp_socket_move_accept_op(
      win_iocp_socket_service_base& socket_service, socket_type socket,
      const Protocol& protocol, const PeerIoExecutor& peer_io_ex,
      typename Protocol::endpoint* peer_endpoint,
      bool enable_connection_aborted, Handler& handler, const IoExecutor& io_ex)
    : operation(&win_iocp_socket_move_accept_op::do_complete),
      socket_service_(socket_service),
      socket_(socket),
      peer_(peer_io_ex),
      protocol_(protocol),
      peer_endpoint_(peer_endpoint),
      enable_connection_aborted_(enable_connection_aborted),
      cancel_requested_(0),
      proxy_op_(0),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  socket_holder& new_socket()
  {
    return new_socket_;
  }

  void* output_buffer()
  {
    return output_buffer_;
  }

  DWORD address_length()
  {
    return sizeof(sockaddr_storage_type) + 16;
  }

  void enable_cancellation(long* cancel_requested, operation* proxy_op)
  {
    cancel_requested_ = cancel_requested;
    proxy_op_ = proxy_op;
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& result_ec,
      std::size_t /*bytes_transferred*/)
  {
    boost::system::error_code ec(result_ec);

    // Take ownership of the operation object.
    win_iocp_socket_move_accept_op* o(
        static_cast<win_iocp_socket_move_accept_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    if (owner)
    {
      typename Protocol::endpoint peer_endpoint;
      std::size_t addr_len = peer_endpoint.capacity();
      socket_ops::complete_iocp_accept(o->socket_,
          o->output_buffer(), o->address_length(),
          peer_endpoint.data(), &addr_len,
          o->new_socket_.get(), ec);

      // Restart the accept operation if we got the connection_aborted error
      // and the enable_connection_aborted socket option is not set.
      if (ec == boost::asio::error::connection_aborted
          && !o->enable_connection_aborted_)
      {
        o->reset();
        if (o->proxy_op_)
          o->proxy_op_->reset();
        o->socket_service_.restart_accept_op(o->socket_,
            o->new_socket_, o->protocol_.family(),
            o->protocol_.type(), o->protocol_.protocol(),
            o->output_buffer(), o->address_length(),
            o->cancel_requested_, o->proxy_op_ ? o->proxy_op_ : o);
        p.v = p.p = 0;
        return;
      }

      // If the socket was successfully accepted, transfer ownership of the
      // socket to the peer object.
      if (!ec)
      {
        o->peer_.assign(o->protocol_,
            typename Protocol::socket::native_handle_type(
              o->new_socket_.get(), peer_endpoint), ec);
        if (!ec)
          o->new_socket_.release();
      }

      // Pass endpoint back to caller.
      if (o->peer_endpoint_)
        *o->peer_endpoint_ = peer_endpoint;
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
    detail::move_binder2<Handler,
      boost::system::error_code, peer_socket_type>
        handler(0, BOOST_ASIO_MOVE_CAST(Handler)(o->handler_), ec,
          BOOST_ASIO_MOVE_CAST(peer_socket_type)(o->peer_));
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, "..."));
      w.complete(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

private:
  typedef typename Protocol::socket::template
    rebind_executor<PeerIoExecutor>::other peer_socket_type;

  win_iocp_socket_service_base& socket_service_;
  socket_type socket_;
  socket_holder new_socket_;
  peer_socket_type peer_;
  Protocol protocol_;
  typename Protocol::endpoint* peer_endpoint_;
  unsigned char output_buffer_[(sizeof(sockaddr_storage_type) + 16) * 2];
  bool enable_connection_aborted_;
  long* cancel_requested_;
  operation* proxy_op_;
  Handler handler_;
  handler_work<Handler, IoExecutor> work_;
};

#endif // defined(BOOST_ASIO_HAS_MOVE)

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_ACCEPT_OP_HPP

/* win_iocp_socket_accept_op.hpp
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
*/