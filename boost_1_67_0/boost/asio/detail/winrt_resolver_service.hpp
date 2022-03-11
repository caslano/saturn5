//
// detail/winrt_resolver_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WINRT_RESOLVER_SERVICE_HPP
#define BOOST_ASIO_DETAIL_WINRT_RESOLVER_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/ip/basic_resolver_query.hpp>
#include <boost/asio/ip/basic_resolver_results.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/detail/winrt_async_manager.hpp>
#include <boost/asio/detail/winrt_resolve_op.hpp>
#include <boost/asio/detail/winrt_utils.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_io_context.hpp>
#else // defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/scheduler.hpp>
#endif // defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Protocol>
class winrt_resolver_service :
  public execution_context_service_base<winrt_resolver_service<Protocol> >
{
public:
  // The implementation type of the resolver. A cancellation token is used to
  // indicate to the asynchronous operation that the operation has been
  // cancelled.
  typedef socket_ops::shared_cancel_token_type implementation_type;

  // The endpoint type.
  typedef typename Protocol::endpoint endpoint_type;

  // The query type.
  typedef boost::asio::ip::basic_resolver_query<Protocol> query_type;

  // The results type.
  typedef boost::asio::ip::basic_resolver_results<Protocol> results_type;

  // Constructor.
  winrt_resolver_service(execution_context& context)
    : execution_context_service_base<
        winrt_resolver_service<Protocol> >(context),
      scheduler_(use_service<scheduler_impl>(context)),
      async_manager_(use_service<winrt_async_manager>(context))
  {
  }

  // Destructor.
  ~winrt_resolver_service()
  {
  }

  // Destroy all user-defined handler objects owned by the service.
  void shutdown()
  {
  }

  // Perform any fork-related housekeeping.
  void notify_fork(execution_context::fork_event)
  {
  }

  // Construct a new resolver implementation.
  void construct(implementation_type&)
  {
  }

  // Move-construct a new resolver implementation.
  void move_construct(implementation_type&,
      implementation_type&)
  {
  }

  // Move-assign from another resolver implementation.
  void move_assign(implementation_type&,
      winrt_resolver_service&, implementation_type&)
  {
  }

  // Destroy a resolver implementation.
  void destroy(implementation_type&)
  {
  }

  // Cancel pending asynchronous operations.
  void cancel(implementation_type&)
  {
  }

  // Resolve a query to a list of entries.
  results_type resolve(implementation_type&,
      const query_type& query, boost::system::error_code& ec)
  {
    try
    {
      using namespace Windows::Networking::Sockets;
      auto endpoint_pairs = async_manager_.sync(
          DatagramSocket::GetEndpointPairsAsync(
            winrt_utils::host_name(query.host_name()),
            winrt_utils::string(query.service_name())), ec);

      if (ec)
        return results_type();

      return results_type::create(
          endpoint_pairs, query.hints(),
          query.host_name(), query.service_name());
    }
    catch (Platform::Exception^ e)
    {
      ec = boost::system::error_code(e->HResult,
          boost::system::system_category());
      return results_type();
    }
  }

  // Asynchronously resolve a query to a list of entries.
  template <typename Handler, typename IoExecutor>
  void async_resolve(implementation_type& impl, const query_type& query,
      Handler& handler, const IoExecutor& io_ex)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef winrt_resolve_op<Protocol, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(query, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((scheduler_.context(),
          *p.p, "resolver", &impl, 0, "async_resolve"));
    (void)impl;

    try
    {
      using namespace Windows::Networking::Sockets;
      async_manager_.async(DatagramSocket::GetEndpointPairsAsync(
            winrt_utils::host_name(query.host_name()),
            winrt_utils::string(query.service_name())), p.p);
      p.v = p.p = 0;
    }
    catch (Platform::Exception^ e)
    {
      p.p->ec_ = boost::system::error_code(
          e->HResult, boost::system::system_category());
      scheduler_.post_immediate_completion(p.p, is_continuation);
      p.v = p.p = 0;
    }
  }

  // Resolve an endpoint to a list of entries.
  results_type resolve(implementation_type&,
      const endpoint_type&, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return results_type();
  }

  // Asynchronously resolve an endpoint to a list of entries.
  template <typename Handler, typename IoExecutor>
  void async_resolve(implementation_type&, const endpoint_type&,
      Handler& handler, const IoExecutor& io_ex)
  {
    boost::system::error_code ec = boost::asio::error::operation_not_supported;
    const results_type results;
    boost::asio::post(io_ex, detail::bind_handler(handler, ec, results));
  }

private:
  // The scheduler implementation used for delivering completions.
#if defined(BOOST_ASIO_HAS_IOCP)
  typedef class win_iocp_io_context scheduler_impl;
#else
  typedef class scheduler scheduler_impl;
#endif
  scheduler_impl& scheduler_;

  winrt_async_manager& async_manager_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_WINRT_RESOLVER_SERVICE_HPP

/* winrt_resolver_service.hpp
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
*/