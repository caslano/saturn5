//  boost cstdint.hpp header file  ------------------------------------------//

//  (C) Copyright Beman Dawes 1999.
//  (C) Copyright Jens Mauer 2001
//  (C) Copyright John Maddock 2001
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/integer for documentation.

//  Revision History
//   31 Oct 01  use BOOST_HAS_LONG_LONG to check for "long long" (Jens M.)
//   16 Apr 01  check LONGLONG_MAX when looking for "long long" (Jens Maurer)
//   23 Jan 01  prefer "long" over "int" for int32_t and intmax_t (Jens Maurer)
//   12 Nov 00  Merged <boost/stdint.h> (Jens Maurer)
//   23 Sep 00  Added INTXX_C macro support (John Maddock).
//   22 Sep 00  Better 64-bit support (John Maddock)
//   29 Jun 00  Reimplement to avoid including stdint.h within namespace boost
//    8 Aug 99  Initial version (Beman Dawes)


#ifndef BOOST_CSTDINT_HPP
#define BOOST_CSTDINT_HPP

//
// Since we always define the INT#_C macros as per C++0x,
// define __STDC_CONSTANT_MACROS so that <stdint.h> does the right
// thing if possible, and so that the user knows that the macros
// are actually defined as per C99.
//
#ifndef __STDC_CONSTANT_MACROS
#  define __STDC_CONSTANT_MACROS
#endif

#include <boost/config.hpp>
//
// For the following code we get several warnings along the lines of:
//
// boost/cstdint.hpp:428:35: error: use of C99 long long integer constant
//
// So we declare this a system header to suppress these warnings.
// See also https://github.com/boostorg/config/issues/190
//
#if defined(__GNUC__) && (__GNUC__ >= 4)
#pragma GCC system_header
#endif

//
// Note that GLIBC is a bit inconsistent about whether int64_t is defined or not
// depending upon what headers happen to have been included first...
// so we disable use of stdint.h when GLIBC does not define __GLIBC_HAVE_LONG_LONG.
// See https://svn.boost.org/trac/boost/ticket/3548 and http://sources.redhat.com/bugzilla/show_bug.cgi?id=10990
//
#if defined(BOOST_HAS_STDINT_H)            \
  && (!defined(__GLIBC__)                  \
      || defined(__GLIBC_HAVE_LONG_LONG)   \
      || (defined(__GLIBC__) && ((__GLIBC__ > 2) || ((__GLIBC__ == 2) && (__GLIBC_MINOR__ >= 17)))))

// The following #include is an implementation artifact; not part of interface.
# ifdef __hpux
// HP-UX has a vaguely nice <stdint.h> in a non-standard location
#   include <inttypes.h>
#   ifdef __STDC_32_MODE__
      // this is triggered with GCC, because it defines __cplusplus < 199707L
#     define BOOST_NO_INT64_T
#   endif
# elif defined(__FreeBSD__) || defined(__IBMCPP__) || defined(_AIX)
#   include <inttypes.h>
# else
#   include <stdint.h>

// There is a bug in Cygwin two _C macros
#   if defined(INTMAX_C) && defined(__CYGWIN__)
#     undef INTMAX_C
#     undef UINTMAX_C
#     define INTMAX_C(c) c##LL
#     define UINTMAX_C(c) c##ULL
#   endif

# endif

#if defined(__QNX__) && defined(__EXT_QNX) 

// QNX (Dinkumware stdlib) defines these as non-standard names.
// Reflect to the standard names.

typedef ::intleast8_t int_least8_t;
typedef ::intfast8_t int_fast8_t;
typedef ::uintleast8_t uint_least8_t;
typedef ::uintfast8_t uint_fast8_t;

typedef ::intleast16_t int_least16_t;
typedef ::intfast16_t int_fast16_t;
typedef ::uintleast16_t uint_least16_t;
typedef ::uintfast16_t uint_fast16_t;

typedef ::intleast32_t int_least32_t;
typedef ::intfast32_t int_fast32_t;
typedef ::uintleast32_t uint_least32_t;
typedef ::uintfast32_t uint_fast32_t;

# ifndef BOOST_NO_INT64_T

