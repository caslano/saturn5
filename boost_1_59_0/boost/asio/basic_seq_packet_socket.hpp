//
// basic_seq_packet_socket.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_SEQ_PACKET_SOCKET_HPP
#define BOOST_ASIO_BASIC_SEQ_PACKET_SOCKET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <boost/asio/basic_socket.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if !defined(BOOST_ASIO_BASIC_SEQ_PACKET_SOCKET_FWD_DECL)
#define BOOST_ASIO_BASIC_SEQ_PACKET_SOCKET_FWD_DECL

// Forward declaration with defaulted arguments.
template <typename Protocol, typename Executor = any_io_executor>
class basic_seq_packet_socket;

#endif // !defined(BOOST_ASIO_BASIC_SEQ_PACKET_SOCKET_FWD_DECL)

/// Provides sequenced packet socket functionality.
/**
 * The basic_seq_packet_socket class template provides asynchronous and blocking
 * sequenced packet socket functionality.
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
 */
template <typename Protocol, typename Executor>
class basic_seq_packet_socket
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
    typedef basic_seq_packet_socket<Protocol, Executor1> other;
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

  /// Construct a basic_seq_packet_socket without opening it.
  /**
   * This constructor creates a sequenced packet socket without opening it. The
   * socket needs to be opened and then connected or accepted before data can
   * be sent or received on it.
   *
   * @param ex The I/O executor that the socket will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the socket.
   */
  explicit basic_seq_packet_socket(const executor_type& ex)
    : basic_socket<Protocol, Executor>(ex)
  {
  }

  /// Construct a basic_seq_packet_socket without opening it.
  /**
   * This constructor creates a sequenced packet socket without opening it. The
   * socket needs to be opened and then connected or accepted before data can
   * be sent or received on it.
   *
   * @param context An execution context which provides the I/O executor that
   * the socket will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the socket.
   */
  template <typename ExecutionContext>
  explicit basic_seq_packet_socket(ExecutionContext& context,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
    : basic_socket<Protocol, Executor>(context)
  {
  }

  /// Construct and open a basic_seq_packet_socket.
  /**
   * This constructor creates and opens a sequenced_packet socket. The socket
   * needs to be connected or accepted before data can be sent or received on
   * it.
   *
   * @param ex The I/O executor that the socket will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the socket.
   *
   * @param protocol An object specifying protocol parameters to be used.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_seq_packet_socket(const executor_type& ex,
      const protocol_type& protocol)
    : basic_socket<Protocol, Executor>(ex, protocol)
  {
  }

  /// Construct and open a basic_seq_packet_socket.
  /**
   * This constructor creates and opens a sequenced_packet socket. The socket
   * needs to be connected or accepted before data can be sent or received on
   * it.
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
  basic_seq_packet_socket(ExecutionContext& context,
      const protocol_type& protocol,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : basic_socket<Protocol, Executor>(context, protocol)
  {
  }

  /// Construct a basic_seq_packet_socket, opening it and binding it to the
  /// given local endpoint.
  /**
   * This constructor creates a sequenced packet socket and automatically opens
   * it bound to the specified endpoint on the local machine. The protocol used
   * is the protocol associated with the given endpoint.
   *
   * @param ex The I/O executor that the socket will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the socket.
   *
   * @param endpoint An endpoint on the local machine to which the sequenced
   * packet socket will be bound.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_seq_packet_socket(const executor_type& ex,
      const endpoint_type& endpoint)
    : basic_socket<Protocol, Executor>(ex, endpoint)
  {
  }

  /// Construct a basic_seq_packet_socket, opening it and binding it to the
  /// given local endpoint.
  /**
   * This constructor creates a sequenced packet socket and automatically opens
   * it bound to the specified endpoint on the local machine. The protocol used
   * is the protocol associated with the given endpoint.
   *
   * @param context An execution context which provides the I/O executor that
   * the socket will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the socket.
   *
   * @param endpoint An endpoint on the local machine to which the sequenced
   * packet socket will be bound.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_seq_packet_socket(ExecutionContext& context,
      const endpoint_type& endpoint,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
    : basic_socket<Protocol, Executor>(context, endpoint)
  {
  }

  /// Construct a basic_seq_packet_socket on an existing native socket.
  /**
   * This constructor creates a sequenced packet socket object to hold an
   * existing native socket.
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
  basic_seq_packet_socket(const executor_type& ex,
      const protocol_type& protocol, const native_handle_type& native_socket)
    : basic_socket<Protocol, Executor>(ex, protocol, native_socket)
  {
  }

  /// Construct a basic_seq_packet_socket on an existing native socket.
  /**
   * This constructor creates a sequenced packet socket object to hold an
   * existing native socket.
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
  basic_seq_packet_socket(ExecutionContext& context,
      const protocol_type& protocol, const native_handle_type& native_socket,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
    : basic_socket<Protocol, Executor>(context, protocol, native_socket)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct a basic_seq_packet_socket from another.
  /**
   * This constructor moves a sequenced packet socket from one object to
   * another.
   *
   * @param other The other basic_seq_packet_socket object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_seq_packet_socket(const executor_type&)
   * constructor.
   */
  basic_seq_packet_socket(basic_seq_packet_socket&& other) BOOST_ASIO_NOEXCEPT
    : basic_socket<Protocol, Executor>(std::move(other))
  {
  }

  /// Move-assign a basic_seq_packet_socket from another.
  /**
   * This assignment operator moves a sequenced packet socket from one object to
   * another.
   *
   * @param other The other basic_seq_packet_socket object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_seq_packet_socket(const executor_type&)
   * constructor.
   */
  basic_seq_packet_socket& operator=(basic_seq_packet_socket&& other)
  {
    basic_socket<Protocol, Executor>::operator=(std::move(other));
    return *this;
  }

  /// Move-construct a basic_seq_packet_socket from a socket of another protocol
  /// type.
  /**
   * This constructor moves a sequenced packet socket from one object to
   * another.
   *
   * @param other The other basic_seq_packet_socket object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_seq_packet_socket(const executor_type&)
   * constructor.
   */
  template <typename Protocol1, typename Executor1>
  basic_seq_packet_socket(basic_seq_packet_socket<Protocol1, Executor1>&& other,
      typename constraint<
        is_convertible<Protocol1, Protocol>::value
          && is_convertible<Executor1, Executor>::value
      >::type = 0)
    : basic_socket<Protocol, Executor>(std::move(other))
  {
  }

  /// Move-assign a basic_seq_packet_socket from a socket of another protocol
  /// type.
  /**
   * This assignment operator moves a sequenced packet socket from one object to
   * another.
   *
   * @param other The other basic_seq_packet_socket object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_seq_packet_socket(const executor_type&)
   * constructor.
   */
  template <typename Protocol1, typename Executor1>
  typename constraint<
    is_convertible<Protocol1, Protocol>::value
      && is_convertible<Executor1, Executor>::value,
    basic_seq_packet_socket&
  >::type operator=(basic_seq_packet_socket<Protocol1, Executor1>&& other)
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
  ~basic_seq_packet_socket()
  {
  }

  /// Send some data on the socket.
  /**
   * This function is used to send data on the sequenced packet socket. The
   * function call will block until the data has been sent successfully, or an
   * until error occurs.
   *
   * @param buffers One or more data buffers to be sent on the socket.
   *
   * @param flags Flags specifying how the send call is to be made.
   *
   * @returns The number of bytes sent.
   *
   * @throws boost::system::system_error Thrown on failure.
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
   * This function is used to send data on the sequenced packet socket. The
   * function call will block the data has been sent successfully, or an until
   * error occurs.
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
   * This function is used to asynchronously send data on the sequenced packet
   * socket. It is an initiating function for an @ref asynchronous_operation,
   * and always returns immediately.
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
   * This function is used to receive data on the sequenced packet socket. The
   * function call will block until data has been received successfully, or
   * until an error occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @param out_flags After the receive call completes, contains flags
   * associated with the received data. For example, if the
   * socket_base::message_end_of_record bit is set then the received data marks
   * the end of a record.
   *
   * @returns The number of bytes received.
   *
   * @throws boost::system::system_error Thrown on failure. An error code of
   * boost::asio::error::eof indicates that the connection was closed by the
   * peer.
   *
   * @par Example
   * To receive into a single data buffer use the @ref buffer function as
   * follows:
   * @code
   * socket.receive(boost::asio::buffer(data, size), out_flags);
   * @endcode
   * See the @ref buffer documentation for information on receiving into
   * multiple buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename MutableBufferSequence>
  std::size_t receive(const MutableBufferSequence& buffers,
      socket_base::message_flags& out_flags)
  {
    boost::system::error_code ec;
    std::size_t s = this->impl_.get_service().receive_with_flags(
        this->impl_.get_implementation(), buffers, 0, out_flags, ec);
    boost::asio::detail::throw_error(ec, "receive");
    return s;
  }

  /// Receive some data on the socket.
  /**
   * This function is used to receive data on the sequenced packet socket. The
   * function call will block until data has been received successfully, or
   * until an error occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @param in_flags Flags specifying how the receive call is to be made.
   *
   * @param out_flags After the receive call completes, contains flags
   * associated with the received data. For example, if the
   * socket_base::message_end_of_record bit is set then the received data marks
   * the end of a record.
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
   * socket.receive(boost::asio::buffer(data, size), 0, out_flags);
   * @endcode
   * See the @ref buffer documentation for information on receiving into
   * multiple buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename MutableBufferSequence>
  std::size_t receive(const MutableBufferSequence& buffers,
      socket_base::message_flags in_flags,
      socket_base::message_flags& out_flags)
  {
    boost::system::error_code ec;
    std::size_t s = this->impl_.get_service().receive_with_flags(
        this->impl_.get_implementation(), buffers, in_flags, out_flags, ec);
    boost::asio::detail::throw_error(ec, "receive");
    return s;
  }

  /// Receive some data on a connected socket.
  /**
   * This function is used to receive data on the sequenced packet socket. The
   * function call will block until data has been received successfully, or
   * until an error occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @param in_flags Flags specifying how the receive call is to be made.
   *
   * @param out_flags After the receive call completes, contains flags
   * associated with the received data. For example, if the
   * socket_base::message_end_of_record bit is set then the received data marks
   * the end of a record.
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
      socket_base::message_flags in_flags,
      socket_base::message_flags& out_flags, boost::system::error_code& ec)
  {
    return this->impl_.get_service().receive_with_flags(
        this->impl_.get_implementation(), buffers, in_flags, out_flags, ec);
  }

  /// Start an asynchronous receive.
  /**
   * This function is used to asynchronously receive data from the sequenced
   * packet socket. It is an initiating function for an @ref
   * asynchronous_operation, and always returns immediately.
   *
   * @param buffers One or more buffers into which the data will be received.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the completion handler is called.
   *
   * @param out_flags Once the asynchronous operation completes, contains flags
   * associated with the received data. For example, if the
   * socket_base::message_end_of_record bit is set then the received data marks
   * the end of a record. The caller must guarantee that the referenced
   * variable remains valid until the completion handler is called.
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
   * @par Example
   * To receive into a single data buffer use the @ref buffer function as
   * follows:
   * @code
   * socket.async_receive(boost::asio::buffer(data, size), out_flags, handler);
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
      socket_base::message_flags& out_flags,
      BOOST_ASIO_MOVE_ARG(ReadToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<ReadToken,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_receive_with_flags(this), token,
        buffers, socket_base::message_flags(0), &out_flags);
  }

  /// Start an asynchronous receive.
  /**
   * This function is used to asynchronously receive data from the sequenced
   * data socket. It is an initiating function for an @ref
   * asynchronous_operation, and always returns immediately.
   *
   * @param buffers One or more buffers into which the data will be received.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the completion handler is called.
   *
   * @param in_flags Flags specifying how the receive call is to be made.
   *
   * @param out_flags Once the asynchronous operation completes, contains flags
   * associated with the received data. For example, if the
   * socket_base::message_end_of_record bit is set then the received data marks
   * the end of a record. The caller must guarantee that the referenced
   * variable remains valid until the completion handler is called.
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
   * @par Example
   * To receive into a single data buffer use the @ref buffer function as
   * follows:
   * @code
   * socket.async_receive(
   *     boost::asio::buffer(data, size),
   *     0, out_flags, handler);
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
      socket_base::message_flags in_flags,
      socket_base::message_flags& out_flags,
      BOOST_ASIO_MOVE_ARG(ReadToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<ReadToken,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_receive_with_flags(this),
        token, buffers, in_flags, &out_flags);
  }

private:
  // Disallow copying and assignment.
  basic_seq_packet_socket(const basic_seq_packet_socket&) BOOST_ASIO_DELETED;
  basic_seq_packet_socket& operator=(
      const basic_seq_packet_socket&) BOOST_ASIO_DELETED;

  class initiate_async_send
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_send(basic_seq_packet_socket* self)
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
    basic_seq_packet_socket* self_;
  };

  class initiate_async_receive_with_flags
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_receive_with_flags(basic_seq_packet_socket* self)
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
        socket_base::message_flags in_flags,
        socket_base::message_flags* out_flags) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ReadHandler.
      BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

      detail::non_const_lvalue<ReadHandler> handler2(handler);
      self_->impl_.get_service().async_receive_with_flags(
          self_->impl_.get_implementation(), buffers, in_flags,
          *out_flags, handler2.value, self_->impl_.get_executor());
    }

  private:
    basic_seq_packet_socket* self_;
  };
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_BASIC_SEQ_PACKET_SOCKET_HPP

/* basic_seq_packet_socket.hpp
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
*/