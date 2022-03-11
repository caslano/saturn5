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