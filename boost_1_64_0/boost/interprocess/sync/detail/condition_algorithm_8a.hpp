//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_CONDITION_ALGORITHM_8A_HPP
#define BOOST_INTERPROCESS_DETAIL_CONDITION_ALGORITHM_8A_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/detail/locks.hpp>
#include <limits>

namespace boost {
namespace interprocess {
namespace ipcdetail {

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//
// Condition variable algorithm taken from pthreads-win32 discussion.
//
// The algorithm was developed by Alexander Terekhov in colaboration with
// Louis Thomas.
//
//     Algorithm 8a / IMPL_SEM,UNBLOCK_STRATEGY == UNBLOCK_ALL
//
// semBlockLock - bin.semaphore
// semBlockQueue - semaphore
// mtxExternal - mutex or CS
// mtxUnblockLock - mutex or CS
// nWaitersGone - int
// nWaitersBlocked - int
// nWaitersToUnblock - int
//
// wait( timeout ) {
//
//   [auto: register int result          ]     // error checking omitted
//   [auto: register int nSignalsWasLeft ]
//   [auto: register int nWaitersWasGone ]
//
//   sem_wait( semBlockLock );
//   nWaitersBlocked++;
//   sem_post( semBlockLock );
//
//   unlock( mtxExternal );
//   bTimedOut = sem_wait( semBlockQueue,timeout );
//
//   lock( mtxUnblockLock );
//   if ( 0 != (nSignalsWasLeft = nWaitersToUnblock) ) {
//     if ( bTimedOut ) {                       // timeout (or canceled)
//       if ( 0 != nWaitersBlocked ) {
//         nWaitersBlocked--;
//       }
//       else {
//         nWaitersGone++;                     // count spurious wakeups.
//       }
//     }
//     if ( 0 == --nWaitersToUnblock ) {
//       if ( 0 != nWaitersBlocked ) {
//         sem_post( semBlockLock );           // open the gate.
//         nSignalsWasLeft = 0;                // do not open the gate
//                                             // below again.
//       }
//       else if ( 0 != (nWaitersWasGone = nWaitersGone) ) {
//         nWaitersGone = 0;
//       }
//     }
//   }
//   else if ( INT_MAX/2 == ++nWaitersGone ) { // timeout/canceled or
//                                             // spurious semaphore :-)
//     sem_wait( semBlockLock );
//     nWaitersBlocked -= nWaitersGone;     // something is going on here
//                                          //  - test of timeouts? :-)
//     sem_post( semBlockLock );
//     nWaitersGone = 0;
//   }
//   unlock( mtxUnblockLock );
//
//   if ( 1 == nSignalsWasLeft ) {
//     if ( 0 != nWaitersWasGone ) {
//       // sem_adjust( semBlockQueue,-nWaitersWasGone );
//       while ( nWaitersWasGone-- ) {
//         sem_wait( semBlockQueue );       // better now than spurious later
//       }
//     } sem_post( semBlockLock );          // open the gate
//   }
//
//   lock( mtxExternal );
//
//   return ( bTimedOut ) ? ETIMEOUT : 0;
// }
//
// signal(bAll) {
//
//   [auto: register int result         ]
//   [auto: register int nSignalsToIssue]
//
//   lock( mtxUnblockLock );
//
//   if ( 0 != nWaitersToUnblock ) {        // the gate is closed!!!
//     if ( 0 == nWaitersBlocked ) {        // NO-OP
//       return unlock( mtxUnblockLock );
//     }
//     if (bAll) {
//       nWaitersToUnblock += nSignalsToIssue=nWaitersBlocked;
//       nWaitersBlocked = 0;
//     }
//     else {
//       nSignalsToIssue = 1;
//       nWaitersToUnblock++;
//       nWaitersBlocked--;
//     }
//   }
//   else if ( nWaitersBlocked > nWaitersGone ) { // HARMLESS RACE CONDITION!
//     sem_wait( semBlockLock );                  // close the gate
//     if ( 0 != nWaitersGone ) {
//       nWaitersBlocked -= nWaitersGone;
//       nWaitersGone = 0;
//     }
//     if (bAll) {
//       nSignalsToIssue = nWaitersToUnblock = nWaitersBlocked;
//       nWaitersBlocked = 0;
//     }
//     else {
//       nSignalsToIssue = nWaitersToUnblock = 1;
//       nWaitersBlocked--;
//     }
//   }
//   else { // NO-OP
//     return unlock( mtxUnblockLock );
//   }
//
//   unlock( mtxUnblockLock );
//   sem_post( semBlockQueue,nSignalsToIssue );
//   return result;
// }
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


// Required interface for ConditionMembers
// class ConditionMembers
// {
//    typedef implementation_defined semaphore_type;
//    typedef implementation_defined mutex_type;
//    typedef implementation_defined integer_type;
//
//    integer_type    &get_nwaiters_blocked()
//    integer_type    &get_nwaiters_gone()
//    integer_type    &get_nwaiters_to_unblock()
//    semaphore_type  &get_sem_block_queue()
//    semaphore_type  &get_sem_block_lock()
//    mutex_type      &get_mtx_unblock_lock()
// };
//
// Must be initialized as following
//
//    get_nwaiters_blocked() == 0
//    get_nwaiters_gone() == 0
//    get_nwaiters_to_unblock() == 0
//    get_sem_block_queue() == initial count 0
//    get_sem_block_lock() == initial count 1
//    get_mtx_unblock_lock() (unlocked)
//
template<class ConditionMembers>
class condition_algorithm_8a
{
   private:
   condition_algorithm_8a();
   ~condition_algorithm_8a();
   condition_algorithm_8a(const condition_algorithm_8a &);
   condition_algorithm_8a &operator=(const condition_algorithm_8a &);

