//
// detail/reactive_socket_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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

#if !defined(BOOST_ASIO_HAS_IOCP) \
  && !defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)

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
    typedef buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence> bufs_type;

    if (bufs_type::is_single_buffer)
    {
      return socket_ops::sync_sendto1(impl.socket_, impl.state_,
          bufs_type::first(buffers).data(),
          bufs_type::first(buffers).size(), flags,
          destination.data(), destination.size(), ec);
    }
    else
    {
      bufs_type bufs(buffers);
      return socket_ops::sync_sendto(impl.socket_, impl.state_,
          bufs.buffers(), bufs.count(), flags,
          destination.data(), destination.size(), ec);
    }
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

    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_socket_sendto_op<ConstBufferSequence,
        endpoint_type, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.socket_,
        buffers, destination, flags, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<reactor_op_cancellation>(
            &reactor_, &impl.reactor_data_, impl.socket_, reactor::write_op);
    }

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

    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_null_buffers_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<reactor_op_cancellation>(
            &reactor_, &impl.reactor_data_, impl.socket_, reactor::write_op);
    }

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
    typedef buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs_type;

    std::size_t addr_len = sender_endpoint.capacity();
    std::size_t bytes_recvd;
    if (bufs_type::is_single_buffer)
    {
      bytes_recvd = socket_ops::sync_recvfrom1(impl.socket_,
          impl.state_, bufs_type::first(buffers).data(),
          bufs_type::first(buffers).size(), flags,
          sender_endpoint.data(), &addr_len, ec);
    }
    else
    {
      bufs_type bufs(buffers);
      bytes_recvd = socket_ops::sync_recvfrom(
          impl.socket_, impl.state_, bufs.buffers(), bufs.count(),
          flags, sender_endpoint.data(), &addr_len, ec);
    }

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

    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_socket_recvfrom_op<MutableBufferSequence,
        endpoint_type, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    int protocol = impl.protocol_.type();
    p.p = new (p.v) op(success_ec_, impl.socket_, protocol,
        buffers, sender_endpoint, flags, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<reactor_op_cancellation>(
            &reactor_, &impl.reactor_data_, impl.socket_, reactor::read_op);
    }

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

    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_null_buffers_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<reactor_op_cancellation>(
            &reactor_, &impl.reactor_data_, impl.socket_, reactor::read_op);
    }

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

    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_socket_accept_op<Socket, Protocol, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.socket_, impl.state_,
        peer, impl.protocol_, peer_endpoint, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected() && !peer.is_open())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<reactor_op_cancellation>(
            &reactor_, &impl.reactor_data_, impl.socket_, reactor::read_op);
    }

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

    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_socket_move_accept_op<Protocol,
        PeerIoExecutor, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, peer_io_ex, impl.socket_,
        impl.state_, impl.protocol_, peer_endpoint, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<reactor_op_cancellation>(
            &reactor_, &impl.reactor_data_, impl.socket_, reactor::read_op);
    }

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

    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_socket_connect_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.socket_, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<reactor_op_cancellation>(
            &reactor_, &impl.reactor_data_, impl.socket_, reactor::connect_op);
    }

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
       //   && !defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)

#endif // BOOST_ASIO_DETAIL_REACTIVE_SOCKET_SERVICE_HPP

/* reactive_socket_service.hpp
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
*/