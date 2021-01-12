//
// detail/functional.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_FUNCTIONAL_HPP
#define BOOST_ASIO_DETAIL_FUNCTIONAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <functional>

#if !defined(BOOST_ASIO_HAS_STD_FUNCTION)
# include <boost/function.hpp>
#endif // !defined(BOOST_ASIO_HAS_STD_FUNCTION)

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_STD_FUNCTION)
using std::function;
#else // defined(BOOST_ASIO_HAS_STD_FUNCTION)
using boost::function;
#endif // defined(BOOST_ASIO_HAS_STD_FUNCTION)

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_FUNCTIONAL_HPP

/* functional.hpp
s9MM5/LBwpsno3DhIU3Ei5wGLsdLU/QyMvfXfEZwHOd+IFvA0t0PjOLL8THuB9L4MlDqfsCKF5ZQ5n7gCDCBROhR1K/eAtGr/MOqBf8mj67jKdqzXf3j7M8e/ZuvEef2eLvm98HiZlOX+NH4k92+u2vAZu/aTpij/UB1CkyxOH753q+TxOLw0f7tX0Vb2vXwqhkQRRr10dF+6A/P+5wNQUwj5x6GbvcMJxg+c+SzzGJ8ZvBT
*/