//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Jens Maurer 2001 - 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  linux specific config options:

#define BOOST_PLATFORM "linux"

// make sure we have __GLIBC_PREREQ if available at all
#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif

//
// <stdint.h> added to glibc 2.1.1
// We can only test for 2.1 though:
//
#if defined(__GLIBC__) && ((__GLIBC__ > 2) || ((__GLIBC__ == 2) && (__GLIBC_MINOR__ >= 1)))
   // <stdint.h> defines int64_t unconditionally, but <sys/types.h> defines
   // int64_t only if __GNUC__.  Thus, assume a fully usable <stdint.h>
   // only when using GCC.  Update 2017: this appears not to be the case for
   // recent glibc releases, see bug report: https://svn.boost.org/trac/boost/ticket/13045
#  if defined(__GNUC__) || ((__GLIBC__ > 2) || ((__GLIBC__ == 2) && (__GLIBC_MINOR__ >= 5)))
#    define BOOST_HAS_STDINT_H
#  endif
#endif

#if defined(__LIBCOMO__)
   //
   // como on linux doesn't have std:: c functions:
   // NOTE: versions of libcomo prior to beta28 have octal version numbering,
   // e.g. version 25 is 21 (dec)
   //
#  if __LIBCOMO_VERSION__ <= 20
#    define BOOST_NO_STDC_NAMESPACE
#  endif

#  if __LIBCOMO_VERSION__ <= 21
#    define BOOST_NO_SWPRINTF
#  endif

#endif

//
// If glibc is past version 2 then we definitely have
// gettimeofday, earlier versions may or may not have it:
//
#if defined(__GLIBC__) && (__GLIBC__ >= 2)
#  define BOOST_HAS_GETTIMEOFDAY
#endif

#ifdef __USE_POSIX199309
#  define BOOST_HAS_NANOSLEEP
#endif

#if defined(__GLIBC__) && defined(__GLIBC_PREREQ)
// __GLIBC_PREREQ is available since 2.1.2

   // swprintf is available since glibc 2.2.0
#  if !__GLIBC_PREREQ(2,2) || (!defined(__USE_ISOC99) && !defined(__USE_UNIX98))
#    define BOOST_NO_SWPRINTF
#  endif
#else
#  define BOOST_NO_SWPRINTF
#endif

// boilerplate code:
#define BOOST_HAS_UNISTD_H
#include <boost/config/detail/posix_features.hpp>
#if defined(__USE_GNU) && !defined(__ANDROID__) && !defined(ANDROID)
#define BOOST_HAS_PTHREAD_YIELD
#endif

#ifndef __GNUC__
//
// if the compiler is not gcc we still need to be able to parse
// the GNU system headers, some of which (mainly <stdint.h>)
// use GNU specific extensions:
//
#  ifndef __extension__
#     define __extension__
#  endif
#  ifndef __const__
#     define __const__ const
#  endif
#  ifndef __volatile__
#     define __volatile__ volatile
#  endif
#  ifndef __signed__
#     define __signed__ signed
#  endif
#  ifndef __typeof__
#     define __typeof__ typeof
#  endif
#  ifndef __inline__
#     define __inline__ inline
#  endif
#endif



/* linux.hpp
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
*/