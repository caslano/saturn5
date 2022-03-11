//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_named_upgradable_mutex_HPP
#define BOOST_INTERPROCESS_named_upgradable_mutex_HPP

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

   //!Opens or creates a global upgradable mutex with a name.
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

   //!Precondition: The thread must have sharable ownership of the mutex.
   //!Effects: The thread atomically releases sharable ownership and tries to acquire
   //!   upgradable ownership. This operation will fail if there are threads with sharable
   //!   or upgradable ownership, but it will maintain sharable ownership.
   //!Returns: If acquires upgradable ownership, returns true. Otherwise returns false.
   //!Throws: An exception derived from interprocess_exception on error.
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

#endif   //BOOST_INTERPROCESS_named_upgradable_mutex_HPP

/* named_upgradable_mutex.hpp
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
*/