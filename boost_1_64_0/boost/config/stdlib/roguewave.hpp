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
17nN22bIJfrb/OXm97i+O2aYJ+ySq3Adtrtm+AF08w/99ynbPe38QbPcBU9tJ/M+MMNjEXeoi20yWeChGbYl6NZw+u8/k0HMDLdEXEq+T/xkzidmaC7ifN4LvO06nuL2IuLqmvI147hnZkgVea77oOMrjvvbDO1kDU9K9eS5/ccMfYXlqeAYyDW8MENSom7/jlk0nWt/ZYYioNuNEqHPyYJoIOd92Z30ZNHXOH8i7t79f7ZyniYLTBXWPmegLeeJlpEt7hhMYVGFxRQGCcbmUJhTYS6FuRXmUZhXYT6F+RUWUFhQYSGFhRUWUVhUYTGFQaJi/hTmVJhLYW6FeRTmVZhPYX6FBRQWVFhIYWGFRRQWVVhMYZCkmD+FOdHumXQrfin9Rh6X9Bb4Vli2metPce0ZLVAAdLt8Z36GN9apexQtUbNquA7N1/2ixQxtsA8y6VYdr+mW5jC05B5OtBaa1TD1/GBEOEsHsgDaK2HvzjydmSyS2QIPhEXLFtxKBhYLrBJW+fPgPxyHls2kW4lNowqTuWzaWGvGY43mVphHYV5DA/ChXdCsJr5QLTK3DZnfboG7wva/GjyK58+Bnx3CNj3L8F/9/jZYuzD84UYXMtfbFggJS9d142syxzvGFkMLmHSbMrPybbYsFrgv4s79vbQXmTMb1i5M1u5SmFthHoV5FeZTmF9hAYUFFRZSWFhhEYVFFRZTGGQ3NofCnApzKcytMI/CvIaG18mhtdDMjcb7CbQo2ithvJ9Ac+bE/YQw3k+geXLhe0WYvp/AuNzafkIz3k+g+fNoeWom8wwoLKiwkKF1TQ6jPdaslmla4i7Hj1ayWF4LbDfpNivy6l0y53sWaCIs9/57U7nN/DguCbq9V7bsaDJfIQtUBt2e//SgEcehLUvUbfS0I0DmKa7VoJmswWtoyb18aE01q20qXfHTUb8kkUXizBy++xaZqwTOnzCePzT4QJs/zXj+0LwlLVBKWPvOB5+QRUtZoI6wWnVLDCHzl7bAHGE7fxkxg62sBWzCbp6Opec2y2m1ayZrjykMyhubQ2FOhbkMrd8AN9o3mtXBNfgfBx7PQOasYIENwvbv+bsnGVS0QE9hZ+YXmkvmRwsIa9fVt537q2SBM8JqlWm+jcxT2QIzTLqdSEysw3FVLZAsbHn/NnXJHNUt8KOwiY9ucH+emhboI2yx7+drHFfLAp8JO2O62JgsVlsbM83kmEEdY3MozKkwl8LcCvMozKswn8L8CgsoLKiwkMLCaLUTdHvcvF1GbrO+BTKLORoYfHGAj00bWPi65rr4e0Oz7YsebA0tMEVY3sxT75IFG+FnhzD+7ECLNtb2IZrxPgTN3VT7XNGMP1fQfM2wPmFcH5pfYQGFBQ0tuUcILb1m9fAYk3+3ixZGcwkrZqv/ORk0xzaFye9CHGhZNauP34Xw93FoLoV5FOZTWEBhIYVFFBZTmKOFoj5Dc5X2oPXVrIEppe+QZov2kEXR1gn7vt6vdchCHguUN+k2e2W202Tuj3BfJ+LWjV1UjyyGBiIu34hcpchcrSzwUMSN2VChA5m3tQVWC2sw/vMlHNfGAjlEmxeLtG5GFmirbROa8TaBFlRYSGFhhUUUFlVYDK2LsFOf9WlP5mtngY+EbbvrvE2/b4yitdCsoan7UD6ORPO0x2MNYbtPPl1EFkLLKIxzQQsbGn6vjfZas0a4z3rQupiVzNHRAnUTdKs+656TLNbZAi2F5cm8YyRZ1Kv1p1ma8wC0DzRrgi9UXzb+PTJXN9zXCesRnladzNcd92fCPmtVbTpZsAceZ7HJ42SM66ntIzW71fbsdbJIL84TLe5cRmExhUFvI8Pf2aB11awp2qE=
*/