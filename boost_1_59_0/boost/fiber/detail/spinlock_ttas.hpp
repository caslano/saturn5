
//          Copyright Oliver Kowalke 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_SPINLOCK_TTAS_H
#define BOOST_FIBERS_SPINLOCK_TTAS_H

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

class spinlock_ttas {
private:
    template< typename FBSplk >
    friend class spinlock_rtm;

    std::atomic< spinlock_status >              state_{ spinlock_status::unlocked };

public:
    spinlock_ttas() = default;

    spinlock_ttas( spinlock_ttas const&) = delete;
    spinlock_ttas & operator=( spinlock_ttas const&) = delete;

    void lock() noexcept {
        static thread_local std::minstd_rand generator{ std::random_device{}() };
        std::size_t collisions = 0 ;
        for (;;) {
            // avoid using multiple pause instructions for a delay of a specific cycle count
            // the delay of cpu_relax() (pause on Intel) depends on the processor family
            // the cycle count can not guaranteed from one system to the next
            // -> check the shared variable 'state_' in between each cpu_relax() to prevent
            //    unnecessarily long delays on some systems
            std::size_t retries = 0;
            // test shared variable 'status_'
            // first access to 'state_' -> chache miss
            // sucessive acccess to 'state_' -> cache hit
            // if 'state_' was released by other fiber
            // cached 'state_' is invalidated -> cache miss
            while ( spinlock_status::locked == state_.load( std::memory_order_relaxed) ) {
#if !defined(BOOST_FIBERS_SPIN_SINGLE_CORE)
                if ( BOOST_FIBERS_SPIN_BEFORE_SLEEP0 > retries) {
                    ++retries;
                    // give CPU a hint that this thread is in a "spin-wait" loop
                    // delays the next instruction's execution for a finite period of time (depends on processor family)
                    // the CPU is not under demand, parts of the pipeline are no longer being used
                    // -> reduces the power consumed by the CPU
                    // -> prevent pipeline stalls
                    cpu_relax();
                } else if ( BOOST_FIBERS_SPIN_BEFORE_YIELD > retries) {
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

#endif // BOOST_FIBERS_SPINLOCK_TTAS_H

/* spinlock_ttas.hpp
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
*/