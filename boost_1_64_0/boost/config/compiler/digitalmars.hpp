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
AAcbekbhL0NgzXe/mx+tmp27CPNf8360bVlYFx5t3pObcq7Gf+NwiwRib+3G2yzvl+aGveN8bZQzvAIi4+L+/T6Hxxv+s483hsXoq/jACN5eOCHn+EHG4TrUfreA8z91Et+Z+NzWSADL/RfGwWfoiO8cZji2C/rRPMJwaBN8s3mTY+1NdjurYBo/n2Q8MA9E7Po9DIMdPNbv3qMM6y/srLZpI+dRztle+AR2P9Yxv9fnQBHI289n+zjsB4jPsucwvLmjb4pC2/K5lIf9hulMHmO47x8Ced/xeH7/YwzY5zW8ZqBR3bj5whbjxn90ru+/DDijPqPuezn8Ti2MyRn6KwBrZmJ4ULnQxzOg2ycAGx37LC7fqzmHzw/kWwk8b96GGJs/cGW++aXaL+GKH0/21/XaXEb1tsyFFpjw3re8F7CtlcWzZ5w37noi5bgFfGlxCVGStj7S4Mu9EeypyQYjcmfbb9yXuJ1sWuZVpsWiC7i+sjZ0W+QeC6DnIlaeqk5zaXFceX6+v8G3+nUUA7+uZV0XVlf87k3sh2/ZAjj8mv/Ewho8ybjWvI5ecgvEnQF9A07Lr6woYhXFSfqM37NCLqKZ46dfNtHkurK2uN2rzyLPud/ghWqt6bNz1cUgDufzpPYpoClmyrPwO6TzPvhWzD5Yqvm0klBv99u8+80FyMaf62dIcKXe4Muj+Ea/wSGvd2Ga7w/MXHMODj5SfTmYARu5dry+zn1fCk+6fSbF3pbs5zzq+/3NeLYxhnN1GDfXpTao7Q3afj64B3dpFYKLLAOfnZscHs93PORMTnIO+pknZdwZxwHtAWWCxCj3KHDvrGto9/xF/g4h00a54SJqaRAkjwowRtcXPfucSKtcxqmoiwczROvBmttm3uB5KVXp0kZFk9dHtxa7vF6HcbpYXoEIjc2zVNsmr/6CM+UB0RHbPiYnRRzkaSbjtmK1J/7a/MOr2xNefqVOExtETd0aOZIf2vEwOS1slFgdJJFoFoC1MYvrATAa21rn99OTX+J2MJUKVZKpgMlCPPXadm7HLYF4bLAZJq9EUQW5TMqiNUhs8px23zK034e15TdhXncLzAONXlGLGMC/5fBjL0CcWsTgOHwavvWdPQwS4QtG/aVeo76oPrHmNuHgh8o99iL7iuuEo3vrzj5uyMC9C8GVK0iD4xzb//v+iX10tmvOQdcG/QWXoWN2e4upp5CLygDDxT1jXGg5t0l66xBNqnt7tPDKdj/z73HpTOy+rMX/iXjz8PlaF8v2i/y8LSmTrMqjZ/yuvJ3n4Rv9Gli71fsAlwN8h8nvx+rfQQcc0MzNr4K9QGRkCF+A4OLc/MXq0pwpwwmC5+MIzXflIfyuQLrD39bwN6gled/o5uqs0aH6Nn04bLs35ARvWrj1gI+c9f0dh3gzgqHY7dcPMA7OffQ7/Rhy2ERF1+6I4+RC5J88DLg3GZD5/srRDt/dJLUld5gQHz3rWmrkLv0Wx1k8kc/c22HLPR734y8E6230dz7Z9E27DnzrcxCv86xhDMtZr3PwfCHjOovrzRce4xgk0TQByr/weR2nLiGp+/UOA7GRutvnMxzqjrK3CdZENQFOZ//wAsTpWET5Wy8EfGRlgXXrv8jHIfuhSQyWYZQDD1IR/8yLR3F4fIrv2Os5Je7tqKECN3Mgnmes0jmujqwxpMxtzQ0VlXD7o9whqZlaG71HO5601fuBuy3ugzVrh38Z8HHlavDbgP/PubV5k7sfuXzeJJy5A8jx5188H7z/i+yNoLVxmJpcXJ52IWHeFzSnJ805yTuPO936AvBbeH7gYj/v7Hh37DHidd8jtrqPYWyP8wTDQCfIfnA/YMun1uZbnJw=
*/