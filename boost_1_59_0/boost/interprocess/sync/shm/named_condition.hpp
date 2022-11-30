//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_SHM_NAMED_CONDITION_HPP
#define BOOST_INTERPROCESS_SHM_NAMED_CONDITION_HPP

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
#include <boost/static_assert.hpp>
#include <boost/interprocess/detail/type_traits.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/detail/managed_open_or_create_impl.hpp>
#include <boost/interprocess/sync/shm/named_creation_functor.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/permissions.hpp>
#if defined (BOOST_INTERPROCESS_NAMED_MUTEX_USES_POSIX_SEMAPHORES)
   #include <boost/interprocess/sync/interprocess_mutex.hpp>
   #include <boost/interprocess/sync/scoped_lock.hpp>
   #include <boost/interprocess/sync/detail/condition_any_algorithm.hpp>
#else
   #include <boost/interprocess/sync/detail/locks.hpp>
#endif


//!\file
//!Describes process-shared variables interprocess_condition class

namespace boost {
namespace interprocess {
namespace ipcdetail {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
class interprocess_tester;
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//! A global condition variable that can be created by name.
//! This condition variable is designed to work with named_mutex and
//! can't be placed in shared memory or memory mapped files.
class shm_named_condition
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   shm_named_condition();
   shm_named_condition(const shm_named_condition &);
   shm_named_condition &operator=(const shm_named_condition &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:
   //!Creates a global condition with a name.
   //!If the condition can't be created throws interprocess_exception
   shm_named_condition(create_only_t, const char *name, const permissions &perm = permissions());

   //!Opens or creates a global condition with a name.
   //!If the condition is created, this call is equivalent to
   //!shm_named_condition(create_only_t, ... )
   //!If the condition is already created, this call is equivalent
   //!shm_named_condition(open_only_t, ... )
   //!Does not throw
   shm_named_condition(open_or_create_t, const char *name, const permissions &perm = permissions());

   //!Opens a global condition with a name if that condition is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   shm_named_condition(open_only_t, const char *name);

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Creates a global condition with a name.
   //!If the condition can't be created throws interprocess_exception
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   shm_named_condition(create_only_t, const wchar_t *name, const permissions &perm = permissions());

   //!Opens or creates a global condition with a name.
   //!If the condition is created, this call is equivalent to
   //!shm_named_condition(create_only_t, ... )
   //!If the condition is already created, this call is equivalent
   //!shm_named_condition(open_only_t, ... )
   //!Does not throw
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   shm_named_condition(open_or_create_t, const wchar_t *name, const permissions &perm = permissions());

   //!Opens a global condition with a name if that condition is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   shm_named_condition(open_only_t, const wchar_t *name);

   #endif //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~shm_named_condition();

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
   template <typename L, typename TimePoint>
   bool timed_wait(L& lock, const TimePoint &abs_time);

   //!The same as:   while (!pred()) {
   //!                  if (!timed_wait(lock, abs_time)) return pred();
   //!               } return true;
   template <typename L, typename TimePoint, typename Pr>
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

   #if defined (BOOST_INTERPROCESS_NAMED_MUTEX_USES_POSIX_SEMAPHORES)
   class internal_condition_members
   {
      public:
      typedef interprocess_mutex       mutex_type;
      typedef interprocess_condition   condvar_type;

      condvar_type&  get_condvar() {  return m_cond;  }
      mutex_type&    get_mutex()   {  return m_mtx; }

      private:
      mutex_type     m_mtx;
      condvar_type   m_cond;
   };

   typedef ipcdetail::condition_any_wrapper<internal_condition_members> internal_condition;
   #else    //defined (BOOST_INTERPROCESS_NAMED_MUTEX_USES_POSIX_SEMAPHORES)
   typedef interprocess_condition internal_condition;
   #endif   //defined (BOOST_INTERPROCESS_NAMED_MUTEX_USES_POSIX_SEMAPHORES)

   internal_condition &internal_cond()
   {  return *static_cast<internal_condition*>(m_shmem.get_user_address()); }

   friend class boost::interprocess::ipcdetail::interprocess_tester;
   void dont_close_on_destruction();

   typedef ipcdetail::managed_open_or_create_impl<shared_memory_object, 0, true, false> open_create_impl_t;
   open_create_impl_t m_shmem;

   template <class T, class Arg> friend class boost::interprocess::ipcdetail::named_creation_functor;
   typedef boost::interprocess::ipcdetail::named_creation_functor<internal_condition> construct_func_t;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline shm_named_condition::~shm_named_condition()
{}

inline shm_named_condition::shm_named_condition(create_only_t, const char *name, const permissions &perm)
   :  m_shmem  (create_only
               ,name
               ,sizeof(internal_condition) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(DoCreate)
               ,perm)
{}

inline shm_named_condition::shm_named_condition(open_or_create_t, const char *name, const permissions &perm)
   :  m_shmem  (open_or_create
               ,name
               ,sizeof(internal_condition) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(DoOpenOrCreate)
               ,perm)
{}

inline shm_named_condition::shm_named_condition(open_only_t, const char *name)
   :  m_shmem  (open_only
               ,name
               ,read_write
               ,0
               ,construct_func_t(DoOpen))
{}

#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline shm_named_condition::shm_named_condition(create_only_t, const wchar_t *name, const permissions &perm)
   :  m_shmem  (create_only
               ,name
               ,sizeof(internal_condition) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(DoCreate)
               ,perm)
{}

inline shm_named_condition::shm_named_condition(open_or_create_t, const wchar_t *name, const permissions &perm)
   :  m_shmem  (open_or_create
               ,name
               ,sizeof(internal_condition) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(DoOpenOrCreate)
               ,perm)
{}

inline shm_named_condition::shm_named_condition(open_only_t, const wchar_t *name)
   :  m_shmem  (open_only
               ,name
               ,read_write
               ,0
               ,construct_func_t(DoOpen))
{}

#endif //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline void shm_named_condition::dont_close_on_destruction()
{  interprocess_tester::dont_close_on_destruction(m_shmem);  }

inline void shm_named_condition::notify_one()
{  this->internal_cond().notify_one(); }

inline void shm_named_condition::notify_all()
{  this->internal_cond().notify_all(); }

template <typename L>
inline void shm_named_condition::wait(L& lock)
{  this->internal_cond().wait(lock); }

template <typename L, typename Pr>
inline void shm_named_condition::wait(L& lock, Pr pred)
{  this->internal_cond().wait(lock, pred); }

template <typename L, typename TimePoint>
inline bool shm_named_condition::timed_wait
   (L& lock, const TimePoint &abs_time)
{  return this->internal_cond().timed_wait(lock, abs_time); }

template <typename L, typename TimePoint, typename Pr>
inline bool shm_named_condition::timed_wait
   (L& lock, const TimePoint &abs_time, Pr pred)
{  return this->internal_cond().timed_wait(lock, abs_time, pred); }

inline bool shm_named_condition::remove(const char *name)
{  return shared_memory_object::remove(name); }

#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline bool shm_named_condition::remove(const wchar_t *name)
{  return shared_memory_object::remove(name); }

#endif


#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace ipcdetail
}  //namespace interprocess
}  //namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif // BOOST_INTERPROCESS_SHM_NAMED_CONDITION_HPP

/* named_condition.hpp
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
*/