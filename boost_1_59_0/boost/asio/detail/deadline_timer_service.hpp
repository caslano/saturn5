//
// detail/deadline_timer_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/associated_cancellation_slot.hpp>
#include <boost/asio/cancellation_type.hpp>
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

  // Move-construct a new timer implementation.
  void move_construct(implementation_type& impl,
      implementation_type& other_impl)
  {
    scheduler_.move_timer(timer_queue_, impl.timer_data, other_impl.timer_data);

    impl.expiry = other_impl.expiry;
    other_impl.expiry = time_type();

    impl.might_have_pending_waits = other_impl.might_have_pending_waits;
    other_impl.might_have_pending_waits = false;
  }

  // Move-assign from another timer implementation.
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

  // Move-construct a new timer implementation.
  void converting_move_construct(implementation_type& impl,
      deadline_timer_service&, implementation_type& other_impl)
  {
    move_construct(impl, other_impl);
  }

  // Move-assign from another timer implementation.
  void converting_move_assign(implementation_type& impl,
      deadline_timer_service& other_service,
      implementation_type& other_impl)
  {
    move_assign(impl, other_service, other_impl);
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
    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef wait_handler<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<op_cancellation>(this, &impl.timer_data);
    }

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

  // Helper class used to implement per-operation cancellation.
  class op_cancellation
  {
  public:
    op_cancellation(deadline_timer_service* s,
        typename timer_queue<Time_Traits>::per_timer_data* p)
      : service_(s),
        timer_data_(p)
    {
    }

    void operator()(cancellation_type_t type)
    {
      if (!!(type &
            (cancellation_type::terminal
              | cancellation_type::partial
              | cancellation_type::total)))
      {
        service_->scheduler_.cancel_timer_by_key(
            service_->timer_queue_, timer_data_, this);
      }
    }

  private:
    deadline_timer_service* service_;
    typename timer_queue<Time_Traits>::per_timer_data* timer_data_;
  };

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