
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
w1/DPvAheKLYazu1yadQvHW83xbpr/36dPLT4VyYBYthC7gQDoHnwtGwEk6CVXAqXApL4AXwXLgcXg4vhGvhtXAd3Ah/DC+GD8BL4KN6/jE9/1t4GXwVXg4P6fl39Pzf4ZXQ5+hxgQ3h1bAFXA/bQcd9B7gRdoV3wp7wLtgL/gSeCK+HY+ANcAq8CVaou0q4GS6FW+DlGs4aOa/1zg6tu5C1JZKfHZFpmp+jA9RvOBY2gGfA
*/