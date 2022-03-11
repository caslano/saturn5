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
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
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

   ~shm_named_semaphore();

   void post();
   void wait();
   bool try_wait();
   bool timed_wait(const boost::posix_time::ptime &abs_time);

   static bool remove(const char *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   friend class interprocess_tester;
   void dont_close_on_destruction();

   interprocess_semaphore *semaphore() const
   {  return static_cast<interprocess_semaphore*>(m_shmem.get_user_address()); }

   typedef ipcdetail::managed_open_or_create_impl<shared_memory_object, 0, true, false> open_create_impl_t;
   open_create_impl_t m_shmem;
   typedef named_creation_functor<interprocess_semaphore, int> construct_func_t;
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

inline void shm_named_semaphore::post()
{  semaphore()->post();   }

inline void shm_named_semaphore::wait()
{  semaphore()->wait();   }

inline bool shm_named_semaphore::try_wait()
{  return semaphore()->try_wait();   }

inline bool shm_named_semaphore::timed_wait(const boost::posix_time::ptime &abs_time)
{  return semaphore()->timed_wait(abs_time); }

inline bool shm_named_semaphore::remove(const char *name)
{  return shared_memory_object::remove(name); }

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_SHM_NAMED_SEMAPHORE_HPP

/* named_semaphore.hpp
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
*/