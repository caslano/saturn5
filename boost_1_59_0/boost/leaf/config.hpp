#ifndef BOOST_LEAF_CONFIG_HPP_INCLUDED
#define BOOST_LEAF_CONFIG_HPP_INCLUDED

// Copyright 2018-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// The following is based in part on Boost Config.

// (C) Copyright John Maddock 2001 - 2003.
// (C) Copyright Martin Wille 2003.
// (C) Copyright Guillaume Melquiond 2003.

#ifndef BOOST_LEAF_ASSERT
#   include <cassert>
#   define BOOST_LEAF_ASSERT assert
#endif

////////////////////////////////////////

#ifdef BOOST_LEAF_DIAGNOSTICS
#   warning BOOST_LEAF_DIAGNOSTICS has been renamed to BOOST_LEAF_CFG_DIAGNOSTICS.
#   define BOOST_LEAF_CFG_DIAGNOSTICS BOOST_LEAF_DIAGNOSTICS
#endif

////////////////////////////////////////

#ifdef BOOST_LEAF_TLS_FREERTOS

#   ifndef BOOST_LEAF_EMBEDDED
#       define BOOST_LEAF_EMBEDDED
#   endif

#endif

////////////////////////////////////////

#ifdef BOOST_LEAF_EMBEDDED

#   ifndef BOOST_LEAF_CFG_DIAGNOSTICS
#       define BOOST_LEAF_CFG_DIAGNOSTICS 0
#   endif

#   ifndef BOOST_LEAF_CFG_STD_SYSTEM_ERROR
#       define BOOST_LEAF_CFG_STD_SYSTEM_ERROR 0
#   endif

#   ifndef BOOST_LEAF_CFG_STD_STRING
#       define BOOST_LEAF_CFG_STD_STRING 0
#   endif

#   ifndef BOOST_LEAF_CFG_CAPTURE
#       define BOOST_LEAF_CFG_CAPTURE 0
#   endif

#endif

////////////////////////////////////////

#ifndef BOOST_LEAF_CFG_DIAGNOSTICS
#   define BOOST_LEAF_CFG_DIAGNOSTICS 1
#endif

#ifndef BOOST_LEAF_CFG_STD_SYSTEM_ERROR
#   define BOOST_LEAF_CFG_STD_SYSTEM_ERROR 1
#endif

#ifndef BOOST_LEAF_CFG_STD_STRING
#   define BOOST_LEAF_CFG_STD_STRING 1
#endif

#ifndef BOOST_LEAF_CFG_CAPTURE
#   define BOOST_LEAF_CFG_CAPTURE 1
#endif

#ifndef BOOST_LEAF_CFG_WIN32
#   define BOOST_LEAF_CFG_WIN32 0
#endif

#ifndef BOOST_LEAF_CFG_GNUC_STMTEXPR
#   ifdef __GNUC__
#   	define BOOST_LEAF_CFG_GNUC_STMTEXPR 1
#   else
#   	define BOOST_LEAF_CFG_GNUC_STMTEXPR 0
#   endif
#endif

#if BOOST_LEAF_CFG_DIAGNOSTICS!=0 && BOOST_LEAF_CFG_DIAGNOSTICS!=1
#   error BOOST_LEAF_CFG_DIAGNOSTICS must be 0 or 1.
#endif

#if BOOST_LEAF_CFG_STD_SYSTEM_ERROR!=0 && BOOST_LEAF_CFG_STD_SYSTEM_ERROR!=1
#   error BOOST_LEAF_CFG_STD_SYSTEM_ERROR must be 0 or 1.
#endif

#if BOOST_LEAF_CFG_STD_STRING!=0 && BOOST_LEAF_CFG_STD_STRING!=1
#   error BOOST_LEAF_CFG_STD_STRING must be 0 or 1.
#endif

#if BOOST_LEAF_CFG_CAPTURE!=0 && BOOST_LEAF_CFG_CAPTURE!=1
#   error BOOST_LEAF_CFG_CAPTURE must be 0 or 1.
#endif

#if BOOST_LEAF_CFG_DIAGNOSTICS && !BOOST_LEAF_CFG_STD_STRING
#   error BOOST_LEAF_CFG_DIAGNOSTICS requires the use of std::string
#endif

#if BOOST_LEAF_CFG_WIN32!=0 && BOOST_LEAF_CFG_WIN32!=1
#   error BOOST_LEAF_CFG_WIN32 must be 0 or 1.
#endif

#if BOOST_LEAF_CFG_GNUC_STMTEXPR!=0 && BOOST_LEAF_CFG_GNUC_STMTEXPR!=1
#   error BOOST_LEAF_CFG_GNUC_STMTEXPR must be 0 or 1.
#endif

////////////////////////////////////////

// Configure BOOST_LEAF_NO_EXCEPTIONS, unless already #defined
#ifndef BOOST_LEAF_NO_EXCEPTIONS

#   if defined(__clang__) && !defined(__ibmxl__)
//  Clang C++ emulates GCC, so it has to appear early.

#       if !__has_feature(cxx_exceptions)
#           define BOOST_LEAF_NO_EXCEPTIONS
#       endif

