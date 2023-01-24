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
oSfNxkPPOg2kphXIqojmmShJOmLjzJM7BlV90ToosvEBT1EwzzczxcmYwV3Rz9aYwYz/YOz011cvfBr8rNZjfwBpOPBDn18ZMTmAtPvdMvxcoYv4+p3FdXURoUMlB0QrDqiD8Tz7+utjAC70Ogx8u/6zKI06ZC9Gfv0VYBV776CU/NptnPObORq+JdukPL2XhFHgioTnO4RVH/nta/iatvfDd+NH9XxdoG3D17vDhacDl5EspLnUIk7tY4kuiMY77CbA7fABg0TDgTCA2UG/R/DRiLr28ysPlg2ZBxFhb5UcyrJ3AERxXMGp6vAri3KoVYPKGOLf628WoOFrPazCDBrCzWe1/7GVCzJaVEcg7VIvZKKpfCdtV5xnPddToArtdpBNK5khVPF258AkOV7LoTVhEZVTRAouMzHCslfi0uDn5DEXGtJWEffWEf9lJBW6PQITqFKr88gsg5RvDzniM8og5m8c1UVt19uF/be1pk7E5MBEDIU6D+XltqnpcSAZqIGQ9Or6BY9qnadCasvG38ysk2Z5JNN377chhq515fwh29+QNKGrTvvcGL9YAaY/REBxBRlfH9sY1xUIsJN1xfohJ4lTOJUkhvEboP1nnyQSVFdsDn/Z0HCa1Jj1CFOWs6/iFDLNP3Z6KCs5pkOyUx8JO9z29Ejtw5zC/vvbfs2T9sXm3fWshOrMMe4/MEjKKRymbeFf5C56qenk
*/