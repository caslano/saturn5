//
// detail/strand_executor_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STRAND_EXECUTOR_SERVICE_HPP
#define BOOST_ASIO_DETAIL_STRAND_EXECUTOR_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/atomic_count.hpp>
#include <boost/asio/detail/executor_op.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/mutex.hpp>
#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/detail/scheduler_operation.hpp>
#include <boost/asio/detail/scoped_ptr.hpp>
#include <boost/asio/execution_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Default service implementation for a strand.
class strand_executor_service
  : public execution_context_service_base<strand_executor_service>
{
public:
  // The underlying implementation of a strand.
  class strand_impl
  {
  public:
    BOOST_ASIO_DECL ~strand_impl();

  private:
    friend class strand_executor_service;

    // Mutex to protect access to internal data.
    mutex* mutex_;

    // Indicates whether the strand is currently "locked" by a handler. This
    // means that there is a handler upcall in progress, or that the strand
    // itself has been scheduled in order to invoke some pending handlers.
    bool locked_;

    // Indicates that the strand has been shut down and will accept no further
    // handlers.
    bool shutdown_;

    // The handlers that are waiting on the strand but should not be run until
    // after the next time the strand is scheduled. This queue must only be
    // modified while the mutex is locked.
    op_queue<scheduler_operation> waiting_queue_;

    // The handlers that are ready to be run. Logically speaking, these are the
    // handlers that hold the strand's lock. The ready queue is only modified
    // from within the strand and so may be accessed without locking the mutex.
    op_queue<scheduler_operation> ready_queue_;

    // Pointers to adjacent handle implementations in linked list.
    strand_impl* next_;
    strand_impl* prev_;

    // The strand service in where the implementation is held.
    strand_executor_service* service_;
  };

  typedef shared_ptr<strand_impl> implementation_type;

  // Construct a new strand service for the specified context.
  BOOST_ASIO_DECL explicit strand_executor_service(execution_context& context);

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void shutdown();

  // Create a new strand_executor implementation.
  BOOST_ASIO_DECL implementation_type create_implementation();

  // Request invocation of the given function.
  template <typename Executor, typename Function, typename Allocator>
  static void dispatch(const implementation_type& impl, Executor& ex,
      BOOST_ASIO_MOVE_ARG(Function) function, const Allocator& a);

  // Request invocation of the given function and return immediately.
  template <typename Executor, typename Function, typename Allocator>
  static void post(const implementation_type& impl, Executor& ex,
      BOOST_ASIO_MOVE_ARG(Function) function, const Allocator& a);

  // Request invocation of the given function and return immediately.
  template <typename Executor, typename Function, typename Allocator>
  static void defer(const implementation_type& impl, Executor& ex,
      BOOST_ASIO_MOVE_ARG(Function) function, const Allocator& a);

  // Determine whether the strand is running in the current thread.
  BOOST_ASIO_DECL static bool running_in_this_thread(
      const implementation_type& impl);

private:
  friend class strand_impl;
  template <typename Executor> class invoker;

  // Adds a function to the strand. Returns true if it acquires the lock.
  BOOST_ASIO_DECL static bool enqueue(const implementation_type& impl,
      scheduler_operation* op);

  // Mutex to protect access to the service-wide state.
  mutex mutex_;

  // Number of mutexes shared between all strand objects.
  enum { num_mutexes = 193 };

  // Pool of mutexes.
  scoped_ptr<mutex> mutexes_[num_mutexes];

  // Extra value used when hashing to prevent recycled memory locations from
  // getting the same mutex.
  std::size_t salt_;

  // The head of a linked list of all implementations.
  strand_impl* impl_list_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/detail/impl/strand_executor_service.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/strand_executor_service.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_DETAIL_STRAND_EXECUTOR_SERVICE_HPP

/* strand_executor_service.hpp
2dbcg6OeUrJvcA34zTV7YqWebHb4OabvuWu7bidmr/97tP9MT6r22+LgegdHve6ReHx79hPO215+p8KRcmpIGzHlpdv1vC463AzWaDRzFBrJPg0L4rge4k2KXjAo8ay4qKSEJP6LqRXSr8ra1e/tkL0qHPrVU+CH+nwzbY8/iT6jniU2+LIGsrLLf1IVPK4abmyy331cmxKGA+BQnJyX8M7H5sm41xgZpHPbNyKD8+wboe38k54xdv66j1nNOaoxYK/2RznGfcsxc9/q41s4zr3CcbnvRH6HOS5NXI77x16kndn6NeqF47peuK4LarbTbYk97mp5/R23B/pf3GH8Ac+gPNkj/l6xr54DFxB32uO6v5vedkr5zyBkzXyrQvc5LCLXUvtH4R+i/ROjlHxenJnLIv2OT76bTru7vlpTbnq/k+VwpJaZEOWXkTKU9tofck72Tjf1Ya59wFbC45P7NWTuiwo2SsvE6vu0Dv4sneafPX/nydbUk44cx9W994ReJz1k/3e9f48OM4T7DT9/zdD++lHV2JUv3pPMyuhr5dmtwskzTJ4jd+v0a3n6WVvl+exLq5+sUy99Ub7/XsvU8ceZ+32i9qdH+efvjM+ZZHtWzdPnt3t6cI1bWAE20ZMu55yvNcXkMX/GeO8j0eyjv1nLf8ho2DTKjGMmv72iOnGUOGzXnT9xPBH55iFt13JvWZdI2CEm/Z5RPTlKWN3/HK7C8yXBN0+oG3vds5r6S2XsYS9hvkvwrfM+MnSekMicmijxxheuEZmQeLonSjwJhZvd4pmATHYKMjXm5QSvBX8h/ur4czn/T46N5x3238LvkqkvaF/r/W+4F6XPmtTa229llDMn6bYnpK/KmaD9l+G3z1EqdHmXWuSw/nsRzIszc5RUeH3/dXfoz/rLcaf+jPvQ1i8GzRl02Xu/eGfF5zQW7zxxcxp98/+OVnPee790Z+X23i/dWf7e+6U7K79XSkX33t9b3XnOprWr4nM2CVPWnE3O/7xzNiN7fp/cuXC99Fh9WsJp60oT3/7bpiP/+eGanl/1rfjaRhXVNfwW9/yWeWX63TsPuXfC3P9b9riW8Q09RkL4wD2uD8me1O/AKPgurAbfg3Xh+7AB/MCsTyTf+eALh/WJesja8j1hJ5n71RX2hoNhXzga9oOTYX9YKHPFbocD4QNwENwGB8ODMF3SL46Sb0n5Zlfpj+TvbTK2MkLm3I2COGs0vBxeAq+XOW3b4eXwWXgFfBNmwo/gONlzegKMlr3Iq8JJsC6cAk+FU2FrmA27wlzYE14FJ8Pp8EpYAHPhDDgTXg2vgzPhIngNvBXOhnfBOXA9vB7ug3NhCbwR/hsugj/Bm2Eseb4FngqXwNPgfXAIvB2Og0vhbHg3vB4ug/fAe+F9cCV8DK6Cr8DV8CB8EH4I18Cj8GHYMJrxHNgUPgdbwmLYGe6B3eF6OBFuglfCHXAafBougs+o/MKdKn24C66Gj8Gn4Wa4Cz4OP4dPwNNiqF94FnwStoB7YT/4PMyCL8Dp4r9a/HfD/XAFfBE+CF+Cu+EB+AJ8Bb4BS+EH8CP4JfwE/hX+CcbQzt6AVeBb8DR4CJ4O34O94AfwBngYLoRfwtvhX+BS+Dm8F/5N2nGe+d6hLmTP/XNUu4Pq97VKBx6DZ8B/yxzS/8Ce4u8j/pHwezgO/iD3UxQP8AUwDi6DVeBqmAQ3w2rwPVgTfg5T4FewFjwKa0OO6fibwIb428IzYC/YGA6ETeBoeCb8HYyHU2ECnAbPhjNgc3gtPAcuhq3hMnguXAvPg5thO7gL/qjaH/wvrKvubY7Xh41gZ9gB9oEd4XDYCU6AXVT6sCvMgd3gHNgDmrk=
*/