//
// detail/resolver_service_base.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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

  // Move-construct a new timer implementation.
  void converting_move_construct(implementation_type& impl,
      resolver_service_base&, implementation_type& other_impl)
  {
    move_construct(impl, other_impl);
  }

  // Move-assign from another timer implementation.
  void converting_move_assign(implementation_type& impl,
      resolver_service_base& other_service,
      implementation_type& other_impl)
  {
    move_assign(impl, other_service, other_impl);
  }

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