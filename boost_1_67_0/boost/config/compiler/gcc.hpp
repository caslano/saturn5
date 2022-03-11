//  (C) Copyright John Maddock 2001 - 2003.
//  (C) Copyright Darin Adler 2001 - 2002.
//  (C) Copyright Jens Maurer 2001 - 2002.
//  (C) Copyright Beman Dawes 2001 - 2003.
//  (C) Copyright Douglas Gregor 2002.
//  (C) Copyright David Abrahams 2002 - 2003.
//  (C) Copyright Synge Todo 2003.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  GNU C++ compiler setup.

//
// Define BOOST_GCC so we know this is "real" GCC and not some pretender:
//
#define BOOST_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#if !defined(__CUDACC__)
#define BOOST_GCC BOOST_GCC_VERSION
#endif

#if defined(__GXX_EXPERIMENTAL_CXX0X__) || (__cplusplus >= 201103L)
#  define BOOST_GCC_CXX11
#endif

#if __GNUC__ == 3
#  if defined (__PATHSCALE__)
#     define BOOST_NO_TWO_PHASE_NAME_LOOKUP
#     define BOOST_NO_IS_ABSTRACT
#  endif

#  if __GNUC_MINOR__ < 4
#     define BOOST_NO_IS_ABSTRACT
#  endif
#  define BOOST_NO_CXX11_EXTERN_TEMPLATE
#endif
#if __GNUC__ < 4
//
// All problems to gcc-3.x and earlier here:
//
#define BOOST_NO_TWO_PHASE_NAME_LOOKUP
#  ifdef __OPEN64__
#     define BOOST_NO_IS_ABSTRACT
#  endif
#endif

// GCC prior to 3.4 had #pragma once too but it didn't work well with filesystem links
#if BOOST_GCC_VERSION >= 30400
#define BOOST_HAS_PRAGMA_ONCE
#endif

#if BOOST_GCC_VERSION < 40400
// Previous versions of GCC did not completely implement value-initialization:
// GCC Bug 30111, "Value-initialization of POD base class doesn't initialize
// members", reported by Jonathan Wakely in 2006,
// http://gcc.gnu.org/bugzilla/show_bug.cgi?id=30111 (fixed for GCC 4.4)
// GCC Bug 33916, "Default constructor fails to initialize array members",
// reported by Michael Elizabeth Chastain in 2007,
// http://gcc.gnu.org/bugzilla/show_bug.cgi?id=33916 (fixed for GCC 4.2.4)
// See also: http://www.boost.org/libs/utility/value_init.htm#compiler_issues
#define BOOST_NO_COMPLETE_VALUE_INITIALIZATION
#endif

#if !defined(__EXCEPTIONS) && !defined(BOOST_NO_EXCEPTIONS)
# define BOOST_NO_EXCEPTIONS
#endif


//
// Threading support: Turn this on unconditionally here (except for
// those platforms where we can know for sure). It will get turned off again
// later if no threading API is detected.
//
#if !defined(__MINGW32__) && !defined(linux) && !defined(__linux) && !defined(__linux__)
# define BOOST_HAS_THREADS
#endif

//
// gcc has "long long"
// Except on Darwin with standard compliance enabled (-pedantic)
// Apple gcc helpfully defines this macro we can query
//
#if !defined(__DARWIN_NO_LONG_LONG)
# define BOOST_HAS_LONG_LONG
#endif

//
// gcc implements the named return value optimization since version 3.1
//
#define BOOST_HAS_NRVO

// Branch prediction hints
#define BOOST_LIKELY(x) __builtin_expect(x, 1)
#define BOOST_UNLIKELY(x) __builtin_expect(x, 0)

//
// Dynamic shared object (DSO) and dynamic-link library (DLL) support
//
#if __GNUC__ >= 4
#  if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(__CYGWIN__)
     // All Win32 development environments, including 64-bit Windows and MinGW, define
     // _WIN32 or one of its variant spellings. Note that Cygwin is a POSIX environment,
     // so does not define _WIN32 or its variants, but still supports dllexport/dllimport.
#    define BOOST_HAS_DECLSPEC
#    define BOOST_SYMBOL_EXPORT __attribute__((__dllexport__))
#    define BOOST_SYMBOL_IMPORT __attribute__((__dllimport__))
#  else
#    define BOOST_SYMBOL_EXPORT __attribute__((__visibility__("default")))
#    define BOOST_SYMBOL_IMPORT
#  endif
#  define BOOST_SYMBOL_VISIBLE __attribute__((__visibility__("default")))
#else
// config/platform/win32.hpp will define BOOST_SYMBOL_EXPORT, etc., unless already defined
#  define BOOST_SYMBOL_EXPORT
#endif

