//
// detail/deadline_timer_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_DEADLINE_TIMER_SERVICE_HPP
#define BOOST_ASIO_DETAIL_DEADLINE_TIMER_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/timer_queue.hpp>
#include <boost/asio/detail/timer_queue_ptime.hpp>
#include <boost/asio/detail/timer_scheduler.hpp>
#include <boost/asio/detail/wait_handler.hpp>
#include <boost/asio/detail/wait_op.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)
# include <chrono>
# include <thread>
#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Time_Traits>
class deadline_timer_service
  : public execution_context_service_base<deadline_timer_service<Time_Traits> >
{
public:
  // The time type.
  typedef typename Time_Traits::time_type time_type;

  // The duration type.
  typedef typename Time_Traits::duration_type duration_type;

  // The implementation type of the timer. This type is dependent on the
  // underlying implementation of the timer service.
  struct implementation_type
    : private boost::asio::detail::noncopyable
  {
    time_type expiry;
    bool might_have_pending_waits;
    typename timer_queue<Time_Traits>::per_timer_data timer_data;
  };

  // Constructor.
  deadline_timer_service(execution_context& context)
    : execution_context_service_base<
        deadline_timer_service<Time_Traits> >(context),
      scheduler_(boost::asio::use_service<timer_scheduler>(context))
  {
    scheduler_.init_task();
    scheduler_.add_timer_queue(timer_queue_);
  }

  // Destructor.
  ~deadline_timer_service()
  {
    scheduler_.remove_timer_queue(timer_queue_);
  }

  // Destroy all user-defined handler objects owned by the service.
  void shutdown()
  {
  }

  // Construct a new timer implementation.
  void construct(implementation_type& impl)
  {
    impl.expiry = time_type();
    impl.might_have_pending_waits = false;
  }

  // Destroy a timer implementation.
  void destroy(implementation_type& impl)
  {
    boost::system::error_code ec;
    cancel(impl, ec);
  }

  // Move-construct a new serial port implementation.
  void move_construct(implementation_type& impl,
      implementation_type& other_impl)
  {
    scheduler_.move_timer(timer_queue_, impl.timer_data, other_impl.timer_data);

    impl.expiry = other_impl.expiry;
    other_impl.expiry = time_type();

    impl.might_have_pending_waits = other_impl.might_have_pending_waits;
    other_impl.might_have_pending_waits = false;
  }

  // Move-assign from another serial port implementation.
  void move_assign(implementation_type& impl,
      deadline_timer_service& other_service,
      implementation_type& other_impl)
  {
    if (this != &other_service)
      if (impl.might_have_pending_waits)
        scheduler_.cancel_timer(timer_queue_, impl.timer_data);

    other_service.scheduler_.move_timer(other_service.timer_queue_,
        impl.timer_data, other_impl.timer_data);

    impl.expiry = other_impl.expiry;
    other_impl.expiry = time_type();

    impl.might_have_pending_waits = other_impl.might_have_pending_waits;
    other_impl.might_have_pending_waits = false;
  }

  // Cancel any asynchronous wait operations associated with the timer.
  std::size_t cancel(implementation_type& impl, boost::system::error_code& ec)
  {
    if (!impl.might_have_pending_waits)
    {
      ec = boost::system::error_code();
      return 0;
    }

    BOOST_ASIO_HANDLER_OPERATION((scheduler_.context(),
          "deadline_timer", &impl, 0, "cancel"));

    std::size_t count = scheduler_.cancel_timer(timer_queue_, impl.timer_data);
    impl.might_have_pending_waits = false;
    ec = boost::system::error_code();
    return count;
  }

  // Cancels one asynchronous wait operation associated with the timer.
  std::size_t cancel_one(implementation_type& impl,
      boost::system::error_code& ec)
  {
    if (!impl.might_have_pending_waits)
    {
      ec = boost::system::error_code();
      return 0;
    }

    BOOST_ASIO_HANDLER_OPERATION((scheduler_.context(),
          "deadline_timer", &impl, 0, "cancel_one"));

    std::size_t count = scheduler_.cancel_timer(
        timer_queue_, impl.timer_data, 1);
    if (count == 0)
      impl.might_have_pending_waits = false;
    ec = boost::system::error_code();
    return count;
  }

  // Get the expiry time for the timer as an absolute time.
  time_type expiry(const implementation_type& impl) const
  {
    return impl.expiry;
  }

  // Get the expiry time for the timer as an absolute time.
  time_type expires_at(const implementation_type& impl) const
  {
    return impl.expiry;
  }

  // Get the expiry time for the timer relative to now.
  duration_type expires_from_now(const implementation_type& impl) const
  {
    return Time_Traits::subtract(this->expiry(impl), Time_Traits::now());
  }

  // Set the expiry time for the timer as an absolute time.
  std::size_t expires_at(implementation_type& impl,
      const time_type& expiry_time, boost::system::error_code& ec)
  {
    std::size_t count = cancel(impl, ec);
    impl.expiry = expiry_time;
    ec = boost::system::error_code();
    return count;
  }

  // Set the expiry time for the timer relative to now.
  std::size_t expires_after(implementation_type& impl,
      const duration_type& expiry_time, boost::system::error_code& ec)
  {
    return expires_at(impl,
        Time_Traits::add(Time_Traits::now(), expiry_time), ec);
  }

  // Set the expiry time for the timer relative to now.
  std::size_t expires_from_now(implementation_type& impl,
      const duration_type& expiry_time, boost::system::error_code& ec)
  {
    return expires_at(impl,
        Time_Traits::add(Time_Traits::now(), expiry_time), ec);
  }

  // Perform a blocking wait on the timer.
  void wait(implementation_type& impl, boost::system::error_code& ec)
  {
    time_type now = Time_Traits::now();
    ec = boost::system::error_code();
    while (Time_Traits::less_than(now, impl.expiry) && !ec)
    {
      this->do_wait(Time_Traits::to_posix_duration(
            Time_Traits::subtract(impl.expiry, now)), ec);
      now = Time_Traits::now();
    }
  }

  // Start an asynchronous wait on the timer.
  template <typename Handler, typename IoExecutor>
  void async_wait(implementation_type& impl,
      Handler& handler, const IoExecutor& io_ex)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef wait_handler<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(handler, io_ex);

    impl.might_have_pending_waits = true;

    BOOST_ASIO_HANDLER_CREATION((scheduler_.context(),
          *p.p, "deadline_timer", &impl, 0, "async_wait"));

    scheduler_.schedule_timer(timer_queue_, impl.expiry, impl.timer_data, p.p);
    p.v = p.p = 0;
  }

