//
// detail/static_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STATIC_MUTEX_HPP
#define BOOST_ASIO_DETAIL_STATIC_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)
# include <boost/asio/detail/null_static_mutex.hpp>
#elif defined(BOOST_ASIO_WINDOWS)
# include <boost/asio/detail/win_static_mutex.hpp>
#elif defined(BOOST_ASIO_HAS_PTHREADS)
# include <boost/asio/detail/posix_static_mutex.hpp>
#elif defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)
# include <boost/asio/detail/std_static_mutex.hpp>
#else
# error Only Windows and POSIX are supported!
#endif

namespace boost {
namespace asio {
namespace detail {

#if !defined(BOOST_ASIO_HAS_THREADS)
typedef null_static_mutex static_mutex;
# define BOOST_ASIO_STATIC_MUTEX_INIT BOOST_ASIO_NULL_STATIC_MUTEX_INIT
#elif defined(BOOST_ASIO_WINDOWS)
typedef win_static_mutex static_mutex;
# define BOOST_ASIO_STATIC_MUTEX_INIT BOOST_ASIO_WIN_STATIC_MUTEX_INIT
#elif defined(BOOST_ASIO_HAS_PTHREADS)
typedef posix_static_mutex static_mutex;
# define BOOST_ASIO_STATIC_MUTEX_INIT BOOST_ASIO_POSIX_STATIC_MUTEX_INIT
#elif defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)
typedef std_static_mutex static_mutex;
# define BOOST_ASIO_STATIC_MUTEX_INIT BOOST_ASIO_STD_STATIC_MUTEX_INIT
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_STATIC_MUTEX_HPP

/* static_mutex.hpp
+8kqfAIurL9bvJEhafnnAodQ7qifzzKkyP/5wVivsRv+VrgXc3GdWH0C48bTTdm56SU1kMDiIxZi5CnUTQhE4r82LpIhG7OcTHP65PBYS5bUxLbQ8doNtkt1vAwFp5O5B3z5G7Yyd97vhy6vSMfuZ8KX8NFxiROHCLV351uIJviI13Fvg2blD8OPqUhU1h5FSGaiRjFfJbseJpJvSbo0KVdBXJhcFRShlO5hp0FhUJrEGYVaY8ZqwtjnpAWiwd5WXM8l/QJ4Dq1SZEnp8w8lK0mNjXftQy3ltiAzRre6PHx0I1NflVDwOZIJPdacWiRJEc0mr3GuEAlFeyKe6wgQcRUOY/PfYEHL3dfXiMsnt8uHgDmSttDNRgeurGNejA9kGXn8zEGEX7Z44of/hcGJuLOXNdvzcaQgGeNnCk4ywMUwLB2PnUrIoRmbq/AA+xgjHu0EL9QpX8iNDyW+icjWd/tzJj9uKo42Va4umNBmtKRrApc6n35Mwz/uiErr4lh1DofiAiCv5xeKlvuZddb+P8H5fDCGCSGFS5/TnlRKqRRzHzUTsReMkYs36g==
*/