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
Wr+dAz60zveLqbGqUu2edQprhH5F171YH0keZTZCCXRHuL5LtrxT1+qfrpEtK1kPX1/ntvdVmplQxsldzp0BxqFjdUqLNNMyTJsS8n5ap741p4fzEBqWE7tkxHZXGhCuKojsGcCZ7QlsY5Db2VHsH8cFu/uFwRLhXT8whgdfvobX7vePrTO9yFXhdL4QfafUzrycvwu6j3LPpEWRRjrKay6OS/Rr4vVzrk0kZR4Lm6nZGTgZeN88vJOExwuN8AGwHYL93MTHQHYMcX5h91rjO+/bbm6d2pOHT1o7G9d9cL3BufRlBe7x9+RxW4YT+/fgwW6B9O0jhAcNBd72Ts4v7Lht9eIn50ujyVrvhQc9LtivM3udMXid1qCzPzrscQaOQ89mJwGHT9aYshPe0/cAD5Z943nob/Uo8CCnoXNNPP/6KLPdNKksIhVkYsn5VbPewwiMeUllzpdZlURREoraEccs+r/pbD2vU75MhUrKRBahgZcXMMW6mF0L4OzLy+8/bX43WX46gpiegRWuLrmbnndWm/w22zr9mNep1IEJY2vErLr4oJ0bPhlrXlY0PmagIWBvxxjNG/LGRn5+BG/3Ng+WrT8kmq8qRaVTlQZ34Wpm8yTGufjlcVekNUiP5+m/0/8z9GWtR9Pz/cXeqeHKvU6yO6s71HEeOtWg4Ehu7aGrvc0urV/dAzyen79/+9DREQ6z67g1irNziAee5XCnh0uD6aYgUOJunru1Sue5LLRRZnUJfY2OpFAPb1NuLhIpoyLJStE4hnMaxflPrfJYrVKpDJ5jy/BUXVL/XH5ijfJtlqZ5mmooyzrVO/RHfe8aO8eXUWyDOBD97RUv9jnlFULbIk2yOHEFyXTEi9LFUFnj+440MUEmy7v9duI7ov5VSA+r3ulVM2ffbnAoEWNAGsRHxEmShm/D88g+hlP7NEicYsw+bRWwNm9MmeTr457tRv+Aj3PbkCcA52OGyZ84NIrPrz2E+NfuofjHlldqBvHRfS/gMHdj/Tr7rGe3GCkfabNHnwM4zOejsv3nIsZk8d7lKr13UVmeRqWVoN/jdWrmKl+PlXGodHDXbglQpx5ZgfTa7Mb7q5hC3PdXwTDud4Jhvm8YwLCvmjODxo/UgRFsauhppZP/12HgQH+06ZN3aEcAg/ZGDP3J9Vf4+4U4rmSa52HnnEWFF+e8lyOw3mjWTjd7ID+eDMunmtu++bsDt2llXMfc69rqHXtw2wGK9nF34q51ab51/94834fiTeDW7TmeT7mPHgAutO94LvMLfxC4mwOo7tJiN+c+0KO+1cNEJSYoIrE18N7PCso7m+dJmgcKvhS4KO76NqFcacD3YlRlad71bVjWH7hQ105EGvn/YOw4Kg9P1HJbWZULt0l4CPb2JMt5fH9EZSoBcfTLMu+yJBnNo7/THNYkexRq2DFhy30suxMXFKPj3oR0eR9yPkl3ogAu9uFYLvpq4OXFUuIZ/Cjeqqxu07g1WrY6lxafwvIwHMfdrSU2lnhZm4H39mbcTSzfiYvTG/pV6jM+Z4HfghXH2SO1+j52FXAqTcYKxCR7+x37D7jN+787ctfYnnZu/5243ObxccYlOdNz3gM+h9sv/47hmAuWRxwE/I66h2klh5DL+7rFDzscdOEZpHXfEeSytPC+YMmL2yLjKMiDu15/0XOIt9X5DQ+/3NEX5nXFy8sUudI6/7/vkCCvtw7zGs5AkBk5W/jbIp1DU2sTmeZauJzOjqwZ7mdlK0SYl7HOi/L/LdvPajPPBbTL9O22bh8EfO3UAsdx/v/Vg7TsNk+1jUwlpqa8OHRPLfK4BGmS5q4P77bYE/TM7c1Ybm7PiOvI/cghdwnUbzE=
*/