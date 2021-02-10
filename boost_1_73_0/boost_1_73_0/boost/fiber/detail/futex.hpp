
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
ewqipKig54YwDnuwZpJLG87H0am/iODcnc/dWbQE/wTc2bKzdzaeHRM3OHmtAW+qGiVFUQPfVAXHdM/5T+10y4lOYbSYT/wgioO5/2UZh+HkzFvGRxP/CA6g9+Y3+KspW4L3oFfwtWYAvHXevna0QH+LkcltLFHpWtM/0UqS5fAUZu7Us542v3oJVc2vGFX8EreQUcZVLW62kCDRNaupiBvciHoL60KsW4vhcuYH4Ti0nDKzfuFlUjQpwgcdhuFm/slqPSaC5A+j6+sdeJETawoiz5OR2dbTM4IK3dCIa03rsOCFfg4OLSfjbYjHXjiaj4No7M+sgFEhGVSCl0pTjLrqnqYx1RCFVE49lohSMU4M5iVBsWEaSOjvdClmS/J/cABsLRrVMvQhemShpPnLywvtSp84jaIgNKg6NLo2FVnVLX1NXLP8CkvK2swA4xL6Bb9E6AXetDeATSMVrBFkhQnPiIlGb5WNH4MuWgZe/2CwygLHssamh9o8uU6JK84Kit/YMLOsYBdSl5impW66b6ClqlEibT3busS6Je1Wl1XUGonBKBU0GkqhzNyjzC8RK+O+yTKNXS2ox4FlBKRFRg1C1MROV7ETdzGJrNliMmkFlFXkj/xJaLlFAdEk1G1MkROOSiSikO8NsDac
*/