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
aXYHdCoXQmtBMUB3PYehs+K7kBvZ6zd5gad4z2xyvo8wJpEgMptG3rsZh3Q0J0+Oob0RFwmbPmlIMfPQM78R9F2gOx3dm2DiLl/8NoaudmigDcRfVo3l56e2zOEb8jb9OotjkI4+b6wnF29D+Mn18FlTTX3YCy4MeRTgDBRrtVM9T3m0SgYoj3SodoORYXzA6bzA67NRGZoMok8ZfBZRUo33XLRdhrXWvdxvxVXZDeYxEiwnSZJz90yUdiWiAJGG3mWAQaG1bpH+effMwUSPNxaTi0HfjOjVSmyAI5RMwHVY6YsEsh/j8cBZmR0giNJY+rVnJJIYINqYi9xIBKxBd5x7OgBjHIOiQFKV0I1UUpQQCE8hyMpgZQB6ZDelBmAdJuBdxqc0MlX/ObIAsxn8FbRbQQZsY+MHGKYfeyebgJq1daeLl1Tvqoe2Z8HzELyWkzS+YmqLN27ysu5I+bj1JCmbbwDWeb96ifKbfB54kgF6E5Te9tsAbda57vtBwLxQlO6Z8rw8nD3mz1nQU8ANPi5p5P3LRA4x/N6TV0CzBrJhnUOEW6sU3FHAlPwQZ40PxENA665ZSDH0BYCNewx9KpaUCXjIKQ8pBqF2DizOKE2aghMFXQEtO3cvrXrQxUZVsNwlaeTI0xiskLiwBHmv8PdyaIqzVaL6SQBhNOOxo+AGba2oehfymexXy/m39ifFn16Zi5xTEhrbwppG
*/