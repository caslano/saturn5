
// Copyright 2005-2011 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Note: if you change this include guard, you also need to change
// container_fwd_compile_fail.cpp
#if !defined(BOOST_DETAIL_CONTAINER_FWD_HPP)
#define BOOST_DETAIL_CONTAINER_FWD_HPP

#if defined(_MSC_VER) && \
    !defined(BOOST_DETAIL_TEST_CONFIG_ONLY)
# pragma once
#endif

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// Define BOOST_DETAIL_NO_CONTAINER_FWD if you don't want this header to      //
// forward declare standard containers.                                       //
//                                                                            //
// BOOST_DETAIL_CONTAINER_FWD to make it foward declare containers even if it //
// normally doesn't.                                                          //
//                                                                            //
// BOOST_DETAIL_NO_CONTAINER_FWD overrides BOOST_DETAIL_CONTAINER_FWD.        //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#if !defined(BOOST_DETAIL_NO_CONTAINER_FWD)
#  if defined(BOOST_DETAIL_CONTAINER_FWD)
     // Force forward declarations.
#  elif defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
     // STLport
#    define BOOST_DETAIL_NO_CONTAINER_FWD
#  elif defined(__LIBCOMO__)
     // Comeau STL:
#    define BOOST_DETAIL_NO_CONTAINER_FWD
#  elif defined(__STD_RWCOMPILER_H__) || defined(_RWSTD_VER)
     // Rogue Wave library:
#    define BOOST_DETAIL_NO_CONTAINER_FWD
#  elif defined(_LIBCPP_VERSION)
     // libc++
#    define BOOST_DETAIL_NO_CONTAINER_FWD
#  elif defined(__GLIBCPP__) || defined(__GLIBCXX__)
     // GNU libstdc++ 3
     //
     // Disable forwarding for all recent versions, as the library has a
     // versioned namespace mode, and I don't know how to detect it.
#    if __GLIBCXX__ >= 20070513 \
        || defined(_GLIBCXX_DEBUG) \
        || defined(_GLIBCXX_PARALLEL) \
        || defined(_GLIBCXX_PROFILE)
#      define BOOST_DETAIL_NO_CONTAINER_FWD
#    else
#      if defined(__GLIBCXX__) && __GLIBCXX__ >= 20040530
#        define BOOST_CONTAINER_FWD_COMPLEX_STRUCT
#      endif
#    endif
#  elif defined(__STL_CONFIG_H)
     // generic SGI STL
     //
     // Forward declaration seems to be okay, but it has a couple of odd
     // implementations.
#    define BOOST_CONTAINER_FWD_BAD_BITSET
#    if !defined(__STL_NON_TYPE_TMPL_PARAM_BUG)
#      define BOOST_CONTAINER_FWD_BAD_DEQUE
#     endif
#  elif defined(__MSL_CPP__)
     // MSL standard lib:
#    define BOOST_DETAIL_NO_CONTAINER_FWD
#  elif defined(__IBMCPP__)
     // The default VACPP std lib, forward declaration seems to be fine.
#  elif defined(MSIPL_COMPILE_H)
     // Modena C++ standard library
#    define BOOST_DETAIL_NO_CONTAINER_FWD
#  elif (defined(_YVALS) && !defined(__IBMCPP__)) || defined(_CPPLIB_VER)
     // Dinkumware Library (this has to appear after any possible replacement
     // libraries)
#  else
#    define BOOST_DETAIL_NO_CONTAINER_FWD
#  endif
#endif

#if !defined(BOOST_DETAIL_TEST_CONFIG_ONLY)

#if defined(BOOST_DETAIL_NO_CONTAINER_FWD) && \
    !defined(BOOST_DETAIL_TEST_FORCE_CONTAINER_FWD)

#include <deque>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <string>
#include <complex>

#else

#include <cstddef>

#if defined(BOOST_CONTAINER_FWD_BAD_DEQUE)
#include <deque>
#endif

#if defined(BOOST_CONTAINER_FWD_BAD_BITSET)
#include <bitset>
#endif

#if defined(BOOST_MSVC)
#pragma warning(push)
#pragma warning(disable:4099) // struct/class mismatch in fwd declarations
#endif

namespace std
{
    template <class T> class allocator;
    template <class charT, class traits, class Allocator> class basic_string;

    template <class charT> struct char_traits;

#if defined(BOOST_CONTAINER_FWD_COMPLEX_STRUCT)
    template <class T> struct complex;
#else
    template <class T> class complex;
#endif

#if !defined(BOOST_CONTAINER_FWD_BAD_DEQUE)
    template <class T, class Allocator> class deque;
#endif

    template <class T, class Allocator> class list;
    template <class T, class Allocator> class vector;
    template <class Key, class T, class Compare, class Allocator> class map;
    template <class Key, class T, class Compare, class Allocator>
    class multimap;
    template <class Key, class Compare, class Allocator> class set;
    template <class Key, class Compare, class Allocator> class multiset;

#if !defined(BOOST_CONTAINER_FWD_BAD_BITSET)
    template <size_t N> class bitset;
#endif
    template <class T1, class T2> struct pair;
}

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

#endif // BOOST_DETAIL_NO_CONTAINER_FWD &&
       // !defined(BOOST_DETAIL_TEST_FORCE_CONTAINER_FWD)

#endif // BOOST_DETAIL_TEST_CONFIG_ONLY

#endif

/* container_fwd.hpp
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
*/