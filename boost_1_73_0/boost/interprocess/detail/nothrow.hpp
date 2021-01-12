//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTERPROCESS_DETAIL_NOTHROW_HPP
#define BOOST_INTERPROCESS_DETAIL_NOTHROW_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace std {   //no namespace versioning in clang+libc++

struct nothrow_t;

}  //namespace std {

namespace boost{ namespace interprocess {

template <int Dummy = 0>
struct nothrow
{
   static const std::nothrow_t &get()   {  return *pnothrow;  }
   static std::nothrow_t *pnothrow;
};

template <int Dummy>
std::nothrow_t *nothrow<Dummy>::pnothrow =
   reinterpret_cast<std::nothrow_t *>(0x1234);  //Avoid sanitizer warnings on references to null

}}  //namespace boost{ namespace interprocess {

#endif //#ifndef BOOST_INTERPROCESS_DETAIL_NOTHROW_HPP

/* nothrow.hpp
648fGGpfvGtR3B4aC7Ne7s6qiVtb9nlLf0mJ7Gue1Vj8gitR/kKZpuNLT+kG1VW9vssVGY7fcEQ26LU/BKxxhvsLOMM9Y1pD++fcune+OJscYcXIM06jjHoX/9uPMTWJvgbw+o6Ha8hD/kS5WUao6WP5baUwXvJEOhOikg5jnPp+Mp1JbjWSJRLjiIQJu29OOmKlctGKJ5KFX2/W5k9yByN+SNSC8OohckzP2iG4VM0oshP/
*/