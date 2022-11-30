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