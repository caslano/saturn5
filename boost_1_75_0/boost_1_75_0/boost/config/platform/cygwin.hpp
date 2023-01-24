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
OObXgnDhAzM4U18DRl0Y3xDP8X/FNYbz4Eb8rSIEvMSiMWc68W8xmfuYKgjDBpq7u5I+tVzwZ3Jtm7ZJEvMp6kjZz1kxZwTSi+BhPlfHwrZTIx+trI0MWW4JWG10RAq4ay05lM4Y7JwyidrSjWWUO/NY6D7ZFH/52lrXfZPBNXRswMxggIFx0k4zNmxFPEF3iKXJye/DeRbL7fUGtF8dozxokcXa7Q3q+A6ntZ+t2O7T8ZhNC5PfX3JsXU8jfijF46C6Fgm2e+hz3RaRUycZsSriF2Xk93kHwr9uur9dYLwcOjIwV53GgAyEF9o7+8HvLLMtaYJlUVv5nkFpuQr7S2HdemntChsxzmrWc95+cHZpk9BmqXx0ytKbrcjYOezS1cKzzZ9JIuD9i+LNfxk18q/MrHc0rPchL2WLtWeyR8MO9xhM+WwycuSPpBHkN3z6/K+3TmSPyiHy7c1DU7/QRcE8F2MUNj87P7VM0LBe8ooC+qEpbHYokJ75z5xMDF+mXlxazCDBjJf11EgSWksMXgBAJniGcZH0bOvXWtpcMICvtuFvJo5WUT6Tl28Ev5lxZECkwXqFkjokOGBnCMb27Q5tW/DYLTAahsQHeMGjJDGTNP+hBUin0+/LS83yMIaeWEn4THGwCpPs+5cKdqGRlju2M4zzpFj/Vrn0gkXkjAXPgz34OeB3wxeHp/U3mYSIf3pS1jGcbsSAQDst
*/