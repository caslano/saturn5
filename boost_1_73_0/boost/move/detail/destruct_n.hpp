//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef BOOST_MOVE_DETAIL_DESTRUCT_N_HPP
#define BOOST_MOVE_DETAIL_DESTRUCT_N_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <cstddef>

namespace boost {
namespace movelib{

template<class T, class RandItUninit>
class destruct_n
{
   public:
   explicit destruct_n(RandItUninit raw)
      : m_ptr(raw), m_size()
   {}

   void incr()
   {
      ++m_size;
   }

   void incr(std::size_t n)
   {
      m_size += n;
   }

   void release()
   {
      m_size = 0u;
   }

   ~destruct_n()
   {
      while(m_size--){
         m_ptr[m_size].~T();
      }
   }
   private:
   RandItUninit m_ptr;
   std::size_t m_size;
};

}} //namespace boost {  namespace movelib{

#endif //#ifndef BOOST_MOVE_DETAIL_DESTRUCT_N_HPP

/* destruct_n.hpp
lNSTd+a4sx5U5ZxzsLYelM3RvtHYzz1v/N4c/6GG9+YZhr0Mw9UZtp1rLrlN915D2XY2DdbOI5XhE0PUYQ50yRPDs61/H3Z7bGz8qDv69Y0aGh81YthtwwfdxHm71H2HY/hSrZ6zmq/fppU5OV4pd3IuevIG25Z2fir7A2ftnpyL7qCe7ahn7fdeyszh3X9M02JbrhL9+07k3QEHhziei/myLsqYRwQdKbhr/cObGUXtI76L
*/