//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_NAMED_UPGRADABLE_MUTEX_HPP
#define BOOST_INTERPROCESS_NAMED_UPGRADABLE_MUTEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/detail/managed_open_or_create_impl.hpp>
#include <boost/interprocess/sync/interprocess_upgradable_mutex.hpp>
#include <boost/interprocess/sync/shm/named_creation_functor.hpp>
#include <boost/interprocess/permissions.hpp>

//!\file
//!Describes a named upgradable mutex class for inter-process synchronization

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
namespace ipcdetail{ class interprocess_tester; }
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

class named_condition;

//!A upgradable mutex with a global name, so it can be found from different
//!processes. This mutex can't be placed in shared memory, and
//!each process should have it's own named upgradable mutex.
class named_upgradable_mutex
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   named_upgradable_mutex();
   named_upgradable_mutex(const named_upgradable_mutex &);
   named_upgradable_mutex &operator=(const named_upgradable_mutex &);
   friend class named_condition;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:

   //!Creates a global upgradable mutex with a name.
   //!If the upgradable mutex can't be created throws interprocess_exception
   named_upgradable_mutex(create_only_t, const char *name, const permissions &perm = permissions());

   //!Opens or creates a global upgradable mutex with a name, and an initial count.
   //!If the upgradable mutex is created, this call is equivalent to
   //!named_upgradable_mutex(create_only_t, ...)
   //!If the upgradable mutex is already created, this call is equivalent to
   //!named_upgradable_mutex(open_only_t, ... ).
   named_upgradable_mutex(open_or_create_t, const char *name, const permissions &perm = permissions());

   //!Opens a global upgradable mutex with a name if that upgradable mutex
   //!is previously.
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   named_upgradable_mutex(open_only_t, const char *name);

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~named_upgradable_mutex();

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
   template<class TimePoint>
   bool timed_lock(const TimePoint &abs_time);

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
   template<class TimePoint>
   bool timed_lock_sharable(const TimePoint &abs_time);

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
   //!   sharable ownership release it.
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
   //!Throws: An exception derived from interprocess_exception on error.
   template<class TimePoint>
   bool timed_unlock_upgradable_and_lock(const TimePoint &abs_time);

   //!Precondition: The thread must have sharable ownership of the mutex.
   //!Effects: The thread atomically releases sharable ownership and tries to acquire
   //!   exclusive ownership. This operation will fail if there are threads with sharable
   //!   or upgradable ownership, but it will maintain sharable ownership.
   //!Returns: If acquires exclusive ownership, returns true. Otherwise returns false.
   //!Throws: An exception derived from interprocess_exception on error.
   bool try_unlock_sharable_and_lock();

   bool try_unlock_sharable_and_lock_upgradable();

   //!Erases a named upgradable mutex from the system.
   //!Returns false on error. Never throws.
   static bool remove(const char *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   friend class ipcdetail::interprocess_tester;
   void dont_close_on_destruction();

   interprocess_upgradable_mutex *mutex() const
   {  return static_cast<interprocess_upgradable_mutex*>(m_shmem.get_user_address()); }

   typedef ipcdetail::managed_open_or_create_impl<shared_memory_object, 0, true, false> open_create_impl_t;
   open_create_impl_t m_shmem;
   typedef ipcdetail::named_creation_functor<interprocess_upgradable_mutex> construct_func_t;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline named_upgradable_mutex::~named_upgradable_mutex()
{}

inline named_upgradable_mutex::named_upgradable_mutex
   (create_only_t, const char *name, const permissions &perm)
   :  m_shmem  (create_only_t()
               ,name
               ,sizeof(interprocess_upgradable_mutex) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoCreate)
               ,perm)
{}

inline named_upgradable_mutex::named_upgradable_mutex
   (open_or_create_t, const char *name, const permissions &perm)
   :  m_shmem  (open_or_create_t()
               ,name
               ,sizeof(interprocess_upgradable_mutex) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoOpenOrCreate)
               ,perm)
{}

inline named_upgradable_mutex::named_upgradable_mutex
   (open_only_t, const char *name)
   :  m_shmem  (open_only_t()
               ,name
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoOpen))
{}

inline void named_upgradable_mutex::dont_close_on_destruction()
{  ipcdetail::interprocess_tester::dont_close_on_destruction(m_shmem);  }

inline void named_upgradable_mutex::lock()
{  this->mutex()->lock();  }

inline void named_upgradable_mutex::unlock()
{  this->mutex()->unlock();  }

inline bool named_upgradable_mutex::try_lock()
{  return this->mutex()->try_lock();  }

template<class TimePoint>
inline bool named_upgradable_mutex::timed_lock(const TimePoint &abs_time)
{  return this->mutex()->timed_lock(abs_time);  }

inline void named_upgradable_mutex::lock_upgradable()
{  this->mutex()->lock_upgradable();  }

inline void named_upgradable_mutex::unlock_upgradable()
{  this->mutex()->unlock_upgradable();  }

inline bool named_upgradable_mutex::try_lock_upgradable()
{  return this->mutex()->try_lock_upgradable();  }

template<class TimePoint>
inline bool named_upgradable_mutex::timed_lock_upgradable(const TimePoint &abs_time)
{  return this->mutex()->timed_lock_upgradable(abs_time);   }

inline void named_upgradable_mutex::lock_sharable()
{  this->mutex()->lock_sharable();  }

inline void named_upgradable_mutex::unlock_sharable()
{  this->mutex()->unlock_sharable();  }

inline bool named_upgradable_mutex::try_lock_sharable()
{  return this->mutex()->try_lock_sharable();  }

template<class TimePoint>
inline bool named_upgradable_mutex::timed_lock_sharable(const TimePoint &abs_time)
{  return this->mutex()->timed_lock_sharable(abs_time);  }

inline void named_upgradable_mutex::unlock_and_lock_upgradable()
{  this->mutex()->unlock_and_lock_upgradable();  }

inline void named_upgradable_mutex::unlock_and_lock_sharable()
{  this->mutex()->unlock_and_lock_sharable();  }

inline void named_upgradable_mutex::unlock_upgradable_and_lock_sharable()
{  this->mutex()->unlock_upgradable_and_lock_sharable();  }

inline void named_upgradable_mutex::unlock_upgradable_and_lock()
{  this->mutex()->unlock_upgradable_and_lock();  }

inline bool named_upgradable_mutex::try_unlock_upgradable_and_lock()
{  return this->mutex()->try_unlock_upgradable_and_lock();  }

template<class TimePoint>
inline bool named_upgradable_mutex::timed_unlock_upgradable_and_lock(const TimePoint &abs_time)
{  return this->mutex()->timed_unlock_upgradable_and_lock(abs_time);  }

inline bool named_upgradable_mutex::try_unlock_sharable_and_lock()
{  return this->mutex()->try_unlock_sharable_and_lock();  }

inline bool named_upgradable_mutex::try_unlock_sharable_and_lock_upgradable()
{  return this->mutex()->try_unlock_sharable_and_lock_upgradable();  }

inline bool named_upgradable_mutex::remove(const char *name)
{  return shared_memory_object::remove(name); }

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_NAMED_UPGRADABLE_MUTEX_HPP

/* named_upgradable_mutex.hpp
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
*/