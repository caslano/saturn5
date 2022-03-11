//  (C) Copyright John Maddock 2001 - 2003.
//  (C) Copyright David Abrahams 2002 - 2003.
//  (C) Copyright Aleksey Gurtovoy 2002.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  CodeGear C++ compiler setup:

#if !defined( BOOST_WITH_CODEGEAR_WARNINGS )
// these warnings occur frequently in optimized template code
# pragma warn -8004 // var assigned value, but never used
# pragma warn -8008 // condition always true/false
# pragma warn -8066 // dead code can never execute
# pragma warn -8104 // static members with ctors not threadsafe
# pragma warn -8105 // reference member in class without ctors
#endif
//
// versions check:
// last known and checked version is 0x621
#if (__CODEGEARC__ > 0x621)
#  if defined(BOOST_ASSERT_CONFIG)
#     error "boost: Unknown compiler version - please run the configure tests and report the results"
#  else
#     pragma message( "boost: Unknown compiler version - please run the configure tests and report the results")
#  endif
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
#define BOOST_NO_CXX11_THREAD_LOCAL
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


/* codegear.hpp
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
*/