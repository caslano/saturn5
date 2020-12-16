//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
//
// Parts of the pthread code come from Boost Threads code:
//
//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2001-2003
// William E. Kempf
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation.  William E. Kempf makes no representations
// about the suitability of this software for any purpose.
// It is provided "as is" without express or implied warranty.
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_SPIN_RECURSIVE_MUTEX_HPP
#define BOOST_INTERPROCESS_DETAIL_SPIN_RECURSIVE_MUTEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/detail/os_thread_functions.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/atomic.hpp>
#include <boost/cstdint.hpp>
#include <boost/interprocess/detail/os_thread_functions.hpp>
#include <boost/interprocess/sync/spin/mutex.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

class spin_recursive_mutex
{
   spin_recursive_mutex(const spin_recursive_mutex &);
   spin_recursive_mutex &operator=(const spin_recursive_mutex &);
   public:

   spin_recursive_mutex();
   ~spin_recursive_mutex();

   void lock();
   bool try_lock();
   bool timed_lock(const boost::posix_time::ptime &abs_time);
   void unlock();
   void take_ownership();
   private:
   spin_mutex     m_mutex;
   unsigned int   m_nLockCount;
   volatile ipcdetail::OS_systemwide_thread_id_t   m_nOwner;
   volatile boost::uint32_t m_s;
};

inline spin_recursive_mutex::spin_recursive_mutex()
   : m_nLockCount(0), m_nOwner(ipcdetail::get_invalid_systemwide_thread_id()){}

inline spin_recursive_mutex::~spin_recursive_mutex(){}

inline void spin_recursive_mutex::lock()
{
   typedef ipcdetail::OS_systemwide_thread_id_t handle_t;
   const handle_t thr_id(ipcdetail::get_current_systemwide_thread_id());
   handle_t old_id;
   ipcdetail::systemwide_thread_id_copy(m_nOwner, old_id);
   if(ipcdetail::equal_systemwide_thread_id(thr_id , old_id)){
      if((unsigned int)(m_nLockCount+1) == 0){
         //Overflow, throw an exception
         throw interprocess_exception("boost::interprocess::spin_recursive_mutex recursive lock overflow");
      }
      ++m_nLockCount;
   }
   else{
      m_mutex.lock();
      ipcdetail::systemwide_thread_id_copy(thr_id, m_nOwner);
      m_nLockCount = 1;
   }
}

inline bool spin_recursive_mutex::try_lock()
{
   typedef ipcdetail::OS_systemwide_thread_id_t handle_t;
   handle_t thr_id(ipcdetail::get_current_systemwide_thread_id());
   handle_t old_id;
   ipcdetail::systemwide_thread_id_copy(m_nOwner, old_id);
   if(ipcdetail::equal_systemwide_thread_id(thr_id , old_id)) {  // we own it
      if((unsigned int)(m_nLockCount+1) == 0){
         //Overflow, throw an exception
         throw interprocess_exception("boost::interprocess::spin_recursive_mutex recursive lock overflow");
      }
      ++m_nLockCount;
      return true;
   }
   if(m_mutex.try_lock()){
      ipcdetail::systemwide_thread_id_copy(thr_id, m_nOwner);
      m_nLockCount = 1;
      return true;
   }
   return false;
}

inline bool spin_recursive_mutex::timed_lock(const boost::posix_time::ptime &abs_time)
{
   typedef ipcdetail::OS_systemwide_thread_id_t handle_t;
   const handle_t thr_id(ipcdetail::get_current_systemwide_thread_id());
   handle_t old_id;
   ipcdetail::systemwide_thread_id_copy(m_nOwner, old_id);
   if(ipcdetail::equal_systemwide_thread_id(thr_id , old_id)) {  // we own it
      if((unsigned int)(m_nLockCount+1) == 0){
         //Overflow, throw an exception
         throw interprocess_exception("boost::interprocess::spin_recursive_mutex recursive lock overflow");
      }
      ++m_nLockCount;
      return true;
   }
   //m_mutex supports abs_time so no need to check it
   if(m_mutex.timed_lock(abs_time)){
      ipcdetail::systemwide_thread_id_copy(thr_id, m_nOwner);
      m_nLockCount = 1;
      return true;
   }
   return false;
}

inline void spin_recursive_mutex::unlock()
{
   typedef ipcdetail::OS_systemwide_thread_id_t handle_t;
   handle_t old_id;
   ipcdetail::systemwide_thread_id_copy(m_nOwner, old_id);
   const handle_t thr_id(ipcdetail::get_current_systemwide_thread_id());
   (void)old_id;
   (void)thr_id;
   BOOST_ASSERT(ipcdetail::equal_systemwide_thread_id(thr_id, old_id));
   --m_nLockCount;
   if(!m_nLockCount){
      const handle_t new_id(ipcdetail::get_invalid_systemwide_thread_id());
      ipcdetail::systemwide_thread_id_copy(new_id, m_nOwner);
      m_mutex.unlock();
   }
}

