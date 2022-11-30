//
// detail/winrt_resolver_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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