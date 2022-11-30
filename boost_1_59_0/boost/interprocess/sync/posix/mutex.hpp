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

#ifndef BOOST_INTERPROCESS_DETAIL_POSIX_MUTEX_HPP
#define BOOST_INTERPROCESS_DETAIL_POSIX_MUTEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <pthread.h>
#include <errno.h>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/sync/posix/timepoint_to_timespec.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/sync/posix/pthread_helpers.hpp>
#include <boost/interprocess/detail/timed_utils.hpp>


#ifndef BOOST_INTERPROCESS_POSIX_TIMEOUTS
#  include <boost/interprocess/detail/os_thread_functions.hpp>
#  include <boost/interprocess/sync/detail/common_algorithms.hpp>
#endif
#include <boost/assert.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

class posix_condition;

class posix_mutex
{
   posix_mutex(const posix_mutex &);
   posix_mutex &operator=(const posix_mutex &);
   public:

   posix_mutex();
   ~posix_mutex();

   void lock();
   bool try_lock();
   template<class TimePoint> bool timed_lock(const TimePoint &abs_time);

   template<class TimePoint> bool try_lock_until(const TimePoint &abs_time)
   {  return this->timed_lock(abs_time);  }

   template<class Duration>  bool try_lock_for(const Duration &dur)
   {  return this->timed_lock(duration_to_ustime(dur)); }

   void unlock();

   friend class posix_condition;

   private:
   pthread_mutex_t   m_mut;
};

inline posix_mutex::posix_mutex()
{
   mutexattr_wrapper mut_attr;
   mutex_initializer mut(m_mut, mut_attr);
   mut.release();
}

inline posix_mutex::~posix_mutex()
{
   int res = pthread_mutex_destroy(&m_mut);
   BOOST_ASSERT(res  == 0);(void)res;
}

inline void posix_mutex::lock()
{
   int res = pthread_mutex_lock(&m_mut);
   #ifdef BOOST_INTERPROCESS_POSIX_ROBUST_MUTEXES
   if (res == EOWNERDEAD)
   {
      //We can't inform the application and data might
      //corrupted, so be safe and mark the mutex as not recoverable
      //so applications can act accordingly.
      pthread_mutex_unlock(&m_mut);
      throw lock_exception(not_recoverable);
   }
   else if (res == ENOTRECOVERABLE)
      throw lock_exception(not_recoverable);
   #endif
   if (res != 0)
      throw lock_exception();
}

inline bool posix_mutex::try_lock()
{
   int res = pthread_mutex_trylock(&m_mut);
   #ifdef BOOST_INTERPROCESS_POSIX_ROBUST_MUTEXES
   if (res == EOWNERDEAD)
   {
      //We can't inform the application and data might
      //corrupted, so be safe and mark the mutex as not recoverable
      //so applications can act accordingly.
      pthread_mutex_unlock(&m_mut);
      throw lock_exception(not_recoverable);
   }
   else if (res == ENOTRECOVERABLE)
      throw lock_exception(not_recoverable);
   #endif
   if (!(res == 0 || res == EBUSY))
      throw lock_exception();
   return res == 0;
}

template<class TimePoint>
inline bool posix_mutex::timed_lock(const TimePoint &abs_time)
{
   #ifdef BOOST_INTERPROCESS_POSIX_TIMEOUTS
   //Posix does not support infinity absolute time so handle it here
   if(ipcdetail::is_pos_infinity(abs_time)){
      this->lock();
      return true;
   }
   timespec ts = timepoint_to_timespec(abs_time);
   int res = pthread_mutex_timedlock(&m_mut, &ts);
   #ifdef BOOST_INTERPROCESS_POSIX_ROBUST_MUTEXES
   if (res == EOWNERDEAD)
   {
      //We can't inform the application and data might
      //corrupted, so be safe and mark the mutex as not recoverable
      //so applications can act accordingly.
      pthread_mutex_unlock(&m_mut);
      throw lock_exception(not_recoverable);
   }
   else if (res == ENOTRECOVERABLE)
      throw lock_exception(not_recoverable);
   #endif
   if (res != 0 && res != ETIMEDOUT)
      throw lock_exception();
   return res == 0;

   #else //BOOST_INTERPROCESS_POSIX_TIMEOUTS

   return ipcdetail::try_based_timed_lock(*this, abs_time);

   #endif   //BOOST_INTERPROCESS_POSIX_TIMEOUTS
}

inline void posix_mutex::unlock()
{
   int res = pthread_mutex_unlock(&m_mut);
   (void)res;
   BOOST_ASSERT(res == 0);
}

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_POSIX_MUTEX_HPP

/* mutex.hpp
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
*/