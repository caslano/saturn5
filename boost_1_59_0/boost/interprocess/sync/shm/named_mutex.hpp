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
   shm_named_mutex(create_only_t, const char *name, const permissions &perm = permissions());

   //!Opens or creates a global mutex with a name.
   //!If the mutex is created, this call is equivalent to
   //!shm_named_mutex(create_only_t, ... )
   //!If the mutex is already created, this call is equivalent
   //!shm_named_mutex(open_only_t, ... )
   //!Does not throw
   shm_named_mutex(open_or_create_t, const char *name, const permissions &perm = permissions());

   //!Opens a global mutex with a name if that mutex is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   shm_named_mutex(open_only_t, const char *name);

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Creates a global interprocess_mutex with a name.
   //!Throws interprocess_exception on error.
   shm_named_mutex(create_only_t, const wchar_t *name, const permissions &perm = permissions());

   //!Opens or creates a global mutex with a name.
   //!If the mutex is created, this call is equivalent to
   //!shm_named_mutex(create_only_t, ... )
   //!If the mutex is already created, this call is equivalent
   //!shm_named_mutex(open_only_t, ... )
   //!Does not throw
   shm_named_mutex(open_or_create_t, const wchar_t *name, const permissions &perm = permissions());

   //!Opens a global mutex with a name if that mutex is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   shm_named_mutex(open_only_t, const wchar_t *name);

   #endif   //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

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
   template<class TimePoint>
   bool timed_lock(const TimePoint &abs_time);

   template<class TimePoint> bool try_lock_until(const TimePoint &abs_time)
   {  return this->timed_lock(abs_time);  }

   template<class Duration>  bool try_lock_for(const Duration &dur)
   {  return this->timed_lock(duration_to_ustime(dur)); }

   //!Erases a named mutex from the system.
   //!Returns false on error. Never throws.
   static bool remove(const char *name);

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Erases a named mutex from the system.
   //!Returns false on error. Never throws.
   static bool remove(const wchar_t *name);

   #endif

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
   :  m_shmem  (create_only_t()
               ,name
               ,sizeof(interprocess_mutex) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoCreate)
               ,perm)
{}

inline shm_named_mutex::shm_named_mutex(open_or_create_t, const char *name, const permissions &perm)
   :  m_shmem  (open_or_create_t()
               ,name
               ,sizeof(interprocess_mutex) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoOpenOrCreate)
               ,perm)
{}

inline shm_named_mutex::shm_named_mutex(open_only_t, const char *name)
   :  m_shmem  (open_only_t()
               ,name
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoOpen))
{}

#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline shm_named_mutex::shm_named_mutex(create_only_t, const wchar_t *name, const permissions &perm)
   :  m_shmem  (create_only_t()
               ,name
               ,sizeof(interprocess_mutex) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoCreate)
               ,perm)
{}

inline shm_named_mutex::shm_named_mutex(open_or_create_t, const wchar_t *name, const permissions &perm)
   :  m_shmem  (open_or_create_t()
               ,name
               ,sizeof(interprocess_mutex) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoOpenOrCreate)
               ,perm)
{}

inline shm_named_mutex::shm_named_mutex(open_only_t, const wchar_t *name)
   :  m_shmem  (open_only_t()
               ,name
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoOpen))
{}

#endif   //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline void shm_named_mutex::lock()
{  this->internal_mutex().lock();  }

inline void shm_named_mutex::unlock()
{  this->internal_mutex().unlock();  }

inline bool shm_named_mutex::try_lock()
{  return this->internal_mutex().try_lock();  }

template<class TimePoint>
inline bool shm_named_mutex::timed_lock(const TimePoint &abs_time)
{  return this->internal_mutex().timed_lock(abs_time);   }

inline bool shm_named_mutex::remove(const char *name)
{  return shared_memory_object::remove(name); }

#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline bool shm_named_mutex::remove(const wchar_t *name)
{  return shared_memory_object::remove(name); }

#endif   //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_SHM_NAMED_MUTEX_HPP

/* named_mutex.hpp
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
*/