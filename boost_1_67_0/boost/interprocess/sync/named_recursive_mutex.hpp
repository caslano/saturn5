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
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/permissions.hpp>
#if !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_WINDOWS)
   #include <boost/interprocess/sync/windows/named_recursive_mutex.hpp>
   #define BOOST_INTERPROCESS_USE_WINDOWS
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
   named_recursive_mutex(create_only_t create_only, const char *name, const permissions &perm = permissions());

   //!Opens or creates a global recursive_mutex with a name.
   //!If the recursive_mutex is created, this call is equivalent to
   //!named_recursive_mutex(create_only_t, ... )
   //!If the recursive_mutex is already created, this call is equivalent
   //!named_recursive_mutex(open_only_t, ... )
   //!Does not throw
   named_recursive_mutex(open_or_create_t open_or_create, const char *name, const permissions &perm = permissions());

   //!Opens a global recursive_mutex with a name if that recursive_mutex is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   named_recursive_mutex(open_only_t open_only, const char *name);

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
   void lock();

   //!Tries to lock the named_recursive_mutex, returns false when named_recursive_mutex
   //!is already locked, returns true when success.
   //!Throws interprocess_exception if a severe error is found.
   bool try_lock();

   //!Tries to lock the named_recursive_mutex until time abs_time,
   //!Returns false when timeout expires, returns true when locks.
   //!Throws interprocess_exception if a severe error is found
   bool timed_lock(const boost::posix_time::ptime &abs_time);

   //!Erases a named recursive mutex
   //!from the system
   static bool remove(const char *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   friend class ipcdetail::interprocess_tester;
   void dont_close_on_destruction();

   #if defined(BOOST_INTERPROCESS_USE_WINDOWS)
      typedef ipcdetail::windows_named_recursive_mutex   impl_t;
      #undef BOOST_INTERPROCESS_USE_WINDOWS
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

inline void named_recursive_mutex::lock()
{  m_mut.lock();  }

inline void named_recursive_mutex::unlock()
{  m_mut.unlock();  }

inline bool named_recursive_mutex::try_lock()
{  return m_mut.try_lock();  }

inline bool named_recursive_mutex::timed_lock(const boost::posix_time::ptime &abs_time)
{  return m_mut.timed_lock(abs_time);  }

inline bool named_recursive_mutex::remove(const char *name)
{  return impl_t::remove(name); }

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_NAMED_RECURSIVE_MUTEX_HPP

/* named_recursive_mutex.hpp
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
*/