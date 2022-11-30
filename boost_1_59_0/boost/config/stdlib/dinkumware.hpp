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
#  if !(defined(_GLOBAL_USING) && (_GLOBAL_USING+0 > 0)) && !defined(BOOST_BORLANDC) && !defined(_STD) && !(defined(__ICC) && (__ICC >= 700))   // can be defined in yvals.h
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
#if defined(_MSC_VER) && (_MSC_VER >= 1310) && !defined(BOOST_BORLANDC)
#  define BOOST_STD_EXTENSION_NAMESPACE stdext
#endif


#if (defined(_MSC_VER) && (_MSC_VER <= 1300) && !defined(BOOST_BORLANDC)) || !defined(_CPPLIB_VER) || (_CPPLIB_VER < 306)
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

#if ((defined(BOOST_MSVC) && BOOST_MSVC >= 1400) || (defined(__clang__) && defined(_MSC_VER))) && (_MSC_VER < 1800)
// Fix for VC++ 8.0 on up ( I do not have a previous version to test )
// or clang-cl. If exceptions are off you must manually include the 
// <exception> header before including the <typeinfo> header. Admittedly 
// trying to use Boost libraries or the standard C++ libraries without 
// exception support is not suggested but currently clang-cl ( v 3.4 ) 
// does not support exceptions and must be compiled with exceptions off.
#if !_HAS_EXCEPTIONS
#include <exception>
#endif
#include <typeinfo>
#if !_HAS_EXCEPTIONS
#  define BOOST_NO_STD_TYPEINFO
#endif  
#endif
#if defined(__ghs__) && !_HAS_NAMESPACE
#  define BOOST_NO_STD_TYPEINFO
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
#if !defined(_CPPLIB_VER) || (_CPPLIB_VER < 650) \
 || ((!defined(BOOST_MSVC) || (BOOST_MSVC < 1910))) && (!defined(__clang__) || !defined(_MSC_VER) || (_MSC_VER < 1929))\
 || !defined(_HAS_CXX17) || (_HAS_CXX17 == 0)
#  define BOOST_NO_CXX17_STD_APPLY
#  define BOOST_NO_CXX17_ITERATOR_TRAITS
#  define BOOST_NO_CXX17_HDR_STRING_VIEW
#  define BOOST_NO_CXX17_HDR_OPTIONAL
#  define BOOST_NO_CXX17_HDR_VARIANT
#  define BOOST_NO_CXX17_HDR_ANY
#  define BOOST_NO_CXX17_HDR_MEMORY_RESOURCE
#  define BOOST_NO_CXX17_HDR_CHARCONV
#  define BOOST_NO_CXX17_HDR_EXECUTION
#  define BOOST_NO_CXX17_HDR_FILESYSTEM
#endif
#if !defined(_CPPLIB_VER) || (_CPPLIB_VER < 650) || !defined(_HAS_CXX17) || (_HAS_CXX17 == 0) || !defined(_MSVC_STL_UPDATE) || (_MSVC_STL_UPDATE < 201709)
#  define BOOST_NO_CXX17_STD_INVOKE
#endif

// C++20 features which aren't configured in suffix.hpp correctly:
#if !defined(_MSVC_STL_UPDATE) || (_MSVC_STL_UPDATE < 202008L) || !defined(_HAS_CXX20) || (_HAS_CXX20 == 0)
#  define BOOST_NO_CXX20_HDR_CONCEPTS
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
#if defined(_CPPLIB_VER) && (_CPPLIB_VER == 650) && (!defined(_MSVC_STL_VERSION) || (_MSVC_STL_VERSION < 142))
#  define BOOST_NO_CXX11_HDR_CODECVT
#endif

#if (_MSVC_LANG > 201700) && !defined(BOOST_NO_CXX11_HDR_CODECVT)
//
// <codecvt> is deprected as of C++17, and by default MSVC emits hard errors
// if you try to use it, so mark it as unavailable:
//
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
// Things deprecated in C++20:
//
#if defined(_HAS_CXX20)
#  define BOOST_NO_CXX11_ATOMIC_SMART_PTR
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
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
*/