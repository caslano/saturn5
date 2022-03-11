
//          Copyright Oliver Kowalke 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_SPINLOCK_TTAS_H
#define BOOST_FIBERS_SPINLOCK_TTAS_H

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