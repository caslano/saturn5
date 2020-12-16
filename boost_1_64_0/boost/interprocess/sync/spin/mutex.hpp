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
85DtTZvaXVbE/U01XMDVM+9vil779zclXnd/U8d9XbP7mmvYo+8p9JL3Nh+HljFoD7ftk1mt8KXubb8dDHEb90EbbNhf7+fo5vjS6h8vv7eV9BKHu69wauvj5Tl72z9eTlp84+VcM2y83L1HaYZ99n5EHLmmfEvVje4e5e6N3u4nd2/77X6ezGrd7seZf+pp5rTN3xuJ01Ze3aLitM3fGz2nbf7e9u+hGA2nbSi/uwz5fdB+HkTMrzunemNW63soFuxt/x6KxB+2h6I7f1Vr2JOwmHQXRky30yKjuleFnvZ4T1br7bGwA+2RtPjaI9eMyDO9rZe5jlbs7TjvckUb6mjF3v8s73LoXm9O8ef3esJXRcxvc/vDxa3kuaoN/VBVB/qhxafA/vD9zjXdo8T2H7Qt/84Xln7hWz+84Pr51/xozfc/eHOXH8Q5ymJLfjLWNB38J7Lcc3yr53iMh4P6Yve4GTd1f8/xDPdY5jetgI4l6ljpfuUnOG6f03nKGHAAmKD2ct3UPq4HmAMm6/le6p+h7kHgQHCM8lFPVPu4Ap3XnAsOAZeCZ+u84zk6v5ir84t54F3gaJ1PHAtu03geV57qHygv9V6dn3xF5yd/qzzVb+k85Ts6T2lndiqYAE5z7fJ0/Ed0rP1h87x1mu9nwJ7gs5q/H4HDwB+D54C7df/E58B8cbv2iDIGAozS+L32iN/QeeRv6jzydi3Xh9UO8RFwJPhoKL0B8qrxfU3v22BdgxayO01S+9Fs8AqwP/ggeAY4B8wDrwQ/pP4TwavB2WqXebnaZZaA14DLwCLwTrAEvBtcDN6ndqKf0/0nHwTLlD+8HHwRXAO+Dt6i9+VW8Bi4FXxHr/8ueAfYkzzcCWaAHweHgfeAueC94Bjwk+A4sBqcBn4KvAS8D7wO/By4GKwBl4NfAKvA+8G7wK+C94JfAz8L2um4H3zQsbfVb3QdA9gfZm/7bb1fO7UdfEfn4x/Xcn4CHA5+V8t5l7eeabxDDPVsL3o2vgTa/g3arl4GU219MA3cp/fxFXCw+jv7aWr8fcS/+b6YezT+F7Re/Mydj9dvQTMP+j8dPSRKvdwo9XiHb4FX3dUriFKvMEq9iij1qlrRy/s/4H1v+E30aw46ud/btvagk/u9k/s9mrUK70fu94EfibWmIxVINbIDqUeOI2lMbuYhC5AqZBtSj5xEBt7+313f0Pnr/P2bvesAj6KIwktyCYGckA6EgBFbVMSg2FtUUFTEqKCgaBJIEDSEM0WxR0XFHjt27F2xN9QgqNhj7xp719ix++/Lf7tzu7N3t0ms3y7Mvezum5k3b97Mtve/CbZgC7ZgC7ZgC7ZgC7ZgC7ZgC7bO7737/bX+/1PmVJikqtu+/8OMcPb1eNn98dA0fBuWb9zbjNl1QsVWEyfBx+2AisZGQ/AB5YIPYExkfifJYXvNgzeijKxHGRNZKYT+SeIDVlrg6SvGvPY37+lJ+LhFfcBQrviAqT6In1PGdOV7/vJc8OpknNkYry76i4Szf0M941Y09VQ7e1pVLbLF+gPjdRHjq9sxo2+CXsp0dYqHi+0vv2+2kVAG1e97HB0bzUJ6IR2ItBB1VSp1VVVXj6yor9mvZlpjBewExND6Wh4iedbU9QvKc/qAoyS934LNy75GpNEm+BxY9Vwh51e2MAmPyX4YZUTjC6BscbOGvumDWys8+xkZ+J1CH+gp0DPCysl6wuHwnobLZ588C6w4BONdcQgKyfM+eHaBXaQWZI5ND4XTMYykjitwvB1pVwcGAv0k+VVf621z9TEMMlz2mpYtbcYnwPp6ly+qwwcdulD6XF33fh7t+Xj2ubHM0eeN9U0NVpe7+lz0utI=
*/