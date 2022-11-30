//
// detail/strand_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STRAND_SERVICE_HPP
#define BOOST_ASIO_DETAIL_STRAND_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/detail/mutex.hpp>
#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/detail/operation.hpp>
#include <boost/asio/detail/scoped_ptr.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Default service implementation for a strand.
class strand_service
  : public boost::asio::detail::service_base<strand_service>
{
private:
  // Helper class to re-post the strand on exit.
  struct on_do_complete_exit;

  // Helper class to re-post the strand on exit.
  struct on_dispatch_exit;

public:

  // The underlying implementation of a strand.
  class strand_impl
    : public operation
  {
  public:
    strand_impl();

  private:
    // Only this service will have access to the internal values.
    friend class strand_service;
    friend struct on_do_complete_exit;
    friend struct on_dispatch_exit;

    // Mutex to protect access to internal data.
    boost::asio::detail::mutex mutex_;

    // Indicates whether the strand is currently "locked" by a handler. This
    // means that there is a handler upcall in progress, or that the strand
    // itself has been scheduled in order to invoke some pending handlers.
    bool locked_;

    // The handlers that are waiting on the strand but should not be run until
    // after the next time the strand is scheduled. This queue must only be
    // modified while the mutex is locked.
    op_queue<operation> waiting_queue_;

    // The handlers that are ready to be run. Logically speaking, these are the
    // handlers that hold the strand's lock. The ready queue is only modified
    // from within the strand and so may be accessed without locking the mutex.
    op_queue<operation> ready_queue_;
  };

  typedef strand_impl* implementation_type;

  // Construct a new strand service for the specified io_context.
  BOOST_ASIO_DECL explicit strand_service(boost::asio::io_context& io_context);

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void shutdown();

  // Construct a new strand implementation.
  BOOST_ASIO_DECL void construct(implementation_type& impl);

  // Request the io_context to invoke the given handler.
  template <typename Handler>
  void dispatch(implementation_type& impl, Handler& handler);

  // Request the io_context to invoke the given handler and return immediately.
  template <typename Handler>
  void post(implementation_type& impl, Handler& handler);

  // Determine whether the strand is running in the current thread.
  BOOST_ASIO_DECL bool running_in_this_thread(
      const implementation_type& impl) const;

private:
  // Helper function to dispatch a handler.
  BOOST_ASIO_DECL void do_dispatch(implementation_type& impl, operation* op);

  // Helper function to post a handler.
  BOOST_ASIO_DECL void do_post(implementation_type& impl,
      operation* op, bool is_continuation);

  BOOST_ASIO_DECL static void do_complete(void* owner,
      operation* base, const boost::system::error_code& ec,
      std::size_t bytes_transferred);

  // The io_context used to obtain an I/O executor.
  io_context& io_context_;

  // The io_context implementation used to post completions.
  io_context_impl& io_context_impl_;

  // Mutex to protect access to the array of implementations.
  boost::asio::detail::mutex mutex_;

  // Number of implementations shared between all strand objects.
#if defined(BOOST_ASIO_STRAND_IMPLEMENTATIONS)
  enum { num_implementations = BOOST_ASIO_STRAND_IMPLEMENTATIONS };
#else // defined(BOOST_ASIO_STRAND_IMPLEMENTATIONS)
  enum { num_implementations = 193 };
#endif // defined(BOOST_ASIO_STRAND_IMPLEMENTATIONS)

  // Pool of implementations.
  scoped_ptr<strand_impl> implementations_[num_implementations];

  // Extra value used when hashing to prevent recycled memory locations from
  // getting the same strand implementation.
  std::size_t salt_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/detail/impl/strand_service.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/strand_service.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_DETAIL_STRAND_SERVICE_HPP

/* strand_service.hpp
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
*/