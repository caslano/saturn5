//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_SHM_NAMED_CONDITION_ANY_HPP
#define BOOST_INTERPROCESS_SHM_NAMED_CONDITION_ANY_HPP

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
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/detail/condition_any_algorithm.hpp>

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
class shm_named_condition_any
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   shm_named_condition_any();
   shm_named_condition_any(const shm_named_condition_any &);
   shm_named_condition_any &operator=(const shm_named_condition_any &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:
   //!Creates a global condition with a name.
   //!If the condition can't be created throws interprocess_exception
   template <class CharT>
   shm_named_condition_any(create_only_t, const CharT *name, const permissions &perm = permissions())
      :  m_shmem  (create_only_t()
                  ,name
                  ,sizeof(internal_condition) +
                     open_create_impl_t::ManagedOpenOrCreateUserOffset
                  ,read_write
                  ,0
                  ,construct_func_t(DoCreate)
                  ,perm)
   {}

   //!Opens or creates a global condition with a name.
   //!If the condition is created, this call is equivalent to
   //!shm_named_condition_any(create_only_t, ... )
   //!If the condition is already created, this call is equivalent
   //!shm_named_condition_any(open_only_t, ... )
   //!Does not throw
   template <class CharT>
   shm_named_condition_any(open_or_create_t, const CharT *name, const permissions &perm = permissions())
      :  m_shmem  (open_or_create_t()
                  ,name
                  ,sizeof(internal_condition) +
                     open_create_impl_t::ManagedOpenOrCreateUserOffset
                  ,read_write
                  ,0
                  ,construct_func_t(DoOpenOrCreate)
                  ,perm)
   {}

   //!Opens a global condition with a name if that condition is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   template <class CharT>
   shm_named_condition_any(open_only_t, const CharT *name)
      :  m_shmem  (open_only_t()
                  ,name
                  ,read_write
                  ,0
                  ,construct_func_t(DoOpen))
   {}

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~shm_named_condition_any()
   {}

   //!If there is a thread waiting on *this, change that
   //!thread's state to ready. Otherwise there is no effect.*/
   void notify_one()
   {  this->internal_cond().notify_one(); }

   //!Change the state of all threads waiting on *this to ready.
   //!If there are no waiting threads, notify_all() has no effect.
   void notify_all()
   {  this->internal_cond().notify_all(); }

   //!Releases the lock on the named_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), and then reacquires the lock.
   template <typename L>
   void wait(L& lock)
   {  this->internal_cond().wait(lock); }

   //!The same as:
   //!while (!pred()) wait(lock)
   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {  this->internal_cond().wait(lock, pred); }

   //!Releases the lock on the named_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), or until time abs_time is reached,
   //!and then reacquires the lock.
   //!Returns: false if time abs_time is reached, otherwise true.
   template <typename L, typename TimePoint>
   bool timed_wait(L& lock, const TimePoint &abs_time)
   {  return this->internal_cond().timed_wait(lock, abs_time); }

   //!The same as:   while (!pred()) {
   //!                  if (!timed_wait(lock, abs_time)) return pred();
   //!               } return true;
   template <typename L, typename TimePoint, typename Pr>
   bool timed_wait(L& lock, const TimePoint &abs_time, Pr pred)
   {  return this->internal_cond().timed_wait(lock, abs_time, pred); }

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
   template <class CharT>
   static bool remove(const CharT *name)
   {  return shared_memory_object::remove(name); }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:

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

   internal_condition &internal_cond()
   {  return *static_cast<internal_condition*>(m_shmem.get_user_address()); }

   friend class boost::interprocess::ipcdetail::interprocess_tester;
   void dont_close_on_destruction()
   {  interprocess_tester::dont_close_on_destruction(m_shmem);  }

   typedef ipcdetail::managed_open_or_create_impl<shared_memory_object, 0, true, false> open_create_impl_t;
   open_create_impl_t m_shmem;

   template <class T, class Arg> friend class boost::interprocess::ipcdetail::named_creation_functor;
   typedef boost::interprocess::ipcdetail::named_creation_functor<internal_condition> construct_func_t;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

}  //namespace ipcdetail
}  //namespace interprocess
}  //namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif // BOOST_INTERPROCESS_SHM_NAMED_CONDITION_ANY_HPP

/* named_condition_any.hpp
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
*/