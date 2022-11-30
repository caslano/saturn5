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
#  define BOOST_NO_CXX11_OVERRIDE
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
#if (_MSC_FULL_VER < 193030705)  || (_MSVC_LANG < 202004)
#  define BOOST_NO_TWO_PHASE_NAME_LOOKUP
#endif

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

//
// Approximate compiler conformance version
//
#ifdef _MSVC_LANG
#  define BOOST_CXX_VERSION _MSVC_LANG
#elif defined(_HAS_CXX17)
#  define BOOST_CXX_VERSION 201703L
#elif BOOST_MSVC >= 1916
#  define BOOST_CXX_VERSION 201402L
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