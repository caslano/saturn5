//  Copyright 2011 John Maddock
//  Copyright 2013, 2017-2018 Cray, Inc.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

// Cray C++ compiler setup.
//
// There are a few parameters that affect the macros defined in this file:
//
// - What version of CCE (Cray Compiling Environment) are we running? This
//   comes from the '_RELEASE_MAJOR', '_RELEASE_MINOR', and
//   '_RELEASE_PATCHLEVEL' macros.
// - What C++ standards conformance level are we using (e.g. '-h
//   std=c++14')? This comes from the '__cplusplus' macro.
// - Are we using GCC extensions ('-h gnu' or '-h nognu')? If we have '-h
//   gnu' then CCE emulates GCC, and the macros '__GNUC__',
//   '__GNUC_MINOR__', and '__GNUC_PATCHLEVEL__' are defined.
//
// This file is organized as follows:
//
// - Verify that the combination of parameters listed above is supported.
//   If we have an unsupported combination, we abort with '#error'.
// - Establish baseline values for all Boost macros.
// - Apply changes to the baseline macros based on compiler version. These
//   changes are cummulative so each version section only describes the
//   changes since the previous version.
//   - Within each version section, we may also apply changes based on
//     other parameters (i.e. C++ standards conformance level and GCC
//     extensions).
//
// To test changes to this file:
//
// ```
// module load cce/8.6.5 # Pick the version you want to test.
// cd boost/libs/config/test/all
// b2 -j 8 toolset=cray cxxstd=03 cxxstd=11 cxxstd=14 cxxstd-dialect=gnu linkflags=-lrt
// ```
// Note: Using 'cxxstd-dialect=iso' is not supported at this time (the
// tests run, but many tests fail).
//
// Note: 'linkflags=-lrt' is needed in Cray Linux Environment. Otherwise
// you get an 'undefined reference to clock_gettime' error.
//
// Note: If a test '*_fail.cpp' file compiles, but fails to run, then it is
// reported as a defect. However, this is not actually a defect. This is an
// area where the test system is somewhat broken. Tests that are failing
// because of this problem are noted in the comments.
//
// Pay attention to the macro definitions for the macros you wish to
// modify. For example, only macros categorized as compiler macros should
// appear in this file; platform macros should not appear in this file.
// Also, some macros have to be defined to specific values; it is not
// always enough to define or undefine a macro.
//
// Macro definitions are available in the source code at:
//
// `boost/libs/config/doc/html/boost_config/boost_macro_reference.html`
//
// Macro definitions are also available online at:
//
// http://www.boost.org/doc/libs/master/libs/config/doc/html/boost_config/boost_macro_reference.html
//
// Typically, if you enable a feature, and the tests pass, then you have
// nothing to worry about. However, it's sometimes hard to figure out if a
// disabled feature needs to stay disabled. To get a list of disabled
// features, run 'b2' in 'boost/libs/config/checks'. These are the macros
// you should pay attention to (in addition to macros that cause test
// failures).

////
//// Front matter
////

