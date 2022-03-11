//
// detail/win_iocp_socket_service_base.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_SERVICE_BASE_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_SERVICE_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)

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
#include <boost/asio/detail/win_iocp_socket_connect_op.hpp>
#include <boost/asio/detail/win_iocp_socket_send_op.hpp>
#include <boost/asio/detail/win_iocp_socket_recv_op.hpp>
#include <boost/asio/detail/win_iocp_socket_recvmsg_op.hpp>
#include <boost/asio/detail/win_iocp_wait_op.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class win_iocp_socket_service_base
{
public:
  // The implementation type of the socket.
  struct base_implementation_type
  {
    // The native socket representation.
    socket_type socket_;

    // The current state of the socket.
    socket_ops::state_type state_;

    // We use a shared pointer as a cancellation token here to work around the
    // broken Windows support for cancellation. MSDN says that when you call
    // closesocket any outstanding WSARecv or WSASend operations will complete
    // with the error ERROR_OPERATION_ABORTED. In practice they complete with
    // ERROR_NETNAME_DELETED, which means you can't tell the difference between
    // a local cancellation and the socket being hard-closed by the peer.
    socket_ops::shared_cancel_token_type cancel_token_;

    // Per-descriptor data used by the reactor.
    select_reactor::per_descriptor_data reactor_data_;

#if defined(BOOST_ASIO_ENABLE_CANCELIO)
    // The ID of the thread from which it is safe to cancel asynchronous
    // operations. 0 means no asynchronous operations have been started yet.
    // ~0 means asynchronous operations have been started from more than one
    // thread, and cancellation is not supported for the socket.
    DWORD safe_cancellation_thread_id_;
#endif // defined(BOOST_ASIO_ENABLE_CANCELIO)

    // Pointers to adjacent socket implementations in linked list.
    base_implementation_type* next_;
    base_implementation_type* prev_;
  };

  // Constructor.
  BOOST_ASIO_DECL win_iocp_socket_service_base(execution_context& context);

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void base_shutdown();

  // Construct a new socket implementation.
  BOOST_ASIO_DECL void construct(base_implementation_type& impl);

  // Move-construct a new socket implementation.
  BOOST_ASIO_DECL void base_move_construct(base_implementation_type& impl,
      base_implementation_type& other_impl) BOOST_ASIO_NOEXCEPT;

  // Move-assign from another socket implementation.
  BOOST_ASIO_DECL void base_move_assign(base_implementation_type& impl,
      win_iocp_socket_service_base& other_service,
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
    typedef win_iocp_wait_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl.cancel_token_, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((context_, *p.p, "socket",
          &impl, impl.socket_, "async_wait"));

    switch (w)
    {
      case socket_base::wait_read:
        start_null_buffers_receive_op(impl, 0, p.p);
        break;
      case socket_base::wait_write:
        start_reactor_op(impl, select_reactor::write_op, p.p);
        break;
      case socket_base::wait_error:
        start_reactor_op(impl, select_reactor::except_op, p.p);
        break;
      default:
        p.p->ec_ = boost::asio::error::invalid_argument;
        iocp_service_.post_immediate_completion(p.p, is_continuation);
        break;
    }

    p.v = p.p = 0;
  }

  // Send the given data to the peer. Returns the number of bytes sent.
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
    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_socket_send_op<
        ConstBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl.cancel_token_, buffers, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((context_, *p.p, "socket",
          &impl, impl.socket_, "async_send"));

    buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence> bufs(buffers);

    start_send_op(impl, bufs.buffers(), bufs.count(), flags,
        (impl.state_ & socket_ops::stream_oriented) != 0 && bufs.all_empty(),
        p.p);
    p.v = p.p = 0;
  }

  // Start an asynchronous wait until data can be sent without blocking.
  template <typename Handler, typename IoExecutor>
  void async_send(base_implementation_type& impl, const null_buffers&,
      socket_base::message_flags, Handler& handler, const IoExecutor& io_ex)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_null_buffers_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl.cancel_token_, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((context_, *p.p, "socket",
          &impl, impl.socket_, "async_send(null_buffers)"));

    start_reactor_op(impl, select_reactor::write_op, p.p);
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
    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_socket_recv_op<
        MutableBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl.state_, impl.cancel_token_,
        buffers, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((context_, *p.p, "socket",
          &impl, impl.socket_, "async_receive"));

    buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs(buffers);

    start_receive_op(impl, bufs.buffers(), bufs.count(), flags,
        (impl.state_ & socket_ops::stream_oriented) != 0 && bufs.all_empty(),
        p.p);
    p.v = p.p = 0;
  }

  // Wait until data can be received without blocking.
  template <typename Handler, typename IoExecutor>
  void async_receive(base_implementation_type& impl,
      const null_buffers&, socket_base::message_flags flags,
      Handler& handler, const IoExecutor& io_ex)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_null_buffers_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl.cancel_token_, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((context_, *p.p, "socket",
          &impl, impl.socket_, "async_receive(null_buffers)"));

    start_null_buffers_receive_op(impl, flags, p.p);
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
    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_socket_recvmsg_op<
        MutableBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl.cancel_token_,
        buffers, out_flags, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((context_, *p.p, "socket",
          &impl, impl.socket_, "async_receive_with_flags"));

    buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs(buffers);

    start_receive_op(impl, bufs.buffers(), bufs.count(), in_flags, false, p.p);
    p.v = p.p = 0;
  }

  // Wait until data can be received without blocking.
  template <typename Handler, typename IoExecutor>
  void async_receive_with_flags(base_implementation_type& impl,
      const null_buffers&, socket_base::message_flags in_flags,
      socket_base::message_flags& out_flags, Handler& handler,
      const IoExecutor& io_ex)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_null_buffers_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl.cancel_token_, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((context_, *p.p, "socket",
          &impl, impl.socket_, "async_receive_with_flags(null_buffers)"));

    // Reset out_flags since it can be given no sensible value at this time.
    out_flags = 0;

    start_null_buffers_receive_op(impl, in_flags, p.p);
    p.v = p.p = 0;
  }

  // Helper function to restart an asynchronous accept operation.
  BOOST_ASIO_DECL void restart_accept_op(socket_type s,
      socket_holder& new_socket, int family, int type, int protocol,
      void* output_buffer, DWORD address_length, operation* op);

