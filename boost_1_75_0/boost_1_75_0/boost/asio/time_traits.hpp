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
uRbc5ppYbjVhwHu2r7d5e0Ru2m6+Zy7eAGHKTSvhTe5fw4DWfsxNjUFaC0NaE6CxXLO7a+xt+Dcc6gqRSHKHzgHRndQQ3XRKdBVLGdFtrtYB0Q050CJT17+R6MbfwYguWn2N2hF8wrUgG4EY7ppI/17hGkv/Ugr8OlWlwLcoBT6Eb395L4QCMVfEZExpaHavYzSY7wqzkaKngzS4RKbB6Hdp2BpS0JYONOg1zLORo49eQIT59nNaImw6HyTCXhclwj1LQ4jw3GNs3Jcmwmj8YggRri1AImSalSOP4/QcPWWR3OQg6yPPyWpj2MJSB/6PzC5grhNXFA1+IW98jad8TLLzwKS83k5fM89Bjo8LLdx/NFhID8kIPcgbbylKS07D7rVhHHNlCTFEUgsW+uqB4mDYq2KIoL5d5PvJHdCt6esubz/02/T1U3Xro4oiimbqvHPCvMvDZgm/LGKODuXjfz3RKcCfnLgIwNwbdGaZoYphQGi+YXDXXJNTOsVHl0WMzmyudh/mmo9J+W2iYLG7OOccG3lxawuenHe3dFseXlDi9OkLSpKKYjI9h1ccX2oArH4NwwHTeOb89ZHrY4oiZhaZp6e1Lz2t7i1Lc2OTi92tUYI51WpaG7U6PNVqXKYHI1TKonmfEbb7KJ3IPpp8SxSCJkQBKUSAHRrlC8cRWACZDhtzr8hbEVhViEaek8+yeCbTGzPkTlOYP0Se
*/