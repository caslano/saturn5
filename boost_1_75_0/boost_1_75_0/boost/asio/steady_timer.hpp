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
RkcqKa5JE+DJ8zKADfD93WQD/HdUmmEaKtZXIR/V4aHonFqFQ6uX+U+e6EO77g4pDVH7+ZPwE9n0sewg+zgw1YL6hsX6IrlGCp5ztlB+BG6y4eR/8nifaevrydQ8+VrFas2zlJJoHq/mWdvkWaN5Vmr1y3kOlFqF5WueKp7xRAjofzQ7aFZRFK5C89wv4piw6MA9szFqcHXGW7ZQYKJszZPN2vnLFwR7QoeL5Irdksg8Xpdn6RaMv0s+9oX5JcA4sEswlrdlla2vn0vQz0BEZ2dWrFHG6IVLCUzBjTeo6A9ewn/3NTl+ResrBxoYHt9RwQWCc3neSqhZt4Yy2c1MyjSoBioYz/LkrHybmqjnrDWD6zVVjg5K7XmjrcDsrhLsmb2K58XZ+Z4fi3k5FVh32sJXQqV64XoMYjifghhCPRlT3QOiYoSY0dyngYVDKxkeT6YLtnaLNTiJqac6PHQqcQeU0cZHfY0KFXgJSU7zh6EWjIq7e/eg6UvUaX6Gfr8LjfHLzY/iWrnhPLSpT9+0HnEQf/tVP9oFTIfTC1pBSsQjfDcBNptIiC9gig5+HeQKayR9bP28YmN9rl640su/hSYwFN2qorzr3lRx81Eg6zmz2aJ53q2tCEnMF73bb5RTnMc+Xgwl6kXr+auf9qM4ETHdedmwAuLgWNTylmp5XjjHm/LWaHkr0fArL1/LW8+TIK8ZypEu94Ol7Hb0
*/