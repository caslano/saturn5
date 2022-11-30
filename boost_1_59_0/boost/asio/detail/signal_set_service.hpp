//
// detail/signal_set_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/associated_cancellation_slot.hpp>
#include <boost/asio/cancellation_type.hpp>
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
# if defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)
#  include <boost/asio/detail/io_uring_service.hpp>
# else // defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)
#  include <boost/asio/detail/reactor.hpp>
# endif // defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)
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

  // Cancel a specific operation associated with the signal set.
  BOOST_ASIO_DECL void cancel_ops_by_key(implementation_type& impl,
      void* cancellation_key);

  // Start an asynchronous operation to wait for a signal to be delivered.
  template <typename Handler, typename IoExecutor>
  void async_wait(implementation_type& impl,
      Handler& handler, const IoExecutor& io_ex)
  {
    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef signal_handler<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<signal_op_cancellation>(this, &impl);
    }

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

  // Helper class used to implement per-operation cancellation
  class signal_op_cancellation
  {
  public:
    signal_op_cancellation(signal_set_service* s, implementation_type* i)
      : service_(s),
        implementation_(i)
    {
    }

    void operator()(cancellation_type_t type)
    {
      if (!!(type &
            (cancellation_type::terminal
              | cancellation_type::partial
              | cancellation_type::total)))
      {
        service_->cancel_ops_by_key(*implementation_, this);
      }
    }

  private:
    signal_set_service* service_;
    implementation_type* implementation_;
  };

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
  // The type used for processing pipe readiness notifications.
  class pipe_read_op;

# if defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)
  // The io_uring service used for waiting for pipe readiness.
  io_uring_service& io_uring_service_;

  // The per I/O object data used for the pipe.
  io_uring_service::per_io_object_data io_object_data_;
# else // defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)
  // The reactor used for waiting for pipe readiness.
  reactor& reactor_;

  // The per-descriptor reactor data used for the pipe.
  reactor::per_descriptor_data reactor_data_;
# endif // defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)
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