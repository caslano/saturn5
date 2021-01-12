//
// system_timer.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SYSTEM_TIMER_HPP
#define BOOST_ASIO_SYSTEM_TIMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/basic_waitable_timer.hpp>
#include <boost/asio/detail/chrono.hpp>

namespace boost {
namespace asio {

/// Typedef for a timer based on the system clock.
/**
 * This typedef uses the C++11 @c &lt;chrono&gt; standard library facility, if
 * available. Otherwise, it may use the Boost.Chrono library. To explicitly
 * utilise Boost.Chrono, use the basic_waitable_timer template directly:
 * @code
 * typedef basic_waitable_timer<boost::chrono::system_clock> timer;
 * @endcode
 */
typedef basic_waitable_timer<chrono::system_clock> system_timer;

} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_SYSTEM_TIMER_HPP

/* system_timer.hpp
6ZUSTDh2QdB4bGHIQkXlDvDJSyYfU3XeVJH7fWZDfeNB4RuQUSpYGiYQPuUDpwTr46bm62klB9AHvuub9oiT6StsrQ/6qFmaN2+7jBDS248sGFII22CQu9HHyi+g8cBkaX8CiaJt5m2G16tgx960MTL9Y/cvcfidiD/8IvZBGWWukDf9MwnrUC8b5CV1/h677MCpON0tX+dvsBtgFQGqhKz9/HSrXtiJh7ub8/fhwDCz3XbV
*/