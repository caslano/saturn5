//  (C) Copyright John Maddock 2001 - 2003.
//  (C) Copyright Jens Maurer 2001.
//  (C) Copyright Peter Dimov 2001.
//  (C) Copyright David Abrahams 2002.
//  (C) Copyright Guillaume Melquiond 2003.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Dinkumware standard library config:

#if !defined(_YVALS) && !defined(_CPPLIB_VER)
#include <boost/config/no_tr1/utility.hpp>
#if !defined(_YVALS) && !defined(_CPPLIB_VER)
#error This is not the Dinkumware lib!
#endif
#endif


#if defined(_CPPLIB_VER) && (_CPPLIB_VER >= 306)
   // full dinkumware 3.06 and above
   // fully conforming provided the compiler supports it:
#  if !(defined(_GLOBAL_USING) && (_GLOBAL_USING+0 > 0)) && !defined(__BORLANDC__) && !defined(_STD) && !(defined(__ICC) && (__ICC >= 700))   // can be defined in yvals.h
#     define BOOST_NO_STDC_NAMESPACE
#  endif
#  if !(defined(_HAS_MEMBER_TEMPLATES_REBIND) && (_HAS_MEMBER_TEMPLATES_REBIND+0 > 0)) && !(defined(_MSC_VER) && (_MSC_VER > 1300)) && defined(BOOST_MSVC)
#     define BOOST_NO_STD_ALLOCATOR
#  endif
#  define BOOST_HAS_PARTIAL_STD_ALLOCATOR
#  if defined(BOOST_MSVC) && (BOOST_MSVC < 1300)
      // if this lib version is set up for vc6 then there is no std::use_facet:
#     define BOOST_NO_STD_USE_FACET
#     define BOOST_HAS_TWO_ARG_USE_FACET
      // C lib functions aren't in namespace std either:
#     define BOOST_NO_STDC_NAMESPACE
      // and nor is <exception>
#     define BOOST_NO_EXCEPTION_STD_NAMESPACE
#  endif
// There's no numeric_limits<long long> support unless _LONGLONG is defined:
#  if !defined(_LONGLONG) && (_CPPLIB_VER <= 310)
#     define BOOST_NO_MS_INT64_NUMERIC_LIMITS
#  endif
// 3.06 appears to have (non-sgi versions of) <hash_set> & <hash_map>,
// and no <slist> at all
#else
#  define BOOST_MSVC_STD_ITERATOR 1
#  define BOOST_NO_STD_ITERATOR
#  define BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
#  define BOOST_NO_STD_ALLOCATOR
#  define BOOST_NO_STDC_NAMESPACE
#  define BOOST_NO_STD_USE_FACET
#  define BOOST_NO_STD_OUTPUT_ITERATOR_ASSIGN
#  define BOOST_HAS_MACRO_USE_FACET
#  ifndef _CPPLIB_VER
      // Updated Dinkum library defines this, and provides
      // its own min and max definitions, as does MTA version.
#     ifndef __MTA__ 
#        define BOOST_NO_STD_MIN_MAX
#     endif
#     define BOOST_NO_MS_INT64_NUMERIC_LIMITS
#  endif
#endif

//
// std extension namespace is stdext for vc7.1 and later, 
// the same applies to other compilers that sit on top
// of vc7.1 (Intel and Comeau):
//
#if defined(_MSC_VER) && (_MSC_VER >= 1310) && !defined(__BORLANDC__)
#  define BOOST_STD_EXTENSION_NAMESPACE stdext
#endif


#if (defined(_MSC_VER) && (_MSC_VER <= 1300) && !defined(__BORLANDC__)) || !defined(_CPPLIB_VER) || (_CPPLIB_VER < 306)
   // if we're using a dinkum lib that's
   // been configured for VC6/7 then there is
   // no iterator traits (true even for icl)
#  define BOOST_NO_STD_ITERATOR_TRAITS
#endif

#if defined(__ICL) && (__ICL < 800) && defined(_CPPLIB_VER) && (_CPPLIB_VER <= 310)
// Intel C++ chokes over any non-trivial use of <locale>
// this may be an overly restrictive define, but regex fails without it:
#  define BOOST_NO_STD_LOCALE
#endif

