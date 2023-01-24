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
vN7k8QRHiFVveq9oJLqwHg5Utzff6Z40Ow+3SC2ayd+MNlBh8zqfOC5XRUFWEJNneV4XzgxeMJqYXuH9vr0It1v6h1NtGwAk9z8aiB4K2GygU1eekHHyD3JzwUq7vJ1kTpAwpje0+L+s+ELkdz/1BfqPEzdbrxRPe+oXN5auNde5rwNhzKYBl8BW5vKXueisGwzuaL9OxgsKXGhas3n1G8ZGEzrGyzeaLtd1CeEVsNRecAxJRVp97ebMMJHf6oHDy06ddaryOjyexDTVQ2UbyaQf5CXuvXLKV08oQLJX+jHn6ka+7zqByEyuWQlNkFjg+0ZsC3F5G6VPe7vd0uwY1F2vbThgbEMXI5dbiNLstALkZ9c5sd2MOHPYs3DYjcwYSKBIbN+ICgqSr8xLDtytN+EN3OUwQeK5txkg4RHwJ17bDtiHdhlHHRa+HSo2DjgzNjvfHMYxvfSMOYD7P+MSrOwUxZH4VrDpC+ovV1htVOPA++ewO/fKh79B1COYNh5qg2rvxhbVmmIIdNemcOKShfAPXpeea6rVq8bfCMNgvE2kpg4fl3bsSASwZNsO5jkbBsz2WZgJwb6a/TxALkvSB4ZXk5k43wzbqKFR7a9+zR1exwhZv11BzZgi/TwMbca+c8HUyzu1N43lXW0A12Van/PHj52GLzjtPG49ZQMOYrgQ9YImj9UFVCPT+gGzfGbr3ok8q42jpgsUn5QV
*/