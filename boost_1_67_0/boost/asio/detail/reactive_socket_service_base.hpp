//
// detail/reactive_socket_service_base.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTIVE_SOCKET_SERVICE_BASE_HPP
#define BOOST_ASIO_DETAIL_REACTIVE_SOCKET_SERVICE_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_IOCP) \
  && !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/buffer.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/socket_base.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/reactive_null_buffers_op.hpp>
#include <boost/asio/detail/reactive_socket_recv_op.hpp>
#include <boost/asio/detail/reactive_socket_recvmsg_op.hpp>
#include <boost/asio/detail/reactive_socket_send_op.hpp>
#include <boost/asio/detail/reactive_wait_op.hpp>
#include <boost/asio/detail/reactor.hpp>
#include <boost/asio/detail/reactor_op.hpp>
#include <boost/asio/detail/socket_holder.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class reactive_socket_service_base
{
public:
  // The native type of a socket.
  typedef socket_type native_handle_type;

  // The implementation type of the socket.
  struct base_implementation_type
  {
    // The native socket representation.
    socket_type socket_;

    // The current state of the socket.
    socket_ops::state_type state_;

    // Per-descriptor data used by the reactor.
    reactor::per_descriptor_data reactor_data_;
  };

  // Constructor.
  BOOST_ASIO_DECL reactive_socket_service_base(execution_context& context);

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void base_shutdown();

  // Construct a new socket implementation.
  BOOST_ASIO_DECL void construct(base_implementation_type& impl);

  // Move-construct a new socket implementation.
  BOOST_ASIO_DECL void base_move_construct(base_implementation_type& impl,
      base_implementation_type& other_impl) BOOST_ASIO_NOEXCEPT;

  // Move-assign from another socket implementation.
  BOOST_ASIO_DECL void base_move_assign(base_implementation_type& impl,
      reactive_socket_service_base& other_service,
      base_implementation_type& other_impl);

  // Destroy a socket implementation.
  BOOST_ASIO_DECL void destroy(base_implementation_type& impl);

  // Determine whether the socket is open.
  bool is_open(const base_implementation_type& impl) const
  {
    return impl.socket_ != invalid_socket;
  }

  // Destroy a socket implementation.
  BOOST_ASIO_DECL boost::system::error_code close(
      base_implementation_type& impl, boost::system::error_code& ec);

  // Release ownership of the socket.
  BOOST_ASIO_DECL socket_type release(
      base_implementation_type& impl, boost::system::error_code& ec);

  // Get the native socket representation.
  native_handle_type native_handle(base_implementation_type& impl)
  {
    return impl.socket_;
  }

  // Cancel all operations associated with the socket.
  BOOST_ASIO_DECL boost::system::error_code cancel(
      base_implementation_type& impl, boost::system::error_code& ec);

  // Determine whether the socket is at the out-of-band data mark.
  bool at_mark(const base_implementation_type& impl,
      boost::system::error_code& ec) const
  {
    return socket_ops::sockatmark(impl.socket_, ec);
  }

  // Determine the number of bytes available for reading.
  std::size_t available(const base_implementation_type& impl,
      boost::system::error_code& ec) const
  {
    return socket_ops::available(impl.socket_, ec);
  }

  // Place the socket into the state where it will listen for new connections.
  boost::system::error_code listen(base_implementation_type& impl,
      int backlog, boost::system::error_code& ec)
  {
    socket_ops::listen(impl.socket_, backlog, ec);
    return ec;
  }

  // Perform an IO control command on the socket.
  template <typename IO_Control_Command>
  boost::system::error_code io_control(base_implementation_type& impl,
      IO_Control_Command& command, boost::system::error_code& ec)
  {
    socket_ops::ioctl(impl.socket_, impl.state_, command.name(),
        static_cast<ioctl_arg_type*>(command.data()), ec);
    return ec;
  }

  // Gets the non-blocking mode of the socket.
  bool non_blocking(const base_implementation_type& impl) const
  {
    return (impl.state_ & socket_ops::user_set_non_blocking) != 0;
  }

  // Sets the non-blocking mode of the socket.
  boost::system::error_code non_blocking(base_implementation_type& impl,
      bool mode, boost::system::error_code& ec)
  {
    socket_ops::set_user_non_blocking(impl.socket_, impl.state_, mode, ec);
    return ec;
  }

  // Gets the non-blocking mode of the native socket implementation.
  bool native_non_blocking(const base_implementation_type& impl) const
  {
    return (impl.state_ & socket_ops::internal_non_blocking) != 0;
  }

  // Sets the non-blocking mode of the native socket implementation.
  boost::system::error_code native_non_blocking(base_implementation_type& impl,
      bool mode, boost::system::error_code& ec)
  {
    socket_ops::set_internal_non_blocking(impl.socket_, impl.state_, mode, ec);
    return ec;
  }

  // Wait for the socket to become ready to read, ready to write, or to have
  // pending error conditions.
  boost::system::error_code wait(base_implementation_type& impl,
      socket_base::wait_type w, boost::system::error_code& ec)
  {
    switch (w)
    {
    case socket_base::wait_read:
      socket_ops::poll_read(impl.socket_, impl.state_, -1, ec);
      break;
    case socket_base::wait_write:
      socket_ops::poll_write(impl.socket_, impl.state_, -1, ec);
      break;
    case socket_base::wait_error:
      socket_ops::poll_error(impl.socket_, impl.state_, -1, ec);
      break;
    default:
      ec = boost::asio::error::invalid_argument;
      break;
    }

    return ec;
  }

  // Asynchronously wait for the socket to become ready to read, ready to
  // write, or to have pending error conditions.
  template <typename Handler, typename IoExecutor>
  void async_wait(base_implementation_type& impl,
      socket_base::wait_type w, Handler& handler, const IoExecutor& io_ex)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_wait_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((reactor_.context(), *p.p, "socket",
          &impl, impl.socket_, "async_wait"));

    int op_type;
    switch (w)
    {
      case socket_base::wait_read:
        op_type = reactor::read_op;
        break;
      case socket_base::wait_write:
        op_type = reactor::write_op;
        break;
      case socket_base::wait_error:
        op_type = reactor::except_op;
        break;
      default:
        p.p->ec_ = boost::asio::error::invalid_argument;
        reactor_.post_immediate_completion(p.p, is_continuation);
        p.v = p.p = 0;
        return;
    }

    start_op(impl, op_type, p.p, is_continuation, false, false);
    p.v = p.p = 0;
  }

  // Send the given data to the peer.
  template <typename ConstBufferSequence>
  size_t send(base_implementation_type& impl,
      const ConstBufferSequence& buffers,
      socket_base::message_flags flags, boost::system::error_code& ec)
  {
    buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence> bufs(buffers);

    return socket_ops::sync_send(impl.socket_, impl.state_,
        bufs.buffers(), bufs.count(), flags, bufs.all_empty(), ec);
  }

  // Wait until data can be sent without blocking.
  size_t send(base_implementation_type& impl, const null_buffers&,
      socket_base::message_flags, boost::system::error_code& ec)
  {
    // Wait for socket to become ready.
    socket_ops::poll_write(impl.socket_, impl.state_, -1, ec);

    return 0;
  }

  // Start an asynchronous send. The data being sent must be valid for the
  // lifetime of the asynchronous operation.
  template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
  void async_send(base_implementation_type& impl,
      const ConstBufferSequence& buffers, socket_base::message_flags flags,
      Handler& handler, const IoExecutor& io_ex)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_socket_send_op<
        ConstBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl.socket_, impl.state_,
        buffers, flags, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((reactor_.context(), *p.p, "socket",
          &impl, impl.socket_, "async_send"));

    start_op(impl, reactor::write_op, p.p, is_continuation, true,
        ((impl.state_ & socket_ops::stream_oriented)
          && buffer_sequence_adapter<boost::asio::const_buffer,
            ConstBufferSequence>::all_empty(buffers)));
    p.v = p.p = 0;
  }

  // Start an asynchronous wait until data can be sent without blocking.
  template <typename Handler, typename IoExecutor>
  void async_send(base_implementation_type& impl, const null_buffers&,
      socket_base::message_flags, Handler& handler, const IoExecutor& io_ex)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_null_buffers_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((reactor_.context(), *p.p, "socket",
          &impl, impl.socket_, "async_send(null_buffers)"));

    start_op(impl, reactor::write_op, p.p, is_continuation, false, false);
    p.v = p.p = 0;
  }

  // Receive some data from the peer. Returns the number of bytes received.
  template <typename MutableBufferSequence>
  size_t receive(base_implementation_type& impl,
      const MutableBufferSequence& buffers,
      socket_base::message_flags flags, boost::system::error_code& ec)
  {
    buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs(buffers);

    return socket_ops::sync_recv(impl.socket_, impl.state_,
        bufs.buffers(), bufs.count(), flags, bufs.all_empty(), ec);
  }

  // Wait until data can be received without blocking.
  size_t receive(base_implementation_type& impl, const null_buffers&,
      socket_base::message_flags, boost::system::error_code& ec)
  {
    // Wait for socket to become ready.
    socket_ops::poll_read(impl.socket_, impl.state_, -1, ec);

    return 0;
  }

  // Start an asynchronous receive. The buffer for the data being received
  // must be valid for the lifetime of the asynchronous operation.
  template <typename MutableBufferSequence,
      typename Handler, typename IoExecutor>
  void async_receive(base_implementation_type& impl,
      const MutableBufferSequence& buffers, socket_base::message_flags flags,
      Handler& handler, const IoExecutor& io_ex)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_socket_recv_op<
        MutableBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl.socket_, impl.state_,
        buffers, flags, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((reactor_.context(), *p.p, "socket",
          &impl, impl.socket_, "async_receive"));

    start_op(impl,
        (flags & socket_base::message_out_of_band)
          ? reactor::except_op : reactor::read_op,
        p.p, is_continuation,
        (flags & socket_base::message_out_of_band) == 0,
        ((impl.state_ & socket_ops::stream_oriented)
          && buffer_sequence_adapter<boost::asio::mutable_buffer,
            MutableBufferSequence>::all_empty(buffers)));
    p.v = p.p = 0;
  }

  // Wait until data can be received without blocking.
  template <typename Handler, typename IoExecutor>
  void async_receive(base_implementation_type& impl,
      const null_buffers&, socket_base::message_flags flags,
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
          &impl, impl.socket_, "async_receive(null_buffers)"));

    start_op(impl,
        (flags & socket_base::message_out_of_band)
          ? reactor::except_op : reactor::read_op,
        p.p, is_continuation, false, false);
    p.v = p.p = 0;
  }

  // Receive some data with associated flags. Returns the number of bytes
  // received.
  template <typename MutableBufferSequence>
  size_t receive_with_flags(base_implementation_type& impl,
      const MutableBufferSequence& buffers,
      socket_base::message_flags in_flags,
      socket_base::message_flags& out_flags, boost::system::error_code& ec)
  {
    buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs(buffers);

    return socket_ops::sync_recvmsg(impl.socket_, impl.state_,
        bufs.buffers(), bufs.count(), in_flags, out_flags, ec);
  }

  // Wait until data can be received without blocking.
  size_t receive_with_flags(base_implementation_type& impl,
      const null_buffers&, socket_base::message_flags,
      socket_base::message_flags& out_flags, boost::system::error_code& ec)
  {
    // Wait for socket to become ready.
    socket_ops::poll_read(impl.socket_, impl.state_, -1, ec);

    // Clear out_flags, since we cannot give it any other sensible value when
    // performing a null_buffers operation.
    out_flags = 0;

    return 0;
  }

  // Start an asynchronous receive. The buffer for the data being received
  // must be valid for the lifetime of the asynchronous operation.
  template <typename MutableBufferSequence,
      typename Handler, typename IoExecutor>
  void async_receive_with_flags(base_implementation_type& impl,
      const MutableBufferSequence& buffers, socket_base::message_flags in_flags,
      socket_base::message_flags& out_flags, Handler& handler,
      const IoExecutor& io_ex)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_socket_recvmsg_op<
        MutableBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl.socket_, buffers,
        in_flags, out_flags, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((reactor_.context(), *p.p, "socket",
          &impl, impl.socket_, "async_receive_with_flags"));

    start_op(impl,
        (in_flags & socket_base::message_out_of_band)
          ? reactor::except_op : reactor::read_op,
        p.p, is_continuation,
        (in_flags & socket_base::message_out_of_band) == 0, false);
    p.v = p.p = 0;
  }

  // Wait until data can be received without blocking.
  template <typename Handler, typename IoExecutor>
  void async_receive_with_flags(base_implementation_type& impl,
      const null_buffers&, socket_base::message_flags in_flags,
      socket_base::message_flags& out_flags, Handler& handler,
      const IoExecutor& io_ex)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_null_buffers_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((reactor_.context(), *p.p, "socket",
          &impl, impl.socket_, "async_receive_with_flags(null_buffers)"));

    // Clear out_flags, since we cannot give it any other sensible value when
    // performing a null_buffers operation.
    out_flags = 0;

    start_op(impl,
        (in_flags & socket_base::message_out_of_band)
          ? reactor::except_op : reactor::read_op,
        p.p, is_continuation, false, false);
    p.v = p.p = 0;
  }

