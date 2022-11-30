//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_NAMED_CONDITION_HPP
#define BOOST_INTERPROCESS_NAMED_CONDITION_HPP

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
   #include <boost/interprocess/sync/windows/named_condition.hpp>
   #define BOOST_INTERPROCESS_NAMED_CONDITION_USE_WINAPI
#else
   #include <boost/interprocess/sync/shm/named_condition.hpp>
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
class named_condition
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   named_condition();
   named_condition(const named_condition &);
   named_condition &operator=(const named_condition &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:

   //!Creates a global condition with a name.
   //!If the condition can't be created throws interprocess_exception
   named_condition(create_only_t, const char *name, const permissions &perm = permissions());

   //!Opens or creates a global condition with a name.
   //!If the condition is created, this call is equivalent to
   //!named_condition(create_only_t, ... )
   //!If the condition is already created, this call is equivalent
   //!named_condition(open_only_t, ... )
   //!Does not throw
   named_condition(open_or_create_t, const char *name, const permissions &perm = permissions());

   //!Opens a global condition with a name if that condition is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   named_condition(open_only_t, const char *name);

   //!Opens a global condition with a name if that condition is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //!Creates a global condition with a name.
   //!If the condition can't be created throws interprocess_exception
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   named_condition(create_only_t, const wchar_t *name, const permissions &perm = permissions());

   //!Opens or creates a global condition with a name.
   //!If the condition is created, this call is equivalent to
   //!named_condition(create_only_t, ... )
   //!If the condition is already created, this call is equivalent
   //!named_condition(open_only_t, ... )
   //!Does not throw
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   named_condition(open_or_create_t, const wchar_t *name, const permissions &perm = permissions());

   //!Opens a global condition with a name if that condition is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   named_condition(open_only_t, const wchar_t *name);

   #endif //#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~named_condition();

   //!If there is a thread waiting on *this, change that
   //!thread's state to ready. Otherwise there is no effect.*/
   void notify_one();

   //!Change the state of all threads waiting on *this to ready.
   //!If there are no waiting threads, notify_all() has no effect.
   void notify_all();

   //!Releases the lock on the named_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), and then reacquires the lock.
   template <typename L>
   void wait(L& lock);

   //!The same as:
   //!while (!pred()) wait(lock)
   template <typename L, typename Pr>
   void wait(L& lock, Pr pred);

   //!Releases the lock on the named_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), or until time abs_time is reached,
   //!and then reacquires the lock.
   //!Returns: false if time abs_time is reached, otherwise true.
   template <typename L, class TimePoint>
   bool timed_wait(L& lock, const TimePoint &abs_time);

   //!The same as:   while (!pred()) {
   //!                  if (!timed_wait(lock, abs_time)) return pred();
   //!               } return true;
   template <typename L, class TimePoint, typename Pr>
   bool timed_wait(L& lock, const TimePoint &abs_time, Pr pred);

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
   static bool remove(const char *name);

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Erases a named condition from the system.
   //!Returns false on error. Never throws.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   static bool remove(const wchar_t *name);

   #endif //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   #if defined(BOOST_INTERPROCESS_NAMED_CONDITION_USE_WINAPI)
   typedef ipcdetail::winapi_named_condition   condition_type;
   #else
   typedef ipcdetail::shm_named_condition       condition_type;
   #endif
   condition_type m_cond;

   friend class ipcdetail::interprocess_tester;
   void dont_close_on_destruction()
   {  ipcdetail::interprocess_tester::dont_close_on_destruction(m_cond); }
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline named_condition::~named_condition()
{}

inline named_condition::named_condition(create_only_t, const char *name, const permissions &perm)
   :  m_cond(create_only_t(), name, perm)
{}

inline named_condition::named_condition(open_or_create_t, const char *name, const permissions &perm)
   :  m_cond(open_or_create_t(), name, perm)
{}

inline named_condition::named_condition(open_only_t, const char *name)
   :  m_cond(open_only_t(), name)
{}

#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline named_condition::named_condition(create_only_t, const wchar_t *name, const permissions &perm)
   :  m_cond(create_only_t(), name, perm)
{}

inline named_condition::named_condition(open_or_create_t, const wchar_t *name, const permissions &perm)
   :  m_cond(open_or_create_t(), name, perm)
{}

inline named_condition::named_condition(open_only_t, const wchar_t *name)
   :  m_cond(open_only_t(), name)
{}

#endif //#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)


inline void named_condition::notify_one()
{  m_cond.notify_one();  }

inline void named_condition::notify_all()
{  m_cond.notify_all();  }

template <typename L>
inline void named_condition::wait(L& lock)
{
   ipcdetail::internal_mutex_lock<L> internal_lock(lock);
   m_cond.wait(internal_lock);
}

template <typename L, typename Pr>
inline void named_condition::wait(L& lock, Pr pred)
{
   ipcdetail::internal_mutex_lock<L> internal_lock(lock);
   m_cond.wait(internal_lock, pred);
}

template <typename L, typename TimePoint>
inline bool named_condition::timed_wait
   (L& lock, const TimePoint &abs_time)
{
   ipcdetail::internal_mutex_lock<L> internal_lock(lock);
   return m_cond.timed_wait(internal_lock, abs_time);
}

template <typename L, typename TimePoint, typename Pr>
inline bool named_condition::timed_wait
   (L& lock, const TimePoint &abs_time, Pr pred)
{
   ipcdetail::internal_mutex_lock<L> internal_lock(lock);
   return m_cond.timed_wait(internal_lock, abs_time, pred);
}

inline bool named_condition::remove(const char *name)
{
   return condition_type::remove(name);
}

#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline bool named_condition::remove(const wchar_t *name)
{
   return condition_type::remove(name);
}

#endif


#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess
}  //namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif // BOOST_INTERPROCESS_NAMED_CONDITION_HPP

/* named_condition.hpp
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
*/