//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Jens Maurer 2001 - 2003. 
//  (C) Copyright David Abrahams 2002. 
//  (C) Copyright Toon Knapen 2003. 
//  (C) Copyright Boris Gubenko 2006 - 2007.
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  hpux specific config options:

#define BOOST_PLATFORM "HP-UX"

// In principle, HP-UX has a nice <stdint.h> under the name <inttypes.h>
// However, it has the following problem:
// Use of UINT32_C(0) results in "0u l" for the preprocessed source
// (verifyable with gcc 2.95.3)
#if (defined(__GNUC__) && (__GNUC__ >= 3)) || defined(__HP_aCC)
#  define BOOST_HAS_STDINT_H
#endif

#if !(defined(__HP_aCC) || !defined(_INCLUDE__STDC_A1_SOURCE))
#  define BOOST_NO_SWPRINTF
#endif
#if defined(__HP_aCC) && !defined(_INCLUDE__STDC_A1_SOURCE)
#  define BOOST_NO_CWCTYPE
#endif

#if defined(__GNUC__)
#  if (__GNUC__ < 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ < 3))
      // GNU C on HP-UX does not support threads (checked up to gcc 3.3)
#     define BOOST_DISABLE_THREADS
#  elif !defined(BOOST_DISABLE_THREADS)
      // threads supported from gcc-3.3 onwards:
#     define BOOST_HAS_THREADS
#     define BOOST_HAS_PTHREADS
#  endif
#elif defined(__HP_aCC) && !defined(BOOST_DISABLE_THREADS)
#  define BOOST_HAS_PTHREADS
#endif

// boilerplate code:
#define BOOST_HAS_UNISTD_H
#include <boost/config/detail/posix_features.hpp>

// the following are always available:
#ifndef BOOST_HAS_GETTIMEOFDAY
#  define BOOST_HAS_GETTIMEOFDAY
#endif
#ifndef BOOST_HAS_SCHED_YIELD
#    define BOOST_HAS_SCHED_YIELD
#endif
#ifndef BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
#    define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
#endif
#ifndef BOOST_HAS_NL_TYPES_H
#    define BOOST_HAS_NL_TYPES_H
#endif
#ifndef BOOST_HAS_NANOSLEEP
#    define BOOST_HAS_NANOSLEEP
#endif
#ifndef BOOST_HAS_GETTIMEOFDAY
#    define BOOST_HAS_GETTIMEOFDAY
#endif
#ifndef BOOST_HAS_DIRENT_H
#    define BOOST_HAS_DIRENT_H
#endif
#ifndef BOOST_HAS_CLOCK_GETTIME
#    define BOOST_HAS_CLOCK_GETTIME
#endif
#ifndef BOOST_HAS_SIGACTION
#  define BOOST_HAS_SIGACTION
#endif
#ifndef BOOST_HAS_NRVO 
#  ifndef __parisc
#    define BOOST_HAS_NRVO
#  endif
#endif
#ifndef BOOST_HAS_LOG1P 
#  define BOOST_HAS_LOG1P
#endif
#ifndef BOOST_HAS_EXPM1
#  define BOOST_HAS_EXPM1
#endif


/* hpux.hpp
UV66CE9AEbGRrRntRMIkh2SbUJasEC5RUChVyQ+DQVoLhpEMMp7KQdqlwi3U5j9RLdCbTXILvFKgONSSOKDlHdjwjOZ6xRThZlWvGJWFc+8WApbZgAuQhLHWHKpSIpsQCIRtthwtCRV6T5VeJC+lRrsu+OaRIKa1NZTXokQ4TAvKZRwT70BdZkQYeZOIDqXNskn5D0p273sGvESvwPZC8EMbVomk0oErPzoLLiO48uZzbxotIBiDN1209s796SlygyKqAHJTCSLRCwF0UzFKskfgP7XTLTc6g+HlfOJPx0E8m48i9C4cj+Zx5F+M4gjegv3mPXiVMEy3wWZ0pTkAv7nvjtxD3NBPMUnkbbwmipY51yVHZkk0Hp7B1LsYWS8hLA8AFZvs0w3BYijK7qmuRFLKHNMiFXLYmAwX02AW+qH1Cy1TVmcEjrUTDTeLT5aBSznuP/Gtp49gv0DaMGTPC345jTLP81jBvvas6n808KejcDj3Z5EfTK1ZgoVKoOK0VJpC2DUP9fC57cJdfI5u5A1NBZck5WUmHYtqQf435KJhrWVCfTYRSLevtcQ5suK1gViRNTWNjCdtRtApbB3k0cFOLeWbDYYtTcuUZM0VTUydEAIbXBNZViSlOU21UY2rpwZNa5YINMUVTznr
*/