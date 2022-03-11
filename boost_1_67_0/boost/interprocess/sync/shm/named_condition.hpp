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
   shm_named_condition(create_only_t create_only, const char *name, const permissions &perm = permissions());

   //!Opens or creates a global condition with a name.
   //!If the condition is created, this call is equivalent to
   //!shm_named_condition(create_only_t, ... )
   //!If the condition is already created, this call is equivalent
   //!shm_named_condition(open_only_t, ... )
   //!Does not throw
   shm_named_condition(open_or_create_t open_or_create, const char *name, const permissions &perm = permissions());

   //!Opens a global condition with a name if that condition is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   shm_named_condition(open_only_t open_only, const char *name);

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
   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time);

   //!The same as:   while (!pred()) {
   //!                  if (!timed_wait(lock, abs_time)) return pred();
   //!               } return true;
   template <typename L, typename Pr>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time, Pr pred);

   //!Erases a named condition from the system.
   //!Returns false on error. Never throws.
   static bool remove(const char *name);

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

template <typename L>
inline bool shm_named_condition::timed_wait
   (L& lock, const boost::posix_time::ptime &abs_time)
{  return this->internal_cond().timed_wait(lock, abs_time); }

template <typename L, typename Pr>
inline bool shm_named_condition::timed_wait
   (L& lock, const boost::posix_time::ptime &abs_time, Pr pred)
{  return this->internal_cond().timed_wait(lock, abs_time, pred); }

inline bool shm_named_condition::remove(const char *name)
{  return shared_memory_object::remove(name); }

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace ipcdetail
}  //namespace interprocess
}  //namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif // BOOST_INTERPROCESS_SHM_NAMED_CONDITION_HPP

/* named_condition.hpp
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
*/