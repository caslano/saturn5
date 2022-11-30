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
   sharable_lock() BOOST_NOEXCEPT
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
   template<class TimePoint>
   sharable_lock(mutex_type& m, const TimePoint& abs_time)
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
   sharable_lock(BOOST_RV_REF(sharable_lock<mutex_type>) upgr) BOOST_NOEXCEPT
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
      BOOST_TRY{
         if(m_locked && mp_mutex)   mp_mutex->unlock_sharable();
      }
      BOOST_CATCH(...){} BOOST_CATCH_END
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
   template<class TimePoint>
   bool timed_lock(const TimePoint& abs_time)
   {
      if(!mp_mutex || m_locked)
         throw lock_exception();
      m_locked = mp_mutex->timed_lock_sharable(abs_time);
      return m_locked;
   }

   //!Effects: If mutex() == 0 or already locked, throws a lock_exception()
   //!   exception. Calls try_lock_shared_until(abs_time) on the referenced mutex.
   //!Postconditions: owns() == the value returned from
   //!   mutex()->timed_lock_sharable(elps_time).
   //!Notes: The sharable_lock changes from a state of not owning the mutex,
   //!   to owning the mutex, but only if it can obtain ownership within the
   //!   specified time interval. If the mutex_type does not support
   //!   timed_lock_sharable(), this function will fail at compile time if
   //!   instantiated, but otherwise have no effect.
   //!
   //!Note: Similar to timed_lock, but with a std-like interface
   template<class TimePoint>
   bool try_lock_until(const TimePoint& abs_time)
   {
      if(!mp_mutex || m_locked)
         throw lock_exception();
      m_locked = mp_mutex->try_lock_shared_until(abs_time);
      return m_locked;
   }

   //!Effects: If mutex() == 0 or already locked, throws a lock_exception()
   //!   exception. Calls try_lock_shared_until(abs_time) on the referenced mutex.
   //!Postconditions: owns() == the value returned from
   //!   mutex()->timed_lock_sharable(elps_time).
   //!Notes: The sharable_lock changes from a state of not owning the mutex,
   //!   to owning the mutex, but only if it can obtain ownership within the
   //!   specified time interval. If the mutex_type does not support
   //!   timed_lock_sharable(), this function will fail at compile time if
   //!   instantiated, but otherwise have no effect.
   //!
   //!Note: Similar to timed_lock, but with a std-like interface
   template<class Duration>
   bool try_lock_for(const Duration& dur)
   {
      if(!mp_mutex || m_locked)
         throw lock_exception();
      m_locked = mp_mutex->try_lock_shared_for(dur);
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
   void swap(sharable_lock<mutex_type> &other) BOOST_NOEXCEPT
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