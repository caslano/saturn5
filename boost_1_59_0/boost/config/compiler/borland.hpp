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
#define BOOST_NO_CXX11_OVERRIDE
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

#define BOOST_BORLANDC __BORLANDC__
#define BOOST_COMPILER "Classic Borland C++ version " BOOST_STRINGIZE(__BORLANDC__)

/* borland.hpp
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
*/