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
wDZM9UKGi8vYYxPlX2cvqueQ0Enme8upXuJb2aAi1+T9T/IU5eGPQIcYQ4LppQrcImHYSRVKdX4jNWB01lbHAUa7RpEVS5V/7LdqjVI3WSplcx6/X1dQnxHzZOSNv0N5f3wkzFip/wBQSwMECgAAAAgALWdKUtGHykMGAQAAtgEAAC8ACQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9jb25uZWN0LXRpbWVvdXQuZFVUBQABtkgkYFWQwU7DMAyG73kK37isFYIDUoWQEJchwWm8QEi91SKNq9pZu7fHyZhUbpb9/f9v+4PTqYPAKWHQRmlEzupeZ2s+C1q/lxe3xzh18OlXGvMIBQIfIy/Yw5Hnm5o4uQNi46NwB6Nfq51784onni/dlmuaxv3zowR/caCDV7hwvmZAyHO8k40YlEH9D7YAXwMJcIoXF2kkLVrcktPgBXcgDHSsRrehwEI6WGgRnOiMxuJM3AOpWyhWUCllhKZoE6tNoE5wJbXsA6WAcMZZStJT+/jQ3u/Mr2w01SN9CDhZVI+BRh/h7GNGaZ17P245sCqL/VLQ3IwrD5FdXS16UTsQr8nfWMHW/QJQSwMECgAAAAgALWdKUnQ335sBAgAAwwMAACoACQBjdXJsLW1hc3Rl
*/