//
// basic_socket.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_SOCKET_HPP
#define BOOST_ASIO_BASIC_SOCKET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/io_object_impl.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/executor.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/socket_base.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)
# include <boost/asio/detail/null_socket_service.hpp>
#elif defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_socket_service.hpp>
#else
# include <boost/asio/detail/reactive_socket_service.hpp>
#endif

#if defined(BOOST_ASIO_HAS_MOVE)
# include <utility>
#endif // defined(BOOST_ASIO_HAS_MOVE)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if !defined(BOOST_ASIO_BASIC_SOCKET_FWD_DECL)
#define BOOST_ASIO_BASIC_SOCKET_FWD_DECL

// Forward declaration with defaulted arguments.
template <typename Protocol, typename Executor = executor>
class basic_socket;

#endif // !defined(BOOST_ASIO_BASIC_SOCKET_FWD_DECL)

/// Provides socket functionality.
/**
 * The basic_socket class template provides functionality that is common to both
 * stream-oriented and datagram-oriented sockets.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <typename Protocol, typename Executor>
class basic_socket
  : public socket_base
{
public:
  /// The type of the executor associated with the object.
  typedef Executor executor_type;

  /// Rebinds the socket type to another executor.
  template <typename Executor1>
  struct rebind_executor
  {
    /// The socket type when rebound to the specified executor.
    typedef basic_socket<Protocol, Executor1> other;
  };

  /// The native representation of a socket.
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined native_handle_type;
#elif defined(BOOST_ASIO_WINDOWS_RUNTIME)
  typedef typename detail::null_socket_service<
    Protocol>::native_handle_type native_handle_type;
#elif defined(BOOST_ASIO_HAS_IOCP)
  typedef typename detail::win_iocp_socket_service<
    Protocol>::native_handle_type native_handle_type;
#else
  typedef typename detail::reactive_socket_service<
    Protocol>::native_handle_type native_handle_type;
#endif

  /// The protocol type.
  typedef Protocol protocol_type;

  /// The endpoint type.
  typedef typename Protocol::endpoint endpoint_type;

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
  /// A basic_socket is always the lowest layer.
  typedef basic_socket<Protocol, Executor> lowest_layer_type;
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)

  /// Construct a basic_socket without opening it.
  /**
   * This constructor creates a socket without opening it.
   *
   * @param ex The I/O executor that the socket will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the socket.
   */
  explicit basic_socket(const executor_type& ex)
    : impl_(ex)
  {
  }

  /// Construct a basic_socket without opening it.
  /**
   * This constructor creates a socket without opening it.
   *
   * @param context An execution context which provides the I/O executor that
   * the socket will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the socket.
   */
  template <typename ExecutionContext>
  explicit basic_socket(ExecutionContext& context,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : impl_(context)
  {
  }

  /// Construct and open a basic_socket.
  /**
   * This constructor creates and opens a socket.
   *
   * @param ex The I/O executor that the socket will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the socket.
   *
   * @param protocol An object specifying protocol parameters to be used.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_socket(const executor_type& ex, const protocol_type& protocol)
    : impl_(ex)
  {
    boost::system::error_code ec;
    impl_.get_service().open(impl_.get_implementation(), protocol, ec);
    boost::asio::detail::throw_error(ec, "open");
  }

  /// Construct and open a basic_socket.
  /**
   * This constructor creates and opens a socket.
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
  basic_socket(ExecutionContext& context, const protocol_type& protocol,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : impl_(context)
  {
    boost::system::error_code ec;
    impl_.get_service().open(impl_.get_implementation(), protocol, ec);
    boost::asio::detail::throw_error(ec, "open");
  }

  /// Construct a basic_socket, opening it and binding it to the given local
  /// endpoint.
  /**
   * This constructor creates a socket and automatically opens it bound to the
   * specified endpoint on the local machine. The protocol used is the protocol
   * associated with the given endpoint.
   *
   * @param ex The I/O executor that the socket will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the socket.
   *
   * @param endpoint An endpoint on the local machine to which the socket will
   * be bound.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_socket(const executor_type& ex, const endpoint_type& endpoint)
    : impl_(ex)
  {
    boost::system::error_code ec;
    const protocol_type protocol = endpoint.protocol();
    impl_.get_service().open(impl_.get_implementation(), protocol, ec);
    boost::asio::detail::throw_error(ec, "open");
    impl_.get_service().bind(impl_.get_implementation(), endpoint, ec);
    boost::asio::detail::throw_error(ec, "bind");
  }

  /// Construct a basic_socket, opening it and binding it to the given local
  /// endpoint.
  /**
   * This constructor creates a socket and automatically opens it bound to the
   * specified endpoint on the local machine. The protocol used is the protocol
   * associated with the given endpoint.
   *
   * @param context An execution context which provides the I/O executor that
   * the socket will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the socket.
   *
   * @param endpoint An endpoint on the local machine to which the socket will
   * be bound.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_socket(ExecutionContext& context, const endpoint_type& endpoint,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : impl_(context)
  {
    boost::system::error_code ec;
    const protocol_type protocol = endpoint.protocol();
    impl_.get_service().open(impl_.get_implementation(), protocol, ec);
    boost::asio::detail::throw_error(ec, "open");
    impl_.get_service().bind(impl_.get_implementation(), endpoint, ec);
    boost::asio::detail::throw_error(ec, "bind");
  }

  /// Construct a basic_socket on an existing native socket.
  /**
   * This constructor creates a socket object to hold an existing native socket.
   *
   * @param ex The I/O executor that the socket will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the socket.
   *
   * @param protocol An object specifying protocol parameters to be used.
   *
   * @param native_socket A native socket.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_socket(const executor_type& ex, const protocol_type& protocol,
      const native_handle_type& native_socket)
    : impl_(ex)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(impl_.get_implementation(),
        protocol, native_socket, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

  /// Construct a basic_socket on an existing native socket.
  /**
   * This constructor creates a socket object to hold an existing native socket.
   *
   * @param context An execution context which provides the I/O executor that
   * the socket will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the socket.
   *
   * @param protocol An object specifying protocol parameters to be used.
   *
   * @param native_socket A native socket.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_socket(ExecutionContext& context, const protocol_type& protocol,
      const native_handle_type& native_socket,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : impl_(context)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(impl_.get_implementation(),
        protocol, native_socket, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct a basic_socket from another.
  /**
   * This constructor moves a socket from one object to another.
   *
   * @param other The other basic_socket object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_socket(const executor_type&) constructor.
   */
  basic_socket(basic_socket&& other) BOOST_ASIO_NOEXCEPT
    : impl_(std::move(other.impl_))
  {
  }

  /// Move-assign a basic_socket from another.
  /**
   * This assignment operator moves a socket from one object to another.
   *
   * @param other The other basic_socket object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_socket(const executor_type&) constructor.
   */
  basic_socket& operator=(basic_socket&& other)
  {
    impl_ = std::move(other.impl_);
    return *this;
  }

  // All sockets have access to each other's implementations.
  template <typename Protocol1, typename Executor1>
  friend class basic_socket;

  /// Move-construct a basic_socket from a socket of another protocol type.
  /**
   * This constructor moves a socket from one object to another.
   *
   * @param other The other basic_socket object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_socket(const executor_type&) constructor.
   */
  template <typename Protocol1, typename Executor1>
  basic_socket(basic_socket<Protocol1, Executor1>&& other,
      typename enable_if<
        is_convertible<Protocol1, Protocol>::value
          && is_convertible<Executor1, Executor>::value
      >::type* = 0)
    : impl_(std::move(other.impl_))
  {
  }

  /// Move-assign a basic_socket from a socket of another protocol type.
  /**
   * This assignment operator moves a socket from one object to another.
   *
   * @param other The other basic_socket object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_socket(const executor_type&) constructor.
   */
  template <typename Protocol1, typename Executor1>
  typename enable_if<
    is_convertible<Protocol1, Protocol>::value
      && is_convertible<Executor1, Executor>::value,
    basic_socket&
  >::type operator=(basic_socket<Protocol1, Executor1> && other)
  {
    basic_socket tmp(std::move(other));
    impl_ = std::move(tmp.impl_);
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Get the executor associated with the object.
  executor_type get_executor() BOOST_ASIO_NOEXCEPT
  {
    return impl_.get_executor();
  }

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
  /// Get a reference to the lowest layer.
  /**
   * This function returns a reference to the lowest layer in a stack of
   * layers. Since a basic_socket cannot contain any further layers, it simply
   * returns a reference to itself.
   *
   * @return A reference to the lowest layer in the stack of layers. Ownership
   * is not transferred to the caller.
   */
  lowest_layer_type& lowest_layer()
  {
    return *this;
  }

  /// Get a const reference to the lowest layer.
  /**
   * This function returns a const reference to the lowest layer in a stack of
   * layers. Since a basic_socket cannot contain any further layers, it simply
   * returns a reference to itself.
   *
   * @return A const reference to the lowest layer in the stack of layers.
   * Ownership is not transferred to the caller.
   */
  const lowest_layer_type& lowest_layer() const
  {
    return *this;
  }
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)

  /// Open the socket using the specified protocol.
  /**
   * This function opens the socket so that it will use the specified protocol.
   *
   * @param protocol An object specifying protocol parameters to be used.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * socket.open(boost::asio::ip::tcp::v4());
   * @endcode
   */
  void open(const protocol_type& protocol = protocol_type())
  {
    boost::system::error_code ec;
    impl_.get_service().open(impl_.get_implementation(), protocol, ec);
    boost::asio::detail::throw_error(ec, "open");
  }

  /// Open the socket using the specified protocol.
  /**
   * This function opens the socket so that it will use the specified protocol.
   *
   * @param protocol An object specifying which protocol is to be used.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * boost::system::error_code ec;
   * socket.open(boost::asio::ip::tcp::v4(), ec);
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * @endcode
   */
  BOOST_ASIO_SYNC_OP_VOID open(const protocol_type& protocol,
      boost::system::error_code& ec)
  {
    impl_.get_service().open(impl_.get_implementation(), protocol, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Assign an existing native socket to the socket.
  /*
   * This function opens the socket to hold an existing native socket.
   *
   * @param protocol An object specifying which protocol is to be used.
   *
   * @param native_socket A native socket.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void assign(const protocol_type& protocol,
      const native_handle_type& native_socket)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(impl_.get_implementation(),
        protocol, native_socket, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

  /// Assign an existing native socket to the socket.
  /*
   * This function opens the socket to hold an existing native socket.
   *
   * @param protocol An object specifying which protocol is to be used.
   *
   * @param native_socket A native socket.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID assign(const protocol_type& protocol,
      const native_handle_type& native_socket, boost::system::error_code& ec)
  {
    impl_.get_service().assign(impl_.get_implementation(),
        protocol, native_socket, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Determine whether the socket is open.
  bool is_open() const
  {
    return impl_.get_service().is_open(impl_.get_implementation());
  }

  /// Close the socket.
  /**
   * This function is used to close the socket. Any asynchronous send, receive
   * or connect operations will be cancelled immediately, and will complete
   * with the boost::asio::error::operation_aborted error.
   *
   * @throws boost::system::system_error Thrown on failure. Note that, even if
   * the function indicates an error, the underlying descriptor is closed.
   *
   * @note For portable behaviour with respect to graceful closure of a
   * connected socket, call shutdown() before closing the socket.
   */
  void close()
  {
    boost::system::error_code ec;
    impl_.get_service().close(impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "close");
  }

  /// Close the socket.
  /**
   * This function is used to close the socket. Any asynchronous send, receive
   * or connect operations will be cancelled immediately, and will complete
   * with the boost::asio::error::operation_aborted error.
   *
   * @param ec Set to indicate what error occurred, if any. Note that, even if
   * the function indicates an error, the underlying descriptor is closed.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::system::error_code ec;
   * socket.close(ec);
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * @endcode
   *
   * @note For portable behaviour with respect to graceful closure of a
   * connected socket, call shutdown() before closing the socket.
   */
  BOOST_ASIO_SYNC_OP_VOID close(boost::system::error_code& ec)
  {
    impl_.get_service().close(impl_.get_implementation(), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Release ownership of the underlying native socket.
  /**
   * This function causes all outstanding asynchronous connect, send and receive
   * operations to finish immediately, and the handlers for cancelled operations
   * will be passed the boost::asio::error::operation_aborted error. Ownership
   * of the native socket is then transferred to the caller.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note This function is unsupported on Windows versions prior to Windows
   * 8.1, and will fail with boost::asio::error::operation_not_supported on
   * these platforms.
   */
#if defined(BOOST_ASIO_MSVC) && (BOOST_ASIO_MSVC >= 1400) \
  && (!defined(_WIN32_WINNT) || _WIN32_WINNT < 0x0603)
  __declspec(deprecated("This function always fails with "
        "operation_not_supported when used on Windows versions "
        "prior to Windows 8.1."))
#endif
  native_handle_type release()
  {
    boost::system::error_code ec;
    native_handle_type s = impl_.get_service().release(
        impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "release");
    return s;
  }

  /// Release ownership of the underlying native socket.
  /**
   * This function causes all outstanding asynchronous connect, send and receive
   * operations to finish immediately, and the handlers for cancelled operations
   * will be passed the boost::asio::error::operation_aborted error. Ownership
   * of the native socket is then transferred to the caller.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note This function is unsupported on Windows versions prior to Windows
   * 8.1, and will fail with boost::asio::error::operation_not_supported on
   * these platforms.
   */
#if defined(BOOST_ASIO_MSVC) && (BOOST_ASIO_MSVC >= 1400) \
  && (!defined(_WIN32_WINNT) || _WIN32_WINNT < 0x0603)
  __declspec(deprecated("This function always fails with "
        "operation_not_supported when used on Windows versions "
        "prior to Windows 8.1."))
#endif
  native_handle_type release(boost::system::error_code& ec)
  {
    return impl_.get_service().release(impl_.get_implementation(), ec);
  }

  /// Get the native socket representation.
  /**
   * This function may be used to obtain the underlying representation of the
   * socket. This is intended to allow access to native socket functionality
   * that is not otherwise provided.
   */
  native_handle_type native_handle()
  {
    return impl_.get_service().native_handle(impl_.get_implementation());
  }

  /// Cancel all asynchronous operations associated with the socket.
  /**
   * This function causes all outstanding asynchronous connect, send and receive
   * operations to finish immediately, and the handlers for cancelled operations
   * will be passed the boost::asio::error::operation_aborted error.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls to cancel() will always fail with
   * boost::asio::error::operation_not_supported when run on Windows XP, Windows
   * Server 2003, and earlier versions of Windows, unless
   * BOOST_ASIO_ENABLE_CANCELIO is defined. However, the CancelIo function has
   * two issues that should be considered before enabling its use:
   *
   * @li It will only cancel asynchronous operations that were initiated in the
   * current thread.
   *
   * @li It can appear to complete without error, but the request to cancel the
   * unfinished operations may be silently ignored by the operating system.
   * Whether it works or not seems to depend on the drivers that are installed.
   *
   * For portable cancellation, consider using one of the following
   * alternatives:
   *
   * @li Disable asio's I/O completion port backend by defining
   * BOOST_ASIO_DISABLE_IOCP.
   *
   * @li Use the close() function to simultaneously cancel the outstanding
   * operations and close the socket.
   *
   * When running on Windows Vista, Windows Server 2008, and later, the
   * CancelIoEx function is always used. This function does not have the
   * problems described above.
   */
#if defined(BOOST_ASIO_MSVC) && (BOOST_ASIO_MSVC >= 1400) \
  && (!defined(_WIN32_WINNT) || _WIN32_WINNT < 0x0600) \
  && !defined(BOOST_ASIO_ENABLE_CANCELIO)
  __declspec(deprecated("By default, this function always fails with "
        "operation_not_supported when used on Windows XP, Windows Server 2003, "
        "or earlier. Consult documentation for details."))
#endif
  void cancel()
  {
    boost::system::error_code ec;
    impl_.get_service().cancel(impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "cancel");
  }

  /// Cancel all asynchronous operations associated with the socket.
  /**
   * This function causes all outstanding asynchronous connect, send and receive
   * operations to finish immediately, and the handlers for cancelled operations
   * will be passed the boost::asio::error::operation_aborted error.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls to cancel() will always fail with
   * boost::asio::error::operation_not_supported when run on Windows XP, Windows
   * Server 2003, and earlier versions of Windows, unless
   * BOOST_ASIO_ENABLE_CANCELIO is defined. However, the CancelIo function has
   * two issues that should be considered before enabling its use:
   *
   * @li It will only cancel asynchronous operations that were initiated in the
   * current thread.
   *
   * @li It can appear to complete without error, but the request to cancel the
   * unfinished operations may be silently ignored by the operating system.
   * Whether it works or not seems to depend on the drivers that are installed.
   *
   * For portable cancellation, consider using one of the following
   * alternatives:
   *
   * @li Disable asio's I/O completion port backend by defining
   * BOOST_ASIO_DISABLE_IOCP.
   *
   * @li Use the close() function to simultaneously cancel the outstanding
   * operations and close the socket.
   *
   * When running on Windows Vista, Windows Server 2008, and later, the
   * CancelIoEx function is always used. This function does not have the
   * problems described above.
   */
#if defined(BOOST_ASIO_MSVC) && (BOOST_ASIO_MSVC >= 1400) \
  && (!defined(_WIN32_WINNT) || _WIN32_WINNT < 0x0600) \
  && !defined(BOOST_ASIO_ENABLE_CANCELIO)
  __declspec(deprecated("By default, this function always fails with "
        "operation_not_supported when used on Windows XP, Windows Server 2003, "
        "or earlier. Consult documentation for details."))
#endif
  BOOST_ASIO_SYNC_OP_VOID cancel(boost::system::error_code& ec)
  {
    impl_.get_service().cancel(impl_.get_implementation(), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Determine whether the socket is at the out-of-band data mark.
  /**
   * This function is used to check whether the socket input is currently
   * positioned at the out-of-band data mark.
   *
   * @return A bool indicating whether the socket is at the out-of-band data
   * mark.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  bool at_mark() const
  {
    boost::system::error_code ec;
    bool b = impl_.get_service().at_mark(impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "at_mark");
    return b;
  }

  /// Determine whether the socket is at the out-of-band data mark.
  /**
   * This function is used to check whether the socket input is currently
   * positioned at the out-of-band data mark.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @return A bool indicating whether the socket is at the out-of-band data
   * mark.
   */
  bool at_mark(boost::system::error_code& ec) const
  {
    return impl_.get_service().at_mark(impl_.get_implementation(), ec);
  }

  /// Determine the number of bytes available for reading.
  /**
   * This function is used to determine the number of bytes that may be read
   * without blocking.
   *
   * @return The number of bytes that may be read without blocking, or 0 if an
   * error occurs.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  std::size_t available() const
  {
    boost::system::error_code ec;
    std::size_t s = impl_.get_service().available(
        impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "available");
    return s;
  }

  /// Determine the number of bytes available for reading.
  /**
   * This function is used to determine the number of bytes that may be read
   * without blocking.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @return The number of bytes that may be read without blocking, or 0 if an
   * error occurs.
   */
  std::size_t available(boost::system::error_code& ec) const
  {
    return impl_.get_service().available(impl_.get_implementation(), ec);
  }

  /// Bind the socket to the given local endpoint.
  /**
   * This function binds the socket to the specified endpoint on the local
   * machine.
   *
   * @param endpoint An endpoint on the local machine to which the socket will
   * be bound.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * socket.open(boost::asio::ip::tcp::v4());
   * socket.bind(boost::asio::ip::tcp::endpoint(
   *       boost::asio::ip::tcp::v4(), 12345));
   * @endcode
   */
  void bind(const endpoint_type& endpoint)
  {
    boost::system::error_code ec;
    impl_.get_service().bind(impl_.get_implementation(), endpoint, ec);
    boost::asio::detail::throw_error(ec, "bind");
  }

  /// Bind the socket to the given local endpoint.
  /**
   * This function binds the socket to the specified endpoint on the local
   * machine.
   *
   * @param endpoint An endpoint on the local machine to which the socket will
   * be bound.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * socket.open(boost::asio::ip::tcp::v4());
   * boost::system::error_code ec;
   * socket.bind(boost::asio::ip::tcp::endpoint(
   *       boost::asio::ip::tcp::v4(), 12345), ec);
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * @endcode
   */
  BOOST_ASIO_SYNC_OP_VOID bind(const endpoint_type& endpoint,
      boost::system::error_code& ec)
  {
    impl_.get_service().bind(impl_.get_implementation(), endpoint, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Connect the socket to the specified endpoint.
  /**
   * This function is used to connect a socket to the specified remote endpoint.
   * The function call will block until the connection is successfully made or
   * an error occurs.
   *
   * The socket is automatically opened if it is not already open. If the
   * connect fails, and the socket was automatically opened, the socket is
   * not returned to the closed state.
   *
   * @param peer_endpoint The remote endpoint to which the socket will be
   * connected.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * boost::asio::ip::tcp::endpoint endpoint(
   *     boost::asio::ip::address::from_string("1.2.3.4"), 12345);
   * socket.connect(endpoint);
   * @endcode
   */
  void connect(const endpoint_type& peer_endpoint)
  {
    boost::system::error_code ec;
    if (!is_open())
    {
      impl_.get_service().open(impl_.get_implementation(),
          peer_endpoint.protocol(), ec);
      boost::asio::detail::throw_error(ec, "connect");
    }
    impl_.get_service().connect(impl_.get_implementation(), peer_endpoint, ec);
    boost::asio::detail::throw_error(ec, "connect");
  }

  /// Connect the socket to the specified endpoint.
  /**
   * This function is used to connect a socket to the specified remote endpoint.
   * The function call will block until the connection is successfully made or
   * an error occurs.
   *
   * The socket is automatically opened if it is not already open. If the
   * connect fails, and the socket was automatically opened, the socket is
   * not returned to the closed state.
   *
   * @param peer_endpoint The remote endpoint to which the socket will be
   * connected.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * boost::asio::ip::tcp::endpoint endpoint(
   *     boost::asio::ip::address::from_string("1.2.3.4"), 12345);
   * boost::system::error_code ec;
   * socket.connect(endpoint, ec);
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * @endcode
   */
  BOOST_ASIO_SYNC_OP_VOID connect(const endpoint_type& peer_endpoint,
      boost::system::error_code& ec)
  {
    if (!is_open())
    {
      impl_.get_service().open(impl_.get_implementation(),
            peer_endpoint.protocol(), ec);
      if (ec)
      {
        BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
      }
    }

    impl_.get_service().connect(impl_.get_implementation(), peer_endpoint, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Start an asynchronous connect.
  /**
   * This function is used to asynchronously connect a socket to the specified
   * remote endpoint. The function call always returns immediately.
   *
   * The socket is automatically opened if it is not already open. If the
   * connect fails, and the socket was automatically opened, the socket is
   * not returned to the closed state.
   *
   * @param peer_endpoint The remote endpoint to which the socket will be
   * connected. Copies will be made of the endpoint object as required.
   *
   * @param handler The handler to be called when the connection operation
   * completes. Copies will be made of the handler as required. The function
   * signature of the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error // Result of operation
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Example
   * @code
   * void connect_handler(const boost::system::error_code& error)
   * {
   *   if (!error)
   *   {
   *     // Connect succeeded.
   *   }
   * }
   *
   * ...
   *
   * boost::asio::ip::tcp::socket socket(my_context);
   * boost::asio::ip::tcp::endpoint endpoint(
   *     boost::asio::ip::address::from_string("1.2.3.4"), 12345);
   * socket.async_connect(endpoint, connect_handler);
   * @endcode
   */
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code))
        ConnectHandler BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ConnectHandler,
      void (boost::system::error_code))
  async_connect(const endpoint_type& peer_endpoint,
      BOOST_ASIO_MOVE_ARG(ConnectHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    boost::system::error_code open_ec;
    if (!is_open())
    {
      const protocol_type protocol = peer_endpoint.protocol();
      impl_.get_service().open(impl_.get_implementation(), protocol, open_ec);
    }

    return async_initiate<ConnectHandler, void (boost::system::error_code)>(
        initiate_async_connect(this), handler, peer_endpoint, open_ec);
  }

  /// Set an option on the socket.
  /**
   * This function is used to set an option on the socket.
   *
   * @param option The new option value to be set on the socket.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @sa SettableSocketOption @n
   * boost::asio::socket_base::broadcast @n
   * boost::asio::socket_base::do_not_route @n
   * boost::asio::socket_base::keep_alive @n
   * boost::asio::socket_base::linger @n
   * boost::asio::socket_base::receive_buffer_size @n
   * boost::asio::socket_base::receive_low_watermark @n
   * boost::asio::socket_base::reuse_address @n
   * boost::asio::socket_base::send_buffer_size @n
   * boost::asio::socket_base::send_low_watermark @n
   * boost::asio::ip::multicast::join_group @n
   * boost::asio::ip::multicast::leave_group @n
   * boost::asio::ip::multicast::enable_loopback @n
   * boost::asio::ip::multicast::outbound_interface @n
   * boost::asio::ip::multicast::hops @n
   * boost::asio::ip::tcp::no_delay
   *
   * @par Example
   * Setting the IPPROTO_TCP/TCP_NODELAY option:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::ip::tcp::no_delay option(true);
   * socket.set_option(option);
   * @endcode
   */
  template <typename SettableSocketOption>
  void set_option(const SettableSocketOption& option)
  {
    boost::system::error_code ec;
    impl_.get_service().set_option(impl_.get_implementation(), option, ec);
    boost::asio::detail::throw_error(ec, "set_option");
  }

  /// Set an option on the socket.
  /**
   * This function is used to set an option on the socket.
   *
   * @param option The new option value to be set on the socket.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @sa SettableSocketOption @n
   * boost::asio::socket_base::broadcast @n
   * boost::asio::socket_base::do_not_route @n
   * boost::asio::socket_base::keep_alive @n
   * boost::asio::socket_base::linger @n
   * boost::asio::socket_base::receive_buffer_size @n
   * boost::asio::socket_base::receive_low_watermark @n
   * boost::asio::socket_base::reuse_address @n
   * boost::asio::socket_base::send_buffer_size @n
   * boost::asio::socket_base::send_low_watermark @n
   * boost::asio::ip::multicast::join_group @n
   * boost::asio::ip::multicast::leave_group @n
   * boost::asio::ip::multicast::enable_loopback @n
   * boost::asio::ip::multicast::outbound_interface @n
   * boost::asio::ip::multicast::hops @n
   * boost::asio::ip::tcp::no_delay
   *
   * @par Example
   * Setting the IPPROTO_TCP/TCP_NODELAY option:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::ip::tcp::no_delay option(true);
   * boost::system::error_code ec;
   * socket.set_option(option, ec);
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * @endcode
   */
  template <typename SettableSocketOption>
  BOOST_ASIO_SYNC_OP_VOID set_option(const SettableSocketOption& option,
      boost::system::error_code& ec)
  {
    impl_.get_service().set_option(impl_.get_implementation(), option, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Get an option from the socket.
  /**
   * This function is used to get the current value of an option on the socket.
   *
   * @param option The option value to be obtained from the socket.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @sa GettableSocketOption @n
   * boost::asio::socket_base::broadcast @n
   * boost::asio::socket_base::do_not_route @n
   * boost::asio::socket_base::keep_alive @n
   * boost::asio::socket_base::linger @n
   * boost::asio::socket_base::receive_buffer_size @n
   * boost::asio::socket_base::receive_low_watermark @n
   * boost::asio::socket_base::reuse_address @n
   * boost::asio::socket_base::send_buffer_size @n
   * boost::asio::socket_base::send_low_watermark @n
   * boost::asio::ip::multicast::join_group @n
   * boost::asio::ip::multicast::leave_group @n
   * boost::asio::ip::multicast::enable_loopback @n
   * boost::asio::ip::multicast::outbound_interface @n
   * boost::asio::ip::multicast::hops @n
   * boost::asio::ip::tcp::no_delay
   *
   * @par Example
   * Getting the value of the SOL_SOCKET/SO_KEEPALIVE option:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::ip::tcp::socket::keep_alive option;
   * socket.get_option(option);
   * bool is_set = option.value();
   * @endcode
   */
  template <typename GettableSocketOption>
  void get_option(GettableSocketOption& option) const
  {
    boost::system::error_code ec;
    impl_.get_service().get_option(impl_.get_implementation(), option, ec);
    boost::asio::detail::throw_error(ec, "get_option");
  }

  /// Get an option from the socket.
  /**
   * This function is used to get the current value of an option on the socket.
   *
   * @param option The option value to be obtained from the socket.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @sa GettableSocketOption @n
   * boost::asio::socket_base::broadcast @n
   * boost::asio::socket_base::do_not_route @n
   * boost::asio::socket_base::keep_alive @n
   * boost::asio::socket_base::linger @n
   * boost::asio::socket_base::receive_buffer_size @n
   * boost::asio::socket_base::receive_low_watermark @n
   * boost::asio::socket_base::reuse_address @n
   * boost::asio::socket_base::send_buffer_size @n
   * boost::asio::socket_base::send_low_watermark @n
   * boost::asio::ip::multicast::join_group @n
   * boost::asio::ip::multicast::leave_group @n
   * boost::asio::ip::multicast::enable_loopback @n
   * boost::asio::ip::multicast::outbound_interface @n
   * boost::asio::ip::multicast::hops @n
   * boost::asio::ip::tcp::no_delay
   *
   * @par Example
   * Getting the value of the SOL_SOCKET/SO_KEEPALIVE option:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::ip::tcp::socket::keep_alive option;
   * boost::system::error_code ec;
   * socket.get_option(option, ec);
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * bool is_set = option.value();
   * @endcode
   */
  template <typename GettableSocketOption>
  BOOST_ASIO_SYNC_OP_VOID get_option(GettableSocketOption& option,
      boost::system::error_code& ec) const
  {
    impl_.get_service().get_option(impl_.get_implementation(), option, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Perform an IO control command on the socket.
  /**
   * This function is used to execute an IO control command on the socket.
   *
   * @param command The IO control command to be performed on the socket.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @sa IoControlCommand @n
   * boost::asio::socket_base::bytes_readable @n
   * boost::asio::socket_base::non_blocking_io
   *
   * @par Example
   * Getting the number of bytes ready to read:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::ip::tcp::socket::bytes_readable command;
   * socket.io_control(command);
   * std::size_t bytes_readable = command.get();
   * @endcode
   */
  template <typename IoControlCommand>
  void io_control(IoControlCommand& command)
  {
    boost::system::error_code ec;
    impl_.get_service().io_control(impl_.get_implementation(), command, ec);
    boost::asio::detail::throw_error(ec, "io_control");
  }

  /// Perform an IO control command on the socket.
  /**
   * This function is used to execute an IO control command on the socket.
   *
   * @param command The IO control command to be performed on the socket.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @sa IoControlCommand @n
   * boost::asio::socket_base::bytes_readable @n
   * boost::asio::socket_base::non_blocking_io
   *
   * @par Example
   * Getting the number of bytes ready to read:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::ip::tcp::socket::bytes_readable command;
   * boost::system::error_code ec;
   * socket.io_control(command, ec);
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * std::size_t bytes_readable = command.get();
   * @endcode
   */
  template <typename IoControlCommand>
  BOOST_ASIO_SYNC_OP_VOID io_control(IoControlCommand& command,
      boost::system::error_code& ec)
  {
    impl_.get_service().io_control(impl_.get_implementation(), command, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Gets the non-blocking mode of the socket.
  /**
   * @returns @c true if the socket's synchronous operations will fail with
   * boost::asio::error::would_block if they are unable to perform the requested
   * operation immediately. If @c false, synchronous operations will block
   * until complete.
   *
   * @note The non-blocking mode has no effect on the behaviour of asynchronous
   * operations. Asynchronous operations will never fail with the error
   * boost::asio::error::would_block.
   */
  bool non_blocking() const
  {
    return impl_.get_service().non_blocking(impl_.get_implementation());
  }

  /// Sets the non-blocking mode of the socket.
  /**
   * @param mode If @c true, the socket's synchronous operations will fail with
   * boost::asio::error::would_block if they are unable to perform the requested
   * operation immediately. If @c false, synchronous operations will block
   * until complete.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note The non-blocking mode has no effect on the behaviour of asynchronous
   * operations. Asynchronous operations will never fail with the error
   * boost::asio::error::would_block.
   */
  void non_blocking(bool mode)
  {
    boost::system::error_code ec;
    impl_.get_service().non_blocking(impl_.get_implementation(), mode, ec);
    boost::asio::detail::throw_error(ec, "non_blocking");
  }

  /// Sets the non-blocking mode of the socket.
  /**
   * @param mode If @c true, the socket's synchronous operations will fail with
   * boost::asio::error::would_block if they are unable to perform the requested
   * operation immediately. If @c false, synchronous operations will block
   * until complete.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note The non-blocking mode has no effect on the behaviour of asynchronous
   * operations. Asynchronous operations will never fail with the error
   * boost::asio::error::would_block.
   */
  BOOST_ASIO_SYNC_OP_VOID non_blocking(
      bool mode, boost::system::error_code& ec)
  {
    impl_.get_service().non_blocking(impl_.get_implementation(), mode, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Gets the non-blocking mode of the native socket implementation.
  /**
   * This function is used to retrieve the non-blocking mode of the underlying
   * native socket. This mode has no effect on the behaviour of the socket
   * object's synchronous operations.
   *
   * @returns @c true if the underlying socket is in non-blocking mode and
   * direct system calls may fail with boost::asio::error::would_block (or the
   * equivalent system error).
   *
   * @note The current non-blocking mode is cached by the socket object.
   * Consequently, the return value may be incorrect if the non-blocking mode
   * was set directly on the native socket.
   *
   * @par Example
   * This function is intended to allow the encapsulation of arbitrary
   * non-blocking system calls as asynchronous operations, in a way that is
   * transparent to the user of the socket object. The following example
   * illustrates how Linux's @c sendfile system call might be encapsulated:
   * @code template <typename Handler>
   * struct sendfile_op
   * {
   *   tcp::socket& sock_;
   *   int fd_;
   *   Handler handler_;
   *   off_t offset_;
   *   std::size_t total_bytes_transferred_;
   *
   *   // Function call operator meeting WriteHandler requirements.
   *   // Used as the handler for the async_write_some operation.
   *   void operator()(boost::system::error_code ec, std::size_t)
   *   {
   *     // Put the underlying socket into non-blocking mode.
   *     if (!ec)
   *       if (!sock_.native_non_blocking())
   *         sock_.native_non_blocking(true, ec);
   *
   *     if (!ec)
   *     {
   *       for (;;)
   *       {
   *         // Try the system call.
   *         errno = 0;
   *         int n = ::sendfile(sock_.native_handle(), fd_, &offset_, 65536);
   *         ec = boost::system::error_code(n < 0 ? errno : 0,
   *             boost::asio::error::get_system_category());
   *         total_bytes_transferred_ += ec ? 0 : n;
   *
   *         // Retry operation immediately if interrupted by signal.
   *         if (ec == boost::asio::error::interrupted)
   *           continue;
   *
   *         // Check if we need to run the operation again.
   *         if (ec == boost::asio::error::would_block
   *             || ec == boost::asio::error::try_again)
   *         {
   *           // We have to wait for the socket to become ready again.
   *           sock_.async_wait(tcp::socket::wait_write, *this);
   *           return;
   *         }
   *
   *         if (ec || n == 0)
   *         {
   *           // An error occurred, or we have reached the end of the file.
   *           // Either way we must exit the loop so we can call the handler.
   *           break;
   *         }
   *
   *         // Loop around to try calling sendfile again.
   *       }
   *     }
   *
   *     // Pass result back to user's handler.
   *     handler_(ec, total_bytes_transferred_);
   *   }
   * };
   *
   * template <typename Handler>
   * void async_sendfile(tcp::socket& sock, int fd, Handler h)
   * {
   *   sendfile_op<Handler> op = { sock, fd, h, 0, 0 };
   *   sock.async_wait(tcp::socket::wait_write, op);
   * } @endcode
   */
  bool native_non_blocking() const
  {
    return impl_.get_service().native_non_blocking(impl_.get_implementation());
  }

  /// Sets the non-blocking mode of the native socket implementation.
  /**
   * This function is used to modify the non-blocking mode of the underlying
   * native socket. It has no effect on the behaviour of the socket object's
   * synchronous operations.
   *
   * @param mode If @c true, the underlying socket is put into non-blocking
   * mode and direct system calls may fail with boost::asio::error::would_block
   * (or the equivalent system error).
   *
   * @throws boost::system::system_error Thrown on failure. If the @c mode is
   * @c false, but the current value of @c non_blocking() is @c true, this
   * function fails with boost::asio::error::invalid_argument, as the
   * combination does not make sense.
   *
   * @par Example
   * This function is intended to allow the encapsulation of arbitrary
   * non-blocking system calls as asynchronous operations, in a way that is
   * transparent to the user of the socket object. The following example
   * illustrates how Linux's @c sendfile system call might be encapsulated:
   * @code template <typename Handler>
   * struct sendfile_op
   * {
   *   tcp::socket& sock_;
   *   int fd_;
   *   Handler handler_;
   *   off_t offset_;
   *   std::size_t total_bytes_transferred_;
   *
   *   // Function call operator meeting WriteHandler requirements.
   *   // Used as the handler for the async_write_some operation.
   *   void operator()(boost::system::error_code ec, std::size_t)
   *   {
   *     // Put the underlying socket into non-blocking mode.
   *     if (!ec)
   *       if (!sock_.native_non_blocking())
   *         sock_.native_non_blocking(true, ec);
   *
   *     if (!ec)
   *     {
   *       for (;;)
   *       {
   *         // Try the system call.
   *         errno = 0;
   *         int n = ::sendfile(sock_.native_handle(), fd_, &offset_, 65536);
   *         ec = boost::system::error_code(n < 0 ? errno : 0,
   *             boost::asio::error::get_system_category());
   *         total_bytes_transferred_ += ec ? 0 : n;
   *
   *         // Retry operation immediately if interrupted by signal.
   *         if (ec == boost::asio::error::interrupted)
   *           continue;
   *
   *         // Check if we need to run the operation again.
   *         if (ec == boost::asio::error::would_block
   *             || ec == boost::asio::error::try_again)
   *         {
   *           // We have to wait for the socket to become ready again.
   *           sock_.async_wait(tcp::socket::wait_write, *this);
   *           return;
   *         }
   *
   *         if (ec || n == 0)
   *         {
   *           // An error occurred, or we have reached the end of the file.
   *           // Either way we must exit the loop so we can call the handler.
   *           break;
   *         }
   *
   *         // Loop around to try calling sendfile again.
   *       }
   *     }
   *
   *     // Pass result back to user's handler.
   *     handler_(ec, total_bytes_transferred_);
   *   }
   * };
   *
   * template <typename Handler>
   * void async_sendfile(tcp::socket& sock, int fd, Handler h)
   * {
   *   sendfile_op<Handler> op = { sock, fd, h, 0, 0 };
   *   sock.async_wait(tcp::socket::wait_write, op);
   * } @endcode
   */
  void native_non_blocking(bool mode)
  {
    boost::system::error_code ec;
    impl_.get_service().native_non_blocking(
        impl_.get_implementation(), mode, ec);
    boost::asio::detail::throw_error(ec, "native_non_blocking");
  }

  /// Sets the non-blocking mode of the native socket implementation.
  /**
   * This function is used to modify the non-blocking mode of the underlying
   * native socket. It has no effect on the behaviour of the socket object's
   * synchronous operations.
   *
   * @param mode If @c true, the underlying socket is put into non-blocking
   * mode and direct system calls may fail with boost::asio::error::would_block
   * (or the equivalent system error).
   *
   * @param ec Set to indicate what error occurred, if any. If the @c mode is
   * @c false, but the current value of @c non_blocking() is @c true, this
   * function fails with boost::asio::error::invalid_argument, as the
   * combination does not make sense.
   *
   * @par Example
   * This function is intended to allow the encapsulation of arbitrary
   * non-blocking system calls as asynchronous operations, in a way that is
   * transparent to the user of the socket object. The following example
   * illustrates how Linux's @c sendfile system call might be encapsulated:
   * @code template <typename Handler>
   * struct sendfile_op
   * {
   *   tcp::socket& sock_;
   *   int fd_;
   *   Handler handler_;
   *   off_t offset_;
   *   std::size_t total_bytes_transferred_;
   *
   *   // Function call operator meeting WriteHandler requirements.
   *   // Used as the handler for the async_write_some operation.
   *   void operator()(boost::system::error_code ec, std::size_t)
   *   {
   *     // Put the underlying socket into non-blocking mode.
   *     if (!ec)
   *       if (!sock_.native_non_blocking())
   *         sock_.native_non_blocking(true, ec);
   *
   *     if (!ec)
   *     {
   *       for (;;)
   *       {
   *         // Try the system call.
   *         errno = 0;
   *         int n = ::sendfile(sock_.native_handle(), fd_, &offset_, 65536);
   *         ec = boost::system::error_code(n < 0 ? errno : 0,
   *             boost::asio::error::get_system_category());
   *         total_bytes_transferred_ += ec ? 0 : n;
   *
   *         // Retry operation immediately if interrupted by signal.
   *         if (ec == boost::asio::error::interrupted)
   *           continue;
   *
   *         // Check if we need to run the operation again.
   *         if (ec == boost::asio::error::would_block
   *             || ec == boost::asio::error::try_again)
   *         {
   *           // We have to wait for the socket to become ready again.
   *           sock_.async_wait(tcp::socket::wait_write, *this);
   *           return;
   *         }
   *
   *         if (ec || n == 0)
   *         {
   *           // An error occurred, or we have reached the end of the file.
   *           // Either way we must exit the loop so we can call the handler.
   *           break;
   *         }
   *
   *         // Loop around to try calling sendfile again.
   *       }
   *     }
   *
   *     // Pass result back to user's handler.
   *     handler_(ec, total_bytes_transferred_);
   *   }
   * };
   *
   * template <typename Handler>
   * void async_sendfile(tcp::socket& sock, int fd, Handler h)
   * {
   *   sendfile_op<Handler> op = { sock, fd, h, 0, 0 };
   *   sock.async_wait(tcp::socket::wait_write, op);
   * } @endcode
   */
  BOOST_ASIO_SYNC_OP_VOID native_non_blocking(
      bool mode, boost::system::error_code& ec)
  {
    impl_.get_service().native_non_blocking(
        impl_.get_implementation(), mode, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Get the local endpoint of the socket.
  /**
   * This function is used to obtain the locally bound endpoint of the socket.
   *
   * @returns An object that represents the local endpoint of the socket.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::ip::tcp::endpoint endpoint = socket.local_endpoint();
   * @endcode
   */
  endpoint_type local_endpoint() const
  {
    boost::system::error_code ec;
    endpoint_type ep = impl_.get_service().local_endpoint(
        impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "local_endpoint");
    return ep;
  }

  /// Get the local endpoint of the socket.
  /**
   * This function is used to obtain the locally bound endpoint of the socket.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns An object that represents the local endpoint of the socket.
   * Returns a default-constructed endpoint object if an error occurred.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::system::error_code ec;
   * boost::asio::ip::tcp::endpoint endpoint = socket.local_endpoint(ec);
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * @endcode
   */
  endpoint_type local_endpoint(boost::system::error_code& ec) const
  {
    return impl_.get_service().local_endpoint(impl_.get_implementation(), ec);
  }

  /// Get the remote endpoint of the socket.
  /**
   * This function is used to obtain the remote endpoint of the socket.
   *
   * @returns An object that represents the remote endpoint of the socket.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::ip::tcp::endpoint endpoint = socket.remote_endpoint();
   * @endcode
   */
  endpoint_type remote_endpoint() const
  {
    boost::system::error_code ec;
    endpoint_type ep = impl_.get_service().remote_endpoint(
        impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "remote_endpoint");
    return ep;
  }

  /// Get the remote endpoint of the socket.
  /**
   * This function is used to obtain the remote endpoint of the socket.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns An object that represents the remote endpoint of the socket.
   * Returns a default-constructed endpoint object if an error occurred.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::system::error_code ec;
   * boost::asio::ip::tcp::endpoint endpoint = socket.remote_endpoint(ec);
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * @endcode
   */
  endpoint_type remote_endpoint(boost::system::error_code& ec) const
  {
    return impl_.get_service().remote_endpoint(impl_.get_implementation(), ec);
  }

  /// Disable sends or receives on the socket.
  /**
   * This function is used to disable send operations, receive operations, or
   * both.
   *
   * @param what Determines what types of operation will no longer be allowed.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @par Example
   * Shutting down the send side of the socket:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send);
   * @endcode
   */
  void shutdown(shutdown_type what)
  {
    boost::system::error_code ec;
    impl_.get_service().shutdown(impl_.get_implementation(), what, ec);
    boost::asio::detail::throw_error(ec, "shutdown");
  }

  /// Disable sends or receives on the socket.
  /**
   * This function is used to disable send operations, receive operations, or
   * both.
   *
   * @param what Determines what types of operation will no longer be allowed.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @par Example
   * Shutting down the send side of the socket:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::system::error_code ec;
   * socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * @endcode
   */
  BOOST_ASIO_SYNC_OP_VOID shutdown(shutdown_type what,
      boost::system::error_code& ec)
  {
    impl_.get_service().shutdown(impl_.get_implementation(), what, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Wait for the socket to become ready to read, ready to write, or to have
  /// pending error conditions.
  /**
   * This function is used to perform a blocking wait for a socket to enter
   * a ready to read, write or error condition state.
   *
   * @param w Specifies the desired socket state.
   *
   * @par Example
   * Waiting for a socket to become readable.
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * socket.wait(boost::asio::ip::tcp::socket::wait_read);
   * @endcode
   */
  void wait(wait_type w)
  {
    boost::system::error_code ec;
    impl_.get_service().wait(impl_.get_implementation(), w, ec);
    boost::asio::detail::throw_error(ec, "wait");
  }

  /// Wait for the socket to become ready to read, ready to write, or to have
  /// pending error conditions.
  /**
   * This function is used to perform a blocking wait for a socket to enter
   * a ready to read, write or error condition state.
   *
   * @param w Specifies the desired socket state.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @par Example
   * Waiting for a socket to become readable.
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::system::error_code ec;
   * socket.wait(boost::asio::ip::tcp::socket::wait_read, ec);
   * @endcode
   */
  BOOST_ASIO_SYNC_OP_VOID wait(wait_type w, boost::system::error_code& ec)
  {
    impl_.get_service().wait(impl_.get_implementation(), w, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Asynchronously wait for the socket to become ready to read, ready to
  /// write, or to have pending error conditions.
  /**
   * This function is used to perform an asynchronous wait for a socket to enter
   * a ready to read, write or error condition state.
   *
   * @param w Specifies the desired socket state.
   *
   * @param handler The handler to be called when the wait operation completes.
   * Copies will be made of the handler as required. The function signature of
   * the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error // Result of operation
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Example
   * @code
   * void wait_handler(const boost::system::error_code& error)
   * {
   *   if (!error)
   *   {
   *     // Wait succeeded.
   *   }
   * }
   *
   * ...
   *
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * socket.async_wait(boost::asio::ip::tcp::socket::wait_read, wait_handler);
   * @endcode
   */
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code))
        WaitHandler BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WaitHandler,
      void (boost::system::error_code))
  async_wait(wait_type w,
      BOOST_ASIO_MOVE_ARG(WaitHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WaitHandler, void (boost::system::error_code)>(
        initiate_async_wait(this), handler, w);
  }

protected:
  /// Protected destructor to prevent deletion through this type.
  /**
   * This function destroys the socket, cancelling any outstanding asynchronous
   * operations associated with the socket as if by calling @c cancel.
   */
  ~basic_socket()
  {
  }

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)
  detail::io_object_impl<
    detail::null_socket_service<Protocol>, Executor> impl_;
#elif defined(BOOST_ASIO_HAS_IOCP)
  detail::io_object_impl<
    detail::win_iocp_socket_service<Protocol>, Executor> impl_;
#else
  detail::io_object_impl<
    detail::reactive_socket_service<Protocol>, Executor> impl_;
#endif

private:
  // Disallow copying and assignment.
  basic_socket(const basic_socket&) BOOST_ASIO_DELETED;
  basic_socket& operator=(const basic_socket&) BOOST_ASIO_DELETED;

  class initiate_async_connect
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_connect(basic_socket* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename ConnectHandler>
    void operator()(BOOST_ASIO_MOVE_ARG(ConnectHandler) handler,
        const endpoint_type& peer_endpoint,
        const boost::system::error_code& open_ec) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ConnectHandler.
      BOOST_ASIO_CONNECT_HANDLER_CHECK(ConnectHandler, handler) type_check;

      if (open_ec)
      {
          boost::asio::post(self_->impl_.get_executor(),
              boost::asio::detail::bind_handler(
                BOOST_ASIO_MOVE_CAST(ConnectHandler)(handler), open_ec));
      }
      else
      {
        detail::non_const_lvalue<ConnectHandler> handler2(handler);
        self_->impl_.get_service().async_connect(
            self_->impl_.get_implementation(), peer_endpoint,
            handler2.value, self_->impl_.get_implementation_executor());
      }
    }

  private:
    basic_socket* self_;
  };

  class initiate_async_wait
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_wait(basic_socket* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename WaitHandler>
    void operator()(BOOST_ASIO_MOVE_ARG(WaitHandler) handler, wait_type w) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a WaitHandler.
      BOOST_ASIO_WAIT_HANDLER_CHECK(WaitHandler, handler) type_check;

      detail::non_const_lvalue<WaitHandler> handler2(handler);
      self_->impl_.get_service().async_wait(
          self_->impl_.get_implementation(), w, handler2.value,
          self_->impl_.get_implementation_executor());
    }

  private:
    basic_socket* self_;
  };
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_BASIC_SOCKET_HPP

/* basic_socket.hpp
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
*/