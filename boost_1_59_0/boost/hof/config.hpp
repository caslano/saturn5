/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    config.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_CONFIG_HPP
#define BOOST_HOF_GUARD_CONFIG_HPP

// Unpack has extra checks to ensure that the function will be invoked with
// the sequence. This extra check can help improve error reporting but it can
// slow down compilation. This is enabled by default.
#ifndef BOOST_HOF_CHECK_UNPACK_SEQUENCE
#define BOOST_HOF_CHECK_UNPACK_SEQUENCE 1
#endif

// Check for std version
#if __cplusplus >= 201606
#define BOOST_HOF_HAS_STD_17 1
#else
#define BOOST_HOF_HAS_STD_17 0
#endif

#if __cplusplus >= 201402
#define BOOST_HOF_HAS_STD_14 1
#else
#define BOOST_HOF_HAS_STD_14 0
#endif

#if __cplusplus >= 201103
#define BOOST_HOF_HAS_STD_11 1
#else
#define BOOST_HOF_HAS_STD_11 0
#endif


// This determines if it safe to use inheritance for EBO. On every platform
// except clang, compilers have problems with ambigous base conversion. So
// this configures the library to use a different technique to achieve empty
// optimization.
#ifndef BOOST_HOF_HAS_EBO
#ifdef __clang__
#define BOOST_HOF_HAS_EBO 1
#else
#define BOOST_HOF_HAS_EBO 0
#endif
#endif

// This configures the library whether expression sfinae can be used to detect
// callability of a function.
#ifndef BOOST_HOF_NO_EXPRESSION_SFINAE
#ifdef _MSC_VER
#define BOOST_HOF_NO_EXPRESSION_SFINAE 1
#else
#define BOOST_HOF_NO_EXPRESSION_SFINAE 0
#endif
#endif

// This configures the library to use manual type deduction in a few places
// where it problematic on a few platforms.
#ifndef BOOST_HOF_HAS_MANUAL_DEDUCTION
#if (defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 8)
#define BOOST_HOF_HAS_MANUAL_DEDUCTION 1
#else
#define BOOST_HOF_HAS_MANUAL_DEDUCTION 0
#endif
#endif

// Whether the compiler has relaxed constexpr.
#ifndef BOOST_HOF_HAS_RELAXED_CONSTEXPR
#ifdef __cpp_constexpr
#if __cpp_constexpr >= 201304
#define BOOST_HOF_HAS_RELAXED_CONSTEXPR 1
#else
#define BOOST_HOF_HAS_RELAXED_CONSTEXPR 0
#endif
#else
#define BOOST_HOF_HAS_RELAXED_CONSTEXPR BOOST_HOF_HAS_STD_14
#endif
#endif

// Whether the compiler supports generic lambdas
#ifndef BOOST_HOF_HAS_GENERIC_LAMBDA
#if defined(__cpp_generic_lambdas) || defined(_MSC_VER)
#define BOOST_HOF_HAS_GENERIC_LAMBDA 1
#else
#define BOOST_HOF_HAS_GENERIC_LAMBDA BOOST_HOF_HAS_STD_14
#endif
#endif

// Whether the compiler supports constexpr lambdas
#ifndef BOOST_HOF_HAS_CONSTEXPR_LAMBDA
#if defined(__cpp_constexpr) && __cpp_constexpr >= 201603
#define BOOST_HOF_HAS_CONSTEXPR_LAMBDA 1
#else
#define BOOST_HOF_HAS_CONSTEXPR_LAMBDA BOOST_HOF_HAS_STD_17
#endif
#endif

// Whether the compiler supports inline variables
#ifndef BOOST_HOF_HAS_INLINE_VARIABLES
#if defined(__cpp_inline_variables)
#define BOOST_HOF_HAS_INLINE_VARIABLES 1
#else
#define BOOST_HOF_HAS_INLINE_VARIABLES BOOST_HOF_HAS_STD_17
#endif
#endif

