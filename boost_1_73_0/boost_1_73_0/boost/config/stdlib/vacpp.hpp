//  (C) Copyright John Maddock 2001 - 2002. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

#if __IBMCPP__ <= 501
#  define BOOST_NO_STD_ALLOCATOR
#endif

#define BOOST_HAS_MACRO_USE_FACET
#define BOOST_NO_STD_MESSAGES

// Apple doesn't seem to reliably defined a *unix* macro
#if !defined(CYGWIN) && (  defined(__unix__)  \
                        || defined(__unix)    \
                        || defined(unix)      \
                        || defined(__APPLE__) \
                        || defined(__APPLE)   \
                        || defined(APPLE))
#  include <unistd.h>
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

#define BOOST_STDLIB "Visual Age default standard library"

/* vacpp.hpp
tF3JbRgNgnApgNwRxskS0xEFlVKN/DAe513LsZJxIXI5zndUOJVafVfVHNGsyAZEo0AJ6CS1QdvbsBIFK/WKFOFh0y05k5W9h4UJ62IsWpCU8204dGVU9iVQSLZs2doSGkTPlF6kqKXOtq7E6sAQad0GKru2xnRIC9oVAom3oasL2hp7Q8Quy5ZlQ/lPWrbHXoCoERUM3AT8ZABLIpm04cZPr6JZCjduHLthOofoEtxwvo137YcXqA2GWVug901LJaJoga0azmhxkPyXTrrlpFcwmcWBH15GWexd+LE3SbNJNAtTeAuDN+/B7W61vP8YwICzpe4/nDjv3jmv8UC/ZZTITXZLFatLoduNqpIYOLmC0P3iWT+KvngF6GSIrrsVzoumvaUFQ90qafyTeRhNEz+xfmN1zruCwrnO2Iuw+mSZ2LnA8ydAhvoTHFWoD44y+QEIG7iob+EoF12tmtGZyXrhJZPYn6Z+FFpTgo0g0AhWKy0RnIreBXfb+ep1IxThz9TBjCArHKA1balFctURzjdQCs7F2nQWM07jKI0mUZBYV2k6HSYjc+r97X6ZBp7l1KXVV2PI//i/YlnN1BBhs3KoD0fwrwXwSAqq6Azf9+aSKuyPMe0piaZphosNg91803uCmqNOLlaD0Qu8
*/