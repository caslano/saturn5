//
// detail/global.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_GLOBAL_HPP
#define BOOST_ASIO_DETAIL_GLOBAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)
# include <boost/asio/detail/null_global.hpp>
#elif defined(BOOST_ASIO_WINDOWS)
# include <boost/asio/detail/win_global.hpp>
#elif defined(BOOST_ASIO_HAS_PTHREADS)
# include <boost/asio/detail/posix_global.hpp>
#elif defined(BOOST_ASIO_HAS_STD_CALL_ONCE)
# include <boost/asio/detail/std_global.hpp>
#else
# error Only Windows, POSIX and std::call_once are supported!
#endif

namespace boost {
namespace asio {
namespace detail {

template <typename T>
inline T& global()
{
#if !defined(BOOST_ASIO_HAS_THREADS)
  return null_global<T>();
#elif defined(BOOST_ASIO_WINDOWS)
  return win_global<T>();
#elif defined(BOOST_ASIO_HAS_PTHREADS)
  return posix_global<T>();
#elif defined(BOOST_ASIO_HAS_STD_CALL_ONCE)
  return std_global<T>();
#endif
}

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_GLOBAL_HPP

/* global.hpp
huwHP48i48ian9PVh3A8sl4VzyW2fNReh5A/lz6qDj/AVh09aKYnWos+hQZwetgaldbDDUUPmvLhngFjg98yvTz5kScXcIjWgYYru8QkEnpiiyWfS3qxE/O50vv9MUD2WOn/lGdHjx6M4sEHP5lrHmQ1qgjtcJEZnOqz19uTdYcH2WnDUw9D+q0chMltyhA7lrycti9zcQIYG+YrVzqgO18yuSGAmWm5ZUvoTxjkok+IWOjF/v07QZYH2mwgNLnb8EzJIc8n1ZE6XMI0t3JAXceBNDFUEx3uk/17zhiCWQ0gUw0YVukYMwzs9gxdiXLKYN13P0FJOJGdIwnxyJr3s6VkkvfOIbX7NCKBcsRhE0O+fP/wkrhjKf5ZZMATW77/nps7ybGUl3AvUyYiQKWRxebeO7sZhp8C/xl6z1RyiEclS9PDVmLUg9H1B+OShQR4SapqK0nAtVpW0jCMSjLeTb+iykcPdmnT9tfDZEywvCxTXXKU2VTB0eO/I9RmW+5OrnSSLMp0IN2jCRP5OsC8yQYarbK12tawuk6STR+eZ2HLczyq+3HVyE6Xo4P7yPd45MbrcAqA2Y4emavOlRwQay5uLZc60HchO0PoRfP+e56P8lgw/9ynslX3UfLnGe4xI27qbvTyZMv1Y2Ek
*/