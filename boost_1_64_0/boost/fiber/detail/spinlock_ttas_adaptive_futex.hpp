
//          Copyright Oliver Kowalke 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_SPINLOCK_TTAS_ADAPTIVE_FUTEX_H
#define BOOST_FIBERS_SPINLOCK_TTAS_ADAPTIVE_FUTEX_H

#include <atomic>
#include <cmath>
#include <random>
#include <thread>

#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/cpu_relax.hpp>
#include <boost/fiber/detail/futex.hpp>

// based on informations from:
// https://software.intel.com/en-us/articles/benefitting-power-and-performance-sleep-loops
// https://software.intel.com/en-us/articles/long-duration-spin-wait-loops-on-hyper-threading-technology-enabled-intel-processors

namespace boost {
namespace fibers {
namespace detail {

class spinlock_ttas_adaptive_futex {
private:
    template< typename FBSplk >
    friend class spinlock_rtm;

    std::atomic< std::int32_t >                 value_{ 0 };
    std::atomic< std::int32_t >                 retries_{ 0 };

public:
    spinlock_ttas_adaptive_futex() = default;

    spinlock_ttas_adaptive_futex( spinlock_ttas_adaptive_futex const&) = delete;
    spinlock_ttas_adaptive_futex & operator=( spinlock_ttas_adaptive_futex const&) = delete;

    void lock() noexcept {
        static thread_local std::minstd_rand generator{ std::random_device{}() };
        std::int32_t collisions = 0, retries = 0, expected = 0;
        const std::int32_t prev_retries = retries_.load( std::memory_order_relaxed);
        const std::int32_t max_relax_retries = (std::min)(
                static_cast< std::int32_t >( BOOST_FIBERS_SPIN_BEFORE_SLEEP0), 2 * prev_retries + 10);
        const std::int32_t max_sleep_retries = (std::min)(
                static_cast< std::int32_t >( BOOST_FIBERS_SPIN_BEFORE_YIELD), 2 * prev_retries + 10);
        // after max. spins or collisions suspend via futex
        while ( retries++ < BOOST_FIBERS_RETRY_THRESHOLD) {
            // avoid using multiple pause instructions for a delay of a specific cycle count
            // the delay of cpu_relax() (pause on Intel) depends on the processor family
            // the cycle count can not guaranteed from one system to the next
            // -> check the shared variable 'value_' in between each cpu_relax() to prevent
            //    unnecessarily long delays on some systems
            // test shared variable 'status_'
            // first access to 'value_' -> chache miss
            // sucessive acccess to 'value_' -> cache hit
            // if 'value_' was released by other fiber
            // cached 'value_' is invalidated -> cache miss
            if ( 0 != ( expected = value_.load( std::memory_order_relaxed) ) ) {
#if !defined(BOOST_FIBERS_SPIN_SINGLE_CORE)
                if ( max_relax_retries > retries) {
                    // give CPU a hint that this thread is in a "spin-wait" loop
                    // delays the next instruction's execution for a finite period of time (depends on processor family)
                    // the CPU is not under demand, parts of the pipeline are no longer being used
                    // -> reduces the power consumed by the CPU
                    // -> prevent pipeline stalls
                    cpu_relax();
                } else if ( max_sleep_retries > retries) {
                    // std::this_thread::sleep_for( 0us) has a fairly long instruction path length,
                    // combined with an expensive ring3 to ring 0 transition costing about 1000 cycles
                    // std::this_thread::sleep_for( 0us) lets give up this_thread the remaining part of its time slice
                    // if and only if a thread of equal or greater priority is ready to run
                    static constexpr std::chrono::microseconds us0{ 0 };
                    std::this_thread::sleep_for( us0);
                } else {
                    // std::this_thread::yield() allows this_thread to give up the remaining part of its time slice,
                    // but only to another thread on the same processor
                    // instead of constant checking, a thread only checks if no other useful work is pending
                    std::this_thread::yield();
                }
#else
                // std::this_thread::yield() allows this_thread to give up the remaining part of its time slice,
                // but only to another thread on the same processor
                // instead of constant checking, a thread only checks if no other useful work is pending
                std::this_thread::yield();
#endif
            } else if ( ! value_.compare_exchange_strong( expected, 1, std::memory_order_acquire) ) {
                // spinlock now contended
                // utilize 'Binary Exponential Backoff' algorithm
                // linear_congruential_engine is a random number engine based on Linear congruential generator (LCG)
                std::uniform_int_distribution< std::int32_t > distribution{
                    0, static_cast< std::int32_t >( 1) << (std::min)(collisions, static_cast< std::int32_t >( BOOST_FIBERS_CONTENTION_WINDOW_THRESHOLD)) };
                const std::int32_t z = distribution( generator);
                ++collisions;
                for ( std::int32_t i = 0; i < z; ++i) {
                    // -> reduces the power consumed by the CPU
                    // -> prevent pipeline stalls
                    cpu_relax();
                }
            } else {
                // success, lock acquired
                retries_.store( prev_retries + (retries - prev_retries) / 8, std::memory_order_relaxed);
                return;
            }
        }
        // failure, lock not acquired
        // pause via futex
        if ( 2 != expected) {
            expected = value_.exchange( 2, std::memory_order_acquire);
        }
        while ( 0 != expected) {
            futex_wait( & value_, 2);
            expected = value_.exchange( 2, std::memory_order_acquire);
        }
        // success, lock acquired
        retries_.store( prev_retries + (retries - prev_retries) / 8, std::memory_order_relaxed);
    }

