//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_POSIX_TIMES_WRK_HPP
#define BOOST_INTERPROCESS_POSIX_TIMES_WRK_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//workaround to avoid winsock redefines when using date-time

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#define BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#endif   //#ifndef WIN32_LEAN_AND_MEAN
#endif   //#ifdef _WIN32

#include <boost/date_time/microsec_time_clock.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>

namespace boost {
namespace interprocess {

typedef boost::date_time::microsec_clock<boost::posix_time::ptime> microsec_clock;

}
}

#ifdef _WIN32
#ifdef BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#undef WIN32_LEAN_AND_MEAN
#undef BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#endif   //#ifdef BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#endif   //#ifdef _WIN32

#endif   //#ifndef BOOST_INTERPROCESS_POSIX_TIMES_WRK_HPP


/* posix_time_types_wrk.hpp
CIktuFa95sL8SI7wOarUEnB4Wf1HY5DrecCKbUMIS9FY8GYQltw72kHYP7rIvdWHLwmb9xxLEpaY/hsK9MUmFogAijFxCU15Q1xuummIb5MYheS6dRdszLF8d9JXmHD1EItDM9gE4LiI7RKOsRRwcJzHelyZrkV4+7cVirg0jF7gjq5Y+aF48SHRwOB3/aG0D66Mlx6CBuYYJAwlYmuWJRE7rmVyG0ckPeYwsRvPS3q8lVHe
*/