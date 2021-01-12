//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 20010.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Based on the unique_threader/unique_joiner design from of Kevlin Henney (n1883)
//
// See http://www.boost.org/libs/chrono for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CHRONO_TYPEOF_CHRONO_HPP
#define BOOST_CHRONO_TYPEOF_CHRONO_HPP

#include <boost/chrono/chrono.hpp>
#include <boost/typeof/typeof.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(boost::chrono::duration, (typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::chrono::time_point, (typename)(typename))
#if 0
BOOST_TYPEOF_REGISTER_TYPE(boost::chrono::system_clock)
#ifdef BOOST_CHRONO_HAS_CLOCK_STEADY
BOOST_TYPEOF_REGISTER_TYPE(boost::chrono::steady_clock)
#endif
BOOST_TYPEOF_REGISTER_TYPE(boost::chrono::high_resolution_clock)

#endif
#endif

/* chrono.hpp
IMeKv3OsUec9M9mIGUCcobATvIy826xscN6LikeVF+37vNvHnGn3I0kfCLj0A83barSek8phz/52794rJPxDfzZ5ZRP/5+K+2cq3ksx4K9+1f2ieEetwFYWVlZPKJxSF8p1FvsUS51t/+DydKO7uLn3FJb/ItS/SZ8D+EucLc5G5yaWvuB2nrpPputJgCf/UnKvpMyPSZ7rWYdTY0jHH95T+yjFN45gqQ3n4r/Ud5/S/UvFL
*/