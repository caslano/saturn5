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

#ifndef BOOST_INTERPROCESS_SHARABLE_LOCK_HPP
#define BOOST_INTERPROCESS_SHARABLE_LOCK_HPP

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
#include <boost/interprocess/detail/simple_swap.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>

//!\file
//!Describes the upgradable_lock class that serves to acquire the upgradable
//!lock of a mutex.

namespace boost {
namespace interprocess {


//!sharable_lock is meant to carry out the tasks for sharable-locking
//!(such as read-locking), unlocking, try-sharable-locking and timed-sharable-locking
//!(recursive or not) for the Mutex. The Mutex need not supply all of this
//!functionality. If the client of sharable_lock<Mutex> does not use functionality which
//!the Mutex does not supply, no harm is done. Mutex ownership can be shared among
//!sharable_locks, and a single upgradable_lock. sharable_lock does not support
//!copy semantics. But sharable_lock supports ownership transfer from an sharable_lock,
//!upgradable_lock and scoped_lock via transfer_lock syntax.*/
template <class SharableMutex>
class sharable_lock
{
   public:
   typedef SharableMutex mutex_type;
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   typedef sharable_lock<SharableMutex> this_type;
   explicit sharable_lock(scoped_lock<mutex_type>&);
   typedef bool this_type::*unspecified_bool_type;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(sharable_lock)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:

   //!Effects: Default constructs a sharable_lock.
   //!Postconditions: owns() == false and mutex() == 0.
   sharable_lock()
      : mp_mutex(0), m_locked(false)
   {}

   //!Effects: m.lock_sharable().
   //!Postconditions: owns() == true and mutex() == &m.
   //!Notes: The constructor will take sharable-ownership of the mutex. If
   //!   another thread already owns the mutex with exclusive ownership
   //!   (scoped_lock), this thread will block until the mutex is released.
   //!   If another thread owns the mutex with sharable or upgradable ownership,
   //!   then no blocking will occur. Whether or not this constructor handles
   //!   recursive locking depends upon the mutex.
   explicit sharable_lock(mutex_type& m)
      : mp_mutex(&m), m_locked(false)
   {  mp_mutex->lock_sharable();   m_locked = true;  }

   //!Postconditions: owns() == false, and mutex() == &m.
   //!Notes: The constructor will not take ownership of the mutex. There is no effect
   //!   required on the referenced mutex.
   sharable_lock(mutex_type& m, defer_lock_type)
      : mp_mutex(&m), m_locked(false)
   {}

   //!Postconditions: owns() == true, and mutex() == &m.
   //!Notes: The constructor will suppose that the mutex is already sharable
   //!   locked. There is no effect required on the referenced mutex.
   sharable_lock(mutex_type& m, accept_ownership_type)
      : mp_mutex(&m), m_locked(true)
   {}

   //!Effects: m.try_lock_sharable()
   //!Postconditions: mutex() == &m. owns() == the return value of the
   //!   m.try_lock_sharable() executed within the constructor.
   //!Notes: The constructor will take sharable-ownership of the mutex if it
   //!   can do so without waiting. Whether or not this constructor handles
   //!   recursive locking depends upon the mutex. If the mutex_type does not
   //!   support try_lock_sharable, this constructor will fail at compile
   //!   time if instantiated, but otherwise have no effect.
   sharable_lock(mutex_type& m, try_to_lock_type)
      : mp_mutex(&m), m_locked(false)
   {  m_locked = mp_mutex->try_lock_sharable();   }

   //!Effects: m.timed_lock_sharable(abs_time)
   //!Postconditions: mutex() == &m. owns() == the return value of the
   //!   m.timed_lock_sharable() executed within the constructor.
   //!Notes: The constructor will take sharable-ownership of the mutex if it
   //!   can do so within the time specified. Whether or not this constructor
   //!   handles recursive locking depends upon the mutex. If the mutex_type
   //!   does not support timed_lock_sharable, this constructor will fail at
   //!   compile time if instantiated, but otherwise have no effect.
   sharable_lock(mutex_type& m, const boost::posix_time::ptime& abs_time)
      : mp_mutex(&m), m_locked(false)
   {  m_locked = mp_mutex->timed_lock_sharable(abs_time);  }

   //!Postconditions: mutex() == upgr.mutex(). owns() == the value of upgr.owns()
   //!   before the construction. upgr.owns() == false after the construction.
   //!Notes: If the upgr sharable_lock owns the mutex, ownership is moved to this
   //!   sharable_lock with no blocking. If the upgr sharable_lock does not own the mutex, then
   //!   neither will this sharable_lock. Only a moved sharable_lock's will match this
   //!   signature. An non-moved sharable_lock can be moved with the expression:
   //!   "boost::move(lock);". This constructor does not alter the state of the mutex,
   //!   only potentially who owns it.
   sharable_lock(BOOST_RV_REF(sharable_lock<mutex_type>) upgr)
      : mp_mutex(0), m_locked(upgr.owns())
   {  mp_mutex = upgr.release(); }

