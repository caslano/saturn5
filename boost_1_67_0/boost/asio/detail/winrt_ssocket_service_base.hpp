//
// detail/winrt_ssocket_service_base.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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