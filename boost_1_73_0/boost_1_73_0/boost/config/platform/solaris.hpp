//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Jens Maurer 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  sun specific config options:

#define BOOST_PLATFORM "Sun Solaris"

#define BOOST_HAS_GETTIMEOFDAY

// boilerplate code:
#define BOOST_HAS_UNISTD_H
#include <boost/config/detail/posix_features.hpp>

//
// pthreads don't actually work with gcc unless _PTHREADS is defined:
//
#if defined(__GNUC__) && defined(_POSIX_THREADS) && !defined(_PTHREADS)
# undef BOOST_HAS_PTHREADS
#endif

#define BOOST_HAS_STDINT_H 
#define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE 
#define BOOST_HAS_LOG1P 
#define BOOST_HAS_EXPM1



/* solaris.hpp
syxXCOe6qSvgaDQ4ztqGIpH7eWPDC+wcOvmC0K4ZuWPbsXvoAstDGra+9EyMj+XkkgsXLlx15JXNBnxHzdJJx91I2yDnDdfxOunqxsCrXLz0FSODnui3FV6mUp+GkFs2uKG9ZMu8rQSH6vfwAWLrOVvp0oRwy3dkvNm/8RmocMt3SoO7jPILb7KXbdCB4IoHmN7jAM+s1FBROKDCfaACAZelHHFpXRaVnFhXa1dbtfI16eKNq5MNJ2/5kTMe2zM=
*/