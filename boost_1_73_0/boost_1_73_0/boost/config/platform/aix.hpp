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
VG6OcnXK3a7cXcrVK7dCuQblXlVui3Lblduj3JfK0avb5fJ9HlepXJVy05W7Xrm4cvOVe0q5Z5V7Q7m/Kfetct8rB38h4QK2x/2kHL0FXO5Ix+OOUm6wcmXKRZWrVm6yctOUm6vcLcrdq9z9yj2n3Erl/qHcfuXwmxEu6Pe4z3IMr/0aQmIdLrVHyhxe4iCEJDlcao+0Lm7bIQGv7WXKjVYumqgo6nL+hRe5Tp74XMg8mHNX9G+oSr4fTb6ZmFc=
*/