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

#ifndef BOOST_INTERPROCESS_DETAIL_POSIX_RECURSIVE_MUTEX_HPP
#define BOOST_INTERPROCESS_DETAIL_POSIX_RECURSIVE_MUTEX_HPP

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
#include <boost/interprocess/sync/posix/pthread_helpers.hpp>
#include <boost/interprocess/sync/posix/timepoint_to_timespec.hpp>
#include <boost/interprocess/detail/timed_utils.hpp>
#include <boost/interprocess/exceptions.hpp>
#ifndef BOOST_INTERPROCESS_POSIX_TIMEOUTS
#  include <boost/interprocess/detail/os_thread_functions.hpp>
#  include <boost/interprocess/sync/detail/common_algorithms.hpp>
#endif
#include <boost/assert.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

class posix_recursive_mutex
{
   posix_recursive_mutex(const posix_recursive_mutex &);
   posix_recursive_mutex &operator=(const posix_recursive_mutex &);
   public:

   posix_recursive_mutex();
   ~posix_recursive_mutex();

   void lock();
   bool try_lock();
   template<class TimePoint> bool timed_lock(const TimePoint &abs_time);
   void unlock();

   private:
   pthread_mutex_t   m_mut;
};

inline posix_recursive_mutex::posix_recursive_mutex()
{
   mutexattr_wrapper mut_attr(true);
   mutex_initializer mut(m_mut, mut_attr);
   mut.release();
}

inline posix_recursive_mutex::~posix_recursive_mutex()
{
   int res = pthread_mutex_destroy(&m_mut);
   BOOST_ASSERT(res == 0);(void)res;
}

inline void posix_recursive_mutex::lock()
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

inline bool posix_recursive_mutex::try_lock()
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
   return (res == 0);
}

template<class TimePoint>
inline bool posix_recursive_mutex::timed_lock(const TimePoint &abs_time)
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

inline void posix_recursive_mutex::unlock()
{
   int res = 0;
   res = pthread_mutex_unlock(&m_mut);
   BOOST_ASSERT(res == 0); (void)res;
}

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_POSIX_RECURSIVE_MUTEX_HPP

/* recursive_mutex.hpp
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
*/