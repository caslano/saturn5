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
fVjDjO1fPU5hfOs28V8Ej78CTrnyHqrH2oA9L815OUnYcfYE87sy2e0YfCehYURJNrOPePWLrD0PpczvF8bfy27u4AwI5s7jW8bfX6IJ+MnQ3jnSrvPR3mP5nj3LaB9QtOsI0dh9z3RzBsQCpl+jM5y5duVpYOkZXCLasgnHJ5gdBmLrXqA8TZA0IkRscBPYJ+9cW/eSi68rFCEvdJyFv2FM8uqezX3U0b/Oe4Gn9eIAOHmnz8V+Blgamx8j0FVkgXzrfjo235GbwOTG7RYRqHfxWTyEI7cSfSyAHrPG83x236HYKEHAknwuIu6D7d8AvIu520x5+6Dpo6yBTmqAyEwWy4rJ5rC70ykvDHA6n8PMFsH4JO/8acRJkSS0gebb4eyb4qBNq66uUdo2bzBpHfdQvi4o67hK4rhw2Hiuwac7ZdVB0xVpLqCs0lFmH4EBcnJJtr6nzIbyYxfSlwjRS0rKrtvyrOn3z3L6fRTiPlIRDblUoCfr926diiRvirILA6ShwvNH5EFeIv885TmEWKFU4HG5wSeidVky+yBgnVzBaRG2ceu8HUxedzqj98kfHse1pMz38Vw6BzP2aNnlGOHG3/ApgsHJyVllWuSa/nlOX5w5MyH0r3I6PCKS3ulYcLY3zqq8StKouOq9MQJGA7VneyPWxLWnS3m84lgwXjm/Odi52Du9FTh0p4HwwrC5LsWIWbtxPEm4P+gPBg6dBFPd5oB/F8cPjTDiHwT6u0EfiIjjalUZ7/OUcXZN8oz7urdpHrCIJpxLiU30Mzn30jro5iN7muYuEoPGnic4IiO4K6VTOVbGHQMGH2QbGR/YQelUBjlvubvE0IeyEcN8Qr56Su5ITmFW5cpp6Kfvwekbkm7KmNyT02VOgHEv/CBtGwwYOcCtH/Dyhyay7x1NYxxPzzfhi9Oj40NX8+M7F6dIXPANHxmwi2NuqBEmTR8TW6zjj0HESfracNlzYXnwu+q+nDzdzbdbRGXetoW4ur58cP7sxqlrZwNrT30G/3/UxFMk2Y9fvIvFrHoSE9P9+OJdDXYDDaBk2TbYO2PqONLQZ3FD+AGgj/uTPbJ+sjOcOygjFZQv+QHP1Osj6DZ2JW+7tirKZLg4RSJiyRv4Dr7qs0TETaXwJuTexnzdTvENpooUa7DI1SUdxcLWy5/tYe8riU4kadHLKD91T2CK3cQoMd62i9q8zeKRFyGIHl6z/j3azWMuIkTAgTVMCg/XZJ+u48MpXxPEeKu4r/tGXS5y6hiadygf7erZiy5HnLlTRc6teQPG27RJn6SpoHWkzLSO17t17Pokikqwoo6ay1vHZcrXQl1RtQioVB/evSNjctlQnh48eZ5V5n4WZbI873R5mi6s4ftMVFu6TNqWuOXRLNd1UwjRJL7uQvW8i7bLd/1hYsYQhoiN/2Zy06RH+HeXmHb2C76Lif9m/E2UNlmVVZ6P7OW/k/EL3Nqr46Sy5fv5dT+572Nce07egCrgC6cdmn87zbuP8eLDdV2ap25H8fM+j/G2SVzB8C4CJ8rYzzvHeUXc9aWog+0ipsl7RcsObx30nSgTkbRue/k1MG8ScBmRQPBgGTky/JqYvdeF3wz9aWXoUWMoXKvlf4bJl3mGRZylpk9chY7f5zJCbIDKnvQrv450zPzJkZEHZd9XWRyX+vv6VbD2+87HMv6478KyyjS/v3g7n+x7LNvzNU2alanpIvZW5OSYiaF2ebqyqqKuqlTXcHl0f0ocPeUb2n2GzhjS78mLNLmIGW8q3+RIko7wkqLZvUzK2wai67GWlHYImJuc5A7ERZen6qsUG+dc1c/lMTmLHR3TIG6hZFWXREdPkfY7fobxp6JpkiI=
*/