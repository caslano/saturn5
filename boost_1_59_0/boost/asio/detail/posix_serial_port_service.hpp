//
// detail/posix_serial_port_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2008 Rep Invariant Systems, Inc. (info@repinvariant.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_POSIX_SERIAL_PORT_SERVICE_HPP
#define BOOST_ASIO_DETAIL_POSIX_SERIAL_PORT_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_SERIAL_PORT)
#if !defined(BOOST_ASIO_WINDOWS) && !defined(__CYGWIN__)

#include <string>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/serial_port_base.hpp>
#include <boost/asio/detail/descriptor_ops.hpp>

#if defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)
# include <boost/asio/detail/io_uring_descriptor_service.hpp>
#else // defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)
# include <boost/asio/detail/reactive_descriptor_service.hpp>
#endif // defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Extend a descriptor_service to provide serial port support.
class posix_serial_port_service :
  public execution_context_service_base<posix_serial_port_service>
{
public:
#if defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)
  typedef io_uring_descriptor_service descriptor_service;
#else // defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)
  typedef reactive_descriptor_service descriptor_service;
#endif // defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)

  // The native type of a serial port.
  typedef descriptor_service::native_handle_type native_handle_type;

  // The implementation type of the serial port.
  typedef descriptor_service::implementation_type implementation_type;

  BOOST_ASIO_DECL posix_serial_port_service(execution_context& context);

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void shutdown();

  // Construct a new serial port implementation.
  void construct(implementation_type& impl)
  {
    descriptor_service_.construct(impl);
  }

  // Move-construct a new serial port implementation.
  void move_construct(implementation_type& impl,
      implementation_type& other_impl)
  {
    descriptor_service_.move_construct(impl, other_impl);
  }

  // Move-assign from another serial port implementation.
  void move_assign(implementation_type& impl,
      posix_serial_port_service& other_service,
      implementation_type& other_impl)
  {
    descriptor_service_.move_assign(impl,
        other_service.descriptor_service_, other_impl);
  }

  // Destroy a serial port implementation.
  void destroy(implementation_type& impl)
  {
    descriptor_service_.destroy(impl);
  }

  // Open the serial port using the specified device name.
  BOOST_ASIO_DECL boost::system::error_code open(implementation_type& impl,
      const std::string& device, boost::system::error_code& ec);

  // Assign a native descriptor to a serial port implementation.
  boost::system::error_code assign(implementation_type& impl,
      const native_handle_type& native_descriptor,
      boost::system::error_code& ec)
  {
    return descriptor_service_.assign(impl, native_descriptor, ec);
  }

  // Determine whether the serial port is open.
  bool is_open(const implementation_type& impl) const
  {
    return descriptor_service_.is_open(impl);
  }

  // Destroy a serial port implementation.
  boost::system::error_code close(implementation_type& impl,
      boost::system::error_code& ec)
  {
    return descriptor_service_.close(impl, ec);
  }

  // Get the native serial port representation.
  native_handle_type native_handle(implementation_type& impl)
  {
    return descriptor_service_.native_handle(impl);
  }

  // Cancel all operations associated with the serial port.
  boost::system::error_code cancel(implementation_type& impl,
      boost::system::error_code& ec)
  {
    return descriptor_service_.cancel(impl, ec);
  }

  // Set an option on the serial port.
  template <typename SettableSerialPortOption>
  boost::system::error_code set_option(implementation_type& impl,
      const SettableSerialPortOption& option, boost::system::error_code& ec)
  {
    return do_set_option(impl,
        &posix_serial_port_service::store_option<SettableSerialPortOption>,
        &option, ec);
  }

  // Get an option from the serial port.
  template <typename GettableSerialPortOption>
  boost::system::error_code get_option(const implementation_type& impl,
      GettableSerialPortOption& option, boost::system::error_code& ec) const
  {
    return do_get_option(impl,
        &posix_serial_port_service::load_option<GettableSerialPortOption>,
        &option, ec);
  }

  // Send a break sequence to the serial port.
  boost::system::error_code send_break(implementation_type& impl,
      boost::system::error_code& ec)
  {
    int result = ::tcsendbreak(descriptor_service_.native_handle(impl), 0);
    descriptor_ops::get_last_error(ec, result < 0);
    return ec;
  }

  // Write the given data. Returns the number of bytes sent.
  template <typename ConstBufferSequence>
  size_t write_some(implementation_type& impl,
      const ConstBufferSequence& buffers, boost::system::error_code& ec)
  {
    return descriptor_service_.write_some(impl, buffers, ec);
  }

  // Start an asynchronous write. The data being written must be valid for the
  // lifetime of the asynchronous operation.
  template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
  void async_write_some(implementation_type& impl,
      const ConstBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
  {
    descriptor_service_.async_write_some(impl, buffers, handler, io_ex);
  }

  // Read some data. Returns the number of bytes received.
  template <typename MutableBufferSequence>
  size_t read_some(implementation_type& impl,
      const MutableBufferSequence& buffers, boost::system::error_code& ec)
  {
    return descriptor_service_.read_some(impl, buffers, ec);
  }

  // Start an asynchronous read. The buffer for the data being received must be
  // valid for the lifetime of the asynchronous operation.
  template <typename MutableBufferSequence,
      typename Handler, typename IoExecutor>
  void async_read_some(implementation_type& impl,
      const MutableBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
  {
    descriptor_service_.async_read_some(impl, buffers, handler, io_ex);
  }

private:
  // Function pointer type for storing a serial port option.
  typedef boost::system::error_code (*store_function_type)(
      const void*, termios&, boost::system::error_code&);

  // Helper function template to store a serial port option.
  template <typename SettableSerialPortOption>
  static boost::system::error_code store_option(const void* option,
      termios& storage, boost::system::error_code& ec)
  {
    static_cast<const SettableSerialPortOption*>(option)->store(storage, ec);
    return ec;
  }

  // Helper function to set a serial port option.
  BOOST_ASIO_DECL boost::system::error_code do_set_option(
      implementation_type& impl, store_function_type store,
      const void* option, boost::system::error_code& ec);

  // Function pointer type for loading a serial port option.
  typedef boost::system::error_code (*load_function_type)(
      void*, const termios&, boost::system::error_code&);

  // Helper function template to load a serial port option.
  template <typename GettableSerialPortOption>
  static boost::system::error_code load_option(void* option,
      const termios& storage, boost::system::error_code& ec)
  {
    static_cast<GettableSerialPortOption*>(option)->load(storage, ec);
    return ec;
  }

  // Helper function to get a serial port option.
  BOOST_ASIO_DECL boost::system::error_code do_get_option(
      const implementation_type& impl, load_function_type load,
      void* option, boost::system::error_code& ec) const;

  // The implementation used for initiating asynchronous operations.
  descriptor_service descriptor_service_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/posix_serial_port_service.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // !defined(BOOST_ASIO_WINDOWS) && !defined(__CYGWIN__)
#endif // defined(BOOST_ASIO_HAS_SERIAL_PORT)

#endif // BOOST_ASIO_DETAIL_POSIX_SERIAL_PORT_SERVICE_HPP

/* posix_serial_port_service.hpp
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
*/