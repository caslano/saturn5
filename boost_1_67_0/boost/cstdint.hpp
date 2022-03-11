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
   !defined(BOOST_MSVC) && !defined(__BORLANDC__) && \
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
#  ifdef __BORLANDC__
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