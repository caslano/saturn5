#ifndef DATE_TIME_LOCALE_CONFIG_HPP___
#define DATE_TIME_LOCALE_CONFIG_HPP___

/* Copyright (c) 2002-2020 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland
 * $Date$
 */

// This file configures whether the library will support locales and hence
// iostream based i/o.  Even if a compiler has some support for locales,
// any failure to be compatible gets the compiler on the exclusion list.
//
// At the moment this is defined for MSVC 6 and any compiler that
// defines BOOST_NO_STD_LOCALE (gcc 2.95.x)

#include "boost/config.hpp" //sets BOOST_NO_STD_LOCALE
#include "boost/config/workaround.hpp"

//This file basically becomes a noop if locales are not properly supported
#if (defined(BOOST_NO_STD_LOCALE)  \
 || (BOOST_WORKAROUND( BOOST_MSVC, < 1300)) \
 || (BOOST_WORKAROUND( __BORLANDC__, BOOST_TESTED_AT( 0x581 )) ) \
 || (BOOST_WORKAROUND( BOOST_XLCPP_ZOS, BOOST_TESTED_AT( 0x42010000 )) ) /* <cctype> "shadows" the locale enabled overloads from <locale> */ \
 )
#define BOOST_DATE_TIME_NO_LOCALE
#endif


#endif


/* locale_config.hpp
E1q1gkYHpUfn4lk0lvbIx5ZOP1iMXukb2k/kldmAqEo4zJMQF4qsWEPULZjng5szh0gi9nA6AFFfxdN4Oc2Cg3Cn1xdn+xw7vqLGroWL4CzLZl40/hBfzKbjIJJV0LXfs/bPr8jBJbd71ERe7TnhPnwiBnwhkUZ7RM/fcMkJHjhERwiD3V7EO0azilGhNsPB/gvMn1IQDqfejII/gkpbrVJ60+E8Cj4HUcV9mvH7eDKN/55MJ9kqiD35bmmBgKtDBHFZdv8Z3bB2lZ6Ps+U8gffxdDkO5mhpFRoPaJyn58Arb+tYgdLt/bJbr53CMjlP0sskTz3dnTJ1Kgr+A1BLAwQKAAAACAAtZ0pSZhKZW6oEAAA1CgAALgAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfSEVBREVSLjNVVAUAAbZIJGCtVV1z2kYUfdevuKUvkMHCbjr5bqYE45oGAwNyHXeY0SzSCm0saRntyjZT97/33JUItpOp8xAYWGm1955zz/2Qv2zRsx/28Xx2R09+QvcL8cG6M5qV+rOM7LcNwvCO6i8Ml1i/A6pHe6u7sEPfZXVHbWcVNljv+DoMvwNuyST5r8fGy5AvsVNbNvYDvdmWap1aag86dPT69Ss6
*/