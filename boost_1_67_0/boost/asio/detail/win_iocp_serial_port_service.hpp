//
// detail/win_iocp_serial_port_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2008 Rep Invariant Systems, Inc. (info@repinvariant.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_SERIAL_PORT_SERVICE_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_SERIAL_PORT_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP) && defined(BOOST_ASIO_HAS_SERIAL_PORT)

#include <string>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/detail/win_iocp_handle_service.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Extend win_iocp_handle_service to provide serial port support.
class win_iocp_serial_port_service :
  public execution_context_service_base<win_iocp_serial_port_service>
{
public:
  // The native type of a serial port.
  typedef win_iocp_handle_service::native_handle_type native_handle_type;

  // The implementation type of the serial port.
  typedef win_iocp_handle_service::implementation_type implementation_type;

  // Constructor.
  BOOST_ASIO_DECL win_iocp_serial_port_service(execution_context& context);

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void shutdown();

  // Construct a new serial port implementation.
  void construct(implementation_type& impl)
  {
    handle_service_.construct(impl);
  }

  // Move-construct a new serial port implementation.
  void move_construct(implementation_type& impl,
      implementation_type& other_impl)
  {
    handle_service_.move_construct(impl, other_impl);
  }

  // Move-assign from another serial port implementation.
  void move_assign(implementation_type& impl,
      win_iocp_serial_port_service& other_service,
      implementation_type& other_impl)
  {
    handle_service_.move_assign(impl,
        other_service.handle_service_, other_impl);
  }

  // Destroy a serial port implementation.
  void destroy(implementation_type& impl)
  {
    handle_service_.destroy(impl);
  }

  // Open the serial port using the specified device name.
  BOOST_ASIO_DECL boost::system::error_code open(implementation_type& impl,
      const std::string& device, boost::system::error_code& ec);

  // Assign a native handle to a serial port implementation.
  boost::system::error_code assign(implementation_type& impl,
      const native_handle_type& handle, boost::system::error_code& ec)
  {
    return handle_service_.assign(impl, handle, ec);
  }

  // Determine whether the serial port is open.
  bool is_open(const implementation_type& impl) const
  {
    return handle_service_.is_open(impl);
  }

  // Destroy a serial port implementation.
  boost::system::error_code close(implementation_type& impl,
      boost::system::error_code& ec)
  {
    return handle_service_.close(impl, ec);
  }

  // Get the native serial port representation.
  native_handle_type native_handle(implementation_type& impl)
  {
    return handle_service_.native_handle(impl);
  }

  // Cancel all operations associated with the handle.
  boost::system::error_code cancel(implementation_type& impl,
      boost::system::error_code& ec)
  {
    return handle_service_.cancel(impl, ec);
  }

  // Set an option on the serial port.
  template <typename SettableSerialPortOption>
  boost::system::error_code set_option(implementation_type& impl,
      const SettableSerialPortOption& option, boost::system::error_code& ec)
  {
    return do_set_option(impl,
        &win_iocp_serial_port_service::store_option<SettableSerialPortOption>,
        &option, ec);
  }

  // Get an option from the serial port.
  template <typename GettableSerialPortOption>
  boost::system::error_code get_option(const implementation_type& impl,
      GettableSerialPortOption& option, boost::system::error_code& ec) const
  {
    return do_get_option(impl,
        &win_iocp_serial_port_service::load_option<GettableSerialPortOption>,
        &option, ec);
  }

  // Send a break sequence to the serial port.
  boost::system::error_code send_break(implementation_type&,
      boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return ec;
  }

  // Write the given data. Returns the number of bytes sent.
  template <typename ConstBufferSequence>
  size_t write_some(implementation_type& impl,
      const ConstBufferSequence& buffers, boost::system::error_code& ec)
  {
    return handle_service_.write_some(impl, buffers, ec);
  }

  // Start an asynchronous write. The data being written must be valid for the
  // lifetime of the asynchronous operation.
  template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
  void async_write_some(implementation_type& impl,
      const ConstBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
  {
    handle_service_.async_write_some(impl, buffers, handler, io_ex);
  }

  // Read some data. Returns the number of bytes received.
  template <typename MutableBufferSequence>
  size_t read_some(implementation_type& impl,
      const MutableBufferSequence& buffers, boost::system::error_code& ec)
  {
    return handle_service_.read_some(impl, buffers, ec);
  }

  // Start an asynchronous read. The buffer for the data being received must be
  // valid for the lifetime of the asynchronous operation.
  template <typename MutableBufferSequence,
      typename Handler, typename IoExecutor>
  void async_read_some(implementation_type& impl,
      const MutableBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
  {
    handle_service_.async_read_some(impl, buffers, handler, io_ex);
  }

private:
  // Function pointer type for storing a serial port option.
  typedef boost::system::error_code (*store_function_type)(
      const void*, ::DCB&, boost::system::error_code&);

  // Helper function template to store a serial port option.
  template <typename SettableSerialPortOption>
  static boost::system::error_code store_option(const void* option,
      ::DCB& storage, boost::system::error_code& ec)
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
      void*, const ::DCB&, boost::system::error_code&);

  // Helper function template to load a serial port option.
  template <typename GettableSerialPortOption>
  static boost::system::error_code load_option(void* option,
      const ::DCB& storage, boost::system::error_code& ec)
  {
    static_cast<GettableSerialPortOption*>(option)->load(storage, ec);
    return ec;
  }

  // Helper function to get a serial port option.
  BOOST_ASIO_DECL boost::system::error_code do_get_option(
      const implementation_type& impl, load_function_type load,
      void* option, boost::system::error_code& ec) const;

  // The implementation used for initiating asynchronous operations.
  win_iocp_handle_service handle_service_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/win_iocp_serial_port_service.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_IOCP) && defined(BOOST_ASIO_HAS_SERIAL_PORT)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_SERIAL_PORT_SERVICE_HPP

/* win_iocp_serial_port_service.hpp
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
*/