   typedef typename ConditionMembers::semaphore_type  semaphore_type;
   typedef typename ConditionMembers::mutex_type      mutex_type;
   typedef typename ConditionMembers::integer_type    integer_type;

   public:
   template<class Lock>
   static bool wait  ( ConditionMembers &data, Lock &lock
                     , bool timeout_enabled, const boost::posix_time::ptime &abs_time);
   static void signal(ConditionMembers &data, bool broadcast);
};

template<class ConditionMembers>
inline void condition_algorithm_8a<ConditionMembers>::signal(ConditionMembers &data, bool broadcast)
{
   integer_type nsignals_to_issue;

   {
      scoped_lock<mutex_type> locker(data.get_mtx_unblock_lock());

      if ( 0 != data.get_nwaiters_to_unblock() ) {        // the gate is closed!!!
         if ( 0 == data.get_nwaiters_blocked() ) {        // NO-OP
            //locker's destructor triggers data.get_mtx_unblock_lock().unlock()
            return;
         }
         if (broadcast) {
            data.get_nwaiters_to_unblock() += nsignals_to_issue = data.get_nwaiters_blocked();
            data.get_nwaiters_blocked() = 0;
         }
         else {
            nsignals_to_issue = 1;
            data.get_nwaiters_to_unblock()++;
            data.get_nwaiters_blocked()--;
         }
      }
      else if ( data.get_nwaiters_blocked() > data.get_nwaiters_gone() ) { // HARMLESS RACE CONDITION!
         data.get_sem_block_lock().wait();                      // close the gate
         if ( 0 != data.get_nwaiters_gone() ) {
            data.get_nwaiters_blocked() -= data.get_nwaiters_gone();
            data.get_nwaiters_gone() = 0;
         }
         if (broadcast) {
            nsignals_to_issue = data.get_nwaiters_to_unblock() = data.get_nwaiters_blocked();
            data.get_nwaiters_blocked() = 0;
         }
         else {
            nsignals_to_issue = data.get_nwaiters_to_unblock() = 1;
            data.get_nwaiters_blocked()--;
         }
      }
      else { // NO-OP
         //locker's destructor triggers data.get_mtx_unblock_lock().unlock()
         return;
      }
      //locker's destructor triggers data.get_mtx_unblock_lock().unlock()
   }
   data.get_sem_block_queue().post(nsignals_to_issue);
}

template<class ConditionMembers>
template<class Lock>
inline bool condition_algorithm_8a<ConditionMembers>::wait
   ( ConditionMembers &data
   , Lock &lock
   , bool tout_enabled
   , const boost::posix_time::ptime &abs_time
   )
{
   //Initialize to avoid warnings
   integer_type nsignals_was_left = 0;
   integer_type nwaiters_was_gone = 0;

   data.get_sem_block_lock().wait();
   ++data.get_nwaiters_blocked();
   data.get_sem_block_lock().post();

   //Unlock external lock and program for relock
   lock_inverter<Lock> inverted_lock(lock);
   scoped_lock<lock_inverter<Lock> >   external_unlock(inverted_lock);

   bool bTimedOut = tout_enabled
      ? !data.get_sem_block_queue().timed_wait(abs_time)
      : (data.get_sem_block_queue().wait(), false);

   {
      scoped_lock<mutex_type> locker(data.get_mtx_unblock_lock());
      if ( 0 != (nsignals_was_left = data.get_nwaiters_to_unblock()) ) {
         if ( bTimedOut ) {                       // timeout (or canceled)
            if ( 0 != data.get_nwaiters_blocked() ) {
               data.get_nwaiters_blocked()--;
            }
            else {
               data.get_nwaiters_gone()++;                     // count spurious wakeups.
            }
         }
         if ( 0 == --data.get_nwaiters_to_unblock() ) {
            if ( 0 != data.get_nwaiters_blocked() ) {
               data.get_sem_block_lock().post();          // open the gate.
               nsignals_was_left = 0;          // do not open the gate below again.
            }
            else if ( 0 != (nwaiters_was_gone = data.get_nwaiters_gone()) ) {
               data.get_nwaiters_gone() = 0;
            }
         }
      }
      else if ( (std::numeric_limits<integer_type>::max)()/2
                == ++data.get_nwaiters_gone() ) { // timeout/canceled or spurious semaphore :-)
         data.get_sem_block_lock().wait();
         data.get_nwaiters_blocked() -= data.get_nwaiters_gone();       // something is going on here - test of timeouts? :-)
         data.get_sem_block_lock().post();
         data.get_nwaiters_gone() = 0;
      }
      //locker's destructor triggers data.get_mtx_unblock_lock().unlock()
   }

   if ( 1 == nsignals_was_left ) {
      if ( 0 != nwaiters_was_gone ) {
         // sem_adjust( data.get_sem_block_queue(),-nwaiters_was_gone );
         while ( nwaiters_was_gone-- ) {
            data.get_sem_block_queue().wait();       // better now than spurious later
         }
      }
      data.get_sem_block_lock().post(); // open the gate
   }

   //lock.lock(); called from unlocker destructor

   return ( bTimedOut ) ? false : true;
}


template<class ConditionMembers>
class condition_8a_wrapper
{
   //Non-copyable
   condition_8a_wrapper(const condition_8a_wrapper &);
   condition_8a_wrapper &operator=(const condition_8a_wrapper &);

