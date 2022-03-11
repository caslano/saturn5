 //////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_NAMED_SEMAPHORE_HPP
#define BOOST_INTERPROCESS_NAMED_SEMAPHORE_HPP

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
#include <boost/interprocess/permissions.hpp>
#include <boost/interprocess/detail/interprocess_tester.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>

#if defined(BOOST_INTERPROCESS_NAMED_SEMAPHORE_USES_POSIX_SEMAPHORES)
#include <boost/interprocess/sync/posix/named_semaphore.hpp>
//Experimental...
#elif !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_WINDOWS)
   #include <boost/interprocess/sync/windows/named_semaphore.hpp>
   #define BOOST_INTERPROCESS_USE_WINDOWS
#else
#include <boost/interprocess/sync/shm/named_semaphore.hpp>
#endif

//!\file
//!Describes a named semaphore class for inter-process synchronization

namespace boost {
namespace interprocess {

//!A semaphore with a global name, so it can be found from different
//!processes. Allows several resource sharing patterns and efficient
//!acknowledgment mechanisms.
class named_semaphore
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Non-copyable
   named_semaphore();
   named_semaphore(const named_semaphore &);
   named_semaphore &operator=(const named_semaphore &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Creates a global semaphore with a name, and an initial count.
   //!If the semaphore can't be created throws interprocess_exception
   named_semaphore(create_only_t, const char *name, unsigned int initialCount, const permissions &perm = permissions());

   //!Opens or creates a global semaphore with a name, and an initial count.
   //!If the semaphore is created, this call is equivalent to
   //!named_semaphore(create_only_t, ...)
   //!If the semaphore is already created, this call is equivalent to
   //!named_semaphore(open_only_t, ... )
   //!and initialCount is ignored.
   named_semaphore(open_or_create_t, const char *name, unsigned int initialCount, const permissions &perm = permissions());

   //!Opens a global semaphore with a name if that semaphore is previously.
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   named_semaphore(open_only_t, const char *name);

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~named_semaphore();

   //!Increments the semaphore count. If there are processes/threads blocked waiting
   //!for the semaphore, then one of these processes will return successfully from
   //!its wait function. If there is an error an interprocess_exception exception is thrown.
   void post();

   //!Decrements the semaphore. If the semaphore value is not greater than zero,
   //!then the calling process/thread blocks until it can decrement the counter.
   //!If there is an error an interprocess_exception exception is thrown.
   void wait();

   //!Decrements the semaphore if the semaphore's value is greater than zero
   //!and returns true. If the value is not greater than zero returns false.
   //!If there is an error an interprocess_exception exception is thrown.
   bool try_wait();

   //!Decrements the semaphore if the semaphore's value is greater
   //!than zero and returns true. Otherwise, waits for the semaphore
   //!to the posted or the timeout expires. If the timeout expires, the
   //!function returns false. If the semaphore is posted the function
   //!returns true. If there is an error throws sem_exception
   bool timed_wait(const boost::posix_time::ptime &abs_time);

   //!Erases a named semaphore from the system.
   //!Returns false on error. Never throws.
   static bool remove(const char *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   friend class ipcdetail::interprocess_tester;
   void dont_close_on_destruction();

   #if defined(BOOST_INTERPROCESS_NAMED_SEMAPHORE_USES_POSIX_SEMAPHORES)
      typedef ipcdetail::posix_named_semaphore   impl_t;
   #elif defined(BOOST_INTERPROCESS_USE_WINDOWS)
      #undef BOOST_INTERPROCESS_USE_WINDOWS
      typedef ipcdetail::windows_named_semaphore impl_t;
   #else
      typedef ipcdetail::shm_named_semaphore     impl_t;
   #endif
   impl_t m_sem;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline named_semaphore::named_semaphore
   (create_only_t, const char *name, unsigned int initialCount, const permissions &perm)
   :  m_sem(create_only, name, initialCount, perm)
{}

inline named_semaphore::named_semaphore
   (open_or_create_t, const char *name, unsigned int initialCount, const permissions &perm)
   :  m_sem(open_or_create, name, initialCount, perm)
{}

inline named_semaphore::named_semaphore(open_only_t, const char *name)
   :  m_sem(open_only, name)
{}

inline named_semaphore::~named_semaphore()
{}

inline void named_semaphore::dont_close_on_destruction()
{  ipcdetail::interprocess_tester::dont_close_on_destruction(m_sem);  }

inline void named_semaphore::wait()
{  m_sem.wait();  }

inline void named_semaphore::post()
{  m_sem.post();  }

inline bool named_semaphore::try_wait()
{  return m_sem.try_wait();  }

inline bool named_semaphore::timed_wait(const boost::posix_time::ptime &abs_time)
{  return m_sem.timed_wait(abs_time);  }

inline bool named_semaphore::remove(const char *name)
{  return impl_t::remove(name);   }

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {


#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_NAMED_SEMAPHORE_HPP

/* named_semaphore.hpp
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
*/