typedef ::intleast64_t int_least64_t;
typedef ::intfast64_t int_fast64_t;
typedef ::uintleast64_t uint_least64_t;
typedef ::uintfast64_t uint_fast64_t;

# endif

#endif

namespace boost
{

  using ::int8_t;
  using ::int_least8_t;
  using ::int_fast8_t;
  using ::uint8_t;
  using ::uint_least8_t;
  using ::uint_fast8_t;

  using ::int16_t;
  using ::int_least16_t;
  using ::int_fast16_t;
  using ::uint16_t;
  using ::uint_least16_t;
  using ::uint_fast16_t;

  using ::int32_t;
  using ::int_least32_t;
  using ::int_fast32_t;
  using ::uint32_t;
  using ::uint_least32_t;
  using ::uint_fast32_t;

# ifndef BOOST_NO_INT64_T

  using ::int64_t;
  using ::int_least64_t;
  using ::int_fast64_t;
  using ::uint64_t;
  using ::uint_least64_t;
  using ::uint_fast64_t;

# endif

  using ::intmax_t;
  using ::uintmax_t;

} // namespace boost

#elif defined(__FreeBSD__) && (__FreeBSD__ <= 4) || defined(__osf__) || defined(__VMS) || defined(__SOLARIS9__) || defined(__NetBSD__)
// FreeBSD and Tru64 have an <inttypes.h> that contains much of what we need.
# include <inttypes.h>

namespace boost {

  using ::int8_t;
  typedef int8_t int_least8_t;
  typedef int8_t int_fast8_t;
  using ::uint8_t;
  typedef uint8_t uint_least8_t;
  typedef uint8_t uint_fast8_t;

  using ::int16_t;
  typedef int16_t int_least16_t;
  typedef int16_t int_fast16_t;
  using ::uint16_t;
  typedef uint16_t uint_least16_t;
  typedef uint16_t uint_fast16_t;

  using ::int32_t;
  typedef int32_t int_least32_t;
  typedef int32_t int_fast32_t;
  using ::uint32_t;
  typedef uint32_t uint_least32_t;
  typedef uint32_t uint_fast32_t;

# ifndef BOOST_NO_INT64_T

  using ::int64_t;
  typedef int64_t int_least64_t;
  typedef int64_t int_fast64_t;
  using ::uint64_t;
  typedef uint64_t uint_least64_t;
  typedef uint64_t uint_fast64_t;

  typedef int64_t intmax_t;
  typedef uint64_t uintmax_t;

# else

  typedef int32_t intmax_t;
  typedef uint32_t uintmax_t;

# endif

} // namespace boost

#else  // BOOST_HAS_STDINT_H

# include <boost/limits.hpp> // implementation artifact; not part of interface
# include <limits.h>         // needed for limits macros


