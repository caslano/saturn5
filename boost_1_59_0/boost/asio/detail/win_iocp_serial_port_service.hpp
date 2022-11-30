//
// detail/win_iocp_serial_port_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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