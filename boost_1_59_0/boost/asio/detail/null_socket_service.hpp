//
// detail/null_socket_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_SOCKET_SERVICE_HPP
#define BOOST_ASIO_DETAIL_NULL_SOCKET_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/buffer.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/socket_base.hpp>
#include <boost/asio/detail/bind_handler.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Protocol>
class null_socket_service :
  public execution_context_service_base<null_socket_service<Protocol> >
{
public:
  // The protocol type.
  typedef Protocol protocol_type;

  // The endpoint type.
  typedef typename Protocol::endpoint endpoint_type;

  // The native type of a socket.
  typedef int native_handle_type;

  // The implementation type of the socket.
  struct implementation_type
  {
  };

  // Constructor.
  null_socket_service(execution_context& context)
    : execution_context_service_base<null_socket_service<Protocol> >(context)
  {
  }

  // Destroy all user-defined handler objects owned by the service.
  void shutdown()
  {
  }

  // Construct a new socket implementation.
  void construct(implementation_type&)
  {
  }

  // Move-construct a new socket implementation.
  void move_construct(implementation_type&, implementation_type&)
  {
  }

  // Move-assign from another socket implementation.
  void move_assign(implementation_type&,
      null_socket_service&, implementation_type&)
  {
  }

  // Move-construct a new socket implementation from another protocol type.
  template <typename Protocol1>
  void converting_move_construct(implementation_type&,
      null_socket_service<Protocol1>&,
      typename null_socket_service<Protocol1>::implementation_type&)
  {
  }

  // Destroy a socket implementation.
  void destroy(implementation_type&)
  {
  }

  // Open a new socket implementation.
  boost::system::error_code open(implementation_type&,
      const protocol_type&, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return ec;
  }

  // Assign a native socket to a socket implementation.
  boost::system::error_code assign(implementation_type&, const protocol_type&,
      const native_handle_type&, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return ec;
  }

  // Determine whether the socket is open.
  bool is_open(const implementation_type&) const
  {
    return false;
  }

  // Destroy a socket implementation.
  boost::system::error_code close(implementation_type&,
      boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return ec;
  }

  // Release ownership of the socket.
  native_handle_type release(implementation_type&,
      boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return 0;
  }

  // Get the native socket representation.
  native_handle_type native_handle(implementation_type&)
  {
    return 0;
  }

  // Cancel all operations associated with the socket.
  boost::system::error_code cancel(implementation_type&,
      boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return ec;
  }

  // Determine whether the socket is at the out-of-band data mark.
  bool at_mark(const implementation_type&,
      boost::system::error_code& ec) const
  {
    ec = boost::asio::error::operation_not_supported;
    return false;
  }

  // Determine the number of bytes available for reading.
  std::size_t available(const implementation_type&,
      boost::system::error_code& ec) const
  {
    ec = boost::asio::error::operation_not_supported;
    return 0;
  }

  // Place the socket into the state where it will listen for new connections.
  boost::system::error_code listen(implementation_type&,
      int, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return ec;
  }

  // Perform an IO control command on the socket.
  template <typename IO_Control_Command>
  boost::system::error_code io_control(implementation_type&,
      IO_Control_Command&, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return ec;
  }

  // Gets the non-blocking mode of the socket.
  bool non_blocking(const implementation_type&) const
  {
    return false;
  }

  // Sets the non-blocking mode of the socket.
  boost::system::error_code non_blocking(implementation_type&,
      bool, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return ec;
  }

  // Gets the non-blocking mode of the native socket implementation.
  bool native_non_blocking(const implementation_type&) const
  {
    return false;
  }

  // Sets the non-blocking mode of the native socket implementation.
  boost::system::error_code native_non_blocking(implementation_type&,
      bool, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return ec;
  }

  // Disable sends or receives on the socket.
  boost::system::error_code shutdown(implementation_type&,
      socket_base::shutdown_type, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return ec;
  }

  // Bind the socket to the specified local endpoint.
  boost::system::error_code bind(implementation_type&,
      const endpoint_type&, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return ec;
  }

  // Set a socket option.
  template <typename Option>
  boost::system::error_code set_option(implementation_type&,
      const Option&, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return ec;
  }

  // Set a socket option.
  template <typename Option>
  boost::system::error_code get_option(const implementation_type&,
      Option&, boost::system::error_code& ec) const
  {
    ec = boost::asio::error::operation_not_supported;
    return ec;
  }

  // Get the local endpoint.
  endpoint_type local_endpoint(const implementation_type&,
      boost::system::error_code& ec) const
  {
    ec = boost::asio::error::operation_not_supported;
    return endpoint_type();
  }

  // Get the remote endpoint.
  endpoint_type remote_endpoint(const implementation_type&,
      boost::system::error_code& ec) const
  {
    ec = boost::asio::error::operation_not_supported;
    return endpoint_type();
  }

  // Send the given data to the peer.
  template <typename ConstBufferSequence>
  std::size_t send(implementation_type&, const ConstBufferSequence&,
      socket_base::message_flags, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return 0;
  }

  // Wait until data can be sent without blocking.
  std::size_t send(implementation_type&, const null_buffers&,
      socket_base::message_flags, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return 0;
  }

  // Start an asynchronous send. The data being sent must be valid for the
  // lifetime of the asynchronous operation.
  template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
  void async_send(implementation_type&, const ConstBufferSequence&,
      socket_base::message_flags, Handler& handler, const IoExecutor& io_ex)
  {
    boost::system::error_code ec = boost::asio::error::operation_not_supported;
    const std::size_t bytes_transferred = 0;
    boost::asio::post(io_ex, detail::bind_handler(
          handler, ec, bytes_transferred));
  }

  // Start an asynchronous wait until data can be sent without blocking.
  template <typename Handler, typename IoExecutor>
  void async_send(implementation_type&, const null_buffers&,
      socket_base::message_flags, Handler& handler, const IoExecutor& io_ex)
  {
    boost::system::error_code ec = boost::asio::error::operation_not_supported;
    const std::size_t bytes_transferred = 0;
    boost::asio::post(io_ex, detail::bind_handler(
          handler, ec, bytes_transferred));
  }

  // Receive some data from the peer. Returns the number of bytes received.
  template <typename MutableBufferSequence>
  std::size_t receive(implementation_type&, const MutableBufferSequence&,
      socket_base::message_flags, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return 0;
  }

  // Wait until data can be received without blocking.
  std::size_t receive(implementation_type&, const null_buffers&,
      socket_base::message_flags, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return 0;
  }

  // Start an asynchronous receive. The buffer for the data being received
  // must be valid for the lifetime of the asynchronous operation.
  template <typename MutableBufferSequence,
      typename Handler, typename IoExecutor>
  void async_receive(implementation_type&, const MutableBufferSequence&,
      socket_base::message_flags, Handler& handler, const IoExecutor& io_ex)
  {
    boost::system::error_code ec = boost::asio::error::operation_not_supported;
    const std::size_t bytes_transferred = 0;
    boost::asio::post(io_ex, detail::bind_handler(
          handler, ec, bytes_transferred));
  }

  // Wait until data can be received without blocking.
  template <typename Handler, typename IoExecutor>
  void async_receive(implementation_type&, const null_buffers&,
      socket_base::message_flags, Handler& handler, const IoExecutor& io_ex)
  {
    boost::system::error_code ec = boost::asio::error::operation_not_supported;
    const std::size_t bytes_transferred = 0;
    boost::asio::post(io_ex, detail::bind_handler(
          handler, ec, bytes_transferred));
  }

  // Receive some data with associated flags. Returns the number of bytes
  // received.
  template <typename MutableBufferSequence>
  std::size_t receive_with_flags(implementation_type&,
      const MutableBufferSequence&, socket_base::message_flags,
      socket_base::message_flags&, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return 0;
  }

  // Wait until data can be received without blocking.
  std::size_t receive_with_flags(implementation_type&,
      const null_buffers&, socket_base::message_flags,
      socket_base::message_flags&, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return 0;
  }

  // Start an asynchronous receive. The buffer for the data being received
  // must be valid for the lifetime of the asynchronous operation.
  template <typename MutableBufferSequence,
      typename Handler, typename IoExecutor>
  void async_receive_with_flags(implementation_type&,
      const MutableBufferSequence&, socket_base::message_flags,
      socket_base::message_flags&, Handler& handler, const IoExecutor& io_ex)
  {
    boost::system::error_code ec = boost::asio::error::operation_not_supported;
    const std::size_t bytes_transferred = 0;
    boost::asio::post(io_ex, detail::bind_handler(
          handler, ec, bytes_transferred));
  }

  // Wait until data can be received without blocking.
  template <typename Handler, typename IoExecutor>
  void async_receive_with_flags(implementation_type&, const null_buffers&,
      socket_base::message_flags, socket_base::message_flags&,
      Handler& handler, const IoExecutor& io_ex)
  {
    boost::system::error_code ec = boost::asio::error::operation_not_supported;
    const std::size_t bytes_transferred = 0;
    boost::asio::post(io_ex, detail::bind_handler(
          handler, ec, bytes_transferred));
  }

  // Send a datagram to the specified endpoint. Returns the number of bytes
  // sent.
  template <typename ConstBufferSequence>
  std::size_t send_to(implementation_type&, const ConstBufferSequence&,
      const endpoint_type&, socket_base::message_flags,
      boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return 0;
  }

  // Wait until data can be sent without blocking.
  std::size_t send_to(implementation_type&, const null_buffers&,
      const endpoint_type&, socket_base::message_flags,
      boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return 0;
  }

  // Start an asynchronous send. The data being sent must be valid for the
  // lifetime of the asynchronous operation.
  template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
  void async_send_to(implementation_type&, const ConstBufferSequence&,
      const endpoint_type&, socket_base::message_flags,
      Handler& handler)
  {
    boost::system::error_code ec = boost::asio::error::operation_not_supported;
    const std::size_t bytes_transferred = 0;
    boost::asio::post(io_ex, detail::bind_handler(
          handler, ec, bytes_transferred));
  }

  // Start an asynchronous wait until data can be sent without blocking.
  template <typename Handler, typename IoExecutor>
  void async_send_to(implementation_type&, const null_buffers&,
      const endpoint_type&, socket_base::message_flags,
      Handler& handler, const IoExecutor& io_ex)
  {
    boost::system::error_code ec = boost::asio::error::operation_not_supported;
    const std::size_t bytes_transferred = 0;
    boost::asio::post(io_ex, detail::bind_handler(
          handler, ec, bytes_transferred));
  }

  // Receive a datagram with the endpoint of the sender. Returns the number of
  // bytes received.
  template <typename MutableBufferSequence>
  std::size_t receive_from(implementation_type&, const MutableBufferSequence&,
      endpoint_type&, socket_base::message_flags,
      boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return 0;
  }

  // Wait until data can be received without blocking.
  std::size_t receive_from(implementation_type&, const null_buffers&,
      endpoint_type&, socket_base::message_flags,
      boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return 0;
  }

  // Start an asynchronous receive. The buffer for the data being received and
  // the sender_endpoint object must both be valid for the lifetime of the
  // asynchronous operation.
  template <typename MutableBufferSequence,
      typename Handler, typename IoExecutor>
  void async_receive_from(implementation_type&, const MutableBufferSequence&,
      endpoint_type&, socket_base::message_flags, Handler& handler,
      const IoExecutor& io_ex)
  {
    boost::system::error_code ec = boost::asio::error::operation_not_supported;
    const std::size_t bytes_transferred = 0;
    boost::asio::post(io_ex, detail::bind_handler(
          handler, ec, bytes_transferred));
  }

  // Wait until data can be received without blocking.
  template <typename Handler, typename IoExecutor>
  void async_receive_from(implementation_type&, const null_buffers&,
      endpoint_type&, socket_base::message_flags, Handler& handler,
      const IoExecutor& io_ex)
  {
    boost::system::error_code ec = boost::asio::error::operation_not_supported;
    const std::size_t bytes_transferred = 0;
    boost::asio::post(io_ex, detail::bind_handler(
          handler, ec, bytes_transferred));
  }

  // Accept a new connection.
  template <typename Socket>
  boost::system::error_code accept(implementation_type&,
      Socket&, endpoint_type*, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return ec;
  }

  // Start an asynchronous accept. The peer and peer_endpoint objects
  // must be valid until the accept's handler is invoked.
  template <typename Socket, typename Handler, typename IoExecutor>
  void async_accept(implementation_type&, Socket&, endpoint_type*,
      Handler& handler, const IoExecutor& io_ex)
  {
    boost::system::error_code ec = boost::asio::error::operation_not_supported;
    boost::asio::post(io_ex, detail::bind_handler(handler, ec));
  }

  // Connect the socket to the specified endpoint.
  boost::system::error_code connect(implementation_type&,
      const endpoint_type&, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return ec;
  }

  // Start an asynchronous connect.
  template <typename Handler, typename IoExecutor>
  void async_connect(implementation_type&, const endpoint_type&,
      Handler& handler, const IoExecutor& io_ex)
  {
    boost::system::error_code ec = boost::asio::error::operation_not_supported;
    boost::asio::post(io_ex, detail::bind_handler(handler, ec));
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_NULL_SOCKET_SERVICE_HPP

/* null_socket_service.hpp
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
*/