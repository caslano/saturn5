//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_MOVE_DETAIL_WORKAROUND_HPP
#define BOOST_MOVE_DETAIL_WORKAROUND_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#if    !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
   #define BOOST_MOVE_PERFECT_FORWARDING
#endif

#if defined(__has_feature)
   #define BOOST_MOVE_HAS_FEATURE __has_feature
#else
   #define BOOST_MOVE_HAS_FEATURE(x) 0
#endif

#if BOOST_MOVE_HAS_FEATURE(address_sanitizer) || defined(__SANITIZE_ADDRESS__)
   #define BOOST_MOVE_ADDRESS_SANITIZER_ON
#endif

//Macros for documentation purposes. For code, expands to the argument
#define BOOST_MOVE_IMPDEF(TYPE) TYPE
#define BOOST_MOVE_SEEDOC(TYPE) TYPE
#define BOOST_MOVE_DOC0PTR(TYPE) TYPE
#define BOOST_MOVE_DOC1ST(TYPE1, TYPE2) TYPE2
#define BOOST_MOVE_I ,
#define BOOST_MOVE_DOCIGN(T1) T1

#if defined(__GNUC__) && (__GNUC__ == 4) && (__GNUC_MINOR__ < 5) && !defined(__clang__)
   //Pre-standard rvalue binding rules
   #define BOOST_MOVE_OLD_RVALUE_REF_BINDING_RULES
#elif defined(_MSC_VER) && (_MSC_VER == 1600)
   //Standard rvalue binding rules but with some bugs
   #define BOOST_MOVE_MSVC_10_MEMBER_RVALUE_REF_BUG
   #define BOOST_MOVE_MSVC_AUTO_MOVE_RETURN_BUG
#elif defined(_MSC_VER) && (_MSC_VER == 1700)
   #define BOOST_MOVE_MSVC_AUTO_MOVE_RETURN_BUG
#endif

#if defined(BOOST_MOVE_DISABLE_FORCEINLINE)
   #define BOOST_MOVE_FORCEINLINE inline
#elif defined(BOOST_MOVE_FORCEINLINE_IS_BOOST_FORCELINE)
   #define BOOST_MOVE_FORCEINLINE BOOST_FORCEINLINE
#elif defined(BOOST_MSVC) && defined(_DEBUG)
   //"__forceinline" and MSVC seems to have some bugs in debug mode
   #define BOOST_MOVE_FORCEINLINE inline
#elif defined(__GNUC__) && ((__GNUC__ < 4) || (__GNUC__ == 4 && (__GNUC_MINOR__ < 5)))
   //Older GCCs have problems with forceinline
   #define BOOST_MOVE_FORCEINLINE inline
#else
   #define BOOST_MOVE_FORCEINLINE BOOST_FORCEINLINE
#endif

#endif   //#ifndef BOOST_MOVE_DETAIL_WORKAROUND_HPP

/* workaround.hpp
BCxJ/HRRbY+H5kRti1WUQxItVwKRAm4o+BD6UVxw+h3S13h1rVIXrTiPI5qKyopAPWyVGJBQZFvRAQE99RP07dYzEDIuLYKvkViBchuwDE3TtRKJRIKmtwPiOBPv3LBdb2xOjLeKs9wAvTJHHfZa015czBzXtF6/QF5rZrva2avuj9D+AM3pbGbBWVOtf1APvfKhrR765UNLOqQCqTVcDO0RvtgqHbOlJuNBEncC1GWrAS4rD6BnrjB+wjXIawE/FJSjh6kKJFj5OfqXptDMV0w0iX6rsEiQcSZYwOIBmTuGDX7K0nXCirxBrKHjAJr4K/3mJ1lMO3gqvr0eNUhpWINIbRtE3reC47f70TLArBC9EqHsaRDH/MMAaUIDA8G1q2XpiQb5MDfdBtqz00cPo5iCvJa3zbseaELCFvhW0G+iOSBaa/MBR2mKAbegsKQp5b7AhLpZK08oX1augzhK0TeMxbCVbhFowTCOFdCjfr728NJZJo5PMEhExNIcfE4xBYIiQacjsy9eS6GVEFmOoSAFOznVqovTAu0+VWclkpjUzvx/H40cRWkQF2iuXp4oNVhhOESpgMSP0mO58PkyOIVg5XNo4fr2z79OyN+Yz+dze6J8xal4Uz1Da5Uu5EMueBGI0hl5HGEUtdTP
*/