// In a developer build of the Cray compiler (i.e. a compiler built by a
// Cray employee), the release patch level is reported as "x". This gives
// versions that look like e.g. "8.6.x".
//
// To accomplish this, the the Cray compiler preprocessor inserts:
//
// #define _RELEASE_PATCHLEVEL x
//
// If we are using a developer build of the compiler, we want to use the
// configuration macros for the most recent patch level of the release. To
// accomplish this, we'll pretend that _RELEASE_PATCHLEVEL is 99.
//
// However, it's difficult to detect if _RELEASE_PATCHLEVEL is x. We must
// consider that the x will be expanded if x is defined as a macro
// elsewhere. For example, imagine if someone put "-D x=3" on the command
// line, and _RELEASE_PATCHLEVEL is x. Then _RELEASE_PATCHLEVEL would
// expand to 3, and we could not distinguish it from an actual
// _RELEASE_PATCHLEVEL of 3. This problem only affects developer builds; in
// production builds, _RELEASE_PATCHLEVEL is always an integer.
//
// IMPORTANT: In developer builds, if x is defined as a macro, you will get
// an incorrect configuration. The behavior in this case is undefined.
//
// Even if x is not defined, we have to use some trickery to detect if
// _RELEASE_PATCHLEVEL is x. First we define BOOST_CRAY_x to some arbitrary
// magic value, 9867657. Then we use BOOST_CRAY_APPEND to append the
// expanded value of _RELEASE_PATCHLEVEL to the string "BOOST_CRAY_".
//
// - If _RELEASE_PATCHLEVEL is undefined, we get "BOOST_CRAY_".
// - If _RELEASE_PATCHLEVEL is 5, we get "BOOST_CRAY_5".
// - If _RELEASE_PATCHLEVEL is x (and x is not defined) we get
//   "BOOST_CRAY_x":
//
// Then we check if BOOST_CRAY_x is equal to the output of
// BOOST_CRAY_APPEND. In other words, the output of BOOST_CRAY_APPEND is
// treated as a macro name, and expanded again. If we can safely assume
// that BOOST_CRAY_ is not a macro defined as our magic number, and
// BOOST_CRAY_5 is not a macro defined as our magic number, then the only
// way the equality test can pass is if _RELEASE_PATCHLEVEL expands to x.
//
// So, that is how we detect if we are using a developer build of the Cray
// compiler.

#define BOOST_CRAY_x 9867657 // Arbitrary number
#define BOOST_CRAY_APPEND(MACRO) BOOST_CRAY_APPEND_INTERNAL(MACRO)
#define BOOST_CRAY_APPEND_INTERNAL(MACRO) BOOST_CRAY_##MACRO

#if BOOST_CRAY_x == BOOST_CRAY_APPEND(_RELEASE_PATCHLEVEL)

    // This is a developer build.
    //
    // - _RELEASE_PATCHLEVEL is defined as x, and x is not defined as a macro.

    // Pretend _RELEASE_PATCHLEVEL is 99, so we get the configuration for the
    // most recent patch level in this release.

    #define BOOST_CRAY_VERSION (_RELEASE_MAJOR * 10000 + _RELEASE_MINOR * 100 + 99)

#else

    // This is a production build.
    //
    // _RELEASE_PATCHLEVEL is not defined as x, or x is defined as a macro.

    #define BOOST_CRAY_VERSION (_RELEASE_MAJOR * 10000 + _RELEASE_MINOR * 100 + _RELEASE_PATCHLEVEL)

#endif // BOOST_CRAY_x == BOOST_CRAY_APPEND(_RELEASE_PATCHLEVEL)

#undef BOOST_CRAY_APPEND_INTERNAL
#undef BOOST_CRAY_APPEND
#undef BOOST_CRAY_x


#ifdef __GNUC__
#   define BOOST_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif

#ifndef BOOST_COMPILER
#   define BOOST_COMPILER "Cray C++ version " BOOST_STRINGIZE(_RELEASE_MAJOR) "." BOOST_STRINGIZE(_RELEASE_MINOR) "." BOOST_STRINGIZE(_RELEASE_PATCHLEVEL)
#endif

// Since the Cray compiler defines '__GNUC__', we have to emulate some
// additional GCC macros in order to make everything work.
//
// FIXME: Perhaps Cray should fix the compiler to define these additional
// macros for GCC emulation?

#if __cplusplus >= 201103L && defined(__GNUC__) && !defined(__GXX_EXPERIMENTAL_CXX0X__)
#   define __GXX_EXPERIMENTAL_CXX0X__ 1
#endif

////
//// Parameter validation
////

// FIXME: Do we really need to support compilers before 8.5? Do they pass
// the Boost.Config tests?

#if BOOST_CRAY_VERSION < 80000
#  error "Boost is not configured for Cray compilers prior to version 8, please try the configure script."
#endif

