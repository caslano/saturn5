//  (C) Copyright John Maddock 2001.
//  (C) Copyright Darin Adler 2001.
//  (C) Copyright Peter Dimov 2001.
//  (C) Copyright David Abrahams 2001 - 2002.
//  (C) Copyright Beman Dawes 2001 - 2003.
//  (C) Copyright Stefan Slapeta 2004.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Metrowerks C++ compiler setup:

// locale support is disabled when linking with the dynamic runtime
#   ifdef _MSL_NO_LOCALE
#     define BOOST_NO_STD_LOCALE
#   endif

#   if __MWERKS__ <= 0x2301  // 5.3
#     define BOOST_NO_FUNCTION_TEMPLATE_ORDERING
#     define BOOST_NO_POINTER_TO_MEMBER_CONST
#     define BOOST_NO_DEPENDENT_TYPES_IN_TEMPLATE_VALUE_PARAMETERS
#     define BOOST_NO_MEMBER_TEMPLATE_KEYWORD
#   endif

#   if __MWERKS__ <= 0x2401  // 6.2
//#     define BOOST_NO_FUNCTION_TEMPLATE_ORDERING
#   endif

#   if(__MWERKS__ <= 0x2407)  // 7.x
#     define BOOST_NO_MEMBER_FUNCTION_SPECIALIZATIONS
#     define BOOST_NO_UNREACHABLE_RETURN_DETECTION
#   endif

#   if(__MWERKS__ <= 0x3003)  // 8.x
#     define BOOST_NO_SFINAE
#    endif

// the "|| !defined(BOOST_STRICT_CONFIG)" part should apply to the last
// tested version *only*:
#   if(__MWERKS__ <= 0x3207) || !defined(BOOST_STRICT_CONFIG) // 9.6
#     define BOOST_NO_MEMBER_TEMPLATE_FRIENDS
#     define BOOST_NO_IS_ABSTRACT
#    endif

#if !__option(wchar_type)
#   define BOOST_NO_INTRINSIC_WCHAR_T
#endif

#if !__option(exceptions) && !defined(BOOST_NO_EXCEPTIONS)
#   define BOOST_NO_EXCEPTIONS
#endif

#if (__INTEL__ && _WIN32) || (__POWERPC__ && macintosh)
#   if __MWERKS__ == 0x3000
#     define BOOST_COMPILER_VERSION 8.0
#   elif __MWERKS__ == 0x3001
#     define BOOST_COMPILER_VERSION 8.1
#   elif __MWERKS__ == 0x3002
#     define BOOST_COMPILER_VERSION 8.2
#   elif __MWERKS__ == 0x3003
#     define BOOST_COMPILER_VERSION 8.3
#   elif __MWERKS__ == 0x3200
#     define BOOST_COMPILER_VERSION 9.0
#   elif __MWERKS__ == 0x3201
#     define BOOST_COMPILER_VERSION 9.1
#   elif __MWERKS__ == 0x3202
#     define BOOST_COMPILER_VERSION 9.2
#   elif __MWERKS__ == 0x3204
#     define BOOST_COMPILER_VERSION 9.3
#   elif __MWERKS__ == 0x3205
#     define BOOST_COMPILER_VERSION 9.4
#   elif __MWERKS__ == 0x3206
#     define BOOST_COMPILER_VERSION 9.5
#   elif __MWERKS__ == 0x3207
#     define BOOST_COMPILER_VERSION 9.6
#   else
#     define BOOST_COMPILER_VERSION __MWERKS__
#   endif
#else
#  define BOOST_COMPILER_VERSION __MWERKS__
#endif

//
// C++0x features
//
//   See boost\config\suffix.hpp for BOOST_NO_LONG_LONG
//
#if __MWERKS__ > 0x3206 && __option(rvalue_refs)
#  define BOOST_HAS_RVALUE_REFS
#else
#  define BOOST_NO_CXX11_RVALUE_REFERENCES
#endif
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
#define BOOST_NO_CXX11_EXTERN_TEMPLATE
#define BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#define BOOST_NO_CXX11_LAMBDAS
#define BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#define BOOST_NO_CXX11_NOEXCEPT
#define BOOST_NO_CXX11_NULLPTR
#define BOOST_NO_CXX11_RANGE_BASED_FOR
#define BOOST_NO_CXX11_RAW_LITERALS
#define BOOST_NO_CXX11_SCOPED_ENUMS
#define BOOST_NO_SFINAE_EXPR
#define BOOST_NO_CXX11_SFINAE_EXPR
#define BOOST_NO_CXX11_STATIC_ASSERT
#define BOOST_NO_CXX11_TEMPLATE_ALIASES
#define BOOST_NO_CXX11_UNICODE_LITERALS
#define BOOST_NO_CXX11_VARIADIC_TEMPLATES
#define BOOST_NO_CXX11_VARIADIC_MACROS
#define BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#define BOOST_NO_CXX11_USER_DEFINED_LITERALS
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

#define BOOST_COMPILER "Metrowerks CodeWarrior C++ version " BOOST_STRINGIZE(BOOST_COMPILER_VERSION)

//
// versions check:
// we don't support Metrowerks prior to version 5.3:
#if __MWERKS__ < 0x2301
#  error "Compiler not supported or configured - please reconfigure"
#endif
//
// last known and checked version:
#if (__MWERKS__ > 0x3205)
#  if defined(BOOST_ASSERT_CONFIG)
#     error "boost: Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif








/* metrowerks.hpp
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
*/