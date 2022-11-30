//
// basic_datagram_socket.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
template <typename Protocol, typename Executor = any_io_executor>
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
 *
 * Synchronous @c send, @c send_to, @c receive, @c receive_from, and @c connect
 * operations are thread safe with respect to each other, if the underlying
 * operating system calls are also thread safe. This means that it is permitted
 * to perform concurrent calls to these synchronous operations on a single
 * socket object. Other synchronous operations, such as @c open or @c close, are
 * not thread safe.
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
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
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
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
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
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
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
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
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
      typename constraint<
        is_convertible<Protocol1, Protocol>::value
          && is_convertible<Executor1, Executor>::value
      >::type = 0)
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
  typename constraint<
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
   * It is an initiating function for an @ref asynchronous_operation, and always
   * returns immediately.
   *
   * @param buffers One or more data buffers to be sent on the socket. Although
   * the buffers object may be copied as necessary, ownership of the underlying
   * memory blocks is retained by the caller, which must guarantee that they
   * remain valid until the completion handler is called.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the send completes. Potential
   * completion tokens include @ref use_future, @ref use_awaitable, @ref
   * yield_context, or a function object with the correct completion signature.
   * The function signature of the completion handler must be:
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

  /// Start an asynchronous send on a connected socket.
  /**
   * This function is used to asynchronously send data on the datagram socket.
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
   * completion handler, which will be called when the send completes. Potential
   * completion tokens include @ref use_future, @ref use_awaitable, @ref
   * yield_context, or a function object with the correct completion signature.
   * The function signature of the completion handler must be:
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
   * @note The async_send operation can only be used with a connected socket.
   * Use the async_send_to function to send data on an unconnected datagram
   * socket.
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
   * remote endpoint. It is an initiating function for an @ref
   * asynchronous_operation, and always returns immediately.
   *
   * @param buffers One or more data buffers to be sent to the remote endpoint.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the completion handler is called.
   *
   * @param destination The remote endpoint to which the data will be sent.
   * Copies will be made of the endpoint as required.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the send completes. Potential
   * completion tokens include @ref use_future, @ref use_awaitable, @ref
   * yield_context, or a function object with the correct completion signature.
   * The function signature of the completion handler must be:
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
   * boost::asio::ip::udp::endpoint destination(
   *     boost::asio::ip::address::from_string("1.2.3.4"), 12345);
   * socket.async_send_to(
   *     boost::asio::buffer(data, size), destination, handler);
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
  async_send_to(const ConstBufferSequence& buffers,
      const endpoint_type& destination,
      BOOST_ASIO_MOVE_ARG(WriteToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WriteToken,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_send_to(this), token, buffers,
        destination, socket_base::message_flags(0));
  }

  /// Start an asynchronous send.
  /**
   * This function is used to asynchronously send a datagram to the specified
   * remote endpoint. It is an initiating function for an @ref
   * asynchronous_operation, and always returns immediately.
   *
   * @param buffers One or more data buffers to be sent to the remote endpoint.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the completion handler is called.
   *
   * @param flags Flags specifying how the send call is to be made.
   *
   * @param destination The remote endpoint to which the data will be sent.
   * Copies will be made of the endpoint as required.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the send completes. Potential
   * completion tokens include @ref use_future, @ref use_awaitable, @ref
   * yield_context, or a function object with the correct completion signature.
   * The function signature of the completion handler must be:
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
  async_send_to(const ConstBufferSequence& buffers,
      const endpoint_type& destination, socket_base::message_flags flags,
      BOOST_ASIO_MOVE_ARG(WriteToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WriteToken,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_send_to(this), token, buffers, destination, flags);
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

  /// Start an asynchronous receive on a connected socket.
  /**
   * This function is used to asynchronously receive data from the datagram
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
   * @note The async_receive operation can only be used with a connected socket.
   * Use the async_receive_from function to receive data on an unconnected
   * datagram socket.
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
   * This function is used to asynchronously receive a datagram. It is an
   * initiating function for an @ref asynchronous_operation, and always returns
   * immediately.
   *
   * @param buffers One or more buffers into which the data will be received.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the completion handler is called.
   *
   * @param sender_endpoint An endpoint object that receives the endpoint of
   * the remote sender of the datagram. Ownership of the sender_endpoint object
   * is retained by the caller, which must guarantee that it is valid until the
   * completion handler is called.
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
   * @code socket.async_receive_from(
   *     boost::asio::buffer(data, size), sender_endpoint, handler); @endcode
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
  async_receive_from(const MutableBufferSequence& buffers,
      endpoint_type& sender_endpoint,
      BOOST_ASIO_MOVE_ARG(ReadToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<ReadToken,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_receive_from(this), token, buffers,
        &sender_endpoint, socket_base::message_flags(0));
  }

  /// Start an asynchronous receive.
  /**
   * This function is used to asynchronously receive a datagram. It is an
   * initiating function for an @ref asynchronous_operation, and always returns
   * immediately.
   *
   * @param buffers One or more buffers into which the data will be received.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the completion handler is called.
   *
   * @param sender_endpoint An endpoint object that receives the endpoint of
   * the remote sender of the datagram. Ownership of the sender_endpoint object
   * is retained by the caller, which must guarantee that it is valid until the
   * completion handler is called.
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
  async_receive_from(const MutableBufferSequence& buffers,
      endpoint_type& sender_endpoint, socket_base::message_flags flags,
      BOOST_ASIO_MOVE_ARG(ReadToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<ReadToken,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_receive_from(this), token,
        buffers, &sender_endpoint, flags);
  }

private:
  // Disallow copying and assignment.
  basic_datagram_socket(const basic_datagram_socket&) BOOST_ASIO_DELETED;
  basic_datagram_socket& operator=(
      const basic_datagram_socket&) BOOST_ASIO_DELETED;

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
          handler2.value, self_->impl_.get_executor());
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
          self_->impl_.get_implementation(), buffers, destination,
          flags, handler2.value, self_->impl_.get_executor());
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
          handler2.value, self_->impl_.get_executor());
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
          self_->impl_.get_implementation(), buffers, *sender_endpoint,
          flags, handler2.value, self_->impl_.get_executor());
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