#   elif defined(__DMC__)
//  Digital Mars C++

#       if !defined(_CPPUNWIND)
#           define BOOST_LEAF_NO_EXCEPTIONS
#       endif

#   elif defined(__GNUC__) && !defined(__ibmxl__)
//  GNU C++:

#       if !defined(__EXCEPTIONS)
#           define BOOST_LEAF_NO_EXCEPTIONS
#       endif

#   elif defined(__KCC)
//  Kai C++

#       if !defined(_EXCEPTIONS)
#           define BOOST_LEAF_NO_EXCEPTIONS
#       endif

#   elif defined(__CODEGEARC__)
//  CodeGear - must be checked for before Borland

#       if !defined(_CPPUNWIND) && !defined(__EXCEPTIONS)
#           define BOOST_LEAF_NO_EXCEPTIONS
#       endif

#   elif defined(__BORLANDC__)
//  Borland

#       if !defined(_CPPUNWIND) && !defined(__EXCEPTIONS)
#           define BOOST_LEAF_NO_EXCEPTIONS
#       endif

#   elif defined(__MWERKS__)
//  Metrowerks CodeWarrior

#       if !__option(exceptions)
#           define BOOST_LEAF_NO_EXCEPTIONS
#       endif

#   elif defined(__IBMCPP__) && defined(__COMPILER_VER__) && defined(__MVS__)
//  IBM z/OS XL C/C++

#       if !defined(_CPPUNWIND) && !defined(__EXCEPTIONS)
#           define BOOST_LEAF_NO_EXCEPTIONS
#       endif

#   elif defined(__ibmxl__)
//  IBM XL C/C++ for Linux (Little Endian)

#       if !__has_feature(cxx_exceptions)
#           define BOOST_LEAF_NO_EXCEPTIONS
#       endif

#   elif defined(_MSC_VER)
//  Microsoft Visual C++
//
//  Must remain the last #elif since some other vendors (Metrowerks, for
//  example) also #define _MSC_VER

#       if !_CPPUNWIND
#           define BOOST_LEAF_NO_EXCEPTIONS
#       endif
#   endif

#endif

#ifdef BOOST_NORETURN
#   define BOOST_LEAF_NORETURN BOOST_NORETURN
#else
#   if defined(_MSC_VER)
#       define BOOST_LEAF_NORETURN __declspec(noreturn)
#   elif defined(__GNUC__)
#       define BOOST_LEAF_NORETURN __attribute__ ((__noreturn__))
#   elif defined(__has_attribute) && defined(__SUNPRO_CC) && (__SUNPRO_CC > 0x5130)
#       if __has_attribute(noreturn)
#           define BOOST_LEAF_NORETURN [[noreturn]]
#       endif
#   elif defined(__has_cpp_attribute)
#       if __has_cpp_attribute(noreturn)
#           define BOOST_LEAF_NORETURN [[noreturn]]
#       endif
#   endif
#endif
#if !defined(BOOST_LEAF_NORETURN)
#  define BOOST_LEAF_NORETURN
#endif

////////////////////////////////////////

#ifdef _MSC_VER
#   define BOOST_LEAF_ALWAYS_INLINE __forceinline
#else
#   define BOOST_LEAF_ALWAYS_INLINE __attribute__((always_inline)) inline
#endif

////////////////////////////////////////

#ifndef BOOST_LEAF_NODISCARD
#   if __cplusplus >= 201703L
#       define BOOST_LEAF_NODISCARD [[nodiscard]]
#   else
#       define BOOST_LEAF_NODISCARD
#   endif
#endif

////////////////////////////////////////

#ifndef BOOST_LEAF_CONSTEXPR
#   if __cplusplus > 201402L
#       define BOOST_LEAF_CONSTEXPR constexpr
#   else
#       define BOOST_LEAF_CONSTEXPR
#   endif
#endif

////////////////////////////////////////

#ifndef BOOST_LEAF_NO_EXCEPTIONS
#   include <exception>
#   if (defined(__cpp_lib_uncaught_exceptions) && __cpp_lib_uncaught_exceptions >= 201411L) || (defined(_MSC_VER) && _MSC_VER >= 1900)
#       define BOOST_LEAF_STD_UNCAUGHT_EXCEPTIONS 1
#   else
#       define BOOST_LEAF_STD_UNCAUGHT_EXCEPTIONS 0
#   endif
#endif

////////////////////////////////////////

#ifdef __GNUC__
#   define BOOST_LEAF_SYMBOL_VISIBLE __attribute__((__visibility__("default")))
#else
#   define BOOST_LEAF_SYMBOL_VISIBLE
#endif

////////////////////////////////////////

#if defined(__GNUC__) && !(defined(__clang__) || defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)) && (__GNUC__ * 100 + __GNUC_MINOR__) < 409
#   ifndef BOOST_LEAF_NO_CXX11_REF_QUALIFIERS
#       define BOOST_LEAF_NO_CXX11_REF_QUALIFIERS
#   endif
#endif

////////////////////////////////////////

// Configure TLS access
#include <boost/leaf/config/tls.hpp>

////////////////////////////////////////

#endif

/* config.hpp
+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
*/