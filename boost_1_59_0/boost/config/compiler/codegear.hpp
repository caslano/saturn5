//  (C) Copyright John Maddock 2001 - 2003.
//  (C) Copyright David Abrahams 2002 - 2003.
//  (C) Copyright Aleksey Gurtovoy 2002.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  CodeGear C++ compiler setup:

//
// versions check:
// last known and checked version is 0x740
#if (__CODEGEARC__ > 0x740)
#  if defined(BOOST_ASSERT_CONFIG)
#     error "boost: Unknown compiler version - please run the configure tests and report the results"
#  else
#     pragma message( "boost: Unknown compiler version - please run the configure tests and report the results")
#  endif
#endif

#ifdef __clang__ // Clang enhanced Windows compiler

#  include "clang.hpp"
#  define BOOST_NO_CXX11_THREAD_LOCAL
#  define BOOST_NO_CXX11_ATOMIC_SMART_PTR

// This bug has been reported to Embarcadero

#if defined(BOOST_HAS_INT128)
#undef BOOST_HAS_INT128
#endif
#if defined(BOOST_HAS_FLOAT128)
#undef BOOST_HAS_FLOAT128
#endif

// The clang-based compilers can not do 128 atomic exchanges

#define BOOST_ATOMIC_NO_CMPXCHG16B

// 32 functions are missing from the current RTL in cwchar, so it really can not be used even if it exists

#  define BOOST_NO_CWCHAR

#  ifndef __MT__  /* If compiling in single-threaded mode, assume there is no CXX11_HDR_ATOMIC */
#    define BOOST_NO_CXX11_HDR_ATOMIC
#  endif

/* temporarily disable this until we can link against fegetround fesetround feholdexcept */

#define BOOST_NO_FENV_H

/* Reported this bug to Embarcadero with the latest C++ Builder Rio release */

#define BOOST_NO_CXX11_HDR_EXCEPTION

//
// check for exception handling support:
//
#if !defined(_CPPUNWIND) && !defined(__EXCEPTIONS) && !defined(BOOST_NO_EXCEPTIONS)
#  define BOOST_NO_EXCEPTIONS
#endif

/*

// On non-Win32 platforms let the platform config figure this out:
#ifdef _WIN32
#  define BOOST_HAS_STDINT_H
#endif

//
// __int64:
//
#if !defined(__STRICT_ANSI__)
#  define BOOST_HAS_MS_INT64
#endif
//
// all versions have a <dirent.h>:
//
#if !defined(__STRICT_ANSI__)
#  define BOOST_HAS_DIRENT_H
#endif
//
// Disable Win32 support in ANSI mode:
//
#  pragma defineonoption BOOST_DISABLE_WIN32 -A
//
// MSVC compatibility mode does some nasty things:
// TODO: look up if this doesn't apply to the whole 12xx range
//
#if defined(_MSC_VER) && (_MSC_VER <= 1200)
#  define BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
#  define BOOST_NO_VOID_RETURNS
#endif
//

*/

// Specific settings for Embarcadero drivers
#  define BOOST_EMBTC          __CODEGEARC__
#  define BOOST_EMBTC_FULL_VER ((__clang_major__      << 16) | \
                                (__clang_minor__      <<  8) | \
                                 __clang_patchlevel__         )

// Detecting which Embarcadero driver is being used
#if defined(BOOST_EMBTC)
#  if defined(_WIN64)
#    define BOOST_EMBTC_WIN64 1
#    define BOOST_EMBTC_WINDOWS 1
#    ifndef BOOST_USE_WINDOWS_H
#      define BOOST_USE_WINDOWS_H
#    endif
#  elif defined(_WIN32)
#    define BOOST_EMBTC_WIN32C 1
#    define BOOST_EMBTC_WINDOWS 1
#    ifndef BOOST_USE_WINDOWS_H
#      define BOOST_USE_WINDOWS_H
#    endif
#  elif defined(__APPLE__) && defined(__arm__)
#    define BOOST_EMBTC_IOSARM 1
#    define BOOST_EMBTC_IOS 1
#  elif defined(__APPLE__) && defined(__aarch64__)
#    define BOOST_EMBTC_IOSARM64 1
#    define BOOST_EMBTC_IOS 1
#  elif defined(__ANDROID__) && defined(__arm__)
#    define BOOST_EMBTC_AARM 1
#    define BOOST_EMBTC_ANDROID 1
#  elif
#    if defined(BOOST_ASSERT_CONFIG)
#       error "Unknown Embarcadero driver"
#    else
#       warning "Unknown Embarcadero driver"
#    endif /* defined(BOOST_ASSERT_CONFIG) */
#  endif
#endif /* defined(BOOST_EMBTC) */

#if defined(BOOST_EMBTC_WINDOWS)

#if !defined(_chdir)
#define _chdir(x) chdir(x)
#endif

#if !defined(_dup2)
#define _dup2(x,y) dup2(x,y)
#endif

#endif

