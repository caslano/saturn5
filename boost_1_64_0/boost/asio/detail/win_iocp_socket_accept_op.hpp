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
Glqz3x0G4RXIHn4gou6bSRzf+q9hhplnYK+NIf/7fnVf5YcYnd3uIv+h75xMlpw/JP4CE36g57vRVHO+v/k26iThP/J8bxgv52aY+veg+hta42t9X8gVOcb6xW+Hmy3h/N4VLhKZoOlf54l/qBlHOVf8PyCdd1mdufuHqRfx/ez3hGp9T8hIHhN6SegU3TuC/S2ye6N5x8Qfnk/pc/V6PfrZ7wX57vcClZlhy8RNl/eC0X7vBSqPoUd9L5jj+awPe7+r/Xk/vi71Xd8LXPNeJbWMMxUOqLnQVLWv0hd+gzjLN5l2wWbvS8qK/cf3VHaguc/3i79hwKv9TDDyfUzdukv8LQIu/XFtD/fI+bSAV5+6Vc59yDxephljOSLHMt3v/Vovfyrnb7CysA6UoWPUj8mxLdyrvnxHp/DdlC1zOkk59IX9tS9sPNhVR2yZcmR2isxZ7ue7yqxD5i2RWezQSwuX2WGuVbnB71r7zLUqt/pdixus16rc57qWtqOilJPTJ5b52PB66dgDwM8mvp+t/7rbxPe2rX/qbOWfKlv2G3LFZv3pXy9/+KwtV4ysujRn84x5N/jZ0PfbO8HPRr/fngp+tvv99jzws6HvZ3Pfz0a/314Lfnsq+O3x4Gdzv+42/eu6V8R1WaHjneM3f+WZJge6jP/WpflLnpvxsP/eDx+rPSNLbf2XBGxb/+a3PD8q+d26Aek3v2veg3bAIDIPmt81fUBuoCavOx2/9zh+v+r4/UfH7986fr/l+P2G4/eb5lo177lJYvuO55H+zsb9WX+Pwx3Q30/gxH6Tva5InxlJEfablqs9+mvhKLgKjoerYSFcA+fCG2AZvBEugTerHexb4eVwHbwGrofr4R3wDng33AKr4HZ4L3wcboS/hQ/CN+AW+Gf4EHwffh8eho/AY3ArjA/Zx4PJ8HHYAj4Bs+AOtVdVadlrUGQti+S3CazQ/F6EXIhFsLX6O8K5sA8shsPhJfBsWAKnwHlwFpwPF8MF8JuwDG6AC+ET8GvQtmcp6y507UZShD3LryDXBM6AGXAm7A7Ph73Vn6N+YyfnO8ft5FRG2JtqbeRwUcrlGTkpvzC5oNPOVZRylVHKVTnkciPS94Jz34Mo5fZHKWetj04uM0q5vCjlCqOUq4xSrsohVxLwt6tUHYXcDNx+lVuq9dTYZVR7ey3gEzAb/hgOgU/Cs+GP4EQ9/hW4E84Wv9qNtvXQVC8vKcJudA/kesLesC/MhoNgfzgVDoLT4BD4dZgLr4JD4Tfh6XAVPEOvd8xSvSxYpv1dO34f0uv9CrmW8FXYFb4O+8HfwjHwH3AK3AfPgb/X678BC+GbcBl8C16v/rXwHXgbfBfeBf8M71H/VvgX+GP4HvxUjzcOqF1K+DFsDz+BWfB92BP+FQ6Ah+EweASOgH+Do+Hf4RxIunV/CtWNUR2fpIj9KeIacD3YFLZVfwf1d4fNYDYcDAfB5vpcaAHLYUv4DdgK3qDH74Bt4VbYDj4J28Nq9T+j/udhB7gXdoSvwK7a73fT+t0DfgR7w9akuQ/sAPvC7rAfzIYD4BmwLZwMB8FL4GBYDtNgBWwNL4enGXv9quegehJJEfa5z1R7iyNhJhyj/fBZMBeO1efjeFgMp2i5FMAlKl8Jz9Xn4TR4Ozwb2va5Ze5cdQWSIuxzX2Bx/2Eh7K7ttJcez1H/EHgJLIPz4SJ4KVwC33PYB/82XAyr4FL4oPofUv82eBl8WuV/DlfBX0DikOfzangAroHvqP9d9R+BN8FP4a2wodqLzYDrYQe4AWbDO2AuvB6eB++FX4Ub4TVwK3wEboO74KPwWbgWPg8fhx/AHbAhZfVD2Az+BbaGh2AH+B4=
*/