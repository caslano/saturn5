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
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
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
   named_upgradable_mutex(create_only_t create_only, const char *name, const permissions &perm = permissions());

   //!Opens or creates a global upgradable mutex with a name, and an initial count.
   //!If the upgradable mutex is created, this call is equivalent to
   //!named_upgradable_mutex(create_only_t, ...)
   //!If the upgradable mutex is already created, this call is equivalent to
   //!named_upgradable_mutex(open_only_t, ... ).
   named_upgradable_mutex(open_or_create_t open_or_create, const char *name, const permissions &perm = permissions());

   //!Opens a global upgradable mutex with a name if that upgradable mutex
   //!is previously.
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   named_upgradable_mutex(open_only_t open_only, const char *name);

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
   bool timed_lock_upgradable(const boost::posix_time::ptime &abs_time);

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
   bool timed_unlock_upgradable_and_lock(const boost::posix_time::ptime &abs_time);

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
   :  m_shmem  (create_only
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
   :  m_shmem  (open_or_create
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
   :  m_shmem  (open_only
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

inline bool named_upgradable_mutex::timed_lock
   (const boost::posix_time::ptime &abs_time)
{  return this->mutex()->timed_lock(abs_time);  }

inline void named_upgradable_mutex::lock_upgradable()
{  this->mutex()->lock_upgradable();  }

inline void named_upgradable_mutex::unlock_upgradable()
{  this->mutex()->unlock_upgradable();  }

inline bool named_upgradable_mutex::try_lock_upgradable()
{  return this->mutex()->try_lock_upgradable();  }

inline bool named_upgradable_mutex::timed_lock_upgradable
   (const boost::posix_time::ptime &abs_time)
{  return this->mutex()->timed_lock_upgradable(abs_time);   }

inline void named_upgradable_mutex::lock_sharable()
{  this->mutex()->lock_sharable();  }

inline void named_upgradable_mutex::unlock_sharable()
{  this->mutex()->unlock_sharable();  }

inline bool named_upgradable_mutex::try_lock_sharable()
{  return this->mutex()->try_lock_sharable();  }

inline bool named_upgradable_mutex::timed_lock_sharable
   (const boost::posix_time::ptime &abs_time)
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

inline bool named_upgradable_mutex::timed_unlock_upgradable_and_lock
   (const boost::posix_time::ptime &abs_time)
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