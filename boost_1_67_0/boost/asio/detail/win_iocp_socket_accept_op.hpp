//
// detail/win_iocp_socket_accept_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
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
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
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

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& result_ec,
      std::size_t /*bytes_transferred*/)
  {
    boost::system::error_code ec(result_ec);

    // Take ownership of the operation object.
    win_iocp_socket_accept_op* o(static_cast<win_iocp_socket_accept_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

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
        handler_work<Handler, IoExecutor>::start(o->handler_, o->io_executor_);
        o->reset();
        o->socket_service_.restart_accept_op(o->socket_,
            o->new_socket_, o->protocol_.family(),
            o->protocol_.type(), o->protocol_.protocol(),
            o->output_buffer(), o->address_length(), o);
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
  Handler handler_;
  IoExecutor io_executor_;
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
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
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

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& result_ec,
      std::size_t /*bytes_transferred*/)
  {
    boost::system::error_code ec(result_ec);

    // Take ownership of the operation object.
    win_iocp_socket_move_accept_op* o(
        static_cast<win_iocp_socket_move_accept_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

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
        handler_work<Handler, IoExecutor>::start(o->handler_, o->io_executor_);
        o->reset();
        o->socket_service_.restart_accept_op(o->socket_,
            o->new_socket_, o->protocol_.family(),
            o->protocol_.type(), o->protocol_.protocol(),
            o->output_buffer(), o->address_length(), o);
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
  Handler handler_;
  IoExecutor io_executor_;
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