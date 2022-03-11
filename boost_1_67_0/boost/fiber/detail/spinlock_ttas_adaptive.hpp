
//          Copyright Oliver Kowalke 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_SPINLOCK_TTAS_ADAPTIVE_H
#define BOOST_FIBERS_SPINLOCK_TTAS_ADAPTIVE_H

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