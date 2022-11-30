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

#ifndef BOOST_INTERPROCESS_UPGRADABLE_LOCK_HPP
#define BOOST_INTERPROCESS_UPGRADABLE_LOCK_HPP

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
#include <boost/interprocess/detail/mpl.hpp>
#include <boost/interprocess/detail/type_traits.hpp>

#include <boost/interprocess/exceptions.hpp>
#include <boost/move/utility_core.hpp>

//!\file
//!Describes the upgradable_lock class that serves to acquire the upgradable
//!lock of a mutex.

namespace boost {
namespace interprocess {

//!upgradable_lock is meant to carry out the tasks for read-locking, unlocking,
//!try-read-locking and timed-read-locking (recursive or not) for the Mutex.
//!Additionally the upgradable_lock can transfer ownership to a scoped_lock
//!using transfer_lock syntax. The Mutex need not supply all of the functionality.
//!If the client of upgradable_lock<Mutex> does not use functionality which the
//!Mutex does not supply, no harm is done. Mutex ownership can be shared among
//!read_locks, and a single upgradable_lock. upgradable_lock does not support
//!copy semantics. However upgradable_lock supports ownership transfer from
//!a upgradable_locks or scoped_locks via transfer_lock syntax.
template <class UpgradableMutex>
class upgradable_lock
{
   public:
   typedef UpgradableMutex mutex_type;
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   typedef upgradable_lock<UpgradableMutex> this_type;
   explicit upgradable_lock(scoped_lock<mutex_type>&);
   typedef bool this_type::*unspecified_bool_type;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(upgradable_lock)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:

   //!Effects: Default constructs a upgradable_lock.
   //!Postconditions: owns() == false and mutex() == 0.
   upgradable_lock() BOOST_NOEXCEPT
      : mp_mutex(0), m_locked(false)
   {}

   explicit upgradable_lock(mutex_type& m)
      : mp_mutex(&m), m_locked(false)
   {  mp_mutex->lock_upgradable();   m_locked = true;  }

   //!Postconditions: owns() == false, and mutex() == &m.
   //!Notes: The constructor will not take ownership of the mutex. There is no effect
   //!   required on the referenced mutex.
   upgradable_lock(mutex_type& m, defer_lock_type)
      : mp_mutex(&m), m_locked(false)
   {}

   //!Postconditions: owns() == true, and mutex() == &m.
   //!Notes: The constructor will suppose that the mutex is already upgradable
   //!   locked. There is no effect required on the referenced mutex.
   upgradable_lock(mutex_type& m, accept_ownership_type)
      : mp_mutex(&m), m_locked(true)
   {}

   //!Effects: m.try_lock_upgradable().
   //!Postconditions: mutex() == &m. owns() == the return value of the
   //!   m.try_lock_upgradable() executed within the constructor.
   //!Notes: The constructor will take upgradable-ownership of the mutex
   //!   if it can do so without waiting. Whether or not this constructor
   //!   handles recursive locking depends upon the mutex. If the mutex_type
   //!   does not support try_lock_upgradable, this constructor will fail at
   //!   compile time if instantiated, but otherwise have no effect.
   upgradable_lock(mutex_type& m, try_to_lock_type)
      : mp_mutex(&m), m_locked(false)
   {  m_locked = mp_mutex->try_lock_upgradable();   }

   //!Effects: m.timed_lock_upgradable(abs_time)
   //!Postconditions: mutex() == &m. owns() == the return value of the
   //!   m.timed_lock_upgradable() executed within the constructor.
   //!Notes: The constructor will take upgradable-ownership of the mutex if it
   //!   can do so within the time specified. Whether or not this constructor
   //!   handles recursive locking depends upon the mutex. If the mutex_type
   //!   does not support timed_lock_upgradable, this constructor will fail
   //!   at compile time if instantiated, but otherwise have no effect.
   template<class TimePoint>
   upgradable_lock(mutex_type& m, const TimePoint& abs_time)
      : mp_mutex(&m), m_locked(false)
   {  m_locked = mp_mutex->timed_lock_upgradable(abs_time);  }

   //!Effects: No effects on the underlying mutex.
   //!Postconditions: mutex() == the value upgr.mutex() had before the
   //!   construction. upgr.mutex() == 0. owns() == upgr.owns() before the
   //!   construction. upgr.owns() == false.
   //!Notes: If upgr is locked, this constructor will lock this upgradable_lock
   //!   while unlocking upgr. If upgr is unlocked, then this upgradable_lock will
   //!   be unlocked as well. Only a moved upgradable_lock's will match this
   //!   signature. An non-moved upgradable_lock can be moved with the
   //!   expression: "boost::move(lock);". This constructor does not alter the
   //!   state of the mutex, only potentially who owns it.
   upgradable_lock(BOOST_RV_REF(upgradable_lock<mutex_type>) upgr) BOOST_NOEXCEPT
      : mp_mutex(0), m_locked(upgr.owns())
   {  mp_mutex = upgr.release(); }

   //!Effects: If scop.owns(), m_.unlock_and_lock_upgradable().
   //!Postconditions: mutex() == the value scop.mutex() had before the construction.
   //!   scop.mutex() == 0. owns() == scop.owns() before the constructor. After the
   //!   construction, scop.owns() == false.
   //!Notes: If scop is locked, this constructor will transfer the exclusive-ownership
   //!   to an upgradable-ownership of this upgradable_lock.
   //!   Only a moved sharable_lock's will match this
   //!   signature. An non-moved sharable_lock can be moved with the
   //!   expression: "boost::move(lock);".
   template<class T>
   upgradable_lock(BOOST_RV_REF(scoped_lock<T>) scop
                  , typename ipcdetail::enable_if< ipcdetail::is_same<T, UpgradableMutex> >::type * = 0)
      : mp_mutex(0), m_locked(false)
   {
      scoped_lock<mutex_type> &u_lock = scop;
      if(u_lock.owns()){
         u_lock.mutex()->unlock_and_lock_upgradable();
         m_locked = true;
      }
      mp_mutex = u_lock.release();
   }

