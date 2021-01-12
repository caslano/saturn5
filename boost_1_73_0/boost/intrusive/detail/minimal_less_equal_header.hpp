/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2015
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_DETAIL_MINIMAL_LESS_EQUAL_HEADER_HPP
#define BOOST_INTRUSIVE_DETAIL_MINIMAL_LESS_EQUAL_HEADER_HPP
#
#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif
#
#//Try to avoid including <functional>, as it's quite big in C++11
#if defined(BOOST_GNU_STDLIB)
#  include <bits/stl_function.h>
#else
#  include <functional>    //Fallback
#endif
#
#endif //BOOST_INTRUSIVE_DETAIL_MINIMAL_LESS_EQUAL_HEADER_HPP

/* minimal_less_equal_header.hpp
aS4FMFJfkkRD6LlXnGNW7+eVGF6/eZIi9qgsd0310je7ib5p0wajoJ1LT0TuW5RLFt9j/E/zOdVrlwMWU9MZL39pMcUABY6Wt4e8yA80vr0PecAEGWsiY77PPIu8QZMZ3FUU3umofRWV0YuTp/6s9kEeay447KujQ2MtYqESfj1VxOr4ig1wyAp9xFZJnljRwdyqNIBTEt8+ruYZTO+83REnXEvClvsLUda2a6p/aFk2wiy7
*/