// We only support recent EDG based compilers.

#ifndef __EDG__
#  error "Unsupported Cray compiler, please try running the configure script."
#endif

////
//// Baseline values
////

#include <boost/config/compiler/common_edg.hpp>

#define BOOST_HAS_NRVO
#define BOOST_NO_COMPLETE_VALUE_INITIALIZATION
#define BOOST_NO_CXX11_AUTO_DECLARATIONS
#define BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#define BOOST_NO_CXX11_CHAR16_T
#define BOOST_NO_CXX11_CHAR32_T
#define BOOST_NO_CXX11_CONSTEXPR
#define BOOST_NO_CXX11_DECLTYPE
#define BOOST_NO_CXX11_DECLTYPE_N3276
#define BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#define BOOST_NO_CXX11_DELETED_FUNCTIONS
#define BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#define BOOST_NO_CXX11_FINAL
#define BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#define BOOST_NO_CXX11_LAMBDAS
#define BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#define BOOST_NO_CXX11_NOEXCEPT
#define BOOST_NO_CXX11_NULLPTR
#define BOOST_NO_CXX11_RANGE_BASED_FOR
#define BOOST_NO_CXX11_RAW_LITERALS
#define BOOST_NO_CXX11_REF_QUALIFIERS
#define BOOST_NO_CXX11_RVALUE_REFERENCES
#define BOOST_NO_CXX11_SCOPED_ENUMS
#define BOOST_NO_CXX11_SFINAE_EXPR
#define BOOST_NO_CXX11_STATIC_ASSERT
#define BOOST_NO_CXX11_TEMPLATE_ALIASES
#define BOOST_NO_CXX11_THREAD_LOCAL
#define BOOST_NO_CXX11_UNICODE_LITERALS
#define BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#define BOOST_NO_CXX11_USER_DEFINED_LITERALS
#define BOOST_NO_CXX11_VARIADIC_MACROS
#define BOOST_NO_CXX11_VARIADIC_TEMPLATES
#define BOOST_NO_CXX11_UNRESTRICTED_UNION
#define BOOST_NO_SFINAE_EXPR
#define BOOST_NO_TWO_PHASE_NAME_LOOKUP

//#define BOOST_BCB_PARTIAL_SPECIALIZATION_BUG
#define BOOST_MATH_DISABLE_STD_FPCLASSIFY
//#define BOOST_HAS_FPCLASSIFY

#define BOOST_SP_USE_PTHREADS 
#define BOOST_AC_USE_PTHREADS 

//
// Everything that follows is working around what are thought to be
// compiler shortcomings. Revist all of these regularly.
//

//#define BOOST_USE_ENUM_STATIC_ASSERT
//#define BOOST_BUGGY_INTEGRAL_CONSTANT_EXPRESSIONS //(this may be implied by the previous #define

// These constants should be provided by the compiler.

#ifndef __ATOMIC_RELAXED
#define __ATOMIC_RELAXED 0
#define __ATOMIC_CONSUME 1
#define __ATOMIC_ACQUIRE 2
#define __ATOMIC_RELEASE 3
#define __ATOMIC_ACQ_REL 4
#define __ATOMIC_SEQ_CST 5
#endif

////
//// Version changes
////

//
// 8.5.0
//

#if BOOST_CRAY_VERSION >= 80500

#if __cplusplus >= 201103L

