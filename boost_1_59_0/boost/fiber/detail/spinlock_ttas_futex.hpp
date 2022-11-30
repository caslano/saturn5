
//          Copyright Oliver Kowalke 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_spinlock_ttas_futex_FUTEX_H
#define BOOST_FIBERS_spinlock_ttas_futex_FUTEX_H

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

class spinlock_ttas_futex {
private:
    template< typename FBSplk >
    friend class spinlock_rtm;

    std::atomic< std::int32_t >                 value_{ 0 };

public:
    spinlock_ttas_futex() = default;

    spinlock_ttas_futex( spinlock_ttas_futex const&) = delete;
    spinlock_ttas_futex & operator=( spinlock_ttas_futex const&) = delete;

    void lock() noexcept {
        static thread_local std::minstd_rand generator{ std::random_device{}() };
        std::int32_t collisions = 0, retries = 0, expected = 0;
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
                if ( BOOST_FIBERS_SPIN_BEFORE_SLEEP0 > retries) {
                    // give CPU a hint that this thread is in a "spin-wait" loop
                    // delays the next instruction's execution for a finite period of time (depends on processor family)
                    // the CPU is not under demand, parts of the pipeline are no longer being used
                    // -> reduces the power consumed by the CPU
                    // -> prevent pipeline stalls
                    cpu_relax();
                } else if ( BOOST_FIBERS_SPIN_BEFORE_YIELD > retries) {
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

#endif // BOOST_FIBERS_spinlock_ttas_futex_FUTEX_H

/* spinlock_ttas_futex.hpp
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
*/