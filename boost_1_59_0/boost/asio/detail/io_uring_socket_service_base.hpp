//
// detail/io_uring_socket_service_base.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IO_URING_SOCKET_SERVICE_BASE_HPP
#define BOOST_ASIO_DETAIL_IO_URING_SOCKET_SERVICE_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IO_URING)

#include <boost/asio/associated_cancellation_slot.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/cancellation_type.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/socket_base.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/io_uring_null_buffers_op.hpp>
#include <boost/asio/detail/io_uring_service.hpp>
#include <boost/asio/detail/io_uring_socket_recv_op.hpp>
#include <boost/asio/detail/io_uring_socket_recvmsg_op.hpp>
#include <boost/asio/detail/io_uring_socket_send_op.hpp>
#include <boost/asio/detail/io_uring_wait_op.hpp>
#include <boost/asio/detail/socket_holder.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class io_uring_socket_service_base
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

    // Per I/O object data used by the io_uring_service.
    io_uring_service::per_io_object_data io_object_data_;
  };

  // Constructor.
  BOOST_ASIO_DECL io_uring_socket_service_base(execution_context& context);

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void base_shutdown();

  // Construct a new socket implementation.
  BOOST_ASIO_DECL void construct(base_implementation_type& impl);

  // Move-construct a new socket implementation.
  BOOST_ASIO_DECL void base_move_construct(base_implementation_type& impl,
      base_implementation_type& other_impl) BOOST_ASIO_NOEXCEPT;

  // Move-assign from another socket implementation.
  BOOST_ASIO_DECL void base_move_assign(base_implementation_type& impl,
      io_uring_socket_service_base& other_service,
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

    int op_type;
    int poll_flags;
    switch (w)
    {
    case socket_base::wait_read:
      op_type = io_uring_service::read_op;
      poll_flags = POLLIN;
      break;
    case socket_base::wait_write:
      op_type = io_uring_service::write_op;
      poll_flags = POLLOUT;
      break;
    case socket_base::wait_error:
      op_type = io_uring_service::except_op;
      poll_flags = POLLPRI | POLLERR | POLLHUP;
      break;
    default:
      op_type = -1;
      poll_flags = -1;
      return;
    }

    // Allocate and construct an operation to wrap the handler.
    typedef io_uring_wait_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.socket_,
        poll_flags, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((io_uring_service_.context(), *p.p,
          "socket", &impl, impl.socket_, "async_wait"));

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<io_uring_op_cancellation>(
            &io_uring_service_, &impl.io_object_data_, op_type);
    }

    start_op(impl, op_type, p.p, is_continuation, op_type == -1);
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
    typedef io_uring_socket_send_op<
        ConstBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.socket_,
        impl.state_, buffers, flags, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<io_uring_op_cancellation>(&io_uring_service_,
            &impl.io_object_data_, io_uring_service::write_op);
    }

    BOOST_ASIO_HANDLER_CREATION((io_uring_service_.context(), *p.p,
          "socket", &impl, impl.socket_, "async_send"));

    start_op(impl, io_uring_service::write_op, p.p, is_continuation,
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

    BOOST_ASIO_HANDLER_CREATION((io_uring_service_.context(), *p.p,
          "socket", &impl, impl.socket_, "async_send(null_buffers)"));

    start_op(impl, io_uring_service::write_op, p.p, is_continuation, false);
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

    int op_type = (flags & socket_base::message_out_of_band)
      ? io_uring_service::except_op : io_uring_service::read_op;

    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef io_uring_socket_recv_op<
        MutableBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.socket_,
        impl.state_, buffers, flags, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<io_uring_op_cancellation>(
            &io_uring_service_, &impl.io_object_data_, op_type);
    }

    BOOST_ASIO_HANDLER_CREATION((io_uring_service_.context(), *p.p,
          "socket", &impl, impl.socket_, "async_receive"));

    start_op(impl, op_type, p.p, is_continuation,
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

    BOOST_ASIO_HANDLER_CREATION((io_uring_service_.context(), *p.p,
          "socket", &impl, impl.socket_, "async_receive(null_buffers)"));

    start_op(impl, op_type, p.p, is_continuation, false);
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

    int op_type = (in_flags & socket_base::message_out_of_band)
      ? io_uring_service::except_op : io_uring_service::read_op;

    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef io_uring_socket_recvmsg_op<
        MutableBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.socket_, impl.state_,
        buffers, in_flags, out_flags, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<io_uring_op_cancellation>(
            &io_uring_service_, &impl.io_object_data_, op_type);
    }

    BOOST_ASIO_HANDLER_CREATION((io_uring_service_.context(), *p.p,
          "socket", &impl, impl.socket_, "async_receive_with_flags"));

    start_op(impl, op_type, p.p, is_continuation, false);
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

    int op_type;
    int poll_flags;
    if ((in_flags & socket_base::message_out_of_band) != 0)
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
          &impl, impl.socket_, "async_receive_with_flags(null_buffers)"));

    // Clear out_flags, since we cannot give it any other sensible value when
    // performing a null_buffers operation.
    out_flags = 0;

    start_op(impl, op_type, p.p, is_continuation, false);
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
      io_uring_operation* op, bool is_continuation, bool noop);

  // Start the asynchronous accept operation.
  BOOST_ASIO_DECL void start_accept_op(base_implementation_type& impl,
      io_uring_operation* op, bool is_continuation, bool peer_is_open);

  // Helper class used to implement per-operation cancellation
  class io_uring_op_cancellation
  {
  public:
    io_uring_op_cancellation(io_uring_service* s,
        io_uring_service::per_io_object_data* p, int o)
      : io_uring_service_(s),
        io_object_data_(p),
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
        io_uring_service_->cancel_ops_by_key(*io_object_data_, op_type_, this);
      }
    }

  private:
    io_uring_service* io_uring_service_;
    io_uring_service::per_io_object_data* io_object_data_;
    int op_type_;
  };

  // The io_uring_service that performs event demultiplexing for the service.
  io_uring_service& io_uring_service_;

  // Cached success value to avoid accessing category singleton.
  const boost::system::error_code success_ec_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/io_uring_socket_service_base.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_IO_URING)

#endif // BOOST_ASIO_DETAIL_IO_URING_SOCKET_SERVICE_BASE_HPP

/* io_uring_socket_service_base.hpp
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
*/