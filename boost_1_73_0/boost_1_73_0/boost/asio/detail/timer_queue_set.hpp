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
kGb0Sb3RiRc+bBGjD1ZNp1OlrjuuTbuFbeLHlB0oeQo5FqxIh0W/YpdijlnRzZKRZLXSriFrHB8MVOt7HBpHCTaHcBtjLd0z9ZEb0pFMKwZb2nBg6oJfmwYXvrgNoZWErpS67JLxLpJkw7UJ1OmgV5w4RFr1MUngmHswhyARFqW4oRipY6Iii3OC3T2yL03i2OmaJ0hqvZuQD9mYv/faRopm4Sq6AObkcxXkEDZSrZ0qB9rareRfmDW7XardAErnaen7lM+NM8loS43v73HV6Ljk3JcCHtFPBmcUInUMNdRLFFznZpH2GMShFx9iRR8zoEOVysQjQKQCoMK5t40f0uZkAH+I6fz/J1b3nDbM7ihDHoYBIfajwKCGGvZHgkPSBqM7AE3PkCAmHeCbC5tJxtfjyVNXtZsru9r6OHQBeL/3HpEq+lp+DkiW0xKj9db6jcHIONa6Y4z8e48wgjT61WttrIbTjO7wmeA5kkeSh5NHyM3d3a0rmtO9rh+iBWKqC1xzI3G125IX9Mhykj4BN4jiAzf7QbQmoAFA2q+AaQttDaQolIxK0+nJ6QHjUntgOPkSIRvudJMgxlSmrrM+ILaKLh3ItwnAVuX5ltF0qKhbbqOpQbVjBRzRsjqofqcNYbbIfjod7JDrdHoq
*/