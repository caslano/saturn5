//  (C) Copyright John Maddock 2001 - 2003.
//  (C) Copyright David Abrahams 2002 - 2003.
//  (C) Copyright Aleksey Gurtovoy 2002.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  CodeGear C++ compiler setup:

#if !defined( BOOST_WITH_CODEGEAR_WARNINGS )
// these warnings occur frequently in optimized template code
# pragma warn -8004 // var assigned value, but never used
# pragma warn -8008 // condition always true/false
# pragma warn -8066 // dead code can never execute
# pragma warn -8104 // static members with ctors not threadsafe
# pragma warn -8105 // reference member in class without ctors
#endif
//
// versions check:
// last known and checked version is 0x621
#if (__CODEGEARC__ > 0x621)
#  if defined(BOOST_ASSERT_CONFIG)
#     error "boost: Unknown compiler version - please run the configure tests and report the results"
#  else
#     pragma message( "boost: Unknown compiler version - please run the configure tests and report the results")
#  endif
#endif

// CodeGear C++ Builder 2009
#if (__CODEGEARC__ <= 0x613)
#  define BOOST_NO_INTEGRAL_INT64_T
#  define BOOST_NO_DEPENDENT_NESTED_DERIVATIONS
#  define BOOST_NO_PRIVATE_IN_AGGREGATE
#  define BOOST_NO_USING_DECLARATION_OVERLOADS_FROM_TYPENAME_BASE
   // we shouldn't really need this - but too many things choke
   // without it, this needs more investigation:
#  define BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
#  define BOOST_SP_NO_SP_CONVERTIBLE
#endif

// CodeGear C++ Builder 2010
#if (__CODEGEARC__ <= 0x621)
#  define BOOST_NO_TYPENAME_WITH_CTOR    // Cannot use typename keyword when making temporaries of a dependant type
#  define BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#  define BOOST_NO_MEMBER_TEMPLATE_FRIENDS
#  define BOOST_NO_NESTED_FRIENDSHIP     // TC1 gives nested classes access rights as any other member
#  define BOOST_NO_USING_TEMPLATE
#  define BOOST_NO_TWO_PHASE_NAME_LOOKUP
// Temporary hack, until specific MPL preprocessed headers are generated
#  define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

// CodeGear has not yet completely implemented value-initialization, for
// example for array types, as I reported in 2010: Embarcadero Report 83751,
// "Value-initialization: arrays should have each element value-initialized",
// http://qc.embarcadero.com/wc/qcmain.aspx?d=83751
// Last checked version: Embarcadero C++ 6.21
// See also: http://www.boost.org/libs/utility/value_init.htm#compiler_issues
// (Niels Dekker, LKEB, April 2010)
#  define BOOST_NO_COMPLETE_VALUE_INITIALIZATION

#  if defined(NDEBUG) && defined(__cplusplus)
      // fix broken <cstring> so that Boost.test works:
#     include <cstring>
#     undef strcmp
#  endif
   // fix broken errno declaration:
#  include <errno.h>
#  ifndef errno
#     define errno errno
#  endif

#endif

// Reportedly, #pragma once is supported since C++ Builder 2010
#if (__CODEGEARC__ >= 0x620)
#  define BOOST_HAS_PRAGMA_ONCE
#endif

//
// C++0x macros:
//
#if (__CODEGEARC__ <= 0x620)
#define BOOST_NO_CXX11_STATIC_ASSERT
#else
#define BOOST_HAS_STATIC_ASSERT
#endif
#define BOOST_HAS_CHAR16_T
#define BOOST_HAS_CHAR32_T
#define BOOST_HAS_LONG_LONG
// #define BOOST_HAS_ALIGNOF
#define BOOST_HAS_DECLTYPE
#define BOOST_HAS_EXPLICIT_CONVERSION_OPS
// #define BOOST_HAS_RVALUE_REFS
#define BOOST_HAS_SCOPED_ENUM
// #define BOOST_HAS_STATIC_ASSERT
#define BOOST_HAS_STD_TYPE_TRAITS

#define BOOST_NO_CXX11_AUTO_DECLARATIONS
#define BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#define BOOST_NO_CXX11_CONSTEXPR
#define BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#define BOOST_NO_CXX11_DELETED_FUNCTIONS
#define BOOST_NO_CXX11_EXTERN_TEMPLATE
#define BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#define BOOST_NO_CXX11_LAMBDAS
#define BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#define BOOST_NO_CXX11_NOEXCEPT
#define BOOST_NO_CXX11_NULLPTR
#define BOOST_NO_CXX11_RANGE_BASED_FOR
#define BOOST_NO_CXX11_RAW_LITERALS
#define BOOST_NO_CXX11_RVALUE_REFERENCES
#define BOOST_NO_SFINAE_EXPR
#define BOOST_NO_CXX11_SFINAE_EXPR
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

//
// TR1 macros:
//
#define BOOST_HAS_TR1_HASH
#define BOOST_HAS_TR1_TYPE_TRAITS
#define BOOST_HAS_TR1_UNORDERED_MAP
#define BOOST_HAS_TR1_UNORDERED_SET

#define BOOST_HAS_MACRO_USE_FACET

#define BOOST_NO_CXX11_HDR_INITIALIZER_LIST

// On non-Win32 platforms let the platform config figure this out:
#ifdef _WIN32
#  define BOOST_HAS_STDINT_H
#endif

