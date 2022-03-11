//  (C) Copyright John Maddock 2001 - 2003.
//  (C) Copyright Darin Adler 2001 - 2002.
//  (C) Copyright Peter Dimov 2001.
//  (C) Copyright Aleksey Gurtovoy 2002.
//  (C) Copyright David Abrahams 2002 - 2003.
//  (C) Copyright Beman Dawes 2002 - 2003.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.
//
//  Microsoft Visual C++ compiler setup:
//
//  We need to be careful with the checks in this file, as contrary
//  to popular belief there are versions with _MSC_VER with the final
//  digit non-zero (mainly the MIPS cross compiler).
//
//  So we either test _MSC_VER >= XXXX or else _MSC_VER < XXXX.
//  No other comparisons (==, >, or <=) are safe.
//

#define BOOST_MSVC _MSC_VER

//
// Helper macro BOOST_MSVC_FULL_VER for use in Boost code:
//
#if _MSC_FULL_VER > 100000000
#  define BOOST_MSVC_FULL_VER _MSC_FULL_VER
#else
#  define BOOST_MSVC_FULL_VER (_MSC_FULL_VER * 10)
#endif

// Attempt to suppress VC6 warnings about the length of decorated names (obsolete):
#pragma warning( disable : 4503 ) // warning: decorated name length exceeded

#define BOOST_HAS_PRAGMA_ONCE

//
// versions check:
// we don't support Visual C++ prior to version 7.1:
#if _MSC_VER < 1310
#  error "Compiler not supported or configured - please reconfigure"
#endif

// VS2005 (VC8) docs: __assume has been in Visual C++ for multiple releases
#define BOOST_UNREACHABLE_RETURN(x) __assume(0);

#if _MSC_FULL_VER < 180020827
#  define BOOST_NO_FENV_H
#endif

#if _MSC_VER < 1400
// although a conforming signature for swprint exists in VC7.1
// it appears not to actually work:
#  define BOOST_NO_SWPRINTF
// Our extern template tests also fail for this compiler:
#  define BOOST_NO_CXX11_EXTERN_TEMPLATE
// Variadic macros do not exist for VC7.1 and lower
#  define BOOST_NO_CXX11_VARIADIC_MACROS
#  define BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#endif

#if _MSC_VER < 1500  // 140X == VC++ 8.0
#  define BOOST_NO_MEMBER_TEMPLATE_FRIENDS
#endif

#if _MSC_VER < 1600  // 150X == VC++ 9.0
   // A bug in VC9:
#  define BOOST_NO_ADL_BARRIER
#endif


#ifndef _NATIVE_WCHAR_T_DEFINED
#  define BOOST_NO_INTRINSIC_WCHAR_T
#endif

//
// check for exception handling support:
#if !defined(_CPPUNWIND) && !defined(BOOST_NO_EXCEPTIONS)
#  define BOOST_NO_EXCEPTIONS
#endif

//
// __int64 support:
//
#define BOOST_HAS_MS_INT64
#if defined(_MSC_EXTENSIONS) || (_MSC_VER >= 1400)
#   define BOOST_HAS_LONG_LONG
#else
#   define BOOST_NO_LONG_LONG
#endif
#if (_MSC_VER >= 1400) && !defined(_DEBUG)
#   define BOOST_HAS_NRVO
#endif
#if _MSC_VER >= 1600  // 160X == VC++ 10.0
#  define BOOST_HAS_PRAGMA_DETECT_MISMATCH
#endif
//
// disable Win32 API's if compiler extensions are
// turned off:
//
#if !defined(_MSC_EXTENSIONS) && !defined(BOOST_DISABLE_WIN32)
#  define BOOST_DISABLE_WIN32
#endif
#if !defined(_CPPRTTI) && !defined(BOOST_NO_RTTI)
#  define BOOST_NO_RTTI
#endif

