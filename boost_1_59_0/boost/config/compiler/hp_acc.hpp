//  (C) Copyright John Maddock 2001 - 2003.
//  (C) Copyright Jens Maurer 2001 - 2003.
//  (C) Copyright Aleksey Gurtovoy 2002.
//  (C) Copyright David Abrahams 2002 - 2003.
//  (C) Copyright Toon Knapen 2003.
//  (C) Copyright Boris Gubenko 2006 - 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  HP aCC C++ compiler setup:

#if defined(__EDG__)
#include <boost/config/compiler/common_edg.hpp>
#endif

#if (__HP_aCC <= 33100)
#    define BOOST_NO_INTEGRAL_INT64_T
#    define BOOST_NO_OPERATORS_IN_NAMESPACE
#  if !defined(_NAMESPACE_STD)
#     define BOOST_NO_STD_LOCALE
#     define BOOST_NO_STRINGSTREAM
#  endif
#endif

#if (__HP_aCC <= 33300)
// member templates are sufficiently broken that we disable them for now
#    define BOOST_NO_MEMBER_TEMPLATES
#    define BOOST_NO_DEPENDENT_NESTED_DERIVATIONS
#    define BOOST_NO_USING_DECLARATION_OVERLOADS_FROM_TYPENAME_BASE
#endif

#if (__HP_aCC <= 38000)
#  define BOOST_NO_TWO_PHASE_NAME_LOOKUP
#endif

#if (__HP_aCC > 50000) && (__HP_aCC < 60000)
#    define BOOST_NO_UNREACHABLE_RETURN_DETECTION
#    define BOOST_NO_TEMPLATE_TEMPLATES
#    define BOOST_NO_SWPRINTF
#    define BOOST_NO_DEPENDENT_TYPES_IN_TEMPLATE_VALUE_PARAMETERS
#    define BOOST_NO_IS_ABSTRACT
#    define BOOST_NO_MEMBER_TEMPLATE_FRIENDS
#endif

// optional features rather than defects:
#if (__HP_aCC >= 33900)
#    define BOOST_HAS_LONG_LONG
#    define BOOST_HAS_PARTIAL_STD_ALLOCATOR
#endif

#if (__HP_aCC >= 50000 ) && (__HP_aCC <= 53800 ) || (__HP_aCC < 31300 )
#    define BOOST_NO_MEMBER_TEMPLATE_KEYWORD
#endif

// This macro should not be defined when compiling in strict ansi
// mode, but, currently, we don't have the ability to determine
// what standard mode we are compiling with. Some future version
// of aCC6 compiler will provide predefined macros reflecting the
// compilation options, including the standard mode.
#if (__HP_aCC >= 60000) || ((__HP_aCC > 38000) && defined(__hpxstd98))
#    define BOOST_NO_TWO_PHASE_NAME_LOOKUP
#endif

#define BOOST_COMPILER "HP aCC version " BOOST_STRINGIZE(__HP_aCC)

//
// versions check:
// we don't support HP aCC prior to version 33000:
#if __HP_aCC < 33000
#  error "Compiler not supported or configured - please reconfigure"
#endif

//
// Extended checks for supporting aCC on PA-RISC
#if __HP_aCC > 30000 && __HP_aCC < 50000
#  if __HP_aCC < 38000
      // versions prior to version A.03.80 not supported
#     error "Compiler version not supported - version A.03.80 or higher is required"
#  elif !defined(__hpxstd98)
      // must compile using the option +hpxstd98 with version A.03.80 and above
#     error "Compiler option '+hpxstd98' is required for proper support"
#  endif //PA-RISC
#endif

//
// C++0x features
//
//   See boost\config\suffix.hpp for BOOST_NO_LONG_LONG
//
#if !defined(__EDG__)

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
#define BOOST_NO_CXX11_USER_DEFINED_LITERALS
#define BOOST_NO_CXX11_ALIGNAS
#define BOOST_NO_CXX11_TRAILING_RESULT_TYPES
#define BOOST_NO_CXX11_INLINE_NAMESPACES
#define BOOST_NO_CXX11_REF_QUALIFIERS
#define BOOST_NO_CXX11_THREAD_LOCAL
#define BOOST_NO_CXX11_UNRESTRICTED_UNION

/*
  See https://forums13.itrc.hp.com/service/forums/questionanswer.do?threadId=1443331 and
      https://forums13.itrc.hp.com/service/forums/questionanswer.do?threadId=1443436
*/

#if (__HP_aCC < 62500) || !defined(HP_CXX0x_SOURCE)
  #define BOOST_NO_CXX11_VARIADIC_MACROS
#endif

#endif

//
// last known and checked version for HP-UX/ia64 is 61300
// last known and checked version for PA-RISC is 38000
#if ((__HP_aCC > 61300) || ((__HP_aCC > 38000) && defined(__hpxstd98)))
#  if defined(BOOST_ASSERT_CONFIG)
#     error "boost: Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif

/* hp_acc.hpp
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
*/