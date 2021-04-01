//
// detail/timer_scheduler_fwd.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_TIMER_SCHEDULER_FWD_HPP
#define BOOST_ASIO_DETAIL_TIMER_SCHEDULER_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)
typedef class winrt_timer_scheduler timer_scheduler;
#elif defined(BOOST_ASIO_HAS_IOCP)
typedef class win_iocp_io_context timer_scheduler;
#elif defined(BOOST_ASIO_HAS_EPOLL)
typedef class epoll_reactor timer_scheduler;
#elif defined(BOOST_ASIO_HAS_KQUEUE)
typedef class kqueue_reactor timer_scheduler;
#elif defined(BOOST_ASIO_HAS_DEV_POLL)
typedef class dev_poll_reactor timer_scheduler;
#else
typedef class select_reactor timer_scheduler;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_TIMER_SCHEDULER_FWD_HPP

/* timer_scheduler_fwd.hpp
f/FH4YD6Xv/osAa70ZANlS3jDdQI3pK9fYc+kxn38LRrb0/G75EyawZVpm6EUEE+Jt6Q9bNGZrcR7UbTSdo7z9amgRg2YN7bIWxgONp7mB9G2iItrdzidbU9RWqGbMbaVHNRwPMf02ba+tEz5LB8/9KsFgvcpdEgKvPP4YuiV1RkJMu2I7bMbzNnglKL3lQd2jfsW/hgVAuqSygT6jNLbvB8EsbclUXe+B0fjmzPo8SEy/MSPj/N/+J5cERaui/yauKCGPo36raMsVK6gSLkAWopr7Dos0GECOoAd43Ppdfctq5rRXcE3ftVYh5zrCvd2uUkCOLgMzafVQYJftbNXKZw17jDIUW6xnu7EIlfg9KKUAiY1K/EPEJadyfULe4JO1Jio03H53iiASOHGEA2QPLf47GNd+DaR98u4HC9A0IZBUE9sZGrVJ0g1AQOp5CzBoymsXj/JZ0KW6iKgXf+PFm5iSlQtpBXpWXUKrvo0lcWJKw9wueLQQL4XKctJECDMzUHJ7DDNxAsY3lzzHK4jSGWjF+R0H1w69h8rtstNDQm57mKhhjZP8ErRw==
*/