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
3AOWgS+ClWAD+BHwZfBj4D7wLvAV8LPgAXAb+KqdH/A18Pvgr8E9mo7XwTfBI+Bh8I+STnc/D5nL1Lnauub7eQg/qawDAVPA5dpvrgAngBU2BvDXfqISvBm8EaxSftI7QFvvE8pf+inxd/ljZZ5C51Xqwvhjj1tN/cdfwRTwHbC3ujPBt8Ec9R8F/h08HzwJzgLfBa8D/wXeoHq3gzHar8Yq/24C+E2wi/IA/xO9b4vbfd7IWDkYCPifN/S10p7SwFFgb9BORyY4Qd356v6R6v0ezAKPgX3Bv4F9wHfF7ZaPjAWCRwzlMxm9GOXH6wteDvZXPtvh4FV63bngNHCePufmg5V6/g5wJngPWAhuVH69+9T/i+q/GbwUfAOcBb4l/i5/tYzv6NhTXRh/9cf0ef9xMFH5m9PAe8CB4EZwBPgJcLTyNo9V3uZLlLf5StUvBGv0ufx5cI3yP1cp//Odyt/8cfBLmu4vgw+q/kPgV8Ba8KvgD8CvgU+DW5Xf9wHwNfDryov9DfCv4KNg3/jWeQc3ITurzNyCw4bGevgFlVtQeQWt8/87fIL/TS7BsqGxp4RPsD1cgm3lEfTzB4ZzB0bPGxgNZ6DyBfq4AjcNjW0TX2DVqtgwvsC2cwVG4gmMm+TyA9aTLuUIVH7AjnEDmngBj3KN5tyA0fECdpQTcPOq2FPOC2jiBKzlOi4vYMc4ARuI6ziSWQlnHzIPWYdsReqRE8jA1bHWTKQS2YLsRo4jfdfAuYcUIuuQLcizyDEk80biQ2YiS5FqZAfScGMnv17nr/P3fvi9d/x/zMudIv6/D6Xyra18Yo3a1fwE0b2DrFuYN8jdJ3OdsmDbNiyWyzdbYyqnnHnHq0X/SjO/0r6W12DNkfNf4bs01jDn6YZPce0FKbIVzhrINHC26Hydb9gY47oBjSOi3cojcn4q60UyjGsJNHzYPKlrszhJzteSXmb2kRC33VKdnwh2K/PYLIZz4LhrBWokHpcP8GVxd2/Gl2fvzXqGcJtdKdcpw70FOV/9QteZpvaETljlys+x9ZKrHvDyiHl1+lInxjfNh34uPM1TDGl+Joo05xPnBU22UBtcWyjv3L+syaZmtz6/ms6aa7lG001YKIR+vjUBUj+Na8rSvWsC3LoUaV2A01YalLhhsdbLEuRuu6284rYVm/lHG4uU1wa3rZjbxitu3X7eULfTwUtFZxr7j3Uxt49XjHb55nbwSuT1jBfIuauwyIkPq+duO/mw6IxhPVsXZ41qgfiNs5LwzbbtW+36Ex9aW5XIGlxZYWVcW5Wu+sXxobVVObaZa8S1qqNSWq8foXqwwa0Hjj3r87577rPRl3s+QteCbE3QPVuagGtzTIezo+meS/0rWl4h5XlamtiPmu6z6gc8etcZ7qWr5+a3dY6/Hppf4rVt/MSd6Livk/yE+F4HK99fD42gu3IlNTblR40HQ9myeZKa7Jq3JZCPLqE+xvL1MeY0uut1vO2oXtOQpgqpypNo7felQfiHwtaLmcqXsG3iRpzRMjeitnfltFun8zS3IPdSVjn+dMq6Ok572/yaskjciPvd9vq8my9DfXB13bbt2hGngQVy/hxZ52ho7xre3N7z5dwE5j/j5fxHs2SVrbMeb5Ccr7Su5P9aJN1Z3+bamHqfA1eLfhfpAxq6EH9XXR8W20f6gEGR1leqfnFXXR/WNTfy+rAUW6Ln6pQ+QO9FitsH6P0Ob/9kKIx3RSbsDfyYdeS1I/yYdfvbzy8UiR+zLEmUffyY9VyrI/yY9fuj5xiq399+jqFo+DFDnCiNhrx+2u7H9kfiXOw451u9gQfwU7atbsRrCo9YVPyWEof7jhyZR0x0288j5uU=
*/