   ConditionMembers m_data;
   typedef ipcdetail::condition_algorithm_8a<ConditionMembers> algo_type;

   public:

   condition_8a_wrapper(){}

   //Compiler-generated destructor is OK
   //~condition_8a_wrapper(){}

   ConditionMembers & get_members()
   {  return m_data; }

   const ConditionMembers & get_members() const
   {  return m_data; }

   void notify_one()
   {  algo_type::signal(m_data, false);  }

   void notify_all()
   {  algo_type::signal(m_data, true);  }

   template <typename L>
   void wait(L& lock)
   {
      if (!lock)
         throw lock_exception();
      algo_type::wait(m_data, lock, false, boost::posix_time::ptime());
   }

   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {
      if (!lock)
         throw lock_exception();

      while (!pred())
         algo_type::wait(m_data, lock, false, boost::posix_time::ptime());
   }

   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {
      if (!lock)
         throw lock_exception();
      return algo_type::wait(m_data, lock, true, abs_time);
   }

   template <typename L, typename Pr>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time, Pr pred)
   {
      if (!lock)
            throw lock_exception();
      while (!pred()){
         if (!algo_type::wait(m_data, lock, true, abs_time))
            return pred();
      }
      return true;
   }
};

}  //namespace ipcdetail
}  //namespace interprocess
}  //namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_CONDITION_ALGORITHM_8A_HPP

