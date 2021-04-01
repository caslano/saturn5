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
aBVtle1bbW8jE8STaTg+0a8b2DmHPw/zT8XzLXmwtXHB1F92lS7PVUy9r1kULUBfp3Ox+18caNSMAHkrfNncf5+Jpl/ytWYuulqyshWBhKxMyRQytOg7hXyCFlXzDZ2ztiEKeziBBlKPvln/LrmGmY3OoNE3iOWzUpPploOclkWvlZJ9YCPLoBg/2rw20gy4JXJkK4WfwLRCa8sjvuLs/2p/Iz/Ee+G7pGWXN20SksVhKw38jJYx2vMWIPl52egcoxmFW/IQw274FEuOExCVEbGZeNvhmU+qFEI8RpEzghANlAIpr6J1SjAJ/sGSNKPJPoH85CZxwrM1qt6oVUUG6tJeaZv2U9SAUQkj0RUZj0Q8ppaDR+/Sk3D6/qC8kq5ClSFc/b0pCSJ/fUZK8MP7XYSKCmPfKcuNVheEzmFtiZlelfjVMmRvaAVidV0DarSNiVALbEd6+IBAg6S8dMYJvKCFmlnJwphamaFYBBp1w3EWONloJ+sdRhbnna+9AyIOguVClnRtABbtToMG2nhvGwemN/zacOf+bX6lKPMOSV+nAOBssOk6tGNqrA==
*/