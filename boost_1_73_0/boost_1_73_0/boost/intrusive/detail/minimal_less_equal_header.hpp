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
ZVbZHsARasfTJvbNIlYT+aLZr83n6awPDOBR/lgmPVA1oS7J5bN+lZn7OlQPJxBmWJU7IAb5/Ym9yC55etQPhLe8Glbok0gTJJgHZAiSsjGgm2dyVDFEgDG/FD9PYaYUWyWm8yfgtmddGCyNeALgBm2L9fLYyqT1mNviM/JiTzZPEqUSG6Co8wU463Djf8u3MT8vRukkxmBM6ZAt54+Q+Gl7KnGe3CO0BjfAz1v0EwaI3m8ng9IAgkpG0ulV9Iw=
*/