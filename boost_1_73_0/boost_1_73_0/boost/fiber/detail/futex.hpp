
//          Copyright Oliver Kowalke 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_FUTEX_H
#define BOOST_FIBERS_DETAIL_FUTEX_H

#include <boost/config.hpp>
#include <boost/predef.h> 

#include <boost/fiber/detail/config.hpp>

#if BOOST_OS_LINUX
extern "C" {
#include <linux/futex.h>
#include <sys/syscall.h>
}
#elif BOOST_OS_WINDOWS
#include <windows.h>
#endif

namespace boost {
namespace fibers {
namespace detail {

#if BOOST_OS_LINUX
BOOST_FORCEINLINE
int sys_futex( void * addr, std::int32_t op, std::int32_t x) {
    return ::syscall( SYS_futex, addr, op, x, nullptr, nullptr, 0);
}

BOOST_FORCEINLINE
int futex_wake( std::atomic< std::int32_t > * addr) {
    return 0 <= sys_futex( static_cast< void * >( addr), FUTEX_WAKE_PRIVATE, 1) ? 0 : -1;
}

BOOST_FORCEINLINE
int futex_wait( std::atomic< std::int32_t > * addr, std::int32_t x) {
    return 0 <= sys_futex( static_cast< void * >( addr), FUTEX_WAIT_PRIVATE, x) ? 0 : -1;
}
#elif BOOST_OS_WINDOWS
BOOST_FORCEINLINE
int futex_wake( std::atomic< std::int32_t > * addr) {
    ::WakeByAddressSingle( static_cast< void * >( addr) );
    return 0;
}

BOOST_FORCEINLINE
int futex_wait( std::atomic< std::int32_t > * addr, std::int32_t x) {
    ::WaitOnAddress( static_cast< volatile void * >( addr), & x, sizeof( x), INFINITE);
    return 0;
}
#else
# warn "no futex support on this platform"
#endif

}}}

#endif // BOOST_FIBERS_DETAIL_FUTEX_H

/* futex.hpp
XqNJyG8yXy/0atlkuV5KED+AO/p6nfGtw9HzhM5kp/VTMl8HnS36vhGn9cIUm6P/dfd7DyKmg+k51eZM57CLiJfBPPlG7e9156P7wO+CeXK6zbkMPvoY8RUwh96s7T+38xIvT57ptPxTbC7I4KP1ZPY7OI+/w9fBKcQOMCmz+f6LRhwE43qXby/tg4PAxM+xOe5cnDdHrgPynQd3Y67N/v88Sv7vL7Kmf4+a99++SFdY5B//igf90LweDC52Xm0=
*/