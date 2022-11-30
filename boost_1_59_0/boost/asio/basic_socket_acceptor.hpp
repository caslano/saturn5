//
// basic_socket_acceptor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_SOCKET_ACCEPTOR_HPP
#define BOOST_ASIO_BASIC_SOCKET_ACCEPTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/any_io_executor.hpp>
#include <boost/asio/basic_socket.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/io_object_impl.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/socket_base.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)
# include <boost/asio/detail/null_socket_service.hpp>
#elif defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_socket_service.hpp>
#elif defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)
# include <boost/asio/detail/io_uring_socket_service.hpp>
#else
# include <boost/asio/detail/reactive_socket_service.hpp>
#endif

#if defined(BOOST_ASIO_HAS_MOVE)
# include <utility>
#endif // defined(BOOST_ASIO_HAS_MOVE)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if !defined(BOOST_ASIO_BASIC_SOCKET_ACCEPTOR_FWD_DECL)
#define BOOST_ASIO_BASIC_SOCKET_ACCEPTOR_FWD_DECL

// Forward declaration with defaulted arguments.
template <typename Protocol, typename Executor = any_io_executor>
class basic_socket_acceptor;

#endif // !defined(BOOST_ASIO_BASIC_SOCKET_ACCEPTOR_FWD_DECL)

/// Provides the ability to accept new connections.
/**
 * The basic_socket_acceptor class template is used for accepting new socket
 * connections.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 *
 * Synchronous @c accept operations are thread safe, if the underlying
 * operating system calls are also thread safe. This means that it is permitted
 * to perform concurrent calls to synchronous @c accept operations on a single
 * socket object. Other synchronous operations, such as @c open or @c close, are
 * not thread safe.
 *
 * @par Example
 * Opening a socket acceptor with the SO_REUSEADDR option enabled:
 * @code
 * boost::asio::ip::tcp::acceptor acceptor(my_context);
 * boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
 * acceptor.open(endpoint.protocol());
 * acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
 * acceptor.bind(endpoint);
 * acceptor.listen();
 * @endcode
 */