#if BOOST_MSVC < 1800
// Fix for VC++ 8.0 on up ( I do not have a previous version to test )
// or clang-cl. If exceptions are off you must manually include the 
// <exception> header before including the <typeinfo> header. Admittedly 
// trying to use Boost libraries or the standard C++ libraries without 
// exception support is not suggested but currently clang-cl ( v 3.4 ) 
// does not support exceptions and must be compiled with exceptions off.
#if !_HAS_EXCEPTIONS && ((defined(BOOST_MSVC) && BOOST_MSVC >= 1400) || (defined(__clang__) && defined(_MSC_VER)))
#include <exception>
#endif
#include <typeinfo>
#if ( (!_HAS_EXCEPTIONS && !defined(__ghs__)) || (defined(__ghs__) && !_HAS_NAMESPACE) ) && !defined(__TI_COMPILER_VERSION__) && !defined(__VISUALDSPVERSION__) \
   && !defined(__VXWORKS__)
#  define BOOST_NO_STD_TYPEINFO
#endif  
#endif

//  C++0x headers implemented in 520 (as shipped by Microsoft)
//
#if !defined(_CPPLIB_VER) || _CPPLIB_VER < 520
#  define BOOST_NO_CXX11_HDR_ARRAY
#  define BOOST_NO_CXX11_HDR_CODECVT
#  define BOOST_NO_CXX11_HDR_FORWARD_LIST
#  define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#  define BOOST_NO_CXX11_HDR_RANDOM
#  define BOOST_NO_CXX11_HDR_REGEX
#  define BOOST_NO_CXX11_HDR_SYSTEM_ERROR
#  define BOOST_NO_CXX11_HDR_UNORDERED_MAP
#  define BOOST_NO_CXX11_HDR_UNORDERED_SET
#  define BOOST_NO_CXX11_HDR_TUPLE
#  define BOOST_NO_CXX11_HDR_TYPEINDEX
#  define BOOST_NO_CXX11_HDR_FUNCTIONAL
#  define BOOST_NO_CXX11_NUMERIC_LIMITS
#  define BOOST_NO_CXX11_SMART_PTR
#endif

#if ((!defined(_HAS_TR1_IMPORTS) || (_HAS_TR1_IMPORTS+0 == 0)) && !defined(BOOST_NO_CXX11_HDR_TUPLE)) \
  && (!defined(_CPPLIB_VER) || _CPPLIB_VER < 610)
#  define BOOST_NO_CXX11_HDR_TUPLE
#endif

//  C++0x headers implemented in 540 (as shipped by Microsoft)
//
#if !defined(_CPPLIB_VER) || _CPPLIB_VER < 540
#  define BOOST_NO_CXX11_HDR_TYPE_TRAITS
#  define BOOST_NO_CXX11_HDR_CHRONO
#  define BOOST_NO_CXX11_HDR_CONDITION_VARIABLE
#  define BOOST_NO_CXX11_HDR_FUTURE
#  define BOOST_NO_CXX11_HDR_MUTEX
#  define BOOST_NO_CXX11_HDR_RATIO
#  define BOOST_NO_CXX11_HDR_THREAD
#  define BOOST_NO_CXX11_ATOMIC_SMART_PTR
#  define BOOST_NO_CXX11_HDR_EXCEPTION
#endif

//  C++0x headers implemented in 610 (as shipped by Microsoft)
//
#if !defined(_CPPLIB_VER) || _CPPLIB_VER < 610
#  define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#  define BOOST_NO_CXX11_HDR_ATOMIC
#  define BOOST_NO_CXX11_ALLOCATOR
// 540 has std::align but it is not a conforming implementation
#  define BOOST_NO_CXX11_STD_ALIGN
#endif

// Before 650 std::pointer_traits has a broken rebind template
#if !defined(_CPPLIB_VER) || _CPPLIB_VER < 650
#  define BOOST_NO_CXX11_POINTER_TRAITS
#elif defined(BOOST_MSVC) && BOOST_MSVC < 1910
#  define BOOST_NO_CXX11_POINTER_TRAITS
#endif

#if defined(__has_include)
#if !__has_include(<shared_mutex>)
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#elif (__cplusplus < 201402) && !defined(_MSC_VER)
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif
#elif !defined(_CPPLIB_VER) || (_CPPLIB_VER < 650)
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif

// C++14 features
#if !defined(_CPPLIB_VER) || (_CPPLIB_VER < 650)
#  define BOOST_NO_CXX14_STD_EXCHANGE
#endif

