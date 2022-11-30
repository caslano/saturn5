//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2012-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_SYNC_DETAIL_COMMON_ALGORITHMS_HPP
#define BOOST_INTERPROCESS_SYNC_DETAIL_COMMON_ALGORITHMS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/sync/spin/wait.hpp>
#include <boost/interprocess/detail/timed_utils.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

template<class MutexType, class TimePoint>
bool try_based_timed_lock(MutexType &m, const TimePoint &abs_time)
{
   //Same as lock()
   if(is_pos_infinity(abs_time)){
      m.lock();
      return true;
   }
   //Always try to lock to achieve POSIX guarantees:
   // "Under no circumstance shall the function fail with a timeout if the mutex
   //  can be locked immediately. The validity of the abs_timeout parameter need not
   //  be checked if the mutex can be locked immediately."
   else if(m.try_lock()){
      return true;
   }
   else{
      spin_wait swait;
      while(microsec_clock<TimePoint>::universal_time() < abs_time){
         if(m.try_lock()){
            return true;
         }
         swait.yield();
      }
      return false;
   }
}

template<class MutexType>
void try_based_lock(MutexType &m)
{
   if(!m.try_lock()){
      spin_wait swait;
      do{
         if(m.try_lock()){
            break;
         }
         else{
            swait.yield();
         }
      }
      while(1);
   }
}

template<class MutexType>
void timeout_when_locking_aware_lock(MutexType &m)
{
   #ifdef BOOST_INTERPROCESS_ENABLE_TIMEOUT_WHEN_LOCKING
      if (!m.timed_lock(microsec_clock<ustime>::universal_time()
           + usduration_milliseconds(BOOST_INTERPROCESS_TIMEOUT_WHEN_LOCKING_DURATION_MS)))
      {
         throw interprocess_exception(timeout_when_locking_error
                                     , "Interprocess mutex timeout when locking. Possible deadlock: "
                                       "owner died without unlocking?");
      }
   #else
      m.lock();
   #endif
}

}  //namespace ipcdetail
}  //namespace interprocess
}  //namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_SYNC_DETAIL_COMMON_ALGORITHMS_HPP

/* common_algorithms.hpp
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
*/