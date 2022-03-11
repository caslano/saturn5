//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Jens Maurer 2001. 
//  (C) Copyright David Abrahams 2003. 
//  (C) Copyright Boris Gubenko 2007. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Rogue Wave std lib:

#define BOOST_RW_STDLIB 1 

#if !defined(__STD_RWCOMPILER_H__) && !defined(_RWSTD_VER)
#  include <boost/config/no_tr1/utility.hpp>
#  if !defined(__STD_RWCOMPILER_H__) && !defined(_RWSTD_VER)
#     error This is not the Rogue Wave standard library
#  endif
#endif
//
// figure out a consistent version number:
//
#ifndef _RWSTD_VER
#  define BOOST_RWSTD_VER 0x010000
#elif _RWSTD_VER < 0x010000
#  define BOOST_RWSTD_VER (_RWSTD_VER << 8)
#else
#  define BOOST_RWSTD_VER _RWSTD_VER
#endif

#ifndef _RWSTD_VER
#  define BOOST_STDLIB "Rogue Wave standard library version (Unknown version)"
#elif _RWSTD_VER < 0x04010200
 #  define BOOST_STDLIB "Rogue Wave standard library version " BOOST_STRINGIZE(_RWSTD_VER)
#else
#  ifdef _RWSTD_VER_STR
#    define BOOST_STDLIB "Apache STDCXX standard library version " _RWSTD_VER_STR
#  else
#    define BOOST_STDLIB "Apache STDCXX standard library version " BOOST_STRINGIZE(_RWSTD_VER)
#  endif
#endif

//
// Prior to version 2.2.0 the primary template for std::numeric_limits
// does not have compile time constants, even though specializations of that
// template do:
//
#if BOOST_RWSTD_VER < 0x020200
#  define BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
#endif

// Sun CC 5.5 patch 113817-07 adds long long specialization, but does not change the
// library version number (http://sunsolve6.sun.com/search/document.do?assetkey=1-21-113817):
#if BOOST_RWSTD_VER <= 0x020101 && (!defined(__SUNPRO_CC) || (__SUNPRO_CC < 0x550))
#  define BOOST_NO_LONG_LONG_NUMERIC_LIMITS
# endif

//
// Borland version of numeric_limits lacks __int64 specialisation:
//
#ifdef __BORLANDC__
#  define BOOST_NO_MS_INT64_NUMERIC_LIMITS
#endif

//
// No std::iterator if it can't figure out default template args:
//
#if defined(_RWSTD_NO_SIMPLE_DEFAULT_TEMPLATES) || defined(RWSTD_NO_SIMPLE_DEFAULT_TEMPLATES) || (BOOST_RWSTD_VER < 0x020000)
#  define BOOST_NO_STD_ITERATOR
#endif

//
// No iterator traits without partial specialization:
//
#if defined(_RWSTD_NO_CLASS_PARTIAL_SPEC) || defined(RWSTD_NO_CLASS_PARTIAL_SPEC)
#  define BOOST_NO_STD_ITERATOR_TRAITS
#endif

//
// Prior to version 2.0, std::auto_ptr was buggy, and there were no
// new-style iostreams, and no conformant std::allocator:
//
#if (BOOST_RWSTD_VER < 0x020000)
#  define BOOST_NO_AUTO_PTR
#  define BOOST_NO_STRINGSTREAM
#  define BOOST_NO_STD_ALLOCATOR
#  define BOOST_NO_STD_LOCALE
#endif

//
// No template iterator constructors without member template support:
//
#if defined(RWSTD_NO_MEMBER_TEMPLATES) || defined(_RWSTD_NO_MEMBER_TEMPLATES)
#  define BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
#endif

//
// RW defines _RWSTD_ALLOCATOR if the allocator is conformant and in use
// (the or _HPACC_ part is a hack - the library seems to define _RWSTD_ALLOCATOR
// on HP aCC systems even though the allocator is in fact broken):
//
#if !defined(_RWSTD_ALLOCATOR) || (defined(__HP_aCC) && __HP_aCC <= 33100)
#  define BOOST_NO_STD_ALLOCATOR
#endif

