//
// detail/io_uring_socket_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IO_URING_SOCKET_SERVICE_HPP
#define BOOST_ASIO_DETAIL_IO_URING_SOCKET_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IO_URING)

#include <boost/asio/buffer.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/socket_base.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/io_uring_null_buffers_op.hpp>
#include <boost/asio/detail/io_uring_service.hpp>
#include <boost/asio/detail/io_uring_socket_accept_op.hpp>
#include <boost/asio/detail/io_uring_socket_connect_op.hpp>
#include <boost/asio/detail/io_uring_socket_recvfrom_op.hpp>
#include <boost/asio/detail/io_uring_socket_sendto_op.hpp>
#include <boost/asio/detail/io_uring_socket_service_base.hpp>
#include <boost/asio/detail/socket_holder.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Protocol>
class io_uring_socket_service :
  public execution_context_service_base<io_uring_socket_service<Protocol> >,
  public io_uring_socket_service_base
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
    io_uring_socket_service_base::base_implementation_type
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
  io_uring_socket_service(execution_context& context)
    : execution_context_service_base<
        io_uring_socket_service<Protocol> >(context),
      io_uring_socket_service_base(context)
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
      io_uring_socket_service_base& other_service,
      implementation_type& other_impl)
  {
    this->base_move_assign(impl, other_service, other_impl);

    impl.protocol_ = other_impl.protocol_;
    other_impl.protocol_ = endpoint_type().protocol();
  }

  // Move-construct a new socket implementation from another protocol type.
  template <typename Protocol1>
  void converting_move_construct(implementation_type& impl,
      io_uring_socket_service<Protocol1>&,
      typename io_uring_socket_service<
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
    typedef io_uring_socket_sendto_op<ConstBufferSequence,
        endpoint_type, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.socket_, impl.state_,
        buffers, destination, flags, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<io_uring_op_cancellation>(&io_uring_service_,
            &impl.io_object_data_, io_uring_service::write_op);
    }

    BOOST_ASIO_HANDLER_CREATION((io_uring_service_.context(), *p.p,
          "socket", &impl, impl.socket_, "async_send_to"));

    start_op(impl, io_uring_service::write_op, p.p, is_continuation, false);
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
    typedef io_uring_null_buffers_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.socket_, POLLOUT, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<io_uring_op_cancellation>(&io_uring_service_,
            &impl.io_object_data_, io_uring_service::write_op);
    }

    BOOST_ASIO_HANDLER_CREATION((io_uring_service_.context(), *p.p, "socket",
          &impl, impl.socket_, "async_send_to(null_buffers)"));

    start_op(impl, io_uring_service::write_op, p.p, is_continuation, false);
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

    int op_type = (flags & socket_base::message_out_of_band)
      ? io_uring_service::except_op : io_uring_service::read_op;

    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef io_uring_socket_recvfrom_op<MutableBufferSequence,
        endpoint_type, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.socket_, impl.state_,
        buffers, sender_endpoint, flags, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<io_uring_op_cancellation>(
            &io_uring_service_, &impl.io_object_data_, op_type);
    }

    BOOST_ASIO_HANDLER_CREATION((io_uring_service_.context(), *p.p,
          "socket", &impl, impl.socket_, "async_receive_from"));

    start_op(impl, op_type, p.p, is_continuation, false);
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

    int op_type;
    int poll_flags;
    if ((flags & socket_base::message_out_of_band) != 0)
    {
      op_type = io_uring_service::except_op;
      poll_flags = POLLPRI;
    }
    else
    {
      op_type = io_uring_service::read_op;
      poll_flags = POLLIN;
    }

    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef io_uring_null_buffers_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.socket_, poll_flags, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<io_uring_op_cancellation>(
            &io_uring_service_, &impl.io_object_data_, op_type);
    }

    BOOST_ASIO_HANDLER_CREATION((io_uring_service_.context(), *p.p, "socket",
          &impl, impl.socket_, "async_receive_from(null_buffers)"));

    // Reset endpoint since it can be given no sensible value at this time.
    sender_endpoint = endpoint_type();

    start_op(impl, op_type, p.p, is_continuation, false);
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
    typedef io_uring_socket_accept_op<Socket, Protocol, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.socket_, impl.state_,
        peer, impl.protocol_, peer_endpoint, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected() && !peer.is_open())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<io_uring_op_cancellation>(&io_uring_service_,
            &impl.io_object_data_, io_uring_service::read_op);
    }

    BOOST_ASIO_HANDLER_CREATION((io_uring_service_.context(), *p.p,
          "socket", &impl, impl.socket_, "async_accept"));

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
    typedef io_uring_socket_move_accept_op<Protocol,
        PeerIoExecutor, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, peer_io_ex, impl.socket_,
        impl.state_, impl.protocol_, peer_endpoint, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<io_uring_op_cancellation>(&io_uring_service_,
            &impl.io_object_data_, io_uring_service::read_op);
    }

    BOOST_ASIO_HANDLER_CREATION((io_uring_service_.context(), *p.p,
          "socket", &impl, impl.socket_, "async_accept"));

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
    typedef io_uring_socket_connect_op<Protocol, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.socket_,
        peer_endpoint, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<io_uring_op_cancellation>(&io_uring_service_,
            &impl.io_object_data_, io_uring_service::write_op);
    }

    BOOST_ASIO_HANDLER_CREATION((io_uring_service_.context(), *p.p,
          "socket", &impl, impl.socket_, "async_connect"));

    start_op(impl, io_uring_service::write_op, p.p, is_continuation, false);
    p.v = p.p = 0;
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IO_URING)

#endif // BOOST_ASIO_DETAIL_IO_URING_SOCKET_SERVICE_HPP

/* io_uring_socket_service.hpp
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
*/