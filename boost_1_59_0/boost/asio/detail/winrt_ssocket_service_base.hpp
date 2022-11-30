//
// detail/winrt_ssocket_service_base.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WINRT_SSOCKET_SERVICE_BASE_HPP
#define BOOST_ASIO_DETAIL_WINRT_SSOCKET_SERVICE_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/buffer.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/socket_base.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/winrt_async_manager.hpp>
#include <boost/asio/detail/winrt_socket_recv_op.hpp>
#include <boost/asio/detail/winrt_socket_send_op.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_io_context.hpp>
#else // defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/scheduler.hpp>
#endif // defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class winrt_ssocket_service_base
{
public:
  // The native type of a socket.
  typedef Windows::Networking::Sockets::StreamSocket^ native_handle_type;

  // The implementation type of the socket.
  struct base_implementation_type
  {
    // Default constructor.
    base_implementation_type()
      : socket_(nullptr),
        next_(0),
        prev_(0)
    {
    }

    // The underlying native socket.
    native_handle_type socket_;

    // Pointers to adjacent socket implementations in linked list.
    base_implementation_type* next_;
    base_implementation_type* prev_;
  };

  // Constructor.
  BOOST_ASIO_DECL winrt_ssocket_service_base(execution_context& context);

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void base_shutdown();

  // Construct a new socket implementation.
  BOOST_ASIO_DECL void construct(base_implementation_type&);

  // Move-construct a new socket implementation.
  BOOST_ASIO_DECL void base_move_construct(base_implementation_type& impl,
      base_implementation_type& other_impl) BOOST_ASIO_NOEXCEPT;

  // Move-assign from another socket implementation.
  BOOST_ASIO_DECL void base_move_assign(base_implementation_type& impl,
      winrt_ssocket_service_base& other_service,
      base_implementation_type& other_impl);

  // Destroy a socket implementation.
  BOOST_ASIO_DECL void destroy(base_implementation_type& impl);

  // Determine whether the socket is open.
  bool is_open(const base_implementation_type& impl) const
  {
    return impl.socket_ != nullptr;
  }

  // Destroy a socket implementation.
  BOOST_ASIO_DECL boost::system::error_code close(
      base_implementation_type& impl, boost::system::error_code& ec);

  // Release ownership of the socket.
  BOOST_ASIO_DECL native_handle_type release(
      base_implementation_type& impl, boost::system::error_code& ec);

  // Get the native socket representation.
  native_handle_type native_handle(base_implementation_type& impl)
  {
    return impl.socket_;
  }

  // Cancel all operations associated with the socket.
  boost::system::error_code cancel(base_implementation_type&,
      boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return ec;
  }

  // Determine whether the socket is at the out-of-band data mark.
  bool at_mark(const base_implementation_type&,
      boost::system::error_code& ec) const
  {
    ec = boost::asio::error::operation_not_supported;
    return false;
  }

  // Determine the number of bytes available for reading.
  std::size_t available(const base_implementation_type&,
      boost::system::error_code& ec) const
  {
    ec = boost::asio::error::operation_not_supported;
    return 0;
  }

  // Perform an IO control command on the socket.
  template <typename IO_Control_Command>
  boost::system::error_code io_control(base_implementation_type&,
      IO_Control_Command&, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return ec;
  }

  // Gets the non-blocking mode of the socket.
  bool non_blocking(const base_implementation_type&) const
  {
    return false;
  }

  // Sets the non-blocking mode of the socket.
  boost::system::error_code non_blocking(base_implementation_type&,
      bool, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return ec;
  }

  // Gets the non-blocking mode of the native socket implementation.
  bool native_non_blocking(const base_implementation_type&) const
  {
    return false;
  }

  // Sets the non-blocking mode of the native socket implementation.
  boost::system::error_code native_non_blocking(base_implementation_type&,
      bool, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return ec;
  }

  // Send the given data to the peer.
  template <typename ConstBufferSequence>
  std::size_t send(base_implementation_type& impl,
      const ConstBufferSequence& buffers,
      socket_base::message_flags flags, boost::system::error_code& ec)
  {
    return do_send(impl,
        buffer_sequence_adapter<boost::asio::const_buffer,
          ConstBufferSequence>::first(buffers), flags, ec);
  }

  // Wait until data can be sent without blocking.
  std::size_t send(base_implementation_type&, const null_buffers&,
      socket_base::message_flags, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
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
    typedef winrt_socket_send_op<ConstBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(buffers, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((scheduler_.context(),
          *p.p, "socket", &impl, 0, "async_send"));

    start_send_op(impl,
        buffer_sequence_adapter<boost::asio::const_buffer,
          ConstBufferSequence>::first(buffers),
        flags, p.p, is_continuation);
    p.v = p.p = 0;
  }

  // Start an asynchronous wait until data can be sent without blocking.
  template <typename Handler, typename IoExecutor>
  void async_send(base_implementation_type&, const null_buffers&,
      socket_base::message_flags, Handler& handler, const IoExecutor& io_ex)
  {
    boost::system::error_code ec = boost::asio::error::operation_not_supported;
    const std::size_t bytes_transferred = 0;
    boost::asio::post(io_ex,
        detail::bind_handler(handler, ec, bytes_transferred));
  }

  // Receive some data from the peer. Returns the number of bytes received.
  template <typename MutableBufferSequence>
  std::size_t receive(base_implementation_type& impl,
      const MutableBufferSequence& buffers,
      socket_base::message_flags flags, boost::system::error_code& ec)
  {
    return do_receive(impl,
        buffer_sequence_adapter<boost::asio::mutable_buffer,
          MutableBufferSequence>::first(buffers), flags, ec);
  }

  // Wait until data can be received without blocking.
  std::size_t receive(base_implementation_type&, const null_buffers&,
      socket_base::message_flags, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
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
    typedef winrt_socket_recv_op<MutableBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(buffers, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((scheduler_.context(),
          *p.p, "socket", &impl, 0, "async_receive"));

    start_receive_op(impl,
        buffer_sequence_adapter<boost::asio::mutable_buffer,
          MutableBufferSequence>::first(buffers),
        flags, p.p, is_continuation);
    p.v = p.p = 0;
  }

  // Wait until data can be received without blocking.
  template <typename Handler, typename IoExecutor>
  void async_receive(base_implementation_type&, const null_buffers&,
      socket_base::message_flags, Handler& handler, const IoExecutor& io_ex)
  {
    boost::system::error_code ec = boost::asio::error::operation_not_supported;
    const std::size_t bytes_transferred = 0;
    boost::asio::post(io_ex,
        detail::bind_handler(handler, ec, bytes_transferred));
  }

protected:
  // Helper function to obtain endpoints associated with the connection.
  BOOST_ASIO_DECL std::size_t do_get_endpoint(
      const base_implementation_type& impl, bool local,
      void* addr, std::size_t addr_len, boost::system::error_code& ec) const;

  // Helper function to set a socket option.
  BOOST_ASIO_DECL boost::system::error_code do_set_option(
      base_implementation_type& impl,
      int level, int optname, const void* optval,
      std::size_t optlen, boost::system::error_code& ec);

  // Helper function to get a socket option.
  BOOST_ASIO_DECL void do_get_option(
      const base_implementation_type& impl,
      int level, int optname, void* optval,
      std::size_t* optlen, boost::system::error_code& ec) const;

  // Helper function to perform a synchronous connect.
  BOOST_ASIO_DECL boost::system::error_code do_connect(
      base_implementation_type& impl,
      const void* addr, boost::system::error_code& ec);

  // Helper function to start an asynchronous connect.
  BOOST_ASIO_DECL void start_connect_op(
      base_implementation_type& impl, const void* addr,
      winrt_async_op<void>* op, bool is_continuation);

  // Helper function to perform a synchronous send.
  BOOST_ASIO_DECL std::size_t do_send(
      base_implementation_type& impl, const boost::asio::const_buffer& data,
      socket_base::message_flags flags, boost::system::error_code& ec);

  // Helper function to start an asynchronous send.
  BOOST_ASIO_DECL void start_send_op(base_implementation_type& impl,
      const boost::asio::const_buffer& data, socket_base::message_flags flags,
      winrt_async_op<unsigned int>* op, bool is_continuation);

  // Helper function to perform a synchronous receive.
  BOOST_ASIO_DECL std::size_t do_receive(
      base_implementation_type& impl, const boost::asio::mutable_buffer& data,
      socket_base::message_flags flags, boost::system::error_code& ec);

  // Helper function to start an asynchronous receive.
  BOOST_ASIO_DECL void start_receive_op(base_implementation_type& impl,
      const boost::asio::mutable_buffer& data, socket_base::message_flags flags,
      winrt_async_op<Windows::Storage::Streams::IBuffer^>* op,
      bool is_continuation);

  // The scheduler implementation used for delivering completions.
#if defined(BOOST_ASIO_HAS_IOCP)
  typedef class win_iocp_io_context scheduler_impl;
#else
  typedef class scheduler scheduler_impl;
#endif
  scheduler_impl& scheduler_;

  // The manager that keeps track of outstanding operations.
  winrt_async_manager& async_manager_;

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
# include <boost/asio/detail/impl/winrt_ssocket_service_base.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_WINRT_SSOCKET_SERVICE_BASE_HPP

/* winrt_ssocket_service_base.hpp
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
*/