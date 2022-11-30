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
#ifdef BOOST_BORLANDC
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