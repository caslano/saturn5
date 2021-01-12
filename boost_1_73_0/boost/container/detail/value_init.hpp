//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_VALUE_INIT_HPP
#define BOOST_CONTAINER_DETAIL_VALUE_INIT_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

namespace boost {
namespace container {
namespace dtl {

template<class T>
struct value_init
{
   value_init()
      : m_t()
   {}

   operator T &() { return m_t; }

   T &get() { return m_t; }

   T m_t;
};

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //#ifndef BOOST_CONTAINER_DETAIL_VALUE_INIT_HPP

/* value_init.hpp
THxvp2lfy9bi+5PN10p82f0tX3Px9bb5ksQ3xZa2qfga2uI1EV+E5WvRRnynbrZ8Zrm7bb6W4huVZvlaiI/jB+0z67feltas32M2n1m/O20+s34jLV9zs37tbD6zLhVsPrPcC/0sn9nO21Isn1mX1TafWZfHx1o+sy5Flq+ZWZexNp/Zb4N6Wz6z/fra4pl1Lk6xfGb7tbalNbejis1nbkeOLW2SWYbNZ27HDTafuR3f36R9
*/