namespace boost
{

//  These are fairly safe guesses for some 16-bit, and most 32-bit and 64-bit
//  platforms.  For other systems, they will have to be hand tailored.
//
//  Because the fast types are assumed to be the same as the undecorated types,
//  it may be possible to hand tailor a more efficient implementation.  Such
//  an optimization may be illusionary; on the Intel x86-family 386 on, for
//  example, byte arithmetic and load/stores are as fast as "int" sized ones.

//  8-bit types  ------------------------------------------------------------//

# if UCHAR_MAX == 0xff
     typedef signed char     int8_t;
     typedef signed char     int_least8_t;
     typedef signed char     int_fast8_t;
     typedef unsigned char   uint8_t;
     typedef unsigned char   uint_least8_t;
     typedef unsigned char   uint_fast8_t;
# else
#    error defaults not correct; you must hand modify boost/cstdint.hpp
# endif

//  16-bit types  -----------------------------------------------------------//

# if USHRT_MAX == 0xffff
#  if defined(__crayx1)
     // The Cray X1 has a 16-bit short, however it is not recommend
     // for use in performance critical code.
     typedef short           int16_t;
     typedef short           int_least16_t;
     typedef int             int_fast16_t;
     typedef unsigned short  uint16_t;
     typedef unsigned short  uint_least16_t;
     typedef unsigned int    uint_fast16_t;
#  else
     typedef short           int16_t;
     typedef short           int_least16_t;
     typedef short           int_fast16_t;
     typedef unsigned short  uint16_t;
     typedef unsigned short  uint_least16_t;
     typedef unsigned short  uint_fast16_t;
#  endif
# elif (USHRT_MAX == 0xffffffff) && defined(__MTA__)
      // On MTA / XMT short is 32 bits unless the -short16 compiler flag is specified
      // MTA / XMT does support the following non-standard integer types
      typedef __short16           int16_t;
      typedef __short16           int_least16_t;
      typedef __short16           int_fast16_t;
      typedef unsigned __short16  uint16_t;
      typedef unsigned __short16  uint_least16_t;
      typedef unsigned __short16  uint_fast16_t;
# elif (USHRT_MAX == 0xffffffff) && defined(CRAY)
     // no 16-bit types on Cray:
     typedef short           int_least16_t;
     typedef short           int_fast16_t;
     typedef unsigned short  uint_least16_t;
     typedef unsigned short  uint_fast16_t;
# else
#    error defaults not correct; you must hand modify boost/cstdint.hpp
# endif

//  32-bit types  -----------------------------------------------------------//

# if UINT_MAX == 0xffffffff
     typedef int             int32_t;
     typedef int             int_least32_t;
     typedef int             int_fast32_t;
     typedef unsigned int    uint32_t;
     typedef unsigned int    uint_least32_t;
     typedef unsigned int    uint_fast32_t;
# elif (USHRT_MAX == 0xffffffff)
     typedef short             int32_t;
     typedef short             int_least32_t;
     typedef short             int_fast32_t;
     typedef unsigned short    uint32_t;
     typedef unsigned short    uint_least32_t;
     typedef unsigned short    uint_fast32_t;
# elif ULONG_MAX == 0xffffffff
     typedef long            int32_t;
     typedef long            int_least32_t;
     typedef long            int_fast32_t;
     typedef unsigned long   uint32_t;
     typedef unsigned long   uint_least32_t;
     typedef unsigned long   uint_fast32_t;
# elif (UINT_MAX == 0xffffffffffffffff) && defined(__MTA__)
      // Integers are 64 bits on the MTA / XMT
      typedef __int32           int32_t;
      typedef __int32           int_least32_t;
      typedef __int32           int_fast32_t;
      typedef unsigned __int32  uint32_t;
      typedef unsigned __int32  uint_least32_t;
      typedef unsigned __int32  uint_fast32_t;
# else
#    error defaults not correct; you must hand modify boost/cstdint.hpp
# endif

//  64-bit types + intmax_t and uintmax_t  ----------------------------------//

# if defined(BOOST_HAS_LONG_LONG) && \
   !defined(BOOST_MSVC) && !defined(BOOST_BORLANDC) && \
   (!defined(__GLIBCPP__) || defined(_GLIBCPP_USE_LONG_LONG)) && \
   (defined(ULLONG_MAX) || defined(ULONG_LONG_MAX) || defined(ULONGLONG_MAX))
#    if defined(__hpux)
     // HP-UX's value of ULONG_LONG_MAX is unusable in preprocessor expressions
#    elif (defined(ULLONG_MAX) && ULLONG_MAX == 18446744073709551615ULL) || (defined(ULONG_LONG_MAX) && ULONG_LONG_MAX == 18446744073709551615ULL) || (defined(ULONGLONG_MAX) && ULONGLONG_MAX == 18446744073709551615ULL)
                                                                 // 2**64 - 1
#    else
#       error defaults not correct; you must hand modify boost/cstdint.hpp
#    endif

