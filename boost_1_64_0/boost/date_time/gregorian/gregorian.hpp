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
YxHxDEOPd/PoRBEjAHFu9ABsjOnevYcMuKOyJELNZfk568LetEevqeJ83g2r6aj9ffXWerBo8OZcykj7CmCLSO9u1Zgga092unzTizEQ1sMYptOQ0kML69b3LAyWcaVpZr7wQlacQESFBl70A3SLGLzuW72R8K09XfqwuwAP1gc/9VvCNpo8zsoHaM19Xpu/UjIRjdLREQfkvg8ol3LQhjv8VEDFODvJ8PBSIEubGk2YYkoAGHlNXfSkT/L7I0r7r8G8Hfg/dr8X3Z+ibSmft0lWQy9FxHat+QK487xSoyncYq0ie/FYI19pcb/hEHupyvURmA7Ouul0rDCYo7109nDuVx2C7fNs40ABXGsEr1B6cKx2Gs1WS4dLkpiaVwBXTiEluKWq+pPGDcr6o+JIRHaguZdxKxWsTPt0YaCw1NAPauDOYSyqnuhu3ybh9cNyG6aRQ7iq7SIjk8fF72KUd28jIWls5HLVhLi7rQDLPSqZwRLDk+jZd/wXn3/HIN7H8fUADhDh27D8nXYxZ5OlHutKN/y8nTo81IsVA+IlJqsv6yVraiix8F1fKA==
*/