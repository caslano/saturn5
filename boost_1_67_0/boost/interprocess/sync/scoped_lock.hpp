//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
//
// This interface is inspired by Howard Hinnant's lock proposal.
// http://home.twcny.rr.com/hinnant/cpp_extensions/threads_move.html
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_SCOPED_LOCK_HPP
#define BOOST_INTERPROCESS_SCOPED_LOCK_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/sync/lock_options.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/mpl.hpp>
#include <boost/interprocess/detail/type_traits.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/detail/simple_swap.hpp>

//!\file
//!Describes the scoped_lock class.

namespace boost {
namespace interprocess {


//!scoped_lock is meant to carry out the tasks for locking, unlocking, try-locking
//!and timed-locking (recursive or not) for the Mutex. The Mutex need not supply all
//!of this functionality. If the client of scoped_lock<Mutex> does not use
//!functionality which the Mutex does not supply, no harm is done. Mutex ownership
//!transfer is supported through the syntax of move semantics. Ownership transfer
//!is allowed both by construction and assignment. The scoped_lock does not support
//!copy semantics. A compile time error results if copy construction or copy
//!assignment is attempted. Mutex ownership can also be moved from an
//!upgradable_lock and sharable_lock via constructor. In this role, scoped_lock
//!shares the same functionality as a write_lock.
template <class Mutex>
class scoped_lock
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   typedef scoped_lock<Mutex> this_type;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(scoped_lock)
   typedef bool this_type::*unspecified_bool_type;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:

   typedef Mutex mutex_type;

   //!Effects: Default constructs a scoped_lock.
   //!Postconditions: owns() == false and mutex() == 0.
   scoped_lock()
      : mp_mutex(0), m_locked(false)
   {}

   //!Effects: m.lock().
   //!Postconditions: owns() == true and mutex() == &m.
   //!Notes: The constructor will take ownership of the mutex. If another thread
   //!   already owns the mutex, this thread will block until the mutex is released.
   //!   Whether or not this constructor handles recursive locking depends upon the mutex.
   explicit scoped_lock(mutex_type& m)
      : mp_mutex(&m), m_locked(false)
   {  mp_mutex->lock();   m_locked = true;  }

   //!Postconditions: owns() == false, and mutex() == &m.
   //!Notes: The constructor will not take ownership of the mutex. There is no effect
   //!   required on the referenced mutex.
   scoped_lock(mutex_type& m, defer_lock_type)
      : mp_mutex(&m), m_locked(false)
   {}

   //!Postconditions: owns() == true, and mutex() == &m.
   //!Notes: The constructor will suppose that the mutex is already locked. There
   //!   is no effect required on the referenced mutex.
   scoped_lock(mutex_type& m, accept_ownership_type)
      : mp_mutex(&m), m_locked(true)
   {}

   //!Effects: m.try_lock().
   //!Postconditions: mutex() == &m. owns() == the return value of the
   //!   m.try_lock() executed within the constructor.
   //!Notes: The constructor will take ownership of the mutex if it can do
   //!   so without waiting. Whether or not this constructor handles recursive
   //!   locking depends upon the mutex. If the mutex_type does not support try_lock,
   //!   this constructor will fail at compile time if instantiated, but otherwise
   //!   have no effect.
   scoped_lock(mutex_type& m, try_to_lock_type)
      : mp_mutex(&m), m_locked(mp_mutex->try_lock())
   {}

   //!Effects: m.timed_lock(abs_time).
   //!Postconditions: mutex() == &m. owns() == the return value of the
   //!   m.timed_lock(abs_time) executed within the constructor.
   //!Notes: The constructor will take ownership of the mutex if it can do
   //!   it until abs_time is reached. Whether or not this constructor
   //!   handles recursive locking depends upon the mutex. If the mutex_type
   //!   does not support try_lock, this constructor will fail at compile
   //!   time if instantiated, but otherwise have no effect.
   scoped_lock(mutex_type& m, const boost::posix_time::ptime& abs_time)
      : mp_mutex(&m), m_locked(mp_mutex->timed_lock(abs_time))
   {}

   //!Postconditions: mutex() == the value scop.mutex() had before the
   //!   constructor executes. s1.mutex() == 0. owns() == the value of
   //!   scop.owns() before the constructor executes. scop.owns().
   //!Notes: If the scop scoped_lock owns the mutex, ownership is moved
   //!   to thisscoped_lock with no blocking. If the scop scoped_lock does not
   //!   own the mutex, then neither will this scoped_lock. Only a moved
   //!   scoped_lock's will match this signature. An non-moved scoped_lock
   //!   can be moved with the expression: "boost::move(lock);". This
   //!   constructor does not alter the state of the mutex, only potentially
   //!   who owns it.
   scoped_lock(BOOST_RV_REF(scoped_lock) scop)
      : mp_mutex(0), m_locked(scop.owns())
   {  mp_mutex = scop.release(); }

