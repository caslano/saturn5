//
// steady_timer.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_STEADY_TIMER_HPP
#define BOOST_ASIO_STEADY_TIMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/basic_waitable_timer.hpp>
#include <boost/asio/detail/chrono.hpp>

namespace boost {
namespace asio {

/// Typedef for a timer based on the steady clock.
/**
 * This typedef uses the C++11 @c &lt;chrono&gt; standard library facility, if
 * available. Otherwise, it may use the Boost.Chrono library. To explicitly
 * utilise Boost.Chrono, use the basic_waitable_timer template directly:
 * @code
 * typedef basic_waitable_timer<boost::chrono::steady_clock> timer;
 * @endcode
 */
typedef basic_waitable_timer<chrono::steady_clock> steady_timer;

} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_STEADY_TIMER_HPP

/* steady_timer.hpp
Y36kNqvRpFxBdc5fijPSgs2IlY/4cld+GoW0aYmVOjGazPfIS7IJrIQkf3BCLAct6JruiRMq/M2RpZJvkilEJzZnxwMZhwTtHa/jC3laoEphhaXV1k6rRCUtTF/1Fg2j6lzLa2hoKtSvwTG6lwvYWompNRELXw3vXDEJ/BVpB4gGqbQ4yRoX1+ttoXybJdyzVoUqylxJOkgknqiNDhYSWm2DepJnkXKgf3CHhIkmklIXoqmZoHXuL8S6Ov7jGsGj0MglTIKD/0J3xiBaIMmpeW1HIvioOeOHtO4rORjqR0CBMLg3WNoHySHYAl2QMNq775LbOmlyM2XRPWasgUOg38CYyucTGhIgvF29mDOXRLxGJRe95Lx18iVREUVWPEgCKlQREVbYDU6m8Xg6XBambO3XUBA5zyTilN1bjS0aaV769oiO+m8DezQnCvQmYR19EK8+bQf7qiJPzqkIh52bxaVuJXVnfctpkformuLAK2aKaI12JFmGu80tryXcx9O62fniGzYwePjG8effV/PWOSn3cq527ajWIRUpR28X2nVv0vCh4fT9yf33J+FO+4vL2y+S6K7ESSyMGbMHaqGh2q6F+onjDKFC64pTzqQvCyRkMxHTJPAj6o7ePg4xvC394kt0LEGin61uHwed
*/