// C++17 features
#if !defined(_CPPLIB_VER) || (_CPPLIB_VER < 650) || !defined(BOOST_MSVC) || (BOOST_MSVC < 1910) || !defined(_HAS_CXX17) || (_HAS_CXX17 == 0)
#  define BOOST_NO_CXX17_STD_APPLY
#  define BOOST_NO_CXX17_ITERATOR_TRAITS
#  define BOOST_NO_CXX17_HDR_STRING_VIEW
#  define BOOST_NO_CXX17_HDR_OPTIONAL
#  define BOOST_NO_CXX17_HDR_VARIANT
#endif
#if !defined(_CPPLIB_VER) || (_CPPLIB_VER < 650) || !defined(_HAS_CXX17) || (_HAS_CXX17 == 0) || !defined(_MSVC_STL_UPDATE) || (_MSVC_STL_UPDATE < 201709)
#  define BOOST_NO_CXX17_STD_INVOKE
#endif

#if !(!defined(_CPPLIB_VER) || (_CPPLIB_VER < 650) || !defined(BOOST_MSVC) || (BOOST_MSVC < 1912) || !defined(_HAS_CXX17) || (_HAS_CXX17 == 0))
// Deprecated std::iterator:
#  define BOOST_NO_STD_ITERATOR
#endif

#if defined(BOOST_INTEL) && (BOOST_INTEL <= 1400)
// Intel's compiler can't handle this header yet:
#  define BOOST_NO_CXX11_HDR_ATOMIC
#endif


//  520..610 have std::addressof, but it doesn't support functions
//
#if !defined(_CPPLIB_VER) || _CPPLIB_VER < 650
#  define BOOST_NO_CXX11_ADDRESSOF
#endif

// Bug specific to VC14, 
// See https://connect.microsoft.com/VisualStudio/feedback/details/1348277/link-error-when-using-std-codecvt-utf8-utf16-char16-t
// and discussion here: http://blogs.msdn.com/b/vcblog/archive/2014/11/12/visual-studio-2015-preview-now-available.aspx?PageIndex=2
#if defined(_CPPLIB_VER) && (_CPPLIB_VER == 650)
#  define BOOST_NO_CXX11_HDR_CODECVT
#endif

#if defined(_CPPLIB_VER) && (_CPPLIB_VER >= 650)
// If _HAS_AUTO_PTR_ETC is defined to 0, std::auto_ptr and std::random_shuffle are not available.
// See https://www.visualstudio.com/en-us/news/vs2015-vs.aspx#C++
// and http://blogs.msdn.com/b/vcblog/archive/2015/06/19/c-11-14-17-features-in-vs-2015-rtm.aspx
#  if defined(_HAS_AUTO_PTR_ETC) && (_HAS_AUTO_PTR_ETC == 0)
#    define BOOST_NO_AUTO_PTR
#    define BOOST_NO_CXX98_RANDOM_SHUFFLE
#    define BOOST_NO_CXX98_FUNCTION_BASE
#    define BOOST_NO_CXX98_BINDERS
#  endif
#endif


//
// Things not supported by the CLR:
#ifdef _M_CEE
#ifndef BOOST_NO_CXX11_HDR_MUTEX
#  define BOOST_NO_CXX11_HDR_MUTEX
#endif
#ifndef BOOST_NO_CXX11_HDR_ATOMIC
#  define BOOST_NO_CXX11_HDR_ATOMIC
#endif
#ifndef BOOST_NO_CXX11_HDR_FUTURE
#  define BOOST_NO_CXX11_HDR_FUTURE
#endif
#ifndef BOOST_NO_CXX11_HDR_CONDITION_VARIABLE
#  define BOOST_NO_CXX11_HDR_CONDITION_VARIABLE
#endif
#ifndef BOOST_NO_CXX11_HDR_THREAD
#  define BOOST_NO_CXX11_HDR_THREAD
#endif
#ifndef BOOST_NO_CXX14_HDR_SHARED_MUTEX
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif
#ifndef BOOST_NO_CXX14_STD_EXCHANGE
#  define BOOST_NO_CXX14_STD_EXCHANGE
#endif
#ifndef BOOST_NO_FENV_H
#  define BOOST_NO_FENV_H
#endif
#endif

#ifdef _CPPLIB_VER
#  define BOOST_DINKUMWARE_STDLIB _CPPLIB_VER
#else
#  define BOOST_DINKUMWARE_STDLIB 1
#endif

#ifdef _CPPLIB_VER
#  define BOOST_STDLIB "Dinkumware standard library version " BOOST_STRINGIZE(_CPPLIB_VER)
#else
#  define BOOST_STDLIB "Dinkumware standard library version 1.x"
#endif

