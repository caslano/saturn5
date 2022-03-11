//
// detail/strand_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
  // Helper function to dispatch a handler. Returns true if the handler should
  // be dispatched immediately.
  BOOST_ASIO_DECL bool do_dispatch(implementation_type& impl, operation* op);

  // Helper fiunction to post a handler.
  BOOST_ASIO_DECL void do_post(implementation_type& impl,
      operation* op, bool is_continuation);

  BOOST_ASIO_DECL static void do_complete(void* owner,
      operation* base, const boost::system::error_code& ec,
      std::size_t bytes_transferred);

  // The io_context implementation used to post completions.
  io_context_impl& io_context_;

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