//
// RTTI and typeinfo detection is possible post gcc-4.3:
//
#if BOOST_GCC_VERSION > 40300
#  ifndef __GXX_RTTI
#     ifndef BOOST_NO_TYPEID
#        define BOOST_NO_TYPEID
#     endif
#     ifndef BOOST_NO_RTTI
#        define BOOST_NO_RTTI
#     endif
#  endif
#endif

//
// Recent GCC versions have __int128 when in 64-bit mode.
//
// We disable this if the compiler is really nvcc with C++03 as it
// doesn't actually support __int128 as of CUDA_VERSION=7500
// even though it defines __SIZEOF_INT128__.
// See https://svn.boost.org/trac/boost/ticket/8048
//     https://svn.boost.org/trac/boost/ticket/11852
// Only re-enable this for nvcc if you're absolutely sure
// of the circumstances under which it's supported:
//
#if defined(__CUDACC__)
#  if defined(BOOST_GCC_CXX11)
#    define BOOST_NVCC_CXX11
#  else
#    define BOOST_NVCC_CXX03
#  endif
#endif

#if defined(__SIZEOF_INT128__) && !defined(BOOST_NVCC_CXX03)
#  define BOOST_HAS_INT128
#endif
//
// Recent GCC versions have a __float128 native type, we need to
// include a std lib header to detect this - not ideal, but we'll
// be including <cstddef> later anyway when we select the std lib.
//
// Nevertheless, as of CUDA 7.5, using __float128 with the host
// compiler in pre-C++11 mode is still not supported.
// See https://svn.boost.org/trac/boost/ticket/11852
//
#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif
#if defined(_GLIBCXX_USE_FLOAT128) && !defined(__STRICT_ANSI__) && !defined(BOOST_NVCC_CXX03)
# define BOOST_HAS_FLOAT128
#endif

// C++0x features in 4.3.n and later
//
#if (BOOST_GCC_VERSION >= 40300) && defined(BOOST_GCC_CXX11)
// C++0x features are only enabled when -std=c++0x or -std=gnu++0x are
// passed on the command line, which in turn defines
// __GXX_EXPERIMENTAL_CXX0X__.
#  define BOOST_HAS_DECLTYPE
#  define BOOST_HAS_RVALUE_REFS
#  define BOOST_HAS_STATIC_ASSERT
#  define BOOST_HAS_VARIADIC_TMPL
#else
#  define BOOST_NO_CXX11_DECLTYPE
#  define BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#  define BOOST_NO_CXX11_RVALUE_REFERENCES
#  define BOOST_NO_CXX11_STATIC_ASSERT
#endif

// C++0x features in 4.4.n and later
//
#if (BOOST_GCC_VERSION < 40400) || !defined(BOOST_GCC_CXX11)
#  define BOOST_NO_CXX11_AUTO_DECLARATIONS
#  define BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#  define BOOST_NO_CXX11_CHAR16_T
#  define BOOST_NO_CXX11_CHAR32_T
#  define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#  define BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#  define BOOST_NO_CXX11_DELETED_FUNCTIONS
#  define BOOST_NO_CXX11_TRAILING_RESULT_TYPES
#  define BOOST_NO_CXX11_INLINE_NAMESPACES
#  define BOOST_NO_CXX11_VARIADIC_TEMPLATES
#endif

#if BOOST_GCC_VERSION < 40500
#  define BOOST_NO_SFINAE_EXPR
#endif

// GCC 4.5 forbids declaration of defaulted functions in private or protected sections
#if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ == 5) || !defined(BOOST_GCC_CXX11)
#  define BOOST_NO_CXX11_NON_PUBLIC_DEFAULTED_FUNCTIONS
#endif

// C++0x features in 4.5.0 and later
//
#if (BOOST_GCC_VERSION < 40500) || !defined(BOOST_GCC_CXX11)
#  define BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#  define BOOST_NO_CXX11_LAMBDAS
#  define BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#  define BOOST_NO_CXX11_RAW_LITERALS
#  define BOOST_NO_CXX11_UNICODE_LITERALS
#endif

// C++0x features in 4.5.1 and later
//
#if (BOOST_GCC_VERSION < 40501) || !defined(BOOST_GCC_CXX11)
// scoped enums have a serious bug in 4.4.0, so define BOOST_NO_CXX11_SCOPED_ENUMS before 4.5.1
// See http://gcc.gnu.org/bugzilla/show_bug.cgi?id=38064
#  define BOOST_NO_CXX11_SCOPED_ENUMS
#endif

// C++0x features in 4.6.n and later
//
#if (BOOST_GCC_VERSION < 40600) || !defined(BOOST_GCC_CXX11)
#define BOOST_NO_CXX11_DEFAULTED_MOVES
#define BOOST_NO_CXX11_NOEXCEPT
#define BOOST_NO_CXX11_NULLPTR
#define BOOST_NO_CXX11_RANGE_BASED_FOR
#define BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#endif

