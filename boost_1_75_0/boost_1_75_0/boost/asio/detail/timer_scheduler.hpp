//
// detail/timer_scheduler.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_TIMER_SCHEDULER_HPP
#define BOOST_ASIO_DETAIL_TIMER_SCHEDULER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/timer_scheduler_fwd.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)
# include <boost/asio/detail/winrt_timer_scheduler.hpp>
#elif defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_io_context.hpp>
#elif defined(BOOST_ASIO_HAS_EPOLL)
# include <boost/asio/detail/epoll_reactor.hpp>
#elif defined(BOOST_ASIO_HAS_KQUEUE)
# include <boost/asio/detail/kqueue_reactor.hpp>
#elif defined(BOOST_ASIO_HAS_DEV_POLL)
# include <boost/asio/detail/dev_poll_reactor.hpp>
#else
# include <boost/asio/detail/select_reactor.hpp>
#endif

#endif // BOOST_ASIO_DETAIL_TIMER_SCHEDULER_HPP

/* timer_scheduler.hpp
98ZANMRHoBWNwbYvSj4MBQB9eIrF4ATeDs8lfAw8tdX8XCOUbNsXib5Oz0hoI8+PA2xAjptkf0rDsSBd0O9UF/S4MfEmDEL07gMr7Uu4qI6l/i5h2YC3iTthWZ9JW8YPxWU95k9cvwTzLiAVbRqYbI2emfL9sS5c3d/JVvfL29rp6n4sK2BgSgdGJ66/0U2zZ7JolpfVCCv8VdT0kSKfp0b76yPS2ouliUzb0Icu6lkIFNmHLutp3hg0kqMLe1YU2R+gS/t+jMGceJ8ymD5Vp4VvQqt6dVsqFvcfYOln9/i2KLZXL5muQLKhMNAGkdJAu7Yx8Ov3cUOG5gJIvkRIhKzAP+X6Y0RyWvks8SuDYJhle9VvqkOHRhJSXmjLZgRUs8kml9tTLlW1wypT6DM3YIGFNbyaTjnObvhDYC/QauB5qPV3ueHbPeqZ9bpAFSXQbteaxJ4PogmxFCkttUpuszTXItcvZcb7U4bBuFx3VGVvLWTVdOqLbbWHLI/XvEqgPoAfgbom4Cg7hzIGsTQ3xFEW5FKOQlb/i/KSP3zKeMmDatK03DBeMpqmTdRGOvUlMfloO72twEM+GPRj/mLHDqPjXM6zVp63U/s26tRzMHRzHAm06t0QU6coy9Biz009bAoDydFQ5L9rFWUpjc1lOrhBZE8o9iOIXcyixcvG0ot321492eAMYu2mT6S8Trk2pSHteEe7nBPvG+rb
*/