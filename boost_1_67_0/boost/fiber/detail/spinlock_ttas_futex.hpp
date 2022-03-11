
//          Copyright Oliver Kowalke 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_spinlock_ttas_futex_FUTEX_H
#define BOOST_FIBERS_spinlock_ttas_futex_FUTEX_H

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