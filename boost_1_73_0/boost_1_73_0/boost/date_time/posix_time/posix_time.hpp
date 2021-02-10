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
LW2fCJAovMSn/EHzFWpSFBOBkecYcJLSCEdHjEem4OlDgWZ8Lp7NfdwPdpNXGCbgOTTpINjDcklXL0SC7SABTyFhza7x+IQdM0oFx1Yu7qsgyme6xR6RCN1sQ/jqmCB87maHo54/Cr8M/Ku+d/bZYz2tCwxKZQeUoPVV33VVK3TWPrLBEsntT8rtYjHNeSwc6BmrIrHbM1uvcJupZSri6UbtlwmALhYLlaPtyiqOG24Lli85QloCUQfANhpBrGoVa81gP+Q5Qoij2cK4AeujRlyuHIwSpD6qZ/xW7GB28jxmXbYp+fo1SkKAJCNs7B5iO2Z5IXO0vOYFr1hUNUobfpfFiFNk0hUdV6BMcb2powT078Bm30QPSJ5MGUC8I5EUabpisVpmFn4yg1TB8Zrv9NdkE/dYCU0ErPCvgsEWR2Sbq5zWLKy3CcZV2Hu12VWYd6s5geZwpCcizxGNjSmn1VxQ/5oynBTojJaZVGzdOyVQZNiEZH333XUsd5KDm5qD4C564yC0glVFT4PO7Y+Dy9Nmdw9L3qkm2yf3oj9mgSR71Sx/feR03jxXzuyjSChFAvQpIWqSZHk48sf+qY8a9NgeeX+7X4d9jzlZwspJbB2+35jTMpOmiVNXJk063IP/GMB6nufCvMXfj8Y6
*/