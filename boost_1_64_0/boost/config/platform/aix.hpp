//  (C) Copyright John Maddock 2001 - 2002. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  IBM/Aix specific config options:

#define BOOST_PLATFORM "IBM Aix"

#define BOOST_HAS_UNISTD_H
#define BOOST_HAS_NL_TYPES_H
#define BOOST_HAS_NANOSLEEP
#define BOOST_HAS_CLOCK_GETTIME

// This needs support in "boost/cstdint.hpp" exactly like FreeBSD.
// This platform has header named <inttypes.h> which includes all
// the things needed.
#define BOOST_HAS_STDINT_H

// Threading API's:
#define BOOST_HAS_PTHREADS
#define BOOST_HAS_PTHREAD_DELAY_NP
#define BOOST_HAS_SCHED_YIELD
//#define BOOST_HAS_PTHREAD_YIELD

// boilerplate code:
#include <boost/config/detail/posix_features.hpp>





/* aix.hpp
7qQxdo+BAyddTlonOSzZSAoEK0oDqPhMdJ02bz24HMWCAYb/OlETDFqKgQ7HDXAYSuWXUrJSCOc+7h4u6rZnfTEQBASD5/tva7Du3wD65Y+558yjCQWcSP3GDpghg0NK/ykLOQdKk6Y2urjBcvac7ceMnVldUwYht7pr3hB/C0QNjn6PE6qZeE8AT+T4Tnkgcglykw4ouXhp5e+UbbJ14sPEY/WI3OIzkcx+9ATUjFgGMpvFJDwAJne03MjiGMB3XgKd8eJEuUH3CK+wZpL8qkAHyI5G1idUcvKF9udIsBfqL9w4jBFVOvbs6GG7+dx8q9HFNsuV3FMZZM/kvaI83aiASsWEY3zdzZ86a9JEs5WL3Xj8BptdR5ZTgq7KSP9u2KiVkpe4xhiuGOkA+Zc5hYXmUlmCBcCuRlWTEJTkj1r+nCl23Bl7qYID4t1d1yBPd41FI+h9jqy0Rt/+1PwDA0Jh5UFGGyusDcY4u4PjvbY0VuriRHOhu4M1rFS5iYm9IOk2Q5AgNsZPNJtRTYh1TmBnZwGmH5xsX8kkQWrHS23AWp8Qj7v1HPORow==
*/