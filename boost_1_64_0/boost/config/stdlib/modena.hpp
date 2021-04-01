//  (C) Copyright Jens Maurer 2001. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Modena C++ standard library (comes with KAI C++)

#if !defined(MSIPL_COMPILE_H)
#  include <boost/config/no_tr1/utility.hpp>
#  if !defined(__MSIPL_COMPILE_H)
#      error "This is not the Modena C++ library!"
#  endif
#endif

#ifndef MSIPL_NL_TYPES
#define BOOST_NO_STD_MESSAGES
#endif

#ifndef MSIPL_WCHART
#define BOOST_NO_STD_WSTRING
#endif

//  C++0x headers not yet implemented
//
#  define BOOST_NO_CXX11_HDR_ARRAY
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
#  define BOOST_NO_CXX11_HDR_TYPE_TRAITS
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

#define BOOST_STDLIB "Modena C++ standard library"






/* modena.hpp
vCvVLdr/BN7GzxNq2P5DjD/rutEthRODhkPd41cd8NRq4MutRWgfcgqNesHoW8luz6L7s+vqlO27pgIIefHxruWWtlxKKqj20Cqar+KmxYRP2XWlIqgsHJhcw7NWkzJHyOutWkNw2l+1fb+2FbOZ2uFQkps2jfIaCb5wMwp5734SqXh1JdrmEb4IBRVtzcEodUCsZ9QLWvHOpfJINmnUEU4WNFBtuoo/4gMeGQjOXOPAL/t0DTc9BJGaHhDDaQxYcGkiqsb+6talmf30AFAiynJDb/C9FzVmxsDbDiAdEDe9q/VdjUsHcDwOle0v+3nz+7kljyHxZ57QUU6djv+wxzaXm7JmtxEa8RU2auSvOvK+E/h2aR7AeHx3F/SZDlNzVY2wAVN705j15p/+ImeUYd2iIWJ65UaPuXmjxGQO8TeCKlX5orH0jL80G7YNRAMO7mJN9BvtB3RgUmaEcyW5nye948yZTLUQcrOJS6Zlgv3Q+kuJKUUNmbprlHcVaO2ZgjNxfEyJ3HsC/P2f4y4Ov2Bo5pL6Onu8tQfveHPd8+gGJlpi88LPXGqLsg==
*/