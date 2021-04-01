
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
JTxWGiVB8Ay0BsortL60eKYVe4eThysmwEGM8r6hzzYgoOOra7dflnAWV2Z9ZUBNdSLc3r0CXuQz/BKiGGI26wNUhcNrw/ylHmRqfI38qaWtrOgWgthK8mZCWUObswvWSy5Rj+CENnl+SxJEhouhKsX0JCnEkDVO6/WwCidNpOo9tg1PUku/9yjFUfNPxQvGZNRBhCzqfXtdB725XtVNZ7xbJX+geREGVg2/olqZd1CDj4Rcs8FFMGAOUPLg8ArBOWYj2BjXVcYreVn9g4LEowz8gQZYMzDHZJFWhj9/vDguZhTDYvYC9SRpsHN5aU79CaiC+es0lxE3+W+DVCZiDqjV2hceCWiBalVFsMOEHc6yp37BkokLfxxtlHNdNMZZF1GlySrCUkQXcVq5mvtvdyslR1Ac7iSoHINXTe0GJDSMfbIZScq2jebZJqwTgDkB/Gn4HE/riXTu6o9SPu3xIMVgLONlHzhiVFMxr7Dwog8tR/Ot/wRS/DagF7Tft6P7Y6ImdtV/v2VRo930MnR/kb6xg4vS16uIzgw8gT3zYiPfCi/Tfk4VX4Y8bw==
*/