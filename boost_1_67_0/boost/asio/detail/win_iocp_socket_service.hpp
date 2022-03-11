//
// detail/win_iocp_socket_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_SERVICE_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)

#include <cstring>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/socket_base.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/mutex.hpp>
#include <boost/asio/detail/operation.hpp>
#include <boost/asio/detail/reactor_op.hpp>
#include <boost/asio/detail/select_reactor.hpp>
#include <boost/asio/detail/socket_holder.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/win_iocp_io_context.hpp>
#include <boost/asio/detail/win_iocp_null_buffers_op.hpp>
#include <boost/asio/detail/win_iocp_socket_accept_op.hpp>
#include <boost/asio/detail/win_iocp_socket_connect_op.hpp>
#include <boost/asio/detail/win_iocp_socket_recvfrom_op.hpp>
#include <boost/asio/detail/win_iocp_socket_send_op.hpp>
#include <boost/asio/detail/win_iocp_socket_service_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Protocol>
class win_iocp_socket_service :
  public execution_context_service_base<win_iocp_socket_service<Protocol> >,
  public win_iocp_socket_service_base
{
public:
  // The protocol type.
  typedef Protocol protocol_type;

  // The endpoint type.
  typedef typename Protocol::endpoint endpoint_type;

  // The native type of a socket.
  class native_handle_type
  {
  public:
    native_handle_type(socket_type s)
      : socket_(s),
        have_remote_endpoint_(false)
    {
    }

    native_handle_type(socket_type s, const endpoint_type& ep)
      : socket_(s),
        have_remote_endpoint_(true),
        remote_endpoint_(ep)
    {
    }

    void operator=(socket_type s)
    {
      socket_ = s;
      have_remote_endpoint_ = false;
      remote_endpoint_ = endpoint_type();
    }

    operator socket_type() const
    {
      return socket_;
    }

    bool have_remote_endpoint() const
    {
      return have_remote_endpoint_;
    }

    endpoint_type remote_endpoint() const
    {
      return remote_endpoint_;
    }

  private:
    socket_type socket_;
    bool have_remote_endpoint_;
    endpoint_type remote_endpoint_;
  };

  // The implementation type of the socket.
  struct implementation_type :
    win_iocp_socket_service_base::base_implementation_type
  {
    // Default constructor.
    implementation_type()
      : protocol_(endpoint_type().protocol()),
        have_remote_endpoint_(false),
        remote_endpoint_()
    {
    }

    // The protocol associated with the socket.
    protocol_type protocol_;

    // Whether we have a cached remote endpoint.
    bool have_remote_endpoint_;

    // A cached remote endpoint.
    endpoint_type remote_endpoint_;
  };

  // Constructor.
  win_iocp_socket_service(execution_context& context)
    : execution_context_service_base<
        win_iocp_socket_service<Protocol> >(context),
      win_iocp_socket_service_base(context)
  {
  }

  // Destroy all user-defined handler objects owned by the service.
  void shutdown()
  {
    this->base_shutdown();
  }

  // Move-construct a new socket implementation.
  void move_construct(implementation_type& impl,
      implementation_type& other_impl) BOOST_ASIO_NOEXCEPT
  {
    this->base_move_construct(impl, other_impl);

    impl.protocol_ = other_impl.protocol_;
    other_impl.protocol_ = endpoint_type().protocol();

    impl.have_remote_endpoint_ = other_impl.have_remote_endpoint_;
    other_impl.have_remote_endpoint_ = false;

    impl.remote_endpoint_ = other_impl.remote_endpoint_;
    other_impl.remote_endpoint_ = endpoint_type();
  }

  // Move-assign from another socket implementation.
  void move_assign(implementation_type& impl,
      win_iocp_socket_service_base& other_service,
      implementation_type& other_impl)
  {
    this->base_move_assign(impl, other_service, other_impl);

    impl.protocol_ = other_impl.protocol_;
    other_impl.protocol_ = endpoint_type().protocol();

    impl.have_remote_endpoint_ = other_impl.have_remote_endpoint_;
    other_impl.have_remote_endpoint_ = false;

    impl.remote_endpoint_ = other_impl.remote_endpoint_;
    other_impl.remote_endpoint_ = endpoint_type();
  }

  // Move-construct a new socket implementation from another protocol type.
  template <typename Protocol1>
  void converting_move_construct(implementation_type& impl,
      win_iocp_socket_service<Protocol1>&,
      typename win_iocp_socket_service<
        Protocol1>::implementation_type& other_impl)
  {
    this->base_move_construct(impl, other_impl);

    impl.protocol_ = protocol_type(other_impl.protocol_);
    other_impl.protocol_ = typename Protocol1::endpoint().protocol();

    impl.have_remote_endpoint_ = other_impl.have_remote_endpoint_;
    other_impl.have_remote_endpoint_ = false;

    impl.remote_endpoint_ = other_impl.remote_endpoint_;
    other_impl.remote_endpoint_ = typename Protocol1::endpoint();
  }

  // Open a new socket implementation.
  boost::system::error_code open(implementation_type& impl,
      const protocol_type& protocol, boost::system::error_code& ec)
  {
    if (!do_open(impl, protocol.family(),
          protocol.type(), protocol.protocol(), ec))
    {
      impl.protocol_ = protocol;
      impl.have_remote_endpoint_ = false;
      impl.remote_endpoint_ = endpoint_type();
    }
    return ec;
  }

  // Assign a native socket to a socket implementation.
  boost::system::error_code assign(implementation_type& impl,
      const protocol_type& protocol, const native_handle_type& native_socket,
      boost::system::error_code& ec)
  {
    if (!do_assign(impl, protocol.type(), native_socket, ec))
    {
      impl.protocol_ = protocol;
      impl.have_remote_endpoint_ = native_socket.have_remote_endpoint();
      impl.remote_endpoint_ = native_socket.remote_endpoint();
    }
    return ec;
  }

  // Get the native socket representation.
  native_handle_type native_handle(implementation_type& impl)
  {
    if (impl.have_remote_endpoint_)
      return native_handle_type(impl.socket_, impl.remote_endpoint_);
    return native_handle_type(impl.socket_);
  }

  // Bind the socket to the specified local endpoint.
  boost::system::error_code bind(implementation_type& impl,
      const endpoint_type& endpoint, boost::system::error_code& ec)
  {
    socket_ops::bind(impl.socket_, endpoint.data(), endpoint.size(), ec);
    return ec;
  }

  // Set a socket option.
  template <typename Option>
  boost::system::error_code set_option(implementation_type& impl,
      const Option& option, boost::system::error_code& ec)
  {
    socket_ops::setsockopt(impl.socket_, impl.state_,
        option.level(impl.protocol_), option.name(impl.protocol_),
        option.data(impl.protocol_), option.size(impl.protocol_), ec);
    return ec;
  }

  // Set a socket option.
  template <typename Option>
  boost::system::error_code get_option(const implementation_type& impl,
      Option& option, boost::system::error_code& ec) const
  {
    std::size_t size = option.size(impl.protocol_);
    socket_ops::getsockopt(impl.socket_, impl.state_,
        option.level(impl.protocol_), option.name(impl.protocol_),
        option.data(impl.protocol_), &size, ec);
    if (!ec)
      option.resize(impl.protocol_, size);
    return ec;
  }

  // Get the local endpoint.
  endpoint_type local_endpoint(const implementation_type& impl,
      boost::system::error_code& ec) const
  {
    endpoint_type endpoint;
    std::size_t addr_len = endpoint.capacity();
    if (socket_ops::getsockname(impl.socket_, endpoint.data(), &addr_len, ec))
      return endpoint_type();
    endpoint.resize(addr_len);
    return endpoint;
  }

  // Get the remote endpoint.
  endpoint_type remote_endpoint(const implementation_type& impl,
      boost::system::error_code& ec) const
  {
    endpoint_type endpoint = impl.remote_endpoint_;
    std::size_t addr_len = endpoint.capacity();
    if (socket_ops::getpeername(impl.socket_, endpoint.data(),
          &addr_len, impl.have_remote_endpoint_, ec))
      return endpoint_type();
    endpoint.resize(addr_len);
    return endpoint;
  }

  // Disable sends or receives on the socket.
  boost::system::error_code shutdown(base_implementation_type& impl,
      socket_base::shutdown_type what, boost::system::error_code& ec)
  {
    socket_ops::shutdown(impl.socket_, what, ec);
    return ec;
  }

  // Send a datagram to the specified endpoint. Returns the number of bytes
  // sent.
  template <typename ConstBufferSequence>
  size_t send_to(implementation_type& impl, const ConstBufferSequence& buffers,
      const endpoint_type& destination, socket_base::message_flags flags,
      boost::system::error_code& ec)
  {
    buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence> bufs(buffers);

    return socket_ops::sync_sendto(impl.socket_, impl.state_,
        bufs.buffers(), bufs.count(), flags,
        destination.data(), destination.size(), ec);
  }

  // Wait until data can be sent without blocking.
  size_t send_to(implementation_type& impl, const null_buffers&,
      const endpoint_type&, socket_base::message_flags,
      boost::system::error_code& ec)
  {
    // Wait for socket to become ready.
    socket_ops::poll_write(impl.socket_, impl.state_, -1, ec);

    return 0;
  }

  // Start an asynchronous send. The data being sent must be valid for the
  // lifetime of the asynchronous operation.
  template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
  void async_send_to(implementation_type& impl,
      const ConstBufferSequence& buffers, const endpoint_type& destination,
      socket_base::message_flags flags, Handler& handler,
      const IoExecutor& io_ex)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_socket_send_op<
        ConstBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl.cancel_token_, buffers, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((context_, *p.p, "socket",
          &impl, impl.socket_, "async_send_to"));

    buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence> bufs(buffers);

    start_send_to_op(impl, bufs.buffers(), bufs.count(),
        destination.data(), static_cast<int>(destination.size()),
        flags, p.p);
    p.v = p.p = 0;
  }

  // Start an asynchronous wait until data can be sent without blocking.
  template <typename Handler, typename IoExecutor>
  void async_send_to(implementation_type& impl, const null_buffers&,
      const endpoint_type&, socket_base::message_flags, Handler& handler,
      const IoExecutor& io_ex)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_null_buffers_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl.cancel_token_, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((context_, *p.p, "socket",
          &impl, impl.socket_, "async_send_to(null_buffers)"));

    start_reactor_op(impl, select_reactor::write_op, p.p);
    p.v = p.p = 0;
  }

  // Receive a datagram with the endpoint of the sender. Returns the number of
  // bytes received.
  template <typename MutableBufferSequence>
  size_t receive_from(implementation_type& impl,
      const MutableBufferSequence& buffers,
      endpoint_type& sender_endpoint, socket_base::message_flags flags,
      boost::system::error_code& ec)
  {
    buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs(buffers);

    std::size_t addr_len = sender_endpoint.capacity();
    std::size_t bytes_recvd = socket_ops::sync_recvfrom(
        impl.socket_, impl.state_, bufs.buffers(), bufs.count(),
        flags, sender_endpoint.data(), &addr_len, ec);

    if (!ec)
      sender_endpoint.resize(addr_len);

    return bytes_recvd;
  }

  // Wait until data can be received without blocking.
  size_t receive_from(implementation_type& impl,
      const null_buffers&, endpoint_type& sender_endpoint,
      socket_base::message_flags, boost::system::error_code& ec)
  {
    // Wait for socket to become ready.
    socket_ops::poll_read(impl.socket_, impl.state_, -1, ec);

    // Reset endpoint since it can be given no sensible value at this time.
    sender_endpoint = endpoint_type();

    return 0;
  }

  // Start an asynchronous receive. The buffer for the data being received and
  // the sender_endpoint object must both be valid for the lifetime of the
  // asynchronous operation.
  template <typename MutableBufferSequence,
      typename Handler, typename IoExecutor>
  void async_receive_from(implementation_type& impl,
      const MutableBufferSequence& buffers, endpoint_type& sender_endp,
      socket_base::message_flags flags, Handler& handler,
      const IoExecutor& io_ex)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_socket_recvfrom_op<MutableBufferSequence,
        endpoint_type, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(sender_endp, impl.cancel_token_,
        buffers, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((context_, *p.p, "socket",
          &impl, impl.socket_, "async_receive_from"));

    buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs(buffers);

    start_receive_from_op(impl, bufs.buffers(), bufs.count(),
        sender_endp.data(), flags, &p.p->endpoint_size(), p.p);
    p.v = p.p = 0;
  }

  // Wait until data can be received without blocking.
  template <typename Handler, typename IoExecutor>
  void async_receive_from(implementation_type& impl, const null_buffers&,
      endpoint_type& sender_endpoint, socket_base::message_flags flags,
      Handler& handler, const IoExecutor& io_ex)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_null_buffers_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl.cancel_token_, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((context_, *p.p, "socket",
          &impl, impl.socket_, "async_receive_from(null_buffers)"));

    // Reset endpoint since it can be given no sensible value at this time.
    sender_endpoint = endpoint_type();

    start_null_buffers_receive_op(impl, flags, p.p);
    p.v = p.p = 0;
  }

  // Accept a new connection.
  template <typename Socket>
  boost::system::error_code accept(implementation_type& impl, Socket& peer,
      endpoint_type* peer_endpoint, boost::system::error_code& ec)
  {
    // We cannot accept a socket that is already open.
    if (peer.is_open())
    {
      ec = boost::asio::error::already_open;
      return ec;
    }

    std::size_t addr_len = peer_endpoint ? peer_endpoint->capacity() : 0;
    socket_holder new_socket(socket_ops::sync_accept(impl.socket_,
          impl.state_, peer_endpoint ? peer_endpoint->data() : 0,
          peer_endpoint ? &addr_len : 0, ec));

    // On success, assign new connection to peer socket object.
    if (new_socket.get() != invalid_socket)
    {
      if (peer_endpoint)
        peer_endpoint->resize(addr_len);
      peer.assign(impl.protocol_, new_socket.get(), ec);
      if (!ec)
        new_socket.release();
    }

    return ec;
  }

  // Start an asynchronous accept. The peer and peer_endpoint objects
  // must be valid until the accept's handler is invoked.
  template <typename Socket, typename Handler, typename IoExecutor>
  void async_accept(implementation_type& impl, Socket& peer,
      endpoint_type* peer_endpoint, Handler& handler, const IoExecutor& io_ex)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_socket_accept_op<Socket,
        protocol_type, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    bool enable_connection_aborted =
      (impl.state_ & socket_ops::enable_connection_aborted) != 0;
    p.p = new (p.v) op(*this, impl.socket_, peer, impl.protocol_,
        peer_endpoint, enable_connection_aborted, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((context_, *p.p, "socket",
          &impl, impl.socket_, "async_accept"));

    start_accept_op(impl, peer.is_open(), p.p->new_socket(),
        impl.protocol_.family(), impl.protocol_.type(),
        impl.protocol_.protocol(), p.p->output_buffer(),
        p.p->address_length(), p.p);
    p.v = p.p = 0;
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  // Start an asynchronous accept. The peer and peer_endpoint objects
  // must be valid until the accept's handler is invoked.
  template <typename PeerIoExecutor, typename Handler, typename IoExecutor>
  void async_move_accept(implementation_type& impl,
      const PeerIoExecutor& peer_io_ex, endpoint_type* peer_endpoint,
      Handler& handler, const IoExecutor& io_ex)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_socket_move_accept_op<
        protocol_type, PeerIoExecutor, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    bool enable_connection_aborted =
      (impl.state_ & socket_ops::enable_connection_aborted) != 0;
    p.p = new (p.v) op(*this, impl.socket_, impl.protocol_,
        peer_io_ex, peer_endpoint, enable_connection_aborted,
        handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((context_, *p.p, "socket",
          &impl, impl.socket_, "async_accept"));

    start_accept_op(impl, false, p.p->new_socket(),
        impl.protocol_.family(), impl.protocol_.type(),
        impl.protocol_.protocol(), p.p->output_buffer(),
        p.p->address_length(), p.p);
    p.v = p.p = 0;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  // Connect the socket to the specified endpoint.
  boost::system::error_code connect(implementation_type& impl,
      const endpoint_type& peer_endpoint, boost::system::error_code& ec)
  {
    socket_ops::sync_connect(impl.socket_,
        peer_endpoint.data(), peer_endpoint.size(), ec);
    return ec;
  }

  // Start an asynchronous connect.
  template <typename Handler, typename IoExecutor>
  void async_connect(implementation_type& impl,
      const endpoint_type& peer_endpoint, Handler& handler,
      const IoExecutor& io_ex)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_socket_connect_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl.socket_, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((context_, *p.p, "socket",
          &impl, impl.socket_, "async_connect"));

    start_connect_op(impl, impl.protocol_.family(), impl.protocol_.type(),
        peer_endpoint.data(), static_cast<int>(peer_endpoint.size()), p.p);
    p.v = p.p = 0;
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_SERVICE_HPP

/* win_iocp_socket_service.hpp
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
*/