     typedef  ::boost::long_long_type            intmax_t;
     typedef  ::boost::ulong_long_type   uintmax_t;
     typedef  ::boost::long_long_type            int64_t;
     typedef  ::boost::long_long_type            int_least64_t;
     typedef  ::boost::long_long_type            int_fast64_t;
     typedef  ::boost::ulong_long_type   uint64_t;
     typedef  ::boost::ulong_long_type   uint_least64_t;
     typedef  ::boost::ulong_long_type   uint_fast64_t;

# elif ULONG_MAX != 0xffffffff

#    if ULONG_MAX == 18446744073709551615 // 2**64 - 1
     typedef long                 intmax_t;
     typedef unsigned long        uintmax_t;
     typedef long                 int64_t;
     typedef long                 int_least64_t;
     typedef long                 int_fast64_t;
     typedef unsigned long        uint64_t;
     typedef unsigned long        uint_least64_t;
     typedef unsigned long        uint_fast64_t;
#    else
#       error defaults not correct; you must hand modify boost/cstdint.hpp
#    endif
# elif defined(__GNUC__) && defined(BOOST_HAS_LONG_LONG)
     __extension__ typedef long long            intmax_t;
     __extension__ typedef unsigned long long   uintmax_t;
     __extension__ typedef long long            int64_t;
     __extension__ typedef long long            int_least64_t;
     __extension__ typedef long long            int_fast64_t;
     __extension__ typedef unsigned long long   uint64_t;
     __extension__ typedef unsigned long long   uint_least64_t;
     __extension__ typedef unsigned long long   uint_fast64_t;
# elif defined(BOOST_HAS_MS_INT64)
     //
     // we have Borland/Intel/Microsoft __int64:
     //
     typedef __int64             intmax_t;
     typedef unsigned __int64    uintmax_t;
     typedef __int64             int64_t;
     typedef __int64             int_least64_t;
     typedef __int64             int_fast64_t;
     typedef unsigned __int64    uint64_t;
     typedef unsigned __int64    uint_least64_t;
     typedef unsigned __int64    uint_fast64_t;
# else // assume no 64-bit integers
#  define BOOST_NO_INT64_T
     typedef int32_t              intmax_t;
     typedef uint32_t             uintmax_t;
# endif

} // namespace boost


#endif // BOOST_HAS_STDINT_H

// intptr_t/uintptr_t are defined separately because they are optional and not universally available
#if defined(BOOST_WINDOWS) && !defined(_WIN32_WCE) && !defined(BOOST_HAS_STDINT_H)
// Older MSVC don't have stdint.h and have intptr_t/uintptr_t defined in stddef.h
#include <stddef.h>
#endif

#if (defined(BOOST_WINDOWS) && !defined(_WIN32_WCE)) \
    || (defined(_XOPEN_UNIX) && (_XOPEN_UNIX+0 > 0) && !defined(__UCLIBC__)) \
    || defined(__CYGWIN__) || defined(__VXWORKS__) \
    || defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__) \
    || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__) || (defined(sun) && !defined(BOOST_HAS_STDINT_H)) || defined(INTPTR_MAX)

namespace boost {
    using ::intptr_t;
    using ::uintptr_t;
}
#define BOOST_HAS_INTPTR_T

// Clang pretends to be GCC, so it'll match this condition
#elif defined(__GNUC__) && defined(__INTPTR_TYPE__) && defined(__UINTPTR_TYPE__)

namespace boost {
    typedef __INTPTR_TYPE__ intptr_t;
    typedef __UINTPTR_TYPE__ uintptr_t;
}
#define BOOST_HAS_INTPTR_T

#endif

#endif // BOOST_CSTDINT_HPP


/****************************************************

Macro definition section:

Added 23rd September 2000 (John Maddock).
Modified 11th September 2001 to be excluded when
BOOST_HAS_STDINT_H is defined (John Maddock).
Modified 11th Dec 2009 to always define the
INT#_C macros if they're not already defined (John Maddock).

******************************************************/

#if !defined(BOOST__STDC_CONSTANT_MACROS_DEFINED) && \
   (!defined(INT8_C) || !defined(INT16_C) || !defined(INT32_C) || !defined(INT64_C))
//
// Undef the macros as a precaution, since we may get here if <stdint.h> has failed
// to define them all, see https://svn.boost.org/trac/boost/ticket/12786
//
#undef INT8_C
#undef INT16_C
#undef INT32_C
#undef INT64_C
#undef INTMAX_C
#undef UINT8_C
#undef UINT16_C
#undef UINT32_C
#undef UINT64_C
#undef UINTMAX_C

#include <limits.h>
# define BOOST__STDC_CONSTANT_MACROS_DEFINED
# if defined(BOOST_HAS_MS_INT64)
//
// Borland/Intel/Microsoft compilers have width specific suffixes:
//
#ifndef INT8_C
#  define INT8_C(value)     value##i8
#endif
#ifndef INT16_C
#  define INT16_C(value)    value##i16
#endif
#ifndef INT32_C
#  define INT32_C(value)    value##i32
#endif
#ifndef INT64_C
#  define INT64_C(value)    value##i64
#endif
#  ifdef BOOST_BORLANDC
    // Borland bug: appending ui8 makes the type a signed char
