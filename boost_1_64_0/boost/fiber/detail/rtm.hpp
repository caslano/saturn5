
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
pIuVydUUVx+xh1C/vHspiitmxu4PdTmg7QQCSl/ZrlN4CQi91bm9unso24IbXjtSF68XkLKc72Np52ZokFL/aoeQEeUWJv/8DfEA6by3nOlLM1puhyZNqYe9FqrfK2PVTPfPkWws5B6rWaR0DC/+PQQZI7m4Wr4MVFzcxi32OxgWZ252jqy0/LnYMZ/zL8qR0Y7CvVMLtZgdrVHn3vOZa/949XzNnpCdWYj4/nXkRPmrDCUu5p62Ik88KHUfxEGlciAQYLWhJ8VJqSIc+gdc8Hiyyuns5N00q2WlepYKhN4Q8Ad0bVGZiJ5q0jitfWnFk4bnAXP9ovJHF64bHQYdUuJVONtQvrTM9sN7b/zAE6fDnJfZUY7zyFINh+nP89WMCy+HNvBIEnc0b9BeuXd6vZC24RHZV5sVY99PW/RTZTSPPKcxKNAaP9ZghMnU9e1utdWAaKBEL5wUBEZRxp698kFbjQGgdkJIZ/nweutzkr98uo63Bkjh/hqb85EW8AH5Gm+Du5QzUWpf3efHMCAM8iV0mgyIymesYu5HoW4xPYQVNX2C+uUDxPFrbA==
*/