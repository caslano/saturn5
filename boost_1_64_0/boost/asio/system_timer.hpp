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
qvAalPyQgnQanTuEJ4xkhGldU4LyX8Iemm6JZAnPs0ioqvbgedR/gHoexmlsoEgKQCGecSaCkxY1jzb+jKao+JeYLnChF+i1ZYeVKA3JW3gs83RVbaGcI/eWKpnreecA253LZpYET9CKRkixyLBRU7Gzp+d3Io2zZZj2kC0v4t14F06I8sOJHln0bMHNBAztQ+bYC4s5kCJHOggdz4KrLGwlojzW2vVWO5t30Dn1HerxzKMvZVBxRHUxlipQFIr/uSlzOGjp/aKF36ltab6cEHqM6OKBSYwNAmLW/qbq9cTVK3NfLfWXsLKAqAhqg1JyYWibQwmoiO8HU9JGiWjjIwHh08aHNqks+DVaCg8ZGp6vnqHsx0mijHXK0Vh7r6qZY6JCg4Ii9Bk8Ptqd8EC/yy8Mjw03VYsXI/FEVKGuO1b4wPDeJGkegvF4EX4SgsISStMNGYJgN0IUKnvfBrDtQrteyPs3ktZpaQtNhEU0Q3O9imSuY65FciPcsZ92LWDNlT375i7YviyriA38sDZSlPN7sh9nkk+Xxq/T9lWrlcT8H93EyeiJH0xgBA==
*/