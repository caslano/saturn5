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
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
*/