template <typename Protocol, typename Executor>
class basic_socket_acceptor
  : public socket_base
{
public:
  /// The type of the executor associated with the object.
  typedef Executor executor_type;

  /// Rebinds the acceptor type to another executor.
  template <typename Executor1>
  struct rebind_executor
  {
    /// The socket type when rebound to the specified executor.
    typedef basic_socket_acceptor<Protocol, Executor1> other;
  };

  /// The native representation of an acceptor.
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined native_handle_type;
#elif defined(BOOST_ASIO_WINDOWS_RUNTIME)
  typedef typename detail::null_socket_service<
    Protocol>::native_handle_type native_handle_type;
#elif defined(BOOST_ASIO_HAS_IOCP)
  typedef typename detail::win_iocp_socket_service<
    Protocol>::native_handle_type native_handle_type;
#elif defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)
  typedef typename detail::io_uring_socket_service<
    Protocol>::native_handle_type native_handle_type;
#else
  typedef typename detail::reactive_socket_service<
    Protocol>::native_handle_type native_handle_type;
#endif

  /// The protocol type.
  typedef Protocol protocol_type;

  /// The endpoint type.
  typedef typename Protocol::endpoint endpoint_type;

  /// Construct an acceptor without opening it.
  /**
   * This constructor creates an acceptor without opening it to listen for new
   * connections. The open() function must be called before the acceptor can
   * accept new socket connections.
   *
   * @param ex The I/O executor that the acceptor will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the
   * acceptor.
   */
  explicit basic_socket_acceptor(const executor_type& ex)
    : impl_(0, ex)
  {
  }

  /// Construct an acceptor without opening it.
  /**
   * This constructor creates an acceptor without opening it to listen for new
   * connections. The open() function must be called before the acceptor can
   * accept new socket connections.
   *
   * @param context An execution context which provides the I/O executor that
   * the acceptor will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the acceptor.
   */
  template <typename ExecutionContext>
  explicit basic_socket_acceptor(ExecutionContext& context,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
    : impl_(0, 0, context)
  {
  }

  /// Construct an open acceptor.
  /**
   * This constructor creates an acceptor and automatically opens it.
   *
   * @param ex The I/O executor that the acceptor will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the
   * acceptor.
   *
   * @param protocol An object specifying protocol parameters to be used.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_socket_acceptor(const executor_type& ex, const protocol_type& protocol)
    : impl_(0, ex)
  {
    boost::system::error_code ec;
    impl_.get_service().open(impl_.get_implementation(), protocol, ec);
    boost::asio::detail::throw_error(ec, "open");
  }

  /// Construct an open acceptor.
  /**
   * This constructor creates an acceptor and automatically opens it.
   *
   * @param context An execution context which provides the I/O executor that
   * the acceptor will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the acceptor.
   *
   * @param protocol An object specifying protocol parameters to be used.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_socket_acceptor(ExecutionContext& context,
      const protocol_type& protocol,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : impl_(0, 0, context)
  {
    boost::system::error_code ec;
    impl_.get_service().open(impl_.get_implementation(), protocol, ec);
    boost::asio::detail::throw_error(ec, "open");
  }

  /// Construct an acceptor opened on the given endpoint.
  /**
   * This constructor creates an acceptor and automatically opens it to listen
   * for new connections on the specified endpoint.
   *
   * @param ex The I/O executor that the acceptor will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the
   * acceptor.
   *
   * @param endpoint An endpoint on the local machine on which the acceptor
   * will listen for new connections.
   *
   * @param reuse_addr Whether the constructor should set the socket option
   * socket_base::reuse_address.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note This constructor is equivalent to the following code:
   * @code
   * basic_socket_acceptor<Protocol> acceptor(my_context);
   * acceptor.open(endpoint.protocol());
   * if (reuse_addr)
   *   acceptor.set_option(socket_base::reuse_address(true));
   * acceptor.bind(endpoint);
   * acceptor.listen();
   * @endcode
   */
  basic_socket_acceptor(const executor_type& ex,
      const endpoint_type& endpoint, bool reuse_addr = true)
    : impl_(0, ex)
  {
    boost::system::error_code ec;
    const protocol_type protocol = endpoint.protocol();
    impl_.get_service().open(impl_.get_implementation(), protocol, ec);
    boost::asio::detail::throw_error(ec, "open");
    if (reuse_addr)
    {
      impl_.get_service().set_option(impl_.get_implementation(),
          socket_base::reuse_address(true), ec);
      boost::asio::detail::throw_error(ec, "set_option");
    }
    impl_.get_service().bind(impl_.get_implementation(), endpoint, ec);
    boost::asio::detail::throw_error(ec, "bind");
    impl_.get_service().listen(impl_.get_implementation(),
        socket_base::max_listen_connections, ec);
    boost::asio::detail::throw_error(ec, "listen");
  }

  /// Construct an acceptor opened on the given endpoint.
  /**
   * This constructor creates an acceptor and automatically opens it to listen
   * for new connections on the specified endpoint.
   *
   * @param context An execution context which provides the I/O executor that
   * the acceptor will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the acceptor.
   *
   * @param endpoint An endpoint on the local machine on which the acceptor
   * will listen for new connections.
   *
   * @param reuse_addr Whether the constructor should set the socket option
   * socket_base::reuse_address.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note This constructor is equivalent to the following code:
   * @code
   * basic_socket_acceptor<Protocol> acceptor(my_context);
   * acceptor.open(endpoint.protocol());
   * if (reuse_addr)
   *   acceptor.set_option(socket_base::reuse_address(true));
   * acceptor.bind(endpoint);
   * acceptor.listen();
   * @endcode
   */
  template <typename ExecutionContext>
  basic_socket_acceptor(ExecutionContext& context,
      const endpoint_type& endpoint, bool reuse_addr = true,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
    : impl_(0, 0, context)
  {
    boost::system::error_code ec;
    const protocol_type protocol = endpoint.protocol();
    impl_.get_service().open(impl_.get_implementation(), protocol, ec);
    boost::asio::detail::throw_error(ec, "open");
    if (reuse_addr)
    {
      impl_.get_service().set_option(impl_.get_implementation(),
          socket_base::reuse_address(true), ec);
      boost::asio::detail::throw_error(ec, "set_option");
    }
    impl_.get_service().bind(impl_.get_implementation(), endpoint, ec);
    boost::asio::detail::throw_error(ec, "bind");
    impl_.get_service().listen(impl_.get_implementation(),
        socket_base::max_listen_connections, ec);
    boost::asio::detail::throw_error(ec, "listen");
  }

  /// Construct a basic_socket_acceptor on an existing native acceptor.
  /**
   * This constructor creates an acceptor object to hold an existing native
   * acceptor.
   *
   * @param ex The I/O executor that the acceptor will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the
   * acceptor.
   *
   * @param protocol An object specifying protocol parameters to be used.
   *
   * @param native_acceptor A native acceptor.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_socket_acceptor(const executor_type& ex,
      const protocol_type& protocol, const native_handle_type& native_acceptor)
    : impl_(0, ex)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(impl_.get_implementation(),
        protocol, native_acceptor, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

  /// Construct a basic_socket_acceptor on an existing native acceptor.
  /**
   * This constructor creates an acceptor object to hold an existing native
   * acceptor.
   *
   * @param context An execution context which provides the I/O executor that
   * the acceptor will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the acceptor.
   *
   * @param protocol An object specifying protocol parameters to be used.
   *
   * @param native_acceptor A native acceptor.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_socket_acceptor(ExecutionContext& context,
      const protocol_type& protocol, const native_handle_type& native_acceptor,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
    : impl_(0, 0, context)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(impl_.get_implementation(),
        protocol, native_acceptor, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct a basic_socket_acceptor from another.
  /**
   * This constructor moves an acceptor from one object to another.
   *
   * @param other The other basic_socket_acceptor object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_socket_acceptor(const executor_type&)
   * constructor.
   */
  basic_socket_acceptor(basic_socket_acceptor&& other) BOOST_ASIO_NOEXCEPT
    : impl_(std::move(other.impl_))
  {
  }

  /// Move-assign a basic_socket_acceptor from another.
  /**
   * This assignment operator moves an acceptor from one object to another.
   *
   * @param other The other basic_socket_acceptor object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_socket_acceptor(const executor_type&)
   * constructor.
   */
  basic_socket_acceptor& operator=(basic_socket_acceptor&& other)
  {
    impl_ = std::move(other.impl_);
    return *this;
  }

  // All socket acceptors have access to each other's implementations.
  template <typename Protocol1, typename Executor1>
  friend class basic_socket_acceptor;

  /// Move-construct a basic_socket_acceptor from an acceptor of another
  /// protocol type.
  /**
   * This constructor moves an acceptor from one object to another.
   *
   * @param other The other basic_socket_acceptor object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_socket_acceptor(const executor_type&)
   * constructor.
   */
  template <typename Protocol1, typename Executor1>
  basic_socket_acceptor(basic_socket_acceptor<Protocol1, Executor1>&& other,
      typename constraint<
        is_convertible<Protocol1, Protocol>::value
          && is_convertible<Executor1, Executor>::value
      >::type = 0)
    : impl_(std::move(other.impl_))
  {
  }

  /// Move-assign a basic_socket_acceptor from an acceptor of another protocol
  /// type.
  /**
   * This assignment operator moves an acceptor from one object to another.
   *
   * @param other The other basic_socket_acceptor object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_socket_acceptor(const executor_type&)
   * constructor.
   */
  template <typename Protocol1, typename Executor1>
  typename constraint<
    is_convertible<Protocol1, Protocol>::value
      && is_convertible<Executor1, Executor>::value,
    basic_socket_acceptor&
  >::type operator=(basic_socket_acceptor<Protocol1, Executor1>&& other)
  {
    basic_socket_acceptor tmp(std::move(other));
    impl_ = std::move(tmp.impl_);
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Destroys the acceptor.
  /**
   * This function destroys the acceptor, cancelling any outstanding
   * asynchronous operations associated with the acceptor as if by calling
   * @c cancel.
   */
  ~basic_socket_acceptor()
  {
  }

  /// Get the executor associated with the object.
  executor_type get_executor() BOOST_ASIO_NOEXCEPT
  {
    return impl_.get_executor();
  }

  /// Open the acceptor using the specified protocol.
  /**
   * This function opens the socket acceptor so that it will use the specified
   * protocol.
   *
   * @param protocol An object specifying which protocol is to be used.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * acceptor.open(boost::asio::ip::tcp::v4());
   * @endcode
   */
  void open(const protocol_type& protocol = protocol_type())
  {
    boost::system::error_code ec;
    impl_.get_service().open(impl_.get_implementation(), protocol, ec);
    boost::asio::detail::throw_error(ec, "open");
  }

  /// Open the acceptor using the specified protocol.
  /**
   * This function opens the socket acceptor so that it will use the specified
   * protocol.
   *
   * @param protocol An object specifying which protocol is to be used.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * boost::system::error_code ec;
   * acceptor.open(boost::asio::ip::tcp::v4(), ec);
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

  /// Assigns an existing native acceptor to the acceptor.
  /*
   * This function opens the acceptor to hold an existing native acceptor.
   *
   * @param protocol An object specifying which protocol is to be used.
   *
   * @param native_acceptor A native acceptor.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void assign(const protocol_type& protocol,
      const native_handle_type& native_acceptor)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(impl_.get_implementation(),
        protocol, native_acceptor, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

  /// Assigns an existing native acceptor to the acceptor.
  /*
   * This function opens the acceptor to hold an existing native acceptor.
   *
   * @param protocol An object specifying which protocol is to be used.
   *
   * @param native_acceptor A native acceptor.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID assign(const protocol_type& protocol,
      const native_handle_type& native_acceptor, boost::system::error_code& ec)
  {
    impl_.get_service().assign(impl_.get_implementation(),
        protocol, native_acceptor, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Determine whether the acceptor is open.
  bool is_open() const
  {
    return impl_.get_service().is_open(impl_.get_implementation());
  }

  /// Bind the acceptor to the given local endpoint.
  /**
   * This function binds the socket acceptor to the specified endpoint on the
   * local machine.
   *
   * @param endpoint An endpoint on the local machine to which the socket
   * acceptor will be bound.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 12345);
   * acceptor.open(endpoint.protocol());
   * acceptor.bind(endpoint);
   * @endcode
   */
  void bind(const endpoint_type& endpoint)
  {
    boost::system::error_code ec;
    impl_.get_service().bind(impl_.get_implementation(), endpoint, ec);
    boost::asio::detail::throw_error(ec, "bind");
  }

  /// Bind the acceptor to the given local endpoint.
  /**
   * This function binds the socket acceptor to the specified endpoint on the
   * local machine.
   *
   * @param endpoint An endpoint on the local machine to which the socket
   * acceptor will be bound.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 12345);
   * acceptor.open(endpoint.protocol());
   * boost::system::error_code ec;
   * acceptor.bind(endpoint, ec);
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

  /// Place the acceptor into the state where it will listen for new
  /// connections.
  /**
   * This function puts the socket acceptor into the state where it may accept
   * new connections.
   *
   * @param backlog The maximum length of the queue of pending connections.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void listen(int backlog = socket_base::max_listen_connections)
  {
    boost::system::error_code ec;
    impl_.get_service().listen(impl_.get_implementation(), backlog, ec);
    boost::asio::detail::throw_error(ec, "listen");
  }

  /// Place the acceptor into the state where it will listen for new
  /// connections.
  /**
   * This function puts the socket acceptor into the state where it may accept
   * new connections.
   *
   * @param backlog The maximum length of the queue of pending connections.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::system::error_code ec;
   * acceptor.listen(boost::asio::socket_base::max_listen_connections, ec);
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * @endcode
   */
  BOOST_ASIO_SYNC_OP_VOID listen(int backlog, boost::system::error_code& ec)
  {
    impl_.get_service().listen(impl_.get_implementation(), backlog, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Close the acceptor.
  /**
   * This function is used to close the acceptor. Any asynchronous accept
   * operations will be cancelled immediately.
   *
   * A subsequent call to open() is required before the acceptor can again be
   * used to again perform socket accept operations.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void close()
  {
    boost::system::error_code ec;
    impl_.get_service().close(impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "close");
  }

  /// Close the acceptor.
  /**
   * This function is used to close the acceptor. Any asynchronous accept
   * operations will be cancelled immediately.
   *
   * A subsequent call to open() is required before the acceptor can again be
   * used to again perform socket accept operations.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::system::error_code ec;
   * acceptor.close(ec);
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * @endcode
   */
  BOOST_ASIO_SYNC_OP_VOID close(boost::system::error_code& ec)
  {
    impl_.get_service().close(impl_.get_implementation(), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Release ownership of the underlying native acceptor.
  /**
   * This function causes all outstanding asynchronous accept operations to
   * finish immediately, and the handlers for cancelled operations will be
   * passed the boost::asio::error::operation_aborted error. Ownership of the
   * native acceptor is then transferred to the caller.
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

  /// Release ownership of the underlying native acceptor.
  /**
   * This function causes all outstanding asynchronous accept operations to
   * finish immediately, and the handlers for cancelled operations will be
   * passed the boost::asio::error::operation_aborted error. Ownership of the
   * native acceptor is then transferred to the caller.
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

  /// Get the native acceptor representation.
  /**
   * This function may be used to obtain the underlying representation of the
   * acceptor. This is intended to allow access to native acceptor functionality
   * that is not otherwise provided.
   */
  native_handle_type native_handle()
  {
    return impl_.get_service().native_handle(impl_.get_implementation());
  }

  /// Cancel all asynchronous operations associated with the acceptor.
  /**
   * This function causes all outstanding asynchronous connect, send and receive
   * operations to finish immediately, and the handlers for cancelled operations
   * will be passed the boost::asio::error::operation_aborted error.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void cancel()
  {
    boost::system::error_code ec;
    impl_.get_service().cancel(impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "cancel");
  }

  /// Cancel all asynchronous operations associated with the acceptor.
  /**
   * This function causes all outstanding asynchronous connect, send and receive
   * operations to finish immediately, and the handlers for cancelled operations
   * will be passed the boost::asio::error::operation_aborted error.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID cancel(boost::system::error_code& ec)
  {
    impl_.get_service().cancel(impl_.get_implementation(), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Set an option on the acceptor.
  /**
   * This function is used to set an option on the acceptor.
   *
   * @param option The new option value to be set on the acceptor.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @sa SettableSocketOption @n
   * boost::asio::socket_base::reuse_address
   * boost::asio::socket_base::enable_connection_aborted
   *
   * @par Example
   * Setting the SOL_SOCKET/SO_REUSEADDR option:
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::acceptor::reuse_address option(true);
   * acceptor.set_option(option);
   * @endcode
   */
  template <typename SettableSocketOption>
  void set_option(const SettableSocketOption& option)
  {
    boost::system::error_code ec;
    impl_.get_service().set_option(impl_.get_implementation(), option, ec);
    boost::asio::detail::throw_error(ec, "set_option");
  }

  /// Set an option on the acceptor.
  /**
   * This function is used to set an option on the acceptor.
   *
   * @param option The new option value to be set on the acceptor.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @sa SettableSocketOption @n
   * boost::asio::socket_base::reuse_address
   * boost::asio::socket_base::enable_connection_aborted
   *
   * @par Example
   * Setting the SOL_SOCKET/SO_REUSEADDR option:
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::acceptor::reuse_address option(true);
   * boost::system::error_code ec;
   * acceptor.set_option(option, ec);
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

  /// Get an option from the acceptor.
  /**
   * This function is used to get the current value of an option on the
   * acceptor.
   *
   * @param option The option value to be obtained from the acceptor.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @sa GettableSocketOption @n
   * boost::asio::socket_base::reuse_address
   *
   * @par Example
   * Getting the value of the SOL_SOCKET/SO_REUSEADDR option:
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::acceptor::reuse_address option;
   * acceptor.get_option(option);
   * bool is_set = option.get();
   * @endcode
   */
  template <typename GettableSocketOption>
  void get_option(GettableSocketOption& option) const
  {
    boost::system::error_code ec;
    impl_.get_service().get_option(impl_.get_implementation(), option, ec);
    boost::asio::detail::throw_error(ec, "get_option");
  }

  /// Get an option from the acceptor.
  /**
   * This function is used to get the current value of an option on the
   * acceptor.
   *
   * @param option The option value to be obtained from the acceptor.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @sa GettableSocketOption @n
   * boost::asio::socket_base::reuse_address
   *
   * @par Example
   * Getting the value of the SOL_SOCKET/SO_REUSEADDR option:
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::acceptor::reuse_address option;
   * boost::system::error_code ec;
   * acceptor.get_option(option, ec);
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * bool is_set = option.get();
   * @endcode
   */
  template <typename GettableSocketOption>
  BOOST_ASIO_SYNC_OP_VOID get_option(GettableSocketOption& option,
      boost::system::error_code& ec) const
  {
    impl_.get_service().get_option(impl_.get_implementation(), option, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Perform an IO control command on the acceptor.
  /**
   * This function is used to execute an IO control command on the acceptor.
   *
   * @param command The IO control command to be performed on the acceptor.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @sa IoControlCommand @n
   * boost::asio::socket_base::non_blocking_io
   *
   * @par Example
   * Getting the number of bytes ready to read:
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::acceptor::non_blocking_io command(true);
   * socket.io_control(command);
   * @endcode
   */
  template <typename IoControlCommand>
  void io_control(IoControlCommand& command)
  {
    boost::system::error_code ec;
    impl_.get_service().io_control(impl_.get_implementation(), command, ec);
    boost::asio::detail::throw_error(ec, "io_control");
  }

  /// Perform an IO control command on the acceptor.
  /**
   * This function is used to execute an IO control command on the acceptor.
   *
   * @param command The IO control command to be performed on the acceptor.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @sa IoControlCommand @n
   * boost::asio::socket_base::non_blocking_io
   *
   * @par Example
   * Getting the number of bytes ready to read:
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::acceptor::non_blocking_io command(true);
   * boost::system::error_code ec;
   * socket.io_control(command, ec);
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * @endcode
   */
  template <typename IoControlCommand>
  BOOST_ASIO_SYNC_OP_VOID io_control(IoControlCommand& command,
      boost::system::error_code& ec)
  {
    impl_.get_service().io_control(impl_.get_implementation(), command, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Gets the non-blocking mode of the acceptor.
  /**
   * @returns @c true if the acceptor's synchronous operations will fail with
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

  /// Sets the non-blocking mode of the acceptor.
  /**
   * @param mode If @c true, the acceptor's synchronous operations will fail
   * with boost::asio::error::would_block if they are unable to perform the
   * requested operation immediately. If @c false, synchronous operations will
   * block until complete.
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

  /// Sets the non-blocking mode of the acceptor.
  /**
   * @param mode If @c true, the acceptor's synchronous operations will fail
   * with boost::asio::error::would_block if they are unable to perform the
   * requested operation immediately. If @c false, synchronous operations will
   * block until complete.
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

  /// Gets the non-blocking mode of the native acceptor implementation.
  /**
   * This function is used to retrieve the non-blocking mode of the underlying
   * native acceptor. This mode has no effect on the behaviour of the acceptor
   * object's synchronous operations.
   *
   * @returns @c true if the underlying acceptor is in non-blocking mode and
   * direct system calls may fail with boost::asio::error::would_block (or the
   * equivalent system error).
   *
   * @note The current non-blocking mode is cached by the acceptor object.
   * Consequently, the return value may be incorrect if the non-blocking mode
   * was set directly on the native acceptor.
   */
  bool native_non_blocking() const
  {
    return impl_.get_service().native_non_blocking(impl_.get_implementation());
  }

  /// Sets the non-blocking mode of the native acceptor implementation.
  /**
   * This function is used to modify the non-blocking mode of the underlying
   * native acceptor. It has no effect on the behaviour of the acceptor object's
   * synchronous operations.
   *
   * @param mode If @c true, the underlying acceptor is put into non-blocking
   * mode and direct system calls may fail with boost::asio::error::would_block
   * (or the equivalent system error).
   *
   * @throws boost::system::system_error Thrown on failure. If the @c mode is
   * @c false, but the current value of @c non_blocking() is @c true, this
   * function fails with boost::asio::error::invalid_argument, as the
   * combination does not make sense.
   */
  void native_non_blocking(bool mode)
  {
    boost::system::error_code ec;
    impl_.get_service().native_non_blocking(
        impl_.get_implementation(), mode, ec);
    boost::asio::detail::throw_error(ec, "native_non_blocking");
  }

  /// Sets the non-blocking mode of the native acceptor implementation.
  /**
   * This function is used to modify the non-blocking mode of the underlying
   * native acceptor. It has no effect on the behaviour of the acceptor object's
   * synchronous operations.
   *
   * @param mode If @c true, the underlying acceptor is put into non-blocking
   * mode and direct system calls may fail with boost::asio::error::would_block
   * (or the equivalent system error).
   *
   * @param ec Set to indicate what error occurred, if any. If the @c mode is
   * @c false, but the current value of @c non_blocking() is @c true, this
   * function fails with boost::asio::error::invalid_argument, as the
   * combination does not make sense.
   */
  BOOST_ASIO_SYNC_OP_VOID native_non_blocking(
      bool mode, boost::system::error_code& ec)
  {
    impl_.get_service().native_non_blocking(
        impl_.get_implementation(), mode, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Get the local endpoint of the acceptor.
  /**
   * This function is used to obtain the locally bound endpoint of the acceptor.
   *
   * @returns An object that represents the local endpoint of the acceptor.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::endpoint endpoint = acceptor.local_endpoint();
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

  /// Get the local endpoint of the acceptor.
  /**
   * This function is used to obtain the locally bound endpoint of the acceptor.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns An object that represents the local endpoint of the acceptor.
   * Returns a default-constructed endpoint object if an error occurred and the
   * error handler did not throw an exception.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::system::error_code ec;
   * boost::asio::ip::tcp::endpoint endpoint = acceptor.local_endpoint(ec);
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

  /// Wait for the acceptor to become ready to read, ready to write, or to have
  /// pending error conditions.
  /**
   * This function is used to perform a blocking wait for an acceptor to enter
   * a ready to read, write or error condition state.
   *
   * @param w Specifies the desired acceptor state.
   *
   * @par Example
   * Waiting for an acceptor to become readable.
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * acceptor.wait(boost::asio::ip::tcp::acceptor::wait_read);
   * @endcode
   */
  void wait(wait_type w)
  {
    boost::system::error_code ec;
    impl_.get_service().wait(impl_.get_implementation(), w, ec);
    boost::asio::detail::throw_error(ec, "wait");
  }

  /// Wait for the acceptor to become ready to read, ready to write, or to have
  /// pending error conditions.
  /**
   * This function is used to perform a blocking wait for an acceptor to enter
   * a ready to read, write or error condition state.
   *
   * @param w Specifies the desired acceptor state.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @par Example
   * Waiting for an acceptor to become readable.
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::system::error_code ec;
   * acceptor.wait(boost::asio::ip::tcp::acceptor::wait_read, ec);
   * @endcode
   */
  BOOST_ASIO_SYNC_OP_VOID wait(wait_type w, boost::system::error_code& ec)
  {
    impl_.get_service().wait(impl_.get_implementation(), w, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Asynchronously wait for the acceptor to become ready to read, ready to
  /// write, or to have pending error conditions.
  /**
   * This function is used to perform an asynchronous wait for an acceptor to
   * enter a ready to read, write or error condition state. It is an initiating
   * function for an @ref asynchronous_operation, and always returns
   * immediately.
   *
   * @param w Specifies the desired acceptor state.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the wait completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   const boost::system::error_code& error // Result of operation.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Completion Signature
   * @code void(boost::system::error_code) @endcode
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
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * acceptor.async_wait(
   *     boost::asio::ip::tcp::acceptor::wait_read,
   *     wait_handler);
   * @endcode
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
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code))
        WaitToken BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WaitToken,
      void (boost::system::error_code))
  async_wait(wait_type w,
      BOOST_ASIO_MOVE_ARG(WaitToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WaitToken, void (boost::system::error_code)>(
        initiate_async_wait(this), token, w);
  }

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
  /// Accept a new connection.
  /**
   * This function is used to accept a new connection from a peer into the
   * given socket. The function call will block until a new connection has been
   * accepted successfully or an error occurs.
   *
   * @param peer The socket into which the new connection will be accepted.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::socket socket(my_context);
   * acceptor.accept(socket);
   * @endcode
   */
  template <typename Protocol1, typename Executor1>
  void accept(basic_socket<Protocol1, Executor1>& peer,
      typename constraint<
        is_convertible<Protocol, Protocol1>::value
      >::type = 0)
  {
    boost::system::error_code ec;
    impl_.get_service().accept(impl_.get_implementation(),
        peer, static_cast<endpoint_type*>(0), ec);
    boost::asio::detail::throw_error(ec, "accept");
  }

  /// Accept a new connection.
  /**
   * This function is used to accept a new connection from a peer into the
   * given socket. The function call will block until a new connection has been
   * accepted successfully or an error occurs.
   *
   * @param peer The socket into which the new connection will be accepted.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::socket socket(my_context);
   * boost::system::error_code ec;
   * acceptor.accept(socket, ec);
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * @endcode
   */
  template <typename Protocol1, typename Executor1>
  BOOST_ASIO_SYNC_OP_VOID accept(
      basic_socket<Protocol1, Executor1>& peer, boost::system::error_code& ec,
      typename constraint<
        is_convertible<Protocol, Protocol1>::value
      >::type = 0)
  {
    impl_.get_service().accept(impl_.get_implementation(),
        peer, static_cast<endpoint_type*>(0), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Start an asynchronous accept.
  /**
   * This function is used to asynchronously accept a new connection into a
   * socket, and additionally obtain the endpoint of the remote peer. It is an
   * initiating function for an @ref asynchronous_operation, and always returns
   * immediately.
   *
   * @param peer The socket into which the new connection will be accepted.
   * Ownership of the peer object is retained by the caller, which must
   * guarantee that it is valid until the completion handler is called.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the accept completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   const boost::system::error_code& error // Result of operation.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Completion Signature
   * @code void(boost::system::error_code) @endcode
   *
   * @par Example
   * @code
   * void accept_handler(const boost::system::error_code& error)
   * {
   *   if (!error)
   *   {
   *     // Accept succeeded.
   *   }
   * }
   *
   * ...
   *
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::socket socket(my_context);
   * acceptor.async_accept(socket, accept_handler);
   * @endcode
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
  template <typename Protocol1, typename Executor1,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code))
        AcceptToken BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(AcceptToken,
      void (boost::system::error_code))
  async_accept(basic_socket<Protocol1, Executor1>& peer,
      BOOST_ASIO_MOVE_ARG(AcceptToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type),
      typename constraint<
        is_convertible<Protocol, Protocol1>::value
      >::type = 0)
  {
    return async_initiate<AcceptToken, void (boost::system::error_code)>(
        initiate_async_accept(this), token,
        &peer, static_cast<endpoint_type*>(0));
  }

  /// Accept a new connection and obtain the endpoint of the peer
  /**
   * This function is used to accept a new connection from a peer into the
   * given socket, and additionally provide the endpoint of the remote peer.
   * The function call will block until a new connection has been accepted
   * successfully or an error occurs.
   *
   * @param peer The socket into which the new connection will be accepted.
   *
   * @param peer_endpoint An endpoint object which will receive the endpoint of
   * the remote peer.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::socket socket(my_context);
   * boost::asio::ip::tcp::endpoint endpoint;
   * acceptor.accept(socket, endpoint);
   * @endcode
   */
  template <typename Executor1>
  void accept(basic_socket<protocol_type, Executor1>& peer,
      endpoint_type& peer_endpoint)
  {
    boost::system::error_code ec;
    impl_.get_service().accept(impl_.get_implementation(),
        peer, &peer_endpoint, ec);
    boost::asio::detail::throw_error(ec, "accept");
  }

  /// Accept a new connection and obtain the endpoint of the peer
  /**
   * This function is used to accept a new connection from a peer into the
   * given socket, and additionally provide the endpoint of the remote peer.
   * The function call will block until a new connection has been accepted
   * successfully or an error occurs.
   *
   * @param peer The socket into which the new connection will be accepted.
   *
   * @param peer_endpoint An endpoint object which will receive the endpoint of
   * the remote peer.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::socket socket(my_context);
   * boost::asio::ip::tcp::endpoint endpoint;
   * boost::system::error_code ec;
   * acceptor.accept(socket, endpoint, ec);
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * @endcode
   */
  template <typename Executor1>
  BOOST_ASIO_SYNC_OP_VOID accept(basic_socket<protocol_type, Executor1>& peer,
      endpoint_type& peer_endpoint, boost::system::error_code& ec)
  {
    impl_.get_service().accept(
        impl_.get_implementation(), peer, &peer_endpoint, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Start an asynchronous accept.
  /**
   * This function is used to asynchronously accept a new connection into a
   * socket, and additionally obtain the endpoint of the remote peer. It is an
   * initiating function for an @ref asynchronous_operation, and always returns
   * immediately.
   *
   * @param peer The socket into which the new connection will be accepted.
   * Ownership of the peer object is retained by the caller, which must
   * guarantee that it is valid until the completion handler is called.
   *
   * @param peer_endpoint An endpoint object into which the endpoint of the
   * remote peer will be written. Ownership of the peer_endpoint object is
   * retained by the caller, which must guarantee that it is valid until the
   * handler is called.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the accept completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   const boost::system::error_code& error // Result of operation.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Completion Signature
   * @code void(boost::system::error_code) @endcode
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
  template <typename Executor1,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code))
        AcceptToken BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(AcceptToken,
      void (boost::system::error_code))
  async_accept(basic_socket<protocol_type, Executor1>& peer,
      endpoint_type& peer_endpoint,
      BOOST_ASIO_MOVE_ARG(AcceptToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<AcceptToken, void (boost::system::error_code)>(
        initiate_async_accept(this), token, &peer, &peer_endpoint);
  }
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Accept a new connection.
  /**
   * This function is used to accept a new connection from a peer. The function
   * call will block until a new connection has been accepted successfully or
   * an error occurs.
   *
   * This overload requires that the Protocol template parameter satisfy the
   * AcceptableProtocol type requirements.
   *
   * @returns A socket object representing the newly accepted connection.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::socket socket(acceptor.accept());
   * @endcode
   */
  typename Protocol::socket::template rebind_executor<executor_type>::other
  accept()
  {
    boost::system::error_code ec;
    typename Protocol::socket::template rebind_executor<
      executor_type>::other peer(impl_.get_executor());
    impl_.get_service().accept(impl_.get_implementation(), peer, 0, ec);
    boost::asio::detail::throw_error(ec, "accept");
    return peer;
  }

  /// Accept a new connection.
  /**
   * This function is used to accept a new connection from a peer. The function
   * call will block until a new connection has been accepted successfully or
   * an error occurs.
   *
   * This overload requires that the Protocol template parameter satisfy the
   * AcceptableProtocol type requirements.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns On success, a socket object representing the newly accepted
   * connection. On error, a socket object where is_open() is false.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::socket socket(acceptor.accept(ec));
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * @endcode
   */
  typename Protocol::socket::template rebind_executor<executor_type>::other
  accept(boost::system::error_code& ec)
  {
    typename Protocol::socket::template rebind_executor<
      executor_type>::other peer(impl_.get_executor());
    impl_.get_service().accept(impl_.get_implementation(), peer, 0, ec);
    return peer;
  }

  /// Start an asynchronous accept.
  /**
   * This function is used to asynchronously accept a new connection. It is an
   * initiating function for an @ref asynchronous_operation, and always returns
   * immediately.
   *
   * This overload requires that the Protocol template parameter satisfy the
   * AcceptableProtocol type requirements.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the accept completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   // Result of operation.
   *   const boost::system::error_code& error,
   *
   *   // On success, the newly accepted socket.
   *   typename Protocol::socket::template
   *     rebind_executor<executor_type>::other peer
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Completion Signature
   * @code void(boost::system::error_code,
   *    typename Protocol::socket::template
   *      rebind_executor<executor_type>::other)) @endcode
   *
   * @par Example
   * @code
   * void accept_handler(const boost::system::error_code& error,
   *     boost::asio::ip::tcp::socket peer)
   * {
   *   if (!error)
   *   {
   *     // Accept succeeded.
   *   }
   * }
   *
   * ...
   *
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * acceptor.async_accept(accept_handler);
   * @endcode
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
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        typename Protocol::socket::template rebind_executor<
          executor_type>::other)) MoveAcceptToken
            BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(MoveAcceptToken,
      void (boost::system::error_code,
        typename Protocol::socket::template
          rebind_executor<executor_type>::other))
  async_accept(
      BOOST_ASIO_MOVE_ARG(MoveAcceptToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<MoveAcceptToken,
      void (boost::system::error_code, typename Protocol::socket::template
        rebind_executor<executor_type>::other)>(
          initiate_async_move_accept(this), token,
          impl_.get_executor(), static_cast<endpoint_type*>(0),
          static_cast<typename Protocol::socket::template
            rebind_executor<executor_type>::other*>(0));
  }

  /// Accept a new connection.
  /**
   * This function is used to accept a new connection from a peer. The function
   * call will block until a new connection has been accepted successfully or
   * an error occurs.
   *
   * This overload requires that the Protocol template parameter satisfy the
   * AcceptableProtocol type requirements.
   *
   * @param ex The I/O executor object to be used for the newly
   * accepted socket.
   *
   * @returns A socket object representing the newly accepted connection.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::socket socket(acceptor.accept());
   * @endcode
   */
  template <typename Executor1>
  typename Protocol::socket::template rebind_executor<Executor1>::other
  accept(const Executor1& ex,
      typename constraint<
        is_executor<Executor1>::value
          || execution::is_executor<Executor1>::value
      >::type = 0)
  {
    boost::system::error_code ec;
    typename Protocol::socket::template
      rebind_executor<Executor1>::other peer(ex);
    impl_.get_service().accept(impl_.get_implementation(), peer, 0, ec);
    boost::asio::detail::throw_error(ec, "accept");
    return peer;
  }

  /// Accept a new connection.
  /**
   * This function is used to accept a new connection from a peer. The function
   * call will block until a new connection has been accepted successfully or
   * an error occurs.
   *
   * This overload requires that the Protocol template parameter satisfy the
   * AcceptableProtocol type requirements.
   *
   * @param context The I/O execution context object to be used for the newly
   * accepted socket.
   *
   * @returns A socket object representing the newly accepted connection.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::socket socket(acceptor.accept());
   * @endcode
   */
  template <typename ExecutionContext>
  typename Protocol::socket::template rebind_executor<
      typename ExecutionContext::executor_type>::other
  accept(ExecutionContext& context,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
  {
    boost::system::error_code ec;
    typename Protocol::socket::template rebind_executor<
        typename ExecutionContext::executor_type>::other peer(context);
    impl_.get_service().accept(impl_.get_implementation(), peer, 0, ec);
    boost::asio::detail::throw_error(ec, "accept");
    return peer;
  }

  /// Accept a new connection.
  /**
   * This function is used to accept a new connection from a peer. The function
   * call will block until a new connection has been accepted successfully or
   * an error occurs.
   *
   * This overload requires that the Protocol template parameter satisfy the
   * AcceptableProtocol type requirements.
   *
   * @param ex The I/O executor object to be used for the newly accepted
   * socket.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns On success, a socket object representing the newly accepted
   * connection. On error, a socket object where is_open() is false.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::socket socket(acceptor.accept(my_context2, ec));
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * @endcode
   */
  template <typename Executor1>
  typename Protocol::socket::template rebind_executor<Executor1>::other
  accept(const Executor1& ex, boost::system::error_code& ec,
      typename constraint<
        is_executor<Executor1>::value
          || execution::is_executor<Executor1>::value
      >::type = 0)
  {
    typename Protocol::socket::template
      rebind_executor<Executor1>::other peer(ex);
    impl_.get_service().accept(impl_.get_implementation(), peer, 0, ec);
    return peer;
  }

  /// Accept a new connection.
  /**
   * This function is used to accept a new connection from a peer. The function
   * call will block until a new connection has been accepted successfully or
   * an error occurs.
   *
   * This overload requires that the Protocol template parameter satisfy the
   * AcceptableProtocol type requirements.
   *
   * @param context The I/O execution context object to be used for the newly
   * accepted socket.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns On success, a socket object representing the newly accepted
   * connection. On error, a socket object where is_open() is false.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::socket socket(acceptor.accept(my_context2, ec));
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * @endcode
   */
  template <typename ExecutionContext>
  typename Protocol::socket::template rebind_executor<
      typename ExecutionContext::executor_type>::other
  accept(ExecutionContext& context, boost::system::error_code& ec,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
  {
    typename Protocol::socket::template rebind_executor<
        typename ExecutionContext::executor_type>::other peer(context);
    impl_.get_service().accept(impl_.get_implementation(), peer, 0, ec);
    return peer;
  }

  /// Start an asynchronous accept.
  /**
   * This function is used to asynchronously accept a new connection. It is an
   * initiating function for an @ref asynchronous_operation, and always returns
   * immediately.
   *
   * This overload requires that the Protocol template parameter satisfy the
   * AcceptableProtocol type requirements.
   *
   * @param ex The I/O executor object to be used for the newly accepted
   * socket.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the accept completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   // Result of operation.
   *   const boost::system::error_code& error,
   *
   *   // On success, the newly accepted socket.
   *   typename Protocol::socket::template rebind_executor<
   *     Executor1>::other peer
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Completion Signature
   * @code void(boost::system::error_code,
   *    typename Protocol::socket::template rebind_executor<
   *      Executor1>::other)) @endcode
   *
   * @par Example
   * @code
   * void accept_handler(const boost::system::error_code& error,
   *     boost::asio::ip::tcp::socket peer)
   * {
   *   if (!error)
   *   {
   *     // Accept succeeded.
   *   }
   * }
   *
   * ...
   *
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * acceptor.async_accept(my_context2, accept_handler);
   * @endcode
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
  template <typename Executor1,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        typename Protocol::socket::template rebind_executor<
          Executor1>::other)) MoveAcceptToken
            BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(MoveAcceptToken,
      void (boost::system::error_code,
        typename Protocol::socket::template rebind_executor<
          Executor1>::other))
  async_accept(const Executor1& ex,
      BOOST_ASIO_MOVE_ARG(MoveAcceptToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type),
      typename constraint<
        is_executor<Executor1>::value
          || execution::is_executor<Executor1>::value
      >::type = 0)
  {
    typedef typename Protocol::socket::template rebind_executor<
      Executor1>::other other_socket_type;

    return async_initiate<MoveAcceptToken,
      void (boost::system::error_code, other_socket_type)>(
        initiate_async_move_accept(this), token,
        ex, static_cast<endpoint_type*>(0),
        static_cast<other_socket_type*>(0));
  }

  /// Start an asynchronous accept.
  /**
   * This function is used to asynchronously accept a new connection. It is an
   * initiating function for an @ref asynchronous_operation, and always returns
   * immediately.
   *
   * This overload requires that the Protocol template parameter satisfy the
   * AcceptableProtocol type requirements.
   *
   * @param context The I/O execution context object to be used for the newly
   * accepted socket.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the accept completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   // Result of operation.
   *   const boost::system::error_code& error,
   *
   *   // On success, the newly accepted socket.
   *   typename Protocol::socket::template rebind_executor<
   *     typename ExecutionContext::executor_type>::other peer
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Completion Signature
   * @code void(boost::system::error_code,
   *    typename Protocol::socket::template rebind_executor<
   *      typename ExecutionContext::executor_type>::other)) @endcode
   *
   * @par Example
   * @code
   * void accept_handler(const boost::system::error_code& error,
   *     boost::asio::ip::tcp::socket peer)
   * {
   *   if (!error)
   *   {
   *     // Accept succeeded.
   *   }
   * }
   *
   * ...
   *
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * acceptor.async_accept(my_context2, accept_handler);
   * @endcode
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
  template <typename ExecutionContext,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        typename Protocol::socket::template rebind_executor<
          typename ExecutionContext::executor_type>::other)) MoveAcceptToken
            BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(MoveAcceptToken,
      void (boost::system::error_code,
        typename Protocol::socket::template rebind_executor<
          typename ExecutionContext::executor_type>::other))
  async_accept(ExecutionContext& context,
      BOOST_ASIO_MOVE_ARG(MoveAcceptToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type),
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
  {
    typedef typename Protocol::socket::template rebind_executor<
      typename ExecutionContext::executor_type>::other other_socket_type;

    return async_initiate<MoveAcceptToken,
      void (boost::system::error_code, other_socket_type)>(
        initiate_async_move_accept(this), token,
        context.get_executor(), static_cast<endpoint_type*>(0),
        static_cast<other_socket_type*>(0));
  }

  /// Accept a new connection.
  /**
   * This function is used to accept a new connection from a peer. The function
   * call will block until a new connection has been accepted successfully or
   * an error occurs.
   *
   * This overload requires that the Protocol template parameter satisfy the
   * AcceptableProtocol type requirements.
   *
   * @param peer_endpoint An endpoint object into which the endpoint of the
   * remote peer will be written.
   *
   * @returns A socket object representing the newly accepted connection.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::endpoint endpoint;
   * boost::asio::ip::tcp::socket socket(acceptor.accept(endpoint));
   * @endcode
   */
  typename Protocol::socket::template rebind_executor<executor_type>::other
  accept(endpoint_type& peer_endpoint)
  {
    boost::system::error_code ec;
    typename Protocol::socket::template rebind_executor<
      executor_type>::other peer(impl_.get_executor());
    impl_.get_service().accept(impl_.get_implementation(),
        peer, &peer_endpoint, ec);
    boost::asio::detail::throw_error(ec, "accept");
    return peer;
  }

  /// Accept a new connection.
  /**
   * This function is used to accept a new connection from a peer. The function
   * call will block until a new connection has been accepted successfully or
   * an error occurs.
   *
   * This overload requires that the Protocol template parameter satisfy the
   * AcceptableProtocol type requirements.
   *
   * @param peer_endpoint An endpoint object into which the endpoint of the
   * remote peer will be written.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns On success, a socket object representing the newly accepted
   * connection. On error, a socket object where is_open() is false.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::endpoint endpoint;
   * boost::asio::ip::tcp::socket socket(acceptor.accept(endpoint, ec));
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * @endcode
   */
  typename Protocol::socket::template rebind_executor<executor_type>::other
  accept(endpoint_type& peer_endpoint, boost::system::error_code& ec)
  {
    typename Protocol::socket::template rebind_executor<
      executor_type>::other peer(impl_.get_executor());
    impl_.get_service().accept(impl_.get_implementation(),
        peer, &peer_endpoint, ec);
    return peer;
  }

  /// Start an asynchronous accept.
  /**
   * This function is used to asynchronously accept a new connection. It is an
   * initiating function for an @ref asynchronous_operation, and always returns
   * immediately.
   *
   * This overload requires that the Protocol template parameter satisfy the
   * AcceptableProtocol type requirements.
   *
   * @param peer_endpoint An endpoint object into which the endpoint of the
   * remote peer will be written. Ownership of the peer_endpoint object is
   * retained by the caller, which must guarantee that it is valid until the
   * completion handler is called.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the accept completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   // Result of operation.
   *   const boost::system::error_code& error,
   *
   *   // On success, the newly accepted socket.
   *   typename Protocol::socket::template
   *     rebind_executor<executor_type>::other peer
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Completion Signature
   * @code void(boost::system::error_code,
   *    typename Protocol::socket::template
   *      rebind_executor<executor_type>::other)) @endcode
   *
   * @par Example
   * @code
   * void accept_handler(const boost::system::error_code& error,
   *     boost::asio::ip::tcp::socket peer)
   * {
   *   if (!error)
   *   {
   *     // Accept succeeded.
   *   }
   * }
   *
   * ...
   *
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::endpoint endpoint;
   * acceptor.async_accept(endpoint, accept_handler);
   * @endcode
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
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        typename Protocol::socket::template rebind_executor<
          executor_type>::other)) MoveAcceptToken
            BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(MoveAcceptToken,
      void (boost::system::error_code,
        typename Protocol::socket::template
          rebind_executor<executor_type>::other))
  async_accept(endpoint_type& peer_endpoint,
      BOOST_ASIO_MOVE_ARG(MoveAcceptToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<MoveAcceptToken,
      void (boost::system::error_code, typename Protocol::socket::template
        rebind_executor<executor_type>::other)>(
          initiate_async_move_accept(this), token,
          impl_.get_executor(), &peer_endpoint,
          static_cast<typename Protocol::socket::template
            rebind_executor<executor_type>::other*>(0));
  }

  /// Accept a new connection.
  /**
   * This function is used to accept a new connection from a peer. The function
   * call will block until a new connection has been accepted successfully or
   * an error occurs.
   *
   * This overload requires that the Protocol template parameter satisfy the
   * AcceptableProtocol type requirements.
   *
   * @param ex The I/O executor object to be used for the newly accepted
   * socket.
   *
   * @param peer_endpoint An endpoint object into which the endpoint of the
   * remote peer will be written.
   *
   * @returns A socket object representing the newly accepted connection.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::endpoint endpoint;
   * boost::asio::ip::tcp::socket socket(
   *     acceptor.accept(my_context2, endpoint));
   * @endcode
   */
  template <typename Executor1>
  typename Protocol::socket::template rebind_executor<Executor1>::other
  accept(const Executor1& ex, endpoint_type& peer_endpoint,
      typename constraint<
        is_executor<Executor1>::value
          || execution::is_executor<Executor1>::value
      >::type = 0)
  {
    boost::system::error_code ec;
    typename Protocol::socket::template
        rebind_executor<Executor1>::other peer(ex);
    impl_.get_service().accept(impl_.get_implementation(),
        peer, &peer_endpoint, ec);
    boost::asio::detail::throw_error(ec, "accept");
    return peer;
  }

  /// Accept a new connection.
  /**
   * This function is used to accept a new connection from a peer. The function
   * call will block until a new connection has been accepted successfully or
   * an error occurs.
   *
   * This overload requires that the Protocol template parameter satisfy the
   * AcceptableProtocol type requirements.
   *
   * @param context The I/O execution context object to be used for the newly
   * accepted socket.
   *
   * @param peer_endpoint An endpoint object into which the endpoint of the
   * remote peer will be written.
   *
   * @returns A socket object representing the newly accepted connection.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::endpoint endpoint;
   * boost::asio::ip::tcp::socket socket(
   *     acceptor.accept(my_context2, endpoint));
   * @endcode
   */
  template <typename ExecutionContext>
  typename Protocol::socket::template rebind_executor<
      typename ExecutionContext::executor_type>::other
  accept(ExecutionContext& context, endpoint_type& peer_endpoint,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
  {
    boost::system::error_code ec;
    typename Protocol::socket::template rebind_executor<
        typename ExecutionContext::executor_type>::other peer(context);
    impl_.get_service().accept(impl_.get_implementation(),
        peer, &peer_endpoint, ec);
    boost::asio::detail::throw_error(ec, "accept");
    return peer;
  }

  /// Accept a new connection.
  /**
   * This function is used to accept a new connection from a peer. The function
   * call will block until a new connection has been accepted successfully or
   * an error occurs.
   *
   * This overload requires that the Protocol template parameter satisfy the
   * AcceptableProtocol type requirements.
   *
   * @param ex The I/O executor object to be used for the newly accepted
   * socket.
   *
   * @param peer_endpoint An endpoint object into which the endpoint of the
   * remote peer will be written.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns On success, a socket object representing the newly accepted
   * connection. On error, a socket object where is_open() is false.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::endpoint endpoint;
   * boost::asio::ip::tcp::socket socket(
   *     acceptor.accept(my_context2, endpoint, ec));
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * @endcode
   */
  template <typename Executor1>
  typename Protocol::socket::template rebind_executor<Executor1>::other
  accept(const executor_type& ex,
      endpoint_type& peer_endpoint, boost::system::error_code& ec,
      typename constraint<
        is_executor<Executor1>::value
          || execution::is_executor<Executor1>::value
      >::type = 0)
  {
    typename Protocol::socket::template
      rebind_executor<Executor1>::other peer(ex);
    impl_.get_service().accept(impl_.get_implementation(),
        peer, &peer_endpoint, ec);
    return peer;
  }

  /// Accept a new connection.
  /**
   * This function is used to accept a new connection from a peer. The function
   * call will block until a new connection has been accepted successfully or
   * an error occurs.
   *
   * This overload requires that the Protocol template parameter satisfy the
   * AcceptableProtocol type requirements.
   *
   * @param context The I/O execution context object to be used for the newly
   * accepted socket.
   *
   * @param peer_endpoint An endpoint object into which the endpoint of the
   * remote peer will be written.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns On success, a socket object representing the newly accepted
   * connection. On error, a socket object where is_open() is false.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::endpoint endpoint;
   * boost::asio::ip::tcp::socket socket(
   *     acceptor.accept(my_context2, endpoint, ec));
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * @endcode
   */
  template <typename ExecutionContext>
  typename Protocol::socket::template rebind_executor<
      typename ExecutionContext::executor_type>::other
  accept(ExecutionContext& context,
      endpoint_type& peer_endpoint, boost::system::error_code& ec,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
  {
    typename Protocol::socket::template rebind_executor<
        typename ExecutionContext::executor_type>::other peer(context);
    impl_.get_service().accept(impl_.get_implementation(),
        peer, &peer_endpoint, ec);
    return peer;
  }

  /// Start an asynchronous accept.
  /**
   * This function is used to asynchronously accept a new connection. It is an
   * initiating function for an @ref asynchronous_operation, and always returns
   * immediately.
   *
   * This overload requires that the Protocol template parameter satisfy the
   * AcceptableProtocol type requirements.
   *
   * @param ex The I/O executor object to be used for the newly accepted
   * socket.
   *
   * @param peer_endpoint An endpoint object into which the endpoint of the
   * remote peer will be written. Ownership of the peer_endpoint object is
   * retained by the caller, which must guarantee that it is valid until the
   * completion handler is called.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the accept completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   // Result of operation.
   *   const boost::system::error_code& error,
   *
   *   // On success, the newly accepted socket.
   *   typename Protocol::socket::template rebind_executor<
   *     Executor1>::other peer
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Completion Signature
   * @code void(boost::system::error_code,
   *    typename Protocol::socket::template rebind_executor<
   *      Executor1>::other)) @endcode
   *
   * @par Example
   * @code
   * void accept_handler(const boost::system::error_code& error,
   *     boost::asio::ip::tcp::socket peer)
   * {
   *   if (!error)
   *   {
   *     // Accept succeeded.
   *   }
   * }
   *
   * ...
   *
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::endpoint endpoint;
   * acceptor.async_accept(my_context2, endpoint, accept_handler);
   * @endcode
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
  template <typename Executor1,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        typename Protocol::socket::template rebind_executor<
          Executor1>::other)) MoveAcceptToken
            BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(MoveAcceptToken,
      void (boost::system::error_code,
        typename Protocol::socket::template rebind_executor<
          Executor1>::other))
  async_accept(const Executor1& ex, endpoint_type& peer_endpoint,
      BOOST_ASIO_MOVE_ARG(MoveAcceptToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type),
      typename constraint<
        is_executor<Executor1>::value
          || execution::is_executor<Executor1>::value
      >::type = 0)
  {
    typedef typename Protocol::socket::template rebind_executor<
      Executor1>::other other_socket_type;

    return async_initiate<MoveAcceptToken,
      void (boost::system::error_code, other_socket_type)>(
        initiate_async_move_accept(this), token,
        ex, &peer_endpoint,
        static_cast<other_socket_type*>(0));
  }

  /// Start an asynchronous accept.
  /**
   * This function is used to asynchronously accept a new connection. It is an
   * initiating function for an @ref asynchronous_operation, and always returns
   * immediately.
   *
   * This overload requires that the Protocol template parameter satisfy the
   * AcceptableProtocol type requirements.
   *
   * @param context The I/O execution context object to be used for the newly
   * accepted socket.
   *
   * @param peer_endpoint An endpoint object into which the endpoint of the
   * remote peer will be written. Ownership of the peer_endpoint object is
   * retained by the caller, which must guarantee that it is valid until the
   * completion handler is called.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the accept completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   // Result of operation.
   *   const boost::system::error_code& error,
   *
   *   // On success, the newly accepted socket.
   *   typename Protocol::socket::template rebind_executor<
   *     typename ExecutionContext::executor_type>::other peer
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Completion Signature
   * @code void(boost::system::error_code,
   *    typename Protocol::socket::template rebind_executor<
   *      typename ExecutionContext::executor_type>::other)) @endcode
   *
   * @par Example
   * @code
   * void accept_handler(const boost::system::error_code& error,
   *     boost::asio::ip::tcp::socket peer)
   * {
   *   if (!error)
   *   {
   *     // Accept succeeded.
   *   }
   * }
   *
   * ...
   *
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::ip::tcp::endpoint endpoint;
   * acceptor.async_accept(my_context2, endpoint, accept_handler);
   * @endcode
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
  template <typename ExecutionContext,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        typename Protocol::socket::template rebind_executor<
          typename ExecutionContext::executor_type>::other)) MoveAcceptToken
            BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(MoveAcceptToken,
      void (boost::system::error_code,
        typename Protocol::socket::template rebind_executor<
          typename ExecutionContext::executor_type>::other))
  async_accept(ExecutionContext& context,
      endpoint_type& peer_endpoint,
      BOOST_ASIO_MOVE_ARG(MoveAcceptToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type),
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
  {
    typedef typename Protocol::socket::template rebind_executor<
      typename ExecutionContext::executor_type>::other other_socket_type;

    return async_initiate<MoveAcceptToken,
      void (boost::system::error_code, other_socket_type)>(
        initiate_async_move_accept(this), token,
        context.get_executor(), &peer_endpoint,
        static_cast<other_socket_type*>(0));
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

private:
  // Disallow copying and assignment.
  basic_socket_acceptor(const basic_socket_acceptor&) BOOST_ASIO_DELETED;
  basic_socket_acceptor& operator=(
      const basic_socket_acceptor&) BOOST_ASIO_DELETED;

  class initiate_async_wait
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_wait(basic_socket_acceptor* self)
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
          self_->impl_.get_implementation(), w,
          handler2.value, self_->impl_.get_executor());
    }

  private:
    basic_socket_acceptor* self_;
  };

  class initiate_async_accept
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_accept(basic_socket_acceptor* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename AcceptHandler, typename Protocol1, typename Executor1>
    void operator()(BOOST_ASIO_MOVE_ARG(AcceptHandler) handler,
        basic_socket<Protocol1, Executor1>* peer,
        endpoint_type* peer_endpoint) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a AcceptHandler.
      BOOST_ASIO_ACCEPT_HANDLER_CHECK(AcceptHandler, handler) type_check;

      detail::non_const_lvalue<AcceptHandler> handler2(handler);
      self_->impl_.get_service().async_accept(
          self_->impl_.get_implementation(), *peer, peer_endpoint,
          handler2.value, self_->impl_.get_executor());
    }

  private:
    basic_socket_acceptor* self_;
  };

  class initiate_async_move_accept
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_move_accept(basic_socket_acceptor* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename MoveAcceptHandler, typename Executor1, typename Socket>
    void operator()(BOOST_ASIO_MOVE_ARG(MoveAcceptHandler) handler,
        const Executor1& peer_ex, endpoint_type* peer_endpoint, Socket*) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a MoveAcceptHandler.
      BOOST_ASIO_MOVE_ACCEPT_HANDLER_CHECK(
          MoveAcceptHandler, handler, Socket) type_check;

      detail::non_const_lvalue<MoveAcceptHandler> handler2(handler);
      self_->impl_.get_service().async_move_accept(
          self_->impl_.get_implementation(), peer_ex, peer_endpoint,
          handler2.value, self_->impl_.get_executor());
    }

  private:
    basic_socket_acceptor* self_;
  };

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)
  detail::io_object_impl<
    detail::null_socket_service<Protocol>, Executor> impl_;
#elif defined(BOOST_ASIO_HAS_IOCP)
  detail::io_object_impl<
    detail::win_iocp_socket_service<Protocol>, Executor> impl_;
#elif defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)
  detail::io_object_impl<
    detail::io_uring_socket_service<Protocol>, Executor> impl_;
#else
  detail::io_object_impl<
    detail::reactive_socket_service<Protocol>, Executor> impl_;
#endif
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_BASIC_SOCKET_ACCEPTOR_HPP

/* basic_socket_acceptor.hpp
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
*/