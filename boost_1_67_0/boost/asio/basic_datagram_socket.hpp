//
// basic_datagram_socket.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_DATAGRAM_SOCKET_HPP
#define BOOST_ASIO_BASIC_DATAGRAM_SOCKET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <boost/asio/basic_socket.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if !defined(BOOST_ASIO_BASIC_DATAGRAM_SOCKET_FWD_DECL)
#define BOOST_ASIO_BASIC_DATAGRAM_SOCKET_FWD_DECL

// Forward declaration with defaulted arguments.
template <typename Protocol, typename Executor = executor>
class basic_datagram_socket;

#endif // !defined(BOOST_ASIO_BASIC_DATAGRAM_SOCKET_FWD_DECL)

/// Provides datagram-oriented socket functionality.
/**
 * The basic_datagram_socket class template provides asynchronous and blocking
 * datagram-oriented socket functionality.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <typename Protocol, typename Executor>
class basic_datagram_socket
  : public basic_socket<Protocol, Executor>
{
public:
  /// The type of the executor associated with the object.
  typedef Executor executor_type;

  /// Rebinds the socket type to another executor.
  template <typename Executor1>
  struct rebind_executor
  {
    /// The socket type when rebound to the specified executor.
    typedef basic_datagram_socket<Protocol, Executor1> other;
  };

  /// The native representation of a socket.
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined native_handle_type;
#else
  typedef typename basic_socket<Protocol,
    Executor>::native_handle_type native_handle_type;
#endif

  /// The protocol type.
  typedef Protocol protocol_type;

  /// The endpoint type.
  typedef typename Protocol::endpoint endpoint_type;

  /// Construct a basic_datagram_socket without opening it.
  /**
   * This constructor creates a datagram socket without opening it. The open()
   * function must be called before data can be sent or received on the socket.
   *
   * @param ex The I/O executor that the socket will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the socket.
   */
  explicit basic_datagram_socket(const executor_type& ex)
    : basic_socket<Protocol, Executor>(ex)
  {
  }

  /// Construct a basic_datagram_socket without opening it.
  /**
   * This constructor creates a datagram socket without opening it. The open()
   * function must be called before data can be sent or received on the socket.
   *
   * @param context An execution context which provides the I/O executor that
   * the socket will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the socket.
   */
  template <typename ExecutionContext>
  explicit basic_datagram_socket(ExecutionContext& context,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : basic_socket<Protocol, Executor>(context)
  {
  }

  /// Construct and open a basic_datagram_socket.
  /**
   * This constructor creates and opens a datagram socket.
   *
   * @param ex The I/O executor that the socket will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the socket.
   *
   * @param protocol An object specifying protocol parameters to be used.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_datagram_socket(const executor_type& ex, const protocol_type& protocol)
    : basic_socket<Protocol, Executor>(ex, protocol)
  {
  }

  /// Construct and open a basic_datagram_socket.
  /**
   * This constructor creates and opens a datagram socket.
   *
   * @param context An execution context which provides the I/O executor that
   * the socket will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the socket.
   *
   * @param protocol An object specifying protocol parameters to be used.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_datagram_socket(ExecutionContext& context,
      const protocol_type& protocol,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : basic_socket<Protocol, Executor>(context, protocol)
  {
  }

  /// Construct a basic_datagram_socket, opening it and binding it to the given
  /// local endpoint.
  /**
   * This constructor creates a datagram socket and automatically opens it bound
   * to the specified endpoint on the local machine. The protocol used is the
   * protocol associated with the given endpoint.
   *
   * @param ex The I/O executor that the socket will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the socket.
   *
   * @param endpoint An endpoint on the local machine to which the datagram
   * socket will be bound.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_datagram_socket(const executor_type& ex, const endpoint_type& endpoint)
    : basic_socket<Protocol, Executor>(ex, endpoint)
  {
  }

  /// Construct a basic_datagram_socket, opening it and binding it to the given
  /// local endpoint.
  /**
   * This constructor creates a datagram socket and automatically opens it bound
   * to the specified endpoint on the local machine. The protocol used is the
   * protocol associated with the given endpoint.
   *
   * @param context An execution context which provides the I/O executor that
   * the socket will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the socket.
   *
   * @param endpoint An endpoint on the local machine to which the datagram
   * socket will be bound.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_datagram_socket(ExecutionContext& context,
      const endpoint_type& endpoint,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : basic_socket<Protocol, Executor>(context, endpoint)
  {
  }

  /// Construct a basic_datagram_socket on an existing native socket.
  /**
   * This constructor creates a datagram socket object to hold an existing
   * native socket.
   *
   * @param ex The I/O executor that the socket will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the socket.
   *
   * @param protocol An object specifying protocol parameters to be used.
   *
   * @param native_socket The new underlying socket implementation.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_datagram_socket(const executor_type& ex,
      const protocol_type& protocol, const native_handle_type& native_socket)
    : basic_socket<Protocol, Executor>(ex, protocol, native_socket)
  {
  }

  /// Construct a basic_datagram_socket on an existing native socket.
  /**
   * This constructor creates a datagram socket object to hold an existing
   * native socket.
   *
   * @param context An execution context which provides the I/O executor that
   * the socket will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the socket.
   *
   * @param protocol An object specifying protocol parameters to be used.
   *
   * @param native_socket The new underlying socket implementation.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_datagram_socket(ExecutionContext& context,
      const protocol_type& protocol, const native_handle_type& native_socket,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : basic_socket<Protocol, Executor>(context, protocol, native_socket)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct a basic_datagram_socket from another.
  /**
   * This constructor moves a datagram socket from one object to another.
   *
   * @param other The other basic_datagram_socket object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_datagram_socket(const executor_type&)
   * constructor.
   */
  basic_datagram_socket(basic_datagram_socket&& other) BOOST_ASIO_NOEXCEPT
    : basic_socket<Protocol, Executor>(std::move(other))
  {
  }

  /// Move-assign a basic_datagram_socket from another.
  /**
   * This assignment operator moves a datagram socket from one object to
   * another.
   *
   * @param other The other basic_datagram_socket object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_datagram_socket(const executor_type&)
   * constructor.
   */
  basic_datagram_socket& operator=(basic_datagram_socket&& other)
  {
    basic_socket<Protocol, Executor>::operator=(std::move(other));
    return *this;
  }

  /// Move-construct a basic_datagram_socket from a socket of another protocol
  /// type.
  /**
   * This constructor moves a datagram socket from one object to another.
   *
   * @param other The other basic_datagram_socket object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_datagram_socket(const executor_type&)
   * constructor.
   */
  template <typename Protocol1, typename Executor1>
  basic_datagram_socket(basic_datagram_socket<Protocol1, Executor1>&& other,
      typename enable_if<
        is_convertible<Protocol1, Protocol>::value
          && is_convertible<Executor1, Executor>::value
      >::type* = 0)
    : basic_socket<Protocol, Executor>(std::move(other))
  {
  }

  /// Move-assign a basic_datagram_socket from a socket of another protocol
  /// type.
  /**
   * This assignment operator moves a datagram socket from one object to
   * another.
   *
   * @param other The other basic_datagram_socket object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_datagram_socket(const executor_type&)
   * constructor.
   */
  template <typename Protocol1, typename Executor1>
  typename enable_if<
    is_convertible<Protocol1, Protocol>::value
      && is_convertible<Executor1, Executor>::value,
    basic_datagram_socket&
  >::type operator=(basic_datagram_socket<Protocol1, Executor1>&& other)
  {
    basic_socket<Protocol, Executor>::operator=(std::move(other));
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Destroys the socket.
  /**
   * This function destroys the socket, cancelling any outstanding asynchronous
   * operations associated with the socket as if by calling @c cancel.
   */
  ~basic_datagram_socket()
  {
  }

  /// Send some data on a connected socket.
  /**
   * This function is used to send data on the datagram socket. The function
   * call will block until the data has been sent successfully or an error
   * occurs.
   *
   * @param buffers One ore more data buffers to be sent on the socket.
   *
   * @returns The number of bytes sent.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note The send operation can only be used with a connected socket. Use
   * the send_to function to send data on an unconnected datagram socket.
   *
   * @par Example
   * To send a single data buffer use the @ref buffer function as follows:
   * @code socket.send(boost::asio::buffer(data, size)); @endcode
   * See the @ref buffer documentation for information on sending multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename ConstBufferSequence>
  std::size_t send(const ConstBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = this->impl_.get_service().send(
        this->impl_.get_implementation(), buffers, 0, ec);
    boost::asio::detail::throw_error(ec, "send");
    return s;
  }

  /// Send some data on a connected socket.
  /**
   * This function is used to send data on the datagram socket. The function
   * call will block until the data has been sent successfully or an error
   * occurs.
   *
   * @param buffers One ore more data buffers to be sent on the socket.
   *
   * @param flags Flags specifying how the send call is to be made.
   *
   * @returns The number of bytes sent.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note The send operation can only be used with a connected socket. Use
   * the send_to function to send data on an unconnected datagram socket.
   */
  template <typename ConstBufferSequence>
  std::size_t send(const ConstBufferSequence& buffers,
      socket_base::message_flags flags)
  {
    boost::system::error_code ec;
    std::size_t s = this->impl_.get_service().send(
        this->impl_.get_implementation(), buffers, flags, ec);
    boost::asio::detail::throw_error(ec, "send");
    return s;
  }

  /// Send some data on a connected socket.
  /**
   * This function is used to send data on the datagram socket. The function
   * call will block until the data has been sent successfully or an error
   * occurs.
   *
   * @param buffers One or more data buffers to be sent on the socket.
   *
   * @param flags Flags specifying how the send call is to be made.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes sent.
   *
   * @note The send operation can only be used with a connected socket. Use
   * the send_to function to send data on an unconnected datagram socket.
   */
  template <typename ConstBufferSequence>
  std::size_t send(const ConstBufferSequence& buffers,
      socket_base::message_flags flags, boost::system::error_code& ec)
  {
    return this->impl_.get_service().send(
        this->impl_.get_implementation(), buffers, flags, ec);
  }

  /// Start an asynchronous send on a connected socket.
  /**
   * This function is used to asynchronously send data on the datagram socket.
   * The function call always returns immediately.
   *
   * @param buffers One or more data buffers to be sent on the socket. Although
   * the buffers object may be copied as necessary, ownership of the underlying
   * memory blocks is retained by the caller, which must guarantee that they
   * remain valid until the handler is called.
   *
   * @param handler The handler to be called when the send operation completes.
   * Copies will be made of the handler as required. The function signature of
   * the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes sent.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @note The async_send operation can only be used with a connected socket.
   * Use the async_send_to function to send data on an unconnected datagram
   * socket.
   *
   * @par Example
   * To send a single data buffer use the @ref buffer function as follows:
   * @code
   * socket.async_send(boost::asio::buffer(data, size), handler);
   * @endcode
   * See the @ref buffer documentation for information on sending multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename ConstBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) WriteHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
      void (boost::system::error_code, std::size_t))
  async_send(const ConstBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(WriteHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WriteHandler,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_send(this), handler,
        buffers, socket_base::message_flags(0));
  }

  /// Start an asynchronous send on a connected socket.
  /**
   * This function is used to asynchronously send data on the datagram socket.
   * The function call always returns immediately.
   *
   * @param buffers One or more data buffers to be sent on the socket. Although
   * the buffers object may be copied as necessary, ownership of the underlying
   * memory blocks is retained by the caller, which must guarantee that they
   * remain valid until the handler is called.
   *
   * @param flags Flags specifying how the send call is to be made.
   *
   * @param handler The handler to be called when the send operation completes.
   * Copies will be made of the handler as required. The function signature of
   * the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes sent.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @note The async_send operation can only be used with a connected socket.
   * Use the async_send_to function to send data on an unconnected datagram
   * socket.
   */
  template <typename ConstBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) WriteHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
      void (boost::system::error_code, std::size_t))
  async_send(const ConstBufferSequence& buffers,
      socket_base::message_flags flags,
      BOOST_ASIO_MOVE_ARG(WriteHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WriteHandler,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_send(this), handler, buffers, flags);
  }

  /// Send a datagram to the specified endpoint.
  /**
   * This function is used to send a datagram to the specified remote endpoint.
   * The function call will block until the data has been sent successfully or
   * an error occurs.
   *
   * @param buffers One or more data buffers to be sent to the remote endpoint.
   *
   * @param destination The remote endpoint to which the data will be sent.
   *
   * @returns The number of bytes sent.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @par Example
   * To send a single data buffer use the @ref buffer function as follows:
   * @code
   * boost::asio::ip::udp::endpoint destination(
   *     boost::asio::ip::address::from_string("1.2.3.4"), 12345);
   * socket.send_to(boost::asio::buffer(data, size), destination);
   * @endcode
   * See the @ref buffer documentation for information on sending multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename ConstBufferSequence>
  std::size_t send_to(const ConstBufferSequence& buffers,
      const endpoint_type& destination)
  {
    boost::system::error_code ec;
    std::size_t s = this->impl_.get_service().send_to(
        this->impl_.get_implementation(), buffers, destination, 0, ec);
    boost::asio::detail::throw_error(ec, "send_to");
    return s;
  }

  /// Send a datagram to the specified endpoint.
  /**
   * This function is used to send a datagram to the specified remote endpoint.
   * The function call will block until the data has been sent successfully or
   * an error occurs.
   *
   * @param buffers One or more data buffers to be sent to the remote endpoint.
   *
   * @param destination The remote endpoint to which the data will be sent.
   *
   * @param flags Flags specifying how the send call is to be made.
   *
   * @returns The number of bytes sent.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ConstBufferSequence>
  std::size_t send_to(const ConstBufferSequence& buffers,
      const endpoint_type& destination, socket_base::message_flags flags)
  {
    boost::system::error_code ec;
    std::size_t s = this->impl_.get_service().send_to(
        this->impl_.get_implementation(), buffers, destination, flags, ec);
    boost::asio::detail::throw_error(ec, "send_to");
    return s;
  }

  /// Send a datagram to the specified endpoint.
  /**
   * This function is used to send a datagram to the specified remote endpoint.
   * The function call will block until the data has been sent successfully or
   * an error occurs.
   *
   * @param buffers One or more data buffers to be sent to the remote endpoint.
   *
   * @param destination The remote endpoint to which the data will be sent.
   *
   * @param flags Flags specifying how the send call is to be made.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes sent.
   */
  template <typename ConstBufferSequence>
  std::size_t send_to(const ConstBufferSequence& buffers,
      const endpoint_type& destination, socket_base::message_flags flags,
      boost::system::error_code& ec)
  {
    return this->impl_.get_service().send_to(this->impl_.get_implementation(),
        buffers, destination, flags, ec);
  }

  /// Start an asynchronous send.
  /**
   * This function is used to asynchronously send a datagram to the specified
   * remote endpoint. The function call always returns immediately.
   *
   * @param buffers One or more data buffers to be sent to the remote endpoint.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param destination The remote endpoint to which the data will be sent.
   * Copies will be made of the endpoint as required.
   *
   * @param handler The handler to be called when the send operation completes.
   * Copies will be made of the handler as required. The function signature of
   * the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes sent.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Example
   * To send a single data buffer use the @ref buffer function as follows:
   * @code
   * boost::asio::ip::udp::endpoint destination(
   *     boost::asio::ip::address::from_string("1.2.3.4"), 12345);
   * socket.async_send_to(
   *     boost::asio::buffer(data, size), destination, handler);
   * @endcode
   * See the @ref buffer documentation for information on sending multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename ConstBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) WriteHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
      void (boost::system::error_code, std::size_t))
  async_send_to(const ConstBufferSequence& buffers,
      const endpoint_type& destination,
      BOOST_ASIO_MOVE_ARG(WriteHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WriteHandler,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_send_to(this), handler, buffers,
        destination, socket_base::message_flags(0));
  }

  /// Start an asynchronous send.
  /**
   * This function is used to asynchronously send a datagram to the specified
   * remote endpoint. The function call always returns immediately.
   *
   * @param buffers One or more data buffers to be sent to the remote endpoint.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param flags Flags specifying how the send call is to be made.
   *
   * @param destination The remote endpoint to which the data will be sent.
   * Copies will be made of the endpoint as required.
   *
   * @param handler The handler to be called when the send operation completes.
   * Copies will be made of the handler as required. The function signature of
   * the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes sent.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   */
  template <typename ConstBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) WriteHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
      void (boost::system::error_code, std::size_t))
  async_send_to(const ConstBufferSequence& buffers,
      const endpoint_type& destination, socket_base::message_flags flags,
      BOOST_ASIO_MOVE_ARG(WriteHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WriteHandler,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_send_to(this), handler, buffers, destination, flags);
  }

  /// Receive some data on a connected socket.
  /**
   * This function is used to receive data on the datagram socket. The function
   * call will block until data has been received successfully or an error
   * occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @returns The number of bytes received.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note The receive operation can only be used with a connected socket. Use
   * the receive_from function to receive data on an unconnected datagram
   * socket.
   *
   * @par Example
   * To receive into a single data buffer use the @ref buffer function as
   * follows:
   * @code socket.receive(boost::asio::buffer(data, size)); @endcode
   * See the @ref buffer documentation for information on receiving into
   * multiple buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename MutableBufferSequence>
  std::size_t receive(const MutableBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = this->impl_.get_service().receive(
        this->impl_.get_implementation(), buffers, 0, ec);
    boost::asio::detail::throw_error(ec, "receive");
    return s;
  }

  /// Receive some data on a connected socket.
  /**
   * This function is used to receive data on the datagram socket. The function
   * call will block until data has been received successfully or an error
   * occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @param flags Flags specifying how the receive call is to be made.
   *
   * @returns The number of bytes received.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note The receive operation can only be used with a connected socket. Use
   * the receive_from function to receive data on an unconnected datagram
   * socket.
   */
  template <typename MutableBufferSequence>
  std::size_t receive(const MutableBufferSequence& buffers,
      socket_base::message_flags flags)
  {
    boost::system::error_code ec;
    std::size_t s = this->impl_.get_service().receive(
        this->impl_.get_implementation(), buffers, flags, ec);
    boost::asio::detail::throw_error(ec, "receive");
    return s;
  }

  /// Receive some data on a connected socket.
  /**
   * This function is used to receive data on the datagram socket. The function
   * call will block until data has been received successfully or an error
   * occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @param flags Flags specifying how the receive call is to be made.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes received.
   *
   * @note The receive operation can only be used with a connected socket. Use
   * the receive_from function to receive data on an unconnected datagram
   * socket.
   */
  template <typename MutableBufferSequence>
  std::size_t receive(const MutableBufferSequence& buffers,
      socket_base::message_flags flags, boost::system::error_code& ec)
  {
    return this->impl_.get_service().receive(
        this->impl_.get_implementation(), buffers, flags, ec);
  }

  /// Start an asynchronous receive on a connected socket.
  /**
   * This function is used to asynchronously receive data from the datagram
   * socket. The function call always returns immediately.
   *
   * @param buffers One or more buffers into which the data will be received.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param handler The handler to be called when the receive operation
   * completes. Copies will be made of the handler as required. The function
   * signature of the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes received.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @note The async_receive operation can only be used with a connected socket.
   * Use the async_receive_from function to receive data on an unconnected
   * datagram socket.
   *
   * @par Example
   * To receive into a single data buffer use the @ref buffer function as
   * follows:
   * @code
   * socket.async_receive(boost::asio::buffer(data, size), handler);
   * @endcode
   * See the @ref buffer documentation for information on receiving into
   * multiple buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename MutableBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) ReadHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
      void (boost::system::error_code, std::size_t))
  async_receive(const MutableBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(ReadHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<ReadHandler,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_receive(this), handler,
        buffers, socket_base::message_flags(0));
  }

  /// Start an asynchronous receive on a connected socket.
  /**
   * This function is used to asynchronously receive data from the datagram
   * socket. The function call always returns immediately.
   *
   * @param buffers One or more buffers into which the data will be received.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param flags Flags specifying how the receive call is to be made.
   *
   * @param handler The handler to be called when the receive operation
   * completes. Copies will be made of the handler as required. The function
   * signature of the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes received.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @note The async_receive operation can only be used with a connected socket.
   * Use the async_receive_from function to receive data on an unconnected
   * datagram socket.
   */
  template <typename MutableBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) ReadHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
      void (boost::system::error_code, std::size_t))
  async_receive(const MutableBufferSequence& buffers,
      socket_base::message_flags flags,
      BOOST_ASIO_MOVE_ARG(ReadHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<ReadHandler,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_receive(this), handler, buffers, flags);
  }

  /// Receive a datagram with the endpoint of the sender.
  /**
   * This function is used to receive a datagram. The function call will block
   * until data has been received successfully or an error occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @param sender_endpoint An endpoint object that receives the endpoint of
   * the remote sender of the datagram.
   *
   * @returns The number of bytes received.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @par Example
   * To receive into a single data buffer use the @ref buffer function as
   * follows:
   * @code
   * boost::asio::ip::udp::endpoint sender_endpoint;
   * socket.receive_from(
   *     boost::asio::buffer(data, size), sender_endpoint);
   * @endcode
   * See the @ref buffer documentation for information on receiving into
   * multiple buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename MutableBufferSequence>
  std::size_t receive_from(const MutableBufferSequence& buffers,
      endpoint_type& sender_endpoint)
  {
    boost::system::error_code ec;
    std::size_t s = this->impl_.get_service().receive_from(
        this->impl_.get_implementation(), buffers, sender_endpoint, 0, ec);
    boost::asio::detail::throw_error(ec, "receive_from");
    return s;
  }
  
  /// Receive a datagram with the endpoint of the sender.
  /**
   * This function is used to receive a datagram. The function call will block
   * until data has been received successfully or an error occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @param sender_endpoint An endpoint object that receives the endpoint of
   * the remote sender of the datagram.
   *
   * @param flags Flags specifying how the receive call is to be made.
   *
   * @returns The number of bytes received.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename MutableBufferSequence>
  std::size_t receive_from(const MutableBufferSequence& buffers,
      endpoint_type& sender_endpoint, socket_base::message_flags flags)
  {
    boost::system::error_code ec;
    std::size_t s = this->impl_.get_service().receive_from(
        this->impl_.get_implementation(), buffers, sender_endpoint, flags, ec);
    boost::asio::detail::throw_error(ec, "receive_from");
    return s;
  }
  
  /// Receive a datagram with the endpoint of the sender.
  /**
   * This function is used to receive a datagram. The function call will block
   * until data has been received successfully or an error occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @param sender_endpoint An endpoint object that receives the endpoint of
   * the remote sender of the datagram.
   *
   * @param flags Flags specifying how the receive call is to be made.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes received.
   */
  template <typename MutableBufferSequence>
  std::size_t receive_from(const MutableBufferSequence& buffers,
      endpoint_type& sender_endpoint, socket_base::message_flags flags,
      boost::system::error_code& ec)
  {
    return this->impl_.get_service().receive_from(
        this->impl_.get_implementation(), buffers, sender_endpoint, flags, ec);
  }

  /// Start an asynchronous receive.
  /**
   * This function is used to asynchronously receive a datagram. The function
   * call always returns immediately.
   *
   * @param buffers One or more buffers into which the data will be received.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param sender_endpoint An endpoint object that receives the endpoint of
   * the remote sender of the datagram. Ownership of the sender_endpoint object
   * is retained by the caller, which must guarantee that it is valid until the
   * handler is called.
   *
   * @param handler The handler to be called when the receive operation
   * completes. Copies will be made of the handler as required. The function
   * signature of the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes received.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Example
   * To receive into a single data buffer use the @ref buffer function as
   * follows:
   * @code socket.async_receive_from(
   *     boost::asio::buffer(data, size), sender_endpoint, handler); @endcode
   * See the @ref buffer documentation for information on receiving into
   * multiple buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename MutableBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) ReadHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
      void (boost::system::error_code, std::size_t))
  async_receive_from(const MutableBufferSequence& buffers,
      endpoint_type& sender_endpoint,
      BOOST_ASIO_MOVE_ARG(ReadHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<ReadHandler,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_receive_from(this), handler, buffers,
        &sender_endpoint, socket_base::message_flags(0));
  }

  /// Start an asynchronous receive.
  /**
   * This function is used to asynchronously receive a datagram. The function
   * call always returns immediately.
   *
   * @param buffers One or more buffers into which the data will be received.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param sender_endpoint An endpoint object that receives the endpoint of
   * the remote sender of the datagram. Ownership of the sender_endpoint object
   * is retained by the caller, which must guarantee that it is valid until the
   * handler is called.
   *
   * @param flags Flags specifying how the receive call is to be made.
   *
   * @param handler The handler to be called when the receive operation
   * completes. Copies will be made of the handler as required. The function
   * signature of the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes received.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   */
  template <typename MutableBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) ReadHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
      void (boost::system::error_code, std::size_t))
  async_receive_from(const MutableBufferSequence& buffers,
      endpoint_type& sender_endpoint, socket_base::message_flags flags,
      BOOST_ASIO_MOVE_ARG(ReadHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<ReadHandler,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_receive_from(this), handler,
        buffers, &sender_endpoint, flags);
  }

