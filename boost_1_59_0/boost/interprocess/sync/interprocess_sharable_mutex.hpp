//////////////////////////////////////////////////////////////////////////////
//  Code based on Howard Hinnant's shared_mutex class
//
// (C) Copyright Howard Hinnant 2007-2010. Distributed under the Boost
// Software License, Version 1.0. (see http://www.boost.org/LICENSE_1_0.txt)
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_SHARABLE_MUTEX_HPP
#define BOOST_INTERPROCESS_SHARABLE_MUTEX_HPP

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
//!Describes interprocess_sharable_mutex class

namespace boost {
namespace interprocess {

//!Wraps a interprocess_sharable_mutex that can be placed in shared memory and can be
//!shared between processes. Allows timed lock tries
class interprocess_sharable_mutex
{
   //Non-copyable
   interprocess_sharable_mutex(const interprocess_sharable_mutex &);
   interprocess_sharable_mutex &operator=(const interprocess_sharable_mutex &);

   friend class interprocess_condition;
   public:

   //!Constructs the sharable lock.
   //!Throws interprocess_exception on error.
   interprocess_sharable_mutex();

   //!Destroys the sharable lock.
   //!Does not throw.
   ~interprocess_sharable_mutex();

   //Exclusive locking

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to obtain exclusive ownership of the mutex,
   //!   and if another thread has exclusive or sharable ownership of
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
   //!   without waiting. If no other thread has exclusive or sharable
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
   //!   waiting if necessary until no other thread has exclusive or sharable
   //!   ownership of the mutex or abs_time is reached.
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

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   typedef scoped_lock<interprocess_mutex> scoped_lock_t;

   //Pack all the control data in a word to be able
   //to use atomic instructions in the future
   struct control_word_t
   {
      unsigned exclusive_in   : 1;
      unsigned num_shared     : sizeof(unsigned)*CHAR_BIT-1;
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

   template<int Dummy>
   struct base_constants_t
   {
      static const unsigned max_readers
         = ~(unsigned(1) << (sizeof(unsigned)*CHAR_BIT-1));
   };
   typedef base_constants_t<0> constants;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

template <int Dummy>
const unsigned interprocess_sharable_mutex::base_constants_t<Dummy>::max_readers;

inline interprocess_sharable_mutex::interprocess_sharable_mutex()
{
   this->m_ctrl.exclusive_in  = 0;
   this->m_ctrl.num_shared   = 0;
}

inline interprocess_sharable_mutex::~interprocess_sharable_mutex()
{}

inline void interprocess_sharable_mutex::lock()
{
   scoped_lock_t lck(m_mut);

   //The exclusive lock must block in the first gate
   //if an exclusive lock has been acquired
   while (this->m_ctrl.exclusive_in){
      this->m_first_gate.wait(lck);
   }

   //Mark that exclusive lock has been acquired
   this->m_ctrl.exclusive_in = 1;

   //Prepare rollback
   exclusive_rollback rollback(this->m_ctrl, this->m_first_gate);

   //Now wait until all readers are gone
   while (this->m_ctrl.num_shared){
      this->m_second_gate.wait(lck);
   }
   rollback.release();
}

inline bool interprocess_sharable_mutex::try_lock()
{
   scoped_lock_t lck(m_mut, try_to_lock);

   //If we can't lock or any has there is any exclusive
   //or sharable mark return false;
   if(!lck.owns()
      || this->m_ctrl.exclusive_in
      || this->m_ctrl.num_shared){
      return false;
   }
   this->m_ctrl.exclusive_in = 1;
   return true;
}

template<class TimePoint>
inline bool interprocess_sharable_mutex::timed_lock
   (const TimePoint &abs_time)
{
   scoped_lock_t lck(m_mut, abs_time);
   if(!lck.owns())   return false;

   //The exclusive lock must block in the first gate
   //if an exclusive lock has been acquired
   while (this->m_ctrl.exclusive_in){
      //Mutexes and condvars handle just fine infinite abs_times
      //so avoid checking it here
      if(!this->m_first_gate.timed_wait(lck, abs_time)){
         if(this->m_ctrl.exclusive_in){
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
   while (this->m_ctrl.num_shared){
      //Mutexes and condvars handle just fine infinite abs_times
      //so avoid checking it here
      if(!this->m_second_gate.timed_wait(lck, abs_time)){
         if(this->m_ctrl.num_shared){
            return false;
         }
         break;
      }
   }
   rollback.release();
   return true;
}

inline void interprocess_sharable_mutex::unlock()
{
   scoped_lock_t lck(m_mut);
   this->m_ctrl.exclusive_in = 0;
   this->m_first_gate.notify_all();
}

//Sharable locking

inline void interprocess_sharable_mutex::lock_sharable()
{
   scoped_lock_t lck(m_mut);

   //The sharable lock must block in the first gate
   //if an exclusive lock has been acquired
   //or there are too many sharable locks
   while(this->m_ctrl.exclusive_in
        || this->m_ctrl.num_shared == constants::max_readers){
      this->m_first_gate.wait(lck);
   }

   //Increment sharable count
   ++this->m_ctrl.num_shared;
}

inline bool interprocess_sharable_mutex::try_lock_sharable()
{
   scoped_lock_t lck(m_mut, try_to_lock);

   //The sharable lock must fail
   //if an exclusive lock has been acquired
   //or there are too many sharable locks
   if(!lck.owns()
      || this->m_ctrl.exclusive_in
      || this->m_ctrl.num_shared == constants::max_readers){
      return false;
   }

   //Increment sharable count
   ++this->m_ctrl.num_shared;
   return true;
}

template<class TimePoint>
inline bool interprocess_sharable_mutex::timed_lock_sharable
   (const TimePoint &abs_time)
{
   scoped_lock_t lck(m_mut, abs_time);
   if(!lck.owns())   return false;

   //The sharable lock must block in the first gate
   //if an exclusive lock has been acquired
   //or there are too many sharable locks
   while (this->m_ctrl.exclusive_in
         || this->m_ctrl.num_shared == constants::max_readers){
      //Mutexes and condvars handle just fine infinite abs_times
      //so avoid checking it here
      if(!this->m_first_gate.timed_wait(lck, abs_time)){
         if(this->m_ctrl.exclusive_in
               || this->m_ctrl.num_shared == constants::max_readers){
            return false;
         }
         break;
      }
   }

   //Increment sharable count
   ++this->m_ctrl.num_shared;
   return true;
}

inline void interprocess_sharable_mutex::unlock_sharable()
{
   scoped_lock_t lck(m_mut);
   //Decrement sharable count
   --this->m_ctrl.num_shared;
   if (this->m_ctrl.num_shared == 0){
      this->m_second_gate.notify_one();
   }
   //Check if there are blocked sharables because of
   //there were too many sharables
   else if(this->m_ctrl.num_shared == (constants::max_readers-1)){
      this->m_first_gate.notify_all();
   }
}

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_SHARABLE_MUTEX_HPP

/* interprocess_sharable_mutex.hpp
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
*/