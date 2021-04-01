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
qrl+GEQZAO3UwlLIt8D9BUllAu1AWdvbWWwSq1DhzzEa+ATG9a+aGuoN/6/AC3guDdDa56ROZTMCyN1VAnZdTl5YzdFfXJ9UVeE/hlbtHm73W5hUJfSYY9Gp7lRwbdi0umOwe5uqnRhSVxANevhJopc0Jxh/ROZ7QqzIEu+usZNZG08yU2UW150LiQKVjdCqhaOaKnMXBfoZXKx37NI3+U5WC/mFvlz8EvHJodpqTk04YEeEtBPWWSKrD25WQUa8YylY56yxmuPjI2HJJldHcxR/SY3nrxdPBXfccGx/k6EdAQso4noN7wosMKGQT8nqFwpoEaSmbuwqBNRrmztaxxf12KinC1SAzxAPWXAJs1behLWkAQ8IUu1kUwlBSelCDL9Xi79EvDN/xsicWIoFo+xpFmUx5a8pEA0mAIy/c5hzQgtNdIB7YPE6qWx1oapRJIHjJopqXfRWzxYvien/KXmdc+vrAFxYcuuFUsJjpJt3BTLOYehvIXDlua3vl5YMhQtXcjqLRMU1NnCuvqB5ZZS5uxxVQZF0gJnb5zr3M9SmTt+EulW9qfdTjQ==
*/