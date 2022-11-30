/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010      Eric Niebler
    Copyright (c) 2014-2015 John Fletcher
    Copyright (c) 2016      Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CONFIG_HPP
#define BOOST_PHOENIX_CONFIG_HPP

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

//////////////////////////////////////////////////////////////////////////
// This section is to sort out whether hash types or unordered types
// are available. This depends on whether stdlib or libc++ is being used
// and also whether C++11 or C++03 is being used.
//////////////////////////////////////////////////////////////////////////
// The idea is to set up the configuration without including the actual
// headers unless that is unavoidable.
//
// The client code should contain the following to include headers
//
// #ifdef BOOST_PHOENIX_HAS_HASH
// #include BOOST_PHOENIX_HASH_SET_HEADER
// #include BOOST_PHOENIX_HASH_MAP_HEADER
// #endif
//
// #ifdef BOOST_PHOENIX_HAS_UNORDERED_SET_AND_MAP
// #include BOOST_PHOENIX_UNORDERED_SET_HEADER
// #include BOOST_PHOENIX_UNORDERED_MAP_HEADER
// #endif
//
// The client code can then chose the implementation provided.
// See the example in test/stl/querying_find2.cpp

// There is no specific thing in Boost Config for libc++
#ifdef _LIBCPP_VERSION
#define BOOST_PHOENIX_USING_LIBCPP
#endif

// This may not be true for some very old version of libc++
// Current libc++ supports unordered_set and unordered_map without C++11.
#if defined(BOOST_PHOENIX_USING_LIBCPP) \
 && !(defined(BOOST_NO_CXX11_HDR_UNORDERED_MAP) || defined(BOOST_NO_CXX11_HDR_UNORDERED_SET))
// This is either libc++ or C++11 or later
#define BOOST_PHOENIX_HAS_UNORDERED_SET_AND_MAP
#define BOOST_PHOENIX_UNORDERED_SET_HEADER <unordered_set>
#define BOOST_PHOENIX_UNORDERED_MAP_HEADER <unordered_map>
#define BOOST_PHOENIX_UNORDERED_NAMESPACE std
#endif

#if defined(BOOST_HAS_HASH)
// This is to sort out case of Clang when using stdlib from gcc
// as Clang thinks it is gcc 4.2.1
// This prevents the failure to include a header with a warning.
#define _GLIBCXX_PERMIT_BACKWARD_HASH
#define BOOST_PHOENIX_HASH_SET_HEADER BOOST_HASH_SET_HEADER
#define BOOST_PHOENIX_HASH_MAP_HEADER BOOST_HASH_MAP_HEADER
#define BOOST_PHOENIX_HAS_HASH
#define BOOST_PHOENIX_HASH_NAMESPACE BOOST_STD_EXTENSION_NAMESPACE
#define BOOST_PHOENIX_HASH_template_rest_param class Hash, class Cmp, class Alloc
#define BOOST_PHOENIX_HASH_type_rest_param           Hash,       Cmp,       Alloc
#elif defined(BOOST_DINKUMWARE_STDLIB) && (BOOST_DINKUMWARE_STDLIB < 610)
#define BOOST_PHOENIX_HASH_SET_HEADER <hash_set>
#define BOOST_PHOENIX_HASH_MAP_HEADER <hash_map>
#define BOOST_PHOENIX_HAS_HASH
#define BOOST_PHOENIX_HASH_NAMESPACE stdext
#define BOOST_PHOENIX_HASH_template_rest_param class Tr, class Alloc
#define BOOST_PHOENIX_HASH_type_rest_param           Tr,       Alloc
#endif

#if BOOST_WORKAROUND(BOOST_GCC, < 40100)
#define BOOST_PHOENIX_SFINAE_AND_OVERLOADS , void* = 0
#else
#define BOOST_PHOENIX_SFINAE_AND_OVERLOADS
#endif

#endif

/* config.hpp
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
*/