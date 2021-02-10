//  (C) Copyright John Maddock 2001 - 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  cygwin specific config options:

#define BOOST_PLATFORM "Cygwin"
#define BOOST_HAS_DIRENT_H
#define BOOST_HAS_LOG1P
#define BOOST_HAS_EXPM1

//
// Threading API:
// See if we have POSIX threads, if we do use them, otherwise
// revert to native Win threads.
#define BOOST_HAS_UNISTD_H
#include <unistd.h>
#if defined(_POSIX_THREADS) && (_POSIX_THREADS+0 >= 0) && !defined(BOOST_HAS_WINTHREADS)
#  define BOOST_HAS_PTHREADS
#  define BOOST_HAS_SCHED_YIELD
#  define BOOST_HAS_GETTIMEOFDAY
#  define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
//#  define BOOST_HAS_SIGACTION
#else
#  if !defined(BOOST_HAS_WINTHREADS)
#     define BOOST_HAS_WINTHREADS
#  endif
#  define BOOST_HAS_FTIME
#endif

//
// find out if we have a stdint.h, there should be a better way to do this:
//
#include <sys/types.h>
#ifdef _STDINT_H
#define BOOST_HAS_STDINT_H
#endif
#if __GNUC__ > 5 && !defined(BOOST_HAS_STDINT_H)
#   define BOOST_HAS_STDINT_H
#endif

#include <cygwin/version.h>
#if (CYGWIN_VERSION_API_MAJOR == 0 && CYGWIN_VERSION_API_MINOR < 231)
/// Cygwin has no fenv.h
#define BOOST_NO_FENV_H
#endif

// Cygwin has it's own <pthread.h> which breaks <shared_mutex> unless the correct compiler flags are used:
#ifndef BOOST_NO_CXX14_HDR_SHARED_MUTEX
#include <pthread.h>
#if !(__XSI_VISIBLE >= 500 || __POSIX_VISIBLE >= 200112)
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif
#endif

// boilerplate code:
#include <boost/config/detail/posix_features.hpp>

//
// Cygwin lies about XSI conformance, there is no nl_types.h:
//
#ifdef BOOST_HAS_NL_TYPES_H
#  undef BOOST_HAS_NL_TYPES_H
#endif





/* cygwin.hpp
75IlUZQXQjccdSXRdXQBgXc1sp73Pz8EhLWVpyuCjVCU7WSu6pTLAksiFerXOIxmQTiJ/Mj6ifKMNTmBEx1Cq8vyo2XIMoHne5H19Cs4KFEyDJXzbFSoRNFo2R/omKr+B0N8NoqGU38S+2FgTVJsTwqVoFxp4eCsbDH43M3dQ1aOHl1JMsFzFALV4yC+QlG3ErVMbs9mjtr60khcGgvRmEFakCXlrmUZCWr3h+hgVUFXDoyLMUABHT64yMRqhTlLMyucLIWiqWkR0uFko4ItWZGMFjTTBDoGvS5o1rC0RldCiUywnuwjx1ow3Cgu+GpHqAGS8JzyJU6OZfAd6BAePG+PEIej0mSPIsDJWS5xeLGK26AxwZuS4CBhNXNa698UTLcQjIkNyZ2dYkwZSZqVaPhXQ6SxS/PczDc2vjS+ItLtNI3TPY5ArEm9pmSz3avzwt9XzOv+vJjgGuNYkaXeASiEyTSMw2E4jixPbyc8Gf3pXU3GI8vlhWWm4/SR+CinqocaokVPH/bhbwu2YsE2bRP+gKc7kCQKx8gAWqGGkzjBG64qdKFtcUM8ocHlV4h61XJoA+TTwFESXsLpqbZvqfeh22R3bM+MxS+P4jUc/8cCmB2OR9GzY+zTe/jZPSpsB/ZdfLPazwB/etgm
*/