// C++0x features in 4.7.n and later
//
#if (BOOST_GCC_VERSION < 40700) || !defined(BOOST_GCC_CXX11)
// Note that while constexpr is partly supported in gcc-4.6 it's a 
// pre-std version with several bugs:
#  define BOOST_NO_CXX11_CONSTEXPR
#  define BOOST_NO_CXX11_FINAL
#  define BOOST_NO_CXX11_TEMPLATE_ALIASES
#  define BOOST_NO_CXX11_USER_DEFINED_LITERALS
#  define BOOST_NO_CXX11_FIXED_LENGTH_VARIADIC_TEMPLATE_EXPANSION_PACKS
#endif

// C++0x features in 4.8.n and later
//
#if (BOOST_GCC_VERSION < 40800) || !defined(BOOST_GCC_CXX11)
#  define BOOST_NO_CXX11_ALIGNAS
#  define BOOST_NO_CXX11_THREAD_LOCAL
#  define BOOST_NO_CXX11_SFINAE_EXPR
#endif

// C++0x features in 4.8.1 and later
//
#if (BOOST_GCC_VERSION < 40801) || !defined(BOOST_GCC_CXX11)
#  define BOOST_NO_CXX11_DECLTYPE_N3276
#  define BOOST_NO_CXX11_REF_QUALIFIERS
#  define BOOST_NO_CXX14_BINARY_LITERALS
#endif

// C++0x features in 5.1 and later
//
#if (BOOST_GCC_VERSION < 50100) || !defined(BOOST_GCC_CXX11)
#  define BOOST_NO_CXX11_UNRESTRICTED_UNION
#endif

// C++14 features in 4.9.0 and later
//
#if (BOOST_GCC_VERSION < 40900) || (__cplusplus < 201300)
#  define BOOST_NO_CXX14_RETURN_TYPE_DEDUCTION
#  define BOOST_NO_CXX14_GENERIC_LAMBDAS
#  define BOOST_NO_CXX14_DIGIT_SEPARATORS
#  define BOOST_NO_CXX14_DECLTYPE_AUTO
#  if !((BOOST_GCC_VERSION >= 40801) && (BOOST_GCC_VERSION < 40900) && defined(BOOST_GCC_CXX11))
#     define BOOST_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES
#  endif
#endif


// C++ 14:
#if !defined(__cpp_aggregate_nsdmi) || (__cpp_aggregate_nsdmi < 201304)
#  define BOOST_NO_CXX14_AGGREGATE_NSDMI
#endif
#if !defined(__cpp_constexpr) || (__cpp_constexpr < 201304)
#  define BOOST_NO_CXX14_CONSTEXPR
#endif
#if (BOOST_GCC_VERSION < 50200) || !defined(__cpp_variable_templates) || (__cpp_variable_templates < 201304)
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

#if __GNUC__ >= 7
#  define BOOST_FALLTHROUGH __attribute__((fallthrough))
#endif

#if defined(__MINGW32__) && !defined(__MINGW64__)
// Currently (March 2019) thread_local is broken on mingw for all current 32bit compiler releases, see
// https://sourceforge.net/p/mingw-w64/bugs/527/
// Not setting this causes program termination on thread exit.
#define BOOST_NO_CXX11_THREAD_LOCAL
#endif

//
// Unused attribute:
#if __GNUC__ >= 4
#  define BOOST_ATTRIBUTE_UNUSED __attribute__((__unused__))
#endif

// Type aliasing hint. Supported since gcc 3.3.
#define BOOST_MAY_ALIAS __attribute__((__may_alias__))

//
// __builtin_unreachable:
#if BOOST_GCC_VERSION >= 40500
#define BOOST_UNREACHABLE_RETURN(x) __builtin_unreachable();
#endif

#ifndef BOOST_COMPILER
#  define BOOST_COMPILER "GNU C++ version " __VERSION__
#endif

// ConceptGCC compiler:
//   http://www.generic-programming.org/software/ConceptGCC/
#ifdef __GXX_CONCEPTS__
#  define BOOST_HAS_CONCEPTS
#  define BOOST_COMPILER "ConceptGCC version " __VERSION__
#endif

// versions check:
// we don't know gcc prior to version 3.30:
#if (BOOST_GCC_VERSION< 30300)
#  error "Compiler not configured - please reconfigure"
#endif
//
// last known and checked version is 8.1:
#if (BOOST_GCC_VERSION > 80100)
#  if defined(BOOST_ASSERT_CONFIG)
#     error "Boost.Config is older than your compiler - please check for an updated Boost release."
#  else
// we don't emit warnings here anymore since there are no defect macros defined for
// gcc post 3.4, so any failures are gcc regressions...
//#     warning "boost: Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif


/* gcc.hpp
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
*/