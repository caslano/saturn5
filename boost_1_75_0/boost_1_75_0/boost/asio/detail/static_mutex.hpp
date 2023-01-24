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
fiZkk/6U3CTXyodHHpCcQfESnmn4nyla3eSV/JBFvBQ5siAoXoGyOnD3Ceo5rwjEQ0zd6jndRa+gwR/sba+9pK0Rj2EmhOnR3flUB4Zq8wNYy3+2oxJ547eoP3+OC+nPcZUjn/Vf0Q15ZfOzqvI8lSnPxXI7t3Xw5ki8/bbsBnJ1IS2YtNyO4z5Q6CFPF2muKFnWdshpwKmY4egP6uEHvLr7VcwUDcwijKrxrqnAKE15nlxElee/VWvZomUgz9mpoLFmKFC8Rs+NPei7rpHq0XYcA2xwQ0NsKzRtJJDpCynbGnW7zhtn2tlm1e0wikYOZZxpe9S2Gj7e9m5NNjB1F5nXAUIqztxf9+lF+Pl0iD4KLZj/uv5Wtx2j/uUqjgN8y4cw+Jp7wPesh8JXdZsO34s2Bl9ZmDhh7hcSJ/jPAW3T8OoXAOC+IdTltICn5idVXlG2woI2Zj/+wKwXiJDrpIIWN+WFHmVyI+U9TOwQhtBdDX2zaShrW9dgbJuzBS8GKLekNMFsGHhRFpqhqoQhPeelAz3au+64us9GdxI6vRklRnrppAWqcgGM5PSXqiu8btts+z/G/Q+omO2zqDQdTx5xM6JYNVnfI8IDgWRwNdvFx9PMSN+P6PRd9vCP7Q3le8jp+zT67bE11MdD1jOBNzCAXJykb+dczqNw9KTh0RoNF95Hafhjloy8Gcp5qi9F6svxP7wP9BggAMSf
*/