inline void spin_recursive_mutex::take_ownership()
{
   typedef ipcdetail::OS_systemwide_thread_id_t handle_t;
   this->m_nLockCount = 1;
   const handle_t thr_id(ipcdetail::get_current_systemwide_thread_id());
   ipcdetail::systemwide_thread_id_copy(thr_id, m_nOwner);
}

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_SPIN_RECURSIVE_MUTEX_HPP

/* recursive_mutex.hpp
Ms8+R3naPsc+Y6/L+RW0NoC8ehtgvTvK+RLu9zIOWRbfBgaA9u5sn5GH33raQDkEbU6jDWROc9sAea5Ii9rABLcNkOfjNNrAkFgbuAbH30fqtIERPWYDhyzzbwPReW0UY+qPZKGlSLcNhh2oNlA7s6pBounH9L22r5HP9ksKda5HUmfYayU8tsxz7RXkTS5WvVcbUR/2UZ+jje9Taedy/j4H6Q4z9oqrjfDCHhnTRgsD9bPw7mOs57XejNLuz3JlbYuqWTX6eU3lxXiijrTYMvDGnwMnPSbjjvuIniL7qYZpixv1hk4yaItbZI5WbXEUjkeQOm1xR40t2jik3cAzAWmtHP/+8NG+gU6wLzpxYJDQdse8JE4Xcg4bv+/eadrkY1Z/iTXGXosaEtvmY12zL8pmryugfHPOpWxtTtnUObMh8bhp64ZsUTs3MvVjuUORbf+ag2dWJzmWkS/uWO7zeJx1lLrYnkRjeWFYP5ZLH3e20XssbwLeOGMZZaljOS5ODbzJj2Xwxh3L83FeHctLsB8dyyH0bVlYP5bNwjcLJzeWTaWXZffEWBadaMeyeg8bIf5gBFIvpLWRDkHdHXZ/cRgLZAhXsCTsknosQNtvN9u+QjTWV/9wKmRT/JmTWl8q3pgajptvoZR/Lcpf+oQlvwx1ip9QduSzZG+E3Mujsoche07PyL4uZV9E2aMF9EdqGYA+ccpeUy1y13jLjTz+xnONIs8I+kQ393fjuG4ZDJk65cFgMCcm/Zg9W3jWMXrrxyzKsDGNrWj3uP7R8VBgj4fEOt1Br1Pbnq9gzkJmGIR0D9rQ3tmG6nVnVsQ8l0Xt+S7w6J9VmZfzwued802ddr5x8OYkmG/Ia7X/SB/PwJBXnoGjYx5yYR9y2WMeVD/m5+GX6xpY1/H7UJ7RifefuW61Q0dJPM8jr9Xun3OJj9PriLx2u5t9tBsyxLQbdRHvFotnWJ6tj/lW/ORfE/OtI0cf8630ye7HfCt90l/Mt9Inu44bSTbmWxTH9Uauu92DoecyfbsBGUmuzZIf/xiLMD6u6cmuY0Yghws/gfpiMCPfgS5I8cIx9Jx/vd6P3huHocdPeOESvP3x66abx5tfGPfbM6sOPP2micsWnH7lGRt540X0eAgvvIV/HINf/IceP+GFh/CPz9DjHvzjSK4fbh7v1xaeN33ld7b49r5Rd+TP2n5Gz+IhypSYbS2M07Yx/2b8Nv4t11/xeR6GtAv/XguJvrx8Rwv9Ir3i8OUdpvouky9dw1es8JWRr1+c8mYgVZLvIPJZa0XRF16uGfTtPgm0gL7wY0GPBd0T9HjQGTw/E/QE0HrQE0EP5PFvpBy+wwKZx/pWQGp0rOm0PzECtaxvFuhg0EOIOYgQC9AAWgHaBNpAX/6DyYdkzCFW42DQ4+W47eu+kHKM1Pi670459mBMu8msd0/QlYg9WBt0CmPZTQItlX27nR0s/1xNO9dj+esTu7IBy90IdHXGvNuQMe82J2ZkC2JKakG3IBalDPQMnj+TMfHO4T6xHXzOxxyrwXZcSTmuIlbgatBsYj5yQK8BzZN9u7w2lpenKe9ilncJy1tArMhlLPdS0Fzusx/wbOzdDxUsr5L9MJX9MI36qmY/1LAfqkBLuc9+wHOmdz+MFhZibkC3Y7nbsx92YD/syH7Yjf2wE/uhnP2wK/thN/bDePYD9i3MRgflGKHBbIC3WWTkY8F80CLQ80CHcX9V7q8NeoFVLp+hQIdryj2V5Z7Gcls4jk4HXYn7q3B/LdAzFaxGhOVmabAaq1Jvq7Hc1W158OzhjU1Zk/Ksxddaw0HlXQDoCowdiSRYq1E8bsVQZLmFCeZHg5ixgrh8SOQ=
*/