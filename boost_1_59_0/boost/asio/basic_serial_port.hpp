//
// basic_serial_port.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2008 Rep Invariant Systems, Inc. (info@repinvariant.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_SERIAL_PORT_HPP
#define BOOST_ASIO_BASIC_SERIAL_PORT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_SERIAL_PORT) \
  || defined(GENERATING_DOCUMENTATION)

#include <string>
#include <boost/asio/any_io_executor.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/io_object_impl.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/serial_port_base.hpp>
#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_serial_port_service.hpp>
#else
# include <boost/asio/detail/posix_serial_port_service.hpp>
#endif

#if defined(BOOST_ASIO_HAS_MOVE)
# include <utility>
#endif // defined(BOOST_ASIO_HAS_MOVE)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Provides serial port functionality.
/**
 * The basic_serial_port class provides a wrapper over serial port
 * functionality.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <typename Executor = any_io_executor>
class basic_serial_port
  : public serial_port_base
{
public:
  /// The type of the executor associated with the object.
  typedef Executor executor_type;

  /// Rebinds the serial port type to another executor.
  template <typename Executor1>
  struct rebind_executor
  {
    /// The serial port type when rebound to the specified executor.
    typedef basic_serial_port<Executor1> other;
  };

  /// The native representation of a serial port.
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined native_handle_type;
#elif defined(BOOST_ASIO_HAS_IOCP)
  typedef detail::win_iocp_serial_port_service::native_handle_type
    native_handle_type;
#else
  typedef detail::posix_serial_port_service::native_handle_type
    native_handle_type;
#endif

  /// A basic_basic_serial_port is always the lowest layer.
  typedef basic_serial_port lowest_layer_type;

  /// Construct a basic_serial_port without opening it.
  /**
   * This constructor creates a serial port without opening it.
   *
   * @param ex The I/O executor that the serial port will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the
   * serial port.
   */
  explicit basic_serial_port(const executor_type& ex)
    : impl_(0, ex)
  {
  }

  /// Construct a basic_serial_port without opening it.
  /**
   * This constructor creates a serial port without opening it.
   *
   * @param context An execution context which provides the I/O executor that
   * the serial port will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the serial port.
   */
  template <typename ExecutionContext>
  explicit basic_serial_port(ExecutionContext& context,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : impl_(0, 0, context)
  {
  }

  /// Construct and open a basic_serial_port.
  /**
   * This constructor creates and opens a serial port for the specified device
   * name.
   *
   * @param ex The I/O executor that the serial port will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the
   * serial port.
   *
   * @param device The platform-specific device name for this serial
   * port.
   */
  basic_serial_port(const executor_type& ex, const char* device)
    : impl_(0, ex)
  {
    boost::system::error_code ec;
    impl_.get_service().open(impl_.get_implementation(), device, ec);
    boost::asio::detail::throw_error(ec, "open");
  }

  /// Construct and open a basic_serial_port.
  /**
   * This constructor creates and opens a serial port for the specified device
   * name.
   *
   * @param context An execution context which provides the I/O executor that
   * the serial port will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the serial port.
   *
   * @param device The platform-specific device name for this serial
   * port.
   */
  template <typename ExecutionContext>
  basic_serial_port(ExecutionContext& context, const char* device,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
    : impl_(0, 0, context)
  {
    boost::system::error_code ec;
    impl_.get_service().open(impl_.get_implementation(), device, ec);
    boost::asio::detail::throw_error(ec, "open");
  }

  /// Construct and open a basic_serial_port.
  /**
   * This constructor creates and opens a serial port for the specified device
   * name.
   *
   * @param ex The I/O executor that the serial port will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the
   * serial port.
   *
   * @param device The platform-specific device name for this serial
   * port.
   */
  basic_serial_port(const executor_type& ex, const std::string& device)
    : impl_(0, ex)
  {
    boost::system::error_code ec;
    impl_.get_service().open(impl_.get_implementation(), device, ec);
    boost::asio::detail::throw_error(ec, "open");
  }

  /// Construct and open a basic_serial_port.
  /**
   * This constructor creates and opens a serial port for the specified device
   * name.
   *
   * @param context An execution context which provides the I/O executor that
   * the serial port will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the serial port.
   *
   * @param device The platform-specific device name for this serial
   * port.
   */
  template <typename ExecutionContext>
  basic_serial_port(ExecutionContext& context, const std::string& device,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
    : impl_(0, 0, context)
  {
    boost::system::error_code ec;
    impl_.get_service().open(impl_.get_implementation(), device, ec);
    boost::asio::detail::throw_error(ec, "open");
  }

  /// Construct a basic_serial_port on an existing native serial port.
  /**
   * This constructor creates a serial port object to hold an existing native
   * serial port.
   *
   * @param ex The I/O executor that the serial port will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the
   * serial port.
   *
   * @param native_serial_port A native serial port.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_serial_port(const executor_type& ex,
      const native_handle_type& native_serial_port)
    : impl_(0, ex)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(impl_.get_implementation(),
        native_serial_port, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

  /// Construct a basic_serial_port on an existing native serial port.
  /**
   * This constructor creates a serial port object to hold an existing native
   * serial port.
   *
   * @param context An execution context which provides the I/O executor that
   * the serial port will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the serial port.
   *
   * @param native_serial_port A native serial port.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_serial_port(ExecutionContext& context,
      const native_handle_type& native_serial_port,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
    : impl_(0, 0, context)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(impl_.get_implementation(),
        native_serial_port, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct a basic_serial_port from another.
  /**
   * This constructor moves a serial port from one object to another.
   *
   * @param other The other basic_serial_port object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_serial_port(const executor_type&)
   * constructor.
   */
  basic_serial_port(basic_serial_port&& other)
    : impl_(std::move(other.impl_))
  {
  }

  /// Move-assign a basic_serial_port from another.
  /**
   * This assignment operator moves a serial port from one object to another.
   *
   * @param other The other basic_serial_port object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_serial_port(const executor_type&)
   * constructor.
   */
  basic_serial_port& operator=(basic_serial_port&& other)
  {
    impl_ = std::move(other.impl_);
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Destroys the serial port.
  /**
   * This function destroys the serial port, cancelling any outstanding
   * asynchronous wait operations associated with the serial port as if by
   * calling @c cancel.
   */
  ~basic_serial_port()
  {
  }

  /// Get the executor associated with the object.
  executor_type get_executor() BOOST_ASIO_NOEXCEPT
  {
    return impl_.get_executor();
  }

  /// Get a reference to the lowest layer.
  /**
   * This function returns a reference to the lowest layer in a stack of
   * layers. Since a basic_serial_port cannot contain any further layers, it
   * simply returns a reference to itself.
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
   * layers. Since a basic_serial_port cannot contain any further layers, it
   * simply returns a reference to itself.
   *
   * @return A const reference to the lowest layer in the stack of layers.
   * Ownership is not transferred to the caller.
   */
  const lowest_layer_type& lowest_layer() const
  {
    return *this;
  }

  /// Open the serial port using the specified device name.
  /**
   * This function opens the serial port for the specified device name.
   *
   * @param device The platform-specific device name.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void open(const std::string& device)
  {
    boost::system::error_code ec;
    impl_.get_service().open(impl_.get_implementation(), device, ec);
    boost::asio::detail::throw_error(ec, "open");
  }

  /// Open the serial port using the specified device name.
  /**
   * This function opens the serial port using the given platform-specific
   * device name.
   *
   * @param device The platform-specific device name.
   *
   * @param ec Set the indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID open(const std::string& device,
      boost::system::error_code& ec)
  {
    impl_.get_service().open(impl_.get_implementation(), device, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Assign an existing native serial port to the serial port.
  /*
   * This function opens the serial port to hold an existing native serial port.
   *
   * @param native_serial_port A native serial port.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void assign(const native_handle_type& native_serial_port)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(impl_.get_implementation(),
        native_serial_port, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

  /// Assign an existing native serial port to the serial port.
  /*
   * This function opens the serial port to hold an existing native serial port.
   *
   * @param native_serial_port A native serial port.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID assign(const native_handle_type& native_serial_port,
      boost::system::error_code& ec)
  {
    impl_.get_service().assign(impl_.get_implementation(),
        native_serial_port, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Determine whether the serial port is open.
  bool is_open() const
  {
    return impl_.get_service().is_open(impl_.get_implementation());
  }

  /// Close the serial port.
  /**
   * This function is used to close the serial port. Any asynchronous read or
   * write operations will be cancelled immediately, and will complete with the
   * boost::asio::error::operation_aborted error.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void close()
  {
    boost::system::error_code ec;
    impl_.get_service().close(impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "close");
  }

  /// Close the serial port.
  /**
   * This function is used to close the serial port. Any asynchronous read or
   * write operations will be cancelled immediately, and will complete with the
   * boost::asio::error::operation_aborted error.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID close(boost::system::error_code& ec)
  {
    impl_.get_service().close(impl_.get_implementation(), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Get the native serial port representation.
  /**
   * This function may be used to obtain the underlying representation of the
   * serial port. This is intended to allow access to native serial port
   * functionality that is not otherwise provided.
   */
  native_handle_type native_handle()
  {
    return impl_.get_service().native_handle(impl_.get_implementation());
  }

  /// Cancel all asynchronous operations associated with the serial port.
  /**
   * This function causes all outstanding asynchronous read or write operations
   * to finish immediately, and the handlers for cancelled operations will be
   * passed the boost::asio::error::operation_aborted error.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void cancel()
  {
    boost::system::error_code ec;
    impl_.get_service().cancel(impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "cancel");
  }

  /// Cancel all asynchronous operations associated with the serial port.
  /**
   * This function causes all outstanding asynchronous read or write operations
   * to finish immediately, and the handlers for cancelled operations will be
   * passed the boost::asio::error::operation_aborted error.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID cancel(boost::system::error_code& ec)
  {
    impl_.get_service().cancel(impl_.get_implementation(), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Send a break sequence to the serial port.
  /**
   * This function causes a break sequence of platform-specific duration to be
   * sent out the serial port.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void send_break()
  {
    boost::system::error_code ec;
    impl_.get_service().send_break(impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "send_break");
  }

  /// Send a break sequence to the serial port.
  /**
   * This function causes a break sequence of platform-specific duration to be
   * sent out the serial port.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID send_break(boost::system::error_code& ec)
  {
    impl_.get_service().send_break(impl_.get_implementation(), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Set an option on the serial port.
  /**
   * This function is used to set an option on the serial port.
   *
   * @param option The option value to be set on the serial port.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @sa SettableSerialPortOption @n
   * boost::asio::serial_port_base::baud_rate @n
   * boost::asio::serial_port_base::flow_control @n
   * boost::asio::serial_port_base::parity @n
   * boost::asio::serial_port_base::stop_bits @n
   * boost::asio::serial_port_base::character_size
   */
  template <typename SettableSerialPortOption>
  void set_option(const SettableSerialPortOption& option)
  {
    boost::system::error_code ec;
    impl_.get_service().set_option(impl_.get_implementation(), option, ec);
    boost::asio::detail::throw_error(ec, "set_option");
  }

  /// Set an option on the serial port.
  /**
   * This function is used to set an option on the serial port.
   *
   * @param option The option value to be set on the serial port.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @sa SettableSerialPortOption @n
   * boost::asio::serial_port_base::baud_rate @n
   * boost::asio::serial_port_base::flow_control @n
   * boost::asio::serial_port_base::parity @n
   * boost::asio::serial_port_base::stop_bits @n
   * boost::asio::serial_port_base::character_size
   */
  template <typename SettableSerialPortOption>
  BOOST_ASIO_SYNC_OP_VOID set_option(const SettableSerialPortOption& option,
      boost::system::error_code& ec)
  {
    impl_.get_service().set_option(impl_.get_implementation(), option, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Get an option from the serial port.
  /**
   * This function is used to get the current value of an option on the serial
   * port.
   *
   * @param option The option value to be obtained from the serial port.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @sa GettableSerialPortOption @n
   * boost::asio::serial_port_base::baud_rate @n
   * boost::asio::serial_port_base::flow_control @n
   * boost::asio::serial_port_base::parity @n
   * boost::asio::serial_port_base::stop_bits @n
   * boost::asio::serial_port_base::character_size
   */
  template <typename GettableSerialPortOption>
  void get_option(GettableSerialPortOption& option) const
  {
    boost::system::error_code ec;
    impl_.get_service().get_option(impl_.get_implementation(), option, ec);
    boost::asio::detail::throw_error(ec, "get_option");
  }

  /// Get an option from the serial port.
  /**
   * This function is used to get the current value of an option on the serial
   * port.
   *
   * @param option The option value to be obtained from the serial port.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @sa GettableSerialPortOption @n
   * boost::asio::serial_port_base::baud_rate @n
   * boost::asio::serial_port_base::flow_control @n
   * boost::asio::serial_port_base::parity @n
   * boost::asio::serial_port_base::stop_bits @n
   * boost::asio::serial_port_base::character_size
   */
  template <typename GettableSerialPortOption>
  BOOST_ASIO_SYNC_OP_VOID get_option(GettableSerialPortOption& option,
      boost::system::error_code& ec) const
  {
    impl_.get_service().get_option(impl_.get_implementation(), option, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Write some data to the serial port.
  /**
   * This function is used to write data to the serial port. The function call
   * will block until one or more bytes of the data has been written
   * successfully, or until an error occurs.
   *
   * @param buffers One or more data buffers to be written to the serial port.
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
   * basic_serial_port.write_some(boost::asio::buffer(data, size));
   * @endcode
   * See the @ref buffer documentation for information on writing multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = impl_.get_service().write_some(
        impl_.get_implementation(), buffers, ec);
    boost::asio::detail::throw_error(ec, "write_some");
    return s;
  }

  /// Write some data to the serial port.
  /**
   * This function is used to write data to the serial port. The function call
   * will block until one or more bytes of the data has been written
   * successfully, or until an error occurs.
   *
   * @param buffers One or more data buffers to be written to the serial port.
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
    return impl_.get_service().write_some(
        impl_.get_implementation(), buffers, ec);
  }

  /// Start an asynchronous write.
  /**
   * This function is used to asynchronously write data to the serial port.
   * It is an initiating function for an @ref asynchronous_operation, and always
   * returns immediately.
   *
   * @param buffers One or more data buffers to be written to the serial port.
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
   * basic_serial_port.async_write_some(
   *     boost::asio::buffer(data, size), handler);
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
        initiate_async_write_some(this), token, buffers);
  }

  /// Read some data from the serial port.
  /**
   * This function is used to read data from the serial port. The function
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
   * basic_serial_port.read_some(boost::asio::buffer(data, size));
   * @endcode
   * See the @ref buffer documentation for information on reading into multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = impl_.get_service().read_some(
        impl_.get_implementation(), buffers, ec);
    boost::asio::detail::throw_error(ec, "read_some");
    return s;
  }

  /// Read some data from the serial port.
  /**
   * This function is used to read data from the serial port. The function
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
    return impl_.get_service().read_some(
        impl_.get_implementation(), buffers, ec);
  }

  /// Start an asynchronous read.
  /**
   * This function is used to asynchronously read data from the serial port.
   * It is an initiating function for an @ref asynchronous_operation, and always
   * returns immediately.
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
   * basic_serial_port.async_read_some(
   *     boost::asio::buffer(data, size), handler);
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
        initiate_async_read_some(this), token, buffers);
  }

private:
  // Disallow copying and assignment.
  basic_serial_port(const basic_serial_port&) BOOST_ASIO_DELETED;
  basic_serial_port& operator=(const basic_serial_port&) BOOST_ASIO_DELETED;

  class initiate_async_write_some
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_write_some(basic_serial_port* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename WriteHandler, typename ConstBufferSequence>
    void operator()(BOOST_ASIO_MOVE_ARG(WriteHandler) handler,
        const ConstBufferSequence& buffers) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a WriteHandler.
      BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

      detail::non_const_lvalue<WriteHandler> handler2(handler);
      self_->impl_.get_service().async_write_some(
          self_->impl_.get_implementation(), buffers,
          handler2.value, self_->impl_.get_executor());
    }

  private:
    basic_serial_port* self_;
  };

  class initiate_async_read_some
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_read_some(basic_serial_port* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename ReadHandler, typename MutableBufferSequence>
    void operator()(BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
        const MutableBufferSequence& buffers) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ReadHandler.
      BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

      detail::non_const_lvalue<ReadHandler> handler2(handler);
      self_->impl_.get_service().async_read_some(
          self_->impl_.get_implementation(), buffers,
          handler2.value, self_->impl_.get_executor());
    }

  private:
    basic_serial_port* self_;
  };

#if defined(BOOST_ASIO_HAS_IOCP)
  detail::io_object_impl<detail::win_iocp_serial_port_service, Executor> impl_;
#else
  detail::io_object_impl<detail::posix_serial_port_service, Executor> impl_;
#endif
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_SERIAL_PORT)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_BASIC_SERIAL_PORT_HPP

/* basic_serial_port.hpp
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
*/