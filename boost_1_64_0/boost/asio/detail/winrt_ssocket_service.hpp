//
// detail/winrt_ssocket_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WINRT_SSOCKET_SERVICE_HPP
#define BOOST_ASIO_DETAIL_WINRT_SSOCKET_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/winrt_socket_connect_op.hpp>
#include <boost/asio/detail/winrt_ssocket_service_base.hpp>
#include <boost/asio/detail/winrt_utils.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Protocol>
class winrt_ssocket_service :
  public execution_context_service_base<winrt_ssocket_service<Protocol> >,
  public winrt_ssocket_service_base
{
public:
  // The protocol type.
  typedef Protocol protocol_type;

  // The endpoint type.
  typedef typename Protocol::endpoint endpoint_type;

  // The native type of a socket.
  typedef Windows::Networking::Sockets::StreamSocket^ native_handle_type;

  // The implementation type of the socket.
  struct implementation_type : base_implementation_type
  {
    // Default constructor.
    implementation_type()
      : base_implementation_type(),
        protocol_(endpoint_type().protocol())
    {
    }

    // The protocol associated with the socket.
    protocol_type protocol_;
  };

  // Constructor.
  winrt_ssocket_service(execution_context& context)
    : execution_context_service_base<winrt_ssocket_service<Protocol> >(context),
      winrt_ssocket_service_base(context)
  {
  }

  // Destroy all user-defined handler objects owned by the service.
  void shutdown()
  {
    this->base_shutdown();
  }

  // Move-construct a new socket implementation.
  void move_construct(implementation_type& impl,
      implementation_type& other_impl) BOOST_ASIO_NOEXCEPT
  {
    this->base_move_construct(impl, other_impl);

    impl.protocol_ = other_impl.protocol_;
    other_impl.protocol_ = endpoint_type().protocol();
  }

  // Move-assign from another socket implementation.
  void move_assign(implementation_type& impl,
      winrt_ssocket_service& other_service,
      implementation_type& other_impl)
  {
    this->base_move_assign(impl, other_service, other_impl);

    impl.protocol_ = other_impl.protocol_;
    other_impl.protocol_ = endpoint_type().protocol();
  }

  // Move-construct a new socket implementation from another protocol type.
  template <typename Protocol1>
  void converting_move_construct(implementation_type& impl,
      winrt_ssocket_service<Protocol1>&,
      typename winrt_ssocket_service<
        Protocol1>::implementation_type& other_impl)
  {
    this->base_move_construct(impl, other_impl);

    impl.protocol_ = protocol_type(other_impl.protocol_);
    other_impl.protocol_ = typename Protocol1::endpoint().protocol();
  }

  // Open a new socket implementation.
  boost::system::error_code open(implementation_type& impl,
      const protocol_type& protocol, boost::system::error_code& ec)
  {
    if (is_open(impl))
    {
      ec = boost::asio::error::already_open;
      return ec;
    }

    try
    {
      impl.socket_ = ref new Windows::Networking::Sockets::StreamSocket;
      impl.protocol_ = protocol;
      ec = boost::system::error_code();
    }
    catch (Platform::Exception^ e)
    {
      ec = boost::system::error_code(e->HResult,
            boost::system::system_category());
    }

    return ec;
  }

  // Assign a native socket to a socket implementation.
  boost::system::error_code assign(implementation_type& impl,
      const protocol_type& protocol, const native_handle_type& native_socket,
      boost::system::error_code& ec)
  {
    if (is_open(impl))
    {
      ec = boost::asio::error::already_open;
      return ec;
    }

    impl.socket_ = native_socket;
    impl.protocol_ = protocol;
    ec = boost::system::error_code();

    return ec;
  }

  // Bind the socket to the specified local endpoint.
  boost::system::error_code bind(implementation_type&,
      const endpoint_type&, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return ec;
  }

  // Get the local endpoint.
  endpoint_type local_endpoint(const implementation_type& impl,
      boost::system::error_code& ec) const
  {
    endpoint_type endpoint;
    endpoint.resize(do_get_endpoint(impl, true,
          endpoint.data(), endpoint.size(), ec));
    return endpoint;
  }

  // Get the remote endpoint.
  endpoint_type remote_endpoint(const implementation_type& impl,
      boost::system::error_code& ec) const
  {
    endpoint_type endpoint;
    endpoint.resize(do_get_endpoint(impl, false,
          endpoint.data(), endpoint.size(), ec));
    return endpoint;
  }

  // Disable sends or receives on the socket.
  boost::system::error_code shutdown(implementation_type&,
      socket_base::shutdown_type, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return ec;
  }

  // Set a socket option.
  template <typename Option>
  boost::system::error_code set_option(implementation_type& impl,
      const Option& option, boost::system::error_code& ec)
  {
    return do_set_option(impl, option.level(impl.protocol_),
        option.name(impl.protocol_), option.data(impl.protocol_),
        option.size(impl.protocol_), ec);
  }

  // Get a socket option.
  template <typename Option>
  boost::system::error_code get_option(const implementation_type& impl,
      Option& option, boost::system::error_code& ec) const
  {
    std::size_t size = option.size(impl.protocol_);
    do_get_option(impl, option.level(impl.protocol_),
        option.name(impl.protocol_),
        option.data(impl.protocol_), &size, ec);
    if (!ec)
      option.resize(impl.protocol_, size);
    return ec;
  }

  // Connect the socket to the specified endpoint.
  boost::system::error_code connect(implementation_type& impl,
      const endpoint_type& peer_endpoint, boost::system::error_code& ec)
  {
    return do_connect(impl, peer_endpoint.data(), ec);
  }

  // Start an asynchronous connect.
  template <typename Handler, typename IoExecutor>
  void async_connect(implementation_type& impl,
      const endpoint_type& peer_endpoint,
      Handler& handler, const IoExecutor& io_ex)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef winrt_socket_connect_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((scheduler_.context(),
          *p.p, "socket", &impl, 0, "async_connect"));

    start_connect_op(impl, peer_endpoint.data(), p.p, is_continuation);
    p.v = p.p = 0;
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_WINRT_SSOCKET_SERVICE_HPP

/* winrt_ssocket_service.hpp
14G/B38ttku9fJ4/xHNqPAa9/I9Vb7yOgBng38Es9g8jv3YcnuMDJlscBxLPHsFKsAdYBSayP4n92nHyOtvHZybHZxbHZy6Yxf5h7BfHSRfp4uPs5OM4we58nB04XxxYC1I+8flxLJ5HgvRwOBfYi8NlOxVPG3AEGAmOBGPZL8IXwdVx+D1cvwaL5x0OP5HtJ4Hx4GQwAZwBinNMAUeC08BzwengbQ7v/h3gVHCn8PP59ina+Gpqa+h84jV8L5/vSoe3/GwA+4DXgCPAa8Gx4HXgeJFmMBf8FbgUrAaL2e8BN4N14BawHrwRTMG5bgIHgdeDw8CbQdSxFK4QvB2sAMXxrwBvAK8GN4KbeDs/v/DYUcTR4vnledh1Bl8As8D94GJxn4ObwUPgTeI+BW9m/x3g2+Dj4Dvgy+B74BHwfTAGx/4A7AYeBnuDn4D9wDpwBvg6eC54EFwEvgHmgW9y+j4CV4CfgavBz8Eq8GvwSvAYeC14CtwO/gDuAX8U8QFPg2+BCq7nJ6AKxuL6OsB40AUOAgPAZWAgeCnYCvw9GATeB7YGnwBDwNfAduCnYAdQPLe0B5PAMDADjATHgFHgGjAavBiMEccHO4GbwTjwHrCrOA/YDfwTKNJzAOwlyiHYG/wRTANDcP3SwUywLzgR7AeuBEW+V4AD4b8EzALl80ty08+58cKl+NfO5qT41y56Uppux/LgdrPdTWynX1v4M27HPgcngF+AYt834CLwBFgMfgdeBH7J63Z8BV7J2+Xzfqp/+VCT6l8+1KX6lw9Kr6bz4SBcOts9yPVNFLW/+ON1SjqBIzk/RoHdwaXcno8GZ/P6JEXgRM6HSdw+TQHFfTsbfAScC74JzgO/AOeDgWIOOhjFaxPH8drE8bwWcT9wOjiD1zFZCorzVII5vL7JOHAbeD54L4j4cbvB37TBSyzajRJOVxk4H6yQ+cffgMEItuX84/dlXXnz067GT7t9ftrV+2mn9PHPLl5nt7uRNbCz/bTL09lFGc6br79f/bBTHPx9gL9d4DrSXOHj3J58reL5DfwWjBLbwZ7s7w9+B84CvwfngAVIdwH4A/w14I/8XuPC9vvY/wD7nwQDwGfAQPAdsBX4HhgGBonxTtz+dASHg5HgRWAeuAHMB28AF4O3gUvAfWAB+DwYB74BdgG/ABPA02B3ULwHpYBhYCrYA+wlzgP2BnPA4WAheA5YAo4GLwXHgNXgWHAnOE6kB5wEvgUOAr8Bp4vjO3GfgnHgD/w+fC78s8HzwPPAyeDl4FRwPTge3AFOAO8Bs8GXwBHgK2Aa+D7YF/wY7CHOByaB34MzQPF+PBN0gYNBNzgEbAu2BjuBbrA+AM8raNDXD3Yq2+Gegjs62OnXWkYuPBhm7Wh6/fGcHQ3rGeUY1jQq2vHvWdeockcTaxsNcf5frG9UvaP5axztQph9O/xf6+jgDv/XKj+yw7/1jjrUNqx5lF575useja/96dY+yqtt2fpHFbUNayBtrG3+OkhWayDV1Pq/DtLeWv/WQkoa4vyPWQ+pvrbpNZGO15rXRXLvbN7aSNlIcx6cB64Gbh/cUbgOQ53KaLgiuGq4vXAH4I7DhQ5zKr3gxsNVwN0Ktw/uMJx7uFNJh5sHtwFuO1wd3DG4qHOcShbcLLgKuC1wj8IdgvsWLh4v2NlwBXAb4HbB1cEdh4sagbBwC+HWwm0ZcXbNprN///l/P5/+//IKkv8/Q/1/obk/Mk2R8yZcfJsVOXAU5iJ0JpV900ERn2vGTB0zY8Tk3KkjpozJLVuJOcoWY/QH8HiQjRSmq2MgzjIHbhXcrXB/hvsULg4zjAvh3oQ7Acfjh/hcnei4+TQeaGmhnDc=
*/