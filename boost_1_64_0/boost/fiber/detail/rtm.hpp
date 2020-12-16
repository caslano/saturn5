
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
Ln8cyg4I2YrjcV9nd4Ns6vGbTpambIZU1xBcz/41UY9fajLx+HbT4/9cUXi8ECzdTe/tgytKG7Zg7im8vYH9O4B6+5UrEm/vIt5+CoqvEuIVh9N7+tYrSjO2Qj6IslnEM5NST19+ReLpzaan56LgoBCsOJvey4dWkGbsgASNC0YnY7LbqaPfsAJx9BbT0btXEI4uZMtxU+/kDdic35hDbMVOszBHk1InX2UF4uStppMXrTAKJ5/jl2aMQiJjyG6C4ZV6+J1+4uEdpodP94/Cw/fxSxvWQ2ZhCD4AxlXq4ev6iYfHTA9f1j8KD/9seWnABnjUG4KnwIBK3bt/ecW9mX1M375++VH49uHLSwO2wbPXENwOgyn17c2XJ75db/r2qsuPwrd/WM4wIPozPJy5bHQvGE6pez+1HHHvBtO9b1tuFO59LDbnt3t6U9/edjni222mb6+93Ch8+49JaEbNk5u698uTFPdGQ5kefs+kUXj4ydhi0O6pTT1850nEwxtND99g0ig83I3N1dg9samHv1NJPLzJ9PB45Sg8vAebC2me1tTJ964kTn6A6eR1laNw8hJsLqB5WlMPn7cs8fAppocPLjsKD78Ym/PbPa2phx+yLPHwdtPDd1h2FB6+DDZXpXlaUw//ahni4V3Ew4eWGYWHX4ktBu2e1tTDj1qGeHiz6eG7Mc5DbGGkC8DMUdfzrgHh5JOZbNChDoxVV/jEpj1Dk5lFCp+39/piFFGjeYJTx/9oaeL4LabjP7u0qU8V10f4PurDVAEDSn2CoI9dMJyCIkKapzoNhh2XJsHQagbD+oo+Qa6PiAfUh6kCRpX61IA+dgHydQVCYPukp+N/BYmODmX8rzCVqeHKiABBZZgeYFGpTAiUsYuYfSvQ/nZPfxox61eQiImZETNJUSbElRFBg8owPcCcUpkAKGMXRa8vhca3ywhoCN22FMmBomb8TFvKVCbAlREhhMowPcCcUhk/KGMXU1uhiKBdlkBjatJSJKbqzZhyLTVGMfXwkmh8feZAw+rcJUlYNZhh1brkGIXVKigiZJdN0Jj6s5zEVJsZUx+Xj1FMXYEiApoMg4bV4eVKWKFBzciKlY9RZHnKEQK7rING1vtlJLIazch6smyMIuvEMoTALhOhkRUrI5HVZEbWemVjFFlfLYH212QnNLjiS5DgOsAMrpuXGKPg2gtF1GgyFhpZoSVIZE0xI2vJJcYosl5cHCGwy2JoZN2wOImsdjOyuhcfo8iKoIiAJrOhkbXE4iSyukhk/bTYGEXWHYshBHbZDo2szsVIZDWbkXXIYmMUWf7FEAJNtkOD6/tSElwtZnC9XTpGwTWtFCHQZDs0uPYvJcHVagbX1qVjFFyOUoTALtuhkfVmCYmsDuX7t5IxiqxjUETILtuhkbV1CYmsmGXexUe+TK4E/d4c2O/5numcgypaqyVLYH1ejLa3S3ZoVD1aTNLAqGVupJTMjUwrNnUplbpYqydLRO1ZjKa3y3VoRK1dTCKq3jJ/UUbmL9yKLmVSF2tBZQmol4vQ8vpUh8bUtUUkphos0x61ZNrj6CJTo1qpkbXGsoTUxkXpznosUURnPcCVlc/SKqUuoPhnPqkL55AoA11sv3/2ZTAJ0uVLmgQBf6YfkPmd6sviHRWl/FIp60sHS1hV+tKdFvmukE6LYFjJj7wCJKyeLjR1CaQbVtMK050lOaiQzpJgWMkPsYIkrDZQdAmmG1buwgwmTd4qoJMmGFnye6kqElm3FZjqVKUbWccWZDCPEi2g8ygYVvKzphAJq2UVdULphtVn+elOrfTn06kVDCv53VENCasL8k1datINqz3yM5htWSPfMtuCYUW/EAqTsPo=
*/