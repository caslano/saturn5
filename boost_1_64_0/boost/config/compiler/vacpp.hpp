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
sRtLZfRzFLb949L3TWVKBbyJbXxiCLBcIL5Hb6td5zLw3avXzU/lxF5tyMU/GAA7I5suurFt7vw4Ov+j/OBb//IaHHu8ECqNbR/gxJLJVdKDzPcR5Qff7AzQ7Bx0bvfGjaeJNJ7+a0jfFgm6ox4vbZgsh/Q/QHpsYCjEpgVwb4m6vYODxnvt3iHwUhH5H0e6mNcVD3kGxDiOevZXTHdHI0Pwcrfo909Bmnen2xsbCkYj8YHotqFgxCvXLxyOsyo6B7zOdT1M185x/hofk/6Jv2+L7AhGPPFAcBDGjWsNt0he7nPbEA/CyBIbGuBpz0AengXbyeqibcH2bYuwnVnftogb68TrqSPmH4wHnBFPyEvNYuX/UmmDJzgYiw4Ged6lgE+DvLWqF4fBbuBakC3vX7HYYByyDpFog5HgkCQTbPt04BWG9a+T12sG1quGAFF+z0KMF4zhKIXMn7dFkbnXHR3waEJW8C+eoBXK4JDH6a9EPtgs55A7AG0XnxCxJ1H2NZgtkcbtlG7VVWwzvdup4FZdJrvwKM5Fcn9mPVk5zFsJY99zp0i7hNOeq01LfS31GnkMIjIxEpFtueLWyei8zHeM1mtos+GcC/6yA+WsO1EoAw3ZfhPUZpUuBDWrFHxwwxZ7tDdXLu4zeZ5TabdnYAGayG7L7TXu45XpHXrdpNuWG2MyT9Ew4ctkwXqR/eTbJXpYXNXNQvacRI9WeaVYTOeEESitWTslOhr8icyg01E/7ka5Bkscyhd9abwkDqTpEn5IQaeJuSIBcSit4mf9cBbT+8O/wu8NHZkaMACBOMCTnt8fngs0jl9zGv5JBAXycAB+2yjOrTKPWD6TQ7PP6O9e7C9D0Vg8BPZMKG72Dl8wBOOkOSZ5dkBnMc7t5/C+ty0UjfjxvJ/zCdVnRLaTQ+nPsWgwYozGyGMI69IfiUa2R0POoWDIK3qvRIdlY7vlfu1SxxUiRtoIYnwQovtRoH+79XryV32skM46p8tncA8pNMAytzvNpm+iNcvttSu01oKJ530qXe3+KXywWpA2aXTLeNJQ4TgPeirRHWuT6QoQIziTr5SIkHRzo2H3UaHMbCVTBOiksbKgT0In3bVsA35VhmR8FIZtoIOxzd52fjqcu9xb0Y5zDnjcvrg74HX30xSi2t55vZqNvC689J1W21YyXKRxvIPqJBs5SrVoTO2SeHIKxrkUT+OSM5lO8bZ2nN/2Wi50C/7s0SepJ9liSHf+sj2O88t5JfseU2v7UukbTyfa0UyqxC+sTEpDV+9p3avZFJpsYre5Zj7LxjEjMIMRqCdegSC+U9afpbgGftbkdUWapeetK9LUriuOYX6QcTDs9HvjoajTw17tC/rjniAYG2hMGf5Y56fTVgJNsCYNmoCGr9FAcAgsMsM+8DsmkZE44/6bYT+k9oErVbZkdFmU0Qhc3ZT2qnYaa0MMxF7Go9F6GVD2z956fr44RncCXcxozFAIZitnKORyuvuhTFPXS/pUyuR+G2wvgNNX8K8UfOsM0kOjJZvobWZbECZSTodtmN0xFX78/AgDxeiT8BN7lEa52JKSscMeh0hGezB6PJ8/pl30xBYNaZADw1iMHzBZ0in8vYLGX0mT/T7xXpVen+cmXnav/P0ytJqlG2e4fMR7ealMnk5sKZ4n20fZGo8a6biHB5twDnBX3hpXMjIPk1GR3+G4ytEb73cSn2NT5VNKJnJVbLAt/J4d9LOifmFtEXtCLcY3Hc2WsRtIbxvxuhlvH+G5S7yYz5fjOZCjw7FumwTwNCfp3UbJFgxSdQZDcCAQgGMcmg8eupt9A6yZxC1lbHXH8cxK29fDaTvY99pa3UjK6HBc69y58zo=
*/