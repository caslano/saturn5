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
7K4cPJf7bTBTOI+aewRRRvN7TMa1n8M5WOd+NXg7OAxcAQ4HPwJHgJ9QP9NbHl4FfgPOAr8FrwYPgHmgS7SfwQhwDBgFjgVjwEIwFhwPNgAngI3Aa3h8cCKYAhaDzcESsCXoAbPAKWAbcCp4HjiD3/v1YG9QhOdicDrYn8yynqb9bzyeMMOvnm5qHYcKUi5XyiG/+co1dEq50UHKeYKUKw9SbkmQchVByq0MUm5tkHJbgpSrDFKuKkg5LS2wXIhFLiZIuZQg5bKDlOsZpFxukHKjg5TzBClXbpGr9JPLt84/BCG30cFr0XgN3nbwChp/8srNwHOTwJvA88SzwcvB2eBAMNnlHd+cB3M5eDO4ELwFvA28DXwaXAQ+By4G14J3gNvAO//J3vnAZ1WVcfy++8dgLzC2sX8gTEQB+ePAIZAIQ/knIkxFQUIZbgMmg00YiIo2jZQUaxXWKkoqNEpUStKZVEstsTCHTYRCm0WKREVFhoXV9z573nvv3nve7d1Glrn383ne3z3nPufcc84959x7zznP74Dy3gS+A24CAwGei2ACuBlMB78C5oBfBgeDD4AF4EPgHHA7WAw+DFaBj4BfBB+zrw/uBL8Hfgf8Mfg4+CpYC/4W/CGYRZ6fBs8Bd4N54E/AceAL4FTwZ+Bc8CXwVnA/uAn8BbgN/CVYB74O/hr8Nfgm+BvwKPgm+C/wMNg7lvd5cBD4R3Ai+FfwKfAfdvrAk3Y84Lt2PGCA8rbJILqDg0C73CeBabjnglngEjAbXAv2AW8D+4L3go/a6QR3gD8FvwW+AD4DHgZ/BHaN53sI7AEeBM8CXwOngb8CZ4Jd7O95sBs4H3wb/8XgO+BS8Bi4HPwLWA4eASvB34NrwBh7vAOMBW8Ff45/DdgAPgm+DH4ffBI8AH4XfA38LPg2WANmUV8/D/YD+3rG2bZovc8wjLNN1OdsPpgOTgq44epaCHexhpuh4S4B8xI4T+XIR5YiNcge5CSSy4vCAmTt32OsagbndyKbcB8ErSWx1mCksDbG2vREjDWWyYp5yCZku318e4y1GzyI/jHbD50y/KqRWiR5Ftd4OoaP6hjrWc71Ba07YqxMpILjKmQ8x2PRm4dstv3AGqQQ/1qwFr/94G7wBBhkomQD57Yie5CD+A/D7yTHwY/GWNM5zgGP4Z82nrBcdzA4GamYDXKuGpyDey3HxWAt7kZkM+6dSANyAhm7Hj1kYAHhkA3oLgXX41djh+d4F7gd92EweAH++O1A0j5GfnGPBwuR+gKOcR8D1+LehMzEvQDJZNKnEtyG30ZwN7gNzMV/F7iTN8MCjg/jv9ZG/DaBJ+ywd3J9jp9F0iZQFkghfuPBo0+gz3E1Uoh7G3gYvd1goj3BhF/mXZQPx/nIWI4Ta0k3Mo/jHZwvtvU4rkH6Mvhdh18jsgv3MTAP3ZyJlD/utehuRibjrgMLwbgryBs4DJyM7tgN5AXZiF+VfYx/BVLDcTW403ajtx/cPBE9jus5t53jo+AJ/OM+Th5wDwaPg3H5pA0ZhsxECvAvBjPnUE8IX2mfm4M/sp7j8eRjE7jUPg9uQr8BOYrswl01Bz8k7W7SYccJ7iKe4xzvxL/Q9gerwZNgAfHFTSLdYM6V5BMpRDYg9YTbBuZw/jDHueBu3I3ISaSOOPLxS7uKdCFlHC8Aq5AtyCHOV+FXg5ysRR+//ciuSSByAsm9h7rHi701l7RynGxPxoBbkUz8doF5YF90hiH5yBzk2UtirUbOzePcWmQzUosUc24/uAGsQWqR3chR/BI30uY4HgwmziPv4ECwEtyIzOS4DNlhu8EGW+8idJA8ZAt+k8HMe7kumAvuxm8OuBYZT9o=
*/