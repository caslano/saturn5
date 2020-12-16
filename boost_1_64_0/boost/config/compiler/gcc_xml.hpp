//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  GCC-XML C++ compiler setup:

#  if !defined(__GCCXML_GNUC__) || ((__GCCXML_GNUC__ <= 3) && (__GCCXML_GNUC_MINOR__ <= 3))
#     define BOOST_NO_IS_ABSTRACT
#  endif

//
// Threading support: Turn this on unconditionally here (except for
// those platforms where we can know for sure). It will get turned off again
// later if no threading API is detected.
//
#if !defined(__MINGW32__) && !defined(_MSC_VER) && !defined(linux) && !defined(__linux) && !defined(__linux__)
# define BOOST_HAS_THREADS
#endif

//
// gcc has "long long"
//
#define BOOST_HAS_LONG_LONG

// C++0x features:
//
#  define BOOST_NO_CXX11_CONSTEXPR
#  define BOOST_NO_CXX11_NULLPTR
#  define BOOST_NO_CXX11_TEMPLATE_ALIASES
#  define BOOST_NO_CXX11_DECLTYPE
#  define BOOST_NO_CXX11_DECLTYPE_N3276
#  define BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#  define BOOST_NO_CXX11_RVALUE_REFERENCES
#  define BOOST_NO_CXX11_STATIC_ASSERT
#  define BOOST_NO_CXX11_VARIADIC_TEMPLATES
#  define BOOST_NO_CXX11_VARIADIC_MACROS
#  define BOOST_NO_CXX11_AUTO_DECLARATIONS
#  define BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#  define BOOST_NO_CXX11_CHAR16_T
#  define BOOST_NO_CXX11_CHAR32_T
#  define BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#  define BOOST_NO_CXX11_DELETED_FUNCTIONS
#  define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#  define BOOST_NO_CXX11_SCOPED_ENUMS
#  define BOOST_NO_SFINAE_EXPR
#  define BOOST_NO_CXX11_SFINAE_EXPR
#  define BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#  define BOOST_NO_CXX11_LAMBDAS
#  define BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#  define BOOST_NO_CXX11_RANGE_BASED_FOR
#  define BOOST_NO_CXX11_RAW_LITERALS
#  define BOOST_NO_CXX11_UNICODE_LITERALS
#  define BOOST_NO_CXX11_NOEXCEPT
#  define BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#  define BOOST_NO_CXX11_USER_DEFINED_LITERALS
#  define BOOST_NO_CXX11_ALIGNAS
#  define BOOST_NO_CXX11_TRAILING_RESULT_TYPES
#  define BOOST_NO_CXX11_INLINE_NAMESPACES
#  define BOOST_NO_CXX11_REF_QUALIFIERS
#  define BOOST_NO_CXX11_FINAL
#  define BOOST_NO_CXX11_THREAD_LOCAL
#  define BOOST_NO_CXX11_UNRESTRICTED_UNION

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

#define BOOST_COMPILER "GCC-XML C++ version " __GCCXML__



/* gcc_xml.hpp
SoW5fsbms7hfRN924BeA1x2xuQOAsbojlhxCDOuHNpqHKcbtnA9OIkbrjrKTRxHHuqOdxb2IjdUN3LNwHqQDPY5nGU88G3FfJzCvXz0HOWP1C/2bfIKdmanEKJuYUtR7QFlYZwllytjzG0VlzpdJFCmbZUMRNNmi52CU77o8LSs4OxsKVDIN1dzIm/XrVGYmMlpZbdKhSFA+2PJFm8cjlF+JMo1UVMThUGA2fO+lsFSh5yvuJq97qbNKBWGTiXX1ngtk3gihXSqvSxSUkTZhKLSZtXnw4Fx4GevS+Y36hOfTSCZKqgCELobK2RY8SFt5Yh/6SqBypUiKwBZFHDV9U1V5GJS+v5qneDtIo3MZB3YoM8eEUGbiGpNJs6BMCmuGMhGTQb8Kx67x+9gklEGYx0HTqWounJsf1mq+1GGEcfDaNpli8kqoysaFzjXvMOzqTl+pXCkyp69OmUwrNocSxP/aZS8vG8owK1U1WlaeV9/Ly8RhEmeNTjntCOPwop/X9WteX+exMUHa1Ct0i7DwYjAXav8u/oYnl6dJrE2WNJ1tsIS+7z5fLrRaBZUayl2ai2a43DtbnWRykXDDqygzFXjKT4VxrD1JZa1w5Yxsjjp29uS4tpz4JJPJZFRGMpdNWwbTRAbLePyTnu84p/15XDRtGYela8ocBfl8MEVlS1EZcK8TFm2zKIj50wihXxTB8otEYdOoMoli+ZkPhLoTFq3sFa+sSVGoUsZNWd9nZg1tTe5j5JqXry60jmSZNoUtjXOeP8trKt7QrBfvH4DsyKBpV424rrxGeXOUQmwq3brx3TWnwWlMdMSIMjYLQ3JfMIYDyXScL4/jNItAPKsnnMKSrOga9sAYDt5dQGVGcX+tud5ycDbldb6NOBm4Xp2vHRrH4XV+aiyHx5L50GHkRLQwGIcEcV8Rue1r/8iePEgOeX/bmwcFQ96HJn0e6w+s49MjPOwTTGvnnvEc/07pL8iDmWF8/3/mKOf4/f8Pho/v/yvPAg6dzblt9dMjOORA9OdeH4ccyJuGGsdl0cjZwuqzOU79Ej/BMUgY0xXPAYysnkCS9O1PCe5/iGl/nHmux+NNjW15azwPkkJOcsznYJNjfj9Djv+B4Tp8+Xl78bgO/25PHrfX1s8f5fn69OcxHKpPcy8YxX29fQw5/lxM9pcvHOEw/IcUnxudh0+8CHH80vp1+dkYDq3L1IspPn5sfItwyHyE+LGXdPiDNhzR7e9wnOnBvccRYx83Xw9+uCeP68H9L92Lx8fjjZaHKwA+3qde5uN8vH9nFOfvAl5O8Ghm7DfyO5wz9ht5332cg1UhdX4YOXxx4c/Lr3vFOB6fl2/uwfH1+9grgcc3LX79HuWcsfU78apxHP49/ErDwV2VF5vtxAkf52dgX/Nxb43xL8DrcyCoN1mLUM6rOaewDYVyXkM49PsOfdVyXks5/ve24028fhxvNM+Db2A8/L7R+h98I+Hg94nEwr+f4fCN6epEMT6fI2fizchhcyJAWJ+3jOe0pcX6vBV5/tyJ9Zl8G3LI3EjSeDvibF6jc9LBd7QcnJe6sk5RzJ9HSLueRB6ZB8i7r1OI8/FL2+U0cviY8/v5TMvzxgrt5+mWQ3SdpDFxFnA4r9xbz3+NnL31/MY55Oyp58szlLO3np85z3h76/k7kbennt9Czng9v/EuinM9v/IAYnvq+dS7kbOnnv+LcfbW81+/B3l76vm3LnCOr+fLAvE99XwqoByu508zbG89f1xynq/njyjE99TzD2nK2VvP3xq2vL31/GnkcD0v23OQPj9XzmyuVK6fsZeq9mC5ftPZ2sDMwnMbsq6C+wNE8IkM1jff1+H4PKbfb0M=
*/