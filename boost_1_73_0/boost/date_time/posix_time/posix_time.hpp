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
wN/AkXAnHAV3wVPgy3As/BieDlMDtDeYA8+GbeE5sDecBvvCTDgAZsMhah4Fi+BMeBoshVfBRWr/HTX/GJbArXAG3A5L4TOwDO6Ec+Ef1PwmrIIO5VUDU2AtjMKFMAcugs3hYlgAl8C2cClsBy+AneCFsAgug8PhcjgHroBl8GK4EJbA78LL4BZ4OXwUXgGfgldlHNn7jte0ybwJm8K3zJG9X3lH/b0LZU+m+utq173iXv0F
*/