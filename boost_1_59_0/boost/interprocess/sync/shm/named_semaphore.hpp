 //////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_SHM_NAMED_SEMAPHORE_HPP
#define BOOST_INTERPROCESS_SHM_NAMED_SEMAPHORE_HPP

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
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/detail/managed_open_or_create_impl.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/interprocess/sync/shm/named_creation_functor.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

class shm_named_semaphore
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Non-copyable
   shm_named_semaphore();
   shm_named_semaphore(const shm_named_semaphore &);
   shm_named_semaphore &operator=(const shm_named_semaphore &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   shm_named_semaphore(create_only_t, const char *name, unsigned int initialCount, const permissions &perm = permissions());

   shm_named_semaphore(open_or_create_t, const char *name, unsigned int initialCount, const permissions &perm = permissions());

   shm_named_semaphore(open_only_t, const char *name);

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   shm_named_semaphore(create_only_t, const wchar_t *name, unsigned int initialCount, const permissions &perm = permissions());

   shm_named_semaphore(open_or_create_t, const wchar_t *name, unsigned int initialCount, const permissions &perm = permissions());

   shm_named_semaphore(open_only_t, const wchar_t *name);

   #endif   //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   ~shm_named_semaphore();

   void post();
   void wait();
   bool try_wait();
   template<class TimePoint> bool timed_wait(const TimePoint &abs_time);

   static bool remove(const char *name);

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   static bool remove(const wchar_t *name);

   #endif

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   friend class interprocess_tester;
   void dont_close_on_destruction();

   interprocess_semaphore *semaphore() const
   {  return static_cast<interprocess_semaphore*>(m_shmem.get_user_address()); }

   typedef ipcdetail::managed_open_or_create_impl<shared_memory_object, 0, true, false> open_create_impl_t;
   open_create_impl_t m_shmem;
   typedef named_creation_functor<interprocess_semaphore, unsigned> construct_func_t;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

inline shm_named_semaphore::~shm_named_semaphore()
{}

inline void shm_named_semaphore::dont_close_on_destruction()
{  interprocess_tester::dont_close_on_destruction(m_shmem);  }

inline shm_named_semaphore::shm_named_semaphore
   (create_only_t, const char *name, unsigned int initialCount, const permissions &perm)
   :  m_shmem  (create_only
               ,name
               ,sizeof(interprocess_semaphore) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(DoCreate, initialCount)
               ,perm)
{}

inline shm_named_semaphore::shm_named_semaphore
   (open_or_create_t, const char *name, unsigned int initialCount, const permissions &perm)
   :  m_shmem  (open_or_create
               ,name
               ,sizeof(interprocess_semaphore) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(DoOpenOrCreate, initialCount)
               ,perm)
{}

inline shm_named_semaphore::shm_named_semaphore
   (open_only_t, const char *name)
   :  m_shmem  (open_only
               ,name
               ,read_write
               ,0
               ,construct_func_t(DoOpen, 0))
{}

#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline shm_named_semaphore::shm_named_semaphore
   (create_only_t, const wchar_t *name, unsigned int initialCount, const permissions &perm)
   :  m_shmem  (create_only
               ,name
               ,sizeof(interprocess_semaphore) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(DoCreate, initialCount)
               ,perm)
{}

inline shm_named_semaphore::shm_named_semaphore
   (open_or_create_t, const wchar_t *name, unsigned int initialCount, const permissions &perm)
   :  m_shmem  (open_or_create
               ,name
               ,sizeof(interprocess_semaphore) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(DoOpenOrCreate, initialCount)
               ,perm)
{}

inline shm_named_semaphore::shm_named_semaphore
   (open_only_t, const wchar_t *name)
   :  m_shmem  (open_only
               ,name
               ,read_write
               ,0
               ,construct_func_t(DoOpen, 0))
{}

#endif   //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline void shm_named_semaphore::post()
{  semaphore()->post();   }

inline void shm_named_semaphore::wait()
{  semaphore()->wait();   }

inline bool shm_named_semaphore::try_wait()
{  return semaphore()->try_wait();   }

template<class TimePoint>
inline bool shm_named_semaphore::timed_wait(const TimePoint &abs_time)
{  return semaphore()->timed_wait(abs_time); }

inline bool shm_named_semaphore::remove(const char *name)
{  return shared_memory_object::remove(name); }

#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline bool shm_named_semaphore::remove(const wchar_t *name)
{  return shared_memory_object::remove(name); }

#endif

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_SHM_NAMED_SEMAPHORE_HPP

/* named_semaphore.hpp
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
*/