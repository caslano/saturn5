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
D58Mqk4zXHiXSN6jmn0P1RQTu52EnWI2jbQ6rzVkK89pACtl7p0065cJtRDpyvLxPHCDSN7LUmn4tRFi4XSLnB/0jhDUJLsuVluis9Z68J028usaIVVonvKauJfm98F6RcocjfVg92xqBzlklRdwwaIO2kpTf4D1+tuqqzy7i/NlEqv+u8t5Mn17f5lN4yJiFIyjM6XA25F26z9QSwMECgAAAAgALWdKUjvFQ2JiEgAAdUsCADIACQBjdXJsLW1hc3Rlci9wcm9qZWN0cy9XaW5kb3dzL1ZDMTIvbGliL2xpYmN1cmwudG1wbFVUBQABtkgkYO1dbW+jSBL+Pr/CsuY0kw9jZzLZ7O6N41XGTiaW8nZxkt2TRoqI3Um4xWABnkn29v77NRj8ChiaprvBj7QvAUPT/VTxVFd1ddH67WVk1L4T29Et87D+sbFbrxFzYA118+mwPnEfP/xS/639pnVlW/8hA7fWJY/axHBvNPuJuM5h/ctEN4b12o1lGc7drJU9rxnasEmveHbd8T+bTWfwTEaa0xjpA9tyrEe3MbBGzSH5TgxrTOzmyHnwmmru7e5+qrff1GqtnktGX21rMq6daQ/EOKwHfehY5qP+NLE1lz7M8a+lV0f9WOuZA2MyJIf17tkZ7frD5Kn2
*/