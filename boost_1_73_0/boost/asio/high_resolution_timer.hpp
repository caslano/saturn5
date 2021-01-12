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
/VfhBQ6FpvgmlVdPCW7QR3NlIMZJ6fuT8Aa4bWAuTzjNcmb54qYTayekLyaUwha05MuLX1ghF7ywEp/pJHFxei8v+2xsLHL9vtWgMvNbwxvGn36r+R0+f583URClDHBOyMCkyIP0jfc8igsW66ls+fnmt2ml4D3DOxmRuE/e56Fi5+9b3Xqwk7kYxQe4hLGotYkdn5Og0vwXPODIHAznkwWaAEqV93YrRpihY0xGFFSJXTBR
*/