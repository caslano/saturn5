//
// detail/win_iocp_socket_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_socket_send_op<
        ConstBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    operation* o = p.p = new (p.v) op(
        impl.cancel_token_, buffers, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((context_, *p.p, "socket",
          &impl, impl.socket_, "async_send_to"));

    buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence> bufs(buffers);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
      o = &slot.template emplace<iocp_op_cancellation>(impl.socket_, o);

    start_send_to_op(impl, bufs.buffers(), bufs.count(),
        destination.data(), static_cast<int>(destination.size()),
        flags, o);
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
    reactor_op* o = p.p = new (p.v) op(impl.cancel_token_, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((context_, *p.p, "socket",
          &impl, impl.socket_, "async_send_to(null_buffers)"));

    start_reactor_op(impl, select_reactor::write_op, o);
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
    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_socket_recvfrom_op<MutableBufferSequence,
        endpoint_type, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    operation* o = p.p = new (p.v) op(sender_endp,
        impl.cancel_token_, buffers, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((context_, *p.p, "socket",
          &impl, impl.socket_, "async_receive_from"));

    buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs(buffers);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
      o = &slot.template emplace<iocp_op_cancellation>(impl.socket_, o);

    start_receive_from_op(impl, bufs.buffers(), bufs.count(),
        sender_endp.data(), flags, &p.p->endpoint_size(), o);
    p.v = p.p = 0;
  }

  // Wait until data can be received without blocking.
  template <typename Handler, typename IoExecutor>
  void async_receive_from(implementation_type& impl, const null_buffers&,
      endpoint_type& sender_endpoint, socket_base::message_flags flags,
      Handler& handler, const IoExecutor& io_ex)
  {
    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_null_buffers_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl.cancel_token_, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((context_, *p.p, "socket",
          &impl, impl.socket_, "async_receive_from(null_buffers)"));

    // Reset endpoint since it can be given no sensible value at this time.
    sender_endpoint = endpoint_type();

    // Optionally register for per-operation cancellation.
    operation* iocp_op = p.p;
    if (slot.is_connected())
    {
      p.p->cancellation_key_ = iocp_op =
        &slot.template emplace<reactor_op_cancellation>(
            impl.socket_, iocp_op);
    }

    int op_type = start_null_buffers_receive_op(impl, flags, p.p, iocp_op);
    p.v = p.p = 0;

    // Update cancellation method if the reactor was used.
    if (slot.is_connected() && op_type != -1)
    {
      static_cast<reactor_op_cancellation*>(iocp_op)->use_reactor(
          &get_reactor(), &impl.reactor_data_, op_type);
    }
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
    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_socket_accept_op<Socket,
        protocol_type, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    bool enable_connection_aborted =
      (impl.state_ & socket_ops::enable_connection_aborted) != 0;
    operation* o = p.p = new (p.v) op(*this, impl.socket_, peer, impl.protocol_,
        peer_endpoint, enable_connection_aborted, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((context_, *p.p, "socket",
          &impl, impl.socket_, "async_accept"));

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      accept_op_cancellation* c =
        &slot.template emplace<accept_op_cancellation>(impl.socket_, o);
      p.p->enable_cancellation(c->get_cancel_requested(), c);
      o = c;
    }

    start_accept_op(impl, peer.is_open(), p.p->new_socket(),
        impl.protocol_.family(), impl.protocol_.type(),
        impl.protocol_.protocol(), p.p->output_buffer(),
        p.p->address_length(), o);
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
    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_socket_move_accept_op<
        protocol_type, PeerIoExecutor, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    bool enable_connection_aborted =
      (impl.state_ & socket_ops::enable_connection_aborted) != 0;
    operation* o = p.p = new (p.v) op(*this, impl.socket_, impl.protocol_,
        peer_io_ex, peer_endpoint, enable_connection_aborted,
        handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((context_, *p.p, "socket",
          &impl, impl.socket_, "async_accept"));

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      accept_op_cancellation* c =
        &slot.template emplace<accept_op_cancellation>(impl.socket_, o);
      p.p->enable_cancellation(c->get_cancel_requested(), c);
      o = c;
    }

    start_accept_op(impl, false, p.p->new_socket(),
        impl.protocol_.family(), impl.protocol_.type(),
        impl.protocol_.protocol(), p.p->output_buffer(),
        p.p->address_length(), o);
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
    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_socket_connect_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl.socket_, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((context_, *p.p, "socket",
          &impl, impl.socket_, "async_connect"));

    // Optionally register for per-operation cancellation.
    operation* iocp_op = p.p;
    if (slot.is_connected())
    {
      p.p->cancellation_key_ = iocp_op =
        &slot.template emplace<reactor_op_cancellation>(
            impl.socket_, iocp_op);
    }

    int op_type = start_connect_op(impl, impl.protocol_.family(),
        impl.protocol_.type(), peer_endpoint.data(),
        static_cast<int>(peer_endpoint.size()), p.p, iocp_op);
    p.v = p.p = 0;

    // Update cancellation method if the reactor was used.
    if (slot.is_connected() && op_type != -1)
    {
      static_cast<reactor_op_cancellation*>(iocp_op)->use_reactor(
          &get_reactor(), &impl.reactor_data_, op_type);
    }
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