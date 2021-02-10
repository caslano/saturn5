
#ifndef BOOST_MPL_AUX_CONFIG_OPERATORS_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_OPERATORS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if !defined(BOOST_MPL_CFG_USE_OPERATORS_OVERLOADING) \
    && ( BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
        || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        || BOOST_WORKAROUND(__EDG_VERSION__, <= 245) \
        || BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, <= 0x0295) \
        || BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(600)) \
        || BOOST_WORKAROUND(__NVCC__, BOOST_TESTED_AT(1)) \
        )

#   define BOOST_MPL_CFG_USE_OPERATORS_OVERLOADING

#endif

#endif // BOOST_MPL_AUX_CONFIG_OPERATORS_HPP_INCLUDED

/* operators.hpp
OwcAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyMDYyVVQFAAG2SCRg5VXbbtpAEH23xD9MqCK1UY3vXFwTCSVpQa0KApo8L+s1XsV43d11KP36jm1uUfvQtE9VJQS79syZs2fPDJFmSlOi2LUR8TwR+PPIdlshY3VtjJfLWf0FH+6WzeKWrzEBSKlTI7JOoZHVZL+CBZNPTJqKx8yIJCuyHb6NiSYNnuV0HPBtB0YIIST/TjQXOczZ15JLFoPaKpoJxVpGAxTCqCA0ZZjnddwevL4lcsvzNzAbzyy/43TclvHw8GBWcCzXnBLNwgNNyUi2GbarM9bL9lvIRU7ZsO3Ygde1fccP8BnJ1shEpxi6GI/MwHFNN+i2W8aNyDWCmstdgaCafdNWqjfZO6ApkYrpIVfC7PeDgemcgj+xfK3TENxuy2gZy5QrwE8uNCDDmhIUZI3iWI0qqNkhSJVFgWePQQtYVbG6lDlut3i0OlvVmsCaaQUEE5+JeDx2xnOGNRQimTyHRIpNnU0zjgSb23Bs2z67Ede2Yfrxj9T/O5G8o0iTxXOBLvYKNUwb1kiFPv6fRvoXrmp/PbjbNz5a9KY23X4eNA7EgdAY+dpItS4w/LCNEkbQ8wwnysViMZsYVO4KLTDi
*/