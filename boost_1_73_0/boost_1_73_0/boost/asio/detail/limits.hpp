//
// detail/limits.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_LIMITS_HPP
#define BOOST_ASIO_DETAIL_LIMITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_BOOST_LIMITS)
# include <boost/limits.hpp>
#else // defined(BOOST_ASIO_HAS_BOOST_LIMITS)
# include <limits>
#endif // defined(BOOST_ASIO_HAS_BOOST_LIMITS)

#endif // BOOST_ASIO_DETAIL_LIMITS_HPP

/* limits.hpp
v+Z2K2qG3I9WPMHL0FjQGjZ2KXtxBbEvw3oe9kJMG+tOTesqLl9WYYc4Q0sg0lYTgkDl0zRMdmVuDIo0BxPct4E8t7zf2d492AW3E2MEx7IVI+NNjZkDB4bXn1weGY5TkxalXthUabgyojMzS8is8OcZ1kCmih60J7VVKWoh2qnyey43rYbWEKq48rKYEcTZ9gK+ui0zdKNJkTbl8kOFMo1lmuKKmxKNXLcag1y/8jbgntrh4DP4zZ9cdZMuItrQoVQO5rtE5fd1wzZj229ORaosOrZRNB1dte1qgcYUnJvIsSdAMyBYFv5naLHdmg7VEC2xrw+CpNeqvuoEULtDSsu4sNLV+LDdwKZ3hQ1WhLSowTM4QK7tosigLO5gL4+6ByK7OajMcyhsTpvinLusoyJVCTqUBnPeFQWY0YlvYtNmAOcv3pfCm4Q9Tdwfy+hdJFCYUY6D6nm8USM2ONo+LWDkNBU5uqboodQoHMih79DBez6GQk3Mr9vpJQ+ZRru3u1UXtyHwHqU9PEj6sgbwyxpXRZ8eSjxwxzx0rqr2NYXb09CFfrQ93UA9WUWPJYZ4HWCPUXhWNJjTspd43C1ag1h30LJkSs6vnVka3wdazmcNFrruQxHq2y26K/B86ReK/zOhfv637+JpCVOi
*/