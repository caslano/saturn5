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
   template<bool TimeoutEnabled, class Lock, class TimePoint>
   static bool wait  ( ConditionMembers &data, Lock &lock, const TimePoint &abs_time)
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

      bool bTimedOut = !do_sem_timed_wait(data.get_sem_block_queue(), abs_time, bool_<TimeoutEnabled>());

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

   static void signal(ConditionMembers &data, bool broadcast)
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

   private:
   template<class TimePoint>
   static bool do_sem_timed_wait(semaphore_type &sem, const TimePoint &abs_time, bool_<true>)
   {  return sem.timed_wait(abs_time); }

   template<class TimePoint>
   static bool do_sem_timed_wait(semaphore_type &sem, const TimePoint &, bool_<false>)
   {  sem.wait();  return true;  }
};

template<class ConditionMembers>
class condition_8a_wrapper
{
   //Non-copyable
   condition_8a_wrapper(const condition_8a_wrapper &);
   condition_8a_wrapper &operator=(const condition_8a_wrapper &);

   ConditionMembers m_data;
   typedef condition_algorithm_8a<ConditionMembers> algo_type;

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
      algo_type::template wait<false>(m_data, lock, 0);
   }

   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {
      if (!lock)
         throw lock_exception();

      while (!pred())
         algo_type::template wait<false>(m_data, lock, 0);
   }

   template <typename L, class TimePoint>
   bool timed_wait(L& lock, const TimePoint &abs_time)
   {
      if (!lock)
         throw lock_exception();
      return algo_type::template wait<true>(m_data, lock, abs_time);
   }

   template <typename L, class TimePoint, typename Pr>
   bool timed_wait(L& lock, const TimePoint &abs_time, Pr pred)
   {
      if (!lock)
            throw lock_exception();
      while (!pred()){
         if (!algo_type::template wait<true>(m_data, lock, abs_time))
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
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
*/