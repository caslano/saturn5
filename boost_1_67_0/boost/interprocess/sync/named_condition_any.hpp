//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_NAMED_CONDITION_ANY_HPP
#define BOOST_INTERPROCESS_NAMED_CONDITION_ANY_HPP

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
#include <boost/interprocess/sync/detail/locks.hpp>
#if !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_WINDOWS)
   #include <boost/interprocess/sync/windows/named_condition_any.hpp>
   #define BOOST_INTERPROCESS_USE_WINDOWS
#else
   #include <boost/interprocess/sync/shm/named_condition_any.hpp>
#endif

//!\file
//!Describes a named condition class for inter-process synchronization

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
namespace ipcdetail{ class interprocess_tester; }
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//! A global condition variable that can be created by name.
//! This condition variable is designed to work with named_mutex and
//! can't be placed in shared memory or memory mapped files.
class named_condition_any
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   named_condition_any();
   named_condition_any(const named_condition_any &);
   named_condition_any &operator=(const named_condition_any &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:
   //!Creates a global condition with a name.
   //!If the condition can't be created throws interprocess_exception
   named_condition_any(create_only_t, const char *name, const permissions &perm = permissions())
      :  m_cond(create_only_t(), name, perm)
   {}

   //!Opens or creates a global condition with a name.
   //!If the condition is created, this call is equivalent to
   //!named_condition_any(create_only_t, ... )
   //!If the condition is already created, this call is equivalent
   //!named_condition_any(open_only_t, ... )
   //!Does not throw
   named_condition_any(open_or_create_t, const char *name, const permissions &perm = permissions())
      :  m_cond(open_or_create_t(), name, perm)
   {}

   //!Opens a global condition with a name if that condition is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   named_condition_any(open_only_t, const char *name)
      :  m_cond(open_only_t(), name)
   {}

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~named_condition_any()
   {}

   //!If there is a thread waiting on *this, change that
   //!thread's state to ready. Otherwise there is no effect.*/
   void notify_one()
   {  m_cond.notify_one();  }

   //!Change the state of all threads waiting on *this to ready.
   //!If there are no waiting threads, notify_all() has no effect.
   void notify_all()
   {  m_cond.notify_all();  }

   //!Releases the lock on the named_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), and then reacquires the lock.
   template <typename L>
   void wait(L& lock)
   {  return m_cond.wait(lock); }

   //!The same as:
   //!while (!pred()) wait(lock)
   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {  return m_cond.wait(lock, pred); }

   //!Releases the lock on the named_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), or until time abs_time is reached,
   //!and then reacquires the lock.
   //!Returns: false if time abs_time is reached, otherwise true.
   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {  return m_cond.timed_wait(lock, abs_time); }

   //!The same as:   while (!pred()) {
   //!                  if (!timed_wait(lock, abs_time)) return pred();
   //!               } return true;
   template <typename L, typename Pr>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time, Pr pred)
   {  return m_cond.timed_wait(lock, abs_time, pred); }

   //!Erases a named condition from the system.
   //!Returns false on error. Never throws.
   static bool remove(const char *name)
   {  return condition_any_type::remove(name);  }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   #if defined(BOOST_INTERPROCESS_USE_WINDOWS)
   typedef ipcdetail::windows_named_condition_any   condition_any_type;
   #else
   typedef ipcdetail::shm_named_condition_any       condition_any_type;
   #endif
   condition_any_type m_cond;

   friend class ipcdetail::interprocess_tester;
   void dont_close_on_destruction()
   {  ipcdetail::interprocess_tester::dont_close_on_destruction(m_cond); }
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

}  //namespace interprocess
}  //namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif // BOOST_INTERPROCESS_NAMED_CONDITION_ANY_HPP

/* named_condition_any.hpp
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
*/