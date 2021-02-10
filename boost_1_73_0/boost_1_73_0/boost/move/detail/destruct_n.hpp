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
BAAAnQoAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNDAwVVQFAAG2SCRgpVZtb9s2EP5OIP/h4DVo4tlmHGTA4igGlFiOvai2IcnJurYTFJmy2MqkK1HJjKL/fUfJb2nSxcH0QRLF5x7eHZ87ylAsU2GQsTYxuIgkPr6wxYNMJ1mb9DxvVNzgyvJIvZ7wuzBPE2LQDcagpRn5BVyW3rO0nvEJI0bK5skCpyeBCkom2mw04fjoCIbXpBMo1gIvzmtwfAp/5Ime+B2aJ62T0xZCrt55pKRrgfawnhUDGgVfGLmUQjGh6jYTUxW34Eh/ESxUXIoWhInMGEG/ypUNuvQEHbxMuLYrHQyLAQJK6jaJlZojfDUEQwQzTMs6bIhkChmfzRMG66SAQUsY0qBT923iurZ/aTme3+3b1nlBWE6AEcrZLBCTcqkWpfu9oev1R619TTcaOh59YPQhEIo2TzAJm5UTOaU6DfpzI0TONRO+LuPA+G5YyqMF6MAhiBRLQcWsyB/EQQZ3jAmoZLFUFWLcF1gkmKdSyVAmbYLxwGMPVtu2R3oyUy144vAeGWO+6uYUXcDUo690/8Zy3P5wsEfMMGRz/Fyl1T2yh65uljIylfJ5xBPMXEYPxq7lmFfWwKvBx8rh
*/