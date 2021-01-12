/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2015
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_MINIMAL_CHAR_TRAITS_HEADER_HPP
#define BOOST_CONTAINER_DETAIL_MINIMAL_CHAR_TRAITS_HEADER_HPP
#
#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif
#
#//Try to avoid including <string>, as it's quite big
#if defined(_MSC_VER) && defined(BOOST_DINKUMWARE_STDLIB)
   #include <iosfwd>   //Dinkum libraries for MSVC define std::char_traits there
#elif defined(BOOST_GNU_STDLIB)
   #include <bits/char_traits.h>
#else
   #include <string>  //Fallback
#endif

#endif //BOOST_CONTAINER_DETAIL_MINIMAL_CHAR_TRAITS_HEADER_HPP

/* minimal_char_traits_header.hpp
DtNge7E7it0DZsDeEr+PhI8S/xjxp4l/mviLxC9r5srcwZzksGbuPVK/+6QdHpT+mAtrwnmwA5wPb4QLYHdYDANdnmsP//p1gmSUjeT8nXN3fc7O+br3uXoMcjo/n4KudU5e+nycc3F9/p2HipDz+bbzuXbEaa7HoGQ07XTZ+XTZ53/v8x89/89Mzc/4N53/7+a7paUcX7X2ke8PpO6TQXnsj6fzrPNRVXZKtn4GrII+DrbO
*/