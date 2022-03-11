//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_NAMED_SHARABLE_MUTEX_HPP
#define BOOST_INTERPROCESS_NAMED_SHARABLE_MUTEX_HPP

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
#include <boost/interprocess/sync/interprocess_sharable_mutex.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/sync/shm/named_creation_functor.hpp>
#include <boost/interprocess/permissions.hpp>

//!\file
//!Describes a named sharable mutex class for inter-process synchronization

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
namespace ipcdetail{ class interprocess_tester; }
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

class named_condition;

//!A sharable mutex with a global name, so it can be found from different
//!processes. This mutex can't be placed in shared memory, and
//!each process should have it's own named sharable mutex.
class named_sharable_mutex
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   named_sharable_mutex();
   named_sharable_mutex(const named_sharable_mutex &);
   named_sharable_mutex &operator=(const named_sharable_mutex &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:

   //!Creates a global sharable mutex with a name.
   //!If the sharable mutex can't be created throws interprocess_exception
   named_sharable_mutex(create_only_t create_only, const char *name, const permissions &perm = permissions());

   //!Opens or creates a global sharable mutex with a name.
   //!If the sharable mutex is created, this call is equivalent to
   //!named_sharable_mutex(create_only_t, ...)
   //!If the sharable mutex is already created, this call is equivalent to
   //!named_sharable_mutex(open_only_t, ... ).
   named_sharable_mutex(open_or_create_t open_or_create, const char *name, const permissions &perm = permissions());

   //!Opens a global sharable mutex with a name if that sharable mutex
   //!is previously.
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   named_sharable_mutex(open_only_t open_only, const char *name);

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~named_sharable_mutex();

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
   //!   waiting if necessary until no other thread has exclusive, or sharable
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

   //!Erases a named sharable mutex from the system.
   //!Returns false on error. Never throws.
   static bool remove(const char *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   friend class ipcdetail::interprocess_tester;
   void dont_close_on_destruction();

   interprocess_sharable_mutex *mutex() const
   {  return static_cast<interprocess_sharable_mutex*>(m_shmem.get_user_address()); }

   typedef ipcdetail::managed_open_or_create_impl<shared_memory_object, 0, true, false> open_create_impl_t;
   open_create_impl_t m_shmem;
   typedef ipcdetail::named_creation_functor<interprocess_sharable_mutex> construct_func_t;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline named_sharable_mutex::~named_sharable_mutex()
{}

inline named_sharable_mutex::named_sharable_mutex
   (create_only_t, const char *name, const permissions &perm)
   :  m_shmem  (create_only
               ,name
               ,sizeof(interprocess_sharable_mutex) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoCreate)
               ,perm)
{}

inline named_sharable_mutex::named_sharable_mutex
   (open_or_create_t, const char *name, const permissions &perm)
   :  m_shmem  (open_or_create
               ,name
               ,sizeof(interprocess_sharable_mutex) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoOpenOrCreate)
               ,perm)
{}

inline named_sharable_mutex::named_sharable_mutex
   (open_only_t, const char *name)
   :  m_shmem  (open_only
               ,name
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoOpen))
{}

inline void named_sharable_mutex::dont_close_on_destruction()
{  ipcdetail::interprocess_tester::dont_close_on_destruction(m_shmem);  }

inline void named_sharable_mutex::lock()
{  this->mutex()->lock();  }

inline void named_sharable_mutex::unlock()
{  this->mutex()->unlock();  }

inline bool named_sharable_mutex::try_lock()
{  return this->mutex()->try_lock();  }

inline bool named_sharable_mutex::timed_lock
   (const boost::posix_time::ptime &abs_time)
{  return this->mutex()->timed_lock(abs_time);  }

inline void named_sharable_mutex::lock_sharable()
{  this->mutex()->lock_sharable();  }

inline void named_sharable_mutex::unlock_sharable()
{  this->mutex()->unlock_sharable();  }

inline bool named_sharable_mutex::try_lock_sharable()
{  return this->mutex()->try_lock_sharable();  }

inline bool named_sharable_mutex::timed_lock_sharable
   (const boost::posix_time::ptime &abs_time)
{  return this->mutex()->timed_lock_sharable(abs_time);  }

inline bool named_sharable_mutex::remove(const char *name)
{  return shared_memory_object::remove(name); }

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_NAMED_SHARABLE_MUTEX_HPP

/* named_sharable_mutex.hpp
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
*/