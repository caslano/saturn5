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
f62v/slQSd60Uv68Vehf6pqbttBl8tXGO8zgW3BVXArpwJ1kPfnPHZ7Q04703K/XpNH+Orm1FSO5OjAO8EouypIJkGBkphSDKfX05RU45uAdhoGkYa3T+me/GIajb2EgyrC/xFNgwZFhHVMmdphde07TjgVV1FBF3mpmWN7buDwM883sGGSqORuIPjPwxxUTHWEMWQewt+xNw+WtyKGxegsjFG2Jv0z8SjHT/Pvv7GF0iwm7o4S2GMUyYG4L+AdcQxu+RYEZxQzAVBsHA+q2sHHZgUHDDnFm73YSsuhYrwxZugDFL3fGr0a3sAk5KK9UZvnEkIWBRmKwBZP4yFhojBYbGJaCjZ79VqvqyJqbPYeb9HQi1nCkx3qvJAAb4J0udxwYAiYaY6eNYLYaayjerIOa1m6gnyVG0kOunX61XoMTKtCYH76BTT2BOQ/TWFjv/7sNJr0rumICaw7jk6P9lolUUMKZSm0AD/otEuwQEoum8LkSWosM0zvOxoghNo/kK/4WZ5KJVAmXzOfMy9Dxq9U1/hv05BpGhEHDlUNhP+YwZ9QB9kMPFlsrPvwYuqzOMMZKqHogR6sBBgztKWdLcmghfBZ7YayY08ZIeWapDoEbVeLmVeas7eCMoYmx4mKMCEKQsliScTByDI7V
*/