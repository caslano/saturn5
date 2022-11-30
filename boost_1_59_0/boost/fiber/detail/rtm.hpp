
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
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
*/