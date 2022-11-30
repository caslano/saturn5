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
#  define BOOST_NO_CXX11_OVERRIDE
#endif

// C++0x features in 4.8.n and later
//
#if (BOOST_GCC_VERSION < 40800) || !defined(BOOST_GCC_CXX11)
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

// C++0x features in 4.9.n and later
//
#if (BOOST_GCC_VERSION < 40900) || !defined(BOOST_GCC_CXX11)
// Although alignas support is added in gcc 4.8, it does not accept
// dependent constant expressions as an argument until gcc 4.9.
#  define BOOST_NO_CXX11_ALIGNAS
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

#if (__GNUC__ < 11) && defined(__MINGW32__) && !defined(__MINGW64__)
// thread_local was broken on mingw for all 32bit compiler releases prior to 11.x, see
// https://sourceforge.net/p/mingw-w64/bugs/527/
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=83562
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