private:
  // Helper function to wait given a duration type. The duration type should
  // either be of type boost::posix_time::time_duration, or implement the
  // required subset of its interface.
  template <typename Duration>
  void do_wait(const Duration& timeout, boost::system::error_code& ec)
  {
#if defined(BOOST_ASIO_WINDOWS_RUNTIME)
    std::this_thread::sleep_for(
        std::chrono::seconds(timeout.total_seconds())
        + std::chrono::microseconds(timeout.total_microseconds()));
    ec = boost::system::error_code();
#else // defined(BOOST_ASIO_WINDOWS_RUNTIME)
    ::timeval tv;
    tv.tv_sec = timeout.total_seconds();
    tv.tv_usec = timeout.total_microseconds() % 1000000;
    socket_ops::select(0, 0, 0, 0, &tv, ec);
#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)
  }

  // The queue of timers.
  timer_queue<Time_Traits> timer_queue_;

  // The object that schedules and executes timers. Usually a reactor.
  timer_scheduler& scheduler_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_DEADLINE_TIMER_SERVICE_HPP

/* deadline_timer_service.hpp
kwjgWBmnsMOKU7WKkWVmthqlwtiFE0EZMDqOpAm01UpBahNcE8Wf6NIdro3iJLW5OMckowF7JLrCWeM/CIil2Tiddgo7d/yJ3TepH38bcz5Qb001ZioIxqCmSmX80bYrB0VEclw7BmtZFEyujaPbM3XsJGO2e9uePLqnZ1EuvXhJHr1waW7uxT3doM2ICxBF6RQ1J0s9ixZsm+izAC3nSrZZsjQjWLi4Z0lSZPHCJfmSngWLOpRZuGCbnnwJGuxQ25LuRYvyJUu1FdNRhcvFww+XhgfFcwUIs2iq2MJciWEDfh6n6jGnBxFpPXwaYvWG28Fnc8k0c6oNkvtUmo0uJDc20QymehMA99n0RKoF09XJlk51IxndwYL6GC4AhCRMx0wSsa4aLk1pBNbJntB9M0Qu1jPIkiSm1CQmT7Z+XNPErdikWLReBynUvdGo24Jae02aHGJ/JmnMR81CryquCmHdBJsJ9mkIT9PtiUzSaCntLCJSPB6oOv6TCJP4iznWCgvB7wyMaWtgzFcDY6IaGDPUwJPtOkImiHq8IOMcEI++Tifa6AtwQ9FWP03gSBKmg0q73AijqgXxDy7rgkyEJmtZtJkOZVMPo97GJAj7x62psphtcdw2N1UAxvwLjHgU6AmcjCEGKv6TSNJIjztquFKefeBKs+mTMxFleQ42CKgJf7GKhH/jVjYVa+1KEgY2V1vTqeLh9A3n9drlhTUDa8J1IgVTzcZmA0QXtFMKVsqm43pg5mjK9PWOjWcv0oaEvkyrKaxpGuBSrSE1QcMpnV6l7dOXafsGRscHlw/2wXgjw6sH+wYHogvMeYJO+dGhrr41vX3pvQdcyM8QWI41Qt2VFIULVnyiw+l0SyrQVS6v1uGDYXIQJ6gotTbcfEdpXCNsz1SQHiv0YYixrx/EuQvtVBwS+jsUGrK5eApBn1AyEFmwUu7HeS0ZAFcCS3eQwOyIdLB7JEKUrDVmI1F8bAoFo5VSpTrbGo0udMaSBXki9C2vSGRNeDBAnhi9d9nEAKAxDlWYINV9VWVr9BQT5kjnLFGr1XImR2zHxFauBLbqIIlqm4WxQvu78o3FZjWpuIM4qqNYm5pXjurnlTea1Sl0a7488L2NQYcMSXltPDdLkPQ1L0NlI3LEtu0kn6f+FqQYvFZnubZTMG8G3LjENjZXi6gH6EAHEQJ7ECBo5xSdt/O4xBc5+Nh0sVkpJy7TKMcsNIrnTxUxQXPNuZxpty1edzdXMANTwiVsUaJlR2EAXGxhJXSkrvG0NIwJiRQKtxw5khYX3xDOZaFfFMBCKRa3BYU+1IrnzEuIItFD6kEqg7k3NSDA5mGuikispdCnlUHNmgbNZJwKsEkObY44ZN1WvNE8WtFItwKgqzMyJfZKcLT9xLlvBntX3OxNeZdoYXNTbJoSWGxmFqtHZJYyvClNhItOiuJ1B8CM2DoM6XQa6x1SW8aVpPmrUzr0Zxk98kbonEz0DJ3NnESB5rWzaDLxF01U4iVwPJ58WQfOlGtlxLmDCz4a3EBDjG6IcAxC11tFPGkT2SGA1Gk5OzmCTFWgrdLIkibgNaEuCYEQEXlNsdVq5pLxk4UdZXgUuqOstcVoCJeFK62K3ZR+FjOnOsjy8puauaJ5asKYtqMRhcfDh2a6kMTFy6yjA+bZBvQ81oF0HvtAOo+FIM23EQQdrORI88t01hLCzkq61kqml05qXxpeo6/EaYQ64ttRBhdPDjB6EwuQRprouZeIw/kZQSnLoILoZhfQiFXdPngzDKmh5dGdZ1zwz6BJxDOAREekULg7fQYWM30SexHcmtHS+P6Sxji/tbAcpER8PzTC1egBO30hyaWjpMujQy6L41Y=
*/