#undef BOOST_HAS_NRVO
#undef BOOST_NO_COMPLETE_VALUE_INITIALIZATION
#undef BOOST_NO_CXX11_AUTO_DECLARATIONS
#undef BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#undef BOOST_NO_CXX11_CHAR16_T
#undef BOOST_NO_CXX11_CHAR32_T
#undef BOOST_NO_CXX11_CONSTEXPR
#undef BOOST_NO_CXX11_DECLTYPE
#undef BOOST_NO_CXX11_DECLTYPE_N3276
#undef BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#undef BOOST_NO_CXX11_DELETED_FUNCTIONS
#undef BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#undef BOOST_NO_CXX11_FINAL
#undef BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#undef BOOST_NO_CXX11_LAMBDAS
#undef BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#undef BOOST_NO_CXX11_NOEXCEPT
#undef BOOST_NO_CXX11_NULLPTR
#undef BOOST_NO_CXX11_RANGE_BASED_FOR
#undef BOOST_NO_CXX11_RAW_LITERALS
#undef BOOST_NO_CXX11_REF_QUALIFIERS
#undef BOOST_NO_CXX11_RVALUE_REFERENCES
#undef BOOST_NO_CXX11_SCOPED_ENUMS
#undef BOOST_NO_CXX11_SFINAE_EXPR
#undef BOOST_NO_CXX11_STATIC_ASSERT
#undef BOOST_NO_CXX11_TEMPLATE_ALIASES
#undef BOOST_NO_CXX11_THREAD_LOCAL
#undef BOOST_NO_CXX11_UNICODE_LITERALS
#undef BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#undef BOOST_NO_CXX11_USER_DEFINED_LITERALS
#undef BOOST_NO_CXX11_VARIADIC_MACROS
#undef BOOST_NO_CXX11_VARIADIC_TEMPLATES
#undef BOOST_NO_CXX11_UNRESTRICTED_UNION
#undef BOOST_NO_SFINAE_EXPR
#undef BOOST_NO_TWO_PHASE_NAME_LOOKUP
#undef BOOST_MATH_DISABLE_STD_FPCLASSIFY
#undef BOOST_SP_USE_PTHREADS 
#undef BOOST_AC_USE_PTHREADS 

#define BOOST_HAS_VARIADIC_TMPL
#define BOOST_HAS_UNISTD_H
#define BOOST_HAS_TR1_COMPLEX_INVERSE_TRIG
#define BOOST_HAS_TR1_COMPLEX_OVERLOADS
#define BOOST_HAS_STDINT_H
#define BOOST_HAS_STATIC_ASSERT
#define BOOST_HAS_SIGACTION
#define BOOST_HAS_SCHED_YIELD
#define BOOST_HAS_RVALUE_REFS
#define BOOST_HAS_PTHREADS
#define BOOST_HAS_PTHREAD_YIELD
#define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
#define BOOST_HAS_PARTIAL_STD_ALLOCATOR
#define BOOST_HAS_NRVO
#define BOOST_HAS_NL_TYPES_H
#define BOOST_HAS_NANOSLEEP
#define BOOST_NO_CXX11_SMART_PTR
#define BOOST_NO_CXX11_HDR_FUNCTIONAL
#define BOOST_NO_CXX14_CONSTEXPR
#define BOOST_HAS_LONG_LONG
#define BOOST_HAS_FLOAT128

#if __cplusplus < 201402L
#define BOOST_NO_CXX11_DECLTYPE_N3276
#endif // __cplusplus < 201402L

#endif // __cplusplus >= 201103L

#endif // BOOST_CRAY_VERSION >= 80500

//
// 8.6.4
// (versions prior to 8.6.5 do not define _RELEASE_PATCHLEVEL)
//

#if BOOST_CRAY_VERSION >= 80600

