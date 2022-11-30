//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_NAMED_RECURSIVE_MUTEX_HPP
#define BOOST_INTERPROCESS_NAMED_RECURSIVE_MUTEX_HPP

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
#include <boost/interprocess/permissions.hpp>

#if !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_WINDOWS)
   #include <boost/interprocess/sync/windows/named_recursive_mutex.hpp>
   #define BOOST_INTERPROCESS_NAMED_RECURSIVE_MUTEX_USE_WINAPI
#else
   #include <boost/interprocess/sync/shm/named_recursive_mutex.hpp>
#endif

//!\file
//!Describes a named named_recursive_mutex class for inter-process synchronization

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
namespace ipcdetail{ class interprocess_tester; }
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!A recursive mutex with a global name, so it can be found from different
//!processes. This mutex can't be placed in shared memory, and
//!each process should have it's own named_recursive_mutex.
class named_recursive_mutex
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   named_recursive_mutex();
   named_recursive_mutex(const named_recursive_mutex &);
   named_recursive_mutex &operator=(const named_recursive_mutex &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:

   //!Creates a global recursive_mutex with a name.
   //!If the recursive_mutex can't be created throws interprocess_exception
   named_recursive_mutex(create_only_t, const char *name, const permissions &perm = permissions());

   //!Opens or creates a global recursive_mutex with a name.
   //!If the recursive_mutex is created, this call is equivalent to
   //!named_recursive_mutex(create_only_t, ... )
   //!If the recursive_mutex is already created, this call is equivalent
   //!named_recursive_mutex(open_only_t, ... )
   //!Does not throw
   named_recursive_mutex(open_or_create_t, const char *name, const permissions &perm = permissions());

   //!Opens a global recursive_mutex with a name if that recursive_mutex is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   named_recursive_mutex(open_only_t, const char *name);

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Creates a global recursive_mutex with a name.
   //!If the recursive_mutex can't be created throws interprocess_exception
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   named_recursive_mutex(create_only_t, const wchar_t *name, const permissions &perm = permissions());

   //!Opens or creates a global recursive_mutex with a name.
   //!If the recursive_mutex is created, this call is equivalent to
   //!named_recursive_mutex(create_only_t, ... )
   //!If the recursive_mutex is already created, this call is equivalent
   //!named_recursive_mutex(open_only_t, ... )
   //!Does not throw
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   named_recursive_mutex(open_or_create_t, const wchar_t *name, const permissions &perm = permissions());

   //!Opens a global recursive_mutex with a name if that recursive_mutex is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   named_recursive_mutex(open_only_t, const wchar_t *name);

   #endif //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~named_recursive_mutex();

   //!Unlocks a previously locked
   //!named_recursive_mutex.
   void unlock();

   //!Locks named_recursive_mutex, sleeps when named_recursive_mutex is already locked.
   //!Throws interprocess_exception if a severe error is found.
   //! 
   //!Note: A program shall not deadlock if the thread that has ownership calls 
   //!   this function. 
   void lock();

   //!Tries to lock the named_recursive_mutex, returns false when named_recursive_mutex
   //!is already locked, returns true when success.
   //!Throws interprocess_exception if a severe error is found.
   //! 
   //!Note: A program shall not deadlock if the thread that has ownership calls 
   //!   this function. 
   bool try_lock();

   //!Tries to lock the named_recursive_mutex until time abs_time,
   //!Returns false when timeout expires, returns true when locks.
   //!Throws interprocess_exception if a severe error is found
   //! 
   //!Note: A program shall not deadlock if the thread that has ownership calls 
   //!   this function. 
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

   //!Erases a named recursive mutex
   //!from the system
   static bool remove(const char *name);

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //!Erases a named recursive mutex
   //!from the system
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   static bool remove(const wchar_t *name);
   #endif   //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   friend class ipcdetail::interprocess_tester;
   void dont_close_on_destruction();

   #if defined(BOOST_INTERPROCESS_NAMED_RECURSIVE_MUTEX_USE_WINAPI)
      typedef ipcdetail::winapi_named_recursive_mutex   impl_t;
   #else
      typedef ipcdetail::shm_named_recursive_mutex impl_t;
   #endif
   impl_t m_mut;

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline named_recursive_mutex::~named_recursive_mutex()
{}

inline void named_recursive_mutex::dont_close_on_destruction()
{  ipcdetail::interprocess_tester::dont_close_on_destruction(m_mut);  }

inline named_recursive_mutex::named_recursive_mutex(create_only_t, const char *name, const permissions &perm)
   :  m_mut  (create_only, name, perm)
{}

inline named_recursive_mutex::named_recursive_mutex(open_or_create_t, const char *name, const permissions &perm)
   :  m_mut  (open_or_create, name, perm)
{}

inline named_recursive_mutex::named_recursive_mutex(open_only_t, const char *name)
   :  m_mut   (open_only, name)
{}

#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline named_recursive_mutex::named_recursive_mutex(create_only_t, const wchar_t *name, const permissions &perm)
   :  m_mut  (create_only, name, perm)
{}

inline named_recursive_mutex::named_recursive_mutex(open_or_create_t, const wchar_t *name, const permissions &perm)
   :  m_mut  (open_or_create, name, perm)
{}

inline named_recursive_mutex::named_recursive_mutex(open_only_t, const wchar_t *name)
   :  m_mut   (open_only, name)
{}

#endif   //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline void named_recursive_mutex::lock()
{  m_mut.lock();  }

inline void named_recursive_mutex::unlock()
{  m_mut.unlock();  }

inline bool named_recursive_mutex::try_lock()
{  return m_mut.try_lock();  }

template<class TimePoint>
inline bool named_recursive_mutex::timed_lock(const TimePoint &abs_time)
{  return m_mut.timed_lock(abs_time);  }

inline bool named_recursive_mutex::remove(const char *name)
{  return impl_t::remove(name); }

#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline bool named_recursive_mutex::remove(const wchar_t *name)
{  return impl_t::remove(name); }

#endif   //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_NAMED_RECURSIVE_MUTEX_HPP

/* named_recursive_mutex.hpp
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
*/