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
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
*/