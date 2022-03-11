//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_SHM_NAMED_RECURSIVE_MUTEX_HPP
#define BOOST_INTERPROCESS_SHM_NAMED_RECURSIVE_MUTEX_HPP

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
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/detail/managed_open_or_create_impl.hpp>
#include <boost/interprocess/sync/interprocess_recursive_mutex.hpp>
#include <boost/interprocess/sync/shm/named_creation_functor.hpp>
#include <boost/interprocess/permissions.hpp>

//!\file
//!Describes a named shm_named_recursive_mutex class for inter-process synchronization

namespace boost {
namespace interprocess {
namespace ipcdetail {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
class interprocess_tester;
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

class shm_named_recursive_mutex
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   shm_named_recursive_mutex();
   shm_named_recursive_mutex(const shm_named_recursive_mutex &);
   shm_named_recursive_mutex &operator=(const shm_named_recursive_mutex &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:

   //!Creates a global recursive_mutex with a name.
   //!If the recursive_mutex can't be created throws interprocess_exception
   shm_named_recursive_mutex(create_only_t create_only, const char *name, const permissions &perm = permissions());

   //!Opens or creates a global recursive_mutex with a name.
   //!If the recursive_mutex is created, this call is equivalent to
   //!shm_named_recursive_mutex(create_only_t, ... )
   //!If the recursive_mutex is already created, this call is equivalent
   //!shm_named_recursive_mutex(open_only_t, ... )
   //!Does not throw
   shm_named_recursive_mutex(open_or_create_t open_or_create, const char *name, const permissions &perm = permissions());

   //!Opens a global recursive_mutex with a name if that recursive_mutex is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   shm_named_recursive_mutex(open_only_t open_only, const char *name);

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~shm_named_recursive_mutex();

   //!Unlocks a previously locked
   //!shm_named_recursive_mutex.
   void unlock();

   //!Locks shm_named_recursive_mutex, sleeps when shm_named_recursive_mutex is already locked.
   //!Throws interprocess_exception if a severe error is found.
   void lock();

   //!Tries to lock the shm_named_recursive_mutex, returns false when shm_named_recursive_mutex
   //!is already locked, returns true when success.
   //!Throws interprocess_exception if a severe error is found.
   bool try_lock();

   //!Tries to lock the shm_named_recursive_mutex until time abs_time,
   //!Returns false when timeout expires, returns true when locks.
   //!Throws interprocess_exception if a severe error is found
   bool timed_lock(const boost::posix_time::ptime &abs_time);

   //!Erases a named recursive mutex
   //!from the system
   static bool remove(const char *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   friend class interprocess_tester;
   void dont_close_on_destruction();

   interprocess_recursive_mutex *mutex() const
   {  return static_cast<interprocess_recursive_mutex*>(m_shmem.get_user_address()); }
   typedef ipcdetail::managed_open_or_create_impl<shared_memory_object, 0, true, false> open_create_impl_t;
   open_create_impl_t m_shmem;
   typedef named_creation_functor<interprocess_recursive_mutex> construct_func_t;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

inline shm_named_recursive_mutex::~shm_named_recursive_mutex()
{}

inline void shm_named_recursive_mutex::dont_close_on_destruction()
{  interprocess_tester::dont_close_on_destruction(m_shmem);  }

inline shm_named_recursive_mutex::shm_named_recursive_mutex(create_only_t, const char *name, const permissions &perm)
   :  m_shmem  (create_only
               ,name
               ,sizeof(interprocess_recursive_mutex) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(DoCreate)
               ,perm)
{}

inline shm_named_recursive_mutex::shm_named_recursive_mutex(open_or_create_t, const char *name, const permissions &perm)
   :  m_shmem  (open_or_create
               ,name
               ,sizeof(interprocess_recursive_mutex) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(DoOpenOrCreate)
               ,perm)
{}

inline shm_named_recursive_mutex::shm_named_recursive_mutex(open_only_t, const char *name)
   :  m_shmem  (open_only
               ,name
               ,read_write
               ,0
               ,construct_func_t(DoOpen))
{}

inline void shm_named_recursive_mutex::lock()
{  this->mutex()->lock();  }

inline void shm_named_recursive_mutex::unlock()
{  this->mutex()->unlock();  }

inline bool shm_named_recursive_mutex::try_lock()
{  return this->mutex()->try_lock();  }

inline bool shm_named_recursive_mutex::timed_lock(const boost::posix_time::ptime &abs_time)
{  return this->mutex()->timed_lock(abs_time);  }

inline bool shm_named_recursive_mutex::remove(const char *name)
{  return shared_memory_object::remove(name); }

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_SHM_NAMED_RECURSIVE_MUTEX_HPP

/* named_recursive_mutex.hpp
+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
*/