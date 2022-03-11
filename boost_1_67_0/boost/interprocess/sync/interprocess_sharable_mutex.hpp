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
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
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

   //!Effects: The calling thread tries to obtain exclusive ownership of the mutex,
   //!   and if another thread has exclusive or sharable ownership of
   //!   the mutex, it waits until it can obtain the ownership.
   //!Throws: interprocess_exception on error.
   void lock();

   //!Effects: The calling thread tries to acquire exclusive ownership of the mutex
   //!   without waiting. If no other thread has exclusive or sharable
   //!   ownership of the mutex this succeeds.
   //!Returns: If it can acquire exclusive ownership immediately returns true.
   //!   If it has to wait, returns false.
   //!Throws: interprocess_exception on error.
   bool try_lock();

   //!Effects: The calling thread tries to acquire exclusive ownership of the mutex
   //!   waiting if necessary until no other thread has exclusive or sharable
   //!   ownership of the mutex or abs_time is reached.
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

inline bool interprocess_sharable_mutex::timed_lock
   (const boost::posix_time::ptime &abs_time)
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

inline bool interprocess_sharable_mutex::timed_lock_sharable
   (const boost::posix_time::ptime &abs_time)
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