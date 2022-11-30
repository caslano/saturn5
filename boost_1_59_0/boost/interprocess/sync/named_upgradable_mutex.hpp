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

   //!Opens or creates a global upgradable mutex with a name.
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

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Creates a global upgradable mutex with a name.
   //!If the upgradable mutex can't be created throws interprocess_exception
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   named_upgradable_mutex(create_only_t, const wchar_t *name, const permissions &perm = permissions());

   //!Opens or creates a global upgradable mutex with a name.
   //!If the upgradable mutex is created, this call is equivalent to
   //!named_upgradable_mutex(create_only_t, ...)
   //!If the upgradable mutex is already created, this call is equivalent to
   //!named_upgradable_mutex(open_only_t, ... ).
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   named_upgradable_mutex(open_or_create_t, const wchar_t *name, const permissions &perm = permissions());

   //!Opens a global upgradable mutex with a name if that upgradable mutex
   //!is previously.
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   named_upgradable_mutex(open_only_t, const wchar_t *name);

   #endif //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~named_upgradable_mutex();

   //Exclusive locking

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to obtain exclusive ownership of the mutex,
   //!   and if another thread has exclusive, sharable or upgradable ownership of
   //!   the mutex, it waits until it can obtain the ownership.
   //!Throws: interprocess_exception on error.
   //!
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown
   void lock();

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to acquire exclusive ownership of the mutex
   //!   without waiting. If no other thread has exclusive, sharable or upgradable
   //!   ownership of the mutex this succeeds.
   //!Returns: If it can acquire exclusive ownership immediately returns true.
   //!   If it has to wait, returns false.
   //!Throws: interprocess_exception on error.
   //!
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown
   bool try_lock();

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to acquire exclusive ownership of the mutex
   //!   waiting if necessary until no other thread has exclusive, sharable or
   //!   upgradable ownership of the mutex or abs_time is reached.
   //!Returns: If acquires exclusive ownership, returns true. Otherwise returns false.
   //!Throws: interprocess_exception on error.
   //!
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown
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

   //Upgradable locking

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to obtain upgradable ownership of the mutex,
   //!   and if another thread has exclusive or upgradable ownership of the mutex,
   //!   waits until it can obtain the ownership.
   //!Throws: interprocess_exception on error.
   //!
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown
   void lock_upgradable();

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to acquire upgradable ownership of the mutex
   //!   without waiting. If no other thread has exclusive or upgradable ownership
   //!   of the mutex this succeeds.
   //!Returns: If it can acquire upgradable ownership immediately returns true.
   //!   If it has to wait, returns false.
   //!Throws: interprocess_exception on error.
   //!
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown
   bool try_lock_upgradable();

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to acquire upgradable ownership of the mutex
   //!   waiting if necessary until no other thread has exclusive or upgradable
   //!   ownership of the mutex or abs_time is reached.
   //!Returns: If acquires upgradable ownership, returns true. Otherwise returns false.
   //!Throws: interprocess_exception on error.
   //!
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown
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

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //!Erases a named upgradable mutex from the system.
   //!Returns false on error. Never throws.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   static bool remove(const wchar_t *name);
   #endif

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

#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline named_upgradable_mutex::named_upgradable_mutex
   (create_only_t, const wchar_t *name, const permissions &perm)
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
   (open_or_create_t, const wchar_t *name, const permissions &perm)
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
   (open_only_t, const wchar_t *name)
   :  m_shmem  (open_only
               ,name
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoOpen))
{}

#endif

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

#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline bool named_upgradable_mutex::remove(const wchar_t *name)
{  return shared_memory_object::remove(name); }

#endif


#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_named_upgradable_mutex_HPP

/* named_upgradable_mutex.hpp
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
*/