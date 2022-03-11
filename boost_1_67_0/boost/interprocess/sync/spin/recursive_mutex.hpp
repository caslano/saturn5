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
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
*/