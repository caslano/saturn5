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
YtwHiNtpl3AOF5MgJkW8wAwO1Mm/xX5w8k5eHNgzvIrlOPBNmi7V9yWb2Jt6HdpXrKUyh6waFQakToXvRgGbieWgUVWAL0SLo4iP8D8exh/Ki/PaciOk9MQZJoQ+KoImJwJX8mPtE3O9pvZerVs/mkmDWM5KfnSx8eAENZAGh2jHF8onAQnrx7EYVnslPjHEz0SaiUMGQuxxL3MV+UBFg2NDvu82diX2kYdOfAfBfVnq/CxkrL85gxziNtPw0nY/f5BZe6Euv4Fvz0ubZtHrlso7vrZnjN9Yx2pT28hR+mPS7OXIZou24YrKrEpU7owGVMw1m9Qw3HdtfzYayeNRTsd/x9hIClgTtCEUDNcNZi2Y8MXcj3poQVzG/qFedeWYTopeMI7jVfBekfgpFq3mkvu9LvmbsChjlThPjI14/gGDJVWaIxFgQfMH2qY5+9wPcrgPIXvox8PSQZmJH+KjHakk7eUfTXtLUhHEAI2kWbGnd6A/dBw63RsE5+YX+ixph0Z8lHrmfBVwcPjmifCJDxQGthyczlCMHGfeqZ21nLa0HQ7CkhwNqDfq5LOZLfi8BK9OcRBPKuAa+1zQ3f/xcbDzLnZYh/F6pwxucXrlBNPo2cs7kbnZKYNaSDVOxMV8s5DynY6rTQz0+ro7pKMddLkoaNF5jcW/ERw7colEPlgM6chUipWJ8XHy+Uj6NaUnpj1mli2o56h9jNob
*/