#if __cplusplus >= 199711L
#define BOOST_HAS_FLOAT128
#define BOOST_HAS_PTHREAD_YIELD // This is a platform macro, but it improves test results.
#define BOOST_NO_COMPLETE_VALUE_INITIALIZATION // This is correct. Test compiles, but fails to run.
#undef  BOOST_NO_CXX11_CHAR16_T
#undef  BOOST_NO_CXX11_CHAR32_T
#undef  BOOST_NO_CXX11_INLINE_NAMESPACES
#undef  BOOST_NO_CXX11_FINAL
#undef  BOOST_NO_CXX11_FIXED_LENGTH_VARIADIC_TEMPLATE_EXPANSION_PACKS
#undef  BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#define BOOST_NO_CXX11_SFINAE_EXPR // This is correct, even though '*_fail.cpp' test fails.
#undef  BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#undef  BOOST_NO_CXX11_VARIADIC_MACROS
#undef  BOOST_NO_CXX11_VARIADIC_TEMPLATES
// 'BOOST_NO_DEDUCED_TYPENAME' test is broken. The test files are enabled /
// disabled with an '#ifdef BOOST_DEDUCED_TYPENAME'. However,
// 'boost/libs/config/include/boost/config/detail/suffix.hpp' ensures that
// 'BOOST_DEDUCED_TYPENAME' is always defined (the value it is defined as
// depends on 'BOOST_NO_DEDUCED_TYPENAME'). So, modifying
// 'BOOST_NO_DEDUCED_TYPENAME' has no effect on which tests are run.
//
// The 'no_ded_typename_pass.cpp' test should always compile and run
// successfully, because 'BOOST_DEDUCED_TYPENAME' must always have an
// appropriate value (it's not just something that you turn on or off).
// Therefore, if you wish to test changes to 'BOOST_NO_DEDUCED_TYPENAME',
// you have to modify 'no_ded_typename_pass.cpp' to unconditionally include
// 'boost_no_ded_typename.ipp'.
#undef  BOOST_NO_DEDUCED_TYPENAME // This is correct. Test is broken.
#undef  BOOST_NO_SFINAE_EXPR
#undef  BOOST_NO_TWO_PHASE_NAME_LOOKUP
#endif // __cplusplus >= 199711L

#if __cplusplus >= 201103L
#undef  BOOST_NO_CXX11_ALIGNAS
#undef  BOOST_NO_CXX11_DECLTYPE_N3276
#define BOOST_NO_CXX11_HDR_ATOMIC
#undef  BOOST_NO_CXX11_HDR_FUNCTIONAL
#define BOOST_NO_CXX11_HDR_REGEX // This is correct. Test compiles, but fails to run.
#undef  BOOST_NO_CXX11_SFINAE_EXPR
#undef  BOOST_NO_CXX11_SMART_PTR
#undef  BOOST_NO_CXX11_TRAILING_RESULT_TYPES
#endif // __cplusplus >= 201103L

#if __cplusplus >= 201402L
#undef  BOOST_NO_CXX14_CONSTEXPR
#define BOOST_NO_CXX14_DIGIT_SEPARATORS
#endif // __cplusplus == 201402L

#endif // BOOST_CRAY_VERSION >= 80600

//
// 8.6.5
// (no change from 8.6.4)
//

//
// 8.7.0
//

#if BOOST_CRAY_VERSION >= 80700

#if __cplusplus >= 199711L
#endif // __cplusplus >= 199711L

#if __cplusplus >= 201103L
#undef  BOOST_NO_CXX11_HDR_ATOMIC
#undef  BOOST_NO_CXX11_HDR_REGEX
#endif // __cplusplus >= 201103L

#if __cplusplus >= 201402L
#endif // __cplusplus == 201402L

#endif // BOOST_CRAY_VERSION >= 80700

//
// Next release
//

#if BOOST_CRAY_VERSION > 80799

#if __cplusplus >= 199711L
#endif // __cplusplus >= 199711L

#if __cplusplus >= 201103L
#endif // __cplusplus >= 201103L

#if __cplusplus >= 201402L
#endif // __cplusplus == 201402L

#endif // BOOST_CRAY_VERSION > 80799

////
//// Remove temporary macros
////

// I've commented out some '#undef' statements to signify that we purposely
// want to keep certain macros.

//#undef __GXX_EXPERIMENTAL_CXX0X__
//#undef BOOST_COMPILER
#undef BOOST_GCC_VERSION
#undef BOOST_CRAY_VERSION

/* cray.hpp
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
*/