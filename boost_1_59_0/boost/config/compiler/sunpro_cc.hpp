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
#define BOOST_NO_CXX11_OVERRIDE
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