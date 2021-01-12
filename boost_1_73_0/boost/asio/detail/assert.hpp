//
// detail/assert.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_ASSERT_HPP
#define BOOST_ASIO_DETAIL_ASSERT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_BOOST_ASSERT)
# include <boost/assert.hpp>
#else // defined(BOOST_ASIO_HAS_BOOST_ASSERT)
# include <cassert>
#endif // defined(BOOST_ASIO_HAS_BOOST_ASSERT)

#if defined(BOOST_ASIO_HAS_BOOST_ASSERT)
# define BOOST_ASIO_ASSERT(expr) BOOST_ASSERT(expr)
#else // defined(BOOST_ASIO_HAS_BOOST_ASSERT)
# define BOOST_ASIO_ASSERT(expr) assert(expr)
#endif // defined(BOOST_ASIO_HAS_BOOST_ASSERT)

#endif // BOOST_ASIO_DETAIL_ASSERT_HPP

/* assert.hpp
/2fu3d0E+vrafF/23jtzZubM+8yZ8xjT2JFjBuQwIFlb5bQLJw4HfLmb9P2BVbeIyayzdotZjzM1+vefUWfLWr3pbtlwmzvB0FzFXEJyahYGtS9vPsW9zm1Vt2k18QN15AbeQNdgN6y3IJPpy0/+s5IuVyWpoUxYDxzlKifxSUJVqc7aLJ01gZ117TewK/cKp0tm0AeSwKN1978Ofl5c/kNbJC46K608TedqLwaP2VakBY+5
*/