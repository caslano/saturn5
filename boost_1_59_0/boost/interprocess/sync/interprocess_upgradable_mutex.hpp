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

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to obtain exclusive ownership of the mutex,
   //!   and if another thread has exclusive, sharable or upgradable ownership of
   //!   the mutex, it waits until it can obtain the ownership.
   //!Throws: interprocess_exception on error.
   //! 
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown.
   void lock();

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to acquire exclusive ownership of the mutex
   //!   without waiting. If no other thread has exclusive, sharable or upgradable
   //!   ownership of the mutex this succeeds.
   //!Returns: If it can acquire exclusive ownership immediately returns true.
   //!   If it has to wait, returns false.
   //!Throws: interprocess_exception on error.
   //! 
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown.
   bool try_lock();

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to acquire exclusive ownership of the mutex
   //!   waiting if necessary until no other thread has exclusive, sharable or
   //!   upgradable ownership of the mutex or abs_time is reached.
   //!Returns: If acquires exclusive ownership, returns true. Otherwise returns false.
   //!Throws: interprocess_exception on error.
   //! 
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown.
   template<class TimePoint>
   bool timed_lock(const TimePoint &abs_time);

   //!Same as `timed_lock`, but this function is modeled after the
   //!standard library interface.
   template<class TimePoint> bool try_lock_until(const TimePoint &abs_time)
   {  return this->timed_lock(abs_time);  }

   //!Same as `timed_lock`, but this function is modeled after the
   //!standard library interface.
   template<class Duration>  bool try_lock_for(const Duration &dur)
   {  return this->timed_lock(ipcdetail::duration_to_ustime(dur)); }


   //!Precondition: The thread must have exclusive ownership of the mutex.
   //!Effects: The calling thread releases the exclusive ownership of the mutex.
   //!Throws: An exception derived from interprocess_exception on error.
   void unlock();

   //Sharable locking

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to obtain sharable ownership of the mutex,
   //!   and if another thread has exclusive ownership of the mutex,
   //!   waits until it can obtain the ownership.
   //!Throws: interprocess_exception on error.
   //! 
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown.
   void lock_sharable();

   //!Same as `lock_sharable` but with a std-compatible interface
   //! 
   void lock_shared()
   {  this->lock_sharable();  }

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to acquire sharable ownership of the mutex
   //!   without waiting. If no other thread has exclusive ownership
   //!   of the mutex this succeeds.
   //!Returns: If it can acquire sharable ownership immediately returns true. If it
   //!   has to wait, returns false.
   //!Throws: interprocess_exception on error.
   //! 
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown.
   bool try_lock_sharable();

   //!Same as `try_lock_sharable` but with a std-compatible interface
   //! 
   bool try_lock_shared()
   {  return this->try_lock_sharable();  }

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to acquire sharable ownership of the mutex
   //!   waiting if necessary until no other thread has exclusive
   //!   ownership of the mutex or abs_time is reached.
   //!Returns: If acquires sharable ownership, returns true. Otherwise returns false.
   //!Throws: interprocess_exception on error.
   //! 
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown.
   template<class TimePoint>
   bool timed_lock_sharable(const TimePoint &abs_time);

   //!Same as `timed_lock_sharable`, but this function is modeled after the
   //!standard library interface.
   template<class TimePoint> bool try_lock_shared_until(const TimePoint &abs_time)
   {  return this->timed_lock_sharable(abs_time);  }

   //!Same as `timed_lock_sharable`, but this function is modeled after the
   //!standard library interface.
   template<class Duration>  bool try_lock_shared_for(const Duration &dur)
   {  return this->timed_lock_sharable(ipcdetail::duration_to_ustime(dur)); }

   //!Precondition: The thread must have sharable ownership of the mutex.
   //!Effects: The calling thread releases the sharable ownership of the mutex.
   //!Throws: An exception derived from interprocess_exception on error.
   void unlock_sharable();

   //!Same as `unlock_sharable` but with a std-compatible interface
   //! 
   void unlock_shared()
   {  this->unlock_sharable();  }

   //Upgradable locking

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to obtain upgradable ownership of the mutex,
   //!   and if another thread has exclusive or upgradable ownership of the mutex,
   //!   waits until it can obtain the ownership.
   //!Throws: interprocess_exception on error.
   //!
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown.
   void lock_upgradable();

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to acquire upgradable ownership of the mutex
   //!   without waiting. If no other thread has exclusive or upgradable ownership
   //!   of the mutex this succeeds.
   //!Returns: If it can acquire upgradable ownership immediately returns true.
   //!   If it has to wait, returns false.
   //!Throws: interprocess_exception on error.
   //!
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown.
   bool try_lock_upgradable();

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to acquire upgradable ownership of the mutex
   //!   waiting if necessary until no other thread has exclusive or upgradable
   //!   ownership of the mutex or abs_time is reached.
   //!Returns: If acquires upgradable ownership, returns true. Otherwise returns false.
   //!Throws: interprocess_exception on error.
   //!
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown.
   template<class TimePoint>
   bool timed_lock_upgradable(const TimePoint &abs_time);

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
   template<class TimePoint>
   bool timed_unlock_upgradable_and_lock(const TimePoint &abs_time);

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

template<class TimePoint>
bool interprocess_upgradable_mutex::timed_lock(const TimePoint &abs_time)
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

template<class TimePoint>
bool interprocess_upgradable_mutex::timed_lock_upgradable(const TimePoint &abs_time)
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

template<class TimePoint>
inline bool interprocess_upgradable_mutex::timed_lock_sharable(const TimePoint &abs_time)
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

template<class TimePoint>
bool interprocess_upgradable_mutex::timed_unlock_upgradable_and_lock(const TimePoint &abs_time)
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