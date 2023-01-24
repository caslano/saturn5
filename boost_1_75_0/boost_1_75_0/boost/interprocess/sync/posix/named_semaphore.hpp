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
i9xfhxSZNu/a9a+8Es5676BQ8WqO5PztHH1ziPBY9N56xUyB/kPTevvZi4lX5VsavFkw/A6vHmuT5fTDmQeCGfcWGsiE1ayXBnPVqgKOn/4S/sCZlzKpSQzNnFixisykm71JOO08/cN5RBcgD2QOAAEqrG+vrRxVTBZFhG/Dzv+4WE1Qnu7MiW01HPhu/4LtLxcPB6/NhEtKEKzqkDprhG5+sKFSlPeZbzV5Hz2f6Exe0aD0x8VzYw+KUxctSnJTvZf60JrvhJdswTZesA9t2E6aTQtNCzpNlgY2OIASx+hZ4lme+J9y2xEGrsJFppr0F/2RYLqAEAqBxMMnVXXoxs6xdNCSvy/7iPj6vmeME0FF/+GHYGM/fQhBJPvtiteRqv9cdNO2bGG18DSExHV1CdL+/Pu+O+GMVvQmSjJbEqPP06Wsrbr6R3mWHof1SraQ8+TFym5EexjD8c0nigPvjMZGoRYeJyd397DpQmeqbKxVwgqFc+E4HysXf3dvvZz1nT4mHd+G6j8mv1rP+laGaauhyDPWWMJxquvH0b/1K+9bo2mDQJ4PXrfZ73bzZgZh3iexxko2/5Po/aIoS4wHnrNMdza38kqQaohsyXefEd96d5cTakiTSbvwOB+zTeu++m3zB4eQSPgQj1sKjFNVwQAhpxGgEOvypx9DQV9tV3fW9G4itGE2MUMT1n8c6WMC1LycuOPoMUpnb2c2
*/