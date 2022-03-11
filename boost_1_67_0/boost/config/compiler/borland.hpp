//  (C) Copyright John Maddock 2001 - 2003.
//  (C) Copyright David Abrahams 2002 - 2003.
//  (C) Copyright Aleksey Gurtovoy 2002.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Borland C++ compiler setup:

//
// versions check:
// we don't support Borland prior to version 5.4:
#if __BORLANDC__ < 0x540
#  error "Compiler not supported or configured - please reconfigure"
#endif

// last known compiler version:
#if (__BORLANDC__ > 0x613)
//#  if defined(BOOST_ASSERT_CONFIG)
#     error "boost: Unknown compiler version - please run the configure tests and report the results"
//#  else
//#     pragma message( "boost: Unknown compiler version - please run the configure tests and report the results")
//#  endif
#elif (__BORLANDC__ == 0x600)
#  error "CBuilderX preview compiler is no longer supported"
#endif

//
// Support macros to help with standard library detection
#if (__BORLANDC__ < 0x560) || defined(_USE_OLD_RW_STL)
#  define BOOST_BCB_WITH_ROGUE_WAVE
#elif __BORLANDC__ < 0x570
#  define BOOST_BCB_WITH_STLPORT
#else
#  define BOOST_BCB_WITH_DINKUMWARE
#endif

//
// Version 5.0 and below:
#   if __BORLANDC__ <= 0x0550
// Borland C++Builder 4 and 5:
#     define BOOST_NO_MEMBER_TEMPLATE_FRIENDS
#     if __BORLANDC__ == 0x0550
// Borland C++Builder 5, command-line compiler 5.5:
#       define BOOST_NO_OPERATORS_IN_NAMESPACE
#     endif
// Variadic macros do not exist for C++ Builder versions 5 and below
#define BOOST_NO_CXX11_VARIADIC_MACROS
#   endif

// Version 5.51 and below:
#if (__BORLANDC__ <= 0x551)
#  define BOOST_NO_CV_SPECIALIZATIONS
#  define BOOST_NO_CV_VOID_SPECIALIZATIONS
#  define BOOST_NO_DEDUCED_TYPENAME
// workaround for missing WCHAR_MAX/WCHAR_MIN:
#ifdef __cplusplus
#include <climits>
#include <cwchar>
#else
#include <limits.h>
#include <wchar.h>
#endif // __cplusplus
#ifndef WCHAR_MAX
#  define WCHAR_MAX 0xffff
#endif
#ifndef WCHAR_MIN
#  define WCHAR_MIN 0
#endif
#endif

// Borland C++ Builder 6 and below:
#if (__BORLANDC__ <= 0x564)

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

//
// new bug in 5.61:
#if (__BORLANDC__ >= 0x561) && (__BORLANDC__ <= 0x580)
   // this seems to be needed by the command line compiler, but not the IDE:
#  define BOOST_NO_MEMBER_FUNCTION_SPECIALIZATIONS
#endif

// Borland C++ Builder 2006 Update 2 and below:
#if (__BORLANDC__ <= 0x582)
#  define BOOST_NO_SFINAE
#  define BOOST_BCB_PARTIAL_SPECIALIZATION_BUG
#  define BOOST_NO_TEMPLATE_TEMPLATES

#  define BOOST_NO_PRIVATE_IN_AGGREGATE

#  ifdef _WIN32
#     define BOOST_NO_SWPRINTF
#  elif defined(linux) || defined(__linux__) || defined(__linux)
      // we should really be able to do without this
      // but the wcs* functions aren't imported into std::
#     define BOOST_NO_STDC_NAMESPACE
      // _CPPUNWIND doesn't get automatically set for some reason:
#     pragma defineonoption BOOST_CPPUNWIND -x
#  endif
#endif

#if (__BORLANDC__ <= 0x613)  // Beman has asked Alisdair for more info
   // we shouldn't really need this - but too many things choke
   // without it, this needs more investigation:
#  define BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
#  define BOOST_NO_IS_ABSTRACT
#  define BOOST_NO_FUNCTION_TYPE_SPECIALIZATIONS
#  define BOOST_NO_USING_TEMPLATE
#  define BOOST_SP_NO_SP_CONVERTIBLE

// Temporary workaround
#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif

// Borland C++ Builder 2008 and below:
#  define BOOST_NO_INTEGRAL_INT64_T
#  define BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#  define BOOST_NO_DEPENDENT_NESTED_DERIVATIONS
#  define BOOST_NO_MEMBER_TEMPLATE_FRIENDS
#  define BOOST_NO_TWO_PHASE_NAME_LOOKUP
#  define BOOST_NO_USING_DECLARATION_OVERLOADS_FROM_TYPENAME_BASE
#  define BOOST_NO_NESTED_FRIENDSHIP
#  define BOOST_NO_TYPENAME_WITH_CTOR
#if (__BORLANDC__ < 0x600)
#  define BOOST_ILLEGAL_CV_REFERENCES
#endif

