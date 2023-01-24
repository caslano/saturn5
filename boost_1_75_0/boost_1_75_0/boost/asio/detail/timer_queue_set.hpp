//
// detail/timer_queue_set.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_TIMER_QUEUE_SET_HPP
#define BOOST_ASIO_DETAIL_TIMER_QUEUE_SET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/timer_queue_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class timer_queue_set
{
public:
  // Constructor.
  BOOST_ASIO_DECL timer_queue_set();

  // Add a timer queue to the set.
  BOOST_ASIO_DECL void insert(timer_queue_base* q);

  // Remove a timer queue from the set.
  BOOST_ASIO_DECL void erase(timer_queue_base* q);

  // Determine whether all queues are empty.
  BOOST_ASIO_DECL bool all_empty() const;

  // Get the wait duration in milliseconds.
  BOOST_ASIO_DECL long wait_duration_msec(long max_duration) const;

  // Get the wait duration in microseconds.
  BOOST_ASIO_DECL long wait_duration_usec(long max_duration) const;

  // Dequeue all ready timers.
  BOOST_ASIO_DECL void get_ready_timers(op_queue<operation>& ops);

  // Dequeue all timers.
  BOOST_ASIO_DECL void get_all_timers(op_queue<operation>& ops);

private:
  timer_queue_base* first_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/timer_queue_set.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_DETAIL_TIMER_QUEUE_SET_HPP

/* timer_queue_set.hpp
KW9RwXJLsjDUa8wl5aeoYJmVDGQZQ1PRK5nl9cklVRyzfYw6B8TkQvd2W4ZqO/1mkIVOMpK7epDt6feOzxmAkXspPcyFNvJqO9ZSfJTQVhbB/2u7YWwlPB+k+EFcFql9vpqWy1KUURxjH5TSvLcwbKDSyA1iW1ybJrZNPkjFtmno72f916iutJPbm7E9gDC8+NviJi8N6VLkA9iug3yMeGkgf4N4aQRv9WXuYcs4QAczMx5wkMmP12pAf/mJpgG1l5DBMXYy72OAwIjHiKjbHjLjLnasm94rSx2PbUPhuDg9jf9FCUhMW3Pd7KqEh94IMhTzsWJwIB8hBkcIMaz6Jw4oSrrQws9EY6AWUvcJs3eraudv9Sq5aBKUdjqXpOoFJOkFRFGBPfAOXobiJjP8uIz/7ng7OmbzkJcTmOs4KOdGN/nX8A4FlxJ7PEHFw2Ru8qIHi0xwk2jISfZ/Q1cRFz5DR9Fu8oaaYSskgkVzG81RSnMkdVOp+eTyZg+JS+jpZ6enffYpwJ/XWuIaAmi0HKeK5EXHuymSl6GPll4VyTce1xXJ9xxv/2H/pplDetPbDb4/dGT4/906X/VDdhoW+Fa2wB+QXmDnB8h5CbAOgGVhK67AMejf6QWxbIEfFTiHP2cgTdVxDEqEoGP4cyS9IAkDkiGgBn/eomv74vRhfKRYb5wl/KdYhOV9Il3el9tNpc+pa/sxaC2Zl0CX
*/