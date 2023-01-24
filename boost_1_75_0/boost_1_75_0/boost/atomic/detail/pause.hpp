/*
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 *
 * (C) Copyright 2013 Tim Blechmann
 * (C) Copyright 2013 Andrey Semashev
 */

#ifndef BOOST_ATOMIC_DETAIL_PAUSE_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_PAUSE_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(_MSC_VER) && (defined(_M_AMD64) || defined(_M_IX86))
extern "C" void _mm_pause(void);
#if defined(BOOST_MSVC)
#pragma intrinsic(_mm_pause)
#endif
#endif

namespace boost {
namespace atomics {
namespace detail {

BOOST_FORCEINLINE void pause() BOOST_NOEXCEPT
{
#if defined(_MSC_VER) && (defined(_M_AMD64) || defined(_M_IX86))
    _mm_pause();
#elif defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
    __asm__ __volatile__("pause;");
#endif
}

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_PAUSE_HPP_INCLUDED_

/* pause.hpp
PXxg31jL1XeO0EfcY38VdUkLbEaoRkkSwXCC6zyC9iZdAzZST3eCsZswLx/GTfQin759hdt+HIFR3gPvz/p8xp5OR3CcdDeQZq8OV94wh0zei4miqUgAw7hQQ6AK5Q4UjZb2j1fuhrVPcT8lgpmRz1NVYSB0vZ8+P+miOm30La9wB0PI9jlqQ56f9aAnrkY/aspWdX4ogsDgzAwOKdynT2VV+x7TvkF+0D/UXvWUlFAz9+AjXfpC0P9i8PEdTBuuvxj87f9dcfnurwb/zyYLX+MhHUmPZv+xhs8jIKZg47GYz0MZXCPunPLB1bodh1nLiVQi3rFO204Hhu23jnprXVQGqrm1y60vhwuF+yO+fFOJI4j4+E6Ryj4fBxUNA7dJfEbT8I2KiSnQgQT+QXmWE5mZaWIylsIZE0x3XcQPa/M5zeT3oPXYdbO94webXo9ig9sflN+xnZQy+PPrqTLT5ky90SIIkw7qyRzbudxfJZol0obT9va2/jp04xzMHup8rY7Fiq2Nwo6qk2Xbru0TDqcrRQYcOMfSd1hrRhf6DjlYX2q+tTJUGogQgSIuzFXS+3vyKzs6m7B7ludvE/rHfkY1hCT/JNUSYnZ4uZTSeScdm5rEys3LLcIqb7fRkxfvNJ+zNLw6+ESgcxsF6yqrs1LeSDw/9rotZefDgJLk0TXuwHD0P/ghApbNzj7jSZJmCSFFjmAo9hz7PXZQ
*/