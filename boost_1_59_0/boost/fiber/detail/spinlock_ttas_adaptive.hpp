
//          Copyright Oliver Kowalke 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_SPINLOCK_TTAS_ADAPTIVE_H
#define BOOST_FIBERS_SPINLOCK_TTAS_ADAPTIVE_H

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <random>
#include <thread>

#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/cpu_relax.hpp>
#include <boost/fiber/detail/spinlock_status.hpp>

// based on informations from:
// https://software.intel.com/en-us/articles/benefitting-power-and-performance-sleep-loops
// https://software.intel.com/en-us/articles/long-duration-spin-wait-loops-on-hyper-threading-technology-enabled-intel-processors

namespace boost {
namespace fibers {
namespace detail {

class spinlock_ttas_adaptive {
private:
    template< typename FBSplk >
    friend class spinlock_rtm;

    std::atomic< spinlock_status >              state_{ spinlock_status::unlocked };
    std::atomic< std::size_t >                  retries_{ 0 };

public:
    spinlock_ttas_adaptive() = default;

    spinlock_ttas_adaptive( spinlock_ttas_adaptive const&) = delete;
    spinlock_ttas_adaptive & operator=( spinlock_ttas_adaptive const&) = delete;

    void lock() noexcept {
        static thread_local std::minstd_rand generator{ std::random_device{}() };
        std::size_t collisions = 0 ;
        for (;;) {
            std::size_t retries = 0;
            const std::size_t prev_retries = retries_.load( std::memory_order_relaxed);
            const std::size_t max_relax_retries = (std::min)(
                    static_cast< std::size_t >( BOOST_FIBERS_SPIN_BEFORE_SLEEP0), 2 * prev_retries + 10);
            const std::size_t max_sleep_retries = (std::min)(
                    static_cast< std::size_t >( BOOST_FIBERS_SPIN_BEFORE_YIELD), 2 * prev_retries + 10);
            // avoid using multiple pause instructions for a delay of a specific cycle count
            // the delay of cpu_relax() (pause on Intel) depends on the processor family
            // the cycle count can not guaranteed from one system to the next
            // -> check the shared variable 'state_' in between each cpu_relax() to prevent
            //    unnecessarily long delays on some systems
            // test shared variable 'status_'
            // first access to 'state_' -> chache miss
            // sucessive acccess to 'state_' -> cache hit
            // if 'state_' was released by other fiber
            // cached 'state_' is invalidated -> cache miss
            while ( spinlock_status::locked == state_.load( std::memory_order_relaxed) ) {
#if !defined(BOOST_FIBERS_SPIN_SINGLE_CORE)
                if ( max_relax_retries > retries) {
                    ++retries;
                    // give CPU a hint that this thread is in a "spin-wait" loop
                    // delays the next instruction's execution for a finite period of time (depends on processor family)
                    // the CPU is not under demand, parts of the pipeline are no longer being used
                    // -> reduces the power consumed by the CPU
                    // -> prevent pipeline stalls
                    cpu_relax();
                } else if ( max_sleep_retries > retries) {
                    ++retries;
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
                std::this_thread::yield();
#endif
            }
            // test-and-set shared variable 'status_'
            // everytime 'status_' is signaled over the bus, even if the test failes
            if ( spinlock_status::locked == state_.exchange( spinlock_status::locked, std::memory_order_acquire) ) {
                // spinlock now contended
                // utilize 'Binary Exponential Backoff' algorithm
                // linear_congruential_engine is a random number engine based on Linear congruential generator (LCG)
                std::uniform_int_distribution< std::size_t > distribution{
                    0, static_cast< std::size_t >( 1) << (std::min)(collisions, static_cast< std::size_t >( BOOST_FIBERS_CONTENTION_WINDOW_THRESHOLD)) };
                const std::size_t z = distribution( generator);
                ++collisions;
                for ( std::size_t i = 0; i < z; ++i) {
                    // -> reduces the power consumed by the CPU
                    // -> prevent pipeline stalls
                    cpu_relax();
                }
            } else {
                retries_.store( prev_retries + (retries - prev_retries) / 8, std::memory_order_relaxed);
                // success, thread has acquired the lock
                break;
            }
        }
    }

    bool try_lock() noexcept {
        return spinlock_status::unlocked == state_.exchange( spinlock_status::locked, std::memory_order_acquire);
    }

    void unlock() noexcept {
        state_.store( spinlock_status::unlocked, std::memory_order_release);
    }
};

}}}

#endif // BOOST_FIBERS_SPINLOCK_TTAS_ADAPTIVE_H

/* spinlock_ttas_adaptive.hpp
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
*/