/* condition_algorithm_8a.hpp
gaOYhtME//zmke0Ouiebjv7iRGPsFyIwlz7RFel06R1ckQ7lnVembxnN9bJxvqyTfjQDQDOO7sUqZLgzTTZoXqF3k2VXGTQnmCYJ9gjY70IYd8Oc4XN/NZj5VnjMoL6h119rPb25iTfAO/gsuQJmp3jPReGW5RZl5eZD0tZiNHbbfFZRH+FPOe6r6h5og5+fmLR8N1+jtwWynj5L329CTXUq5GGxjAWiuVUrUPW5XLdeJprrScKlIcNnCuI7ZhnTR8D+L9inCgxqXhweMzZdNZZymchyso6DynHUWnZXskz524Q7zBYuu/J0o+yKShflUekFVXbwpyo7U470Rvp+o9YcsS2AD2V/kh58mTKt5T20xyyHO+jbaLRw3WzT35FbOI+vPC8roOwwDcojnfUyUZhMU7rYYy3jL4mmv4aZqy1so032jgU/YW6FGR3jndNtDqJN1qdsxR3vWygdkIWUYFlv8D1SKnMUdCfGgyiU7H78Tnmpz3qD8v9NbN3vY+BfuVbtyX3v7+l7nqOt1kubif78QpjLMAu/HmY7dFu9ilnwl9C5dFIfrqwPMnx+U8NtkvSK/PjTTz35rf4qopvr6IgbOxejr/8jzJ9Q056APUlvgTt05WBIsna2I0ZZlzge2/gRJ9p0f3r7QWnYk0h1oiC/0NsnnUQarOvnpjzPWkJ+fjLnWDso/DBHc+19nd5ZUTiLqGbRWxmE0wV1R0xNO4JxB2KleRVmvdtrXooR3/kdgq6am9AwhXz0pzc78Zpuzv2rz5Vz/9Jzjbl6r1SN3Yr6m+sBc708sL99/d2+v32N0KS/fY3wn372NfkH/ezrhoP9fNcNW0x7X/P9BOqi/f2EvZ3I9xNm3x1DZSTKLZ7LDW7E78fIjcrAR07JERbecdCBRDA+Lsa0FGVbmQKSoNsLwlDOt+itFtJUQ9+3ORINvXBkv8cxTb8K55MttGJHc1M/XEZ30rOjHhtT1O0mifur8G7i+zrHYPRZC/QL8WYhAdvtseqxM0W1BpZt3EVhrXaciVXxULTvqTC5aN/LYG6AqUIb/4fm1I/qZeZ864xzvPKZVW/S3qf4HnLM1q/A2Wu8thxtlvQkgT8n6FuFQ8iiEHfpy+OMeVlXCHV16Ss7k7g/9Xsk9rMLfjoIP+Erlxpzqk+Z5gamGYA60AbonBIR5oyFuNWzIiKdjaLPwX+H9z/c4m3YmDAF9vDojpAXm+zsCuqzYDtbiGgNh7TWMJfrLFfTGKcbhAnRHSKiXREtI1q6whpHR0Z3jYh2hsOD2xmOr4hWiFHWQukXfMtbjlnvEt8uRH0erCX41IGZmMdGOkT5k04m8FjVBw7qHnof+F/2zgQ+iiIL490zk3sMIRcQIoQkQIIBIoZTLgVBFCVcyqUhhAAREoYQEBQ1HCIoKCrersZrRRSXVVRUXBFwBUVFREUXJSrKIWhEQOSQ/erN666e6ZpkEtzjt0u0+U9Vv6quqq6uu17tJf81PZHMMs/tgl1rR3ctUDlofVejE7mNHHmRrY1MZwupy8BegcpAD+U7rcZyRbZ31eWKVd9EbgP7PturEO4lXVV7tAuvxa7gSZMgY+a9IPbFWve7nmig3hNe0fX09oRXdK37HuRAe8L3NFTvCV/Z9fT2hK/sGvw+5JVd674POZg94UZclzayx7UAH89aM67WaoPO7eF6oAbdFn7hP1SL8MNvDr9vnnUl2cP6Pd7VFlVYZa6tc55dqXje20jbSuXz5L75HvE16Jc4jTwLv5Vps6yxPaw3JsJvdVg9kz3Bv0vyg8f4GlPchNNx00oKAuiZ8ItfVhB6WOzvXo61imcmyGf65t9ke7wnijzdTR1vKDwJKs5wL9s=
*/