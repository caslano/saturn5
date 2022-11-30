//
// basic_raw_socket.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
template <typename Protocol, typename Executor = any_io_executor>
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
 *
 * Synchronous @c send, @c send_to, @c receive, @c receive_from, and @c connect
 * operations are thread safe with respect to each other, if the underlying
 * operating system calls are also thread safe. This means that it is permitted
 * to perform concurrent calls to these synchronous operations on a single
 * socket object. Other synchronous operations, such as @c open or @c close, are
 * not thread safe.
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
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
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
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
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
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
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
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
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
      typename constraint<
        is_convertible<Protocol1, Protocol>::value
          && is_convertible<Executor1, Executor>::value
      >::type = 0)
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
  typename constraint<
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
   * This function is used to asynchronously send data on the raw socket. It is
   * an initiating function for an @ref asynchronous_operation, and always
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
   * This function is used to asynchronously send data on the raw socket. It is
   * an initiating function for an @ref asynchronous_operation, and always
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
   * @note The async_send operation can only be used with a connected socket.
   * Use the async_send_to function to send data on an unconnected raw
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
   * This function is used to asynchronously send raw data to the specified
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
   * This function is used to asynchronously receive data from the raw
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
   * raw socket.
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
   * This function is used to asynchronously receive raw data. It is an
   * initiating function for an @ref asynchronous_operation, and always returns
   * immediately.
   *
   * @param buffers One or more buffers into which the data will be received.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the completion handler is called.
   *
   * @param sender_endpoint An endpoint object that receives the endpoint of
   * the remote sender of the data. Ownership of the sender_endpoint object
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
   *     boost::asio::buffer(data, size), 0, sender_endpoint, handler); @endcode
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
   * This function is used to asynchronously receive raw data. It is an
   * initiating function for an @ref asynchronous_operation, and always returns
   * immediately.
   *
   * @param buffers One or more buffers into which the data will be received.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the completion handler is called.
   *
   * @param sender_endpoint An endpoint object that receives the endpoint of
   * the remote sender of the data. Ownership of the sender_endpoint object
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
  basic_raw_socket(const basic_raw_socket&) BOOST_ASIO_DELETED;
  basic_raw_socket& operator=(const basic_raw_socket&) BOOST_ASIO_DELETED;

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
          handler2.value, self_->impl_.get_executor());
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
          self_->impl_.get_implementation(), buffers, destination,
          flags, handler2.value, self_->impl_.get_executor());
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
          handler2.value, self_->impl_.get_executor());
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
          self_->impl_.get_implementation(), buffers, *sender_endpoint,
          flags, handler2.value, self_->impl_.get_executor());
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