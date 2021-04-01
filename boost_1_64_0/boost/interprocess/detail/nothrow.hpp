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
JA4XZWz7zlmMQ9Q6PMTJrHJMXpOo5QyRhCrCtSI5u+oq1UCO4NAIMMsJvgRDGF30iXb6I+lOtn3hyMM27pqai6PmuYeaRYpj3ChQFIrjQ1uDC1o1w9f1ihmBDkBup9h7DQCYG/Gzl16k3inTKG5w1dPxf/9YQ8AosPaJrrQ9NF/sqg2VJdWKNRNiSICZQJa0Q99tHs4oRgz9XwMelmmIait7UHsNLZyxKPB55kIPHtLWoxn3jZ1Am0YEkeLofP65bPSpxdWKWe5W7l7xIwi8rU35D5isrPW7cRDmwBqTZihN1rXv9Brbm/J+EZxruD52I+UfKcqkMxugQpvNfK8o8XKh5+o6rj4I5GuRi3Rt6ms8ddbPspODa/vOceLl+oBfEjVgb6YT58XQPCbr9IIhmGsO9S9kpURLRs7WAA9dMawzVaSAR4mtgec0rZpi+xEP0hAj5GdkhOYGUK5Ga58v3iLJRMkBntVuPnWvrTdu5qd4vneXmOsJ1YQGrfFUCttU9nHuTxyX/HZxBmWQMwSGYUQU7cToyTck6BERP+8NYRSfN0EzaLIPWpu0zA==
*/