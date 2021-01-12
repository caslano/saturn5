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
eG9aOWVT1p8+H0YuMtOMklzKwAC7kF22dHnVV+P0Dzwd20jdhs4iBdDhvL/nEVUKTjUCG2wo6EuctG0kFJdeTAyLmQxvcbRZH3/FYPWs2IU/TfhDWxhXV4HqAQslOyx84UGzsc6lTP7eZ0KjThzOgC3NpfzkQVirctrJ3/GdeK2Gj9kTiNT3tZG0OyvQtB3D20r8lOcsSLyb5Do72ui+vKIaEAPm/SPZoxWYawv4ZLvWwQcD
*/