#   define UINT8_C(value)    static_cast<unsigned char>(value##u)
#  else
#   define UINT8_C(value)    value##ui8
#  endif
#ifndef UINT16_C
#  define UINT16_C(value)   value##ui16
#endif
#ifndef UINT32_C
#  define UINT32_C(value)   value##ui32
#endif
#ifndef UINT64_C
#  define UINT64_C(value)   value##ui64
#endif
#ifndef INTMAX_C
#  define INTMAX_C(value)   value##i64
#  define UINTMAX_C(value)  value##ui64
#endif

# else
//  do it the old fashioned way:

//  8-bit types  ------------------------------------------------------------//

#  if (UCHAR_MAX == 0xff) && !defined(INT8_C)
#   define INT8_C(value) static_cast<boost::int8_t>(value)
#   define UINT8_C(value) static_cast<boost::uint8_t>(value##u)
#  endif

//  16-bit types  -----------------------------------------------------------//

#  if (USHRT_MAX == 0xffff) && !defined(INT16_C)
#   define INT16_C(value) static_cast<boost::int16_t>(value)
#   define UINT16_C(value) static_cast<boost::uint16_t>(value##u)
#  endif

//  32-bit types  -----------------------------------------------------------//
#ifndef INT32_C
#  if (UINT_MAX == 0xffffffff)
#   define INT32_C(value) value
#   define UINT32_C(value) value##u
#  elif ULONG_MAX == 0xffffffff
#   define INT32_C(value) value##L
#   define UINT32_C(value) value##uL
#  endif
#endif

//  64-bit types + intmax_t and uintmax_t  ----------------------------------//
#ifndef INT64_C
#  if defined(BOOST_HAS_LONG_LONG) && \
    (defined(ULLONG_MAX) || defined(ULONG_LONG_MAX) || defined(ULONGLONG_MAX) || defined(_ULLONG_MAX) || defined(_LLONG_MAX))

#    if defined(__hpux)
        // HP-UX's value of ULONG_LONG_MAX is unusable in preprocessor expressions
#       define INT64_C(value) value##LL
#       define UINT64_C(value) value##uLL
#    elif (defined(ULLONG_MAX) && ULLONG_MAX == 18446744073709551615ULL) ||  \
        (defined(ULONG_LONG_MAX) && ULONG_LONG_MAX == 18446744073709551615ULL) ||  \
        (defined(ULONGLONG_MAX) && ULONGLONG_MAX == 18446744073709551615ULL) || \
        (defined(_ULLONG_MAX) && _ULLONG_MAX == 18446744073709551615ULL) || \
        (defined(_LLONG_MAX) && _LLONG_MAX == 9223372036854775807LL)

#       define INT64_C(value) value##LL
#       define UINT64_C(value) value##uLL
#    else
#       error defaults not correct; you must hand modify boost/cstdint.hpp
#    endif
#  elif ULONG_MAX != 0xffffffff

#    if ULONG_MAX == 18446744073709551615U // 2**64 - 1
#       define INT64_C(value) value##L
#       define UINT64_C(value) value##uL
#    else
#       error defaults not correct; you must hand modify boost/cstdint.hpp
#    endif
#  elif defined(BOOST_HAS_LONG_LONG)
     // Usual macros not defined, work things out for ourselves:
#    if(~0uLL == 18446744073709551615ULL)
#       define INT64_C(value) value##LL
#       define UINT64_C(value) value##uLL
#    else
#       error defaults not correct; you must hand modify boost/cstdint.hpp
#    endif
#  else
#    error defaults not correct; you must hand modify boost/cstdint.hpp
#  endif

#  ifdef BOOST_NO_INT64_T
#   define INTMAX_C(value) INT32_C(value)
#   define UINTMAX_C(value) UINT32_C(value)
#  else
#   define INTMAX_C(value) INT64_C(value)
#   define UINTMAX_C(value) UINT64_C(value)
#  endif
#endif
# endif // Borland/Microsoft specific width suffixes

#endif // INT#_C macros.





/* cstdint.hpp
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
*/