// Whether inline variables defined with lambdas have external linkage.
// Currently, no compiler supports this yet.
#ifndef BOOST_HOF_HAS_INLINE_LAMBDAS
#define BOOST_HOF_HAS_INLINE_LAMBDAS 0
#endif

// Whether the compiler supports variable templates
#ifndef BOOST_HOF_HAS_VARIABLE_TEMPLATES
#if defined(__clang__) && __clang_major__ == 3 && __clang_minor__ < 5
#define BOOST_HOF_HAS_VARIABLE_TEMPLATES 0
#elif defined(__cpp_variable_templates)
#define BOOST_HOF_HAS_VARIABLE_TEMPLATES 1
#else
#define BOOST_HOF_HAS_VARIABLE_TEMPLATES BOOST_HOF_HAS_STD_14
#endif
#endif

// Whether a constexpr function can use a void return type
#ifndef BOOST_HOF_NO_CONSTEXPR_VOID
#if BOOST_HOF_HAS_RELAXED_CONSTEXPR
#define BOOST_HOF_NO_CONSTEXPR_VOID 0
#else
#define BOOST_HOF_NO_CONSTEXPR_VOID 1
#endif
#endif

// Whether to use template aliases
#ifndef BOOST_HOF_HAS_TEMPLATE_ALIAS
#if defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 8
#define BOOST_HOF_HAS_TEMPLATE_ALIAS 0
#else
#define BOOST_HOF_HAS_TEMPLATE_ALIAS 1
#endif
#endif

// Whether evaluations of function in brace initialization is ordered from
// left-to-right.
#ifndef BOOST_HOF_NO_ORDERED_BRACE_INIT
#if (defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 9) || defined(_MSC_VER)
#define BOOST_HOF_NO_ORDERED_BRACE_INIT 1
#else
#define BOOST_HOF_NO_ORDERED_BRACE_INIT 0
#endif 
#endif

// Whether the compiler has trouble mangling some expressions used in
// decltype.
#ifndef BOOST_HOF_HAS_MANGLE_OVERLOAD
#if defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7
#define BOOST_HOF_HAS_MANGLE_OVERLOAD 0
#else
#define BOOST_HOF_HAS_MANGLE_OVERLOAD 1
#endif
#endif

// Whether an incomplete 'this' pointer can be used in a trailing decltype.
#ifndef BOOST_HOF_HAS_COMPLETE_DECLTYPE
#if !BOOST_HOF_HAS_MANGLE_OVERLOAD || (defined(__GNUC__) && !defined (__clang__))
#define BOOST_HOF_HAS_COMPLETE_DECLTYPE 0
#else
#define BOOST_HOF_HAS_COMPLETE_DECLTYPE 1
#endif
#endif

// Whether function will deduce noexcept from an expression
#ifndef BOOST_HOF_HAS_NOEXCEPT_DEDUCTION
#if defined(__GNUC__) && !defined (__clang__) && ((__GNUC__ == 4 && __GNUC_MINOR__ < 8) || (__GNUC__ == 7 && __GNUC_MINOR__ == 1))
#define BOOST_HOF_HAS_NOEXCEPT_DEDUCTION 0
#else
#define BOOST_HOF_HAS_NOEXCEPT_DEDUCTION 1
#endif
#endif

// Some type expansion failures on gcc 4.6
#ifndef BOOST_HOF_NO_TYPE_PACK_EXPANSION_IN_TEMPLATE
#if defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7
#define BOOST_HOF_NO_TYPE_PACK_EXPANSION_IN_TEMPLATE 1
#else
#define BOOST_HOF_NO_TYPE_PACK_EXPANSION_IN_TEMPLATE 0
#endif
#endif

// Whether to use std::default_constructible, it is a little buggy on gcc 4.6.
#ifndef BOOST_HOF_NO_STD_DEFAULT_CONSTRUCTIBLE
#if defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7
#define BOOST_HOF_NO_STD_DEFAULT_CONSTRUCTIBLE 1
#else
#define BOOST_HOF_NO_STD_DEFAULT_CONSTRUCTIBLE 0
#endif
#endif

#endif

/* config.hpp
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
*/