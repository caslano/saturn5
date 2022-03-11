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
#include <boost/interprocess/sync/posix/ptime_to_timespec.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/sync/posix/pthread_helpers.hpp>

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
   bool timed_lock(const boost::posix_time::ptime &abs_time);
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
   if (pthread_mutex_lock(&m_mut) != 0)
      throw lock_exception();
}

inline bool posix_mutex::try_lock()
{
   int res = pthread_mutex_trylock(&m_mut);
   if (!(res == 0 || res == EBUSY))
      throw lock_exception();
   return res == 0;
}

inline bool posix_mutex::timed_lock(const boost::posix_time::ptime &abs_time)
{
   #ifdef BOOST_INTERPROCESS_POSIX_TIMEOUTS
   //Posix does not support infinity absolute time so handle it here
   if(abs_time == boost::posix_time::pos_infin){
      this->lock();
      return true;
   }
   timespec ts = ptime_to_timespec(abs_time);
   int res = pthread_mutex_timedlock(&m_mut, &ts);
   if (res != 0 && res != ETIMEDOUT)
      throw lock_exception();
   return res == 0;

   #else //BOOST_INTERPROCESS_POSIX_TIMEOUTS

   return ipcdetail::try_based_timed_lock(*this, abs_time);

   #endif   //BOOST_INTERPROCESS_POSIX_TIMEOUTS
}

inline void posix_mutex::unlock()
{
   int res = 0;
   res = pthread_mutex_unlock(&m_mut);
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