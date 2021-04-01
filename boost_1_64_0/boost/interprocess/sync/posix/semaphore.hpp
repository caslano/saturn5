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
db72AACIFSIX+vSEMWyznLpg3Ni404v5f0p2uCqZ0r2PJ2vtVfgaq1kxjuWY+SUp4ZhS2zdA2nG7LiegtII0JhaGECttPeIfBubW9VWZ+qQkXnmnf9XE1gh9TMztwNKHLwus9FUhZ/8lvOGQIrH21uPR6ERz1evK4WNa2P5vUGIPaL95/Zsb+Mtf1RX6elkS3vLtyuDG9XkQOShV7SUYVRJfh4uRhPtW26RaYIcXthYbxUozKiMzwSVkhWNkB/KYnjFb4UgngW7KgAOIaz4ThwMjmzl9/NSXvy+74iz0FNDfuK7bkIKFzWAhfVIxAklM6SFFAVSPGCPiXFHEUBh8/gXBZCEC6eGtXWD682bUKQ08RFxp77Ksrrz1Ooi3UQDrkQDAruWfGYzA4qhyxh9CTIHUjCBSdbhpM6T4hJppkeumMJVD+TVfUl/udbSa87ifKWKJ9SwbjASaXXgV2T1EG93VHljmRlIcb67AXW2ijM6inPZAlYd4VGW2uWMNE7Cf8dsINoPXiSvMG6Qxap2Nw7ExjxLV7ElzcmIiGLo9r6ipdkwWHTmjREIrwg==
*/