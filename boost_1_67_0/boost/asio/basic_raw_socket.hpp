//
// basic_raw_socket.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_RAW_SOCKET_HPP
#define BOOST_ASIO_BASIC_RAW_SOCKET_HPP

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

#if !defined(BOOST_ASIO_BASIC_RAW_SOCKET_FWD_DECL)
#define BOOST_ASIO_BASIC_RAW_SOCKET_FWD_DECL

// Forward declaration with defaulted arguments.
template <typename Protocol, typename Executor = executor>
class basic_raw_socket;

#endif // !defined(BOOST_ASIO_BASIC_RAW_SOCKET_FWD_DECL)

/// Provides raw-oriented socket functionality.
/**
 * The basic_raw_socket class template provides asynchronous and blocking
 * raw-oriented socket functionality.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <typename Protocol, typename Executor>
class basic_raw_socket
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
    typedef basic_raw_socket<Protocol, Executor1> other;
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

  /// Construct a basic_raw_socket without opening it.
  /**
   * This constructor creates a raw socket without opening it. The open()
   * function must be called before data can be sent or received on the socket.
   *
   * @param ex The I/O executor that the socket will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the socket.
   */
  explicit basic_raw_socket(const executor_type& ex)
    : basic_socket<Protocol, Executor>(ex)
  {
  }

  /// Construct a basic_raw_socket without opening it.
  /**
   * This constructor creates a raw socket without opening it. The open()
   * function must be called before data can be sent or received on the socket.
   *
   * @param context An execution context which provides the I/O executor that
   * the socket will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the socket.
   */
  template <typename ExecutionContext>
  explicit basic_raw_socket(ExecutionContext& context,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : basic_socket<Protocol, Executor>(context)
  {
  }

  /// Construct and open a basic_raw_socket.
  /**
   * This constructor creates and opens a raw socket.
   *
   * @param ex The I/O executor that the socket will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the socket.
   *
   * @param protocol An object specifying protocol parameters to be used.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_raw_socket(const executor_type& ex, const protocol_type& protocol)
    : basic_socket<Protocol, Executor>(ex, protocol)
  {
  }

  /// Construct and open a basic_raw_socket.
  /**
   * This constructor creates and opens a raw socket.
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
  basic_raw_socket(ExecutionContext& context, const protocol_type& protocol,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : basic_socket<Protocol, Executor>(context, protocol)
  {
  }

  /// Construct a basic_raw_socket, opening it and binding it to the given
  /// local endpoint.
  /**
   * This constructor creates a raw socket and automatically opens it bound
   * to the specified endpoint on the local machine. The protocol used is the
   * protocol associated with the given endpoint.
   *
   * @param ex The I/O executor that the socket will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the socket.
   *
   * @param endpoint An endpoint on the local machine to which the raw
   * socket will be bound.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_raw_socket(const executor_type& ex, const endpoint_type& endpoint)
    : basic_socket<Protocol, Executor>(ex, endpoint)
  {
  }

  /// Construct a basic_raw_socket, opening it and binding it to the given
  /// local endpoint.
  /**
   * This constructor creates a raw socket and automatically opens it bound
   * to the specified endpoint on the local machine. The protocol used is the
   * protocol associated with the given endpoint.
   *
   * @param context An execution context which provides the I/O executor that
   * the socket will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the socket.
   *
   * @param endpoint An endpoint on the local machine to which the raw
   * socket will be bound.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_raw_socket(ExecutionContext& context, const endpoint_type& endpoint,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : basic_socket<Protocol, Executor>(context, endpoint)
  {
  }

  /// Construct a basic_raw_socket on an existing native socket.
  /**
   * This constructor creates a raw socket object to hold an existing
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
  basic_raw_socket(const executor_type& ex,
      const protocol_type& protocol, const native_handle_type& native_socket)
    : basic_socket<Protocol, Executor>(ex, protocol, native_socket)
  {
  }

  /// Construct a basic_raw_socket on an existing native socket.
  /**
   * This constructor creates a raw socket object to hold an existing
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
  basic_raw_socket(ExecutionContext& context,
      const protocol_type& protocol, const native_handle_type& native_socket,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : basic_socket<Protocol, Executor>(context, protocol, native_socket)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct a basic_raw_socket from another.
  /**
   * This constructor moves a raw socket from one object to another.
   *
   * @param other The other basic_raw_socket object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_raw_socket(const executor_type&)
   * constructor.
   */
  basic_raw_socket(basic_raw_socket&& other) BOOST_ASIO_NOEXCEPT
    : basic_socket<Protocol, Executor>(std::move(other))
  {
  }

  /// Move-assign a basic_raw_socket from another.
  /**
   * This assignment operator moves a raw socket from one object to another.
   *
   * @param other The other basic_raw_socket object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_raw_socket(const executor_type&)
   * constructor.
   */
  basic_raw_socket& operator=(basic_raw_socket&& other)
  {
    basic_socket<Protocol, Executor>::operator=(std::move(other));
    return *this;
  }

  /// Move-construct a basic_raw_socket from a socket of another protocol
  /// type.
  /**
   * This constructor moves a raw socket from one object to another.
   *
   * @param other The other basic_raw_socket object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_raw_socket(const executor_type&)
   * constructor.
   */
  template <typename Protocol1, typename Executor1>
  basic_raw_socket(basic_raw_socket<Protocol1, Executor1>&& other,
      typename enable_if<
        is_convertible<Protocol1, Protocol>::value
          && is_convertible<Executor1, Executor>::value
      >::type* = 0)
    : basic_socket<Protocol, Executor>(std::move(other))
  {
  }

  /// Move-assign a basic_raw_socket from a socket of another protocol type.
  /**
   * This assignment operator moves a raw socket from one object to another.
   *
   * @param other The other basic_raw_socket object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_raw_socket(const executor_type&)
   * constructor.
   */
  template <typename Protocol1, typename Executor1>
  typename enable_if<
    is_convertible<Protocol1, Protocol>::value
      && is_convertible<Executor1, Executor>::value,
    basic_raw_socket&
  >::type operator=(basic_raw_socket<Protocol1, Executor1>&& other)
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
  ~basic_raw_socket()
  {
  }

  /// Send some data on a connected socket.
  /**
   * This function is used to send data on the raw socket. The function call
   * will block until the data has been sent successfully or an error occurs.
   *
   * @param buffers One ore more data buffers to be sent on the socket.
   *
   * @returns The number of bytes sent.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note The send operation can only be used with a connected socket. Use
   * the send_to function to send data on an unconnected raw socket.
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
   * This function is used to send data on the raw socket. The function call
   * will block until the data has been sent successfully or an error occurs.
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
   * the send_to function to send data on an unconnected raw socket.
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
   * This function is used to send data on the raw socket. The function call
   * will block until the data has been sent successfully or an error occurs.
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
   * the send_to function to send data on an unconnected raw socket.
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
   * This function is used to send data on the raw socket. The function call
   * will block until the data has been sent successfully or an error occurs.
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
   * Use the async_send_to function to send data on an unconnected raw
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
   * This function is used to send data on the raw socket. The function call
   * will block until the data has been sent successfully or an error occurs.
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
   * Use the async_send_to function to send data on an unconnected raw
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

  /// Send raw data to the specified endpoint.
  /**
   * This function is used to send raw data to the specified remote endpoint.
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

  /// Send raw data to the specified endpoint.
  /**
   * This function is used to send raw data to the specified remote endpoint.
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

  /// Send raw data to the specified endpoint.
  /**
   * This function is used to send raw data to the specified remote endpoint.
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
   * This function is used to asynchronously send raw data to the specified
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
   * This function is used to asynchronously send raw data to the specified
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
   * This function is used to receive data on the raw socket. The function
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
   * the receive_from function to receive data on an unconnected raw
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
   * This function is used to receive data on the raw socket. The function
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
   * the receive_from function to receive data on an unconnected raw
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
   * This function is used to receive data on the raw socket. The function
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
   * the receive_from function to receive data on an unconnected raw
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
   * This function is used to asynchronously receive data from the raw
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
   * raw socket.
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
   * This function is used to asynchronously receive data from the raw
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
   * raw socket.
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

  /// Receive raw data with the endpoint of the sender.
  /**
   * This function is used to receive raw data. The function call will block
   * until data has been received successfully or an error occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @param sender_endpoint An endpoint object that receives the endpoint of
   * the remote sender of the data.
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
  
  /// Receive raw data with the endpoint of the sender.
  /**
   * This function is used to receive raw data. The function call will block
   * until data has been received successfully or an error occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @param sender_endpoint An endpoint object that receives the endpoint of
   * the remote sender of the data.
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
  
  /// Receive raw data with the endpoint of the sender.
  /**
   * This function is used to receive raw data. The function call will block
   * until data has been received successfully or an error occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @param sender_endpoint An endpoint object that receives the endpoint of
   * the remote sender of the data.
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
   * This function is used to asynchronously receive raw data. The function
   * call always returns immediately.
   *
   * @param buffers One or more buffers into which the data will be received.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param sender_endpoint An endpoint object that receives the endpoint of
   * the remote sender of the data. Ownership of the sender_endpoint object
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
   *     boost::asio::buffer(data, size), 0, sender_endpoint, handler); @endcode
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
   * This function is used to asynchronously receive raw data. The function
   * call always returns immediately.
   *
   * @param buffers One or more buffers into which the data will be received.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param sender_endpoint An endpoint object that receives the endpoint of
   * the remote sender of the data. Ownership of the sender_endpoint object
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

    explicit initiate_async_send(basic_raw_socket* self)
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
    basic_raw_socket* self_;
  };

  class initiate_async_send_to
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_send_to(basic_raw_socket* self)
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
    basic_raw_socket* self_;
  };

  class initiate_async_receive
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_receive(basic_raw_socket* self)
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
    basic_raw_socket* self_;
  };

  class initiate_async_receive_from
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_receive_from(basic_raw_socket* self)
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
    basic_raw_socket* self_;
  };
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_BASIC_RAW_SOCKET_HPP

/* basic_raw_socket.hpp
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
*/