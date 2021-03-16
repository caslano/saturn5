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
5II+48ZBf2LPUj+9kAs6jbFLoEP7Tc66RJbEZvmi/7Af+YXWlmkvOqadq2xbjU4D5uy9Ay9Tu8vZEgiSGX0WQkjbz+l7PLqxQA1E2tUeLbVMUtl8GdyezRq0FmT3i2xo3pzuSx70WKVilOSQz/YljwLrB9T0coGkktnsTDK1AE7JGNDSFZLJLyWzmbR2K8Be3I/mnjZmiDFzWk+VSV4vkyJ6AgO/aGTB38mZrK4lOLgvFpxLniEz0DnLmXR5Xjs=
*/