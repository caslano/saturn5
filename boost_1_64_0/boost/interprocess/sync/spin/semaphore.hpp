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
S0NqiRO7sTRJvrIEfG2pNhaj9OjUuHgM4DDgZ63HYdj4Cxt38etDMdgLYi70eAs91sLGVoxF0uMpbCyFjaNw4yVsrIQLJwGMhIqLcOMhTkZy4CAcGAg3/mEzpEokYB2Ic7AxDsQ3ENuAv5fYuAYb05AYz3AyKPELrjiKJ98NmUCXY38ZqBuj4B0zcbMlKj4hFpPwSpmKRcA+0q9I5cgT2gqygBKLkDQOwRuDkBh/QNyBYA4GgrpxBv4wBm+AAlsATIGNJTgZSYchmIS0DH+/j6TiBRYgESdgYQRK8LeKDVBxARMw7uYgzUe6G6kdKeMYrKGFNBYpgjQf6W6kV5CWIw3EDf4opHFItUgnI92O9MbcACcQbMEWbMEWbMEWbMEWbMEWbMEWbMH2V21/n/9/99f+K4Rfe8kgfOsosv3/EWOzwvR0Gopzi8z4t7HnLFxAAfPOHRI9L9mkzNUHIqaeddzKIliC3ZW1Bls1WIIHB+P4Q/R5YaUqjuB+b98M5Os6jgDlEkdg++SUpuhxBJHFsfL5wRDMGOLCEFj6mK/BELRCrnaHPnziB8x20reH7Up1633xYPwsseupbook9I8Cf4y+98hNLEc8H6gnNXIdgp1iRS6aAmXztAXk8WULGl+iqhg/mTw6NazIDEORHjXxHUscvqQNM/etq2psqqc/x1Kx1wiO2r6YoyVPtk5ultdL8j7cmbeqVsk7Uc731fo+MK/qHyb5cnFurJwboPM9Qr7k/MWifhJmm/KlTbafxMNyjLLS56hG46P3HfXY17BpGwSJxOqxomaOBJtW+rlepy/kSz62ZsRhE5N822u9d3xftu/CdL0fX7OjfZaZVNSZzpkJffqaHbJvlsSY1/r3Uc6M3vq5bYEtJ+anxGMmOq+94prX7Lpm9HbPa4+bPuJKXZjSfM9nUZual+G2qaehuDal/AYfNtXmw6ZU3tSQzEf1+2p9/MDr6MPJPWR/UR8/1I9jqN8x3y/o4/aDHAmh2pfE+EGKXk7P85xTwe/D93GJD9/HJb58H2Pm6tPz/Ps+8npjLTR7C9KqSDdTL8bSGL2I26OiG8vPNV/45sO/JF2nL5Tj1FckInJxTaMsOX8xYjOmydoVGVaeVWxdKuXkqLrct3GGup7Q3sKTYq1jtInsNxkr49h0JI3ebfk4HtR1gAeC7iTnK+Av0BvtF/96bAeY50WOveT8RNjVSEv+VeTYKeDhuhziKyjlCs+vWFNliPCcJX7VV8A2yzOBy8iCTPkbhFOhWNsOiOciXyP4HsiS9XyOtq7r5Inu78kxFYq7/k5a9mFLXTgsvS2xzwoctmTrX/WzPyBmXipewT3unjHv51T74j1d9J7mKe/7W+TzMf6W+hh/S32Nv5h56aku+B5zXoI/vdv3+FmUZzwc43uc8F7PeNiHv/HDvvyNtfeFen9je16ZwNLuQuqFdCfbVay0i/OK2jZr3G0mfDUYWan6e1tXeyMxmMlV5fwtRh1+L0PKkbEZzXcr4qceaevELs8es6p9U6ZLhWcVqbM4ZK3fZJW9vZw/FSX3NYZhvP6Kvm3vjzkC8qUOTE8BxnYGfrPS+4ZTkN3S/xSc96o3D3RHKXcla32cWtkvge9KFo6Bxzq2J/x9UlgW5UNx6hw5Tfj6WGXVyf5q2M+SuSgEed9A2hsyhbMHxuBTmjnPqOuYY10ead+FQhOvYx7fjqQPrWPQMdedcmBANf76z5v4+0dU2+KcksQzc9YjyY+drEe6PnYgg37sONpXlmM9X8k2hGOn1G4f7pmliY1TG/RrD44S3gJde1GObuzo20tesY2NUPBypH2QJ9w3FM7IdttGsnMmn321/a/iCIrpoHUg5Wk=
*/