private:
  class initiate_async_send
  { 
  public:
    typedef Executor executor_type;

    explicit initiate_async_send(basic_datagram_socket* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename WriteHandler, typename ConstBufferSequence>
    void operator()(BOOST_ASIO_MOVE_ARG(WriteHandler) handler,
        const ConstBufferSequence& buffers,
        socket_base::message_flags flags) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a WriteHandler.
      BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

      detail::non_const_lvalue<WriteHandler> handler2(handler);
      self_->impl_.get_service().async_send(
          self_->impl_.get_implementation(), buffers, flags,
          handler2.value, self_->impl_.get_implementation_executor());
    }

  private:
    basic_datagram_socket* self_;
  };

  class initiate_async_send_to
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_send_to(basic_datagram_socket* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename WriteHandler, typename ConstBufferSequence>
    void operator()(BOOST_ASIO_MOVE_ARG(WriteHandler) handler,
        const ConstBufferSequence& buffers, const endpoint_type& destination,
        socket_base::message_flags flags) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a WriteHandler.
      BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

      detail::non_const_lvalue<WriteHandler> handler2(handler);
      self_->impl_.get_service().async_send_to(
          self_->impl_.get_implementation(), buffers, destination, flags,
          handler2.value, self_->impl_.get_implementation_executor());
    }

  private:
    basic_datagram_socket* self_;
  };

  class initiate_async_receive
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_receive(basic_datagram_socket* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename ReadHandler, typename MutableBufferSequence>
    void operator()(BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
        const MutableBufferSequence& buffers,
        socket_base::message_flags flags) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ReadHandler.
      BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

      detail::non_const_lvalue<ReadHandler> handler2(handler);
      self_->impl_.get_service().async_receive(
          self_->impl_.get_implementation(), buffers, flags,
          handler2.value, self_->impl_.get_implementation_executor());
    }

  private:
    basic_datagram_socket* self_;
  };

  class initiate_async_receive_from
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_receive_from(basic_datagram_socket* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename ReadHandler, typename MutableBufferSequence>
    void operator()(BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
        const MutableBufferSequence& buffers, endpoint_type* sender_endpoint,
        socket_base::message_flags flags) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ReadHandler.
      BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

      detail::non_const_lvalue<ReadHandler> handler2(handler);
      self_->impl_.get_service().async_receive_from(
          self_->impl_.get_implementation(), buffers, *sender_endpoint, flags,
          handler2.value, self_->impl_.get_implementation_executor());
    }

  private:
    basic_datagram_socket* self_;
  };
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_BASIC_DATAGRAM_SOCKET_HPP

/* basic_datagram_socket.hpp
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
*/