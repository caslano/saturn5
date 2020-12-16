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
5TqDmENq66oraTp/84mEadvgfCuOdVQta45z5M+SjoOkJB17DDc46sRx+6ANJf6vhp5nOreo16SHTra6Y3OnyHPP4ttFJoD11KFyrJS0XyTHLmoQhxUO+32pUI4Ns/egpWz0OSZhjqcxgfvyLFeUcKYMm0TOmZrynyjnrwmMJ+QdxPa09ZCr/FOpaqE6OE78qwKTkI14VzdtZ6fInEcrTdNnsR3Pu5LaM6z1ahNTnyezFl86r5x7oPuRt5d8bm+QYzVkTVJDRxstLV5aXGqeKZskzkuxv5Gmx8x18D/lbpda/34j8Y8wc/W5UrevJhbOE0dVTdmzu9w8yuP7HEfOUb7JtMgpyJs8YLe13M6DPsc7SxyPkIcG5KGBlWFkXdOrpk9pLWHWBobKPqAcs+8xEmJ3T1rzMtMmy0U+aL6RrhB/Wy1zrXushqPuUesnBbzi2C4yiaYdPyn+N/m6XnHchrIc69+gJfX3Y+77NJ7zGwI1+V+ieZpV0xwlngWh/kLCvG5NlWc7x0z5NfPMS/sqSYfJSxfxr7fzYsq+BUcGWnd5X1vbcJ+qmvubzbVCz90qHji7O4dsp+m+843c7wm23GHkLkCO9+lvB+NaRj6fjVx6F5VrXPnbYFwTX7k8Wy756lHBuKYuuVH4m+Gf2CbU7yPbtYZ/TalxRbi/4Zzfu8z9G7lN6TXPh7xang9p6AG8IeVnZc0umiuT5Pa3bWWELoDY6wyf65dja8Pn88Oe7fIhL+s4eS4ql4XmY+45/nwpnVd26SyauuU/nqHyPczzcrf4ZwdGB1r4jWlomAHmu/gl8c8IjA808HyHKDBheptv4ufFPyswJRDv6p8Xcv4VOT89MDKQ5Pt+e0xk+gbesc40+3m/JcfysTX+DrazG8k3I12zVdjV/mbszScjX44fYUTZ5310hIYp7c76Fdk3dnJy48TUuKbJWYmJwdTmGDhuldwreWhyl+TxiY2CTTskto5L4YtybCKaJbcfj/PXhP0TLuw7XJ8/mffKc8veL9+kewTHnrT6oheVaaXKt5L2XzVbTplxpMYSvkK/k0x4vruupESaRn6HmDY/TMIFzfjBWPHn2nayTTwzeOIOxvpvyDbxXMruUDfyIt/PBxIbx8UlJsV1IMed4hMbBJOoo15jRL7Pqjvlmt8il9OsDDnmnX9579brp3S3vyXmu783VCbPlom7nG+CYNxk/nt+F6h8SXfzXbDWy062yGpdWNddv+WDo0KiLln1k/dodITQ7fEYGyvxGBsrd79jmm/3wz1rIt2D66RcTvi190X0ATKsiVqefib49AWEC3+/3C7+LWjpxJt7GXCMEU4wYfqZ79Kfiv9u6zarged71045fy93v2XYs1zHXc3z5HGR24y9gsaR7d/U5d+JDHXd3qNW/EPM+NFe8d/Iu8NZ1uU8l0L1JL4H972n3Rd047kUjKeeJHrWE5Vf21PvfXJeMC7N8t0n/5VQ3T/xN994883nrgPyzUc5c0zKOazPP6SLuBqG+nzlUsJX3R9+v/U2+91nle9h7vNu8b9h/dpK8u/z74/ov8W/Dzsi7v67NPRMkPOvMFrSwN0PaF35UGS2c4c66zHG/OTYj3nnuFH67qOUfTuevW/afXdD+u7b/fvuARpmGWX1roSZmPz15NnJvZMnJF+QPDq5J3bp0xKbxCXQnzej82rBhJHH/fOsu59I2rZSdzvrMTu937Nac9SvPqfBj0TuUWuNhk2zwxJfK4761fHkB7SOa7/fBr/Wcfx2HD/nzpyFzZGmUsczKa+J2XYdnxhMSA7Gj/Wr4ypfkW3X8ULPOi6yWrZVyD4sfSHtIcUtG823c4FH3Z8R3v+FzeHEa4c=
*/