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
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
*/