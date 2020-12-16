//  (C) Copyright John Maddock 2001 - 2002.
//  (C) Copyright Aleksey Gurtovoy 2002.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  MPW C++ compilers setup:

#   if    defined(__SC__)
#     define BOOST_COMPILER "MPW SCpp version " BOOST_STRINGIZE(__SC__)
#   elif defined(__MRC__)
#     define BOOST_COMPILER "MPW MrCpp version " BOOST_STRINGIZE(__MRC__)
#   else
#     error "Using MPW compiler configuration by mistake.  Please update."
#   endif

//
// MPW 8.90:
//
#if (MPW_CPLUS <= 0x890) || !defined(BOOST_STRICT_CONFIG)
#  define BOOST_NO_CV_SPECIALIZATIONS
#  define BOOST_NO_DEPENDENT_NESTED_DERIVATIONS
#  define BOOST_NO_DEPENDENT_TYPES_IN_TEMPLATE_VALUE_PARAMETERS
#  define BOOST_NO_INCLASS_MEMBER_INITIALIZATION
#  define BOOST_NO_INTRINSIC_WCHAR_T
#  define BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#  define BOOST_NO_USING_TEMPLATE

#  define BOOST_NO_CWCHAR
#  define BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS

#  define BOOST_NO_STD_ALLOCATOR /* actually a bug with const reference overloading */

#endif

//
// C++0x features
//
//   See boost\config\suffix.hpp for BOOST_NO_LONG_LONG
//
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
#define BOOST_NO_CXX11_RVALUE_REFERENCES
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

//
// versions check:
// we don't support MPW prior to version 8.9:
#if MPW_CPLUS < 0x890
#  error "Compiler not supported or configured - please reconfigure"
#endif
//
// last known and checked version is 0x890:
#if (MPW_CPLUS > 0x890)
#  if defined(BOOST_ASSERT_CONFIG)
#     error "boost: Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif



/* mpw.hpp
hZ1Ery3zfZR/WrsM4lgGEP1t1A7xle2aAoY3+JFyK5EVsq64vH+U89Bp8mb/AOKuPKfAIhXXA1cOAobrgS6G7yH4faHvehe8z/XpufMDRwAbLjUWyX3E3LPw9/oShd2tPBcxKIPr8wliV80wWKxhXj9/IWDOtZhDXG4o850Xw++suijz1H2AQTV5+X74Svh9uCVxBbjqegbP6F/3asDomxS8yUHO1yiHv1vBddLOa0Y5u8T2M3kt4Hvbdj7JcG7bebadm97F949FrDVEZxcLzXUgD6C4D8+1mJwUWVomMsil8J+zDQVR7hEvvyQJU6WjopPjsQrbMfEolcuFDMLUZLkRnVbxc5ufsXyMkFlq0ipNxDhXSk4l2nObdnw/8S42vvM0KWNXu0ZR+R78Sa9OudVRkCRKeC7pain00w3Kz205IxnXzzipp7pGJmjPF45RGRkLVZmkCKEhxrmw4+uDKSpbuC6rXJ/pJkwhiK700ad3WzfB8lMiTRMTJ3GE+dX3yXBnzPO6zPNKpdEm17LJa+1qb9BUjZznrHIZU1YmyispSPTVEZlrvA0TW2aZjCpBo7K250atLj1MZWYyncU6lbYp2i62AZ4X3+DlkqEJlNShIB4BR8r1KJWpRBQrFRSZYI4C23KhzrK2ToUxGi5PirHxAV1rfLQ5Y8WzoAe8MelGcm5DI/zpfCi3jGtAKmdFkksTx2khcAdXR0rnOj/5bq7zaW5i1yq5YFtW1N9lvLfx5KokynQaJF1muyS3rowzVK4UbvBrU8kmVunaqU4DSb8lVKYQOsiyMgwtyhB9DzCWJyufdEoYFkUZhYK5tURJLF+fylXCGpU4TUyIGGoWjuXrLK9QaKmcmLZijMtIfx644clWWiUFzL9jXDS3shjTk8kqoaMqyJLKksKyFsUzdK9tZBjksVERkWOtivsSKmdF6routFEl+MsfL/Y5l4lVpEJpDZEBgzN+9nrsPfysXTvlKqPUFwJP3iP9fv97fHvJKKhkroT//Mi74xOeXGJ1WKgoJ3IP9bbXVj7pxfO8zORCUQRpGEW66YONxebgYxNO9/z+6zPZQISZqeIsKmnA43H9/rBX1tREJq7iUPhmRV783ptUrhKpLkKZx1Iwz/iezI+5TJaFqUqyNl4yl8F9MZU5nyW5tnnWaBf2Nhnft3geZRnZKIkSwVZ/3pi7zdogFnlWhUa6xqDHTTjn8TXFxAVuV1gvXbKkpLJ8CuN3UCeYfAD+LSsbZYXwjif99xQzTC52OibzNPfk6pMDsLviY/Yyk1VCKVmGpuT13dmaX/TGUp/JRcKGVRXLMBPjjkKHoij7iCcbFjYJClfecW5uG1mcm7zy5qGOkyDXXBYzxb55nMkZkQZu4Md5JfZwm+v75HmSylcuW5UbY5pwxfx728eYKSzPSkgZmTyyRtzR7QAv9wnB7fBlYIJAy5ilMUYe5x/hffNlYbLUaAxEzMu+huszweOM52mUVM36jM1Y9N5c8HvzvIqNSaxgVoXePHBNsHk8TF3dqtIKbqXp+ZgQfE0Xh1FQpaGgL+h9X3w3Bbtnl5nJK50I3OyNfAOF9w10PZdEkRaLmzAcyOjg4+Jxwedtk8Kby1iM8RqOa0K0i/D6Kimr3AQJCnt7JtHKPS28O744drnqFOX4Hk3gOUJA17m6SGNbBlktteYe07flmzvV6mLg9VVY6jK1INBMaaDLvK9mAh4HO9KmyvJSUC/UfkzxJPBjkQeRCQuxPLY6XTtcCXifRSooTVUlneAl1oAY/5rJaZEbVQSpCsWoawrsM9RF3iZxaWOTlUEt6ovh2j/ga39VmDgpE8G8bng+U39GZXKRh1WsjKxE9wLX08M=
*/