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
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
*/