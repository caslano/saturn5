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
   shm_named_recursive_mutex(create_only_t, const char *name, const permissions &perm = permissions());

   //!Opens or creates a global recursive_mutex with a name.
   //!If the recursive_mutex is created, this call is equivalent to
   //!shm_named_recursive_mutex(create_only_t, ... )
   //!If the recursive_mutex is already created, this call is equivalent
   //!shm_named_recursive_mutex(open_only_t, ... )
   //!Does not throw
   shm_named_recursive_mutex(open_or_create_t, const char *name, const permissions &perm = permissions());

   //!Opens a global recursive_mutex with a name if that recursive_mutex is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   shm_named_recursive_mutex(open_only_t, const char *name);

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Creates a global recursive_mutex with a name.
   //!If the recursive_mutex can't be created throws interprocess_exception
   shm_named_recursive_mutex(create_only_t, const wchar_t *name, const permissions &perm = permissions());

   //!Opens or creates a global recursive_mutex with a name.
   //!If the recursive_mutex is created, this call is equivalent to
   //!shm_named_recursive_mutex(create_only_t, ... )
   //!If the recursive_mutex is already created, this call is equivalent
   //!shm_named_recursive_mutex(open_only_t, ... )
   //!Does not throw
   shm_named_recursive_mutex(open_or_create_t, const wchar_t *name, const permissions &perm = permissions());

   //!Opens a global recursive_mutex with a name if that recursive_mutex is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   shm_named_recursive_mutex(open_only_t, const wchar_t *name);

   #endif   //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

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
   template<class TimePoint>
   bool timed_lock(const TimePoint &abs_time);

   template<class TimePoint> bool try_lock_until(const TimePoint &abs_time)
   {  return this->timed_lock(abs_time);  }

   template<class Duration>  bool try_lock_for(const Duration &dur)
   {  return this->timed_lock(duration_to_ustime(dur)); }

   //!Erases a named recursive mutex
   //!from the system
   static bool remove(const char *name);

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Erases a named recursive mutex
   //!from the system
   static bool remove(const wchar_t *name);

   #endif   //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

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
   :  m_shmem  (create_only_t()
               ,name
               ,sizeof(interprocess_recursive_mutex) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(DoCreate)
               ,perm)
{}

inline shm_named_recursive_mutex::shm_named_recursive_mutex(open_or_create_t, const char *name, const permissions &perm)
   :  m_shmem  (open_or_create_t()
               ,name
               ,sizeof(interprocess_recursive_mutex) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(DoOpenOrCreate)
               ,perm)
{}

inline shm_named_recursive_mutex::shm_named_recursive_mutex(open_only_t, const char *name)
   :  m_shmem  (open_only_t()
               ,name
               ,read_write
               ,0
               ,construct_func_t(DoOpen))
{}

#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline shm_named_recursive_mutex::shm_named_recursive_mutex(create_only_t, const wchar_t *name, const permissions &perm)
   :  m_shmem  (create_only_t()
               ,name
               ,sizeof(interprocess_recursive_mutex) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(DoCreate)
               ,perm)
{}

inline shm_named_recursive_mutex::shm_named_recursive_mutex(open_or_create_t, const wchar_t *name, const permissions &perm)
   :  m_shmem  (open_or_create_t()
               ,name
               ,sizeof(interprocess_recursive_mutex) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(DoOpenOrCreate)
               ,perm)
{}

inline shm_named_recursive_mutex::shm_named_recursive_mutex(open_only_t, const wchar_t *name)
   :  m_shmem  (open_only_t()
               ,name
               ,read_write
               ,0
               ,construct_func_t(DoOpen))
{}

#endif   //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline void shm_named_recursive_mutex::lock()
{  this->mutex()->lock();  }

inline void shm_named_recursive_mutex::unlock()
{  this->mutex()->unlock();  }

inline bool shm_named_recursive_mutex::try_lock()
{  return this->mutex()->try_lock();  }

template<class TimePoint>
inline bool shm_named_recursive_mutex::timed_lock(const TimePoint &abs_time)
{  return this->mutex()->timed_lock(abs_time);  }

inline bool shm_named_recursive_mutex::remove(const char *name)
{  return shared_memory_object::remove(name); }

#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline bool shm_named_recursive_mutex::remove(const wchar_t *name)
{  return shared_memory_object::remove(name); }

#endif   //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_SHM_NAMED_RECURSIVE_MUTEX_HPP

/* named_recursive_mutex.hpp
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
*/