   //!Effects: If upgr.owns() then calls unlock_upgradable_and_lock_sharable() on the
   //!   referenced mutex.
   //!Postconditions: mutex() == the value upgr.mutex() had before the construction.
   //!   upgr.mutex() == 0 owns() == the value of upgr.owns() before construction.
   //!   upgr.owns() == false after the construction.
   //!Notes: If upgr is locked, this constructor will lock this sharable_lock while
   //!   unlocking upgr. Only a moved sharable_lock's will match this
   //!   signature. An non-moved upgradable_lock can be moved with the expression:
   //!   "boost::move(lock);".*/
   template<class T>
   sharable_lock(BOOST_RV_REF(upgradable_lock<T>) upgr
      , typename ipcdetail::enable_if< ipcdetail::is_same<T, SharableMutex> >::type * = 0)
      : mp_mutex(0), m_locked(false)
   {
      upgradable_lock<mutex_type> &u_lock = upgr;
      if(u_lock.owns()){
         u_lock.mutex()->unlock_upgradable_and_lock_sharable();
         m_locked = true;
      }
      mp_mutex = u_lock.release();
   }

   //!Effects: If scop.owns() then calls unlock_and_lock_sharable() on the
   //!   referenced mutex.
   //!Postconditions: mutex() == the value scop.mutex() had before the construction.
   //!   scop.mutex() == 0 owns() == scop.owns() before the constructor. After the
   //!   construction, scop.owns() == false.
   //!Notes: If scop is locked, this constructor will transfer the exclusive ownership
   //!   to a sharable-ownership of this sharable_lock.
   //!   Only a moved scoped_lock's will match this
   //!   signature. An non-moved scoped_lock can be moved with the expression:
   //!   "boost::move(lock);".
   template<class T>
   sharable_lock(BOOST_RV_REF(scoped_lock<T>) scop
               , typename ipcdetail::enable_if< ipcdetail::is_same<T, SharableMutex> >::type * = 0)
      : mp_mutex(0), m_locked(false)
   {
      scoped_lock<mutex_type> &e_lock = scop;
      if(e_lock.owns()){
         e_lock.mutex()->unlock_and_lock_sharable();
         m_locked = true;
      }
      mp_mutex = e_lock.release();
   }

   //!Effects: if (owns()) mp_mutex->unlock_sharable().
   //!Notes: The destructor behavior ensures that the mutex lock is not leaked.
   ~sharable_lock()
   {
      try{
         if(m_locked && mp_mutex)   mp_mutex->unlock_sharable();
      }
      catch(...){}
   }

   //!Effects: If owns() before the call, then unlock_sharable() is called on mutex().
   //!   *this gets the state of upgr and upgr gets set to a default constructed state.
   //!Notes: With a recursive mutex it is possible that both this and upgr own the mutex
   //!   before the assignment. In this case, this will own the mutex after the assignment
   //!   (and upgr will not), but the mutex's lock count will be decremented by one.
   sharable_lock &operator=(BOOST_RV_REF(sharable_lock<mutex_type>) upgr)
   {
      if(this->owns())
         this->unlock();
      m_locked = upgr.owns();
      mp_mutex = upgr.release();
      return *this;
   }

   //!Effects: If mutex() == 0 or already locked, throws a lock_exception()
   //!   exception. Calls lock_sharable() on the referenced mutex.
   //!Postconditions: owns() == true.
   //!Notes: The sharable_lock changes from a state of not owning the
   //!   mutex, to owning the mutex, blocking if necessary.
   void lock()
   {
      if(!mp_mutex || m_locked)
         throw lock_exception();
      mp_mutex->lock_sharable();
      m_locked = true;
   }

   //!Effects: If mutex() == 0 or already locked, throws a lock_exception()
   //!   exception. Calls try_lock_sharable() on the referenced mutex.
   //!Postconditions: owns() == the value returned from
   //!   mutex()->try_lock_sharable().
   //!Notes: The sharable_lock changes from a state of not owning the mutex,
   //!   to owning the mutex, but only if blocking was not required. If the
   //!   mutex_type does not support try_lock_sharable(), this function will
   //!   fail at compile time if instantiated, but otherwise have no effect.
   bool try_lock()
   {
      if(!mp_mutex || m_locked)
         throw lock_exception();
      m_locked = mp_mutex->try_lock_sharable();
      return m_locked;
   }

   //!Effects: If mutex() == 0 or already locked, throws a lock_exception()
   //!   exception. Calls timed_lock_sharable(abs_time) on the referenced mutex.
   //!Postconditions: owns() == the value returned from
   //!   mutex()->timed_lock_sharable(elps_time).
   //!Notes: The sharable_lock changes from a state of not owning the mutex,
   //!   to owning the mutex, but only if it can obtain ownership within the
   //!   specified time interval. If the mutex_type does not support
   //!   timed_lock_sharable(), this function will fail at compile time if
   //!   instantiated, but otherwise have no effect.
   bool timed_lock(const boost::posix_time::ptime& abs_time)
   {
      if(!mp_mutex || m_locked)
         throw lock_exception();
      m_locked = mp_mutex->timed_lock_sharable(abs_time);
      return m_locked;
   }

   //!Effects: If mutex() == 0 or not locked, throws a lock_exception() exception.
   //!   Calls unlock_sharable() on the referenced mutex.
   //!Postconditions: owns() == false.
   //!Notes: The sharable_lock changes from a state of owning the mutex, to
   //!   not owning the mutex.
   void unlock()
   {
      if(!mp_mutex || !m_locked)
         throw lock_exception();
      mp_mutex->unlock_sharable();
      m_locked = false;
   }

   //!Effects: Returns true if this scoped_lock has
   //!acquired the referenced mutex.
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
   void swap(sharable_lock<mutex_type> &other)
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

#endif // BOOST_INTERPROCESS_SHARABLE_LOCK_HPP

/* sharable_lock.hpp
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
*/