//
// __int64:
//
#if !defined(__STRICT_ANSI__)
#  define BOOST_HAS_MS_INT64
#endif
//
// check for exception handling support:
//
#if !defined(_CPPUNWIND) && !defined(BOOST_CPPUNWIND) && !defined(__EXCEPTIONS) && !defined(BOOST_NO_EXCEPTIONS)
#  define BOOST_NO_EXCEPTIONS
#endif
//
// all versions have a <dirent.h>:
//
#if !defined(__STRICT_ANSI__)
#  define BOOST_HAS_DIRENT_H
#endif
//
// all versions support __declspec:
//
#if defined(__STRICT_ANSI__)
// config/platform/win32.hpp will define BOOST_SYMBOL_EXPORT, etc., unless already defined
#  define BOOST_SYMBOL_EXPORT
#endif
//
// ABI fixing headers:
//
#ifndef BOOST_ABI_PREFIX
#  define BOOST_ABI_PREFIX "boost/config/abi/borland_prefix.hpp"
#endif
#ifndef BOOST_ABI_SUFFIX
#  define BOOST_ABI_SUFFIX "boost/config/abi/borland_suffix.hpp"
#endif
//
// Disable Win32 support in ANSI mode:
//
#  pragma defineonoption BOOST_DISABLE_WIN32 -A
//
// MSVC compatibility mode does some nasty things:
// TODO: look up if this doesn't apply to the whole 12xx range
//
#if defined(_MSC_VER) && (_MSC_VER <= 1200)
#  define BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
#  define BOOST_NO_VOID_RETURNS
#endif

#define BOOST_COMPILER "CodeGear C++ version " BOOST_STRINGIZE(__CODEGEARC__)


/* codegear.hpp
iyArQwcypu+icVsNwflF5MVFGsSaj7WGPmApPxdRmCZeUmq6VMTax6WFekhljqSea7uxn4m+wZLxPvYi5WYic/wsdLNYEOumgfg3Wfxe6LquVUaiP3gZ70Sf/SZvc7e03Di0bTG4fBmw3z7Py566sdTwKBN0J0kJYXofYukFIoqCMpTaKRpNnLh/r2+BLHuLPy19uwhE0zF/JUr8EfN6DNPcTsLSEWSWoCTqd3f/ZuhckGVJHshMG9M3873RyW9xOS/MbdkCoTCmW+absAeYXCg83wvtLIhF89QKxxz0kcXkUxHHblyAl/vhU7MBn3eLRt4dzy+j0I8En05pwRb6h2VytnAKqadJ6hpyuje00D8slXuw6ydxUoaWQENJ7dcT31E30kksKw9yzxHGVEAJYv4uDZQrShx4+934rOpy6Tb5OZNLRJYmVl5Enhj62Tbe32TyvsjDIvBSxxJNn3PDZ+Tub/M8Z77rxkFCZXEAoPo3xeQcEVlJHIeJKwY+/3wsC6lcKcrYtWRJbcFnhsZbeiytWAR57gWJG4th00mVWRx/mLwnQieI89gNRcNRhi4njj8gS/2hek7iZZg0apukPhX97lGZB0eu5Th+WAg85FMCQo+ln6b8I1ka5bZt58DHwc3CNyYo90F+KsuReJZQxpO8ri9TbiGCIHVczw4Fs7Tsi2Der7C8Sw32osKtJEhXIfVzlfJzkfmp61lSgq7+ldBT0Sf2d1gZ/MyKHb9KZEOe7hg+sSk3F26Ul27m+0IeLkwfPbwsX1KXvz2Qz032UZlSOEEeB0VeiDk5nh2u7W2xLOij/TvGWOynWQFjY9+6Bd7TX5Nprq2e5umVPD3bsUs7yjwBu7FKqCvPrzFB9B/6HWP+FgeBC89kSy689A5bl/Id9DNtaY8nlW1jeaM78H18GY0jE3bqx6njhAK+8ofn5Kv1MHvtSx3Gt6p5fssyLLxEMiq3CPKakvn2uq/t2KkcKGhiVS9siOojLjMMhoP9/SKZtqoz8go1+sFm8Tgidj03zUNHyC3XDdmiq2s9aKeFjXl8U/Qo+jU26jq0/NIOfSkqN4GXZB7ks3CnZbWZejrxXd4XisR146ys5UhnQP+zhkzouGUckbRIl0D/s1QmF7kbR7aTi6pIs1JCfhT1M/goU1KZVMhOGsW+F0iho4dxQDTa/SSVyUSRJbnjlUUlIz+/G2DFaa43Ot815kWZrAR4k75TOTtsHz0MrwwrLZ9d19XR03V/jsqXInJKmaRbio7MZlc1G0yNlNxpnI+xdD1RlE7uxYEjqpRWZldlokty/lc58lAq7uvxjsnmws8sN7LskMpKV3OdtfXZdfnrGekgA4wQVSz9s9sHgK3f7as7ezm90gfnnlMSK/cgRq/z4dr4qvw5Q+7z5fo6H9l7mPqGsRcQZ3mZX//VT7UVwPYCNtT9giov6t7WpS9Se7uFxepi1sEj8j3HmvPzYZzTNefqMM7Tas7ElzgHLm+B+RpNa98QDk1rZgiHplU2cg4foWktDuHQtM4O4UBad1B7whcrDqs7xKYuGdjpPnZAYucNOR3nvSBOJUfrCLEvc0zHeW/AvsIxGudljWFdEOyrHMM4AfuagT2N72l1B22Wca9peQxwYo9M95W3ImbYKtf94NwXeT8ICjfI0iC/0Y4ANtpgf9hf5PZtSa/2/33suOUk1TmXDPt7P6wsirQVHfcyCAfZf9bh7IxmXcXYavPzrZuOEsw4B79KMFjNs3OEMYKpc9+9+LZdjZHzW5TdsxVwuown750CpksA7/otdReZT6BtBIdMEexX2ykmRUm8ixMUW28vy+EOyor4DoljLWPCGPetdzIcIq/zxLHOWqc=
*/