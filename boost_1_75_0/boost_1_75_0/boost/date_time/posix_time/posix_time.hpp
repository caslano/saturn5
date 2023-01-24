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
ZA6eHabbA1nTUZFOWdmQEM4y6G3iTlrAp5hh0O1PqR9U8S/aUg/3iM6FD1NXYmlEgAONR6IUylxSpuXbZX8tsxd5Sb/Hkev0GgB5li1pzCyQauddsEflKYxjCMq1QSe8FyacJSXp5nyzjgIoygDLlUIGswUhS5qErmd0hp1gw4YNXOXTMlLPDSYskKQ9u0OPrPxAFEO9cpoZHz8up2C0SaLW7+rjZ9FBUpXzxoTwRgZBm7UUYWzPIXQAcH7qLyCpqtkkKkbc8AVlSmsatY4jUb8Gtbyb1iD5HmkiG5Bp7yuOCkOd+Obut+N4sy5JR+oTdJIYLlIHFHGB98no+MKtEjzHX7Wt9S9ly3rLPYVf4tiS5Yfsu75x8MJshpeEJPoh/fpQpyQk581mrZvgXzl/4OG6/PtwZa+0ezpeAggVQ+o5JO3yFEp+dRoEAVxJXGQySHY/SfHN7dhfuqpaZLY0z4fRTIBCbrT9OCLTJtkoVhnPpwnFLOyCQX9Nsg6mNRISGMS3cHb9EURpWZ/euHJxmHycrTKKySGX/r3YRG863F03h8Yz9pAgsqyeX4eN7nxQ9vXzOg9p2cgf9vycmowgHk9rBrUKd7+9J0fDS0xPibb++DoTOkq/AKqtfnd0rAE9+BpzwgsebHL2wqxuRKwCiN2NbA2F4slbriL/U6jInm4i861+2FuxOrYo47CvWjh7uV1njPdmRCl2Q5O4
*/