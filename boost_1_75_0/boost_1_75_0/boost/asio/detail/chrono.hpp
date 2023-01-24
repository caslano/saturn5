//
// detail/chrono.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_CHRONO_HPP
#define BOOST_ASIO_DETAIL_CHRONO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_CHRONO)
# include <chrono>
#elif defined(BOOST_ASIO_HAS_BOOST_CHRONO)
# include <boost/chrono/system_clocks.hpp>
#endif // defined(BOOST_ASIO_HAS_BOOST_CHRONO)

namespace boost {
namespace asio {
namespace chrono {

#if defined(BOOST_ASIO_HAS_STD_CHRONO)
using std::chrono::duration;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::microseconds;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::minutes;
using std::chrono::hours;
using std::chrono::time_point_cast;
#if defined(BOOST_ASIO_HAS_STD_CHRONO_MONOTONIC_CLOCK)
typedef std::chrono::monotonic_clock steady_clock;
#else // defined(BOOST_ASIO_HAS_STD_CHRONO_MONOTONIC_CLOCK)
using std::chrono::steady_clock;
#endif // defined(BOOST_ASIO_HAS_STD_CHRONO_MONOTONIC_CLOCK)
using std::chrono::system_clock;
using std::chrono::high_resolution_clock;
#elif defined(BOOST_ASIO_HAS_BOOST_CHRONO)
using boost::chrono::duration;
using boost::chrono::time_point;
using boost::chrono::duration_cast;
using boost::chrono::nanoseconds;
using boost::chrono::microseconds;
using boost::chrono::milliseconds;
using boost::chrono::seconds;
using boost::chrono::minutes;
using boost::chrono::hours;
using boost::chrono::time_point_cast;
using boost::chrono::system_clock;
using boost::chrono::steady_clock;
using boost::chrono::high_resolution_clock;
#endif // defined(BOOST_ASIO_HAS_BOOST_CHRONO)

} // namespace chrono
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_CHRONO_HPP

/* chrono.hpp
OstOWXuVp6mW3PIy1V++d5LPViLGhbam6ai/OEnCnP+V/hIfhGsCwnUgALCjs43OMdtmnGukdioUhCzlMlI7hvJAMKvqneTwiovpe4/tpHpn0i7A0e1jOuidceSZm1Qwtg1ltv4NUn4s6MtRGNgX7g6ECccc5I0VMmt3Km7RGRzbNuyE0Vw/RsNoxq+4uD6VsCtSTghrdEqZpq1ucyGmg+8Iw6Puut/sIqyLgE6Ic5A56NfLMemrJaul1+7s5IAvAuOMc0wOdMqOg29CX9mFxauM7ro2aObrvVXH99xq5GP+hpH0QmR5ZjzGp+DGlN1BUvEQkY1Et1DPwNDd7srA/LQSHrQoqcQXQ5bcqE1LsjBoU8eR2WoReWiILFCY07vexW6xo5ef0HUCfMdlydvxOczE0VEXWACRwZ6Gs56iq3zXkm0vUtpsdJCE5aopYEfrGlFfJx0Tc1T896L4l74kn42SZyCnXsoH++TvwgX2Scf7fF/7nM7DjmEW3B5Z3BLocNjVaSe9ZqFZgNc8fkh+CwRSHzXk68VHDS6d0+kgB5tb2fnRRigSN56Ff9O+WmtZbUgrXxZFB9OQqkfixYDNA9J4TcCm6DkJtddPixkWVlzlb84wGWF2izzn4KXEuvPWwb/CQCnDIHnxhbQT+38hsaJ/q1QifdVwHEON0qTmxGXGpgyT3lz4NO6I7sQedGYPnjWS6DckthJZr+7V
*/