   //!Effects: If upgr.owns() then calls unlock_upgradable_and_lock() on the
   //!   referenced mutex. upgr.release() is called.
   //!Postconditions: mutex() == the value upgr.mutex() had before the construction.
   //!   upgr.mutex() == 0. owns() == upgr.owns() before the construction.
   //!   upgr.owns() == false after the construction.
   //!Notes: If upgr is locked, this constructor will lock this scoped_lock while
   //!   unlocking upgr. If upgr is unlocked, then this scoped_lock will be
   //!   unlocked as well. Only a moved upgradable_lock's will match this
   //!   signature. An non-moved upgradable_lock can be moved with
   //!   the expression: "boost::move(lock);" This constructor may block if
   //!   other threads hold a sharable_lock on this mutex (sharable_lock's can
   //!   share ownership with an upgradable_lock).
   template<class T>
   explicit scoped_lock(BOOST_RV_REF(upgradable_lock<T>) upgr
      , typename ipcdetail::enable_if< ipcdetail::is_same<T, Mutex> >::type * = 0)
      : mp_mutex(0), m_locked(false)
   {
      upgradable_lock<mutex_type> &u_lock = upgr;
      if(u_lock.owns()){
         u_lock.mutex()->unlock_upgradable_and_lock();
         m_locked = true;
      }
      mp_mutex = u_lock.release();
   }

   //!Effects: If upgr.owns() then calls try_unlock_upgradable_and_lock() on the
   //!referenced mutex:
   //!   a)if try_unlock_upgradable_and_lock() returns true then mutex() obtains
   //!      the value from upgr.release() and owns() is set to true.
   //!   b)if try_unlock_upgradable_and_lock() returns false then upgr is
   //!      unaffected and this scoped_lock construction as the same effects as
   //!      a default construction.
   //!   c)Else upgr.owns() is false. mutex() obtains the value from upgr.release()
   //!      and owns() is set to false
   //!Notes: This construction will not block. It will try to obtain mutex
   //!   ownership from upgr immediately, while changing the lock type from a
   //!   "read lock" to a "write lock". If the "read lock" isn't held in the
   //!   first place, the mutex merely changes type to an unlocked "write lock".
   //!   If the "read lock" is held, then mutex transfer occurs only if it can
   //!   do so in a non-blocking manner.
   template<class T>
   scoped_lock(BOOST_RV_REF(upgradable_lock<T>) upgr, try_to_lock_type
         , typename ipcdetail::enable_if< ipcdetail::is_same<T, Mutex> >::type * = 0)
      : mp_mutex(0), m_locked(false)
   {
      upgradable_lock<mutex_type> &u_lock = upgr;
      if(u_lock.owns()){
         if((m_locked = u_lock.mutex()->try_unlock_upgradable_and_lock()) == true){
            mp_mutex = u_lock.release();
         }
      }
      else{
         u_lock.release();
      }
   }

   //!Effects: If upgr.owns() then calls timed_unlock_upgradable_and_lock(abs_time)
   //!   on the referenced mutex:
   //!   a)if timed_unlock_upgradable_and_lock(abs_time) returns true then mutex()
   //!      obtains the value from upgr.release() and owns() is set to true.
   //!   b)if timed_unlock_upgradable_and_lock(abs_time) returns false then upgr
   //!      is unaffected and this scoped_lock construction as the same effects
   //!      as a default construction.
   //!   c)Else upgr.owns() is false. mutex() obtains the value from upgr.release()
   //!      and owns() is set to false
   //!Notes: This construction will not block. It will try to obtain mutex ownership
   //!   from upgr immediately, while changing the lock type from a "read lock" to a
   //!   "write lock". If the "read lock" isn't held in the first place, the mutex
   //!   merely changes type to an unlocked "write lock". If the "read lock" is held,
   //!   then mutex transfer occurs only if it can do so in a non-blocking manner.
   template<class T>
   scoped_lock(BOOST_RV_REF(upgradable_lock<T>) upgr, boost::posix_time::ptime &abs_time
               , typename ipcdetail::enable_if< ipcdetail::is_same<T, Mutex> >::type * = 0)
      : mp_mutex(0), m_locked(false)
   {
      upgradable_lock<mutex_type> &u_lock = upgr;
      if(u_lock.owns()){
         if((m_locked = u_lock.mutex()->timed_unlock_upgradable_and_lock(abs_time)) == true){
            mp_mutex = u_lock.release();
         }
      }
      else{
         u_lock.release();
      }
   }

   //!Effects: If shar.owns() then calls try_unlock_sharable_and_lock() on the
   //!referenced mutex.
   //!   a)if try_unlock_sharable_and_lock() returns true then mutex() obtains
   //!      the value from shar.release() and owns() is set to true.
   //!   b)if try_unlock_sharable_and_lock() returns false then shar is
   //!      unaffected and this scoped_lock construction has the same
   //!      effects as a default construction.
   //!   c)Else shar.owns() is false. mutex() obtains the value from
   //!      shar.release() and owns() is set to false
   //!Notes: This construction will not block. It will try to obtain mutex
   //!   ownership from shar immediately, while changing the lock type from a
   //!   "read lock" to a "write lock". If the "read lock" isn't held in the
   //!   first place, the mutex merely changes type to an unlocked "write lock".
   //!   If the "read lock" is held, then mutex transfer occurs only if it can
   //!   do so in a non-blocking manner.
   template<class T>
   scoped_lock(BOOST_RV_REF(sharable_lock<T>) shar, try_to_lock_type
      , typename ipcdetail::enable_if< ipcdetail::is_same<T, Mutex> >::type * = 0)
      : mp_mutex(0), m_locked(false)
   {
      sharable_lock<mutex_type> &s_lock = shar;
      if(s_lock.owns()){
         if((m_locked = s_lock.mutex()->try_unlock_sharable_and_lock()) == true){
            mp_mutex = s_lock.release();
         }
      }
      else{
         s_lock.release();
      }
   }

