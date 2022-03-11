////////////////////////////////////////////////////////////////////////////////
//
//  Code based on Howard Hinnant's upgrade_mutex class
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_UPGRADABLE_MUTEX_HPP
#define BOOST_INTERPROCESS_UPGRADABLE_MUTEX_HPP

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
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <climits>


//!\file
//!Describes interprocess_upgradable_mutex class

namespace boost {
namespace interprocess {

//!Wraps a interprocess_upgradable_mutex that can be placed in shared memory and can be
//!shared between processes. Allows timed lock tries
class interprocess_upgradable_mutex
{
   //Non-copyable
   interprocess_upgradable_mutex(const interprocess_upgradable_mutex &);
   interprocess_upgradable_mutex &operator=(const interprocess_upgradable_mutex &);

   friend class interprocess_condition;
   public:

   //!Constructs the upgradable lock.
   //!Throws interprocess_exception on error.
   interprocess_upgradable_mutex();

   //!Destroys the upgradable lock.
   //!Does not throw.
   ~interprocess_upgradable_mutex();

   //Exclusive locking

   //!Effects: The calling thread tries to obtain exclusive ownership of the mutex,
   //!   and if another thread has exclusive, sharable or upgradable ownership of
   //!   the mutex, it waits until it can obtain the ownership.
   //!Throws: interprocess_exception on error.
   void lock();

   //!Effects: The calling thread tries to acquire exclusive ownership of the mutex
   //!   without waiting. If no other thread has exclusive, sharable or upgradable
   //!   ownership of the mutex this succeeds.
   //!Returns: If it can acquire exclusive ownership immediately returns true.
   //!   If it has to wait, returns false.
   //!Throws: interprocess_exception on error.
   bool try_lock();

   //!Effects: The calling thread tries to acquire exclusive ownership of the mutex
   //!   waiting if necessary until no other thread has exclusive, sharable or
   //!   upgradable ownership of the mutex or abs_time is reached.
   //!Returns: If acquires exclusive ownership, returns true. Otherwise returns false.
   //!Throws: interprocess_exception on error.
   bool timed_lock(const boost::posix_time::ptime &abs_time);

   //!Precondition: The thread must have exclusive ownership of the mutex.
   //!Effects: The calling thread releases the exclusive ownership of the mutex.
   //!Throws: An exception derived from interprocess_exception on error.
   void unlock();

   //Sharable locking

   //!Effects: The calling thread tries to obtain sharable ownership of the mutex,
   //!   and if another thread has exclusive ownership of the mutex,
   //!   waits until it can obtain the ownership.
   //!Throws: interprocess_exception on error.
   void lock_sharable();

   //!Effects: The calling thread tries to acquire sharable ownership of the mutex
   //!   without waiting. If no other thread has exclusive ownership
   //!   of the mutex this succeeds.
   //!Returns: If it can acquire sharable ownership immediately returns true. If it
   //!   has to wait, returns false.
   //!Throws: interprocess_exception on error.
   bool try_lock_sharable();

   //!Effects: The calling thread tries to acquire sharable ownership of the mutex
   //!   waiting if necessary until no other thread has exclusive
   //!   ownership of the mutex or abs_time is reached.
   //!Returns: If acquires sharable ownership, returns true. Otherwise returns false.
   //!Throws: interprocess_exception on error.
   bool timed_lock_sharable(const boost::posix_time::ptime &abs_time);

   //!Precondition: The thread must have sharable ownership of the mutex.
   //!Effects: The calling thread releases the sharable ownership of the mutex.
   //!Throws: An exception derived from interprocess_exception on error.
   void unlock_sharable();

   //Upgradable locking

   //!Effects: The calling thread tries to obtain upgradable ownership of the mutex,
   //!   and if another thread has exclusive or upgradable ownership of the mutex,
   //!   waits until it can obtain the ownership.
   //!Throws: interprocess_exception on error.
   void lock_upgradable();

   //!Effects: The calling thread tries to acquire upgradable ownership of the mutex
   //!   without waiting. If no other thread has exclusive or upgradable ownership
   //!   of the mutex this succeeds.
   //!Returns: If it can acquire upgradable ownership immediately returns true.
   //!   If it has to wait, returns false.
   //!Throws: interprocess_exception on error.
   bool try_lock_upgradable();

   //!Effects: The calling thread tries to acquire upgradable ownership of the mutex
   //!   waiting if necessary until no other thread has exclusive or upgradable
   //!   ownership of the mutex or abs_time is reached.
   //!Returns: If acquires upgradable ownership, returns true. Otherwise returns false.
   //!Throws: interprocess_exception on error.
   bool timed_lock_upgradable(const boost::posix_time::ptime &abs_time);

