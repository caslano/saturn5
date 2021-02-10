
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
MITZHRh2ZvBF2/3ve4aL7aRJk1bFMtjDOd935lzHWvbgyU+7DEvDwYNXWH9DvPDZKU0F/4vE6m6FMPwCzQcVl/h8BNUADlpfwhN4lNYX6NdaYcv1Rv8Ow0fQLbWR+jbQystQ/8SVRrPVP+flTtDrTEH//ASGL1++gKcwOh2+NPX9hQkXUUEJA1+RYkXEtQlvknrljyzabi1J3ppAFETMugEbZFSC5KnaRIIA/mY0JoUkCUQSEiJjQVf4hxagMgIpZQTOvenCnfxpwiajcdbi7HgFMuMVSyCL1gQEiQldNzBlJBTwFBEQP6FSIWalKC8spCegiMhlC6ONiJjkEK0jyqIV0kUKMqVK+WowiCvBcCeDhMdyEHcOsTKV39rVAq3Jox3wUoHiUEligpY3IecJTfUTXYSLZbViVGbmwSwkLJIBFyAJYy0cqlIimy0Q8FtvmVoSSrSeKv2QvJCabZPx/IYgurUFSitRIB26BeUSjo43oSoSImr52hEdS+vl2uUPhOxgewK8QKugZ/vg+j1YRZJKE67c4NKbB3Blz2b2JFiA9x7syaLF++BOLjA3KLIKINtSEIlWCKB5yShJbpD/1Ho3rOASzuezsTcNwunM+7wIfX/8yZn5rjeBM+gNn8OEr3V+P+9Bj9GVTgD4
*/