/* dinkumware.hpp
UqNYYMF96hdbAPfooNjD8RtiqF9eiLWGsEzjZ1CZVrTsZKHrcjtaIWbeN736Ue5oxclC1+U+NJ7fhOa3ltMcTNWW4N+ZBg1e4rFJFrouN6MtZbmvKvT+KuX3StwvEDbI1ngmnbPQkslC1+XW12IPK+yuu/IAmoNv8BgjC12Xm9HC5WdFiyILXZfb0DozyzryWBfqM7RuzM5pz1Dutrd8ToSuve1o1ZilKZ20lo4/tLPCnv43J4rFOMjeibW3sKz2yX9T7u/FGAkL/p2wyB0tiix07W0JiQtdQ1tDLHQ9b0tV5m/GzHspv1RxKfYNtHZzhFjovHaGWOj62hVioXPQHWKh63lPiIXuH7whFrrv8KFt4+2cm+cMlflBrHeFrcnY205lok1nVndkH6rP8ZHHha7LnSEWukdwoRmYLcx5X7m+p4p7NMN/iNqZyvrN2qujdoZY6Jrdl8rSetuWk+YPsdA9QiDEQvck8Ilb6F7GhNY2ImjP/rtv07VBLMV91UN+UKxFZh3Nawva1kjFxrywUpwv0oD1kYXc0/GjmclC7+mYogygJwu9TpvRhkYolnFcmp+DNiXSqjPQHv1v/FzSUTtemhdtEbOjfc4vlObUG6AQs4Jm3XlpHrQ1zFZn3ZVIcQYDzGJ2YlqmZ9QWowFyRSj21nA4k7RAGqxPo9jhdt+S2dMZ4A4ods73ojjVl94AU3l+VZ6PlGYxGWhP8g9+Hhs3YrA0H9oKZr0HftVIc2cwwChmFfL7/6YcMhpgGbNLNfSTpZkyGej69xw/3978iHKwpLIHme8OlWZjFsDP+33LbwdteqQDrY6wf2F6cB0izIeWLOwVftYXaPCW4jIbwMMs+nFMdmm2LAbYzKxWP21LaZZYA+xkdjfPub7SzFkNkIZZgS5/HqY4tOwaxdaUrttFmiubAayg2L08w/dJ86N1Y/YeFv8jzZ7dACVYmdlrFsxDcTlwzoNip/s4XNKcOQ2QTbHgtV+YG60oK/PzX7YclF9uA0wDxar1OFuc+hrtLbPnE67WlGbKa4CezJovi11GuaPFKhb8OyJhnrA2I9KH1kC08y1+Xt/q72zSHPkMAMyKzYzrK82T3wAfQDHH1ktvpQUKGMDA4tJUvr1NmrWQAaZHKBbdVf+Y6sNHKR6yuDylsw6idhYPnpeEBc9LwvxouRQL/j2XMFMJAwxgpk0/5FdpbrQyzPocnnORykSLVSykz6BkeDOrmFXF7Gg9mV0+s1FHbUF7HKFY1kdbk6W5LAZ4plGs4J3fukmDbwz0XMl7/FyvfYUh0mxoXTSKrez/pCz1WXkD/MzM8WEwjbulogHSgWJLnhXsQmWixTIb8d3R3TS2aLmYbeqadIfGAa0HszO6Smbqz0oG+JFZnxdtM1C/oOVkdm7e9haUQ2UDXGHW6IJnIpVZxQAXIhS7+3dkI5rX1Q0whFmB80cnS/NaDYCnA7LZJbQmKrOpAV5qFJsWubADjVEzAzQHxZKvD1krDZrj9SFasYPXssRQDm0NMJDZvZ+H5KTcO4f2WdeHkcNoLnUxQG+WwzfZqj0gsxvgXKRi/daVrkQ5JISW+fjzDOprN9pYZqvrZC1F87qXAQ6z+vz1TtSnPusrjj9hPR/sodxt/Qwwj1mOXNtPU+79DdCW2c1+C25Ic6I1YbYsqvxH6he03Sy/+l9nk7kcOH6gWETT9eNp3NEKMasWf2QulYmm43Ow7ek1dK5DG8hy9/Q1F5cGQ0OOh9DzBFoDvWKxFdrlp/zGKnEfUsW50T5HKjYr6bedZBPDx3nRekYo1ujZke/IJmMOGsX0Kb9oqM+mGqAss+mNW3elMfoBj03WlrW6zispbpYB/hH1fcQ=
*/