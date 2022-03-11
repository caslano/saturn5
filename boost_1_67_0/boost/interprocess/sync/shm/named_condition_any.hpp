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
#include <boost/static_assert.hpp>
#include <boost/interprocess/detail/type_traits.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/detail/managed_open_or_create_impl.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
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
   shm_named_condition_any(create_only_t create_only, const char *name, const permissions &perm = permissions())
      :  m_shmem  (create_only
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
   shm_named_condition_any(open_or_create_t open_or_create, const char *name, const permissions &perm = permissions())
      :  m_shmem  (open_or_create
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
   shm_named_condition_any(open_only_t open_only, const char *name)
      :  m_shmem  (open_only
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
   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {  return this->internal_cond().timed_wait(lock, abs_time); }

   //!The same as:   while (!pred()) {
   //!                  if (!timed_wait(lock, abs_time)) return pred();
   //!               } return true;
   template <typename L, typename Pr>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time, Pr pred)
   {  return this->internal_cond().timed_wait(lock, abs_time, pred); }

   //!Erases a named condition from the system.
   //!Returns false on error. Never throws.
   static bool remove(const char *name)
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