//
// TR1 features:
//
#if (_MSC_VER >= 1700) && defined(_HAS_CXX17) && (_HAS_CXX17 > 0)
// # define BOOST_HAS_TR1_HASH          // don't know if this is true yet.
// # define BOOST_HAS_TR1_TYPE_TRAITS   // don't know if this is true yet.
# define BOOST_HAS_TR1_UNORDERED_MAP
# define BOOST_HAS_TR1_UNORDERED_SET
#endif

//
// C++0x features
//
//   See above for BOOST_NO_LONG_LONG

// C++ features supported by VC++ 10 (aka 2010)
//
#if _MSC_VER < 1600
#  define BOOST_NO_CXX11_AUTO_DECLARATIONS
#  define BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#  define BOOST_NO_CXX11_LAMBDAS
#  define BOOST_NO_CXX11_RVALUE_REFERENCES
#  define BOOST_NO_CXX11_STATIC_ASSERT
#  define BOOST_NO_CXX11_NULLPTR
#  define BOOST_NO_CXX11_DECLTYPE
#endif // _MSC_VER < 1600

#if _MSC_VER >= 1600
#  define BOOST_HAS_STDINT_H
#endif

// C++11 features supported by VC++ 11 (aka 2012)
//
#if _MSC_VER < 1700
#  define BOOST_NO_CXX11_FINAL
#  define BOOST_NO_CXX11_RANGE_BASED_FOR
#  define BOOST_NO_CXX11_SCOPED_ENUMS
#endif // _MSC_VER < 1700

// C++11 features supported by VC++ 12 (aka 2013).
//
#if _MSC_FULL_VER < 180020827
#  define BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#  define BOOST_NO_CXX11_DELETED_FUNCTIONS
#  define BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#  define BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#  define BOOST_NO_CXX11_RAW_LITERALS
#  define BOOST_NO_CXX11_TEMPLATE_ALIASES
#  define BOOST_NO_CXX11_TRAILING_RESULT_TYPES
#  define BOOST_NO_CXX11_VARIADIC_TEMPLATES
#  define BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#  define BOOST_NO_CXX11_DECLTYPE_N3276
#endif

#if _MSC_FULL_VER >= 180020827
#define BOOST_HAS_EXPM1
#define BOOST_HAS_LOG1P
#endif

// C++11 features supported by VC++ 14 (aka 2015)
//
#if (_MSC_FULL_VER < 190023026)
#  define BOOST_NO_CXX11_NOEXCEPT
#  define BOOST_NO_CXX11_DEFAULTED_MOVES
#  define BOOST_NO_CXX11_REF_QUALIFIERS
#  define BOOST_NO_CXX11_USER_DEFINED_LITERALS
#  define BOOST_NO_CXX11_ALIGNAS
#  define BOOST_NO_CXX11_INLINE_NAMESPACES
#  define BOOST_NO_CXX11_CHAR16_T
#  define BOOST_NO_CXX11_CHAR32_T
#  define BOOST_NO_CXX11_UNICODE_LITERALS
#  define BOOST_NO_CXX14_DECLTYPE_AUTO
#  define BOOST_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES
#  define BOOST_NO_CXX14_RETURN_TYPE_DEDUCTION
#  define BOOST_NO_CXX14_BINARY_LITERALS
#  define BOOST_NO_CXX14_GENERIC_LAMBDAS
#  define BOOST_NO_CXX14_DIGIT_SEPARATORS
#  define BOOST_NO_CXX11_THREAD_LOCAL
#  define BOOST_NO_CXX11_UNRESTRICTED_UNION
#endif
// C++11 features supported by VC++ 14 update 3 (aka 2015)
//
#if (_MSC_FULL_VER < 190024210)
#  define BOOST_NO_CXX14_VARIABLE_TEMPLATES
#  define BOOST_NO_SFINAE_EXPR
#  define BOOST_NO_CXX11_CONSTEXPR
#endif

