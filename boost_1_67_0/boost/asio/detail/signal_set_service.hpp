//
// detail/signal_set_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SIGNAL_SET_SERVICE_HPP
#define BOOST_ASIO_DETAIL_SIGNAL_SET_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <cstddef>
#include <signal.h>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/detail/signal_handler.hpp>
#include <boost/asio/detail/signal_op.hpp>
#include <boost/asio/detail/socket_types.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_io_context.hpp>
#else // defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/scheduler.hpp>
#endif // defined(BOOST_ASIO_HAS_IOCP)

#if !defined(BOOST_ASIO_WINDOWS) && !defined(__CYGWIN__)
# include <boost/asio/detail/reactor.hpp>
#endif // !defined(BOOST_ASIO_WINDOWS) && !defined(__CYGWIN__)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

#if defined(NSIG) && (NSIG > 0)
enum { max_signal_number = NSIG };
#else
enum { max_signal_number = 128 };
#endif

extern BOOST_ASIO_DECL struct signal_state* get_signal_state();

extern "C" BOOST_ASIO_DECL void boost_asio_signal_handler(int signal_number);

class signal_set_service :
  public execution_context_service_base<signal_set_service>
{
public:
  // Type used for tracking an individual signal registration.
  class registration
  {
  public:
    // Default constructor.
    registration()
      : signal_number_(0),
        queue_(0),
        undelivered_(0),
        next_in_table_(0),
        prev_in_table_(0),
        next_in_set_(0)
    {
    }

  private:
    // Only this service will have access to the internal values.
    friend class signal_set_service;

    // The signal number that is registered.
    int signal_number_;

    // The waiting signal handlers.
    op_queue<signal_op>* queue_;

    // The number of undelivered signals.
    std::size_t undelivered_;

    // Pointers to adjacent registrations in the registrations_ table.
    registration* next_in_table_;
    registration* prev_in_table_;

    // Link to next registration in the signal set.
    registration* next_in_set_;
  };

  // The implementation type of the signal_set.
  class implementation_type
  {
  public:
    // Default constructor.
    implementation_type()
      : signals_(0)
    {
    }

  private:
    // Only this service will have access to the internal values.
    friend class signal_set_service;

    // The pending signal handlers.
    op_queue<signal_op> queue_;

    // Linked list of registered signals.
    registration* signals_;
  };

  // Constructor.
  BOOST_ASIO_DECL signal_set_service(execution_context& context);

  // Destructor.
  BOOST_ASIO_DECL ~signal_set_service();

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void shutdown();

  // Perform fork-related housekeeping.
  BOOST_ASIO_DECL void notify_fork(
      boost::asio::execution_context::fork_event fork_ev);

  // Construct a new signal_set implementation.
  BOOST_ASIO_DECL void construct(implementation_type& impl);

  // Destroy a signal_set implementation.
  BOOST_ASIO_DECL void destroy(implementation_type& impl);

  // Add a signal to a signal_set.
  BOOST_ASIO_DECL boost::system::error_code add(implementation_type& impl,
      int signal_number, boost::system::error_code& ec);

  // Remove a signal to a signal_set.
  BOOST_ASIO_DECL boost::system::error_code remove(implementation_type& impl,
      int signal_number, boost::system::error_code& ec);

  // Remove all signals from a signal_set.
  BOOST_ASIO_DECL boost::system::error_code clear(implementation_type& impl,
      boost::system::error_code& ec);

  // Cancel all operations associated with the signal set.
  BOOST_ASIO_DECL boost::system::error_code cancel(implementation_type& impl,
      boost::system::error_code& ec);

  // Start an asynchronous operation to wait for a signal to be delivered.
  template <typename Handler, typename IoExecutor>
  void async_wait(implementation_type& impl,
      Handler& handler, const IoExecutor& io_ex)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef signal_handler<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((scheduler_.context(),
          *p.p, "signal_set", &impl, 0, "async_wait"));

    start_wait_op(impl, p.p);
    p.v = p.p = 0;
  }

  // Deliver notification that a particular signal occurred.
  BOOST_ASIO_DECL static void deliver_signal(int signal_number);

private:
  // Helper function to add a service to the global signal state.
  BOOST_ASIO_DECL static void add_service(signal_set_service* service);

  // Helper function to remove a service from the global signal state.
  BOOST_ASIO_DECL static void remove_service(signal_set_service* service);

  // Helper function to create the pipe descriptors.
  BOOST_ASIO_DECL static void open_descriptors();

  // Helper function to close the pipe descriptors.
  BOOST_ASIO_DECL static void close_descriptors();

  // Helper function to start a wait operation.
  BOOST_ASIO_DECL void start_wait_op(implementation_type& impl, signal_op* op);

  // The scheduler used for dispatching handlers.
#if defined(BOOST_ASIO_HAS_IOCP)
  typedef class win_iocp_io_context scheduler_impl;
#else
  typedef class scheduler scheduler_impl;
#endif
  scheduler_impl& scheduler_;

#if !defined(BOOST_ASIO_WINDOWS) \
  && !defined(BOOST_ASIO_WINDOWS_RUNTIME) \
  && !defined(__CYGWIN__)
  // The type used for registering for pipe reactor notifications.
  class pipe_read_op;

  // The reactor used for waiting for pipe readiness.
  reactor& reactor_;

  // The per-descriptor reactor data used for the pipe.
  reactor::per_descriptor_data reactor_data_;
#endif // !defined(BOOST_ASIO_WINDOWS)
       //   && !defined(BOOST_ASIO_WINDOWS_RUNTIME)
       //   && !defined(__CYGWIN__)

  // A mapping from signal number to the registered signal sets.
  registration* registrations_[max_signal_number];

  // Pointers to adjacent services in linked list.
  signal_set_service* next_;
  signal_set_service* prev_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/signal_set_service.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_DETAIL_SIGNAL_SET_SERVICE_HPP

/* signal_set_service.hpp
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
*/