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
WJqiKoRxJkqXGXhVZNokBSv0lku6iDwTZOkhyZd7ghhCVDJfFxmawRCgTJxjgNuwzmJWKFm16Y2FKpoqtN9JydbXGPIMPYFTwwPLO4VZKLhow63lD52JD7eG6xq2PwVnAIY9RV3Xlt3HfHO0VAB7XBVMoOUC+HKVchYrgz/vo2nGxHdujGszcMa+5dgeXMA8LxhfZJDlesxWDKOQRRhhDb0zv/iuEfQtz4dZwcKvAh7QU2g0w5kIZmuexjEvWhgLUF8AY78WPFuU1XQfFpwqBRVhbHYzinLNjSCVYxpKrMeyerNwyVqbes7Yo9zqWYZZcGMop5+5UFbgWy3LeSZksCNYPoDlVz0K9RnmGLP4ViNfnkvpUZ7N+QKfXpn20L8ZjY0r838VVMt7YmphTy2taOP+YA+3iud7MPq+h8IFDb2gIO8B33bIyX3P1JKm7TrXaO56S4GL2WPpCsb9UqVFhni2pCiDiolRcW52WjBjlHyIlnHKM6bj6VSHBvvLGpdlEkrUQXmoolisEThjaf6AtxkpKtAfb3LZt1xyprOnSqM9BdunjWZ138JKD7HAGXWzGenWtN7INOyBNXpxU43mJqx0vxutVuWapu3U6sWPXz5V99ZQ1bN6aR1CGCPf+9zrLOM6FhTiEg84tg+v
*/