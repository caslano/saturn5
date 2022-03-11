//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_NAMED_MUTEX_HPP
#define BOOST_INTERPROCESS_NAMED_MUTEX_HPP

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
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/permissions.hpp>

#if defined(BOOST_INTERPROCESS_NAMED_MUTEX_USES_POSIX_SEMAPHORES)
   #include <boost/interprocess/sync/posix/named_mutex.hpp>
   #define BOOST_INTERPROCESS_USE_POSIX_SEMAPHORES
#elif !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_WINDOWS)
   #include <boost/interprocess/sync/windows/named_mutex.hpp>
   #define BOOST_INTERPROCESS_USE_WINDOWS
#else
#include <boost/interprocess/sync/shm/named_mutex.hpp>
#endif

//!\file
//!Describes a named mutex class for inter-process synchronization

namespace boost {
namespace interprocess {

class named_condition;

//!A mutex with a global name, so it can be found from different
//!processes. This mutex can't be placed in shared memory, and
//!each process should have it's own named_mutex.
class named_mutex
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Non-copyable
   named_mutex();
   named_mutex(const named_mutex &);
   named_mutex &operator=(const named_mutex &);
   friend class named_condition;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Creates a global mutex with a name.
   //!Throws interprocess_exception on error.
   named_mutex(create_only_t create_only, const char *name, const permissions &perm = permissions());

   //!Opens or creates a global mutex with a name.
   //!If the mutex is created, this call is equivalent to
   //!named_mutex(create_only_t, ... )
   //!If the mutex is already created, this call is equivalent
   //!named_mutex(open_only_t, ... )
   //!Does not throw
   named_mutex(open_or_create_t open_or_create, const char *name, const permissions &perm = permissions());

   //!Opens a global mutex with a name if that mutex is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   named_mutex(open_only_t open_only, const char *name);

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~named_mutex();

   //!Unlocks a previously locked
   //!mutex.
   void unlock();

   //!Locks the mutex, sleeps when the mutex is already locked.
   //!Throws interprocess_exception if a severe error is found
   void lock();

   //!Tries to lock the mutex, returns false when the mutex
   //!is already locked, returns true when success.
   //!Throws interprocess_exception if a severe error is found
   bool try_lock();

   //!Tries to lock the the mutex until time abs_time,
   //!Returns false when timeout expires, returns true when locks.
   //!Throws interprocess_exception if a severe error is found
   bool timed_lock(const boost::posix_time::ptime &abs_time);

   //!Erases a named mutex from the system.
   //!Returns false on error. Never throws.
   static bool remove(const char *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   friend class ipcdetail::interprocess_tester;
   void dont_close_on_destruction();

   public:
   #if defined(BOOST_INTERPROCESS_USE_POSIX_SEMAPHORES)
      typedef ipcdetail::posix_named_mutex      internal_mutex_type;
      #undef BOOST_INTERPROCESS_USE_POSIX_SEMAPHORES
   #elif defined(BOOST_INTERPROCESS_USE_WINDOWS)
      typedef ipcdetail::windows_named_mutex    internal_mutex_type;
      #undef BOOST_INTERPROCESS_USE_WINDOWS
   #else
      typedef ipcdetail::shm_named_mutex        internal_mutex_type;
   #endif
   internal_mutex_type &internal_mutex()
   {  return m_mut; }

   internal_mutex_type m_mut;

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline named_mutex::named_mutex(create_only_t, const char *name, const permissions &perm)
   :  m_mut(create_only_t(), name, perm)
{}

inline named_mutex::named_mutex(open_or_create_t, const char *name, const permissions &perm)
   :  m_mut(open_or_create_t(), name, perm)
{}

inline named_mutex::named_mutex(open_only_t, const char *name)
   :  m_mut(open_only_t(), name)
{}

inline void named_mutex::dont_close_on_destruction()
{  ipcdetail::interprocess_tester::dont_close_on_destruction(m_mut); }

inline named_mutex::~named_mutex()
{}

inline void named_mutex::lock()
{  m_mut.lock();  }

inline void named_mutex::unlock()
{  m_mut.unlock();  }

inline bool named_mutex::try_lock()
{  return m_mut.try_lock();  }

inline bool named_mutex::timed_lock(const boost::posix_time::ptime &abs_time)
{  return m_mut.timed_lock(abs_time);  }

inline bool named_mutex::remove(const char *name)
{  return internal_mutex_type::remove(name);   }

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_NAMED_MUTEX_HPP

/* named_mutex.hpp
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
*/