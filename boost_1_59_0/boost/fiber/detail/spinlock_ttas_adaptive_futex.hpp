
//          Copyright Oliver Kowalke 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_SPINLOCK_TTAS_ADAPTIVE_FUTEX_H
#define BOOST_FIBERS_SPINLOCK_TTAS_ADAPTIVE_FUTEX_H

#include <algorithm>
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
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
*/