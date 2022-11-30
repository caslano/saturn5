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
   scoped_lock() BOOST_NOEXCEPT
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
   template<class TimePoint>
   scoped_lock(mutex_type& m, const TimePoint& abs_time)
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
   scoped_lock(BOOST_RV_REF(scoped_lock) scop) BOOST_NOEXCEPT
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
   template<class T, class TimePoint>
   scoped_lock(BOOST_RV_REF(upgradable_lock<T>) upgr, const TimePoint &abs_time
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
      BOOST_TRY{  if(m_locked && mp_mutex)   mp_mutex->unlock();  }
      BOOST_CATCH(...){} BOOST_CATCH_END
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
   template<class TimePoint>
   bool timed_lock(const TimePoint& abs_time)
   {
      if(!mp_mutex || m_locked)
         throw lock_exception();
      m_locked = mp_mutex->timed_lock(abs_time);
      return m_locked;
   }

   //!Effects: If mutex() == 0 or if already locked, throws a lock_exception()
   //!   exception. Calls try_lock_until(abs_time) on the referenced mutex.
   //!Postconditions: owns() == the value returned from mutex()-> timed_lock(abs_time).
   //!Notes: The scoped_lock changes from a state of not owning the mutex, to
   //!   owning the mutex, but only if it can obtain ownership by the specified
   //!   time. If the mutex_type does not support timed_lock (), this function
   //!   will fail at compile time if instantiated, but otherwise have no effect.*/
   template<class TimePoint>
   bool try_lock_until(const TimePoint& abs_time)
   {
      if(!mp_mutex || m_locked)
         throw lock_exception();
      m_locked = mp_mutex->try_lock_until(abs_time);
      return m_locked;
   }

   //!Effects: If mutex() == 0 or if already locked, throws a lock_exception()
   //!   exception. Calls try_lock_until(abs_time) on the referenced mutex.
   //!Postconditions: owns() == the value returned from mutex()-> timed_lock(abs_time).
   //!Notes: The scoped_lock changes from a state of not owning the mutex, to
   //!   owning the mutex, but only if it can obtain ownership by the specified
   //!   time. If the mutex_type does not support timed_lock (), this function
   //!   will fail at compile time if instantiated, but otherwise have no effect.*/
   template<class Duration>
   bool try_lock_for(const Duration& dur)
   {
      if(!mp_mutex || m_locked)
         throw lock_exception();
      m_locked = mp_mutex->try_lock_for(dur);
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
   bool owns() const BOOST_NOEXCEPT
   {  return m_locked && mp_mutex;  }

   //!Conversion to bool.
   //!Returns owns().
   operator unspecified_bool_type() const BOOST_NOEXCEPT
   {  return m_locked? &this_type::m_locked : 0;   }

   //!Effects: Returns a pointer to the referenced mutex, or 0 if
   //!there is no mutex to reference.
   mutex_type* mutex() const BOOST_NOEXCEPT
   {  return  mp_mutex;  }

   //!Effects: Returns a pointer to the referenced mutex, or 0 if there is no
   //!   mutex to reference.
   //!Postconditions: mutex() == 0 and owns() == false.
   mutex_type* release() BOOST_NOEXCEPT
   {
      mutex_type *mut = mp_mutex;
      mp_mutex = 0;
      m_locked = false;
      return mut;
   }

   //!Effects: Swaps state with moved lock.
   //!Throws: Nothing.
   void swap( scoped_lock<mutex_type> &other) BOOST_NOEXCEPT
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