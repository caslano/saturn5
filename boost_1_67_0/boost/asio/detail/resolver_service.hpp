//
// detail/resolver_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
  results_type resolve(implementation_type&, const query_type& query,
      boost::system::error_code& ec)
  {
    boost::asio::detail::addrinfo_type* address_info = 0;

    socket_ops::getaddrinfo(query.host_name().c_str(),
        query.service_name().c_str(), query.hints(), &address_info, ec);
    auto_addrinfo auto_address_info(address_info);

    return ec ? results_type() : results_type::create(
        address_info, query.host_name(), query.service_name());
  }

  // Asynchronously resolve a query to a list of entries.
  template <typename Handler, typename IoExecutor>
  void async_resolve(implementation_type& impl, const query_type& query,
      Handler& handler, const IoExecutor& io_ex)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef resolve_query_op<Protocol, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl, query, scheduler_, handler, io_ex);

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