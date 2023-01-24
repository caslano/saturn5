//
// detail/event.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_EVENT_HPP
#define BOOST_ASIO_DETAIL_EVENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)
# include <boost/asio/detail/null_event.hpp>
#elif defined(BOOST_ASIO_WINDOWS)
# include <boost/asio/detail/win_event.hpp>
#elif defined(BOOST_ASIO_HAS_PTHREADS)
# include <boost/asio/detail/posix_event.hpp>
#elif defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)
# include <boost/asio/detail/std_event.hpp>
#else
# error Only Windows, POSIX and std::condition_variable are supported!
#endif

namespace boost {
namespace asio {
namespace detail {

#if !defined(BOOST_ASIO_HAS_THREADS)
typedef null_event event;
#elif defined(BOOST_ASIO_WINDOWS)
typedef win_event event;
#elif defined(BOOST_ASIO_HAS_PTHREADS)
typedef posix_event event;
#elif defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)
typedef std_event event;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_EVENT_HPP

/* event.hpp
FYsr4/VZsZIwYHHlJH1WPKCV/qjCO0fxOtw6ULPXlRWsm7sazRLrAP0pd36Cjt79U833g98BoY87v4Lje1BC3Mlg5vV6YT8sshiyu90fzFSlqjIvw9ug6nbmK5ASPo4qb8WcVnmjjCm5RnzplgBmEBIGkaXQkhHzs1/JxEx7vIX2SP40B5DnuYW6FLfPkXFzHJVz+tLpmvRCdnMLXkbs9eCBS1sgbgBqZjvRHrZLL+G7PC6zdKgTTMpxYEh5MKIjLXzln00W/havx8baJLyKhyUDoB32dfvDhJ657vyfOdAU8/0cH55cOcWHibpoU9Yz61jsXgXm3OvYly9Cog8uLs8yAi+IyBVnGsknSbBSuTwC5DPHRrrpzsHTulKuoOTqvILnN3Hrvho88852rJtpIE9CXTEiuXhRQwvo5Cwu7e2jgEgHmVMNdkojoMtMMs775WsxgZOVutdMwwC/YWQGh77+zGn0AAQs+9PKq8xpC3E1OshuhBTa8b0CmPkCM3OgPM9ursoeKksKar055LvYe5P6NmU2DEdxNhowxYndNSwvQB2C4kEAJMfELqPoQT5Sax/9j47zxUrJ69rTwfzO70FeVIqgjz3U2fHCxwWD/hTZ3PJJQfJ3OqnivsqCulV+/SlArtfgyYQqaadX9088nQ5/YhNPf8J5Tujwd3h64mmfXgT1a3osdFJuNRbM1nHN+UZx+oD7igvebw/o
*/