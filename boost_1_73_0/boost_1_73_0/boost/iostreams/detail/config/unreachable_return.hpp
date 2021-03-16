// (C) Copyright 2010 Daniel James
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_UNREACHABLE_RETURN_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_UNREACHABLE_RETURN_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp>

#if defined(_MSC_VER) || defined(__GNUC__)
#define BOOST_IOSTREAMS_UNREACHABLE_RETURN(x) \
    BOOST_UNREACHABLE_RETURN(x)
#else
#define BOOST_IOSTREAMS_UNREACHABLE_RETURN(x) \
    return x;
#endif

#endif

/* unreachable_return.hpp
HpBW83ZKyWi2c0pWVtqnZGWlg75OgdqF9MIUSnOfKrSbLO0JS1tvaW9Z2ruW5l5BrnyrH2xtQDP4MpotNJvIoDkQDWv+PpcUX2dWtHcuH/FgKasNtdG4+amj+WzhcVrYlZ4w8QgekPVGSvFEiOSYbjt4wfUOynpDW2Wd4cjfmKF/6UdGWJzVjmTf3pbsXUn2koBjXVkR6Xp+SlCMgsyE8z5X5EGRsMhnciiGu70lI8XXerB8XR9qo1zmGbbOzPE=
*/