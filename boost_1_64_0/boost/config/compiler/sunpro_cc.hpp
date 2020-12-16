//  (C) Copyright John Maddock 2001.
//  (C) Copyright Jens Maurer 2001 - 2003.
//  (C) Copyright Peter Dimov 2002.
//  (C) Copyright Aleksey Gurtovoy 2002 - 2003.
//  (C) Copyright David Abrahams 2002.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Sun C++ compiler setup:

#    if __SUNPRO_CC <= 0x500
#      define BOOST_NO_MEMBER_TEMPLATES
#      define BOOST_NO_FUNCTION_TEMPLATE_ORDERING
#    endif

#    if (__SUNPRO_CC <= 0x520)
       //
       // Sunpro 5.2 and earler:
       //
       // although sunpro 5.2 supports the syntax for
       // inline initialization it often gets the value
       // wrong, especially where the value is computed
       // from other constants (J Maddock 6th May 2001)
#      define BOOST_NO_INCLASS_MEMBER_INITIALIZATION

       // Although sunpro 5.2 supports the syntax for
       // partial specialization, it often seems to
       // bind to the wrong specialization.  Better
       // to disable it until suppport becomes more stable
       // (J Maddock 6th May 2001).
#      define BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#    endif

#    if (__SUNPRO_CC <= 0x530)
       // Requesting debug info (-g) with Boost.Python results
       // in an internal compiler error for "static const"
       // initialized in-class.
       //    >> Assertion:   (../links/dbg_cstabs.cc, line 611)
       //         while processing ../test.cpp at line 0.
       // (Jens Maurer according to Gottfried Ganssauge 04 Mar 2002)
#      define BOOST_NO_INCLASS_MEMBER_INITIALIZATION

       // SunPro 5.3 has better support for partial specialization,
       // but breaks when compiling std::less<shared_ptr<T> >
       // (Jens Maurer 4 Nov 2001).

       // std::less specialization fixed as reported by George
       // Heintzelman; partial specialization re-enabled
       // (Peter Dimov 17 Jan 2002)

//#      define BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

       // integral constant expressions with 64 bit numbers fail
#      define BOOST_NO_INTEGRAL_INT64_T
#    endif

#    if (__SUNPRO_CC < 0x570)
#      define BOOST_NO_TEMPLATE_TEMPLATES
       // see http://lists.boost.org/MailArchives/boost/msg47184.php
       // and http://lists.boost.org/MailArchives/boost/msg47220.php
#      define BOOST_NO_INCLASS_MEMBER_INITIALIZATION
#      define BOOST_NO_SFINAE
#      define BOOST_NO_ARRAY_TYPE_SPECIALIZATIONS
#    endif
#    if (__SUNPRO_CC <= 0x580)
#      define BOOST_NO_IS_ABSTRACT
#    endif

#    if (__SUNPRO_CC <= 0x5100)
       // Sun 5.10 may not correctly value-initialize objects of
       // some user defined types, as was reported in April 2010
       // (CR 6947016), and confirmed by Steve Clamage.
       // (Niels Dekker, LKEB, May 2010).
#      define BOOST_NO_COMPLETE_VALUE_INITIALIZATION
#    endif

//
// Dynamic shared object (DSO) and dynamic-link library (DLL) support
//
#if __SUNPRO_CC > 0x500
#  define BOOST_SYMBOL_EXPORT __global
#  define BOOST_SYMBOL_IMPORT __global
#  define BOOST_SYMBOL_VISIBLE __global
#endif

#if (__SUNPRO_CC < 0x5130)
// C++03 features in 12.4:
#define BOOST_NO_TWO_PHASE_NAME_LOOKUP
#define BOOST_NO_SFINAE_EXPR
#define BOOST_NO_ADL_BARRIER
#define BOOST_NO_CXX11_VARIADIC_MACROS
#endif

#if (__SUNPRO_CC < 0x5130) || (__cplusplus < 201100)
// C++11 only featuires in 12.4:
#define BOOST_NO_CXX11_AUTO_DECLARATIONS
#define BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#define BOOST_NO_CXX11_CHAR16_T
#define BOOST_NO_CXX11_CHAR32_T
#define BOOST_NO_CXX11_CONSTEXPR
#define BOOST_NO_CXX11_DECLTYPE
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
#define BOOST_NO_CXX11_STATIC_ASSERT
#define BOOST_NO_CXX11_TEMPLATE_ALIASES
#define BOOST_NO_CXX11_UNICODE_LITERALS
#define BOOST_NO_CXX11_ALIGNAS
#define BOOST_NO_CXX11_TRAILING_RESULT_TYPES
#define BOOST_NO_CXX11_INLINE_NAMESPACES
#define BOOST_NO_CXX11_FINAL
#define BOOST_NO_CXX11_UNRESTRICTED_UNION
#endif

#if (__SUNPRO_CC < 0x5140) || (__cplusplus < 201103)
#define BOOST_NO_CXX11_VARIADIC_TEMPLATES
#define BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#define BOOST_NO_CXX11_FIXED_LENGTH_VARIADIC_TEMPLATE_EXPANSION_PACKS
#define BOOST_NO_CXX11_DECLTYPE_N3276
#define BOOST_NO_CXX11_USER_DEFINED_LITERALS
#define BOOST_NO_CXX11_REF_QUALIFIERS
#define BOOST_NO_CXX11_THREAD_LOCAL
#endif

#define BOOST_NO_COMPLETE_VALUE_INITIALIZATION
//
// C++0x features
//
#  define BOOST_HAS_LONG_LONG

