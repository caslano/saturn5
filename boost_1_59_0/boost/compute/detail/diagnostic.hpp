//---------------------------------------------------------------------------//
// Copyright (c) 2016 Jakub Szuppe <j.szuppe@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_DIAGNOSTIC_HPP
#define BOOST_COMPUTE_DETAIL_DIAGNOSTIC_HPP

// Macros for suppressing warnings for GCC version 4.6 or later. Usage:
//
//   BOOST_COMPUTE_BOOST_COMPUTE_GCC_DIAG_OFF(sign-compare);
//   if(a < b){
//   BOOST_COMPUTE_BOOST_COMPUTE_GCC_DIAG_ON(sign-compare);
//
// Source: https://svn.boost.org/trac/boost/wiki/Guidelines/WarningsGuidelines
#if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 402
#define BOOST_COMPUTE_GCC_DIAG_STR(s) #s
#define BOOST_COMPUTE_GCC_DIAG_JOINSTR(x,y) BOOST_COMPUTE_GCC_DIAG_STR(x ## y)
# define BOOST_COMPUTE_GCC_DIAG_DO_PRAGMA(x) _Pragma (#x)
# define BOOST_COMPUTE_GCC_DIAG_PRAGMA(x) BOOST_COMPUTE_GCC_DIAG_DO_PRAGMA(GCC diagnostic x)
# if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 406
#  define BOOST_COMPUTE_GCC_DIAG_OFF(x) BOOST_COMPUTE_GCC_DIAG_PRAGMA(push) \
      BOOST_COMPUTE_GCC_DIAG_PRAGMA(ignored BOOST_COMPUTE_GCC_DIAG_JOINSTR(-W,x))
#  define BOOST_COMPUTE_GCC_DIAG_ON(x) BOOST_COMPUTE_GCC_DIAG_PRAGMA(pop)
# else
#  define BOOST_COMPUTE_GCC_DIAG_OFF(x) \
      BOOST_COMPUTE_GCC_DIAG_PRAGMA(ignored BOOST_COMPUTE_GCC_DIAG_JOINSTR(-W,x))
#  define BOOST_COMPUTE_GCC_DIAG_ON(x) \
      BOOST_COMPUTE_GCC_DIAG_PRAGMA(warning BOOST_COMPUTE_GCC_DIAG_JOINSTR(-W,x))
# endif
#else // Ensure these macros do nothing for other compilers.
# define BOOST_COMPUTE_GCC_DIAG_OFF(x)
# define BOOST_COMPUTE_GCC_DIAG_ON(x)
#endif

// Macros for suppressing warnings for Clang.
//
//   BOOST_COMPUTE_BOOST_COMPUTE_CLANG_DIAG_OFF(sign-compare);
//   if(a < b){
//   BOOST_COMPUTE_BOOST_COMPUTE_CLANG_DIAG_ON(sign-compare);
//
// Source: https://svn.boost.org/trac/boost/wiki/Guidelines/WarningsGuidelines
#ifdef __clang__
#  define BOOST_COMPUTE_CLANG_DIAG_STR(s) # s
// stringize s to "no-sign-compare"
#  define BOOST_COMPUTE_CLANG_DIAG_JOINSTR(x,y) BOOST_COMPUTE_CLANG_DIAG_STR(x ## y)
//  join -W with no-unused-variable to "-Wno-sign-compare"
#  define BOOST_COMPUTE_CLANG_DIAG_DO_PRAGMA(x) _Pragma (#x)
// _Pragma is unary operator  #pragma ("")
#  define BOOST_COMPUTE_CLANG_DIAG_PRAGMA(x) \
      BOOST_COMPUTE_CLANG_DIAG_DO_PRAGMA(clang diagnostic x)
#  define BOOST_COMPUTE_CLANG_DIAG_OFF(x) BOOST_COMPUTE_CLANG_DIAG_PRAGMA(push) \
      BOOST_COMPUTE_CLANG_DIAG_PRAGMA(ignored BOOST_COMPUTE_CLANG_DIAG_JOINSTR(-W,x))
