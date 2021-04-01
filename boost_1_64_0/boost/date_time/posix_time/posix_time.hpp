#ifndef POSIX_TIME_HPP___
#define POSIX_TIME_HPP___

/* Copyright (c) 2002-2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst 
 * $Date$
 */
/*!@file posix_time.hpp Global header file to get all of posix time types 
 */

#include "boost/date_time/compiler_config.hpp"
#include "boost/date_time/posix_time/ptime.hpp"
#if defined(BOOST_DATE_TIME_OPTIONAL_GREGORIAN_TYPES)
#include "boost/date_time/posix_time/date_duration_operators.hpp"
#endif

// output functions
#if defined(BOOST_DATE_TIME_INCLUDE_LIMITED_HEADERS)
#include "boost/date_time/posix_time/time_formatters_limited.hpp"
#else
#include "boost/date_time/posix_time/time_formatters.hpp"
#endif // BOOST_DATE_TIME_INCLUDE_LIMITED_HEADERS

// streaming operators
#if defined(USE_DATE_TIME_PRE_1_33_FACET_IO)
#include "boost/date_time/posix_time/posix_time_legacy_io.hpp"
#else
#include "boost/date_time/posix_time/posix_time_io.hpp"
#endif // USE_DATE_TIME_PRE_1_33_FACET_IO

#include "boost/date_time/posix_time/time_parsers.hpp"
#include "boost/date_time/posix_time/conversion.hpp"


#endif


/* posix_time.hpp
0JqXbqv0gwtp2PCkBOPVnqYVTjn/dbve8yB3tzxljqI6L8s42oT8l+hIszMVsU9kqB0htIBjqrijwbFeWZClMaCrttbfNVxw9V2b+IlFFYLmma+W1UfoGKG2T4xycVmmI/xLizvzWhBuF41gUnCI0lZpbS395D4rJkzO+lp4xg0jtkREH1r60YSune7RMJDl/5pb55dbuGJeMCr+qk7J8KVBRU1qh327boPS05R2fLin1LCQh+OPWI2M1xx1Z8tJ+BBbbw36gC9t3yuTYrs/S6DKI+crfo+K0oROMy2Xptzg5XeU+gzC+zcuPGHxvXjq0d95Uh8B2wKWsWhKLmsJQoZ43n9lFqy82LNrvUvBn7PYEwhIOZFiPQpcBz1b7RGj705F6g4UPKUPx3nCgNzk6gCM3t7K12Lz2zc+LpNJgl7R4NPg/Ge4KYNW6Q3WTUHlGHlBaNhRm829gIdiKhly5Y+eZLt0JS4ST8DO/XJqVcR/8nqitiqkNoAk2AICM2g4PxLagOrPdmaqTOTGSuXW+dYtBlpJY0SUapOjr04f+gfJPC8AOYRPQsv6bQ==
*/