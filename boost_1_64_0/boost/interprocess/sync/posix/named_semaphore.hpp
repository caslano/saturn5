//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_POSIX_NAMED_CONDITION_HPP
#define BOOST_INTERPROCESS_POSIX_NAMED_CONDITION_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/sync/posix/semaphore_wrapper.hpp>

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
namespace ipcdetail{ class interprocess_tester; }
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

namespace ipcdetail {

class posix_named_semaphore
{
   posix_named_semaphore();
   posix_named_semaphore(const posix_named_semaphore&);
   posix_named_semaphore &operator= (const posix_named_semaphore &);

   public:
   posix_named_semaphore
      (create_only_t, const char *name, unsigned int initialCount, const permissions &perm = permissions())
   {  semaphore_open(mp_sem, DoCreate, name, initialCount, perm);   }

   posix_named_semaphore(open_or_create_t, const char *name, unsigned int initialCount, const permissions &perm = permissions())
   {  semaphore_open(mp_sem, DoOpenOrCreate, name, initialCount, perm);   }

   posix_named_semaphore(open_only_t, const char *name)
   {  semaphore_open(mp_sem, DoOpen, name);   }

   ~posix_named_semaphore()
   {
      if(mp_sem != BOOST_INTERPROCESS_POSIX_SEM_FAILED)
         semaphore_close(mp_sem);
   }

   void post()
   {  semaphore_post(mp_sem); }

   void wait()
   {  semaphore_wait(mp_sem); }

   bool try_wait()
   {  return semaphore_try_wait(mp_sem); }

   bool timed_wait(const boost::posix_time::ptime &abs_time)
   {  return semaphore_timed_wait(mp_sem, abs_time); }

   static bool remove(const char *name)
   {  return semaphore_unlink(name);   }

   private:
   friend class ipcdetail::interprocess_tester;
   void dont_close_on_destruction()
   {  mp_sem = BOOST_INTERPROCESS_POSIX_SEM_FAILED; }

   sem_t      *mp_sem;
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_POSIX_NAMED_CONDITION_HPP

/* named_semaphore.hpp
GvfcTNP4tXpzatOhD5c5isqqlJYpkub9ssvhaVaFYtoT2unqoaXsSJJatlDgXzrjtcJAlaqVAwjjtmqI75gsLaqn/Feqp9/eeFyxAwg+tfL1DwReZyJ8SSbm246fLcujvM0tJC93TeSDJauApnR19yRWAfCJG9v83bfMNjJoh1JQ1Rj6rKOzQ/782AwcHkpCTPSNcwH7PxkaEwPJy5jOs4e6G52oDKDHXC68jYadY4xqQ5HUFEGFLVY8EfxK1AWkj3vl6fb6Kravu02ttneaDTGFTt79Va/jsdbVFLQysl8k5H47TtPVQ4KzTe6Gvkb6PMZurkYxM1kaDZRip6vvxf4EUrtFNd2o3MsJI4ZCQZ5Ov/q0gEtiqC/0RTqgx3GF6iF2YoyX34BL1x36pTke4u6Z2RZbi56QqnEKbdod96HR3pAFXpRhgPqBtWLA8eDZiTuU564oHjXqRg5aDkD+DWKa2NKzxzAI79reF0zSjwCQiNygj6oIUfQSczYCN93L21i7zMx19DS3R53OaHpy1ZtjLrwokdd400x6f/IHx4mSUp63lalZnhuomw==
*/