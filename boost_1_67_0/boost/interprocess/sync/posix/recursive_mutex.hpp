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
#include <boost/interprocess/sync/posix/ptime_to_timespec.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
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
   bool timed_lock(const boost::posix_time::ptime &abs_time);
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
   if (pthread_mutex_lock(&m_mut) != 0)
      throw lock_exception();
}

inline bool posix_recursive_mutex::try_lock()
{
   int res = pthread_mutex_trylock(&m_mut);
   if (!(res == 0 || res == EBUSY))
      throw lock_exception();
   return res == 0;
}

inline bool posix_recursive_mutex::timed_lock(const boost::posix_time::ptime &abs_time)
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