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
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
*/