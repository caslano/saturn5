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
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
*/