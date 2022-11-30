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

#include <boost/interprocess/sync/cv_status.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/interprocess_tester.hpp>
#include <boost/interprocess/permissions.hpp>
#include <boost/interprocess/sync/detail/locks.hpp>
#if !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_WINDOWS)
   #include <boost/interprocess/sync/windows/named_condition_any.hpp>
   #define BOOST_INTERPROCESS_NAMED_CONDITION_ANY_USE_WINAPI
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

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Creates a global condition with a name.
   //!If the condition can't be created throws interprocess_exception
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   named_condition_any(create_only_t, const wchar_t *name, const permissions &perm = permissions())
      :  m_cond(create_only_t(), name, perm)
   {}

   //!Opens or creates a global condition with a name.
   //!If the condition is created, this call is equivalent to
   //!named_condition_any(create_only_t, ... )
   //!If the condition is already created, this call is equivalent
   //!named_condition_any(open_only_t, ... )
   //!Does not throw
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   named_condition_any(open_or_create_t, const wchar_t *name, const permissions &perm = permissions())
      :  m_cond(open_or_create_t(), name, perm)
   {}

   //!Opens a global condition with a name if that condition is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   named_condition_any(open_only_t, const wchar_t *name)
      :  m_cond(open_only_t(), name)
   {}

   #endif   //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

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
   template <typename L, typename TimePoint>
   bool timed_wait(L& lock, const TimePoint &abs_time)
   {  return m_cond.timed_wait(lock, abs_time); }

   //!The same as:   while (!pred()) {
   //!                  if (!timed_wait(lock, abs_time)) return pred();
   //!               } return true;
   template <typename L, typename TimePoint, typename Pr>
   bool timed_wait(L& lock, const TimePoint &abs_time, Pr pred)
   {  return m_cond.timed_wait(lock, abs_time, pred); }

   //!Same as `timed_wait`, but this function is modeled after the
   //!standard library interface.
   template <typename L, class TimePoint>
   cv_status wait_until(L& lock, const TimePoint &abs_time)
   {  return this->timed_wait(lock, abs_time) ? cv_status::no_timeout : cv_status::timeout; }

   //!Same as `timed_wait`, but this function is modeled after the
   //!standard library interface.
   template <typename L, class TimePoint, typename Pr>
   bool wait_until(L& lock, const TimePoint &abs_time, Pr pred)
   {  return this->timed_wait(lock, abs_time, pred); }

   //!Same as `timed_wait`, but this function is modeled after the
   //!standard library interface and uses relative timeouts.
   template <typename L, class Duration>
   cv_status wait_for(L& lock, const Duration &dur)
   {  return this->wait_until(lock, ipcdetail::duration_to_ustime(dur)); }

   //!Same as `timed_wait`, but this function is modeled after the
   //!standard library interface and uses relative timeouts
   template <typename L, class Duration, typename Pr>
   bool wait_for(L& lock, const Duration &dur, Pr pred)
   {  return this->wait_until(lock, ipcdetail::duration_to_ustime(dur), pred); }

   //!Erases a named condition from the system.
   //!Returns false on error. Never throws.
   static bool remove(const char *name)
   {  return condition_any_type::remove(name);  }

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Erases a named condition from the system.
   //!Returns false on error. Never throws.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   static bool remove(const wchar_t *name)
   {  return condition_any_type::remove(name);  }

   #endif //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   #if defined(BOOST_INTERPROCESS_NAMED_CONDITION_ANY_USE_WINAPI)
   typedef ipcdetail::winapi_named_condition_any   condition_any_type;
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