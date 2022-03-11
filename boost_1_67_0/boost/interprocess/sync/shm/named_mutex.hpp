//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_SHM_NAMED_MUTEX_HPP
#define BOOST_INTERPROCESS_SHM_NAMED_MUTEX_HPP

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
#include <boost/interprocess/detail/interprocess_tester.hpp>
#include <boost/interprocess/permissions.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/detail/managed_open_or_create_impl.hpp>
#include <boost/interprocess/sync/shm/named_creation_functor.hpp>

//!\file
//!Describes a named mutex class for inter-process synchronization

namespace boost {
namespace interprocess {
namespace ipcdetail {

class named_condition;

//!A mutex with a global name, so it can be found from different
//!processes. This mutex can't be placed in shared memory, and
//!each process should have it's own named mutex.
class shm_named_mutex
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Non-copyable
   shm_named_mutex();
   shm_named_mutex(const shm_named_mutex &);
   shm_named_mutex &operator=(const shm_named_mutex &);
   friend class named_condition;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Creates a global interprocess_mutex with a name.
   //!Throws interprocess_exception on error.
   shm_named_mutex(create_only_t create_only, const char *name, const permissions &perm = permissions());

   //!Opens or creates a global mutex with a name.
   //!If the mutex is created, this call is equivalent to
   //!shm_named_mutex(create_only_t, ... )
   //!If the mutex is already created, this call is equivalent
   //!shm_named_mutex(open_only_t, ... )
   //!Does not throw
   shm_named_mutex(open_or_create_t open_or_create, const char *name, const permissions &perm = permissions());

   //!Opens a global mutex with a name if that mutex is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   shm_named_mutex(open_only_t open_only, const char *name);

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~shm_named_mutex();

   //!Unlocks a previously locked
   //!interprocess_mutex.
   void unlock();

   //!Locks interprocess_mutex, sleeps when interprocess_mutex is already locked.
   //!Throws interprocess_exception if a severe error is found
   void lock();

   //!Tries to lock the interprocess_mutex, returns false when interprocess_mutex
   //!is already locked, returns true when success.
   //!Throws interprocess_exception if a severe error is found
   bool try_lock();

   //!Tries to lock the interprocess_mutex until time abs_time,
   //!Returns false when timeout expires, returns true when locks.
   //!Throws interprocess_exception if a severe error is found
   bool timed_lock(const boost::posix_time::ptime &abs_time);

   //!Erases a named mutex from the system.
   //!Returns false on error. Never throws.
   static bool remove(const char *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   typedef interprocess_mutex internal_mutex_type;
   interprocess_mutex &internal_mutex()
   {  return *static_cast<interprocess_mutex*>(m_shmem.get_user_address()); }

   private:
   friend class ipcdetail::interprocess_tester;
   void dont_close_on_destruction();
   typedef ipcdetail::managed_open_or_create_impl<shared_memory_object, 0, true, false> open_create_impl_t;
   open_create_impl_t m_shmem;
   typedef ipcdetail::named_creation_functor<interprocess_mutex> construct_func_t;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline void shm_named_mutex::dont_close_on_destruction()
{  ipcdetail::interprocess_tester::dont_close_on_destruction(m_shmem);  }

inline shm_named_mutex::~shm_named_mutex()
{}

inline shm_named_mutex::shm_named_mutex(create_only_t, const char *name, const permissions &perm)
   :  m_shmem  (create_only
               ,name
               ,sizeof(interprocess_mutex) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoCreate)
               ,perm)
{}

inline shm_named_mutex::shm_named_mutex(open_or_create_t, const char *name, const permissions &perm)
   :  m_shmem  (open_or_create
               ,name
               ,sizeof(interprocess_mutex) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoOpenOrCreate)
               ,perm)
{}

inline shm_named_mutex::shm_named_mutex(open_only_t, const char *name)
   :  m_shmem  (open_only
               ,name
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoOpen))
{}

inline void shm_named_mutex::lock()
{  this->internal_mutex().lock();  }

inline void shm_named_mutex::unlock()
{  this->internal_mutex().unlock();  }

inline bool shm_named_mutex::try_lock()
{  return this->internal_mutex().try_lock();  }

inline bool shm_named_mutex::timed_lock(const boost::posix_time::ptime &abs_time)
{  return this->internal_mutex().timed_lock(abs_time);   }

inline bool shm_named_mutex::remove(const char *name)
{  return shared_memory_object::remove(name); }

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_SHM_NAMED_MUTEX_HPP

/* named_mutex.hpp
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
*/