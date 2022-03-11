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
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
*/