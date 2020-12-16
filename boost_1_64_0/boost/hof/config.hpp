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
9OEW0/BBOu5slE3Vv/VQDL95ok9/+s4X3fjXy11cW6nQqhHf5wlNURtYXuqDE1P0Q7/5XROslVW9Qvzp/ISLSK/grYoCi0CBul4m6cU/4zFiGNrBUhgb6oKnf5F/GP2UzhnqOqlrq5RfVMeR/biOjRV5bMMv4E9vY0U+f/bCJ1oyj7YsVHgpCC4PvUXPZgKeh+a6HErZLz5XEqMcaXM5xdefU4p8hBUixW1mirORwoMU14u3OIUXYZ2RIqBS1F5GWK3pm4TVj/smYRXGp+ZMdAhtMVuYDAxFtYfn1cwiM9vQOdrwML1M5hk0mBcMMDar46VQiyF+3CAmVc4K6rL9tWiCgdkpCS34TM82dB5jPhA+lH0rbyACr0QmFsjZgBUfYtn1sPVwn/qLVC5xZsEMAO+nPW0BfqcEfrEEfvLV44S8wB0A8piF8mgL8YUyfnhyPHd/KADtA2IcCzF2veqv3auwAr+HJVa/l4YTUsR4VEKPfR1iORAZI/Z25Dq1QSUgGhHNIhOdqXWz0sshfjZIrvX4sREMe4C5/DQtYZyqvUc0nSPHFdeShXLQ8NA5Gf9Q7Dyb1HAoO98Qw/OMQ16vYqOhxWCIQ60Px4zhaHTxjQ4IRPtgdUbZoABhNdSlxF8fviciXhOfM0nEzjcdJ+pvsjf30cZaWH6JpN4N3Y1B6mYYqgCpp+F4csonhKShl14xSbdhRtQd1ZVWt25qvgxNRPoQmHzcEv8USf4YHU0zPjRWykuEKifJHz9339eyaLSYBHB9tTrLqPd9VPf7uVzdpqVsbORlguuKJeNXTmQzsceJxBkB9nEIZgXEMJ4g5TbXkDoaEBnDTC+pgPgp3/hHzVAUEPd1Uh+D/DgTS52O6EdA74B4tbOK7YSzsF3GR221do+J4W2M4c5upL9NkkdlX8T0e+fvin7naOUGet8fqob2rvF5k8QVBzmJQQl93qT4vInGh+jN045JBrHEeQdJYfar2OZMLsgg3qmvJJ3e0+Bl/79+1vNX6eSwwaRKFt0XIZF1hdSQC8NHsl0/XC/PTnNi0+qvsTVN34za0gEKawjpMndNfGhp/GZH/GZn/OYcv16WmzW7HXn4LGnvcSNbYbCnXzRjSloforNrvZkx9LliOsysfnyG9gASQVF+FfH661DMrN0vcy/vv9I3TV48pjB0cPGYC10TYrMas79pmwGdsqN4YpjRbfsAjBsN/5ZdqT4jcaBRDgt07QemajhX+4HseLEuSmzRab/5sGMvypdrGfgsoO3qCJotg858i8jx6Cgwou01F0CzQWcFG5j65JuZSp/sBscT1iYPKylU6zlBmzy7y6l5vdaI3L/FWDBS+Vhl/0RJRAc5qQaLVOE3ovCX3RiuH2Vc+Wy6hbx8mN8aMHlfxL/6sL8XeGY1eGbAi7zxKF47pyZ4JZePDncTrX+jfB0Fa7sNevS90KBHvkmPFzOs9OhM9Pj8UMv06OpW9ECtqEVz4U7GVzV5Gm3mVrXTv89Bnkfr6mPtP7nUd/Jp3AkEsQDQQa4yiSebY8YI9KTsQzlQlx6GPRTnBv72WCzOZ7Ln+zEsvbqfcuSRZyX5nRbj5MLQnOKFNOCcM0gNOHPFkE9jkuW1qsZ2PA97OBelideHGoKUkk3CbvMAZNfPnGoMGoUQX5yMzw4krxI/2RNDprUfozDegS7P9MmdSfeBEMHo/Gt26PBEcaDrP2NxWFJQJa2DZZp1M43/UKKRfjQw5xkV8o1AvjN7ailmmeKa/Ua9F+BgA3T9Oi9o0o7ODDVGkuuPx426TvPDJLS6nar6JNqNTbcZXHiWcknx4YSvHf3JcuMXQzifGwkHUL5rzXy5OMXrSL7yKnpNurA=
*/