//
// If we have a std::locale, we still may not have std::use_facet:
//
#if defined(_RWSTD_NO_TEMPLATE_ON_RETURN_TYPE) && !defined(BOOST_NO_STD_LOCALE)
#  define BOOST_NO_STD_USE_FACET
#  define BOOST_HAS_TWO_ARG_USE_FACET
#endif

//
// There's no std::distance prior to version 2, or without
// partial specialization support:
//
#if (BOOST_RWSTD_VER < 0x020000) || defined(_RWSTD_NO_CLASS_PARTIAL_SPEC)
    #define BOOST_NO_STD_DISTANCE
#endif

//
// Some versions of the rogue wave library don't have assignable
// OutputIterators:
//
#if BOOST_RWSTD_VER < 0x020100
#  define BOOST_NO_STD_OUTPUT_ITERATOR_ASSIGN
#endif

//
// Disable BOOST_HAS_LONG_LONG when the library has no support for it.
//
#if !defined(_RWSTD_LONG_LONG) && defined(BOOST_HAS_LONG_LONG)
#  undef BOOST_HAS_LONG_LONG
#endif

//
// check that on HP-UX, the proper RW library is used
//
#if defined(__HP_aCC) && !defined(_HP_NAMESPACE_STD)
#  error "Boost requires Standard RW library. Please compile and link with -AA"
#endif

//
// Define macros specific to RW V2.2 on HP-UX
//
#if defined(__HP_aCC) && (BOOST_RWSTD_VER == 0x02020100)
#  ifndef __HP_TC1_MAKE_PAIR
#    define __HP_TC1_MAKE_PAIR
#  endif
#  ifndef _HP_INSTANTIATE_STD2_VL
#    define _HP_INSTANTIATE_STD2_VL
#  endif
#endif

#if _RWSTD_VER < 0x05000000
#  define BOOST_NO_CXX11_HDR_ARRAY
#endif
// type_traits header is incomplete:
#  define BOOST_NO_CXX11_HDR_TYPE_TRAITS
//
//  C++0x headers not yet implemented
//
#  define BOOST_NO_CXX11_HDR_CHRONO
#  define BOOST_NO_CXX11_HDR_CODECVT
#  define BOOST_NO_CXX11_HDR_CONDITION_VARIABLE
#  define BOOST_NO_CXX11_HDR_FORWARD_LIST
#  define BOOST_NO_CXX11_HDR_FUTURE
#  define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#  define BOOST_NO_CXX11_HDR_MUTEX
#  define BOOST_NO_CXX11_HDR_RANDOM
#  define BOOST_NO_CXX11_HDR_RATIO
#  define BOOST_NO_CXX11_HDR_REGEX
#  define BOOST_NO_CXX11_HDR_SYSTEM_ERROR
#  define BOOST_NO_CXX11_HDR_THREAD
#  define BOOST_NO_CXX11_HDR_TUPLE
#  define BOOST_NO_CXX11_HDR_TYPEINDEX
#  define BOOST_NO_CXX11_HDR_UNORDERED_MAP
#  define BOOST_NO_CXX11_HDR_UNORDERED_SET
#  define BOOST_NO_CXX11_NUMERIC_LIMITS
#  define BOOST_NO_CXX11_ALLOCATOR
#  define BOOST_NO_CXX11_POINTER_TRAITS
#  define BOOST_NO_CXX11_ATOMIC_SMART_PTR
#  define BOOST_NO_CXX11_SMART_PTR
#  define BOOST_NO_CXX11_HDR_FUNCTIONAL
#  define BOOST_NO_CXX11_HDR_ATOMIC
#  define BOOST_NO_CXX11_STD_ALIGN
#  define BOOST_NO_CXX11_ADDRESSOF
#  define BOOST_NO_CXX11_HDR_EXCEPTION

#if defined(__has_include)
#if !__has_include(<shared_mutex>)
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#elif __cplusplus < 201402
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif
#else
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif

// C++14 features
#  define BOOST_NO_CXX14_STD_EXCHANGE

// C++17 features
#  define BOOST_NO_CXX17_STD_APPLY
#  define BOOST_NO_CXX17_STD_INVOKE
#  define BOOST_NO_CXX17_ITERATOR_TRAITS

/* roguewave.hpp
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
*/