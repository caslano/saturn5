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
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>

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
   upgradable_lock()
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
   upgradable_lock(mutex_type& m, const boost::posix_time::ptime& abs_time)
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
   upgradable_lock(BOOST_RV_REF(upgradable_lock<mutex_type>) upgr)
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
      try{
         if(m_locked && mp_mutex)   mp_mutex->unlock_upgradable();
      }
      catch(...){}
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
   bool timed_lock(const boost::posix_time::ptime& abs_time)
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
   void swap(upgradable_lock<mutex_type> &other)
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