// C++14 features supported by VC++ 14.1 (Visual Studio 2017)
//
#if (_MSC_VER < 1910)
#  define BOOST_NO_CXX14_AGGREGATE_NSDMI
#endif

// C++17 features supported by VC++ 14.1 (Visual Studio 2017) Update 3
//
#if (_MSC_VER < 1911) || (_MSVC_LANG < 201703)
#  define BOOST_NO_CXX17_STRUCTURED_BINDINGS
#  define BOOST_NO_CXX17_IF_CONSTEXPR
// Let the defaults handle these now:
//#  define BOOST_NO_CXX17_HDR_OPTIONAL
//#  define BOOST_NO_CXX17_HDR_STRING_VIEW
#endif

// MSVC including version 14 has not yet completely
// implemented value-initialization, as is reported:
// "VC++ does not value-initialize members of derived classes without
// user-declared constructor", reported in 2009 by Sylvester Hesp:
// https://connect.microsoft.com/VisualStudio/feedback/details/484295
// "Presence of copy constructor breaks member class initialization",
// reported in 2009 by Alex Vakulenko:
// https://connect.microsoft.com/VisualStudio/feedback/details/499606
// "Value-initialization in new-expression", reported in 2005 by
// Pavel Kuznetsov (MetaCommunications Engineering):
// https://connect.microsoft.com/VisualStudio/feedback/details/100744
// Reported again by John Maddock in 2015 for VC14:
// https://connect.microsoft.com/VisualStudio/feedback/details/1582233/c-subobjects-still-not-value-initialized-correctly
// See also: http://www.boost.org/libs/utility/value_init.htm#compiler_issues
// (Niels Dekker, LKEB, May 2010)
// Still present in VC15.5, Dec 2017.
#define BOOST_NO_COMPLETE_VALUE_INITIALIZATION
//
// C++ 11:
//
// This is supported with /permissive- for 15.5 onwards, unfortunately we appear to have no way to tell
// if this is in effect or not, in any case nothing in Boost is currently using this, so we'll just go
// on defining it for now:
//
#  define BOOST_NO_TWO_PHASE_NAME_LOOKUP

#if (_MSC_VER < 1912) || (_MSVC_LANG < 201402)
// Supported from msvc-15.5 onwards:
#define BOOST_NO_CXX11_SFINAE_EXPR
#endif
#if (_MSC_VER < 1915) || (_MSVC_LANG < 201402)
// C++ 14:
// Still gives internal compiler error for msvc-15.5:
#  define BOOST_NO_CXX14_CONSTEXPR
#endif
// C++ 17:
#if (_MSC_VER < 1912) || (_MSVC_LANG < 201703)
#define BOOST_NO_CXX17_INLINE_VARIABLES
#define BOOST_NO_CXX17_FOLD_EXPRESSIONS
#endif

//
// Things that don't work in clr mode:
//
#ifdef _M_CEE
#ifndef BOOST_NO_CXX11_THREAD_LOCAL
#  define BOOST_NO_CXX11_THREAD_LOCAL
#endif
#ifndef BOOST_NO_SFINAE_EXPR
#  define BOOST_NO_SFINAE_EXPR
#endif
#ifndef BOOST_NO_CXX11_REF_QUALIFIERS
#  define BOOST_NO_CXX11_REF_QUALIFIERS
#endif
#endif
#ifdef _M_CEE_PURE
#ifndef BOOST_NO_CXX11_CONSTEXPR
#  define BOOST_NO_CXX11_CONSTEXPR
#endif
#endif

//
// prefix and suffix headers:
//
#ifndef BOOST_ABI_PREFIX
#  define BOOST_ABI_PREFIX "boost/config/abi/msvc_prefix.hpp"
#endif
#ifndef BOOST_ABI_SUFFIX
#  define BOOST_ABI_SUFFIX "boost/config/abi/msvc_suffix.hpp"
#endif

