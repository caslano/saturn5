//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_POSIX_SEMAPHORE_HPP
#define BOOST_INTERPROCESS_POSIX_SEMAPHORE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/sync/posix/semaphore_wrapper.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

class posix_semaphore
{
   posix_semaphore();
   posix_semaphore(const posix_semaphore&);
   posix_semaphore &operator= (const posix_semaphore &);

   public:
   posix_semaphore(unsigned int initialCount)
   {  semaphore_init(&m_sem, initialCount);  }

   ~posix_semaphore()
   {  semaphore_destroy(&m_sem);  }

   void post()
   {  semaphore_post(&m_sem); }

   void wait()
   {  semaphore_wait(&m_sem); }

   bool try_wait()
   {  return semaphore_try_wait(&m_sem); }

   bool timed_wait(const boost::posix_time::ptime &abs_time)
   {  return semaphore_timed_wait(&m_sem, abs_time); }

   private:
   sem_t       m_sem;
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_POSIX_SEMAPHORE_HPP

/* semaphore.hpp
1eYBt7ogN3j0J1eZoWTASQPn5irffmhb7ukjbhXVCbtXjY2PrFEY1zqohErL/ZmL4iMyF27DGvSuKTi+Tt1zFDqeNbj9NUcmyQRJhzJ2ObY1ewpvoNfHZxeFMapr7LzQG7AdaL0Se+tP9XXsKG9w288b3jffV08c9/a55ZMms2/u+S/BMypQVPef/PZYQAlaM8wIKsOvMJvikOz8vvYrzGAKIuKDQ6V7nCd87Vok72SfliQmRPzwcmc+rtBs8lGVzoJdsgfXy8ciQbz8HWTzKqzUqPdg52p+BHqQMfddpKRC0Ekuz/APmsFyJiPHcqiSUB2sB3bzYenf2zz2onVs6RNt2cIRqSO19ryu2C5T267YMVMy0lN3uWafs0T4k+bEWB2ifmMrggGjPuKPie3aWaODOWNDtz1x6wHjLbHnRQ9AJgqbR9U34aWvkK4C2A07W8agCulrIly8p13OIOAOfuj+mFnG9ijnE0puWDC5+YOpiulv3Aybbe7SS1Sfe4rDg1TglXYUDFeaki42N0mK0p1zm/Ezcs8W6LGPyWsIphwBGI7WEuQRARh5LGzcy6KBfC1VL5Drikeh2Z2X2i2Uc0iUfeRPlEwb75VF4OvZ5gbf5b+QYMFd90RB6J/SQtl17k9mEw/LLzqSGbVPNpmNwCO7PQRUnFOpPcu4/ERpx087KNpfBaxIH/P6Kw8mJEyl+ZHRfYMKGECD+rQQ
*/