   //!Precondition: The thread must have upgradable ownership of the mutex.
   //!Effects: The calling thread releases the upgradable ownership of the mutex.
   //!Throws: An exception derived from interprocess_exception on error.
   void unlock_upgradable();

   //Demotions

   //!Precondition: The thread must have exclusive ownership of the mutex.
   //!Effects: The thread atomically releases exclusive ownership and acquires
   //!   upgradable ownership. This operation is non-blocking.
   //!Throws: An exception derived from interprocess_exception on error.
   void unlock_and_lock_upgradable();

   //!Precondition: The thread must have exclusive ownership of the mutex.
   //!Effects: The thread atomically releases exclusive ownership and acquires
   //!   sharable ownership. This operation is non-blocking.
   //!Throws: An exception derived from interprocess_exception on error.
   void unlock_and_lock_sharable();

   //!Precondition: The thread must have upgradable ownership of the mutex.
   //!Effects: The thread atomically releases upgradable ownership and acquires
   //!   sharable ownership. This operation is non-blocking.
   //!Throws: An exception derived from interprocess_exception on error.
   void unlock_upgradable_and_lock_sharable();

   //Promotions

   //!Precondition: The thread must have upgradable ownership of the mutex.
   //!Effects: The thread atomically releases upgradable ownership and acquires
   //!   exclusive ownership. This operation will block until all threads with
   //!   sharable ownership release their sharable lock.
   //!Throws: An exception derived from interprocess_exception on error.
   void unlock_upgradable_and_lock();

   //!Precondition: The thread must have upgradable ownership of the mutex.
   //!Effects: The thread atomically releases upgradable ownership and tries to
   //!   acquire exclusive ownership. This operation will fail if there are threads
   //!   with sharable ownership, but it will maintain upgradable ownership.
   //!Returns: If acquires exclusive ownership, returns true. Otherwise returns false.
   //!Throws: An exception derived from interprocess_exception on error.
   bool try_unlock_upgradable_and_lock();

   //!Precondition: The thread must have upgradable ownership of the mutex.
   //!Effects: The thread atomically releases upgradable ownership and tries to acquire
   //!   exclusive ownership, waiting if necessary until abs_time. This operation will
   //!   fail if there are threads with sharable ownership or timeout reaches, but it
   //!   will maintain upgradable ownership.
   //!Returns: If acquires exclusive ownership, returns true. Otherwise returns false.
   //!Throws: An exception derived from interprocess_exception on error. */
   bool timed_unlock_upgradable_and_lock(const boost::posix_time::ptime &abs_time);

   //!Precondition: The thread must have sharable ownership of the mutex.
   //!Effects: The thread atomically releases sharable ownership and tries to acquire
   //!   exclusive ownership. This operation will fail if there are threads with sharable
   //!   or upgradable ownership, but it will maintain sharable ownership.
   //!Returns: If acquires exclusive ownership, returns true. Otherwise returns false.
   //!Throws: An exception derived from interprocess_exception on error.
   bool try_unlock_sharable_and_lock();

   //!Precondition: The thread must have sharable ownership of the mutex.
   //!Effects: The thread atomically releases sharable ownership and tries to acquire
   //!   upgradable ownership. This operation will fail if there are threads with sharable
   //!   or upgradable ownership, but it will maintain sharable ownership.
   //!Returns: If acquires upgradable ownership, returns true. Otherwise returns false.
   //!Throws: An exception derived from interprocess_exception on error.
   bool try_unlock_sharable_and_lock_upgradable();

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   typedef scoped_lock<interprocess_mutex> scoped_lock_t;

   //Pack all the control data in a word to be able
   //to use atomic instructions in the future
   struct control_word_t
   {
      unsigned exclusive_in         : 1;
      unsigned upgradable_in        : 1;
      unsigned num_upr_shar         : sizeof(unsigned)*CHAR_BIT-2;
   }                       m_ctrl;

   interprocess_mutex      m_mut;
   interprocess_condition  m_first_gate;
   interprocess_condition  m_second_gate;

   private:
   //Rollback structures for exceptions or failure return values
   struct exclusive_rollback
   {
      exclusive_rollback(control_word_t         &ctrl
                        ,interprocess_condition &first_gate)
         :  mp_ctrl(&ctrl), m_first_gate(first_gate)
      {}

      void release()
      {  mp_ctrl = 0;   }

