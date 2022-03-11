//
// detail/reactive_socket_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTIVE_SOCKET_SERVICE_HPP
#define BOOST_ASIO_DETAIL_REACTIVE_SOCKET_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/buffer.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/socket_base.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/reactive_null_buffers_op.hpp>
#include <boost/asio/detail/reactive_socket_accept_op.hpp>
#include <boost/asio/detail/reactive_socket_connect_op.hpp>
#include <boost/asio/detail/reactive_socket_recvfrom_op.hpp>
#include <boost/asio/detail/reactive_socket_sendto_op.hpp>
#include <boost/asio/detail/reactive_socket_service_base.hpp>
#include <boost/asio/detail/reactor.hpp>
#include <boost/asio/detail/reactor_op.hpp>
#include <boost/asio/detail/socket_holder.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Protocol>
class reactive_socket_service :
  public execution_context_service_base<reactive_socket_service<Protocol> >,
  public reactive_socket_service_base
{
public:
  // The protocol type.
  typedef Protocol protocol_type;

  // The endpoint type.
  typedef typename Protocol::endpoint endpoint_type;

  // The native type of a socket.
  typedef socket_type native_handle_type;

  // The implementation type of the socket.
  struct implementation_type :
    reactive_socket_service_base::base_implementation_type
  {
    // Default constructor.
    implementation_type()
      : protocol_(endpoint_type().protocol())
    {
    }

    // The protocol associated with the socket.
    protocol_type protocol_;
  };

  // Constructor.
  reactive_socket_service(execution_context& context)
    : execution_context_service_base<
        reactive_socket_service<Protocol> >(context),
      reactive_socket_service_base(context)
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
  }

  // Move-assign from another socket implementation.
  void move_assign(implementation_type& impl,
      reactive_socket_service_base& other_service,
      implementation_type& other_impl)
  {
    this->base_move_assign(impl, other_service, other_impl);

    impl.protocol_ = other_impl.protocol_;
    other_impl.protocol_ = endpoint_type().protocol();
  }

  // Move-construct a new socket implementation from another protocol type.
  template <typename Protocol1>
  void converting_move_construct(implementation_type& impl,
      reactive_socket_service<Protocol1>&,
      typename reactive_socket_service<
        Protocol1>::implementation_type& other_impl)
  {
    this->base_move_construct(impl, other_impl);

    impl.protocol_ = protocol_type(other_impl.protocol_);
    other_impl.protocol_ = typename Protocol1::endpoint().protocol();
  }

  // Open a new socket implementation.
  boost::system::error_code open(implementation_type& impl,
      const protocol_type& protocol, boost::system::error_code& ec)
  {
    if (!do_open(impl, protocol.family(),
          protocol.type(), protocol.protocol(), ec))
      impl.protocol_ = protocol;
    return ec;
  }

  // Assign a native socket to a socket implementation.
  boost::system::error_code assign(implementation_type& impl,
      const protocol_type& protocol, const native_handle_type& native_socket,
      boost::system::error_code& ec)
  {
    if (!do_assign(impl, protocol.type(), native_socket, ec))
      impl.protocol_ = protocol;
    return ec;
  }

  // Get the native socket representation.
  native_handle_type native_handle(implementation_type& impl)
  {
    return impl.socket_;
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
    endpoint_type endpoint;
    std::size_t addr_len = endpoint.capacity();
    if (socket_ops::getpeername(impl.socket_,
          endpoint.data(), &addr_len, false, ec))
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
      const ConstBufferSequence& buffers,
      const endpoint_type& destination, socket_base::message_flags flags,
      Handler& handler, const IoExecutor& io_ex)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_socket_sendto_op<ConstBufferSequence,
        endpoint_type, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl.socket_, buffers,
        destination, flags, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((reactor_.context(), *p.p, "socket",
          &impl, impl.socket_, "async_send_to"));

    start_op(impl, reactor::write_op, p.p, is_continuation, true, false);
    p.v = p.p = 0;
  }

  // Start an asynchronous wait until data can be sent without blocking.
  template <typename Handler, typename IoExecutor>
  void async_send_to(implementation_type& impl, const null_buffers&,
      const endpoint_type&, socket_base::message_flags,
      Handler& handler, const IoExecutor& io_ex)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_null_buffers_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((reactor_.context(), *p.p, "socket",
          &impl, impl.socket_, "async_send_to(null_buffers)"));

    start_op(impl, reactor::write_op, p.p, is_continuation, false, false);
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
  size_t receive_from(implementation_type& impl, const null_buffers&,
      endpoint_type& sender_endpoint, socket_base::message_flags,
      boost::system::error_code& ec)
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
      const MutableBufferSequence& buffers, endpoint_type& sender_endpoint,
      socket_base::message_flags flags, Handler& handler,
      const IoExecutor& io_ex)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_socket_recvfrom_op<MutableBufferSequence,
        endpoint_type, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    int protocol = impl.protocol_.type();
    p.p = new (p.v) op(impl.socket_, protocol, buffers,
        sender_endpoint, flags, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((reactor_.context(), *p.p, "socket",
          &impl, impl.socket_, "async_receive_from"));

    start_op(impl,
        (flags & socket_base::message_out_of_band)
          ? reactor::except_op : reactor::read_op,
        p.p, is_continuation, true, false);
    p.v = p.p = 0;
  }

  // Wait until data can be received without blocking.
  template <typename Handler, typename IoExecutor>
  void async_receive_from(implementation_type& impl, const null_buffers&,
      endpoint_type& sender_endpoint, socket_base::message_flags flags,
      Handler& handler, const IoExecutor& io_ex)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_null_buffers_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((reactor_.context(), *p.p, "socket",
          &impl, impl.socket_, "async_receive_from(null_buffers)"));

    // Reset endpoint since it can be given no sensible value at this time.
    sender_endpoint = endpoint_type();

    start_op(impl,
        (flags & socket_base::message_out_of_band)
          ? reactor::except_op : reactor::read_op,
        p.p, is_continuation, false, false);
    p.v = p.p = 0;
  }

  // Accept a new connection.
  template <typename Socket>
  boost::system::error_code accept(implementation_type& impl,
      Socket& peer, endpoint_type* peer_endpoint, boost::system::error_code& ec)
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

  // Start an asynchronous accept. The peer and peer_endpoint objects must be
  // valid until the accept's handler is invoked.
  template <typename Socket, typename Handler, typename IoExecutor>
  void async_accept(implementation_type& impl, Socket& peer,
      endpoint_type* peer_endpoint, Handler& handler, const IoExecutor& io_ex)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_socket_accept_op<Socket, Protocol, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl.socket_, impl.state_, peer,
        impl.protocol_, peer_endpoint, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((reactor_.context(), *p.p, "socket",
          &impl, impl.socket_, "async_accept"));

    start_accept_op(impl, p.p, is_continuation, peer.is_open());
    p.v = p.p = 0;
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  // Start an asynchronous accept. The peer_endpoint object must be valid until
  // the accept's handler is invoked.
  template <typename PeerIoExecutor, typename Handler, typename IoExecutor>
  void async_move_accept(implementation_type& impl,
      const PeerIoExecutor& peer_io_ex, endpoint_type* peer_endpoint,
      Handler& handler, const IoExecutor& io_ex)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_socket_move_accept_op<Protocol,
        PeerIoExecutor, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(peer_io_ex, impl.socket_, impl.state_,
        impl.protocol_, peer_endpoint, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((reactor_.context(), *p.p, "socket",
          &impl, impl.socket_, "async_accept"));

    start_accept_op(impl, p.p, is_continuation, false);
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
      const endpoint_type& peer_endpoint,
      Handler& handler, const IoExecutor& io_ex)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_socket_connect_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl.socket_, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((reactor_.context(), *p.p, "socket",
          &impl, impl.socket_, "async_connect"));

    start_connect_op(impl, p.p, is_continuation,
        peer_endpoint.data(), peer_endpoint.size());
    p.v = p.p = 0;
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_REACTIVE_SOCKET_SERVICE_HPP

/* reactive_socket_service.hpp
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
*/