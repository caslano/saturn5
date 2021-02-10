#ifndef GREGORIAN_HPP__
#define GREGORIAN_HPP__

/* Copyright (c) 2002-2004 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst 
 * $Date$
 */

/*! @file gregorian.hpp
  Single file header that provides overall include for all elements of 
  the gregorian date-time system.  This includes the various types 
  defined, but also other functions for formatting and parsing.
*/


#include "boost/date_time/compiler_config.hpp"
#include "boost/date_time/gregorian/gregorian_types.hpp"
#include "boost/date_time/gregorian/conversion.hpp"
#if defined(BOOST_DATE_TIME_INCLUDE_LIMITED_HEADERS)
#include "boost/date_time/gregorian/formatters_limited.hpp"
#else
#include "boost/date_time/gregorian/formatters.hpp"
#endif

#if defined(USE_DATE_TIME_PRE_1_33_FACET_IO)
#include "boost/date_time/gregorian/greg_facet.hpp"
#else
#include "boost/date_time/gregorian/gregorian_io.hpp"
#endif // USE_DATE_TIME_PRE_1_33_FACET_IO

#include "boost/date_time/gregorian/parsers.hpp"



#endif

/* gregorian.hpp
ysPARmHuvUqxnyGL277MY/IPcUtuV+ldePPA+zgP5umKRD1vtCj6/4j+cGJbRbaMdqmVslGWJbKnbuGny0UIF16w9MmCaeyJypbnZ9E58NK6GrGqrm2FxK7Wd9reZRmeh9FlmEX20Bj3RugeeJT4PnhBEmEL+Lh4WHGSBBf+IjHeo/GbCZK3R0b25CP5F1BLAwQKAAAACAAtZ0pSr5fZTwYFAAAGCwAANgAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfSFRUUDIwMEFMSUFTRVMuM1VUBQABtkgkYK1WXU/jRhR996+4Sl8I8jphqUTpfqheCMUlG0dxsjRSJGtij/G0E9vyjIGo2//eM2MHCMt292GDiM3M/Zpzzz2Dt+rR4Q/7OJ4JR9/8xPY3xgfPndO0Lv/iiX7ZIY4/U/sDxxWe35FqQI9en+M+fZfXZzqwXnGX6615j+PvSLcyRZqvgXFexeYVK61n539WVtta3OSaDs76dHR6+gu9otfDoxOXzlkhuKRI82LN6xuX3qZ25bec3d97ir93iWti0tsLOM+FIlVm+o7VnPAuRcILxVNiilKuklqs8YcoSOecMiE5nYXTZTD53aW7XCR5F2dbNqTyspEp5eyWU80TLm7b
*/