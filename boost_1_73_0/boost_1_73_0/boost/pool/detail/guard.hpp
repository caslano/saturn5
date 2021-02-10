// Copyright (C) 2000 Stephen Cleary
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POOL_GUARD_HPP
#define BOOST_POOL_GUARD_HPP

/*!
  \file
  \brief Extremely Light-Weight guard class.
  \details Auto-lock/unlock-er
  detail/guard.hpp provides a type guard<Mutex>
  that allows scoped access to the Mutex's locking and unlocking operations.
  It is used to ensure that a Mutex is unlocked, even if an exception is thrown.
*/

namespace boost {

namespace details {
namespace pool {

template <typename Mutex> //!< \tparam Mutex (platform-specific) mutex class.
class guard
{ //! Locks the mutex, binding guard<Mutex> to Mutex.
	/*! Example:
	Given a (platform-specific) mutex class, we can wrap code as follows:

	extern mutex global_lock;

	static void f()
	{
		boost::details::pool::guard<mutex> g(global_lock);
		// g's constructor locks "global_lock"

		... // do anything:
				//   throw exceptions
				//   return
				//   or just fall through
	} // g's destructor unlocks "global_lock"
	*/
  private:
    Mutex & mtx;

    guard(const guard &); //!< Guards the mutex, ensuring unlocked on destruction, even if exception is thrown.
    void operator=(const guard &);

  public:
    explicit guard(Mutex & nmtx)
    :mtx(nmtx)
    { //! Locks the mutex of the guard class.
			mtx.lock();
		}

    ~guard()
    { //! destructor unlocks the mutex of the guard class.
			mtx.unlock();
		}
}; // class guard

} // namespace pool
} // namespace details

} // namespace boost

#endif

/* guard.hpp
SAfkjPqQc9hvwCxKgMs1PAU3YeB2o8ieQ8g5OmzI4Za02bnqJqiBGgLIxomcAFVge0+4hnuDSk5RO8gPsizlxgZZnqb3I0T2kJzRqJLTPl6hulUqVci2/1O6I2dFQfeK3273pbHfc6Awxh6BKMKNgPxwgED7/hH4tX9Ux0EFY1GQgSJgKn6oSdCMdRlkH/O/yfLRCGzoN5KuNH04OgjqkHLQIUNr8qfQqkxnl5dNbwajGhUtaB8TmS0JoZUCIeBbYFTgOMeDAizKhXZpzz7YOew3siWwGk0HSYkhAF1EQH1MkM8A6DZuUWz7xM5aDhgWNGpDRrtSMMXmcR8/iZ0HxM6D7ewU05ldOCg8Qev6lwWuos+lEV1X0xsVsJjqC0EWOCkloqsqVG6N/FN8qxJXR/m3ltFu+97yR7ZK7OvyuIUnNEE5OnorYHuxUzf9IKOOG6PYgV33gJ4Hm6CIQzAmTy1NuXPigP8s5Qvj+g+t0Hdil/Q64szMtBoL6n/RxMTcIgGLMJUzxFR5K/LMyOsMvZkzBM1NsWP/RnXnMRscfDp2LYVAjyM0wEkXyzu7j/6ymIhnXC8Gx1tfDbe/2qudLLBoIkc+ow22v+1/Ys+9B5+ZL4Mdgi08Pb8MqTiEVxcX4ZsLtKd3HYdXgSUT
*/