//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_ADDRESSOF_HPP
#define BOOST_CONTAINER_DETAIL_ADDRESSOF_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <cstddef>

namespace boost {
namespace container {
namespace dtl {

template <typename T>
BOOST_CONTAINER_FORCEINLINE T* addressof(T& obj)
{
   return static_cast<T*>(
      static_cast<void*>(
         const_cast<char*>(
            &reinterpret_cast<const volatile char&>(obj)
   )));
}

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_ADDRESSOF_HPP

/* addressof.hpp
rr8ze5dxHQ0EGtT1DrN3JWjXj4FAg7reZbCL5V7+1LjqBgEN6tquXXya6em9x1u7GgUBDep6j8Gux35dsta4OgcBDep6n9m7mmvX0CCgQV07GOwaf8FriXGVBgEN6trJ4BhuuvnEtgDtWhgENKhrF0Nd26/3NK43g4AGdf2D2buCtOtfQUCDunYz2NVw8fZZxlUdBDSo6wMGu8aWh5/rql2RwUCDuvYw2FVn3fWOxtU1GGhQ14fMvh3mmL0yGGg=
*/