protected:
  // Open a new socket implementation.
  BOOST_ASIO_DECL boost::system::error_code do_open(
      base_implementation_type& impl, int af,
      int type, int protocol, boost::system::error_code& ec);

  // Assign a native socket to a socket implementation.
  BOOST_ASIO_DECL boost::system::error_code do_assign(
      base_implementation_type& impl, int type,
      const native_handle_type& native_socket, boost::system::error_code& ec);

  // Start the asynchronous read or write operation.
  BOOST_ASIO_DECL void start_op(base_implementation_type& impl, int op_type,
      reactor_op* op, bool is_continuation, bool is_non_blocking, bool noop);

  // Start the asynchronous accept operation.
  BOOST_ASIO_DECL void start_accept_op(base_implementation_type& impl,
      reactor_op* op, bool is_continuation, bool peer_is_open);

  // Start the asynchronous connect operation.
  BOOST_ASIO_DECL void start_connect_op(base_implementation_type& impl,
      reactor_op* op, bool is_continuation,
      const socket_addr_type* addr, size_t addrlen);

  // The selector that performs event demultiplexing for the service.
  reactor& reactor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/reactive_socket_service_base.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // !defined(BOOST_ASIO_HAS_IOCP)
       //   && !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_REACTIVE_SOCKET_SERVICE_BASE_HPP

/* reactive_socket_service_base.hpp
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
*/