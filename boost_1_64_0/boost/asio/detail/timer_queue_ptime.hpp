//
// detail/timer_queue_ptime.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
XgQF49LoCxl9+0c0323oh3c2MW/u1OcKrLaczZTnRUi8GXlPv6L5htGKbXVcmTLm2eZMrt+6q7gyWY64Ml2Ep6BtIK7MeOw60hOHeL2zhb+qrcSBaTvNGZNQeBbB84eqN7HmlPSUlOBzLOxay+H7XfGl19wffIbLtUgniV8nYsRofF2+73Ij+OYqCn/3yxye6OLDqSQkDkxcX+/foK/XeSd1fu+Dfzv1t4wFBft1e2+/PwasWB3X12uJvp7EWtLPgsZWJq6L+V89R1bSL5uQ/sP2/++2//n2N/+vsv1vdELmRacTkntsdDp3DVFeb22UfF1rIvOVW/L7CrzSRRdtsOhY7Qr2kXSOpHNFx28vcHdQlckFD5P8Y8BhYA043K6LJO3KglaGtYv+NXxVUfLVRslXHyVfY5R8a218zCvvGBvHR+a725J3t3xvMA6a5wbhGwmfKj8W3Frxgnng3uBwsAwcDxaD08AJ4CxwH3AuOEnGYT/wFLAUPE3SZ0v6Qil/DTgFvFWuez+4P/iE6E5+Ah4kMVx84E9J0ek0pX/EXj8vop7r4rpMG1KX6e/26/V/0GX6u/SY4n6+1o8uU/E6+gmqg1ZCa6HOv3FtqBw6A7odWg2tgzb/nbzf43pJ8SN+xI/4ET/+2mPD7f+ziLwe/P91YT97I+WP4nL2p6wpMyt8M6m2csYs2e//va9l/NR0l9dotfj6mAo9sim2I3ND/e3nF04Yg4VvMcuuxXnDCvIjxCGX8llmPfJOnZ5k7Sz+P/I66H1H4//jHp2/N7/Jxf+Hucam/jVr2kTrcJAT9Fn/qM7fkd957Tmn96458J9uW1PtAD6k+cbDs1+HRNLLMvwOqG6Pwi+I7N85/LiLfxBq0Pt9cX/tf8PaXaFeu/tlh6oLXv0s5cmhJ9XdMr9t3mNea3Hrz3/5v8Xvu/vaXfPXAOkKtAXkfgSrxY95GlhmszPcFOwHbgXmgJBeYxsg6d3BAWA+OBAcK+licAdwqpyvlHR9YG2DtYukxMSIaxzqt3bXxMRmrW/E1zZiX9v4O9c1/o1rGutzPaM5/sqHJiZGXMuIr2O0fB1jIv0cP+JH/Igf8eO/c2yw3//8VC9bT7//X1e+GLdQ+uz+3/6+aRWlB8/y++yfswl6DzpvxKjxxb6isaMKi/1eTktnz7GC8QFysl14xP1/NjyT4akL55EIAtuKDULOlip/+LgCX5DnT/auBDCq4gy/zWXIIUmAEAKEhXAkBEK4w9Ea5DAcwgJBQdFsJIFEQhKToIBoN4gVFSUKWkTQtHIKCioqCmhUrChoQ0WlFmvaoohHiy0qVmz7zb//m337jt3Nhtorq8OXefPPzPvnfG/ezPd7rAMoJLcpBQ/7JDd++vQZsFWXb0iP1i3ez/TYEbCHmHDaD8P36AW0bqHLkDaI0rpDeAevfeGQD/6MAtIy8G+vtbAj0Fhsdl8oiCacT3B0sea1DzM5L3AcbaDevDywibjpZxPUvNab5PU75HXanZe+wciyX5aoO5fQjLJHWoaybxtmwYFaYnZfTSv7ihTrsneZnFP4EOVhLzPLt0llb+BDbRuuzwsuEToa8vKcy0nwLnfINqncJ2jLPcHEjsOKcAs7DsW6e2rieRylizX/7GmTcmhEmbv05dC0czgT9OdwdvFe+ZNsZ/P3cLcNw3VDPmCIzi+scDN4o7xke8c1z7oox0vw2Mck/1HoZVN2w70OJ+LW8zkdJMdc7RwXdzJY2UIy4UhfwV72gnmevakfkMw2+COUlZAy24saWi5kFmP/SDtK5y+kaRnu23NWI5lkOtB5jDMo6zSUw/0ZYh/mZOzqjAkdZLW3k+UnQf5nQj7Kadzbyfs=
*/