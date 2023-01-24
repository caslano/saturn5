//
// deadline_timer.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DEADLINE_TIMER_HPP
#define BOOST_ASIO_DEADLINE_TIMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_BOOST_DATE_TIME) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/socket_types.hpp> // Must come before posix_time.
#include <boost/asio/basic_deadline_timer.hpp>

#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace boost {
namespace asio {

/// Typedef for the typical usage of timer. Uses a UTC clock.
typedef basic_deadline_timer<boost::posix_time::ptime> deadline_timer;

} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
       // || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_DEADLINE_TIMER_HPP

/* deadline_timer.hpp
arCK/TI/n3GJwoZjeyqwPSeOxYbbg2jcU58kWOZh/EbNMH6jTqcmDsfjFpo/p4g/8Qmsuvq00kgU8MA9aRY9wMWKFWupxbXQUTcHBmzsXRGBGUeZERgDP8EHFuROw/nEQkOgqFBUQIce2Da0WYSy1wH8x+ideUuB7o3Uiwb80fzMj+iyuiwiqPl136bJs+MlXTzwaPOxDQeDsWwXmfpZK8qNVDPpwF3Dk465LCmZskK1qBU9iDRgDzeMSMi6YrQ5lAVC1Tn+xiKMUpruJUypFg9ZUNh2nuCrYjG0LHAEJiIfAlwZb3TSsdtMHY8EvXPgyxBJNjHv/mS8IU5pimB5uKLrFzEExZg1F1lX9VohXv473gom4ZNZHyHFmErfh1jSwDtI+Kz1GSWw+R+Hr79GfpqNZ++x/UGJdbKD8e+blPKbylUX90MHpqiIqocqZKzVBbUW+0rfxWxozQrcBBZDqsk5rg41ht9rRR6gzATpbHUeKplzksJJDGTlz07chWsPFnV2GstogsnegCydt/5GHW2cYaa+IjZ+NHkkYMCCR/5Cpy+ybt7aPwSjXrMCLYCTYjHexjyLh3S67lmDWaMis46DB3kia3yeixLWfmzmZu7eHPQkgtY8qpCmAjk1Uhb/gBir8WyB1NBMOOvqCPgeqJltUaeyMY3H1D9zZJFh8Y0JvHOCeIQYf9RKESPN2ZJd0SYss35SCcvgGTwe
*/