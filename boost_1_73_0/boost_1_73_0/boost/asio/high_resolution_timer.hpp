//
// high_resolution_timer.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_HIGH_RESOLUTION_TIMER_HPP
#define BOOST_ASIO_HIGH_RESOLUTION_TIMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/basic_waitable_timer.hpp>
#include <boost/asio/detail/chrono.hpp>

namespace boost {
namespace asio {

/// Typedef for a timer based on the high resolution clock.
/**
 * This typedef uses the C++11 @c &lt;chrono&gt; standard library facility, if
 * available. Otherwise, it may use the Boost.Chrono library. To explicitly
 * utilise Boost.Chrono, use the basic_waitable_timer template directly:
 * @code
 * typedef basic_waitable_timer<boost::chrono::high_resolution_clock> timer;
 * @endcode
 */
typedef basic_waitable_timer<
    chrono::high_resolution_clock>
  high_resolution_timer;

} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_HIGH_RESOLUTION_TIMER_HPP

/* high_resolution_timer.hpp
fXiz0jCEsdNur8Q8SA8ETKBq0f+KMuJlgjhlbRSv4Y0mpZa2bgyZGkJIqTuI2fGJE5RcMkonAaUB+ocWmXk+CUSFi5oOq0o+kHSpGZNhyEU65YFKoUUQkmzDlbDJAkE9pm656ctP5fTUrSj3T592RLgPoeUpvYqU4dwTyYHazoJj14bQEf95aD14PFjl/7HOKr+DBPdagp6w+ipTJHxJx+XtLu3IyOD2PCP5lmTrATgkCelXpfYJuOo0Ajps4Y27UvocRJH++90zef//MJNnfFrSvpH6KdtEgCGEVY0I20LLa6GW9Isx2OQWgQyQaEywCgwx7Qrg/aKUhqxroOueTeIjJ3oxi4briBaM12C7eDUcHI9i4cieEzeu6MeHERgqEatW0sBCgBpH9Gn8pT4b8hnDqRk9f/vmzfnza5I/GxJ3iG4PlEZ0GTqfmsftAXoSdtpmWpeTm/rxiJvYzyeg7lfeS2dYqi9us6osWOe6TauMCBz18bxDlBiPmZm62bpiOsvLTUDnqzKnPl+DJN4nKyAlNR2S9YqP8WrlSUAFWtHuVktCw5ftaTE5K5nkGc1mn44odUEb0BC/UrJn2MvoVEyZOJC06VVqU0mx7XSwRV5FdlrT/oz6/yuABjI2MclyXTQmT+miBeOExDdE
*/