#define BOOST_NO_CXX11_SFINAE_EXPR

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
#if !defined(__cpp_decltype_auto) || (__cpp_decltype_auto < 201304) || (__cplusplus < 201402L)
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

// Turn on threading support for Solaris 12.
// Ticket #11972
#if (__SUNPRO_CC >= 0x5140) && defined(__SunOS_5_12) && !defined(BOOST_HAS_THREADS)
# define BOOST_HAS_THREADS
#endif

//
// Version
//

#define BOOST_COMPILER "Sun compiler version " BOOST_STRINGIZE(__SUNPRO_CC)

//
// versions check:
// we don't support sunpro prior to version 4:
#if __SUNPRO_CC < 0x400
#error "Compiler not supported or configured - please reconfigure"
#endif
//
// last known and checked version:
#if (__SUNPRO_CC > 0x5150)
#  if defined(BOOST_ASSERT_CONFIG)
#     error "Boost.Config is older than your compiler - please check for an updated Boost release."
#  endif
#endif

/* sunpro_cc.hpp
3uiQ6nlC5uuJOSIBp9ffF43V5oviwPZ6I+6Ba2NDxu4ysnMLfh2yLD0uRygWcsZ8zvrshFc8m0/WI3PGT/5+rShj0K04jBf0/ST9ODKN0ygEqv60MDydHJHwebCPfUkHzCftWOehdLecNstIWyundRhpPXLafCNtnZzWydJSCr9LjTSFX5eRpvBbZqQJfp2YtsJI6+VpizDt+ZhWBHds6AfS/qGdtTOVxjYq59ctAqP2Ux95ZBrHsA+LvNiNJJoT0yUa5KHSkJx1RpOU+5q6ttBlGqIw8RYJJw7qt7QZ+EhSKmAh96P4wysXAl6CyKnpshzrH/dyWuH91mA4Fh0Yipsv2cV3DPbE1+EnIB5nDR5jlXIKXJY1z2Ke/huWDu1H9nlW7IDIM+dVBpZLlfO4RJjH05/meeB4Mi9o2xktvOa9Z7SYHzdpn3qlSNeKIu0WlpYr58dKVL+fszS8MZfOYVmifodYegbirWWFAAYEdoRhu+W6E3aPjOGZgYS9XWCYjr6lEvZxgeH5x8g+llNgrxcYHG4XjXyEHWAY7vUSSG17hGGg1jn2rkdO5Pm+kZ7Nl9L0cYWMHmLYCB4BlwSfr7O0RDKZZm1NCz73sfQdg85BfBCyYryryjH9VQJLl0OJUpk9c6VpUYGfEHn9Ki543y9wNz+sh/etxNrhTCvq3ysMZYtHtoVC8aHAtkh/3OMccsIeKNDRvgvqKVJUK6vWI8rqYnUdSKNHu3cPrJN3mLr+WF1dd3q2O2NB0HbyG1zM+exGbSoyToP5SjGZ3qF5BM18RuNJF6upSHZjjMaNvXEQzloCidIY1EirCHyLhKfLCMfQg5fqscrEB9IgvlLabQQwkb5Pn0kDX2AbTCj9OP5MCNyj4LFifg8rg/L3yHhuANwz8uPy94+ZuHcCBcvYm7LKSThs5WIBmRRswe6QeGw0aTxpWB3k9zEmJYGPVOEoC60kvut2CeeDeELk3WVibnaYglmBt6jfchN3Jl9SyRSFDHfQmh397lEPhSJYNZH6aNngBXN2FIyUQbjGnCb9OltXv5hVwAbTNZzPQeIDn8SNJsAovmLOa4YfqQCJ+8gP7g6i98H4UJ0B+7KgvdWkhb4v0QZ5hSXa/USLn06iLRFxWtT5dqL1VIxH19WKWPXyJqJ34/gkys4Ima+wMZlz4VSJPC9k/mHGJ2zcFXLlJ3ZI81fLrHoy3zboHQCR4/fnfO5lfHgXibIrQ8Ecu7uEBtgOons3p8OvkIRSd2RyMOENlhmZtM/T0cLqjwVVVx/lIOg+yXxc4cbGOB6O4MNkeFOX8E6OZ0qJeGIPWIHcsWqx8EOU8HQOwRT5Lt/8ewMbTezBMXdE6Hz3W7ENCk8epAzqBb63F09ar2kXPX+rxvIHIdaec7szGGKHwYOD3h6NcL0W3ttDuN2Kw087NTN/ay28x6hfeTK5IF5XLohZ5YI82y/yb8E4S9u9kSH2hSRlAZ6AhwlXIIb1A1YFcWw75nNbUek8AP7cqNf8FvQdT7+qjcmzWIbd4USC0s++Wkq/6SbTZ/01ZnpZou+4VUoHetEXU+9g+jAw5I4HecwrfFqM8BMmPpQuwhEoP5MmfTrI8N0V8Nzjzx/gY/RZpEGZb3FUtYHSLW2gdLUNRK+2AelBXxwO0Bde/1DI63eGwM4B2T8AsncOwNrYOeTFuqCvzSOQlk1l9sTLxu/3w3lCPLbdt53jGJPavy3oEfS/RHqegfYy2J2CKnkRfouN8Jry8txi9L8is0Tiu0v8irrG/Si7cF69tR3auWwCb9CX9o3TPsIY8E7rcbpTw+WdzOdvzDD9F9/sVawM+Ar5ZAK2+PIjaeK9UeVNe2Ep4J0E3sk=
*/