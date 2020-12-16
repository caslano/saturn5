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
4GSlg2mfrQ7df4icPd9f6TBD/ZvvwoEwP0HjlvCnsCTBSefz4AY4F94Py+DDcB78A5wP34ULofF8kfrNRt8DLoEjIP7Y9sNiuD+Z8NKB24p6F9WGTlwuqhq1EbUHNZPn48oTAgNvhUO43QS1DrUFtZ/nu2F/On1JJ2H3VliREOiCykV15FkeZnN4XgVX8WwDahu/d6F2VuAmMqWoA+hXwvWogzzfDjN6Ei6YBdNPhkZ9JyEwBFWE6s/zHJ6t5Pda1HR+b4KjeV6KWniryTzMURtQSzHfbWThFvQZJN4OuB39AVR/9ONQpagVxgz1LmrgKcQDdcC4CdtUEk86tMv53QUORz8FLkCt59nWUyDPlqHfCQ+i9vJsHfqkHPyt4sRe1Cb021A9eLYH5lQhC2fCpr1xl+ddYBGs5tlyOAX9OlgEq1AbeL4F/S7UBvTbUAer0MMVxD9jPm6gPkefY4jcTNhmKCobO/wewu8pqB3zCTd2tqD287sH5gt4nnkBa69QQ9BPR03hdyncZdIXrkS/HLkNqLXod8ItMHMYv2EO3IfsjgsgKuk20tWYX0g8MFuKyr4Qu3Abqqkxh59n85zfczBL74OcIR391bAL+i1wCixCLUQtR61H7eP5VtgD2Z1wNG7shTnoi1AH+J3UF39QC9F3hD0WECfUUtQQ9Ct5vg61Hn0e+r1wJu5U8Xsbzw+ifxd2uYg0Ho49nveHeagq1GpD5B+GazBbzu8NcCtqN88OoDJGII/9nTzrwu9cVKBfQqACrkRtRDVFvxCZjnAIas1tyPP8XdRMY4ZajlqP2obcFth0JOHl90ZkMy/GHqoHz6bA0XAHMntQB1Cp/cljnpfyfDlqA2o7KpPn78IhcByqFBUYhf/IruD3FtgG/Xb82MfvgfxOv4Rwombyuxo1+hLkYSl8GDu7UPtQG3m2gWcH+b0N7kb/LsxYSLhu4zn67IXoB/C+o7JRo9HnwAp4AJmmo0kjfs80z1Dp63if0A/h+W44HVahqo3ZImT5vQG1Av1w9FnIj0bNQS1HbUTtQgVuxww1HDUHtQy1HrUd9S4q9Q7yCjUaNQe1DLURtR21D5V0J2mAGoLKQy1ArURtQG1H7UOlrscP1HBUEaoatQq1EbUdtReV9EvyDJWHqkatQW1DvYvK+BVlDTUdVY1ah9qOOojKuov8QhWhqlGrUBtQ21H7UEf/jv4d/fv/+kuyYzFBux58+KDp5RWcMlc+f15hsfOzsrTnrPks0u3Zp1efXtmze15Q2Te7zwmu2YLj+/esnMNOxKKe8zgLicN9QxKF8y6qqCqfbi7WuKDf9Av65VeVVs7uVT7LjAsNCgxpxCCpvU+Bs30KAi5PLymcV15ZPrsqq8ukrlnmgsm5JRdzx03WqWx4LCllx0t77qDc0pSx3xEpAb5a4ybnjxwxdMrUSSPyS6qK5+ZXVQWceyr/PoSxSgZIEgN4nD+7uKBq/rzi/KpZpZinBMY1eql3QGeE2PnjmPttv8B+VtCug/d4YvfF2PXVac0j9qZJtq27J+b8RjXviQnd7YlbMWepoYm5x3MTAcuIDVMJca5xf1Zz0mQb9nfZdLOXgGIx8qyUOQmx6fAl6ZAb46fd5erGtawWcY04yzbJMdiKyhTN4rqZXzSzZxz1vSDf45ez7+Az/zP2ZKe1e4ZT81DeePNd8mNd+XbunoBLrf7WwJVa79/K2i1ewNps9/7MXNdep4iz/HRWi3uGTrWVWRtYglT4nO/z3HNmH7DmZ1GGe0ecx+I9l+sOK5PinhW0weqrWDPXLHxPrX1Wz4a3sfWDuBLkkqLwWTD3WZm5rCfsYu+zLTVrdUn3nebe4cTM9ORU5xo=
*/