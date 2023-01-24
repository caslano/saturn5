//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_SPIN_SEMAPHORE_HPP
#define BOOST_INTERPROCESS_DETAIL_SPIN_SEMAPHORE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/atomic.hpp>
#include <boost/interprocess/detail/os_thread_functions.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/sync/detail/common_algorithms.hpp>
#include <boost/interprocess/sync/detail/locks.hpp>
#include <boost/cstdint.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

class spin_semaphore
{
   spin_semaphore(const spin_semaphore &);
   spin_semaphore &operator=(const spin_semaphore &);

   public:
   spin_semaphore(unsigned int initialCount);
   ~spin_semaphore();

   void post();
   void wait();
   bool try_wait();
   bool timed_wait(const boost::posix_time::ptime &abs_time);

//   int get_count() const;
   private:
   volatile boost::uint32_t m_count;
};


inline spin_semaphore::~spin_semaphore()
{}

inline spin_semaphore::spin_semaphore(unsigned int initialCount)
{  ipcdetail::atomic_write32(&this->m_count, boost::uint32_t(initialCount));  }

inline void spin_semaphore::post()
{
   ipcdetail::atomic_inc32(&m_count);
}

inline void spin_semaphore::wait()
{
   ipcdetail::lock_to_wait<spin_semaphore> lw(*this);
   return ipcdetail::try_based_lock(lw);
}

inline bool spin_semaphore::try_wait()
{
   return ipcdetail::atomic_add_unless32(&m_count, boost::uint32_t(-1), boost::uint32_t(0));
}

inline bool spin_semaphore::timed_wait(const boost::posix_time::ptime &abs_time)
{
   ipcdetail::lock_to_wait<spin_semaphore> lw(*this);
   return ipcdetail::try_based_timed_lock(lw, abs_time);
}

//inline int spin_semaphore::get_count() const
//{
   //return (int)ipcdetail::atomic_read32(&m_count);
//}

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_SPIN_SEMAPHORE_HPP

/* semaphore.hpp
dq9cBSqO2D4e3SH4qsxftMVlryTdl6iyw1nmFSgDleZX1grRXubIXfl2X6pcmLeYAJ1fDA+WOz2dejZ2eY+BV1rtjSKnd3lXmdqmJOSEFOZmXlmOoe/3AwXJg3a8/dt8ZuTt4rQGaxzLyRCJhBv0vUJTkb84yl4pN1V2u1WukXhl5Jtv6PL9QVq41W59HXNANxefwzgBs68KnfetdiUYWeu81LeInXT1ntrtpPcTWTU8GF10bfsG0g+mMPUt+qYbnXWv+yYChRrmjB/f165QeoHeIiazPcu+yEf1TF84BsZ886dOzEu6MFoqyqsYDNY+/qjX09Unsx9j0Zv7huivS2SxjVEj3rVz0gPEKMBPUUFOYdKJ0dhlfgRqIL9ivfpgi1DIvLZ64bSkuv85F7YKlvwGYmJxEl9NoWc5PhtUp4MpA0COObY5CxL+1kmzmB2Il0qPSo87hjN1RcZ3Lzr8hTXQz9szzD5wrXHOSDLogwkT1yhB/hmxa4Z/bDJ67iPtqd78XEqec01+WW7wwo7EQI+XfQe3XUL5X4wr7hN0bq2SKfdzkS9YizSk8XeXJOPsPrjujAP6TUa6xFF9YpwtVG643myhmFRHjMbsNr9RC1FCzLujozGAMX98aBsxdakHVa55n977qSXM37jFpj4aHsnVz/y+pjr0ZZoI83TFEU0fvYMQCvVjNwPWklf7uKK3votZiZmJWYqZi1nD
*/