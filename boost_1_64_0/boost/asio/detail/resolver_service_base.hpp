//
// detail/resolver_service_base.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_RESOLVER_SERVICE_BASE_HPP
#define BOOST_ASIO_DETAIL_RESOLVER_SERVICE_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/detail/mutex.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/resolve_op.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/scoped_ptr.hpp>
#include <boost/asio/detail/thread.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_io_context.hpp>
#else // defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/scheduler.hpp>
#endif // defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class resolver_service_base
{
public:
  // The implementation type of the resolver. A cancellation token is used to
  // indicate to the background thread that the operation has been cancelled.
  typedef socket_ops::shared_cancel_token_type implementation_type;

  // Constructor.
  BOOST_ASIO_DECL resolver_service_base(execution_context& context);

  // Destructor.
  BOOST_ASIO_DECL ~resolver_service_base();

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void base_shutdown();

  // Perform any fork-related housekeeping.
  BOOST_ASIO_DECL void base_notify_fork(
      execution_context::fork_event fork_ev);

  // Construct a new resolver implementation.
  BOOST_ASIO_DECL void construct(implementation_type& impl);

  // Destroy a resolver implementation.
  BOOST_ASIO_DECL void destroy(implementation_type&);

  // Move-construct a new resolver implementation.
  BOOST_ASIO_DECL void move_construct(implementation_type& impl,
      implementation_type& other_impl);

  // Move-assign from another resolver implementation.
  BOOST_ASIO_DECL void move_assign(implementation_type& impl,
      resolver_service_base& other_service,
      implementation_type& other_impl);

  // Cancel pending asynchronous operations.
  BOOST_ASIO_DECL void cancel(implementation_type& impl);

protected:
  // Helper function to start an asynchronous resolve operation.
  BOOST_ASIO_DECL void start_resolve_op(resolve_op* op);

#if !defined(BOOST_ASIO_WINDOWS_RUNTIME)
  // Helper class to perform exception-safe cleanup of addrinfo objects.
  class auto_addrinfo
    : private boost::asio::detail::noncopyable
  {
  public:
    explicit auto_addrinfo(boost::asio::detail::addrinfo_type* ai)
      : ai_(ai)
    {
    }

    ~auto_addrinfo()
    {
      if (ai_)
        socket_ops::freeaddrinfo(ai_);
    }

    operator boost::asio::detail::addrinfo_type*()
    {
      return ai_;
    }

  private:
    boost::asio::detail::addrinfo_type* ai_;
  };
#endif // !defined(BOOST_ASIO_WINDOWS_RUNTIME)

  // Helper class to run the work scheduler in a thread.
  class work_scheduler_runner;

  // Start the work scheduler if it's not already running.
  BOOST_ASIO_DECL void start_work_thread();

  // The scheduler implementation used to post completions.
#if defined(BOOST_ASIO_HAS_IOCP)
  typedef class win_iocp_io_context scheduler_impl;
#else
  typedef class scheduler scheduler_impl;
#endif
  scheduler_impl& scheduler_;

private:
  // Mutex to protect access to internal data.
  boost::asio::detail::mutex mutex_;

  // Private scheduler used for performing asynchronous host resolution.
  boost::asio::detail::scoped_ptr<scheduler_impl> work_scheduler_;

  // Thread used for running the work io_context's run loop.
  boost::asio::detail::scoped_ptr<boost::asio::detail::thread> work_thread_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/resolver_service_base.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_DETAIL_RESOLVER_SERVICE_BASE_HPP

/* resolver_service_base.hpp
n9dYdiq6pDmdC0NCiF1sk3BAMv/111o+ksDxrkbM4bPchqnho3LDEe9O6F/3Hmh2veRpjt4JKID7XxAdgjYn5XsGR/rj7oMW+8FjuAcYVe2SCU0K0PE4uAxIRAQHA1a+jVs3NJUnMryn2AB3jy6+OMEDy5NkcqG8+t0T4SkuWgnHrHh8APJ/6R8wcEDXy+uGLPZpps2bOAVwaZE50Rb+aFH5grESQcv+76H4TNOeeP92II36fT/XDKJ1XgD/95/x0aYBXHC+bYgYP3mFFpCQP8N4uB79C0+7tNHm39X6CGkzFDJmii0T12oq3KOOYmJ5fWfpOd9xrYwq6UHF6RdnVb8R0ML33Xh5JfndHIHVhof44KX9zhrjAzNpkZmtFdyxnzFcgmcmpFQTcTCAiQWi9qa5W3fMu8dK1FMuuJj+pqyDMX/BTo/4wqa8u9kYLylGtUAvvTlJsIRu7Eec8aheIymCmT/A4zQDcqW8TWrRpnoFScSp119p2+TrPr0VgSHnjdqkTKjeYa3X3w3alVyf71b9/ZFSNgzBOGHOUzefwexfvzwux5BHcMfLPQ==
*/