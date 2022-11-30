//
// detail/reactive_socket_service_base.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
  && !defined(BOOST_ASIO_WINDOWS_RUNTIME) \
  && !defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)

#include <boost/asio/associated_cancellation_slot.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/cancellation_type.hpp>
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

    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_wait_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, handler, io_ex);

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

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<reactor_op_cancellation>(
            &reactor_, &impl.reactor_data_, impl.socket_, op_type);
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
    typedef buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence> bufs_type;

    if (bufs_type::is_single_buffer)
    {
      return socket_ops::sync_send1(impl.socket_,
          impl.state_, bufs_type::first(buffers).data(),
          bufs_type::first(buffers).size(), flags, ec);
    }
    else
    {
      bufs_type bufs(buffers);
      return socket_ops::sync_send(impl.socket_, impl.state_,
          bufs.buffers(), bufs.count(), flags, bufs.all_empty(), ec);
    }
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

    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_socket_send_op<
        ConstBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.socket_,
        impl.state_, buffers, flags, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<reactor_op_cancellation>(
            &reactor_, &impl.reactor_data_, impl.socket_, reactor::write_op);
    }

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
    typedef buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs_type;

    if (bufs_type::is_single_buffer)
    {
      return socket_ops::sync_recv1(impl.socket_,
          impl.state_, bufs_type::first(buffers).data(),
          bufs_type::first(buffers).size(), flags, ec);
    }
    else
    {
      bufs_type bufs(buffers);
      return socket_ops::sync_recv(impl.socket_, impl.state_,
          bufs.buffers(), bufs.count(), flags, bufs.all_empty(), ec);
    }
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

    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_socket_recv_op<
        MutableBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.socket_,
        impl.state_, buffers, flags, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<reactor_op_cancellation>(
            &reactor_, &impl.reactor_data_, impl.socket_, reactor::read_op);
    }

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

    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_socket_recvmsg_op<
        MutableBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.socket_,
        buffers, in_flags, out_flags, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<reactor_op_cancellation>(
            &reactor_, &impl.reactor_data_, impl.socket_, reactor::read_op);
    }

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

  // Helper class used to implement per-operation cancellation
  class reactor_op_cancellation
  {
  public:
    reactor_op_cancellation(reactor* r,
        reactor::per_descriptor_data* p, int d, int o)
      : reactor_(r),
        reactor_data_(p),
        descriptor_(d),
        op_type_(o)
    {
    }

    void operator()(cancellation_type_t type)
    {
      if (!!(type &
            (cancellation_type::terminal
              | cancellation_type::partial
              | cancellation_type::total)))
      {
        reactor_->cancel_ops_by_key(descriptor_,
            *reactor_data_, op_type_, this);
      }
    }

  private:
    reactor* reactor_;
    reactor::per_descriptor_data* reactor_data_;
    int descriptor_;
    int op_type_;
  };

  // The selector that performs event demultiplexing for the service.
  reactor& reactor_;

  // Cached success value to avoid accessing category singleton.
  const boost::system::error_code success_ec_;
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
       //   && !defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)

#endif // BOOST_ASIO_DETAIL_REACTIVE_SOCKET_SERVICE_BASE_HPP

/* reactive_socket_service_base.hpp
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
*/