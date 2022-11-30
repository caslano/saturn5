//
// basic_stream_socket.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
template <typename Protocol, typename Executor = any_io_executor>
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
 * Synchronous @c send, @c receive, and @c connect operations are thread safe
 * with respect to each other, if the underlying operating system calls are
 * also thread safe. This means that it is permitted to perform concurrent
 * calls to these synchronous operations on a single socket object. Other
 * synchronous operations, such as @c open or @c close, are not thread safe.
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
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
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
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
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
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
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
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
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
      typename constraint<
        is_convertible<Protocol1, Protocol>::value
          && is_convertible<Executor1, Executor>::value
      >::type = 0)
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
  typename constraint<
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
   * It is an initiating function for an @ref asynchronous_operation, and always
   * returns immediately.
   *
   * @param buffers One or more data buffers to be sent on the socket. Although
   * the buffers object may be copied as necessary, ownership of the underlying
   * memory blocks is retained by the caller, which must guarantee that they
   * remain valid until the completion handler is called.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the send completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred // Number of bytes sent.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Completion Signature
   * @code void(boost::system::error_code, std::size_t) @endcode
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
   *
   * @par Per-Operation Cancellation
   * On POSIX or Windows operating systems, this asynchronous operation supports
   * cancellation for the following boost::asio::cancellation_type values:
   *
   * @li @c cancellation_type::terminal
   *
   * @li @c cancellation_type::partial
   *
   * @li @c cancellation_type::total
   */
  template <typename ConstBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) WriteToken
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
      void (boost::system::error_code, std::size_t))
  async_send(const ConstBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(WriteToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WriteToken,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_send(this), token,
        buffers, socket_base::message_flags(0));
  }

  /// Start an asynchronous send.
  /**
   * This function is used to asynchronously send data on the stream socket.
   * It is an initiating function for an @ref asynchronous_operation, and always
   * returns immediately.
   *
   * @param buffers One or more data buffers to be sent on the socket. Although
   * the buffers object may be copied as necessary, ownership of the underlying
   * memory blocks is retained by the caller, which must guarantee that they
   * remain valid until the completion handler is called.
   *
   * @param flags Flags specifying how the send call is to be made.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the send completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred // Number of bytes sent.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Completion Signature
   * @code void(boost::system::error_code, std::size_t) @endcode
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
   *
   * @par Per-Operation Cancellation
   * On POSIX or Windows operating systems, this asynchronous operation supports
   * cancellation for the following boost::asio::cancellation_type values:
   *
   * @li @c cancellation_type::terminal
   *
   * @li @c cancellation_type::partial
   *
   * @li @c cancellation_type::total
   */
  template <typename ConstBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) WriteToken
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
      void (boost::system::error_code, std::size_t))
  async_send(const ConstBufferSequence& buffers,
      socket_base::message_flags flags,
      BOOST_ASIO_MOVE_ARG(WriteToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WriteToken,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_send(this), token, buffers, flags);
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
   * socket. It is an initiating function for an @ref asynchronous_operation,
   * and always returns immediately.
   *
   * @param buffers One or more buffers into which the data will be received.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the completion handler is called.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the receive completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred // Number of bytes received.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Completion Signature
   * @code void(boost::system::error_code, std::size_t) @endcode
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
   *
   * @par Per-Operation Cancellation
   * On POSIX or Windows operating systems, this asynchronous operation supports
   * cancellation for the following boost::asio::cancellation_type values:
   *
   * @li @c cancellation_type::terminal
   *
   * @li @c cancellation_type::partial
   *
   * @li @c cancellation_type::total
   */
  template <typename MutableBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) ReadToken
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
      void (boost::system::error_code, std::size_t))
  async_receive(const MutableBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(ReadToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<ReadToken,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_receive(this), token,
        buffers, socket_base::message_flags(0));
  }

  /// Start an asynchronous receive.
  /**
   * This function is used to asynchronously receive data from the stream
   * socket. It is an initiating function for an @ref asynchronous_operation,
   * and always returns immediately.
   *
   * @param buffers One or more buffers into which the data will be received.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the completion handler is called.
   *
   * @param flags Flags specifying how the receive call is to be made.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the receive completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred // Number of bytes received.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Completion Signature
   * @code void(boost::system::error_code, std::size_t) @endcode
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
   *
   * @par Per-Operation Cancellation
   * On POSIX or Windows operating systems, this asynchronous operation supports
   * cancellation for the following boost::asio::cancellation_type values:
   *
   * @li @c cancellation_type::terminal
   *
   * @li @c cancellation_type::partial
   *
   * @li @c cancellation_type::total
   */
  template <typename MutableBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) ReadToken
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
      void (boost::system::error_code, std::size_t))
  async_receive(const MutableBufferSequence& buffers,
      socket_base::message_flags flags,
      BOOST_ASIO_MOVE_ARG(ReadToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<ReadToken,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_receive(this), token, buffers, flags);
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
   * It is an initiating function for an @ref asynchronous_operation, and always
   * returns immediately.
   *
   * @param buffers One or more data buffers to be written to the socket.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the completion handler is called.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the write completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred // Number of bytes written.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Completion Signature
   * @code void(boost::system::error_code, std::size_t) @endcode
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
   *
   * @par Per-Operation Cancellation
   * On POSIX or Windows operating systems, this asynchronous operation supports
   * cancellation for the following boost::asio::cancellation_type values:
   *
   * @li @c cancellation_type::terminal
   *
   * @li @c cancellation_type::partial
   *
   * @li @c cancellation_type::total
   */
  template <typename ConstBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) WriteToken
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
      void (boost::system::error_code, std::size_t))
  async_write_some(const ConstBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(WriteToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WriteToken,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_send(this), token,
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
   * socket. It is an initiating function for an @ref asynchronous_operation,
   * and always returns immediately.
   *
   * @param buffers One or more buffers into which the data will be read.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the completion handler is called.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the read completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred // Number of bytes read.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Completion Signature
   * @code void(boost::system::error_code, std::size_t) @endcode
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
   *
   * @par Per-Operation Cancellation
   * On POSIX or Windows operating systems, this asynchronous operation supports
   * cancellation for the following boost::asio::cancellation_type values:
   *
   * @li @c cancellation_type::terminal
   *
   * @li @c cancellation_type::partial
   *
   * @li @c cancellation_type::total
   */
  template <typename MutableBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) ReadToken
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
      void (boost::system::error_code, std::size_t))
  async_read_some(const MutableBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(ReadToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<ReadToken,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_receive(this), token,
        buffers, socket_base::message_flags(0));
  }