// For example: #pragma clang diagnostic ignored "-Wno-sign-compare"
#  define BOOST_COMPUTE_CLANG_DIAG_ON(x) BOOST_COMPUTE_CLANG_DIAG_PRAGMA(pop)
// For example: #pragma clang diagnostic warning "-Wno-sign-compare"
#else // Ensure these macros do nothing for other compilers.
#  define BOOST_COMPUTE_CLANG_DIAG_OFF(x)
#  define BOOST_COMPUTE_CLANG_DIAG_ON(x)
#  define BOOST_COMPUTE_CLANG_DIAG_PRAGMA(x)
#endif

// Macros for suppressing warnings for MSVC. Usage:
//
//   BOOST_COMPUTE_BOOST_COMPUTE_MSVC_DIAG_OFF(4018); //sign-compare
//   if(a < b){
//   BOOST_COMPUTE_BOOST_COMPUTE_MSVC_DIAG_ON(4018);
//
#if defined(_MSC_VER)
#  define BOOST_COMPUTE_MSVC_DIAG_DO_PRAGMA(x) __pragma(x)
#  define BOOST_COMPUTE_MSVC_DIAG_PRAGMA(x) \
          BOOST_COMPUTE_MSVC_DIAG_DO_PRAGMA(warning(x))
#  define BOOST_COMPUTE_MSVC_DIAG_OFF(x) BOOST_COMPUTE_MSVC_DIAG_PRAGMA(push) \
          BOOST_COMPUTE_MSVC_DIAG_PRAGMA(disable: x)
#  define BOOST_COMPUTE_MSVC_DIAG_ON(x) BOOST_COMPUTE_MSVC_DIAG_PRAGMA(pop)
#else // Ensure these macros do nothing for other compilers.
#  define BOOST_COMPUTE_MSVC_DIAG_OFF(x)
#  define BOOST_COMPUTE_MSVC_DIAG_ON(x)
#endif

// Macros for suppressing warnings for GCC, Clang and MSVC. Usage:
//
//   BOOST_COMPUTE_DIAG_OFF(sign-compare, sign-compare, 4018);
//   if(a < b){
//   BOOST_COMPUTE_DIAG_ON(sign-compare, sign-compare, 4018);
//
#if defined(_MSC_VER) // MSVC
#  define BOOST_COMPUTE_DIAG_OFF(gcc, clang, msvc) BOOST_COMPUTE_MSVC_DIAG_OFF(msvc)
#  define BOOST_COMPUTE_DIAG_ON(gcc, clang, msvc) BOOST_COMPUTE_MSVC_DIAG_ON(msvc)
#elif defined(__clang__) // Clang
#  define BOOST_COMPUTE_DIAG_OFF(gcc, clang, msvc) BOOST_COMPUTE_CLANG_DIAG_OFF(clang)
#  define BOOST_COMPUTE_DIAG_ON(gcc, clang, msvc) BOOST_COMPUTE_CLANG_DIAG_ON(clang)
#elif defined(__GNUC__) // GCC/G++
#  define BOOST_COMPUTE_DIAG_OFF(gcc, clang, msvc) BOOST_COMPUTE_GCC_DIAG_OFF(gcc)
#  define BOOST_COMPUTE_DIAG_ON(gcc, clang, msvc) BOOST_COMPUTE_GCC_DIAG_ON(gcc)
#else // Ensure these macros do nothing for other compilers.
#  define BOOST_COMPUTE_DIAG_OFF(gcc, clang, msvc)
#  define BOOST_COMPUTE_DIAG_ON(gcc, clang, msvc)
#endif

#define BOOST_COMPUTE_DISABLE_DEPRECATED_DECLARATIONS() \
    BOOST_COMPUTE_DIAG_OFF(deprecated-declarations, deprecated-declarations, 4996)
#define BOOST_COMPUTE_ENABLE_DEPRECATED_DECLARATIONS() \
    BOOST_COMPUTE_DIAG_ON(deprecated-declarations, deprecated-declarations, 4996);


#endif /* BOOST_COMPUTE_DETAIL_DIAGNOSTIC_HPP */

/* diagnostic.hpp
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
*/