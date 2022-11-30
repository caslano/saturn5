//
// detail/resolver_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_RESOLVER_SERVICE_HPP
#define BOOST_ASIO_DETAIL_RESOLVER_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/ip/basic_resolver_query.hpp>
#include <boost/asio/ip/basic_resolver_results.hpp>
#include <boost/asio/detail/concurrency_hint.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/resolve_endpoint_op.hpp>
#include <boost/asio/detail/resolve_query_op.hpp>
#include <boost/asio/detail/resolver_service_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Protocol>
class resolver_service :
  public execution_context_service_base<resolver_service<Protocol> >,
  public resolver_service_base
{
public:
  // The implementation type of the resolver. A cancellation token is used to
  // indicate to the background thread that the operation has been cancelled.
  typedef socket_ops::shared_cancel_token_type implementation_type;

  // The endpoint type.
  typedef typename Protocol::endpoint endpoint_type;

  // The query type.
  typedef boost::asio::ip::basic_resolver_query<Protocol> query_type;

  // The results type.
  typedef boost::asio::ip::basic_resolver_results<Protocol> results_type;

  // Constructor.
  resolver_service(execution_context& context)
    : execution_context_service_base<resolver_service<Protocol> >(context),
      resolver_service_base(context)
  {
  }

  // Destroy all user-defined handler objects owned by the service.
  void shutdown()
  {
    this->base_shutdown();
  }

  // Perform any fork-related housekeeping.
  void notify_fork(execution_context::fork_event fork_ev)
  {
    this->base_notify_fork(fork_ev);
  }

  // Resolve a query to a list of entries.
  results_type resolve(implementation_type&, const query_type& qry,
      boost::system::error_code& ec)
  {
    boost::asio::detail::addrinfo_type* address_info = 0;

    socket_ops::getaddrinfo(qry.host_name().c_str(),
        qry.service_name().c_str(), qry.hints(), &address_info, ec);
    auto_addrinfo auto_address_info(address_info);

    return ec ? results_type() : results_type::create(
        address_info, qry.host_name(), qry.service_name());
  }

  // Asynchronously resolve a query to a list of entries.
  template <typename Handler, typename IoExecutor>
  void async_resolve(implementation_type& impl, const query_type& qry,
      Handler& handler, const IoExecutor& io_ex)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef resolve_query_op<Protocol, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl, qry, scheduler_, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((scheduler_.context(),
          *p.p, "resolver", &impl, 0, "async_resolve"));

    start_resolve_op(p.p);
    p.v = p.p = 0;
  }

  // Resolve an endpoint to a list of entries.
  results_type resolve(implementation_type&,
      const endpoint_type& endpoint, boost::system::error_code& ec)
  {
    char host_name[NI_MAXHOST];
    char service_name[NI_MAXSERV];
    socket_ops::sync_getnameinfo(endpoint.data(), endpoint.size(),
        host_name, NI_MAXHOST, service_name, NI_MAXSERV,
        endpoint.protocol().type(), ec);

    return ec ? results_type() : results_type::create(
        endpoint, host_name, service_name);
  }

  // Asynchronously resolve an endpoint to a list of entries.
  template <typename Handler, typename IoExecutor>
  void async_resolve(implementation_type& impl, const endpoint_type& endpoint,
      Handler& handler, const IoExecutor& io_ex)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef resolve_endpoint_op<Protocol, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl, endpoint, scheduler_, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((scheduler_.context(),
          *p.p, "resolver", &impl, 0, "async_resolve"));

    start_resolve_op(p.p);
    p.v = p.p = 0;
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_RESOLVER_SERVICE_HPP

/* resolver_service.hpp
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
*/