private:
  // Disallow copying and assignment.
  basic_stream_socket(const basic_stream_socket&) BOOST_ASIO_DELETED;
  basic_stream_socket& operator=(const basic_stream_socket&) BOOST_ASIO_DELETED;

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
          handler2.value, self_->impl_.get_executor());
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
          handler2.value, self_->impl_.get_executor());
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
CL6wTL0AdgZo5kDsPkgXQ+VD6Du7sjb1mEhKBFdKxQ0IIKSUslpUtGQXgg3RjeiscR90vLMsZeNhspcYfIJidXZGAfhlfSThkV5nuxRU0aBmMsa8VlP79JSFZ8IZX0BsZymk3e5f+NwkTXEKgs6S9WkMt2YiMcXcVwP9mY59XIPN7iNyOMzZvrlcILF8GXwxDlwmyZFZH2Lz1FUoD/OxTJGvPd48Jis9hxkrJQ4XOu5DfghjpprMpBUTa0293LTuFySUGeRzzWCw/VZ6WSkyP+TlKMY3vXHvJQpLiuLPxQUTkzOZPk13aiqKQdaU7NbjRt1serFHb+1QtcSPNs+OUTHPau5Y9huWDox6cLaCOuIsBdx9vTrHZlyoem6bffQ0JOlFF8+dt2RwQZUksnWmYdseNr4wg0Z2EijWGsXh3OscA6ve15yQWg6h2tX1XwW0lWo14GHXesx/n2IWHfO8Gh2b44LQVuRt1Zp5aDF0XoIpmxWhZphbjuyujf+pfNhSYo71Dqge/9Qs0aAv/ODoDH3gqv8gavhtlQkCFRD4HjcQfWlNAxHu9gv8dEV9ZMDGwoBFTB+ms8AGBI5PDpT+PT9M1FiRrireJLZJ/5zR6PjMSCsWEUQ/T5rc03CrQAN/0T2A3YfU9fChb6V8VTEZFXnEaLIscG5u7tm1vul489fgwJWSpvHSuWMfUgQLr7PJohllVoUcd8XBGeHCHlBrucykm8k6LD6Mc7jNlr4Mr4yQk+QNKGk75JW3nDZsO/mMiJDD5A0teUXhZ9OSfNEIfD9sO6rtzJ7GedeDM1vshaxncPRM9tU4mSdIb14WdD2lCZsOP8XeRe3FueqZmF+PhiIVWoc3EnVdc/3D+qDyo1cadiU+yLROSu1z96Skyrocwn3duUZC0xlm1RMcts8lVbtHLKS4A9uT/DSZrSt4Bh+V5k1fnc6Zwg6Aawg8tYcOA793qdQQKXmOzpbJFxrAr6qUtiIXTN0zW+Nz5FDhv3cW0y0hKprtREo+ye0Jz71wW0bW7LfweJtWqnvK5BIg+DVaX0nVP4lyYr4Qdn8vaecdkeXpdmgK02mLtwflMEyNZzio2xqPhSr/92pTXjlkEMmCfp+Q9XwIDdfoXn1BfoA9JT1vXK8ZhGaRXteCXqj9cHtCBuwFU3QsoW+w+nxN2RVf24fxgbBPdMHpXwPDRs8zStiiWs4c5qE+q3U2/1DyWlyTG7sAAiz900mZ9hSGuDb/RfOcnYtceIdJRr/JnrFl5VggxwJmZ8ZrRuxGJHo1/gNjD2vRpBupe8Kg5U7V6zbcnIGte+vt2jFZcvU8Frg5X1V9PrYFQCLnDgawPW0hqy3AX0AmCHxcwq/3m4MX2dNeJo3UXthn+6CvDYOfG0aN5f9dafnflecfsiDTA4NvfNxQgDdeGMFvajBoIIAggK8yBhAmDihlAsaowiJlWqrMW/6sk6+n4eIf/pAUgVPblJgj06Gene6Nn+FpT+ayNOtHe0kZGS9LyCl5mjmSh4azM3X9MHU9JrCEuLEREx5ZN1v9Edd8uySZp5pxKta78cNM/VHVmXLmXtJoMvyPmU/jhqlJKcmFd6nD8bHeRBZZ4Pz10ItWff7PQTaujcCL/Qs4z0qf/oix2FmTdD61I3V9GWMoHBD84zBA7qtBNgcJEBPfNM0y6DdVKbmw8IvEqiaCXtqCHoQ3nOUl10WvlgbqzLBzoepNN92EuF58FO8S0NFLmXMUPNNEbjwVyu3xQic9egW+VBF+z9ftrhmbjWlbteMfidOoBv0nBU8udk2sHsL19/ak87GUdxB67mH5Y+GwKDnyNjsHJaEnCSAzVRWtlxMscvIW/Mkbu7IcvNuy/VGcAyiSGSEey0IfRRIdCbE/0fDIlNBAvr2rQD9Was6f+FNWmsLo6MpEtmSFefpbP0WcdHsmp2/0qw4/CFCm5m87cs5xR3cosmW+RBxzzn6KtJuYlEVszMmZGIdMqAvgaL1S7kZn+JoFNmtkSgBOtGZvs1pFK6+FoMK5zn0x2jmA/Ht/UiF8AAmvBPX4yo7Vvycg5HHR3iZ1lAViQj7BzQbjJxvKS7KHSpsl/NX50Hq4YxB9pTsxPTz6Amdim4rjw7RaC17ca99DagIbblQnSYd5btYJmrfFgUaMk0FPmXvvTdqhTQ+1KxywuiVu2yZSb8YVF6p37iMTDKmNZBLJWxec5nIN2Zd3wQuv1tIkPA/cwN/7GFHKPbfDEI7blPWiKUc0uoo4TvIOl174w/qPdJq2wuGal1qwsThgGnUpcv3dtYF93r2hfcEpAL9HED/AzcJHZ2DQpb245/JW0sKVkrMyEhKiIiISYs5O0lKSYhNiAhMSAs9fjJ7lRJJFegvAEgJDuqO6G0O6gRPCmbATqgrqS7ZqjanANL2SelW+VP4NTA7/mx6enBQZGX3vpAIl90JWN17I6/jupmrMI3+VXtIXQSv1C6+m1vbMQGJkZqJY2+hE+OpPrmduJDd6D1IlrpiaGPhHMfzWiH4pMylUZZOdrVMoRHQ5UDg5YKSzX7hfdfkp0lV4KTSwf0mEozNwaVNFU0hTOKljRJQ9KbSfvX8pIzRp9OnnIMWaLDOFsegnp3Wsn/QcFzEy9rqC8vEFB3x3gnYJC7H7BSsVAPCRF/+CDEg4DiggIQ6AYAYMEPwABpDwDCgA4wuA8IED8G8GGCACFVCACQEg3ggRoDgSBKC8HfDHsCpbFyZHhydbZsogHYMzA8NwdPTf4dBP6fz3ioqWGd3yT6LUxEHpIGDZhjPRIRSyHMnZwZBgySVkk1Kk3CYmz20buBD45bQnwBl/hUabANKbIZBvl06PzI0a3Tq/Vw+j7z0jC+m2XQ8VWeLAo4eRDYApuqmotaLHhYywxtd63GDHmoxET3J0i1+t7m+ylGf4fQ7MfsJepOLxVZzCc9B8G5tUPllgzrtJu3Of6XkG8shYCKxUjdboke0B5MVp31SFdNPMA9KowboMNGcWol/firQDO7KcyhZPud7zaPCqLc7v02+jcjjJjHfm/R1V34SVnIy7w72ZEBdBBYVwKZfpISl8E5UjG+8g5SbODv6AM+kqQlpcuC1OJ3Ky5KFdkZJlDjR6jgpc6jrK5qhDaGSzPxZ+RCUh93dxB/k4tL4X+anEpa2Jsbjf6SJNM5agX/dfAYU+cVS9rL8fEko71+oUsLGk5Q58TbbWR+Ck532U6JgXiRhXedLffHp4thFu2ygLbQJ2RGepYwlUx3NHoT9ZHmyfUxEER8B60WFQDk2LpV2UCVfWQyedg+Ge33WlYyjLpx38GsnKwDfnpl9kkw1VPaTcF4SrbBkOjA4g5goOd9zHBr1pVRVCFREuG+heUS0Bxj4We3i1Y2QfMkT2zn5ojPpV0m+nRNBSqoZtabGVKnP7yYMWIJqXZC+xkV/rF+DWPkMOP9DNJZnKVqBLwG63YHvDlSMPC4MuLptLW7Yrs6GNUHtT5Tp62ckEOoDnQL114jQPp/1sQvcIm7a2+B+p4dhlvZfnzYjecyZXMTNBwuQDDiAfEFB7gudFJ8C17a6JkqkxvT31bqharTgOR+xMV+P0TNXu6/sOuxHW/yo8lyEkywUkwcB20BtmfgRKtz5VLDHyNFS8PgUvHtEzlpeO6NgR+WjBR7jzSzFmPIk0MyfQCSqCuYlH0NDI/KE916VCOMIODM9sY6/M7hZxXL2MHLyTeaEaSJ9hg7KYRt60sM+xVVe90dc6+ZLNHC60hyqDXwArl61pPzoMSFIeVZRdSNvyzMnVuAmJB7Ni0XcatGtvd6mGC3rp2T0b/ebSYc1bPS+lf9xnOP9RdBP51lGx5AmKxVK3WAmNLkV/81UM2vwpBi9CabHptdQEbVRYiwUDI4qk/WMKKTc9HBvaYK78b+z5IfbUfK5mKI6aYfrBFabsL9kcD4jaMiDqYA0XDygFPrQ2tWH089v5ROTLsQsLOtIbzklYKRy3S8k7RbXyHKjViLGCKWMdYc+ENd1Ce4Yu59qcBvi1J2OZ9qDx4SmOSWRbe1DtrX3uot+hAaLhoNVhC2v4TH/fC4uVc5p9HWeOViZsvrRm4HOL899vJSOaoKVSe8Juea0THu5xFXh0rrI0igua7w2UNnsqfov5jv6XHUYWkSihyGXTTnh23oJi/KoK3bh19DWt+QwcrFvvuDJ3tBG34+peoxB3Aqa8cDb+vd/NuC6+R82xQxf0s865uhhdUxZ8+PviIr9NgJK2z2+Yf4tKqaWjwM2tDfCWbanBbvj+atGZadeUiqYGitQVrJ0UddVWbpSwa3holZmLjPqLLuOTWFgGAg+Y7BxxhT7mOhBe45y43tzm29urdC1Jt/Ulaa5HInsITOl5HZ3fBALzqshZJXfhRLuVWPiSu8OuUXQ+6tyq68l0StW3tpVA7LW4YLGj4m9/fwhZDe3IP6A19Ybuy98jJ3xM6n1w9Vi1WpPj4B6kohWu94M/GWD6lobz+5HEUUfj52zwc9z3PRXwlQX8wQ7+bA93uYOz2stZ93/p+CnjqPNTPv+Ge/3Bvf3h3v3Bh0lNSTnyi+03+tFxBhT4sZwC/V4w8qPtCPeLeg0C6P8xrIYBefPAFokmKjbB0PjQB/3wyzWxqVpYLQwWnVtJkT/l5x9dJjvGWq42vrXA6EIncGuC5CRwxb5ezR3S9ZnG+Cs8Bafr4YZPanzjXSIYdSdN+6dpDj4cnPdiK2LjoOTn04BNcoXSR7hXRW7ZZXF1hT4syjaA6vhZMQTrKw2pxdX6nfx5HKozZTV8HFf2pURM27hVFV3TK7s25yCv2jHLFUoWhjvNoNql2ZRS7Vu5/Sj6JM6B2//2xv3jZ+fg6odod/o9D3wTE3MNkzOdA6Mdo/37A+iaKFsGR+iyMLuwioaoSoeoUEjo94yzKYzmVxZpw1hrf41wHxLNEOUc+vdPI8RXdGNNJKN9NXiIg4OjjSNkjXNoCPMHH2Rz75tw1w4GQEgJ2J/hDIAAhxogPPmDGX8PNtz3xznu9VnbAe8DGSD8AwhgXx3YHwTsp9P/Y+a4/gfX/oc/prWxof4z7c61VEUXimMrN6aHk6oLoZ/Ad00RtdtOrUJ9vuDuMqc5iGB+Kg0RAXe7JeoCHeXvjTiDb5dv1/z2DX7szvoX4Dw27PLfhSn2P82wE/Bl+Wgmj8YOY1Wl8rik81qNXwynzFP3WOWPnB8n1JPjj2ary7V8DhbfYiVr4Cc6NYjWy/eMKA+THawv2pxk5rkxTfBg681WwpPQZNvLbSMOz+IdPrZ5YWoNJEjFSyBywPLch6o8XXmvQ5kcFKGJ4JWa2ce2KDk21OSUGVkxsdY0ECvO5hlJTdXjn+dIcjTlRGodQ2eKqta1JRNxdVFQMNoZ2unFjqkcZajmMkoj1aNJvaiPC/SMC08LS6QSdHKzKLS4E1VLyNJgqmXwS6nn4+3vfRtZurx2drErsPFLuTPL8eV7tLZU9XJnMUWrOhs2kcFXsrGPl3E5GPWI6yjazaAnLnKZnBjxKCZWovUlCVeqC/mb1jI7iFW9yjHDRwm5cmCanKeIeo3vRL25uzq4TgYJuud6DkkcPd98TMo2252euEub7AQuglgkZ0ml4/hxdYH3sRVV+pkvfMws9iPacSz9ZrsQaiW789blWLgFyurmqKl93XYv6OZhHPdzYwH5tq8PiGpXV5J47Y82aEq2J3Jh+zeUV+t/Td+DW29LThQ0KqUZRkKQ/8X2FjSFFM8X8qe9ZI/kuN11e/L14km4817ZwJxRpxHzVSTIfNFHbYkg8+D+5zeil1seLCo/P+AOSsk0Y9Nlo4k+GYZm0abjTMTByaQwDTedJMxUKSzpJrQypTSIRNG02spB4fU3RJ0YZNLh8D5nD285M06+O0fevTsPvHn8x3FeM7wv34437S+bXts3H75debVkjIbNcu67kFvx4H3335BsC6Ne5SiSNYr2W/RfJLAhVkmf0mNnl9mNb+YxECBjR0Z5qYURqtmt2ZvxygvP6rXPxcDCSujX5Jm4iqluKLLM+FV8GLVb7bNo4X7LNJlB8DJZs+60ZX/mzJvcwcyvzRzBngvzwuiJuCH8VEW68phpVQkhO5MOePTMuuBQxXpYhdrPyPURxk+9so79zdvRK+jSLS/c74qLBUZdrNU9mzNFo6gJVPmykD2Ib5h3VtQa1A8Be952nvaddB50JW/1MfkMUFPDcyPTsuu5FvURrlKXqKnTkz/aHU3/LVlEG75vMbxPyNLMJ8bMfbarnTcPmFwqjKwrZQ0HjwW9vInCnOB6c+fTjaikVEgxuF/Q0wPQQ266y/OzseF1avFS7ZK2qTvEVmrji5uwNu08G5kAnThEdfrW13pua9MQ2Rb6W7nZu6uVlsax9b8duGjH8nd1AFHzGHodCpNP4wDrcnJKeAieC2oplQiRQ63SK1zYPNbggIuK74GbYTFGz7XKSECOraQqv1o7bE06jcRfRueaOIkNCFW0LLBCj2U4gPS0MoX4JnTl6adwlsl8kfaO46pu2U0DpE0f0rw4WkN7JVAONvyrJKyM8TgShnQ4aO+TcWmBcSHWJUGDXDxM73fyZP6b9SXEI48PPaesBWCOh2aupiSFaW2+kQmjC8wajOcTqRzhRWPSfWi5cIXYbYVP+zxl/tx8IJhnCrNjinL/FhT//sfeOKOjin3R2WmQm3Cm9lRGPfnEUcK+vKLk2WYBs/c8Xjzx3Zq6SK0yL7VvlL6GH8+RH5eJnl+5x3Z2Rv35HHokpv8GDJT9m2W/h0SLB0ka6mswvHNItj41x7kUbG8/E/A7GtM/gzt57O/fOPQspoZ2RgQiodJbgnpnK+FXaRfAiKa++WMLdUpBNVYqbu7OJTDbwvuxODNz6k5XNj7Wd8tkyQ7ZJsY6ryJEdJyESuHh7nZwx3Z0rVoDgk4NhfSYzEjESUsjh2GhG6jUk79/isOJVj5msa/VIrhz2BTysj9ugN/AtTDlU68ewRYRDh81i2mYiBLFOtXFSKtHh23y1EkbIdrF5GCIMZ1DNYUrX6rsp/ACJQJFyBBS8TPW5dHGUm67ehwCNli7RNJkrYhJSO+7/O2oyG2cfVr10GA3ugNCFwPI0Rso2NcuyXoXOABigGf/69Cn7/7Nf1o7BPi9eMblcErw5Vsm7f0Th8wLPNjPDwqAA+5AleEAGowO3Hz58+pp57ehUeL7LkyOtZ16csS3Yoz9Qck19Se/k7lVLXwU2lcxO8kSyfMYjv7nkYLu6/NwL8XQ369j6uSYssGoSufsxlXar6zTxMx5LeOyNdGoPiWT/UeOj4GpvqSnbGUgmx+h7HvzYv9b5icNFq+zSnFZ0GewO4X+KnwIjK98sAB18y2rgdQebh0mGe5qu5bOlXZjr+149rod9DbLq5vVNiWUV7l++ZbO2JBwbFDcw60qK4224+/spajpy7NsUOphAjaiWWipapv4/gIYn3nTfe4J4RjYHfUaqtDMJF3GWGckOzom96KXTQCfMg3aFUIzliL3mzMp/imH6t8QMurysq+R+IyF8RPyi4o/2ptk92slN16oERKVdDb7k5dlshpJpbsdbOycRVCLD3Ipi5szuhSZAu2jG8mqWFGj1CSIy9oJS7m+Z1wS3JgvQyOq/T4H5y/UF5Od0hxg
*/