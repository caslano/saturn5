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
B1sxkx1YqM6wUCkwUVWXHIgFYyb7sJFTlUdpUGYYL8dqLPk/yt4yKastZjKK1md2FmjNRP0f4ehops1o15jp7a+ZWrdmMF1Y+1919XdMkw6zDicDde9guJnVN30O0nEs0mZZFp+7xawenspMh/1nFVUW5elMZHQBptoN8cywd9FB9RqWYM0VTF7WWdW9WHpqHeiJ1mNWXy9k9k4sZFrpqRWz9+AKVnXxMia0jVJWuJgZ7jRgKhZszVKMIcaysSNrwGis6opM1lsSD5jZZQ0BiFU9mDVCvBbM6i8OoDFYdhEsYobhLGhrRUxVxP+rLsGq7syqzsfiXYbFe+ZB9USWaomWTKsmsqrTWAN67EBU0B0mNHoak5l41nibs8w49t/hwiziEMxwRDRTllCWLJFmB445cHoASxYSCxqapeqNg+ro68zqKJYs+8+Z6a9Z1ZUOiIO/Yooe9ppVPZtV/SWr+u2D6hAWMzEsWe6z7IpjMePzX3oUKz2elZ7PTKeIMh35+SDM4GD2vivNcmQYixkFJu8h/w0xkTUMcBbviSzocNasBP+XLsMiVoiV7sFK12Gm/+U9wCbDcuQuqzle1opAs5rzOwjDDVnEHlhOhGm5gOdMbLrFB5bDsbYug2UaUBnTNGYsT4HeHZx+jNm8jL8pk7ppk+i+iyvKJpMAOLcsriSmJ9elw/o0VgZZ+aJM5s0FmNg1DppHmDJPb2UN
*/