    bool try_lock() noexcept {
        std::int32_t expected = 0;
        return value_.compare_exchange_strong( expected, 1, std::memory_order_acquire);
    }

    void unlock() noexcept {
        if ( 1 != value_.fetch_sub( 1, std::memory_order_acquire) ) {
            value_.store( 0, std::memory_order_release);
            futex_wake( & value_);
        }
    }
};

}}}

#endif // BOOST_FIBERS_SPINLOCK_TTAS_ADAPTIVE_FUTEX_H

/* spinlock_ttas_adaptive_futex.hpp
sPu0sPu0sPu0sPu0sPuSYB9UYPcB7IMW2AcXbd0OS7FuedJ/qm4vsoW9SAt7kRb2Ii3sRVrYi7SwF2lhL0qCnc8Syv7AmkoW2IcWbd0Oq7TucMJ/qm4vtoW9WAt7sRb2Yi3sxVrYi7WwF2thL06CfY4CezHAPscC+5xFW7f/zd6RBUZVJGcm15AEZuQyyhUluMMlkcsgIpMVcICAIyIGuaIcRkGMMoEoIEc4DdkFV5FLBRWPxQMUIYBiAnKzCire7hJW5IVBF0URUXe2qqu75/WbN8kkMS7uMh/Je91d1dVV1dVV3f268QDXzEm/q7jdYSp2R1ixO8KK3RFW7I6wYneEFbsjrNgdIWI/rBM75C7ABEXsh2s2bsezXW/N/V3E7bBtL0ue4ZoFhxxCdhbuvPA6Cm9tGmSjFdhG7GNbGArwz8HdiDcJKLcj5fRcFofPWEh2PD2oE0GdwIF6WN4JsN2wPD2XxXJYp7I87sQWJ9HG3c2U8W4tT9SC+ohUIo9iotcsho0PmkH0Ws3E7mxPDZ0fNYEJfu85HLlbAuJElib6tdeqi9hRDRFbw4k4PoyIT1oUtVyACYqIT9ZMnI4iFoel5t9DQj7H43R6aqRfcq26kC3VELItnJATwgj5DGQrm5HOGIR8pmaichSyPND0sbtJyudwWP6LlPLF+hXWqkvZWg0pR4WTcmIYKVus6uI5JChShvcaCcJJylEk5Y13kZTP4SjcXMoxVZeyrRpSjg4n5dphpGy3GtbK7aqU4b1GYm6ScjRJ+eBYkvI5HHSbSzm26lKOqoaUY8JJuU4YKTvhUd3wqUoZ3mskxCYpx5CU/XeQlM/hGNtcynFVl3J0NaQcG07KjjBSTrIaVsKTVCnDe41E1CTlWJJyTDZJ+RwOqc2lbK+6lGOqIeW4cFK2hJFystWw8J2sShneaySAJinHkZSbjSEpn8MRtLmUa1VdyrHVkLI9nJStYaTsshrWuV2qlOG9xmLl/BI7SbnLqHM+XDaXcnzVpRxXDSnXCidlWxgpp1oNy9qpqpThvcbC5fySWiTlG2875+NlcyknVF3K9mpIOT6clKPCSDnNaljFTlOlDO81GC/Hk5TvyvqdxsuJVZdyrWpIOSGclKPDSNltNSxauw1SdtdkvJxAUp47/HcaL9euupTjqyHlxHBSjgkjZY/VsEbtMUjZU5PxciJJedXQ32m8XKfqUk6ohpRrh5NybBgpe62GJWmvQcremoyXa5OUt9zyO42XHVWXcmI1pFwnnJTjwkg506quQGOCIuXMmoyX65CUD2X+TuNlS9WlXLsaUnaEk7I9jJSzrOqCMyYoUs6qyXjZQVL+16DfWbxcNr80KGr1K/UoAKHVdLoMgnLwFoTgMoVaPFUUt5oVtxmLB78tNSseZSzuFsWjzIpHG4t7RPFos+IxxuIuUTzGrHissbhXFI81Kx5nLJ4pisfpi9PBITH0dSI8li1/k66MOMmPBruvITsazG77tQ8NOf87/zv/O/87/zv/O/87/zv/O/87/zv/O/87/zv/+5/6mZ7vOehMKTvvkE4MpkOZvRbfpfg/0+K7mB/8WFc7uxMK4kQwpqRZcvEI3SFaXNSRQPBoYYvvKjaPCSm4QJjB1o9o2iyLzovcBFhmF+fWo7eX/IBT1swu+F6agGejQ1LlT5DMgFYlGxuZjY285wfZSDdWhQ8e8ZAqHryi/TkWH2tPnsXnwmMcp2OGrwk+4kFCyI0TO1Ru4CHWDaxQ1WkrMcSNGW6LL0X7gqd4MMWDwO9aFablxpS9iDUrnMtDzuXgHNF0zhuPNmUHMs+npOZphxJo0sjLRXeDCSIvgszjIG7tOkL0h9CSNMXsIfE=
*/