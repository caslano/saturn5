//
// detail/thread.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_THREAD_HPP
#define BOOST_ASIO_DETAIL_THREAD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)
# include <boost/asio/detail/null_thread.hpp>
#elif defined(BOOST_ASIO_WINDOWS)
# if defined(UNDER_CE)
#  include <boost/asio/detail/wince_thread.hpp>
# elif defined(BOOST_ASIO_WINDOWS_APP)
#  include <boost/asio/detail/winapp_thread.hpp>
# else
#  include <boost/asio/detail/win_thread.hpp>
# endif
#elif defined(BOOST_ASIO_HAS_PTHREADS)
# include <boost/asio/detail/posix_thread.hpp>
#elif defined(BOOST_ASIO_HAS_STD_THREAD)
# include <boost/asio/detail/std_thread.hpp>
#else
# error Only Windows, POSIX and std::thread are supported!
#endif

namespace boost {
namespace asio {
namespace detail {

#if !defined(BOOST_ASIO_HAS_THREADS)
typedef null_thread thread;
#elif defined(BOOST_ASIO_WINDOWS)
# if defined(UNDER_CE)
typedef wince_thread thread;
# elif defined(BOOST_ASIO_WINDOWS_APP)
typedef winapp_thread thread;
# else
typedef win_thread thread;
# endif
#elif defined(BOOST_ASIO_HAS_PTHREADS)
typedef posix_thread thread;
#elif defined(BOOST_ASIO_HAS_STD_THREAD)
typedef std_thread thread;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_THREAD_HPP

/* thread.hpp
76SVR7zk2xBmS2b8dexck8JIKft50Mi+wqEuxCvQ9ATchmZHJwzayDail38bHa59Icgez45CwsXLP4SJg1InAZOq9VzgpteboAYJsC1Eud1ULAvYMrHGq8iGIefDACr49XOvFGTEV3MgMk4ooNW0V1ofeUGb0ZFh0OtxM38ZNZvPTGFmo1REH6TD1zdYe4S7UN/u42ik5Y8UUijwqkMmJDMqM3J5tgTrinYTW9k7IQVRBYhCYrkysg1i5L3tK+0KY558deyNRUCsG8fBewf3EbgXtwNqVpdtfc60q2VlDQlaTo8RoDeloAcONoviF9B3xqOQ9kXz4Of8zm9puacot3MpWM/e3LXmliTTYCKLfK8FMFzsIT2zYMGkFnLsbA8WPbjA+VaqraF3UTkgrrKqIGev6Uk1rNL/JJ73lPoPxqsaR0zbUOi6plULrgFpujJdJwOMDC1CkRHra7/Tb422QM3PnKSu8+r2L1apeA3Vdr1QbOnTnGHljJAzd58GhVc5nIqLPaJ8ES0qJ1FYCg0hiPYihF2a9wVO5/+CxRhK262b6R/MC59UdsT4bA==
*/