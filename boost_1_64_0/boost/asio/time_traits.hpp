//
// time_traits.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_TIME_TRAITS_HPP
#define BOOST_ASIO_TIME_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/socket_types.hpp> // Must come before posix_time.

#if defined(BOOST_ASIO_HAS_BOOST_DATE_TIME) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Time traits suitable for use with the deadline timer.
template <typename Time>
struct time_traits;

/// Time traits specialised for posix_time.
template <>
struct time_traits<boost::posix_time::ptime>
{
  /// The time type.
  typedef boost::posix_time::ptime time_type;

  /// The duration type.
  typedef boost::posix_time::time_duration duration_type;

  /// Get the current time.
  static time_type now()
  {
#if defined(BOOST_DATE_TIME_HAS_HIGH_PRECISION_CLOCK)
    return boost::posix_time::microsec_clock::universal_time();
#else // defined(BOOST_DATE_TIME_HAS_HIGH_PRECISION_CLOCK)
    return boost::posix_time::second_clock::universal_time();
#endif // defined(BOOST_DATE_TIME_HAS_HIGH_PRECISION_CLOCK)
  }

  /// Add a duration to a time.
  static time_type add(const time_type& t, const duration_type& d)
  {
    return t + d;
  }

  /// Subtract one time from another.
  static duration_type subtract(const time_type& t1, const time_type& t2)
  {
    return t1 - t2;
  }

  /// Test whether one time is less than another.
  static bool less_than(const time_type& t1, const time_type& t2)
  {
    return t1 < t2;
  }

  /// Convert to POSIX duration type.
  static boost::posix_time::time_duration to_posix_duration(
      const duration_type& d)
  {
    return d;
  }
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
       // || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_TIME_TRAITS_HPP

/* time_traits.hpp
eJGWAN2Zpwp1VzIiWWANBQHW8kxRYLcp4Z4102VWCMqZIqXvSjjdWoksYLTymZLwEeCRENgBhaI22jmpchz+vL+n/aWlBq3YN30Gug5/d72PFd2x8A4+gmv9JXWkpz1tUMa7vkP4CpRCESKRu/SOcB1fj6ANWQaAaG8If7JI5fmx7wkH3CJPE0t1Ibt/8vit5Te087BV9KGu8XL9pB/+0L0rQaZQsjaCQzc6o6TCVpyOzWnH4ZC1cmcECuBqwO7unmQSvxQZOpsToOpldgZ/VP2EtS6opB4JWAOS/rAQwOAn/JjUZJOm9Xjki1gEk8Gbalsr4x03rdrXVhMmDeki4GUaR6JCRnjGYZu0PuArq4VTZlcFKW3fAT+mJ+QWkMhmHC1loTfYH7EfYEd2LJ7R9M4dh1aq70LltMrpwJL7NTLsXC4BvW068u+O/PBb/pWwGJZZOKxVPxuW3/Rse2J5wqxtudjQg3wkXeNsCyGxG/rkDCS+PAEzS6+sdoPQS3nnJgGGhYvVTZknpj4r6pb/WHCWcxbZK5Lb06P/gk1ZweXOlPO35bLM7sheYw==
*/