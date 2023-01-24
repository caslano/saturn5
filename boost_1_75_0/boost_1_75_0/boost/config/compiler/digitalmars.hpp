//  Copyright (C) Christof Meerwald 2003
//  Copyright (C) Dan Watkins 2003
//
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  Digital Mars C++ compiler setup:
#define BOOST_COMPILER __DMC_VERSION_STRING__

#define BOOST_HAS_LONG_LONG
#define BOOST_HAS_PRAGMA_ONCE

#if !defined(BOOST_STRICT_CONFIG)
#define BOOST_NO_MEMBER_TEMPLATE_FRIENDS
#define BOOST_NO_OPERATORS_IN_NAMESPACE
#define BOOST_NO_UNREACHABLE_RETURN_DETECTION
#define BOOST_NO_SFINAE
#define BOOST_NO_USING_TEMPLATE
#define BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#endif

//
// has macros:
#define BOOST_HAS_DIRENT_H
#define BOOST_HAS_STDINT_H
#define BOOST_HAS_WINTHREADS

#if (__DMC__ >= 0x847)
#define BOOST_HAS_EXPM1
#define BOOST_HAS_LOG1P
#endif

//
// Is this really the best way to detect whether the std lib is in namespace std?
//
#ifdef __cplusplus
#include <cstddef>
#endif
#if !defined(__STL_IMPORT_VENDOR_CSTD) && !defined(_STLP_IMPORT_VENDOR_CSTD)
#  define BOOST_NO_STDC_NAMESPACE
#endif


// check for exception handling support:
#if !defined(_CPPUNWIND) && !defined(BOOST_NO_EXCEPTIONS)
#  define BOOST_NO_EXCEPTIONS
#endif

//
// C++0x features
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

#if (__DMC__ <= 0x840)
#error "Compiler not supported or configured - please reconfigure"
#endif
//
// last known and checked version is ...:
#if (__DMC__ > 0x848)
#  if defined(BOOST_ASSERT_CONFIG)
#     error "boost: Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif

/* digitalmars.hpp
4sewCFi8+Nxs5Oq8EbkaY8gVzUcuWxQtOMv9H8Fr/0JkDPWQ6YU0cmaaDdekyaAmSXmBVZmqqMh+wRz3Hlws1kg1clgqECfhgzahupTVPNQfzEbOxj9HzmgMOaFuFmGN6//N9U9B+jX9Hkl+f1oli+e49/JK8tOV1KYr+bLYJrHXeCywmyFzO6Rvvcboxr+282+04W5CON75WmaPWP0TIFBE7TQW2sXPhBjqxVVpvc0sYzP2mnn9Q+HIa3z9v2Ydmw/FqzAfnC9r9/lUuy9Z2322zNTuPwIj+jqHsfR1CwxlOoxZ5Aidr5vkCANQ+I/XmRxh+HUqR3j49TRGWGqRI3xCZBT3MjnC4jm0fdNt4Sdf57acr0Hmi9eJnRDV7xZkbLfGU7p6Sgw5h3GLoIsH5OWST8wVdFQpazggU7/xHVa/8aGf83P2N0Am8fOUfTq3fHSM4yKYQA1CLg1kTr3bp2y0dTT/VMZerfPnPNbFfZAZ/nkqRl4qVBS1BNGTuFSoFackoQTHUJ6oYY9giDP7fDv6c5Pd/ItQ0FbBy1MSLkEJgVr3C9z+1QPrVL/c/vUNbn86DzJ/+0bK5tt8MNTsy7+dhWo2hUAbP8JlyFw6nbEYKu9C1TgmJIFm6VcewXJYjWu56qCSBwuuj95wFOhVziaXofsdhtxB/4CdlVKOlUoZMhjVqBpKgdNB4jvQmJkGWhS9Gi2yedIxM5+D
*/