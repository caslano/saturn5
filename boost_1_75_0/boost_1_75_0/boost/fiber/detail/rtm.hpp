
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_FIBER_DETAIL_RTM_H
#define BOOST_FIBER_DETAIL_RTM_H

#include <cstdint>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

struct rtm_status {
    enum {
        none            = 0,
        explicit_abort  = 1 << 0,
        may_retry       = 1 << 1,
        memory_conflict = 1 << 2,
        buffer_overflow = 1 << 3,
        debug_hit       = 1 << 4,
        nested_abort    = 1 << 5
    };

    static constexpr std::uint32_t success = ~std::uint32_t{ 0 };
};

static BOOST_FORCEINLINE
std::uint32_t rtm_begin() noexcept {
    std::uint32_t result = rtm_status::success;
    __asm__ __volatile__
    (
        ".byte 0xc7,0xf8 ; .long 0"
        : "+a" (result)
        :
        : "memory"
    );
    return result;
}

static BOOST_FORCEINLINE
void rtm_end() noexcept {
    __asm__ __volatile__
    (
        ".byte 0x0f,0x01,0xd5"
        :
        :
        : "memory"
    );
}

static BOOST_FORCEINLINE
void rtm_abort_lock_not_free() noexcept {
    __asm__ __volatile__
    (
        ".byte 0xc6,0xf8,0xff"
        :
        :
        : "memory"
    );
}

static BOOST_FORCEINLINE
bool rtm_test() noexcept {
    bool result;
    __asm__ __volatile__
    (
        ".byte 0x0f,0x01,0xd6; setz %0"
        : "=q" (result)
        :
        : "memory"
    );
    return result;
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBER_DETAIL_RTM_H

/* rtm.hpp
j32RFQlaP4iFXh/xJ2E4ns87QK9p7N1De/3Nj9Dr3FTe7VthP7A2lK0/8q5fh10PgqgvB3rNhlAg+bkPabpuIxExeKAeeoZMwilItU1Dy81KHQAL6UlRq9p4RsR//Kir0Du0Ani97VZ6/gzyCncidns4ea6WKI7LwShYPdrnxPOEpG2w39PYTzRlUSFr6nk4c9mr0exVfTH7BZxTW+SLWbnAVc1uo0YW1gTyV8d3NCjjtNchPDMil/knSIcmdIUTVXoGUTE+Oq0+SgNp1/jPSVWNDqSzt6QbTKjGbM7YB8u70MKTjClX9ybpoS1DFWxO6UVHZmwGnWGRGfTb3JvOtj+vpyrHr+dxRaG8Mmk1HYyH+NM916uxkWI0byiHi/uiTHKpQxkiiWeSeOaPXN4LNtpAVmsIhqJoJjsvq5TOtv6kTBNmevdHOq9W6yWLZpO1T8VzP5FJ8Rp1BG4W6GHhlL8yWqeT6CYy3WcT8lOgoNlJBQn0QOF4FIhGkqGcAa4BI//KxAsCQwIyFTT7Wh0BN4xufjcCj77jUXT0Fdu945ezvWLK9w9anpdRZfcAFCzr0xeEA3PBKE3b+sfYAmVv9QxmJCG4Llbsc/cnM8fE04kmHsYDfRrlKqxjD96Bp9UI9g3v9iCVfe6vROTUJPww++LHeBSKWLLRmvFYeeoBdvUPC6PPQ6XOEc0VBZJ3XSRHlVT4VHhzhcGvYV2U
*/