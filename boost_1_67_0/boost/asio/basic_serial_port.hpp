//
// basic_serial_port.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/io_object_impl.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/executor.hpp>
#include <boost/asio/serial_port_base.hpp>
#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_serial_port_service.hpp>
#else
# include <boost/asio/detail/reactive_serial_port_service.hpp>
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
template <typename Executor = executor>
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
  typedef detail::reactive_serial_port_service::native_handle_type
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
    : impl_(ex)
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
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value,
        basic_serial_port
      >::type* = 0)
    : impl_(context)
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
    : impl_(ex)
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
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : impl_(context)
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
    : impl_(ex)
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
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : impl_(context)
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
    : impl_(ex)
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
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : impl_(context)
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
   * The function call always returns immediately.
   *
   * @param buffers One or more data buffers to be written to the serial port.
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
   * basic_serial_port.async_write_some(
   *     boost::asio::buffer(data, size), handler);
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
        initiate_async_write_some(this), handler, buffers);
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
   * basic_serial_port.async_read_some(
   *     boost::asio::buffer(data, size), handler);
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
        initiate_async_read_some(this), handler, buffers);
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
          self_->impl_.get_implementation(), buffers, handler2.value,
          self_->impl_.get_implementation_executor());
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
          self_->impl_.get_implementation(), buffers, handler2.value,
          self_->impl_.get_implementation_executor());
    }

  private:
    basic_serial_port* self_;
  };

#if defined(BOOST_ASIO_HAS_IOCP)
  detail::io_object_impl<detail::win_iocp_serial_port_service, Executor> impl_;
#else
  detail::io_object_impl<detail::reactive_serial_port_service, Executor> impl_;
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