   //!Effects: if (owns()) mp_mutex->unlock().
   //!Notes: The destructor behavior ensures that the mutex lock is not leaked.*/
   ~scoped_lock()
   {
      try{  if(m_locked && mp_mutex)   mp_mutex->unlock();  }
      catch(...){}
   }

   //!Effects: If owns() before the call, then unlock() is called on mutex().
   //!   *this gets the state of scop and scop gets set to a default constructed state.
   //!Notes: With a recursive mutex it is possible that both this and scop own
   //!   the same mutex before the assignment. In this case, this will own the
   //!   mutex after the assignment (and scop will not), but the mutex's lock
   //!   count will be decremented by one.
   scoped_lock &operator=(BOOST_RV_REF(scoped_lock) scop)
   {
      if(this->owns())
         this->unlock();
      m_locked = scop.owns();
      mp_mutex = scop.release();
      return *this;
   }

   //!Effects: If mutex() == 0 or if already locked, throws a lock_exception()
   //!   exception. Calls lock() on the referenced mutex.
   //!Postconditions: owns() == true.
   //!Notes: The scoped_lock changes from a state of not owning the mutex, to
   //!   owning the mutex, blocking if necessary.
   void lock()
   {
      if(!mp_mutex || m_locked)
         throw lock_exception();
      mp_mutex->lock();
      m_locked = true;
   }

   //!Effects: If mutex() == 0 or if already locked, throws a lock_exception()
   //!   exception. Calls try_lock() on the referenced mutex.
   //!Postconditions: owns() == the value returned from mutex()->try_lock().
   //!Notes: The scoped_lock changes from a state of not owning the mutex, to
   //!   owning the mutex, but only if blocking was not required. If the
   //!   mutex_type does not support try_lock(), this function will fail at
   //!   compile time if instantiated, but otherwise have no effect.*/
   bool try_lock()
   {
      if(!mp_mutex || m_locked)
         throw lock_exception();
      m_locked = mp_mutex->try_lock();
      return m_locked;
   }

   //!Effects: If mutex() == 0 or if already locked, throws a lock_exception()
   //!   exception. Calls timed_lock(abs_time) on the referenced mutex.
   //!Postconditions: owns() == the value returned from mutex()-> timed_lock(abs_time).
   //!Notes: The scoped_lock changes from a state of not owning the mutex, to
   //!   owning the mutex, but only if it can obtain ownership by the specified
   //!   time. If the mutex_type does not support timed_lock (), this function
   //!   will fail at compile time if instantiated, but otherwise have no effect.*/
   bool timed_lock(const boost::posix_time::ptime& abs_time)
   {
      if(!mp_mutex || m_locked)
         throw lock_exception();
      m_locked = mp_mutex->timed_lock(abs_time);
      return m_locked;
   }

   //!Effects: If mutex() == 0 or if not locked, throws a lock_exception()
   //!   exception. Calls unlock() on the referenced mutex.
   //!Postconditions: owns() == false.
   //!Notes: The scoped_lock changes from a state of owning the mutex, to not
   //!   owning the mutex.*/
   void unlock()
   {
      if(!mp_mutex || !m_locked)
         throw lock_exception();
      mp_mutex->unlock();
      m_locked = false;
   }

   //!Effects: Returns true if this scoped_lock has acquired
   //!the referenced mutex.
   bool owns() const
   {  return m_locked && mp_mutex;  }

   //!Conversion to bool.
   //!Returns owns().
   operator unspecified_bool_type() const
   {  return m_locked? &this_type::m_locked : 0;   }

   //!Effects: Returns a pointer to the referenced mutex, or 0 if
   //!there is no mutex to reference.
   mutex_type* mutex() const
   {  return  mp_mutex;  }

   //!Effects: Returns a pointer to the referenced mutex, or 0 if there is no
   //!   mutex to reference.
   //!Postconditions: mutex() == 0 and owns() == false.
   mutex_type* release()
   {
      mutex_type *mut = mp_mutex;
      mp_mutex = 0;
      m_locked = false;
      return mut;
   }

   //!Effects: Swaps state with moved lock.
   //!Throws: Nothing.
   void swap( scoped_lock<mutex_type> &other)
   {
      (simple_swap)(mp_mutex, other.mp_mutex);
      (simple_swap)(m_locked, other.m_locked);
   }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   mutex_type *mp_mutex;
   bool        m_locked;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

} // namespace interprocess
} // namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif // BOOST_INTERPROCESS_SCOPED_LOCK_HPP

/* scoped_lock.hpp
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
*/