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
STx5ugdqbXRl+s2Pe97NUUWrJ0J4do34B92HF7BddsJa7RHcryN4aM9GDe/T/yqX5two4e55XXdX72eJ5kH+2dLe/Y97JIWsbOCpntXNXIJ1qu94hDV0Pnk/Nn4gFzLZuGxS2fBLvKqhyWXyxHBSZsYgSMlOlE3RPTJc62Srp6KrcYniw2/9dOGGrYly/pxxTMN6FJ5vQ/CwtCrjHDYGeHbIauXjOv7hduWTrZnDrhmLRTPogpter1BC0K/cG+Zl4v1X+36zCFl2g6zpDh9PYBdRry3K9HFugp899IJwODjgr6h7L/IDBFvPlfXKJbdn7SaaoeqCJClHsQlBEmEgOk70nt2stWYxquebi9qSyxdYmoQ6eHmgdSJZvQ2B40pAUD2jUHysSCoZ/BtVahFp87vJA13hzCk2gsxsHkyOt9bN+ahePOhc9/OM6KH6WWyilTIhhYRWuz/J7kVJG7h9lirGtFyUhTzccBEKCSWbYKNiWIAqvgoNCvFBxczPWkDZQRm+kgbBoWRodiqGRahiWWhQOxDamrVwBUJ+kgbU12jL5G8UoELJwjmo9FoxwVPXSHR8UTFnsxaZspBOIteSy60dd11fHBqoZsaQwEXZpfg5FpLJ5ywWgegV15Jb12hpFG8UvAolk+Kk0uvCBFdcJ8mfgyrCwoJ094Q4pdpa4EA9jjmLStkCXPCIIdQTyKNxLXnGDroVITnOzw5a
*/