#  undef BOOST_COMPILER
#  define BOOST_COMPILER "Embarcadero-Clang C++ version " BOOST_STRINGIZE(__CODEGEARC__) " clang: " __clang_version__
// #  define __CODEGEARC_CLANG__ __CODEGEARC__
// #  define __EMBARCADERO_CLANG__ __CODEGEARC__
// #  define __BORLANDC_CLANG__ __BORLANDC__

#else // #if !defined(__clang__)

# define BOOST_CODEGEARC  __CODEGEARC__
# define BOOST_BORLANDC   __BORLANDC__

#if !defined( BOOST_WITH_CODEGEAR_WARNINGS )
// these warnings occur frequently in optimized template code
# pragma warn -8004 // var assigned value, but never used
# pragma warn -8008 // condition always true/false
# pragma warn -8066 // dead code can never execute
# pragma warn -8104 // static members with ctors not threadsafe
# pragma warn -8105 // reference member in class without ctors
#endif

// CodeGear C++ Builder 2009
#if (__CODEGEARC__ <= 0x613)
#  define BOOST_NO_INTEGRAL_INT64_T
#  define BOOST_NO_DEPENDENT_NESTED_DERIVATIONS
#  define BOOST_NO_PRIVATE_IN_AGGREGATE
#  define BOOST_NO_USING_DECLARATION_OVERLOADS_FROM_TYPENAME_BASE
   // we shouldn't really need this - but too many things choke
   // without it, this needs more investigation:
#  define BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
#  define BOOST_SP_NO_SP_CONVERTIBLE
#endif

// CodeGear C++ Builder 2010
#if (__CODEGEARC__ <= 0x621)
#  define BOOST_NO_TYPENAME_WITH_CTOR    // Cannot use typename keyword when making temporaries of a dependant type
#  define BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#  define BOOST_NO_MEMBER_TEMPLATE_FRIENDS
#  define BOOST_NO_NESTED_FRIENDSHIP     // TC1 gives nested classes access rights as any other member
#  define BOOST_NO_USING_TEMPLATE
#  define BOOST_NO_TWO_PHASE_NAME_LOOKUP
// Temporary hack, until specific MPL preprocessed headers are generated
#  define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

// CodeGear has not yet completely implemented value-initialization, for
// example for array types, as I reported in 2010: Embarcadero Report 83751,
// "Value-initialization: arrays should have each element value-initialized",
// http://qc.embarcadero.com/wc/qcmain.aspx?d=83751
// Last checked version: Embarcadero C++ 6.21
// See also: http://www.boost.org/libs/utility/value_init.htm#compiler_issues
// (Niels Dekker, LKEB, April 2010)
#  define BOOST_NO_COMPLETE_VALUE_INITIALIZATION

#  if defined(NDEBUG) && defined(__cplusplus)
      // fix broken <cstring> so that Boost.test works:
#     include <cstring>
#     undef strcmp
#  endif
   // fix broken errno declaration:
#  include <errno.h>
#  ifndef errno
#     define errno errno
#  endif

#endif

// Reportedly, #pragma once is supported since C++ Builder 2010
#if (__CODEGEARC__ >= 0x620)
#  define BOOST_HAS_PRAGMA_ONCE
#endif

#define BOOST_NO_FENV_H

//
// C++0x macros:
//
#if (__CODEGEARC__ <= 0x620)
#define BOOST_NO_CXX11_STATIC_ASSERT
#else
#define BOOST_HAS_STATIC_ASSERT
#endif
#define BOOST_HAS_CHAR16_T
#define BOOST_HAS_CHAR32_T
#define BOOST_HAS_LONG_LONG
// #define BOOST_HAS_ALIGNOF
#define BOOST_HAS_DECLTYPE
#define BOOST_HAS_EXPLICIT_CONVERSION_OPS
// #define BOOST_HAS_RVALUE_REFS
#define BOOST_HAS_SCOPED_ENUM
// #define BOOST_HAS_STATIC_ASSERT
#define BOOST_HAS_STD_TYPE_TRAITS

#define BOOST_NO_CXX11_AUTO_DECLARATIONS
#define BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#define BOOST_NO_CXX11_CONSTEXPR
#define BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#define BOOST_NO_CXX11_DELETED_FUNCTIONS
#define BOOST_NO_CXX11_EXTERN_TEMPLATE
#define BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#define BOOST_NO_CXX11_LAMBDAS
#define BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#define BOOST_NO_CXX11_NOEXCEPT
#define BOOST_NO_CXX11_NULLPTR
#define BOOST_NO_CXX11_RANGE_BASED_FOR
#define BOOST_NO_CXX11_RAW_LITERALS
#define BOOST_NO_CXX11_RVALUE_REFERENCES
#define BOOST_NO_SFINAE_EXPR
#define BOOST_NO_CXX11_SFINAE_EXPR
#define BOOST_NO_CXX11_TEMPLATE_ALIASES
#define BOOST_NO_CXX11_UNICODE_LITERALS
#define BOOST_NO_CXX11_VARIADIC_TEMPLATES
#define BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#define BOOST_NO_CXX11_USER_DEFINED_LITERALS
#define BOOST_NO_CXX11_ALIGNAS
#define BOOST_NO_CXX11_TRAILING_RESULT_TYPES
#define BOOST_NO_CXX11_INLINE_NAMESPACES
#define BOOST_NO_CXX11_REF_QUALIFIERS
#define BOOST_NO_CXX11_FINAL
#define BOOST_NO_CXX11_OVERRIDE
#define BOOST_NO_CXX11_THREAD_LOCAL
#define BOOST_NO_CXX11_DECLTYPE_N3276
#define BOOST_NO_CXX11_UNRESTRICTED_UNION

