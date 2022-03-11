//
// detail/null_socket_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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