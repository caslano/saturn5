//
// detail/timer_queue_ptime.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_TIMER_QUEUE_PTIME_HPP
#define BOOST_ASIO_DETAIL_TIMER_QUEUE_PTIME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)

#include <boost/asio/time_traits.hpp>
#include <boost/asio/detail/timer_queue.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

struct forwarding_posix_time_traits : time_traits<boost::posix_time::ptime> {};

// Template specialisation for the commonly used instantation.
template <>
class timer_queue<time_traits<boost::posix_time::ptime> >
  : public timer_queue_base
{
public:
  // The time type.
  typedef boost::posix_time::ptime time_type;

  // The duration type.
  typedef boost::posix_time::time_duration duration_type;

  // Per-timer data.
  typedef timer_queue<forwarding_posix_time_traits>::per_timer_data
    per_timer_data;

  // Constructor.
  BOOST_ASIO_DECL timer_queue();

  // Destructor.
  BOOST_ASIO_DECL virtual ~timer_queue();

  // Add a new timer to the queue. Returns true if this is the timer that is
  // earliest in the queue, in which case the reactor's event demultiplexing
  // function call may need to be interrupted and restarted.
  BOOST_ASIO_DECL bool enqueue_timer(const time_type& time,
      per_timer_data& timer, wait_op* op);

  // Whether there are no timers in the queue.
  BOOST_ASIO_DECL virtual bool empty() const;

  // Get the time for the timer that is earliest in the queue.
  BOOST_ASIO_DECL virtual long wait_duration_msec(long max_duration) const;

  // Get the time for the timer that is earliest in the queue.
  BOOST_ASIO_DECL virtual long wait_duration_usec(long max_duration) const;

  // Dequeue all timers not later than the current time.
  BOOST_ASIO_DECL virtual void get_ready_timers(op_queue<operation>& ops);

  // Dequeue all timers.
  BOOST_ASIO_DECL virtual void get_all_timers(op_queue<operation>& ops);

  // Cancel and dequeue operations for the given timer.
  BOOST_ASIO_DECL std::size_t cancel_timer(
      per_timer_data& timer, op_queue<operation>& ops,
      std::size_t max_cancelled = (std::numeric_limits<std::size_t>::max)());

  // Cancel and dequeue operations for the given timer and key.
  BOOST_ASIO_DECL void cancel_timer_by_key(per_timer_data* timer,
      op_queue<operation>& ops, void* cancellation_key);

  // Move operations from one timer to another, empty timer.
  BOOST_ASIO_DECL void move_timer(per_timer_data& target,
      per_timer_data& source);

private:
  timer_queue<forwarding_posix_time_traits> impl_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/timer_queue_ptime.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)

#endif // BOOST_ASIO_DETAIL_TIMER_QUEUE_PTIME_HPP

/* timer_queue_ptime.hpp
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
*/