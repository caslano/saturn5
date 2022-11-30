//
// detail/winrt_ssocket_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
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
*/