//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_SPIN_MUTEX_HPP
#define BOOST_INTERPROCESS_DETAIL_SPIN_MUTEX_HPP

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
#include <boost/assert.hpp>
#include <boost/interprocess/detail/atomic.hpp>
#include <boost/cstdint.hpp>
#include <boost/interprocess/detail/os_thread_functions.hpp>
#include <boost/interprocess/sync/detail/common_algorithms.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

class spin_mutex
{
   spin_mutex(const spin_mutex &);
   spin_mutex &operator=(const spin_mutex &);
   public:

   spin_mutex();
   ~spin_mutex();

   void lock();
   bool try_lock();
   bool timed_lock(const boost::posix_time::ptime &abs_time);
   void unlock();
   void take_ownership(){}
   private:
   volatile boost::uint32_t m_s;
};

inline spin_mutex::spin_mutex()
   : m_s(0)
{
   //Note that this class is initialized to zero.
   //So zeroed memory can be interpreted as an
   //initialized mutex
}

inline spin_mutex::~spin_mutex()
{
   //Trivial destructor
}

inline void spin_mutex::lock(void)
{
#ifdef BOOST_INTERPROCESS_ENABLE_TIMEOUT_WHEN_LOCKING
	boost::posix_time::ptime wait_time
		= microsec_clock::universal_time()
		+ boost::posix_time::milliseconds(BOOST_INTERPROCESS_TIMEOUT_WHEN_LOCKING_DURATION_MS);
	if (!timed_lock(wait_time))
	{
		throw interprocess_exception(timeout_when_locking_error
			, "Interprocess mutex timeout when locking. Possible deadlock: "
			"owner died without unlocking?");
	}
#else
   return ipcdetail::try_based_lock(*this);
#endif
}

inline bool spin_mutex::try_lock(void)
{
   boost::uint32_t prev_s = ipcdetail::atomic_cas32(const_cast<boost::uint32_t*>(&m_s), 1, 0);
   return m_s == 1 && prev_s == 0;
}

inline bool spin_mutex::timed_lock(const boost::posix_time::ptime &abs_time)
{  return ipcdetail::try_based_timed_lock(*this, abs_time); }

inline void spin_mutex::unlock(void)
{  ipcdetail::atomic_cas32(const_cast<boost::uint32_t*>(&m_s), 0, 1);   }

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_SPIN_MUTEX_HPP

/* mutex.hpp
qenmPNTpAz1/SUJyoKnRqc16Kp2fmreyhWelZjk1F4/SZ936rari5DOq7x6Xtdh1pp9+pHKAVTNqzbJEBiNqJ6gdgd27dUKIx2saOfBK9hygHEX8dP7kS5mehUhb05DUbR9CDqqA221BtM9tmBYxJw/uZiAvGUXEY1nqnHaKx8atsjhbRFAxWnH6ZOpySk6dvqADTS51PNtfJwyLux3bGccUiTuLf4Z9aFZdc1nEDxNc5mxkKsCT4wq0ds8iXOMQYbRSN7gO+0XWWvJkzp/liTJWVemqCcIm/xOjkqUxEosq9AJJI2xN+fiCrDHdVeuo/hiHLyRFa2db/Uw8Vp6UJJLJ7gkgKtadsfAXKG2tAJuNu+ZY0mUUvyjAK81kOdk8/ITIGdwRctcV6e2nsasGWVy8hVkw242GvBSDueuk2u940/ZPoqDdOaOcJS+dJSNoX89jUznletWU1FKVtcsHtXPdDGuN5Gaa/6piwx2fU6D9+a8IGSlSpLa9R0n37dIc6WrftPT/CggAjOuJl+DbR00jSwd9VSiCN3NXNyetMLMnJeS+9zVznKg9yayj1lNJ5VADONio5GpuHMpoKfu/txfocEVKwR2Hn6p61bxoLrFlZuClm5MqbRbqEzmSQgPI4h5wkqRw2lvH+0O/srIW1+ZHTMv93piyBLKzPcb4qzDrKbft60amKE9zu9ClxjdhgjAFyZJHXFZz4kgY
*/