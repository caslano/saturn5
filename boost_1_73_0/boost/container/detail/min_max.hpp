//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_MIN_MAX_HPP
#define BOOST_CONTAINER_DETAIL_MIN_MAX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace container {
namespace dtl {

template<class T>
const T &max_value(const T &a, const T &b)
{  return a > b ? a : b;   }

template<class T>
const T &min_value(const T &a, const T &b)
{  return a < b ? a : b;   }

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_MIN_MAX_HPP

/* min_max.hpp
+8+p+C0Jdz7vJz99vPVzlCd94dS8DOv8J3Ciem+m43E1afVzT6dV2tS0NO6NUjk43ZtUqrwf1BGY2gp93eAXFX6D2Ly1VJXvvu7nKivo41XrGNazXbGyXQn4VD2Uz1ZfeT4vUZXH8UW09/Euvz+oT2vpj1boXs88ObF0f0zKKemRq/dJC5Um6Wp9Qp7X7pNeKryCU5+Q9trt206F1xabmv2b29fThinShhejvNtwuWT6mbTh
*/