      ~exclusive_rollback()
      {
         if(mp_ctrl){
            mp_ctrl->exclusive_in = 0;
            m_first_gate.notify_all();
         }
      }
      control_word_t          *mp_ctrl;
      interprocess_condition  &m_first_gate;
   };

   struct upgradable_to_exclusive_rollback
   {
      upgradable_to_exclusive_rollback(control_word_t         &ctrl)
         :  mp_ctrl(&ctrl)
      {}

      void release()
      {  mp_ctrl = 0;   }

      ~upgradable_to_exclusive_rollback()
      {
         if(mp_ctrl){
            //Recover upgradable lock
            mp_ctrl->upgradable_in = 1;
            ++mp_ctrl->num_upr_shar;
            //Execute the second half of exclusive locking
            mp_ctrl->exclusive_in = 0;
         }
      }
      control_word_t          *mp_ctrl;
   };

   template<int Dummy>
   struct base_constants_t
   {
      static const unsigned max_readers
         = ~(unsigned(3) << (sizeof(unsigned)*CHAR_BIT-2));
   };
   typedef base_constants_t<0> constants;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

template <int Dummy>
const unsigned interprocess_upgradable_mutex::base_constants_t<Dummy>::max_readers;

inline interprocess_upgradable_mutex::interprocess_upgradable_mutex()
{
   this->m_ctrl.exclusive_in  = 0;
   this->m_ctrl.upgradable_in = 0;
   this->m_ctrl.num_upr_shar   = 0;
}

inline interprocess_upgradable_mutex::~interprocess_upgradable_mutex()
{}

inline void interprocess_upgradable_mutex::lock()
{
   scoped_lock_t lck(m_mut);

   //The exclusive lock must block in the first gate
   //if an exclusive or upgradable lock has been acquired
   while (this->m_ctrl.exclusive_in || this->m_ctrl.upgradable_in){
      this->m_first_gate.wait(lck);
   }

   //Mark that exclusive lock has been acquired
   this->m_ctrl.exclusive_in = 1;

   //Prepare rollback
   exclusive_rollback rollback(this->m_ctrl, this->m_first_gate);

   //Now wait until all readers are gone
   while (this->m_ctrl.num_upr_shar){
      this->m_second_gate.wait(lck);
   }
   rollback.release();
}

inline bool interprocess_upgradable_mutex::try_lock()
{
   scoped_lock_t lck(m_mut, try_to_lock);

   //If we can't lock or any has there is any exclusive, upgradable
   //or sharable mark return false;
   if(!lck.owns()
      || this->m_ctrl.exclusive_in
      || this->m_ctrl.num_upr_shar){
      return false;
   }
   this->m_ctrl.exclusive_in = 1;
   return true;
}

inline bool interprocess_upgradable_mutex::timed_lock
   (const boost::posix_time::ptime &abs_time)
{
   //Mutexes and condvars handle just fine infinite abs_times
   //so avoid checking it here
   scoped_lock_t lck(m_mut, abs_time);
   if(!lck.owns())   return false;

   //The exclusive lock must block in the first gate
   //if an exclusive or upgradable lock has been acquired
   while (this->m_ctrl.exclusive_in || this->m_ctrl.upgradable_in){
      if(!this->m_first_gate.timed_wait(lck, abs_time)){
         if(this->m_ctrl.exclusive_in || this->m_ctrl.upgradable_in){
            return false;
         }
         break;
      }
   }

   //Mark that exclusive lock has been acquired
   this->m_ctrl.exclusive_in = 1;

   //Prepare rollback
   exclusive_rollback rollback(this->m_ctrl, this->m_first_gate);

   //Now wait until all readers are gone
   while (this->m_ctrl.num_upr_shar){
      if(!this->m_second_gate.timed_wait(lck, abs_time)){
         if(this->m_ctrl.num_upr_shar){
            return false;
         }
         break;
      }
   }
   rollback.release();
   return true;
}

inline void interprocess_upgradable_mutex::unlock()
{
   scoped_lock_t lck(m_mut);
   this->m_ctrl.exclusive_in = 0;
   this->m_first_gate.notify_all();
}

//Upgradable locking

inline void interprocess_upgradable_mutex::lock_upgradable()
{
   scoped_lock_t lck(m_mut);

   //The upgradable lock must block in the first gate
   //if an exclusive or upgradable lock has been acquired
   //or there are too many sharable locks
   while(this->m_ctrl.exclusive_in || this->m_ctrl.upgradable_in
         || this->m_ctrl.num_upr_shar == constants::max_readers){
      this->m_first_gate.wait(lck);
   }

   //Mark that upgradable lock has been acquired
   //And add upgradable to the sharable count
   this->m_ctrl.upgradable_in = 1;
   ++this->m_ctrl.num_upr_shar;
}

inline bool interprocess_upgradable_mutex::try_lock_upgradable()
{
   scoped_lock_t lck(m_mut, try_to_lock);

   //The upgradable lock must fail
   //if an exclusive or upgradable lock has been acquired
   //or there are too many sharable locks
   if(!lck.owns()
      || this->m_ctrl.exclusive_in
      || this->m_ctrl.upgradable_in
      || this->m_ctrl.num_upr_shar == constants::max_readers){
      return false;
   }

   //Mark that upgradable lock has been acquired
   //And add upgradable to the sharable count
   this->m_ctrl.upgradable_in = 1;
   ++this->m_ctrl.num_upr_shar;
   return true;
}

inline bool interprocess_upgradable_mutex::timed_lock_upgradable
   (const boost::posix_time::ptime &abs_time)
{
   //Mutexes and condvars handle just fine infinite abs_times
   //so avoid checking it here
   scoped_lock_t lck(m_mut, abs_time);
   if(!lck.owns())   return false;

   //The upgradable lock must block in the first gate
   //if an exclusive or upgradable lock has been acquired
   //or there are too many sharable locks
   while(this->m_ctrl.exclusive_in
         || this->m_ctrl.upgradable_in
         || this->m_ctrl.num_upr_shar == constants::max_readers){
      if(!this->m_first_gate.timed_wait(lck, abs_time)){
         if((this->m_ctrl.exclusive_in
             || this->m_ctrl.upgradable_in
             || this->m_ctrl.num_upr_shar == constants::max_readers)){
            return false;
         }
         break;
      }
   }

   //Mark that upgradable lock has been acquired
   //And add upgradable to the sharable count
   this->m_ctrl.upgradable_in = 1;
   ++this->m_ctrl.num_upr_shar;
   return true;
}

inline void interprocess_upgradable_mutex::unlock_upgradable()
{
   scoped_lock_t lck(m_mut);
   //Mark that upgradable lock has been acquired
   //And add upgradable to the sharable count
   this->m_ctrl.upgradable_in = 0;
   --this->m_ctrl.num_upr_shar;
   this->m_first_gate.notify_all();
}

//Sharable locking

inline void interprocess_upgradable_mutex::lock_sharable()
{
   scoped_lock_t lck(m_mut);

   //The sharable lock must block in the first gate
   //if an exclusive lock has been acquired
   //or there are too many sharable locks
   while(this->m_ctrl.exclusive_in
        || this->m_ctrl.num_upr_shar == constants::max_readers){
      this->m_first_gate.wait(lck);
   }

   //Increment sharable count
   ++this->m_ctrl.num_upr_shar;
}

inline bool interprocess_upgradable_mutex::try_lock_sharable()
{
   scoped_lock_t lck(m_mut, try_to_lock);

   //The sharable lock must fail
   //if an exclusive lock has been acquired
   //or there are too many sharable locks
   if(!lck.owns()
      || this->m_ctrl.exclusive_in
      || this->m_ctrl.num_upr_shar == constants::max_readers){
      return false;
   }

   //Increment sharable count
   ++this->m_ctrl.num_upr_shar;
   return true;
}

inline bool interprocess_upgradable_mutex::timed_lock_sharable
   (const boost::posix_time::ptime &abs_time)
{
   //Mutexes and condvars handle just fine infinite abs_times
   //so avoid checking it here
   scoped_lock_t lck(m_mut, abs_time);
   if(!lck.owns())   return false;

   //The sharable lock must block in the first gate
   //if an exclusive lock has been acquired
   //or there are too many sharable locks
   while (this->m_ctrl.exclusive_in
         || this->m_ctrl.num_upr_shar == constants::max_readers){
      if(!this->m_first_gate.timed_wait(lck, abs_time)){
         if(this->m_ctrl.exclusive_in
            || this->m_ctrl.num_upr_shar == constants::max_readers){
            return false;
         }
         break;
      }
   }

   //Increment sharable count
   ++this->m_ctrl.num_upr_shar;
   return true;
}

inline void interprocess_upgradable_mutex::unlock_sharable()
{
   scoped_lock_t lck(m_mut);
   //Decrement sharable count
   --this->m_ctrl.num_upr_shar;
   if (this->m_ctrl.num_upr_shar == 0){
      this->m_second_gate.notify_one();
   }
   //Check if there are blocked sharables because of
   //there were too many sharables
   else if(this->m_ctrl.num_upr_shar == (constants::max_readers-1)){
      this->m_first_gate.notify_all();
   }
}

//Downgrading

inline void interprocess_upgradable_mutex::unlock_and_lock_upgradable()
{
   scoped_lock_t lck(m_mut);
   //Unmark it as exclusive
   this->m_ctrl.exclusive_in     = 0;
   //Mark it as upgradable
   this->m_ctrl.upgradable_in    = 1;
   //The sharable count should be 0 so increment it
   this->m_ctrl.num_upr_shar   = 1;
   //Notify readers that they can enter
   m_first_gate.notify_all();
}

inline void interprocess_upgradable_mutex::unlock_and_lock_sharable()
{
   scoped_lock_t lck(m_mut);
   //Unmark it as exclusive
   this->m_ctrl.exclusive_in   = 0;
   //The sharable count should be 0 so increment it
   this->m_ctrl.num_upr_shar   = 1;
   //Notify readers that they can enter
   m_first_gate.notify_all();
}

inline void interprocess_upgradable_mutex::unlock_upgradable_and_lock_sharable()
{
   scoped_lock_t lck(m_mut);
   //Unmark it as upgradable (we don't have to decrement count)
   this->m_ctrl.upgradable_in    = 0;
   //Notify readers/upgradable that they can enter
   m_first_gate.notify_all();
}

//Upgrading

inline void interprocess_upgradable_mutex::unlock_upgradable_and_lock()
{
   scoped_lock_t lck(m_mut);
   //Simulate unlock_upgradable() without
   //notifying sharables.
   this->m_ctrl.upgradable_in = 0;
   --this->m_ctrl.num_upr_shar;
   //Execute the second half of exclusive locking
   this->m_ctrl.exclusive_in = 1;

   //Prepare rollback
   upgradable_to_exclusive_rollback rollback(m_ctrl);

   while (this->m_ctrl.num_upr_shar){
      this->m_second_gate.wait(lck);
   }
   rollback.release();
}

inline bool interprocess_upgradable_mutex::try_unlock_upgradable_and_lock()
{
   scoped_lock_t lck(m_mut, try_to_lock);
   //Check if there are no readers
   if(!lck.owns()
      || this->m_ctrl.num_upr_shar != 1){
      return false;
   }
   //Now unlock upgradable and mark exclusive
   this->m_ctrl.upgradable_in = 0;
   --this->m_ctrl.num_upr_shar;
   this->m_ctrl.exclusive_in = 1;
   return true;
}

inline bool interprocess_upgradable_mutex::timed_unlock_upgradable_and_lock
   (const boost::posix_time::ptime &abs_time)
{
   //Mutexes and condvars handle just fine infinite abs_times
   //so avoid checking it here
   scoped_lock_t lck(m_mut, abs_time);
   if(!lck.owns())   return false;

   //Simulate unlock_upgradable() without
   //notifying sharables.
   this->m_ctrl.upgradable_in = 0;
   --this->m_ctrl.num_upr_shar;
   //Execute the second half of exclusive locking
   this->m_ctrl.exclusive_in = 1;

   //Prepare rollback
   upgradable_to_exclusive_rollback rollback(m_ctrl);

   while (this->m_ctrl.num_upr_shar){
      if(!this->m_second_gate.timed_wait(lck, abs_time)){
         if(this->m_ctrl.num_upr_shar){
            return false;
         }
         break;
      }
   }
   rollback.release();
   return true;
}

inline bool interprocess_upgradable_mutex::try_unlock_sharable_and_lock()
{
   scoped_lock_t lck(m_mut, try_to_lock);

   //If we can't lock or any has there is any exclusive, upgradable
   //or sharable mark return false;
   if(!lck.owns()
      || this->m_ctrl.exclusive_in
      || this->m_ctrl.upgradable_in
      || this->m_ctrl.num_upr_shar != 1){
      return false;
   }
   this->m_ctrl.exclusive_in = 1;
   this->m_ctrl.num_upr_shar = 0;
   return true;
}

inline bool interprocess_upgradable_mutex::try_unlock_sharable_and_lock_upgradable()
{
   scoped_lock_t lck(m_mut, try_to_lock);

   //The upgradable lock must fail
   //if an exclusive or upgradable lock has been acquired
   if(!lck.owns()
      || this->m_ctrl.exclusive_in
      || this->m_ctrl.upgradable_in){
      return false;
   }

   //Mark that upgradable lock has been acquired
   this->m_ctrl.upgradable_in = 1;
   return true;
}

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {


#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_UPGRADABLE_MUTEX_HPP

/* interprocess_upgradable_mutex.hpp
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
*/