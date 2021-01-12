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
t7nlfkLr9e5XOXLXpohiPgh1HDJl/xGZQI+oXPUyL3OicBx0yvHkubHlyIbA8t0nlcogmSR++nkPY5LsretWloTrWpZm38o4se/tvdA5+5AUj7N3u8mVJZxj77tcJ25amX1ZO0T/pucKqxHf2k9Fjn2Jfa8n08jOKJnv2PcnnTlaXyGzTqiWkmZvuSyx0ilWeO/KDxLutSwpS5DT/m63PpQ0z0XOd1hmXGlpYW643czBLsOR
*/