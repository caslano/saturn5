// Copyright (c) 2016-2022 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PFR_DETAIL_CONFIG_HPP
#define BOOST_PFR_DETAIL_CONFIG_HPP
#pragma once

#include <type_traits> // to get non standard platform macro definitions (__GLIBCXX__ for example)

// Reminder:
//  * MSVC++ 14.2 _MSC_VER == 1927 <- Loophole is known to work (Visual Studio ????)
//  * MSVC++ 14.1 _MSC_VER == 1916 <- Loophole is known to NOT work (Visual Studio 2017)
//  * MSVC++ 14.0 _MSC_VER == 1900 (Visual Studio 2015)
//  * MSVC++ 12.0 _MSC_VER == 1800 (Visual Studio 2013)

#if defined(_MSC_VER)
#   if !defined(_MSVC_LANG) || _MSC_VER <= 1900
#       error Boost.PFR library requires more modern MSVC compiler.
#   endif
#elif __cplusplus < 201402L
#   error Boost.PFR library requires at least C++14.
#endif

#ifndef BOOST_PFR_USE_LOOPHOLE
#   if defined(_MSC_VER)
#       if _MSC_VER >= 1927
#           define BOOST_PFR_USE_LOOPHOLE 1
#       else
#           define BOOST_PFR_USE_LOOPHOLE 0
#       endif
#   elif defined(__clang_major__) && __clang_major__ >= 8
#       define BOOST_PFR_USE_LOOPHOLE 0
#   else
#       define BOOST_PFR_USE_LOOPHOLE 1
#   endif
#endif

#ifndef BOOST_PFR_USE_CPP17
#   ifdef __cpp_structured_bindings
#       define BOOST_PFR_USE_CPP17 1
#   elif defined(_MSVC_LANG)
#       if _MSVC_LANG >= 201703L
#           define BOOST_PFR_USE_CPP17 1
#       else
#           define BOOST_PFR_USE_CPP17 0
#       endif
#   else
#       define BOOST_PFR_USE_CPP17 0
#   endif
#endif

#if (!BOOST_PFR_USE_CPP17 && !BOOST_PFR_USE_LOOPHOLE)
#   if (defined(_MSC_VER) && _MSC_VER < 1916) ///< in Visual Studio 2017 v15.9 PFR library with classic engine normally works
#      error Boost.PFR requires /std:c++latest or /std:c++17 flags on your compiler.
#   endif
#endif

#ifndef BOOST_PFR_USE_STD_MAKE_INTEGRAL_SEQUENCE
// Assume that libstdc++ since GCC-7.3 does not have linear instantiation depth in std::make_integral_sequence
#   if defined( __GLIBCXX__) && __GLIBCXX__ >= 20180101
#       define BOOST_PFR_USE_STD_MAKE_INTEGRAL_SEQUENCE 1
#   elif defined(_MSC_VER)
#       define BOOST_PFR_USE_STD_MAKE_INTEGRAL_SEQUENCE 1
//# elif other known working lib
#   else
#       define BOOST_PFR_USE_STD_MAKE_INTEGRAL_SEQUENCE 0
#   endif
#endif

#ifndef BOOST_PFR_HAS_GUARANTEED_COPY_ELISION
#   if  defined(__cpp_guaranteed_copy_elision) && (!defined(_MSC_VER) || _MSC_VER > 1928)
#       define BOOST_PFR_HAS_GUARANTEED_COPY_ELISION 1
#   else
#       define BOOST_PFR_HAS_GUARANTEED_COPY_ELISION 0
#   endif
#endif

#if defined(__has_cpp_attribute)
#   if __has_cpp_attribute(maybe_unused)
#       define BOOST_PFR_MAYBE_UNUSED [[maybe_unused]]
#   endif
#endif

#ifndef BOOST_PFR_MAYBE_UNUSED
#   define BOOST_PFR_MAYBE_UNUSED
#endif


#endif // BOOST_PFR_DETAIL_CONFIG_HPP

/* config.hpp
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
*/