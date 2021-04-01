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
xgPRnb8uRQ8jXZktKDLBqBkSajbYowVmfmpeFOpeTIe9uferZMmvsuYDkz8U9ab/XwjFAd/al1XFN0V4ypht9Crbbx4SEeiNwPfRm8jpDpthg80bQ2FY5OPMWIuaotw7RNsa/JpVU/7zE5cuVb8h767lofHJ8M2bdfJSnPADX3ZXH48wu7gk3Y5nFAIwZLT0zri2h8OX9FT7H8uA4mRfIZMql3E0A13870bpMinR3cMPDE7ZqBe4LPtSLEU4HJkYr3zmgMzyiG71Vyt9XmmScjwmdpbjt2eeWzV7Ewc9hG/uEVGx71AkWkFiCeQuJm85o+z6I2bPmVYbTjOFB09k3SwjtuT6LF6+BWKH3MsaO4uH0PG8hZyMzEMRJm/nmDGaVp8rNzwGU7Kz0VDEAkR8zU5eNiYlkx6jQ+s8LN7w3hePQAYkdEEOvoOaQ9ePDYFaNOuHvpppqXAcpiRhdbEB8fPQYYhVWqqJ/wU8V/3Osy2fagHvUk4RHt5QThAnBa39i0zzbYj+OCsF3kzrm1ndK1bTOC5sLLp68eYfEZhLarmpsSNM4GnGk7FmLQ==
*/