// C++ 14:
#if !defined(__cpp_aggregate_nsdmi) || (__cpp_aggregate_nsdmi < 201304)
#  define BOOST_NO_CXX14_AGGREGATE_NSDMI
#endif
#if !defined(__cpp_binary_literals) || (__cpp_binary_literals < 201304)
#  define BOOST_NO_CXX14_BINARY_LITERALS
#endif
#if !defined(__cpp_constexpr) || (__cpp_constexpr < 201304)
#  define BOOST_NO_CXX14_CONSTEXPR
#endif
#if !defined(__cpp_decltype_auto) || (__cpp_decltype_auto < 201304)
#  define BOOST_NO_CXX14_DECLTYPE_AUTO
#endif
#if (__cplusplus < 201304) // There's no SD6 check for this....
#  define BOOST_NO_CXX14_DIGIT_SEPARATORS
#endif
#if !defined(__cpp_generic_lambdas) || (__cpp_generic_lambdas < 201304)
#  define BOOST_NO_CXX14_GENERIC_LAMBDAS
#endif
#if !defined(__cpp_init_captures) || (__cpp_init_captures < 201304)
#  define BOOST_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES
#endif
#if !defined(__cpp_return_type_deduction) || (__cpp_return_type_deduction < 201304)
#  define BOOST_NO_CXX14_RETURN_TYPE_DEDUCTION
#endif
#if !defined(__cpp_variable_templates) || (__cpp_variable_templates < 201304)
#  define BOOST_NO_CXX14_VARIABLE_TEMPLATES
#endif

// C++17
#if !defined(__cpp_structured_bindings) || (__cpp_structured_bindings < 201606)
#  define BOOST_NO_CXX17_STRUCTURED_BINDINGS
#endif

#if !defined(__cpp_inline_variables) || (__cpp_inline_variables < 201606)
#  define BOOST_NO_CXX17_INLINE_VARIABLES
#endif

#if !defined(__cpp_fold_expressions) || (__cpp_fold_expressions < 201603)
#  define BOOST_NO_CXX17_FOLD_EXPRESSIONS
#endif

#if !defined(__cpp_if_constexpr) || (__cpp_if_constexpr < 201606)
#  define BOOST_NO_CXX17_IF_CONSTEXPR
#endif

//
// TR1 macros:
//
#define BOOST_HAS_TR1_HASH
#define BOOST_HAS_TR1_TYPE_TRAITS
#define BOOST_HAS_TR1_UNORDERED_MAP
#define BOOST_HAS_TR1_UNORDERED_SET

#define BOOST_HAS_MACRO_USE_FACET

#define BOOST_NO_CXX11_HDR_INITIALIZER_LIST

// On non-Win32 platforms let the platform config figure this out:
#ifdef _WIN32
#  define BOOST_HAS_STDINT_H
#endif

//
// __int64:
//
#if !defined(__STRICT_ANSI__)
#  define BOOST_HAS_MS_INT64
#endif
//
// check for exception handling support:
//
#if !defined(_CPPUNWIND) && !defined(BOOST_CPPUNWIND) && !defined(__EXCEPTIONS) && !defined(BOOST_NO_EXCEPTIONS)
#  define BOOST_NO_EXCEPTIONS
#endif
//
// all versions have a <dirent.h>:
//
#if !defined(__STRICT_ANSI__)
#  define BOOST_HAS_DIRENT_H
#endif
//
// all versions support __declspec:
//
#if defined(__STRICT_ANSI__)
// config/platform/win32.hpp will define BOOST_SYMBOL_EXPORT, etc., unless already defined
#  define BOOST_SYMBOL_EXPORT
#endif
//
// ABI fixing headers:
//
#ifndef BOOST_ABI_PREFIX
#  define BOOST_ABI_PREFIX "boost/config/abi/borland_prefix.hpp"
#endif
#ifndef BOOST_ABI_SUFFIX
#  define BOOST_ABI_SUFFIX "boost/config/abi/borland_suffix.hpp"
#endif
//
// Disable Win32 support in ANSI mode:
//
#  pragma defineonoption BOOST_DISABLE_WIN32 -A
//
// MSVC compatibility mode does some nasty things:
// TODO: look up if this doesn't apply to the whole 12xx range
//
#if defined(_MSC_VER) && (_MSC_VER <= 1200)
#  define BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
#  define BOOST_NO_VOID_RETURNS
#endif

#define BOOST_COMPILER "CodeGear C++ version " BOOST_STRINGIZE(__CODEGEARC__)

#endif // #if !defined(__clang__)

/* codegear.hpp
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
*/