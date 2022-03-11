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
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
*/