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
KTg4kETYH9AaCJRUvv2UuR2GXXHM9xbqgedH9c8IxFzrwt+z3IdJfMMzPlVvdv5eSOiEW2EP/wjr392Eaekj8UtxhvWgY+FyAREinplc8lUEiPoKtZDwiQkFyXoAHetXb2xFKQDrfgN68hyYQ4cQuTKCbql4xKdeCcUSstcbfI/kKh2XZjGefOKT15hc987E+/fNV8f16q2VSx6RSx1bUo5nE/FOWGurH4E4sPEvaD0fit+AbrBvXMnuA2jM5wPSCJFvvdKGa39VSJdaxw/hMWA8Ouiw3kGjc5SnkcITUMijrf3bXl5fX2zzzYCl3KELBovOKRTcpGhxYbMI8lsWcuvoX/TCDm1crRiBpgL79X88vel1NyiUzb4v82gOAR0trVvTvC0TTbqqQd8UYlY1gvuT7hxi7KFprem2fvwLCDIF+zWI9RlPJgmroHBnKTpjUoIYYIBaVR5OBFvkTF4jcLMZ0o0IGnxDpZuC2uftsIz/vhyTdJXdsPD4iovjd0EEcFjR1DGNQKiIg0VfkzLq/RGpCIOSbArXBs5lahQS8IaMNF/KaUvG2R0zyg==
*/