   //!Effects: If shar.owns() then calls try_unlock_sharable_and_lock_upgradable()
   //!   on the referenced mutex.
   //!   a)if try_unlock_sharable_and_lock_upgradable() returns true then mutex()
   //!      obtains the value from shar.release() and owns() is set to true.
   //!   b)if try_unlock_sharable_and_lock_upgradable() returns false then shar is
   //!      unaffected and this upgradable_lock construction has the same
   //!      effects as a default construction.
   //!   c)Else shar.owns() is false. mutex() obtains the value from shar.release()
   //!      and owns() is set to false.
   //!Notes: This construction will not block. It will try to obtain mutex
   //!   ownership from shar immediately, while changing the lock type from a
   //!   "read lock" to an "upgradable lock". If the "read lock" isn't held
   //!   in the first place, the mutex merely changes type to an unlocked
   //!   "upgradable lock". If the "read lock" is held, then mutex transfer
   //!   occurs only if it can do so in a non-blocking manner.
   template<class T>
   upgradable_lock( BOOST_RV_REF(sharable_lock<T>) shar, try_to_lock_type
                  , typename ipcdetail::enable_if< ipcdetail::is_same<T, UpgradableMutex> >::type * = 0)
      : mp_mutex(0), m_locked(false)
   {
      sharable_lock<mutex_type> &s_lock = shar;
      if(s_lock.owns()){
         if((m_locked = s_lock.mutex()->try_unlock_sharable_and_lock_upgradable()) == true){
            mp_mutex = s_lock.release();
         }
      }
      else{
         s_lock.release();
      }
   }

   //!Effects: if (owns()) m_->unlock_upgradable().
   //!Notes: The destructor behavior ensures that the mutex lock is not leaked.
   ~upgradable_lock()
   {
      BOOST_TRY{
         if(m_locked && mp_mutex)   mp_mutex->unlock_upgradable();
      }
      BOOST_CATCH(...){} BOOST_CATCH_END
   }

   //!Effects: If owns(), then unlock_upgradable() is called on mutex().
   //!   *this gets the state of upgr and upgr gets set to a default constructed state.
   //!Notes: With a recursive mutex it is possible that both this and upgr own the
   //!   mutex before the assignment. In this case, this will own the mutex
   //!   after the assignment (and upgr will not), but the mutex's upgradable lock
   //!   count will be decremented by one.
   upgradable_lock &operator=(BOOST_RV_REF(upgradable_lock) upgr)
   {
      if(this->owns())
         this->unlock();
      m_locked = upgr.owns();
      mp_mutex = upgr.release();
      return *this;
   }

   //!Effects: If mutex() == 0 or if already locked, throws a lock_exception()
   //!   exception. Calls lock_upgradable() on the referenced mutex.
   //!Postconditions: owns() == true.
   //!Notes: The sharable_lock changes from a state of not owning the mutex,
   //!   to owning the mutex, blocking if necessary.
   void lock()
   {
      if(!mp_mutex || m_locked)
         throw lock_exception();
      mp_mutex->lock_upgradable();
      m_locked = true;
   }

   //!Effects: If mutex() == 0 or if already locked, throws a lock_exception()
   //!   exception. Calls try_lock_upgradable() on the referenced mutex.
   //!Postconditions: owns() == the value returned from
   //!   mutex()->try_lock_upgradable().
   //!Notes: The upgradable_lock changes from a state of not owning the mutex,
   //!   to owning the mutex, but only if blocking was not required. If the
   //!   mutex_type does not support try_lock_upgradable(), this function will
   //!   fail at compile time if instantiated, but otherwise have no effect.
   bool try_lock()
   {
      if(!mp_mutex || m_locked)
         throw lock_exception();
      m_locked = mp_mutex->try_lock_upgradable();
      return m_locked;
   }

   //!Effects: If mutex() == 0 or if already locked, throws a lock_exception()
   //!   exception. Calls timed_lock_upgradable(abs_time) on the referenced mutex.
   //!Postconditions: owns() == the value returned from
   //!   mutex()->timed_lock_upgradable(abs_time).
   //!Notes: The upgradable_lock changes from a state of not owning the mutex,
   //!   to owning the mutex, but only if it can obtain ownership within the
   //!   specified time. If the mutex_type does not support
   //!   timed_lock_upgradable(abs_time), this function will fail at compile
   //!   time if instantiated, but otherwise have no effect.
   template<class TimePoint>
   bool timed_lock(const TimePoint& abs_time)
   {
      if(!mp_mutex || m_locked)
         throw lock_exception();
      m_locked = mp_mutex->timed_lock_upgradable(abs_time);
      return m_locked;
   }

   //!Effects: If mutex() == 0 or if not locked, throws a lock_exception()
   //!   exception. Calls unlock_upgradable() on the referenced mutex.
   //!Postconditions: owns() == false.
   //!Notes: The upgradable_lock changes from a state of owning the mutex,
   //!   to not owning the mutex.
   void unlock()
   {
      if(!mp_mutex || !m_locked)
         throw lock_exception();
      mp_mutex->unlock_upgradable();
      m_locked = false;
   }

   //!Effects: Returns true if this scoped_lock has acquired the
   //!referenced mutex.
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
   void swap(upgradable_lock<mutex_type> &other) BOOST_NOEXCEPT
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

#endif // BOOST_INTERPROCESS_UPGRADABLE_LOCK_HPP

/* upgradable_lock.hpp
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
*/