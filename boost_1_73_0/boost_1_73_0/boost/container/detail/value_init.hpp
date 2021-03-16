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
7xLD90RtAl9P/3JizoC6oWvX/CHp8rU9Dv3yT1J+zD+w7L232r+54/jSwAV9n1kzm8a9l/n9Xlu+5qd/n/nKrUuu2bn6paf2yTchxtu2Ph314pAr1v4w9sHobbPy739bvvMl3nb5t0OH5J9Yfuv2KTckHe0euIXmz/w3YxNfLhwzZs+V3S4et2jg5P5C3ML8loNx4xojsn+eMjjulf8Y/MlbQmxj/qILhiU/23f9zh+WvnDb/qavpgnxNfNzXmg=
*/