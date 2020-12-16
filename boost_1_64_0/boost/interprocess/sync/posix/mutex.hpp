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
jqldAdb7jz4UI+bb/DypeQ22sda/YWrgtf4LHPZ9EJuTxEZI+UyZCHIfxPdxgdeWw22d90HAX9s+CM2pThfPflUYa7cP4slmgdNmktO+D+J9Mf+pTJta7YOwzSuLdbb0PvjcqFtw5Qkd1Pwsv4xWUOzxri+4Kp7eQ15A/WL8LqTsmDzlXggpS+/3VwrVGHMu7hO6F2HRl0hBMO93PSruh7MZ51uS2WXxK5/uxYl9veRXo6DPVBHhTkAc5VwJ23FcrO9sWIg9P2+AwXNUlY4yP6+LDZif4bZW+fkSa36Gv7b8vCVEnZ/L96vCWLv8vKea/Nw11J6fPxDnBinT5vTy8/18Vt9JOG4D7gO34Fkr+Vm2QrjYQ+/hGS5XDP13H5L8QszeFqj1yfO7kW7H0DzmdsxjfkH3PtbNs8nIHG+ec/DWb8L8dzbjFKljwhyp/DbwHLlGIIb3CY0vm2BdI/ApyWzQB+slqnUGMqzynCrz+5l1zPf7eZDMcfS8BZTqosLMyze+3R2In9+9Mca9/biXaD7DU1o4rmgGQgsBqb/yIwrLR/qlugP6hOppCnk8TOr5qyT5x/UEjKhfT2kMe5FmHO5UzMH2DEVeQmLtFOdvXIjzN+Ki0qPaRJ0TdXlopDsR6ya4LMA7orlM4z0cJL8LzDN33qD3sgvv91Oau23BflcZfpcv8/M8LtTtTAzo/zDyrzCg/zyPDb/ponyeoQV7PoX3O3+G6y1hDjfNY8x5XOQZmGWegT29wwVkz++W7ff72o8x1zzxd9wz0l7GDcZLzT6u/LaokIMI5btlgettuK97ObdMUW+vjgzQntmvDmdRWc3PM8q50dWUc+lR9nLuY5Q9ucr0oYq71uXchVzOrWbJV53Q2wM+CX6CZ3nUz5qaV5BfMrmk6DrjXL0V3vcxuZTPEnoO734pub3HaZQrS8ic4eyuLXIYemU/Jbt8xzR8vcb6jjd+F3Z5GlbB02kxSfyNbiXZfk4XZrNma3v0BY7X1PXccdlWwCci/B9XpGwrkKxSb2iiSBO6V+js67TqIb/GLOvyKZxhZntg/ElhbinPdzO/E1lePUZ+OpwO5KIIXLSmCDYnyK9U2NWDf1weol1QnD+D1tpsRnpS/LF67XXHZItMPskY5aWP26ISsl9D9lIe9uTnDl8/+bsit/I8Orp/AZtR65zi8h3uV1vcS7f5dG+l5V6sea+4sHR8obmWbhVkfNxxuk6gtGjOZiNtwm1xjuZ0WUz3H9b84kj3d8j7dGZrBr6pTvigKml9TQ93RJJsG6yIZR2sLDcKcl/Tmp4EZwxK5sioIaEh7pAwIZPKMksh842Q0S9yhzjdzlAsALrBHRKJX0pdrUYY1sDdt8Kdo9gdEqrZ9bWyXKUhFzUmoIyrHochdM4+Q6bKTyYDMruETP05L8hy0VemvyETPefJQDIeyHxH4ZnzgCETF+srsxQy3wuZenNuNWQa+Mmsrsfxipzzs4yXr/7Y3bHea48g12fDgqzPjDa3KJcSqFySbe7fqE6iMoHsNpv1FH9vvnWXabdGyvE35FP3kR3qPcrXVI/I/C6fI/1UureW/6Pq2+vHfeKcaPyylsmW2pG+4Zj4gHUj3NZ9bz/8tdWN2+oH2NvvVzeaNWMt+gDJ1dSNPWPtdeMPSbC3pw3XjLXvAxjtlPvjvDcm4CL3uH7Es0Z7nzUMY0E8ECT+ySsqwaGlCC+VR1m0bl7cU/dr4UfQdZVVdn8SrcMmYVUbnWXNPiHetHl2QBndG6y1Ev1bSBvl1F7IvarQ0+wK0J9F3LhtF/jbcoMirAkcVmu67kpgPWW4onBNxPUzZKvU6ept0GvBpWtVLdK1qhbpasjyeXM=
*/