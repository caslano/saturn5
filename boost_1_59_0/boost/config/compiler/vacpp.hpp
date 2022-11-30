//  (C) Copyright John Maddock 2001 - 2003.
//  (C) Copyright Toon Knapen 2001 - 2003.
//  (C) Copyright Lie-Quan Lee 2001.
//  (C) Copyright Markus Schoepflin 2002 - 2003.
//  (C) Copyright Beman Dawes 2002 - 2003.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Visual Age (IBM) C++ compiler setup:

#if __IBMCPP__ <= 501
#  define BOOST_NO_MEMBER_TEMPLATE_FRIENDS
#  define BOOST_NO_MEMBER_FUNCTION_SPECIALIZATIONS
#endif

#if (__IBMCPP__ <= 502)
// Actually the compiler supports inclass member initialization but it
// requires a definition for the class member and it doesn't recognize
// it as an integral constant expression when used as a template argument.
#  define BOOST_NO_INCLASS_MEMBER_INITIALIZATION
#  define BOOST_NO_INTEGRAL_INT64_T
#  define BOOST_NO_MEMBER_TEMPLATE_KEYWORD
#endif

#if (__IBMCPP__ <= 600) || !defined(BOOST_STRICT_CONFIG)
#  define BOOST_NO_POINTER_TO_MEMBER_TEMPLATE_PARAMETERS
#endif

#if (__IBMCPP__ <= 1110)
// XL C++ V11.1 and earlier versions may not always value-initialize
// a temporary object T(), when T is a non-POD aggregate class type.
// Michael Wong (IBM Canada Ltd) has confirmed this issue and gave it
// high priority. -- Niels Dekker (LKEB), May 2010.
#  define BOOST_NO_COMPLETE_VALUE_INITIALIZATION
#endif

//
// On AIX thread support seems to be indicated by _THREAD_SAFE:
//
#ifdef _THREAD_SAFE
#  define BOOST_HAS_THREADS
#endif

#define BOOST_COMPILER "IBM Visual Age version " BOOST_STRINGIZE(__IBMCPP__)

//
// versions check:
// we don't support Visual age prior to version 5:
#if __IBMCPP__ < 500
#error "Compiler not supported or configured - please reconfigure"
#endif
//
// last known and checked version is 1210:
#if (__IBMCPP__ > 1210)
#  if defined(BOOST_ASSERT_CONFIG)
#     error "boost: Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif

// Some versions of the compiler have issues with default arguments on partial specializations
#if __IBMCPP__ <= 1010
#define BOOST_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS
#endif

// Type aliasing hint. Supported since XL C++ 13.1
#if (__IBMCPP__ >= 1310)
#  define BOOST_MAY_ALIAS __attribute__((__may_alias__))
#endif

//
// C++0x features
//
//   See boost\config\suffix.hpp for BOOST_NO_LONG_LONG
//
#if ! __IBMCPP_AUTO_TYPEDEDUCTION
#  define BOOST_NO_CXX11_AUTO_DECLARATIONS
#  define BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#endif
#if ! __IBMCPP_UTF_LITERAL__
#  define BOOST_NO_CXX11_CHAR16_T
#  define BOOST_NO_CXX11_CHAR32_T
#endif
#if ! __IBMCPP_CONSTEXPR
#  define BOOST_NO_CXX11_CONSTEXPR
#endif
#if ! __IBMCPP_DECLTYPE
#  define BOOST_NO_CXX11_DECLTYPE
#else
#  define BOOST_HAS_DECLTYPE
#endif
#define BOOST_NO_CXX11_DECLTYPE_N3276
#define BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#define BOOST_NO_CXX11_DELETED_FUNCTIONS
#if ! __IBMCPP_EXPLICIT_CONVERSION_OPERATORS
#  define BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#endif
#if ! __IBMCPP_EXTERN_TEMPLATE
#  define BOOST_NO_CXX11_EXTERN_TEMPLATE
#endif
#if ! __IBMCPP_VARIADIC_TEMPLATES
// not enabled separately at this time
#  define BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#endif
#define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#define BOOST_NO_CXX11_LAMBDAS
#define BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#define BOOST_NO_CXX11_NOEXCEPT
#define BOOST_NO_CXX11_NULLPTR
#define BOOST_NO_CXX11_RANGE_BASED_FOR
#define BOOST_NO_CXX11_RAW_LITERALS
#define BOOST_NO_CXX11_USER_DEFINED_LITERALS
#if ! __IBMCPP_RVALUE_REFERENCES
#  define BOOST_NO_CXX11_RVALUE_REFERENCES
#endif
#if ! __IBMCPP_SCOPED_ENUM
#  define BOOST_NO_CXX11_SCOPED_ENUMS
#endif
#define BOOST_NO_SFINAE_EXPR
#define BOOST_NO_CXX11_SFINAE_EXPR
#define BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#if ! __IBMCPP_STATIC_ASSERT
#  define BOOST_NO_CXX11_STATIC_ASSERT
#endif
#define BOOST_NO_CXX11_TEMPLATE_ALIASES
#define BOOST_NO_CXX11_UNICODE_LITERALS
#if ! __IBMCPP_VARIADIC_TEMPLATES
#  define BOOST_NO_CXX11_VARIADIC_TEMPLATES
#endif
#if ! __C99_MACRO_WITH_VA_ARGS
#  define BOOST_NO_CXX11_VARIADIC_MACROS
#endif
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

/* vacpp.hpp
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
*/