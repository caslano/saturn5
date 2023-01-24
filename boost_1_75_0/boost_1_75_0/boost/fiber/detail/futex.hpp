
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
ps6w9HRkwyISjMAi0mB3MNIykEL6sRRtsT5hj+vBkwe3C5v4PJ5GD8EhU7RE0kIODpk6cMg0gIM7XKy2jnjAlBl1KqoA4lnbNviyJuSly6x76TJrLxnAWMpX0lQHrf0v6WhC9wIaoQlGWEURr2FBMScpb52xE4YpZTOJilLF25YmEsNNhRvGTCyCixv/NTlowKLPhNFGFSOKM44IAQzqHoZov2z2/ckdTTRMnUvS8waXJJVjuycZt0UoEsa0naHnGWQ3L5bpKApu4odUfeEZ2oc27Vuc1ApxfwLhqjjqSnMy3WQAKLljIHrz0IMAIHmMft/pRKdx4Hx3BV02tT7mkqXQRToHKh2hSO9Oa+8gqzrb/FFokddI37vYoO/NYow4O23/gLEwarv+WbgTo2lVm5by4VDH96Gu3Xo7e0Qc1R/XEyf1/M10rcyka/nNxPHM4NfSTNLjbjgf5PwVkTjEY3Evt87sLasr3Ux2aLmZVDeTt5HOr2n8W6n8fZdMZLN2Kon8QfTN+GCXEgYPlLL15zEv+B830etjcFXuh6dQ6Issevz5TdTsrpv0fuUj9CLNyam1jEUjP8TIXZWcRctLy5frncSMbQIwL5bkL1SLzVFRnDa+IwpMetiERoIoMy+ru6X8HJ5V0212vzsVCAdPezbBgDEY8Dxuc/omnnbIn4P0RVJuyhEuWCD/Jw+soaWky5KE/bOVdFm/g9yv
*/