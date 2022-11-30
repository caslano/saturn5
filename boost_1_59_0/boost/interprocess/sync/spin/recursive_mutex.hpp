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
   template<class TimePoint>
   bool timed_lock(const TimePoint &abs_time);

   template<class TimePoint> bool try_lock_until(const TimePoint &abs_time)
   {  return this->timed_lock(abs_time);  }

   template<class Duration>  bool try_lock_for(const Duration &dur)
   {  return this->timed_lock(duration_to_ustime(dur)); }

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

template<class TimePoint>
inline bool spin_recursive_mutex::timed_lock(const TimePoint &abs_time)
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
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
*/