protected:
  // Open a new socket implementation.
  BOOST_ASIO_DECL boost::system::error_code do_open(
      base_implementation_type& impl, int family, int type,
      int protocol, boost::system::error_code& ec);

  // Assign a native socket to a socket implementation.
  BOOST_ASIO_DECL boost::system::error_code do_assign(
      base_implementation_type& impl, int type,
      socket_type native_socket, boost::system::error_code& ec);

  // Helper function to start an asynchronous send operation.
  BOOST_ASIO_DECL void start_send_op(base_implementation_type& impl,
      WSABUF* buffers, std::size_t buffer_count,
      socket_base::message_flags flags, bool noop, operation* op);

  // Helper function to start an asynchronous send_to operation.
  BOOST_ASIO_DECL void start_send_to_op(base_implementation_type& impl,
      WSABUF* buffers, std::size_t buffer_count,
      const socket_addr_type* addr, int addrlen,
      socket_base::message_flags flags, operation* op);

  // Helper function to start an asynchronous receive operation.
  BOOST_ASIO_DECL void start_receive_op(base_implementation_type& impl,
      WSABUF* buffers, std::size_t buffer_count,
      socket_base::message_flags flags, bool noop, operation* op);

  // Helper function to start an asynchronous null_buffers receive operation.
  BOOST_ASIO_DECL void start_null_buffers_receive_op(
      base_implementation_type& impl,
      socket_base::message_flags flags, reactor_op* op);

  // Helper function to start an asynchronous receive_from operation.
  BOOST_ASIO_DECL void start_receive_from_op(base_implementation_type& impl,
      WSABUF* buffers, std::size_t buffer_count, socket_addr_type* addr,
      socket_base::message_flags flags, int* addrlen, operation* op);

  // Helper function to start an asynchronous accept operation.
  BOOST_ASIO_DECL void start_accept_op(base_implementation_type& impl,
      bool peer_is_open, socket_holder& new_socket, int family, int type,
      int protocol, void* output_buffer, DWORD address_length, operation* op);

  // Start an asynchronous read or write operation using the reactor.
  BOOST_ASIO_DECL void start_reactor_op(base_implementation_type& impl,
      int op_type, reactor_op* op);

  // Start the asynchronous connect operation using the reactor.
  BOOST_ASIO_DECL void start_connect_op(base_implementation_type& impl,
      int family, int type, const socket_addr_type* remote_addr,
      std::size_t remote_addrlen, win_iocp_socket_connect_op_base* op);

  // Helper function to close a socket when the associated object is being
  // destroyed.
  BOOST_ASIO_DECL void close_for_destruction(base_implementation_type& impl);

  // Update the ID of the thread from which cancellation is safe.
  BOOST_ASIO_DECL void update_cancellation_thread_id(
      base_implementation_type& impl);

  // Helper function to get the reactor. If no reactor has been created yet, a
  // new one is obtained from the execution context and a pointer to it is
  // cached in this service.
  BOOST_ASIO_DECL select_reactor& get_reactor();

  // The type of a ConnectEx function pointer, as old SDKs may not provide it.
  typedef BOOL (PASCAL *connect_ex_fn)(SOCKET,
      const socket_addr_type*, int, void*, DWORD, DWORD*, OVERLAPPED*);

  // Helper function to get the ConnectEx pointer. If no ConnectEx pointer has
  // been obtained yet, one is obtained using WSAIoctl and the pointer is
  // cached. Returns a null pointer if ConnectEx is not available.
  BOOST_ASIO_DECL connect_ex_fn get_connect_ex(
      base_implementation_type& impl, int type);

  // The type of a NtSetInformationFile function pointer.
  typedef LONG (NTAPI *nt_set_info_fn)(HANDLE, ULONG_PTR*, void*, ULONG, ULONG);

  // Helper function to get the NtSetInformationFile function pointer. If no
  // NtSetInformationFile pointer has been obtained yet, one is obtained using
  // GetProcAddress and the pointer is cached. Returns a null pointer if
  // NtSetInformationFile is not available.
  BOOST_ASIO_DECL nt_set_info_fn get_nt_set_info();

  // Helper function to emulate InterlockedCompareExchangePointer functionality
  // for:
  // - very old Platform SDKs; and
  // - platform SDKs where MSVC's /Wp64 option causes spurious warnings.
  BOOST_ASIO_DECL void* interlocked_compare_exchange_pointer(
      void** dest, void* exch, void* cmp);

  // Helper function to emulate InterlockedExchangePointer functionality for:
  // - very old Platform SDKs; and
  // - platform SDKs where MSVC's /Wp64 option causes spurious warnings.
  BOOST_ASIO_DECL void* interlocked_exchange_pointer(void** dest, void* val);

  // The execution context used to obtain the reactor, if required.
  execution_context& context_;

  // The IOCP service used for running asynchronous operations and dispatching
  // handlers.
  win_iocp_io_context& iocp_service_;

  // The reactor used for performing connect operations. This object is created
  // only if needed.
  select_reactor* reactor_;

  // Pointer to ConnectEx implementation.
  void* connect_ex_;

  // Pointer to NtSetInformationFile implementation.
  void* nt_set_info_;

  // Mutex to protect access to the linked list of implementations. 
  boost::asio::detail::mutex mutex_;

  // The head of a linked list of all implementations.
  base_implementation_type* impl_list_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/win_iocp_socket_service_base.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_SERVICE_BASE_HPP

/* win_iocp_socket_service_base.hpp
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
*/