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
#define BOOST_NO_CXX11_CHAR16_T
#define BOOST_NO_CXX11_CHAR32_T
#define BOOST_NO_CXX11_CONSTEXPR
#define BOOST_NO_CXX11_DECLTYPE
#define BOOST_NO_CXX11_DECLTYPE_N3276
#define BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#define BOOST_NO_CXX11_DELETED_FUNCTIONS
#define BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#define BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
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

#ifdef c_plusplus
// EDG has "long long" in non-strict mode
// However, some libraries have insufficient "long long" support
// #define BOOST_HAS_LONG_LONG
#endif

/* common_edg.hpp
sT6/0X3z3IfoN+2UdDLRqfZub3VH+X1+LXS1ovRy6axXzjmWl1afehx2842xuY19FeRr7OIowzojzI+cxvqp0jFdjAM2OKb/rgoHNh/TL+zAcDamn9iJ4WxMd2+K4WxM/x6G45iu7h1iOBvTpyYxHMd0fCf8Q/zsMg1j33KzUgBdnsK1u/PrSx18fmwLzENUnWF/oBMVGCpwHsLbbKEDezmkPRagXmW4OXugewvntxAenT1Qn5SjwMH2Y2vXV45pDHJQ1+EVCDfbDvjjEC7Tqlqu5l/dpsKh5SAc/VercGg5Ev7EnSpcjVnoq12HdzYYf+qmKhxajoT/YpcKVy2H7/l/0LQ5C72gKHwB56anwWbvcH/KptpNj3GTE3W7dfq17ek2PU/aVE4sjz2jK0/Ijld7+b1763QJpyYcX/OluvSpI130nbQVuVA9kJ816S92TeOXjXkyXKuFrSCd158bc+Xe2siKlr1AMRI3rqP3wjoa2t1y3Ue1wGF6vQa/C8NAVm5grI/cQ+FlMy7VtDKkQd7JZh5cUWD2xZ+jbeVkwkvh0bfi+g/51Mdhr+pX4oO0Xy1Aa/fvBSn/NJAb79ixlm9lUfq4/h7BFjmHOfa4Y/KkA8xh+9xxGSbj7sfQAsXpc2ERAIWRPaPVU/HulNy0pDH0ud+5wwjWAN2r/Tk8LAeIit3o4mjf/aItnMe7OLmjPAo81cf73Ppsakxj3aoUFUh95o8Djn0d0/5CFd5Pd3bhKRvg4mz+TGWbu7bRq+dXb9+OPH1FEzExgZgeMhCbuRlietjAtG96c8Sq3eeV3kZrTW4eL0L3J3n/bc2DkmPcn57EcD2UIDZ+S8T0cILp7r41xbptVmQSh3sb5OFHY6/GbgfYabq3DD2/fkP6A+y8P4hdOwj8UKgB6bDsRfIqGNoEbdF9+iLt04sbvYW1p69CFaNvg6/r/uYUee45x6FGCN4x8X6tC90PJ1g/hOeRs9wLnOu/16364bTu1+9n9oF55hVBkQk58rbXz1TPLLu5KuQyvofJZGwwRLS9UiyudXursytERMrsHdl+iy/eAaSgTKX1qGOetF+Xv4bFsePQVhK/hHhaFMmjy5aTRl5+HMeKcx+gY4Wq+Y46F73jCK2tqp//gPTnKPcLiJ3uJ84N1i/ib9hi4txXw55RhUO4ygu7R4g45rRex44Bhn0Y93tGxiEc2JWPrblZvVlA9PVPhLO81m2rzQyM+9NbEWfztUM7MJzN12Z2Yjibl+2/CYazeVnvphjO5mV7bobh3R7urao54S0QwzkbzuFp/5rxkiKKnMwRdgSe1maXcM2j9b4EPl1DR0UQpNf9LKdWe1wnX3k/1SkJd/i8bhbasKpKGNqqMsu/queE8Fxsc4vJ65ezdXpDbunJlVubvPEzyrgwbPFY6b1o4KKOwdcNagTaSMW1FXGIoZ5DbmPhU/TbM7MdMWwLPA+a4JgUxLTKHRqraqne24Xwhrnn8Z0QLplVOcme6aQOX2hLobVnqDLhnPIWGuf7Are+lQ6H6U9fCPc0b60xvm7ffxsM5/tCt2XhUEzE0t0aw/pB7Oe359gUSau8o8LMPYI9OpzvETxxrw7vJ4Nv9NMxtRCpFRRB6sf4vZmdn2931OdGf2tC8q2pBoU+GfvM2feb34rCs+IgudFOo8fwLeYYfsx71GPIGL6FjuGAeY+qZB9xRz2+HyucpAVDckvN73CMn2T9sV/ajpqf/VSN8ZbjeOVx8i4P6ABBlOog/qEtHDdtVKZGFQ6ASpPZxYxpXOeInGEAVus/eWsIwmfnO73mcfoq4nycfsMODIdSkDUYhrNxOrwJhrNx+vxNMZzpfnkzDB8Yp993C8Q=
*/