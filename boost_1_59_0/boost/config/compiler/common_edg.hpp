//  (C) Copyright John Maddock 2001 - 2002.
//  (C) Copyright Jens Maurer 2001.
//  (C) Copyright David Abrahams 2002.
//  (C) Copyright Aleksey Gurtovoy 2002.
//  (C) Copyright Markus Schoepflin 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//
// Options common to all edg based compilers.
//
// This is included from within the individual compiler mini-configs.

#ifndef  __EDG_VERSION__
#  error This file requires that __EDG_VERSION__ be defined.
#endif

#if (__EDG_VERSION__ <= 238)
#   define BOOST_NO_INTEGRAL_INT64_T
#   define BOOST_NO_SFINAE
#endif

#if (__EDG_VERSION__ <= 240)
#   define BOOST_NO_VOID_RETURNS
#endif

#if (__EDG_VERSION__ <= 241) && !defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
#   define BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
#endif

#if (__EDG_VERSION__ <= 244) && !defined(BOOST_NO_TEMPLATE_TEMPLATES)
#   define BOOST_NO_TEMPLATE_TEMPLATES
#endif

#if (__EDG_VERSION__ < 300) && !defined(BOOST_NO_IS_ABSTRACT)
#   define BOOST_NO_IS_ABSTRACT
#endif

#if (__EDG_VERSION__ <= 303) && !defined(BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL)
#   define BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#endif

// See also kai.hpp which checks a Kai-specific symbol for EH
# if !defined(__KCC) && !defined(__EXCEPTIONS) && !defined(BOOST_NO_EXCEPTIONS)
#     define BOOST_NO_EXCEPTIONS
# endif

# if !defined(__NO_LONG_LONG)
#     define BOOST_HAS_LONG_LONG
# else
#     define BOOST_NO_LONG_LONG
# endif

// Not sure what version was the first to support #pragma once, but
// different EDG-based compilers (e.g. Intel) supported it for ages.
// Add a proper version check if it causes problems.
#define BOOST_HAS_PRAGMA_ONCE

//
// C++0x features
//
//   See above for BOOST_NO_LONG_LONG
//
#if (__EDG_VERSION__ < 310)
#  define BOOST_NO_CXX11_EXTERN_TEMPLATE
#endif
#if (__EDG_VERSION__ <= 310)
// No support for initializer lists
#  define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#endif
#if (__EDG_VERSION__ < 400)
#  define BOOST_NO_CXX11_VARIADIC_MACROS
#endif

#define BOOST_NO_CXX11_AUTO_DECLARATIONS
#define BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#define BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#define BOOST_NO_CXX11_DELETED_FUNCTIONS
#define BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#define BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#define BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#define BOOST_NO_CXX11_NOEXCEPT
#define BOOST_NO_CXX11_NULLPTR
#define BOOST_NO_CXX11_RVALUE_REFERENCES
#define BOOST_NO_CXX11_SCOPED_ENUMS
#define BOOST_NO_SFINAE_EXPR
#define BOOST_NO_CXX11_SFINAE_EXPR
#define BOOST_NO_CXX11_STATIC_ASSERT
#define BOOST_NO_CXX11_TEMPLATE_ALIASES
#define BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#define BOOST_NO_CXX11_ALIGNAS
#define BOOST_NO_CXX11_TRAILING_RESULT_TYPES
#define BOOST_NO_CXX11_INLINE_NAMESPACES
#define BOOST_NO_CXX11_REF_QUALIFIERS
#define BOOST_NO_CXX11_FINAL
#define BOOST_NO_CXX11_OVERRIDE
#define BOOST_NO_CXX11_THREAD_LOCAL
#define BOOST_NO_CXX11_UNRESTRICTED_UNION

//__cpp_decltype 200707 possibly?
#define BOOST_NO_CXX11_DECLTYPE
#define BOOST_NO_CXX11_DECLTYPE_N3276

#if !defined(__cpp_unicode_characters) || (__cpp_unicode_characters < 200704)
#   define BOOST_NO_CXX11_CHAR16_T
#   define BOOST_NO_CXX11_CHAR32_T
#endif
#if !defined(__cpp_unicode_literals) || (__cpp_unicode_literals < 200710)
#   define BOOST_NO_CXX11_UNICODE_LITERALS
#endif
#if !defined(__cpp_user_defined_literals) || (__cpp_user_defined_literals < 200809)
#   define BOOST_NO_CXX11_USER_DEFINED_LITERALS
#endif
#if !defined(__cpp_variadic_templates) || (__cpp_variadic_templates < 200704)
#   define BOOST_NO_CXX11_VARIADIC_TEMPLATES
#endif
#if !defined(__cpp_constexpr) || (__cpp_constexpr < 200907)
#   define BOOST_NO_CXX11_CONSTEXPR
#endif
#if !defined(__cpp_lambdas) || (__cpp_lambdas < 200907)
#   define BOOST_NO_CXX11_LAMBDAS
#endif
#if !defined(__cpp_range_based_for) || (__cpp_range_based_for < 200710)
#   define BOOST_NO_CXX11_RANGE_BASED_FOR
#endif
#if !defined(__cpp_raw_strings) || (__cpp_raw_strings < 200610)
#   define BOOST_NO_CXX11_RAW_LITERALS
#endif


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

#ifdef c_plusplus
// EDG has "long long" in non-strict mode
// However, some libraries have insufficient "long long" support
// #define BOOST_HAS_LONG_LONG
#endif

/* common_edg.hpp
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
*/