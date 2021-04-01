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
D1ir/ac+AL5LmqIhy4CC5NQGyUxxs9yxFGwxiC2UP2KJK/fzT1WP9F1uEIr8KLpLd7hz9axQU1QH4OWMd0ELl+ZL9laBDPOpMk1m4RaZpYZD49vQL3Qg0zonuYRmrDrC1v+VPsT+AEJkgTJqsXILR+FmwaNbDWS+kDYw2F1ttSb9SfyHsbhpnfee9T60xm812Gr4b+UfGHC2dZgSb6sD6ZVz5MLxaKZv9bG2B0SJXVd8nLCTxQ54QYHMdfix+xZ7zIM4ZVU5erTv27bsakVoB5moa5vXJToSX6oGDPrkC+c8H4ubk+dmxDkdHfowTT6GTZK2F7VtzRvkBUA3CmtP9PKrnTY3Ce+KgLvN4ZKcBowP5cO9mJYWh88RhsHjypOr+qAluHPTY3lNkSGUVS1Y/QZCeevHFMSwA81fkH4kvvFp4EB8hw6V7hxScngXvED20B4/xT8WPS77cTV93emPJlCGak1I0LEgTXgUBHEBWhjoGsN/wRURPUti3p0/MCeAS9xuqnhzMtE4MqFuuREfUeJ89i9tfvLJKEXO/YEBQJE6PILlYVrqucEK1w==
*/