#ifndef BOOST_COMPILER
// TODO:
// these things are mostly bogus. 1200 means version 12.0 of the compiler. The
// artificial versions assigned to them only refer to the versions of some IDE
// these compilers have been shipped with, and even that is not all of it. Some
// were shipped with freely downloadable SDKs, others as crosscompilers in eVC.
// IOW, you can't use these 'versions' in any sensible way. Sorry.
# if defined(UNDER_CE)
#   if _MSC_VER < 1400
      // Note: I'm not aware of any CE compiler with version 13xx
#      if defined(BOOST_ASSERT_CONFIG)
#         error "boost: Unknown EVC++ compiler version - please run the configure tests and report the results"
#      else
#         pragma message("boost: Unknown EVC++ compiler version - please run the configure tests and report the results")
#      endif
#   elif _MSC_VER < 1500
#     define BOOST_COMPILER_VERSION evc8
#   elif _MSC_VER < 1600
#     define BOOST_COMPILER_VERSION evc9
#   elif _MSC_VER < 1700
#     define BOOST_COMPILER_VERSION evc10
#   elif _MSC_VER < 1800 
#     define BOOST_COMPILER_VERSION evc11 
#   elif _MSC_VER < 1900 
#     define BOOST_COMPILER_VERSION evc12
#   elif _MSC_VER < 2000  
#     define BOOST_COMPILER_VERSION evc14
#   else
#      if defined(BOOST_ASSERT_CONFIG)
#         error "boost: Unknown EVC++ compiler version - please run the configure tests and report the results"
#      else
#         pragma message("boost: Unknown EVC++ compiler version - please run the configure tests and report the results")
#      endif
#   endif
# else
#   if _MSC_VER < 1200
      // Note: Versions up to 10.0 aren't supported.
#     define BOOST_COMPILER_VERSION 5.0
#   elif _MSC_VER < 1300
#     define BOOST_COMPILER_VERSION 6.0
#   elif _MSC_VER < 1310
#     define BOOST_COMPILER_VERSION 7.0
#   elif _MSC_VER < 1400
#     define BOOST_COMPILER_VERSION 7.1
#   elif _MSC_VER < 1500
#     define BOOST_COMPILER_VERSION 8.0
#   elif _MSC_VER < 1600
#     define BOOST_COMPILER_VERSION 9.0
#   elif _MSC_VER < 1700
#     define BOOST_COMPILER_VERSION 10.0
#   elif _MSC_VER < 1800 
#     define BOOST_COMPILER_VERSION 11.0
#   elif _MSC_VER < 1900
#     define BOOST_COMPILER_VERSION 12.0
#   elif _MSC_VER < 1910
#     define BOOST_COMPILER_VERSION 14.0
#   elif _MSC_VER < 1920
#     define BOOST_COMPILER_VERSION 14.1
#   elif _MSC_VER < 1930
#     define BOOST_COMPILER_VERSION 14.2
#   else
#     define BOOST_COMPILER_VERSION _MSC_VER
#   endif
# endif

#  define BOOST_COMPILER "Microsoft Visual C++ version " BOOST_STRINGIZE(BOOST_COMPILER_VERSION)
#endif

#include <boost/config/pragma_message.hpp>

//
// last known and checked version is 19.20.27508 (VC++ 2019 RC3):
#if (_MSC_VER > 1920)
#  if defined(BOOST_ASSERT_CONFIG)
#     error "Boost.Config is older than your current compiler version."
#  elif !defined(BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE)
      //
      // Disabled as of March 2018 - the pace of VS releases is hard to keep up with
      // and in any case, we have relatively few defect macros defined now.
      // BOOST_PRAGMA_MESSAGE("Info: Boost.Config is older than your compiler version - probably nothing bad will happen - but you may wish to look for an updated Boost version. Define BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE to suppress this message.")
#  endif
#endif

/* visualc.hpp
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
*/