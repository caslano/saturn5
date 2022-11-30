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
   named_sharable_mutex(create_only_t, const char *name, const permissions &perm = permissions());

   //!Opens or creates a global sharable mutex with a name.
   //!If the sharable mutex is created, this call is equivalent to
   //!named_sharable_mutex(create_only_t, ...)
   //!If the sharable mutex is already created, this call is equivalent to
   //!named_sharable_mutex(open_only_t, ... ).
   named_sharable_mutex(open_or_create_t, const char *name, const permissions &perm = permissions());

   //!Opens a global sharable mutex with a name if that sharable mutex
   //!is previously.
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   named_sharable_mutex(open_only_t, const char *name);

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Creates a global sharable mutex with a name.
   //!If the sharable mutex can't be created throws interprocess_exception
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   named_sharable_mutex(create_only_t, const wchar_t *name, const permissions &perm = permissions());

   //!Opens or creates a global sharable mutex with a name.
   //!If the sharable mutex is created, this call is equivalent to
   //!named_sharable_mutex(create_only_t, ...)
   //!If the sharable mutex is already created, this call is equivalent to
   //!named_sharable_mutex(open_only_t, ... ).
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   named_sharable_mutex(open_or_create_t, const wchar_t *name, const permissions &perm = permissions());

   //!Opens a global sharable mutex with a name if that sharable mutex
   //!is previously.
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   named_sharable_mutex(open_only_t, const wchar_t *name);

   #endif   //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~named_sharable_mutex();

   //Exclusive locking

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to obtain exclusive ownership of the mutex,
   //!   and if another thread has exclusive or sharable ownership of
   //!   the mutex, it waits until it can obtain the ownership.
   //!Throws: interprocess_exception on error.
   //! 
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown.
   void lock();

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to acquire exclusive ownership of the mutex
   //!   without waiting. If no other thread has exclusive or sharable
   //!   ownership of the mutex this succeeds.
   //!Returns: If it can acquire exclusive ownership immediately returns true.
   //!   If it has to wait, returns false.
   //!Throws: interprocess_exception on error.
   //! 
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown.
   bool try_lock();

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to acquire exclusive ownership of the mutex
   //!   waiting if necessary until no other thread has exclusive, or sharable
   //!   ownership of the mutex or abs_time is reached.
   //!Returns: If acquires exclusive ownership, returns true. Otherwise returns false.
   //!Throws: interprocess_exception on error.
   //! 
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown.
   template<class TimePoint>
   bool timed_lock(const TimePoint &abs_time);

   //!Same as `timed_lock`, but this function is modeled after the
   //!standard library interface.
   template<class TimePoint> bool try_lock_until(const TimePoint &abs_time)
   {  return this->timed_lock(abs_time);  }

   //!Same as `timed_lock`, but this function is modeled after the
   //!standard library interface.
   template<class Duration>  bool try_lock_for(const Duration &dur)
   {  return this->timed_lock(ipcdetail::duration_to_ustime(dur)); }

   //!Precondition: The thread must have exclusive ownership of the mutex.
   //!Effects: The calling thread releases the exclusive ownership of the mutex.
   //!Throws: An exception derived from interprocess_exception on error.
   void unlock();

   //Sharable locking

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to obtain sharable ownership of the mutex,
   //!   and if another thread has exclusive ownership of the mutex,
   //!   waits until it can obtain the ownership.
   //!Throws: interprocess_exception on error.
   //!
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown
   void lock_sharable();

   //!Same as `lock_sharable` but with a std-compatible interface
   //! 
   void lock_shared()
   {  this->lock_sharable();  }

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to acquire sharable ownership of the mutex
   //!   without waiting. If no other thread has exclusive ownership
   //!   of the mutex this succeeds.
   //!Returns: If it can acquire sharable ownership immediately returns true. If it
   //!   has to wait, returns false.
   //!Throws: interprocess_exception on error.
   //!
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown
   bool try_lock_sharable();

   //!Same as `try_lock_sharable` but with a std-compatible interface
   //! 
   bool try_lock_shared()
   {  return this->try_lock_sharable();  }

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to acquire sharable ownership of the mutex
   //!   waiting if necessary until no other thread has exclusive
   //!   ownership of the mutex or abs_time is reached.
   //!Returns: If acquires sharable ownership, returns true. Otherwise returns false.
   //!Throws: interprocess_exception on error.
   //!
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown
   template<class TimePoint>
   bool timed_lock_sharable(const TimePoint &abs_time);

   //!Same as `timed_lock_sharable`, but this function is modeled after the
   //!standard library interface.
   template<class TimePoint> bool try_lock_shared_until(const TimePoint &abs_time)
   {  return this->timed_lock_sharable(abs_time);  }

   //!Same as `timed_lock_sharable`, but this function is modeled after the
   //!standard library interface.
   template<class Duration>  bool try_lock_shared_for(const Duration &dur)
   {  return this->timed_lock_sharable(ipcdetail::duration_to_ustime(dur)); }

   //!Precondition: The thread must have sharable ownership of the mutex.
   //!Effects: The calling thread releases the sharable ownership of the mutex.
   //!Throws: An exception derived from interprocess_exception on error.
   void unlock_sharable();

   //!Same as `unlock_sharable` but with a std-compatible interface
   //! 
   void unlock_shared()
   {  this->unlock_sharable();  }

   //!Erases a named sharable mutex from the system.
   //!Returns false on error. Never throws.
   static bool remove(const char *name);

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Erases a named sharable mutex from the system.
   //!Returns false on error. Never throws.
   static bool remove(const wchar_t *name);

   #endif

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

#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline named_sharable_mutex::named_sharable_mutex
   (create_only_t, const wchar_t *name, const permissions &perm)
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
   (open_or_create_t, const wchar_t *name, const permissions &perm)
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
   (open_only_t, const wchar_t *name)
   :  m_shmem  (open_only
               ,name
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoOpen))
{}

#endif

inline void named_sharable_mutex::dont_close_on_destruction()
{  ipcdetail::interprocess_tester::dont_close_on_destruction(m_shmem);  }

inline void named_sharable_mutex::lock()
{  this->mutex()->lock();  }

inline void named_sharable_mutex::unlock()
{  this->mutex()->unlock();  }

inline bool named_sharable_mutex::try_lock()
{  return this->mutex()->try_lock();  }

template<class TimePoint>
inline bool named_sharable_mutex::timed_lock
   (const TimePoint &abs_time)
{  return this->mutex()->timed_lock(abs_time);  }

inline void named_sharable_mutex::lock_sharable()
{  this->mutex()->lock_sharable();  }

inline void named_sharable_mutex::unlock_sharable()
{  this->mutex()->unlock_sharable();  }

inline bool named_sharable_mutex::try_lock_sharable()
{  return this->mutex()->try_lock_sharable();  }

template<class TimePoint>
inline bool named_sharable_mutex::timed_lock_sharable
   (const TimePoint &abs_time)
{  return this->mutex()->timed_lock_sharable(abs_time);  }

inline bool named_sharable_mutex::remove(const char *name)
{  return shared_memory_object::remove(name); }

#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline bool named_sharable_mutex::remove(const wchar_t *name)
{  return shared_memory_object::remove(name); }

#endif //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_NAMED_SHARABLE_MUTEX_HPP

/* named_sharable_mutex.hpp
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
*/