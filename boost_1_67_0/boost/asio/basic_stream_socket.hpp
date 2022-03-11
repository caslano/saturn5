//
// basic_stream_socket.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_STREAM_SOCKET_HPP
#define BOOST_ASIO_BASIC_STREAM_SOCKET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <boost/asio/async_result.hpp>
#include <boost/asio/basic_socket.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if !defined(BOOST_ASIO_BASIC_STREAM_SOCKET_FWD_DECL)
#define BOOST_ASIO_BASIC_STREAM_SOCKET_FWD_DECL

// Forward declaration with defaulted arguments.
template <typename Protocol, typename Executor = executor>
class basic_stream_socket;

#endif // !defined(BOOST_ASIO_BASIC_STREAM_SOCKET_FWD_DECL)

/// Provides stream-oriented socket functionality.
/**
 * The basic_stream_socket class template provides asynchronous and blocking
 * stream-oriented socket functionality.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 *
 * @par Concepts:
 * AsyncReadStream, AsyncWriteStream, Stream, SyncReadStream, SyncWriteStream.
 */
template <typename Protocol, typename Executor>
class basic_stream_socket
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
    typedef basic_stream_socket<Protocol, Executor1> other;
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

  /// Construct a basic_stream_socket without opening it.
  /**
   * This constructor creates a stream socket without opening it. The socket
   * needs to be opened and then connected or accepted before data can be sent
   * or received on it.
   *
   * @param ex The I/O executor that the socket will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the socket.
   */
  explicit basic_stream_socket(const executor_type& ex)
    : basic_socket<Protocol, Executor>(ex)
  {
  }

  /// Construct a basic_stream_socket without opening it.
  /**
   * This constructor creates a stream socket without opening it. The socket
   * needs to be opened and then connected or accepted before data can be sent
   * or received on it.
   *
   * @param context An execution context which provides the I/O executor that
   * the socket will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the socket.
   */
  template <typename ExecutionContext>
  explicit basic_stream_socket(ExecutionContext& context,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : basic_socket<Protocol, Executor>(context)
  {
  }

  /// Construct and open a basic_stream_socket.
  /**
   * This constructor creates and opens a stream socket. The socket needs to be
   * connected or accepted before data can be sent or received on it.
   *
   * @param ex The I/O executor that the socket will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the socket.
   *
   * @param protocol An object specifying protocol parameters to be used.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_stream_socket(const executor_type& ex, const protocol_type& protocol)
    : basic_socket<Protocol, Executor>(ex, protocol)
  {
  }

  /// Construct and open a basic_stream_socket.
  /**
   * This constructor creates and opens a stream socket. The socket needs to be
   * connected or accepted before data can be sent or received on it.
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
  basic_stream_socket(ExecutionContext& context, const protocol_type& protocol,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : basic_socket<Protocol, Executor>(context, protocol)
  {
  }

  /// Construct a basic_stream_socket, opening it and binding it to the given
  /// local endpoint.
  /**
   * This constructor creates a stream socket and automatically opens it bound
   * to the specified endpoint on the local machine. The protocol used is the
   * protocol associated with the given endpoint.
   *
   * @param ex The I/O executor that the socket will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the socket.
   *
   * @param endpoint An endpoint on the local machine to which the stream
   * socket will be bound.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_stream_socket(const executor_type& ex, const endpoint_type& endpoint)
    : basic_socket<Protocol, Executor>(ex, endpoint)
  {
  }

  /// Construct a basic_stream_socket, opening it and binding it to the given
  /// local endpoint.
  /**
   * This constructor creates a stream socket and automatically opens it bound
   * to the specified endpoint on the local machine. The protocol used is the
   * protocol associated with the given endpoint.
   *
   * @param context An execution context which provides the I/O executor that
   * the socket will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the socket.
   *
   * @param endpoint An endpoint on the local machine to which the stream
   * socket will be bound.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_stream_socket(ExecutionContext& context, const endpoint_type& endpoint,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : basic_socket<Protocol, Executor>(context, endpoint)
  {
  }

  /// Construct a basic_stream_socket on an existing native socket.
  /**
   * This constructor creates a stream socket object to hold an existing native
   * socket.
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
  basic_stream_socket(const executor_type& ex,
      const protocol_type& protocol, const native_handle_type& native_socket)
    : basic_socket<Protocol, Executor>(ex, protocol, native_socket)
  {
  }

  /// Construct a basic_stream_socket on an existing native socket.
  /**
   * This constructor creates a stream socket object to hold an existing native
   * socket.
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
  basic_stream_socket(ExecutionContext& context,
      const protocol_type& protocol, const native_handle_type& native_socket,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : basic_socket<Protocol, Executor>(context, protocol, native_socket)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct a basic_stream_socket from another.
  /**
   * This constructor moves a stream socket from one object to another.
   *
   * @param other The other basic_stream_socket object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_stream_socket(const executor_type&)
   * constructor.
   */
  basic_stream_socket(basic_stream_socket&& other) BOOST_ASIO_NOEXCEPT
    : basic_socket<Protocol, Executor>(std::move(other))
  {
  }

  /// Move-assign a basic_stream_socket from another.
  /**
   * This assignment operator moves a stream socket from one object to another.
   *
   * @param other The other basic_stream_socket object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_stream_socket(const executor_type&)
   * constructor.
   */
  basic_stream_socket& operator=(basic_stream_socket&& other)
  {
    basic_socket<Protocol, Executor>::operator=(std::move(other));
    return *this;
  }

  /// Move-construct a basic_stream_socket from a socket of another protocol
  /// type.
  /**
   * This constructor moves a stream socket from one object to another.
   *
   * @param other The other basic_stream_socket object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_stream_socket(const executor_type&)
   * constructor.
   */
  template <typename Protocol1, typename Executor1>
  basic_stream_socket(basic_stream_socket<Protocol1, Executor1>&& other,
      typename enable_if<
        is_convertible<Protocol1, Protocol>::value
          && is_convertible<Executor1, Executor>::value
      >::type* = 0)
    : basic_socket<Protocol, Executor>(std::move(other))
  {
  }

  /// Move-assign a basic_stream_socket from a socket of another protocol type.
  /**
   * This assignment operator moves a stream socket from one object to another.
   *
   * @param other The other basic_stream_socket object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_stream_socket(const executor_type&)
   * constructor.
   */
  template <typename Protocol1, typename Executor1>
  typename enable_if<
    is_convertible<Protocol1, Protocol>::value
      && is_convertible<Executor1, Executor>::value,
    basic_stream_socket&
  >::type operator=(basic_stream_socket<Protocol1, Executor1>&& other)
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
  ~basic_stream_socket()
  {
  }

  /// Send some data on the socket.
  /**
   * This function is used to send data on the stream socket. The function
   * call will block until one or more bytes of the data has been sent
   * successfully, or an until error occurs.
   *
   * @param buffers One or more data buffers to be sent on the socket.
   *
   * @returns The number of bytes sent.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note The send operation may not transmit all of the data to the peer.
   * Consider using the @ref write function if you need to ensure that all data
   * is written before the blocking operation completes.
   *
   * @par Example
   * To send a single data buffer use the @ref buffer function as follows:
   * @code
   * socket.send(boost::asio::buffer(data, size));
   * @endcode
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

  /// Send some data on the socket.
  /**
   * This function is used to send data on the stream socket. The function
   * call will block until one or more bytes of the data has been sent
   * successfully, or an until error occurs.
   *
   * @param buffers One or more data buffers to be sent on the socket.
   *
   * @param flags Flags specifying how the send call is to be made.
   *
   * @returns The number of bytes sent.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note The send operation may not transmit all of the data to the peer.
   * Consider using the @ref write function if you need to ensure that all data
   * is written before the blocking operation completes.
   *
   * @par Example
   * To send a single data buffer use the @ref buffer function as follows:
   * @code
   * socket.send(boost::asio::buffer(data, size), 0);
   * @endcode
   * See the @ref buffer documentation for information on sending multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
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

  /// Send some data on the socket.
  /**
   * This function is used to send data on the stream socket. The function
   * call will block until one or more bytes of the data has been sent
   * successfully, or an until error occurs.
   *
   * @param buffers One or more data buffers to be sent on the socket.
   *
   * @param flags Flags specifying how the send call is to be made.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes sent. Returns 0 if an error occurred.
   *
   * @note The send operation may not transmit all of the data to the peer.
   * Consider using the @ref write function if you need to ensure that all data
   * is written before the blocking operation completes.
   */
  template <typename ConstBufferSequence>
  std::size_t send(const ConstBufferSequence& buffers,
      socket_base::message_flags flags, boost::system::error_code& ec)
  {
    return this->impl_.get_service().send(
        this->impl_.get_implementation(), buffers, flags, ec);
  }

  /// Start an asynchronous send.
  /**
   * This function is used to asynchronously send data on the stream socket.
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
   * @note The send operation may not transmit all of the data to the peer.
   * Consider using the @ref async_write function if you need to ensure that all
   * data is written before the asynchronous operation completes.
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

  /// Start an asynchronous send.
  /**
   * This function is used to asynchronously send data on the stream socket.
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
   * @note The send operation may not transmit all of the data to the peer.
   * Consider using the @ref async_write function if you need to ensure that all
   * data is written before the asynchronous operation completes.
   *
   * @par Example
   * To send a single data buffer use the @ref buffer function as follows:
   * @code
   * socket.async_send(boost::asio::buffer(data, size), 0, handler);
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
      socket_base::message_flags flags,
      BOOST_ASIO_MOVE_ARG(WriteHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WriteHandler,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_send(this), handler, buffers, flags);
  }

  /// Receive some data on the socket.
  /**
   * This function is used to receive data on the stream socket. The function
   * call will block until one or more bytes of data has been received
   * successfully, or until an error occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @returns The number of bytes received.
   *
   * @throws boost::system::system_error Thrown on failure. An error code of
   * boost::asio::error::eof indicates that the connection was closed by the
   * peer.
   *
   * @note The receive operation may not receive all of the requested number of
   * bytes. Consider using the @ref read function if you need to ensure that the
   * requested amount of data is read before the blocking operation completes.
   *
   * @par Example
   * To receive into a single data buffer use the @ref buffer function as
   * follows:
   * @code
   * socket.receive(boost::asio::buffer(data, size));
   * @endcode
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

  /// Receive some data on the socket.
  /**
   * This function is used to receive data on the stream socket. The function
   * call will block until one or more bytes of data has been received
   * successfully, or until an error occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @param flags Flags specifying how the receive call is to be made.
   *
   * @returns The number of bytes received.
   *
   * @throws boost::system::system_error Thrown on failure. An error code of
   * boost::asio::error::eof indicates that the connection was closed by the
   * peer.
   *
   * @note The receive operation may not receive all of the requested number of
   * bytes. Consider using the @ref read function if you need to ensure that the
   * requested amount of data is read before the blocking operation completes.
   *
   * @par Example
   * To receive into a single data buffer use the @ref buffer function as
   * follows:
   * @code
   * socket.receive(boost::asio::buffer(data, size), 0);
   * @endcode
   * See the @ref buffer documentation for information on receiving into
   * multiple buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
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
   * This function is used to receive data on the stream socket. The function
   * call will block until one or more bytes of data has been received
   * successfully, or until an error occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @param flags Flags specifying how the receive call is to be made.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes received. Returns 0 if an error occurred.
   *
   * @note The receive operation may not receive all of the requested number of
   * bytes. Consider using the @ref read function if you need to ensure that the
   * requested amount of data is read before the blocking operation completes.
   */
  template <typename MutableBufferSequence>
  std::size_t receive(const MutableBufferSequence& buffers,
      socket_base::message_flags flags, boost::system::error_code& ec)
  {
    return this->impl_.get_service().receive(
        this->impl_.get_implementation(), buffers, flags, ec);
  }

  /// Start an asynchronous receive.
  /**
   * This function is used to asynchronously receive data from the stream
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
   * @note The receive operation may not receive all of the requested number of
   * bytes. Consider using the @ref async_read function if you need to ensure
   * that the requested amount of data is received before the asynchronous
   * operation completes.
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

  /// Start an asynchronous receive.
  /**
   * This function is used to asynchronously receive data from the stream
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
   * @note The receive operation may not receive all of the requested number of
   * bytes. Consider using the @ref async_read function if you need to ensure
   * that the requested amount of data is received before the asynchronous
   * operation completes.
   *
   * @par Example
   * To receive into a single data buffer use the @ref buffer function as
   * follows:
   * @code
   * socket.async_receive(boost::asio::buffer(data, size), 0, handler);
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
      socket_base::message_flags flags,
      BOOST_ASIO_MOVE_ARG(ReadHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<ReadHandler,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_receive(this), handler, buffers, flags);
  }

  /// Write some data to the socket.
  /**
   * This function is used to write data to the stream socket. The function call
   * will block until one or more bytes of the data has been written
   * successfully, or until an error occurs.
   *
   * @param buffers One or more data buffers to be written to the socket.
   *
   * @returns The number of bytes written.
   *
   * @throws boost::system::system_error Thrown on failure. An error code of
   * boost::asio::error::eof indicates that the connection was closed by the
   * peer.
   *
   * @note The write_some operation may not transmit all of the data to the
   * peer. Consider using the @ref write function if you need to ensure that
   * all data is written before the blocking operation completes.
   *
   * @par Example
   * To write a single data buffer use the @ref buffer function as follows:
   * @code
   * socket.write_some(boost::asio::buffer(data, size));
   * @endcode
   * See the @ref buffer documentation for information on writing multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = this->impl_.get_service().send(
        this->impl_.get_implementation(), buffers, 0, ec);
    boost::asio::detail::throw_error(ec, "write_some");
    return s;
  }

  /// Write some data to the socket.
  /**
   * This function is used to write data to the stream socket. The function call
   * will block until one or more bytes of the data has been written
   * successfully, or until an error occurs.
   *
   * @param buffers One or more data buffers to be written to the socket.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes written. Returns 0 if an error occurred.
   *
   * @note The write_some operation may not transmit all of the data to the
   * peer. Consider using the @ref write function if you need to ensure that
   * all data is written before the blocking operation completes.
   */
  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers,
      boost::system::error_code& ec)
  {
    return this->impl_.get_service().send(
        this->impl_.get_implementation(), buffers, 0, ec);
  }

  /// Start an asynchronous write.
  /**
   * This function is used to asynchronously write data to the stream socket.
   * The function call always returns immediately.
   *
   * @param buffers One or more data buffers to be written to the socket.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param handler The handler to be called when the write operation completes.
   * Copies will be made of the handler as required. The function signature of
   * the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes written.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @note The write operation may not transmit all of the data to the peer.
   * Consider using the @ref async_write function if you need to ensure that all
   * data is written before the asynchronous operation completes.
   *
   * @par Example
   * To write a single data buffer use the @ref buffer function as follows:
   * @code
   * socket.async_write_some(boost::asio::buffer(data, size), handler);
   * @endcode
   * See the @ref buffer documentation for information on writing multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename ConstBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) WriteHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
      void (boost::system::error_code, std::size_t))
  async_write_some(const ConstBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(WriteHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WriteHandler,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_send(this), handler,
        buffers, socket_base::message_flags(0));
  }

  /// Read some data from the socket.
  /**
   * This function is used to read data from the stream socket. The function
   * call will block until one or more bytes of data has been read successfully,
   * or until an error occurs.
   *
   * @param buffers One or more buffers into which the data will be read.
   *
   * @returns The number of bytes read.
   *
   * @throws boost::system::system_error Thrown on failure. An error code of
   * boost::asio::error::eof indicates that the connection was closed by the
   * peer.
   *
   * @note The read_some operation may not read all of the requested number of
   * bytes. Consider using the @ref read function if you need to ensure that
   * the requested amount of data is read before the blocking operation
   * completes.
   *
   * @par Example
   * To read into a single data buffer use the @ref buffer function as follows:
   * @code
   * socket.read_some(boost::asio::buffer(data, size));
   * @endcode
   * See the @ref buffer documentation for information on reading into multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = this->impl_.get_service().receive(
        this->impl_.get_implementation(), buffers, 0, ec);
    boost::asio::detail::throw_error(ec, "read_some");
    return s;
  }

  /// Read some data from the socket.
  /**
   * This function is used to read data from the stream socket. The function
   * call will block until one or more bytes of data has been read successfully,
   * or until an error occurs.
   *
   * @param buffers One or more buffers into which the data will be read.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes read. Returns 0 if an error occurred.
   *
   * @note The read_some operation may not read all of the requested number of
   * bytes. Consider using the @ref read function if you need to ensure that
   * the requested amount of data is read before the blocking operation
   * completes.
   */
  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers,
      boost::system::error_code& ec)
  {
    return this->impl_.get_service().receive(
        this->impl_.get_implementation(), buffers, 0, ec);
  }

  /// Start an asynchronous read.
  /**
   * This function is used to asynchronously read data from the stream socket.
   * The function call always returns immediately.
   *
   * @param buffers One or more buffers into which the data will be read.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param handler The handler to be called when the read operation completes.
   * Copies will be made of the handler as required. The function signature of
   * the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes read.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @note The read operation may not read all of the requested number of bytes.
   * Consider using the @ref async_read function if you need to ensure that the
   * requested amount of data is read before the asynchronous operation
   * completes.
   *
   * @par Example
   * To read into a single data buffer use the @ref buffer function as follows:
   * @code
   * socket.async_read_some(boost::asio::buffer(data, size), handler);
   * @endcode
   * See the @ref buffer documentation for information on reading into multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename MutableBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) ReadHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
      void (boost::system::error_code, std::size_t))
  async_read_some(const MutableBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(ReadHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<ReadHandler,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_receive(this), handler,
        buffers, socket_base::message_flags(0));
  }

private:
  class initiate_async_send
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_send(basic_stream_socket* self)
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
    basic_stream_socket* self_;
  };

  class initiate_async_receive
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_receive(basic_stream_socket* self)
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
    basic_stream_socket* self_;
  };
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_BASIC_STREAM_SOCKET_HPP

/* basic_stream_socket.hpp
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
*/