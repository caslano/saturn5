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
1jZXDjhrXsqUGJTuMtnpl08nx1mNclgXnW250neHQPIw3B1b6t8cm2k/dMHW5V5PutiWQ0rykPfgZZbOv2xz3r5/8MZ7b6TSF8ypzs4fK3BdvQ3cJleedbFumPVu5IGDPw+QuDJqVW7mtQOm3m53nn1Unqf09NrjhZ+Hjt83bPwA77GSh3euHjZC+33BdcWupTPdA6sh3LakuPNl+OBREwWchglsd1t9fKTwxV9zXy04MbHw3au8d8p3cwdLCk/b4uBgctXU1eXOlrcOBSIyRgkj5i9ZqF2ZmKNrr1UTE9smFGLh7yL3ecG7x8n2ZjK/bGAHMTrLMhQlwhYdGM+WPCUcMWTfkXcZCuPX7Fv4sGL5utpf5161mtDq80Dv9LKBQ7Ym3r7HKjktEerT+aANHbEXa39ieuxAWu7Oa4e2iEV++Lnlo4eWymbvNLfBHTfGlHluYhzqzOti7l2x58biYxqxWttoxwp1y1x0P4dMusLcRmsxJ7fW2dy9OimRMYPVB9QfujrfYnLd6HJG8NxNKbNuK6pdD9l+gKGf7hJ1b542y22M89vIrjcOe2+70Yc5XvN2uNH22NtF5MDjST9Fh16amzlC92NexXzT127jQhs/ZtmeTCx5v0l5eHT25bp4teVNd2BYZePEN5bs8k3WMnMbP1SkWE1O6hxQ+/OeMDmRVuvOVcf99qx084tLqDb3YMCGP5bnd75jJWo3
*/