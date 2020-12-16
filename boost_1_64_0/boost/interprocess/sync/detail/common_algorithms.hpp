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
DewHzAYOA+bweDoPOB04HzgbmMvjVhKwBHgWcAWwHXADsD1wK7AL8E5gVx6fUoB/AXYDvgIcCDwKHAQ8DhwGPAkcDkSatRHAVsCRwFTgWOA4YD9gLnAS8ArgNOAqoOBHBfAC2J8GzgG+AMwV8QHHAd8CTgC+DRwF/Ao4GqgLtd4iPuBgYAdgd2AGMBU4F9gDuBDYAbgS2AlYAews+AycDNwHnAJ8Dthf5A94ruA7MErEB3QB94drdeoQL/8O+j0wScuAWQ97NnA1THYV9LDsrluX0I7dUp9QlZ9OoX27fx29Qod2B9YttGOs8zevX+j47tB1DEVWId1VwesaSqsKXhf5sKrg9A15qqTOobVV9dM7tK2qYXQP7a06Nf1DB6qkDqJjVaHpIfLXQXSyKjg9RO49weki2jfW+T+nj2jAnrp1EmXu8dVLtGhPaLqJDiPfJ2FaYzE6AGY2zGqYSpgjMGFYlKbAZMJ4YMphdsDshzkK48aiNB1mNkwZzHaYF2FOwLSfiD4UpgBmLcwumIMwNTDuTKeWCjMD5hKY9TB7YQ7DaJPgF2YUTAFMOcwumIMw38DETYbfyad1Jp3++///++Xk/xeUkvj/esr/FzL3n4nVzLcqcdwMD4k5OONaTKIzU+kux8jhE4ZPHjwua8Lg8cOzPMWQJ6B450B3LoCX9xB+Rpl37OPI/jH23e5Xy4hPlXd/3qQ7Rwvp3Vl/vrsyjb6/rnfF/2Ewc2CWw9wK8xjMUZgzdSGBNV27FvgAjFL/eKq8y5xMd0c8psyYDErj7di3dGirYFgWKO7dBzZVfvYnY+Tvp4OSh+YCiPcFvKePuxTv9qDf7cdN6NFPY7f+0i3NcHNLt16G2+eppltPw+016dbDcHtYuqVqfIdjk+nWj+wrTHs62ReZ9r6Kdwbyfocov3guP+ubtnIWnEj7aIyV4o465b0sB3fWrHVM1gUO35Bd/xLRv6CPQOh/hMnFAeBWPVxVrzhsXXX3TVU/QK+6+6Z+P2ANu1TjOptVeqknz5vWBMELovkrpLSn4Aw6Cje0wnDm10j5vsAat/jId+m0toaMYfr+pd5WcARmN8x1uo47XA56+xNnhAHOFuhJZtjs7n+HEbI651M6WlrS0VLSmvzXuCzbcjs5SN/36fHodQZiY3QVzGws/jbpEeQnjUobHZTlLtmZvUg+A/YH4vFeZBblvQz/no314msWnd374fZcrLQ/j98vwHSB6crus2PrfgtjtK3SNNm2vupl1OGevc32Ybr16Gu47ZBuJt0c6dbDaDPxvXzbTFaaXbYheGh7i6O6G+Wy342S7z5k3SLaOPN9DtURcmtp0lLZ+tzdTWO9Eu10bz1vC9wlZPn1prY3v8hzaVbe4px8nKXY6n4il2F7ov0B4UN+EkIfqj2ganMIU9afdUZfXqJqb5JWtqHFRUvxsEBTtjnfsDtTzgoXW+8szqHvzZC6SPO+ZAG53aOt1sLN+4n9yC0StfYDv3ou5aanEE1z3F+MwnjTFWeYjXz18nN7uITotqB9R7CbEX4jtMwPKfyrKa2sv4LDX0M0XS1yo6gEzLeCXeh7S70l/r/MMkXXow+9Eoyb6ZXLeacr0q35y+/sD3sT2HfD3hPhToTJhJkE8yL8vQTzMgzaHr7J9pQSVJsKj+nWx17HZb2V48A6cqOy931rJsvYp44ejvZG9DlMI97DrhK6T/rIOppfUrIkr9hWR80xfCPRfqSNg0yv59QyAxGeqn7Kd+Vf0PfJWju42Oqswj/qAmZk8o3aIfq+SBth6jqBXMi+wi0DpiP5+5RyzDJGuO4+R/6amLJvhpOfeL/6Kem/JXqfOml+20Pf3GYdfY/sWeg=
*/