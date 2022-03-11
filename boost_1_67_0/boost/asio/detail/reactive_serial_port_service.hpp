//
// detail/reactive_serial_port_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2008 Rep Invariant Systems, Inc. (info@repinvariant.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTIVE_SERIAL_PORT_SERVICE_HPP
#define BOOST_ASIO_DETAIL_REACTIVE_SERIAL_PORT_SERVICE_HPP

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
#include <boost/asio/detail/reactive_descriptor_service.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Extend reactive_descriptor_service to provide serial port support.
class reactive_serial_port_service :
  public execution_context_service_base<reactive_serial_port_service>
{
public:
  // The native type of a serial port.
  typedef reactive_descriptor_service::native_handle_type native_handle_type;

  // The implementation type of the serial port.
  typedef reactive_descriptor_service::implementation_type implementation_type;

  BOOST_ASIO_DECL reactive_serial_port_service(execution_context& context);

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
      reactive_serial_port_service& other_service,
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
        &reactive_serial_port_service::store_option<SettableSerialPortOption>,
        &option, ec);
  }

  // Get an option from the serial port.
  template <typename GettableSerialPortOption>
  boost::system::error_code get_option(const implementation_type& impl,
      GettableSerialPortOption& option, boost::system::error_code& ec) const
  {
    return do_get_option(impl,
        &reactive_serial_port_service::load_option<GettableSerialPortOption>,
        &option, ec);
  }

  // Send a break sequence to the serial port.
  boost::system::error_code send_break(implementation_type& impl,
      boost::system::error_code& ec)
  {
    errno = 0;
    descriptor_ops::error_wrapper(::tcsendbreak(
          descriptor_service_.native_handle(impl), 0), ec);
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
  reactive_descriptor_service descriptor_service_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/reactive_serial_port_service.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // !defined(BOOST_ASIO_WINDOWS) && !defined(__CYGWIN__)
#endif // defined(BOOST_ASIO_HAS_SERIAL_PORT)

#endif // BOOST_ASIO_DETAIL_REACTIVE_SERIAL_PORT_SERVICE_HPP

/* reactive_serial_port_service.hpp
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
*/