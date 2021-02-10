//
// detail/mutex.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_MUTEX_HPP
#define BOOST_ASIO_DETAIL_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)
# include <boost/asio/detail/null_mutex.hpp>
#elif defined(BOOST_ASIO_WINDOWS)
# include <boost/asio/detail/win_mutex.hpp>
#elif defined(BOOST_ASIO_HAS_PTHREADS)
# include <boost/asio/detail/posix_mutex.hpp>
#elif defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)
# include <boost/asio/detail/std_mutex.hpp>
#else
# error Only Windows, POSIX and std::mutex are supported!
#endif

namespace boost {
namespace asio {
namespace detail {

#if !defined(BOOST_ASIO_HAS_THREADS)
typedef null_mutex mutex;
#elif defined(BOOST_ASIO_WINDOWS)
typedef win_mutex mutex;
#elif defined(BOOST_ASIO_HAS_PTHREADS)
typedef posix_mutex mutex;
#elif defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)
typedef std_mutex mutex;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_MUTEX_HPP

/* mutex.hpp
aBBfZ5AC6qacxiNZsPCbfCaETA7YHOgrB0UPv/xvU45wFvcFOh+ypKqS4g5o+M/zTM7kfZaAq8qxB13eFywTNlcu4uvjC+Irp2s038jlTI47mu4T/f6ABkIpajw6CLgO0WwsaDJMRp9AhNyrFUIUxQe9+Ob0/OL0Bj/7wsxFOhF+luYFHgzsgQg5wu669UwwbpxL/9lEII8Wu/E4SyAvgZeUTa5HIc2EVXOXZIjDXnz9HuA9lP5OCzlVIzkRo2SWDEVAaJYtNhxKd6Csjua/Pz47F0JydnpxE5fcXenuSESvy6td/Ph2d1H8UoSd98dX+NH/TtP+Ti8+f4O28qsvG3B9LlhcZw9O+TQbST95Pa3ZdOAne30tc735061jT4q10uU1G+7GV8kdKIEgAQVA6QtvbV8xhT4A9Zo/+vFbkEOITsAnD6E+pJJ3ZUGJRho0uSBJk0xnNd/txh+FElzcnL//POCDvfhEJLkGGDct5Z80Fy4jvBACgzQQIvv27PyUv/rxG3u59ONiCWjwCo2Fpsga+UOkpvPr7tX1T8r2wVrcq5bKTEX2/RI78nqMEy3vd70skxfdqcxKhhtlVVNvjxL78Slb1my7p2LKNoSozI1CyVqIozZRBia9ydmGDCryo744aKmdOwVYDUaI
*/