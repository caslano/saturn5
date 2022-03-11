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

namespace boost {
namespace interprocess {
namespace ipcdetail {

template<class MutexType>
bool try_based_timed_lock(MutexType &m, const boost::posix_time::ptime &abs_time)
{
   //Same as lock()
   if(abs_time == boost::posix_time::pos_infin){
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
      while(microsec_clock::universal_time() < abs_time){
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
void timed_based_lock(MutexType &m, unsigned const uCheckPeriodSec)
{
   const boost::posix_time::time_duration dur(0, 0, uCheckPeriodSec);
   boost::posix_time::ptime deadline(microsec_clock::universal_time()+dur);
   if(!m.timed_lock(deadline)){
      spin_wait swait;
      do{
         deadline = microsec_clock::universal_time()+dur;
         if(m.timed_lock(deadline)){
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
void timed_based_timed_lock(MutexType &m, const boost::posix_time::ptime &abs_time, unsigned const uCheckPeriodSec)
{
   const boost::posix_time::time_duration dur(0, 0, uCheckPeriodSec);
   boost::posix_time::ptime deadline(microsec_clock::universal_time()+dur);
   if(abs_time <= deadline){
      m.timed_lock(abs_time);
   }
   else if(!m.timed_lock(deadline)){
      spin_wait swait;
      do{
         deadline = microsec_clock::universal_time()+dur;
         if(m.timed_lock(deadline)){
            break;
         }
         else{
            swait.yield();
         }
      }
      while(1);
   }
}

}  //namespace ipcdetail
}  //namespace interprocess
}  //namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_SYNC_DETAIL_COMMON_ALGORITHMS_HPP

/* common_algorithms.hpp
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
*/