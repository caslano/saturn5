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
bq4FJOn+cQYk0C78eRih1S2QZEzG7OMrzBWtvgZyaPUqWEKrG8Cgo/gj93Duuk98GxykTbziXuaQbWI4u4m50nPHG+AoHcL74TAdxUPQSMt9jBnaaAfOgPW0C+fDXtqDa2E7HcBNsIs2cS/soMO4H3roKL60mfvT4LO48H7ufzqEd0MfHcGHIEzH8PgHeC5oG74C5At8Fm+EGOsDD3JcSGS9iXvBRofx5A3cn3QAN0EqbeJecNBh3A9OOoqHIJ2Whzh3yKQdeOrDzBFt4ESTn3G0E18NSVWsx+ugU/ePvwkxOoK/3MKzTIdxP3joKB4CHy2tHAuaaQfOAJN24XwI0h5cCwE6gJvAoE3cC/V0GPdDHR3F6Ru5RrQL3w4zGKd6H2TR6qvbGA+tLoY6Wl0BDXQY/wRMWr1qE+dIq1fDLjqEfw32Gs6lnXMBO+sdOAMm0S6cD6nVnAuuhXQ6gJvAQZu4F4b1uLgfbKyP4iGIsV462D8M0g6cAQdoF86HRN0/rgWhA7gJomxj4l5Io8O4H6bSUZzfyXj8bI/P2sz9zGfd+Mku7gHWO7qZK1hCq5+EMlpd18Nc0eogtNHqB6GPVj8MB2jZwt8XMEJHcN5W7j2OpT62jWecVj8b4rrQ5iP8bf4YzyYdxNdu53i0iTu+ynNKx/CHvsa1pg38zT7uSfbvfJzPPcH1quMcd/Ds7OR3lRsmY+ZmF9ebVp8JQTr2bX5n2M31quV88Syw0278MNjYJoyfh5msj+EJ3+G+oh247Ls8pxxLnmYOYYT7wYnnw1Hag2/Zx7VmP+7v8XcHHGR9AG+A/XQIf+L7zIseF38XltAxfF+EY9BhfNuzPDsrWI8LnuO5YH0APwx1rFf/DAK0+iVopm0/4N6HerZX7waTVp+9n3cOrT4XorT6/T9i/LT6PLCzH/VsSKfVc2Em7Tlgl0cgRKvv/DH7pNVfgYO0ehsM07afcP0hiXlz4W+DnY7hzJ9yLzFX6h8d5F1Kq2NwkFa/CjFaLc9zjb7IfYI/9TPGxn48+Nc/555nvfqMX/E+pNVOWEwbA7y7II1zNPFOyKIj+Agk0PJrrikM6DVVw8hKrvsh7hOYqtcLl0MuHcAbIIkO4X1wmM9G8QcHeV4Ym4E3gotWT3uB8dDq2VBHR/E5h3nvcKwAvvEI50iH8Qde4ri0OgNctPqcGPuhw/i9v+cZodXnQhutdsIOWr0CIrR6DQzSYfzEK1wjvS5HeT/AJL2HcS2k0QHcBLtoE/fCdjqM+6GRjuIhaKDlD7y7YBXtwBnQRrtwPqynPbgWeugAboK9tIl7YQcdxv2who7iIcijZYj9Qy7twBkwk3bhfFhCe3AtFNMB3AR+2sS9UEaHcT9k0VE8BFNp+SP7hxm0A7tgkPlxYwNidAA3QSP3lXrcMOdFq92wnQ7ir/2JdwUdGGF7KKNN3At+Ooz7YQ0dxUOwipZjjAEaaAeeBYdpD14NA3QQb4GjdBg/DyN0DK99nWu6msaXjkmWSV/iuPgp2LtqsqhfhAFafWVCsgjbq4tgEq3uBCdtjEuW8e9KliDbq8vApNUHoI8OJbLNu9mG7dUvnM7naXXae5IlTEfwlROSxcV4QnjPe5NlCW17X7L8FOq1bXwWDNpxRrJ88f3Jksv+1ZkfSJZiWr0dVtEee7LUgp0O4CZIoE3cC0l0GPfDDDqKh2AqLcnJkgKTaAfOgCzahfNhJu3BtZBGB3AX7OdcwvjMFLan1XfCYlr9EPjpKM5LTZaD2viaD7JNgLHh18F902RRl34oWTy0+ptnJUsDHTk7WX43mblme5cjWZbCpBu5Fngd2GkTH4ODbKO+NS1ZDtPqNrCzH/XPYSY=
*/