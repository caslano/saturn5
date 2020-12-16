
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
zs/Ku3KYZ+QHDDmW6w75aweqIm8eqAP5nc8KI//Os0LIBwsg3+tZdeRvelYP8tXJ4sjvSRZDPviS1HlZx65tyzu+ZIDvPLK2iTvAb05WBbxBsg7Ajw0QBvzDAUKAhwgAnjxAHfD4AXoADxkgDvjJZ8QAD7kkVV0G+NN3jSthgM8lA3V3gN/5jCrgVz2jA/Bv+wsDvqG/EOBhAoC/2F8d8If76wG8WX9xwM/2EwM87FLX8I0Tg/MY4F3IYN0d4D36qQLetp8OwH/vKwz47r5CgF8mAPi4vuqAP91XD+A39BUH3NBXDPDLLkkNtxVkNW58lefGPJ2M2t0h/9jTqsh3fFoH8qanhZEvf0oI+XAB5Cc+pY588lN6kG/3lDjyAU+JIR9+Saq6rSC0fbt4z8ifJaN2d8gnJaki3zVJB/KWJGHkj/YRQr6RAPJT+6gjP6SPHuStfcSRD+4jhnyjS1LnZUa+2TP9shjglWSw7g7woU+qAt7tSR2ARzwpDPg3TwgBHikA+IIn1AEf+YQewO9+QhzwJk+IAR55iar6LaUlYZ6r+mYyWHeHfNrjqsg/9LgO5Js9Loz8D72FkL9cAPklvdWRz+itB/n7e4sjf2VvMeQvvyRV3VYwfGbelZ6RzyWDdXfIv/KYKvKJj+lAvuVjwsif6yWEfFMB5PN7qSOf3UsP8g/3Ekf+2l5iyDe9RHX+q5iWd3hGvgkZtbtDfkyiKvJPJupA/rpEYeQv9hRCvrkA8h/2VEd+ck89yPfqKY58655iyDf3gLxv/7Dv8T2+x/f8yd6VgEc2BOGZzCQzSSYHEoIsww4GwZBgEL5BMAgGQRDEHSyCIIgzcUQWi/W5iXuxWHcQTJzBIu51r3XNimPdt+jqet2v683r2ZnIRnzmfd8yr+q9rur6q/pVvX7pzh7ZI3tkfNSzTyH91k0hwvBl5ApL8S8jOzsCLY62taNswbolGIFdGYyyZKiZ/WI3stSxsZ6dxiA/ifI/VkwcnfvxyPBa7Ia8kXlp3XB3EWu486lwOomMrb5R0PeoJbm+TG734qhouKcrcBpjsZ8hUKFdKtMqlWkBZZpBmUZQJpY4sJIrE01HGXbUSX2sX5Z+VC7sF3W0LQliIpjEwYeUiU8XY0Yqs1Jf/5NZDFK60fS/XPaftR3NqNOvpd1pq+jLQPRPZSi6J/fTisUd0eqnot1o+Whnf2CWgx3HljC9HFsyJuMAJXoe60fiyC/mjZwZP9ZdHR/evJ6hNQM4PdMDvfKKLxLMIuc1BPzRnqn8xsS0X+eNPNwsL9gYLujBRtk1KLZ6dqJqRabT6U+BfgvvVVrfC3MrF4qu1jHbdcYrpXUbeyJN0ughMGsQy4tnHKchaSSOfOYRofBxm/VFQNPVjYtDgEYQE/z6nnj1q4mvt/A4os8yNthvU/4dLl4DIZSoy3c4+sKpW5gJLfQw/ZiiYVXRCvaXjPLPEIPnOPEi0I9cU5rGNd6FXrOwC8rSUKYsDWXK0lCmTH8B2ikR4WdJ5n7Dw06hjWcjTYDHwxHRTqL/U3BAaN4B8dXD/qk9iqGgmCEohvzShfC9KflaptFN90RRxDtRFPFNFEVK/3VFquNnxkvO3ObPkRHu5OkN+9lDcygP/AVF/NGwaR88nKpfxSd6MIJjcOhZh3PyFgfjTxagt7/4jfHb+9d7D19m/PYd17BOqfG7dMFHrz7JIcrkJY81C9lTKAUNKZmG22Xfrm1qsWSR+dCTz7Bmx7EFvNX5S+bg4BhjAyxrvPk89yB4uSBtwH4fs7hxVjES507ZvWkFZoUDiUmc4AICMvBS9nDvjpbhb3y0BkFs0FHSles0BIoncJgrFDlmGRzGQQl8+EY=
*/