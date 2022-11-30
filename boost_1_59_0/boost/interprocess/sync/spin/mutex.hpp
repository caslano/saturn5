//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_SPIN_MUTEX_HPP
#define BOOST_INTERPROCESS_DETAIL_SPIN_MUTEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/assert.hpp>
#include <boost/interprocess/detail/atomic.hpp>
#include <boost/cstdint.hpp>
#include <boost/interprocess/detail/os_thread_functions.hpp>
#include <boost/interprocess/sync/detail/common_algorithms.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

class spin_mutex
{
   spin_mutex(const spin_mutex &);
   spin_mutex &operator=(const spin_mutex &);
   public:

   spin_mutex();
   ~spin_mutex();

   void lock();
   bool try_lock();
   template<class TimePoint>
   bool timed_lock(const TimePoint &abs_time);

   template<class TimePoint> bool try_lock_until(const TimePoint &abs_time)
   {  return this->timed_lock(abs_time);  }

   template<class Duration>  bool try_lock_for(const Duration &dur)
   {  return this->timed_lock(duration_to_ustime(dur)); }

   void unlock();
   void take_ownership(){}
   private:
   volatile boost::uint32_t m_s;

   struct common_lock_wrapper
   {
      common_lock_wrapper(spin_mutex &sp)
         : m_sp(sp)
      {}

      void lock()
      {
         ipcdetail::try_based_lock(m_sp);
      }

      template<class TimePoint>
      bool timed_lock(const TimePoint &abs_time)
      {  return m_sp.timed_lock(abs_time);   }

      spin_mutex &m_sp;
   };
};

inline spin_mutex::spin_mutex()
   : m_s(0)
{
   //Note that this class is initialized to zero.
   //So zeroed memory can be interpreted as an
   //initialized mutex
}

inline spin_mutex::~spin_mutex()
{
   //Trivial destructor
}

inline void spin_mutex::lock(void)
{
   common_lock_wrapper clw(*this);
   ipcdetail::timeout_when_locking_aware_lock(clw);
}

inline bool spin_mutex::try_lock(void)
{
   boost::uint32_t prev_s = ipcdetail::atomic_cas32(const_cast<boost::uint32_t*>(&m_s), 1, 0);
   return m_s == 1 && prev_s == 0;
}

template<class TimePoint>
inline bool spin_mutex::timed_lock(const TimePoint &abs_time)
{  return ipcdetail::try_based_timed_lock(*this, abs_time); }

inline void spin_mutex::unlock(void)
{  ipcdetail::atomic_cas32(const_cast<boost::uint32_t*>(&m_s), 0, 1);   }

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_SPIN_MUTEX_HPP

/* mutex.hpp
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
*/