//
//  Positive Feature detection
//
// Borland C++ Builder 2008 and below:
#if (__BORLANDC__ >= 0x599)
#  pragma defineonoption BOOST_CODEGEAR_0X_SUPPORT -Ax
#endif
//
// C++0x Macros:
//
#if !defined( BOOST_CODEGEAR_0X_SUPPORT ) || (__BORLANDC__ < 0x610)
#  define BOOST_NO_CXX11_CHAR16_T
#  define BOOST_NO_CXX11_CHAR32_T
#  define BOOST_NO_CXX11_DECLTYPE
#  define BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#  define BOOST_NO_CXX11_EXTERN_TEMPLATE
#  define BOOST_NO_CXX11_RVALUE_REFERENCES
#  define BOOST_NO_CXX11_SCOPED_ENUMS
#  define BOOST_NO_CXX11_STATIC_ASSERT
#else
#  define BOOST_HAS_ALIGNOF
#  define BOOST_HAS_CHAR16_T
#  define BOOST_HAS_CHAR32_T
#  define BOOST_HAS_DECLTYPE
#  define BOOST_HAS_EXPLICIT_CONVERSION_OPS
#  define BOOST_HAS_REF_QUALIFIER
#  define BOOST_HAS_RVALUE_REFS
#  define BOOST_HAS_STATIC_ASSERT
#endif

#define BOOST_NO_CXX11_AUTO_DECLARATIONS
#define BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#define BOOST_NO_CXX11_CONSTEXPR
#define BOOST_NO_CXX11_DECLTYPE_N3276
#define BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#define BOOST_NO_CXX11_DEFAULTED_MOVES
#define BOOST_NO_CXX11_DELETED_FUNCTIONS
#define BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#define BOOST_NO_CXX11_LAMBDAS
#define BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#define BOOST_NO_CXX11_NULLPTR
#define BOOST_NO_CXX11_RANGE_BASED_FOR
#define BOOST_NO_CXX11_RAW_LITERALS
#define BOOST_NO_CXX11_RVALUE_REFERENCES
#define BOOST_NO_CXX11_SCOPED_ENUMS
#define BOOST_NO_SFINAE_EXPR
#define BOOST_NO_CXX11_SFINAE_EXPR
#define BOOST_NO_CXX11_TEMPLATE_ALIASES
#define BOOST_NO_CXX11_UNICODE_LITERALS    // UTF-8 still not supported
#define BOOST_NO_CXX11_VARIADIC_TEMPLATES
#define BOOST_NO_CXX11_NOEXCEPT
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

#if __BORLANDC__ >= 0x590
#  define BOOST_HAS_TR1_HASH

#  define BOOST_HAS_MACRO_USE_FACET
#endif

//
// Post 0x561 we have long long and stdint.h:
#if __BORLANDC__ >= 0x561
#  ifndef __NO_LONG_LONG
#     define BOOST_HAS_LONG_LONG
#  else
#     define BOOST_NO_LONG_LONG
#  endif
   // On non-Win32 platforms let the platform config figure this out:
#  ifdef _WIN32
#      define BOOST_HAS_STDINT_H
#  endif
#endif

// Borland C++Builder 6 defaults to using STLPort.  If _USE_OLD_RW_STL is
// defined, then we have 0x560 or greater with the Rogue Wave implementation
// which presumably has the std::DBL_MAX bug.
#if defined( BOOST_BCB_WITH_ROGUE_WAVE )
// <climits> is partly broken, some macros define symbols that are really in
// namespace std, so you end up having to use illegal constructs like
// std::DBL_MAX, as a fix we'll just include float.h and have done with:
#include <float.h>
#endif
//
// __int64:
//
#if (__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__)
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
#ifndef __STRICT_ANSI__
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
#if __BORLANDC__ != 0x600 // not implemented for version 6 compiler yet
#ifndef BOOST_ABI_PREFIX
#  define BOOST_ABI_PREFIX "boost/config/abi/borland_prefix.hpp"
#endif
#ifndef BOOST_ABI_SUFFIX
#  define BOOST_ABI_SUFFIX "boost/config/abi/borland_suffix.hpp"
#endif
#endif
//
// Disable Win32 support in ANSI mode:
//
#if __BORLANDC__ < 0x600
#  pragma defineonoption BOOST_DISABLE_WIN32 -A
#elif defined(__STRICT_ANSI__)
#  define BOOST_DISABLE_WIN32
#endif
//
// MSVC compatibility mode does some nasty things:
// TODO: look up if this doesn't apply to the whole 12xx range
//
#if defined(_MSC_VER) && (_MSC_VER <= 1200)
#  define BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
#  define BOOST_NO_VOID_RETURNS
#endif

// Borland did not implement value-initialization completely, as I reported
// in 2007, Borland Report 51854, "Value-initialization: POD struct should be
// zero-initialized", http://qc.embarcadero.com/wc/qcmain.aspx?d=51854
// See also: http://www.boost.org/libs/utility/value_init.htm#compiler_issues
// (Niels Dekker, LKEB, April 2010)
#define BOOST_NO_COMPLETE_VALUE_INITIALIZATION

#define BOOST_COMPILER "Borland C++ version " BOOST_STRINGIZE(__BORLANDC__)

/* borland.hpp
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
*/