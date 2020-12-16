
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
5cY204Pa6PuHjVGl18n7hyCqBEQxT0feP3iRPyft9w/oQS70oC/jWg+qTdwxAyfqyAuIy2bgRJ2pz1zyAqId+XMX+QsIOw/K1XvQ3Ftwoox40Au34ESZ3oMW13vQ+dhignjQCdhiQu9Bbo0HFWk9qN1yY7vpQe30LcfvN+P0G3nL8dnNOP1mIraAvOV4BvkL0n7LgR7kRg+67TGtB4UTh6E+P5DXHLuiPCCKGSzymmM95P+yyF9z2HlQnt6DrrkJ57+IB3XfhPNfeg9aQu9B9diiw6V60PrYIhA1HpSr8aBirQd1WG7sMD2og75LeehGrpLbpb5LufFGUAmIcl7Kpb5L6eJ8Rkz3XQp6UC56UEu/1oNqEquiPj6X+jKlDOUBUUxMudSXKT/cAHxGXNQvU+w8yKP3oKYbeGfKXKoHbYXKAlHjQWV6DyrAFiuIB/14PW+xQu9BeRoPKtF4EG4fQe7FvZ2EH+EF9NXNEddz3SqlKwFxd9StUkLHQFdf3WzA+YyY7qsbdKU8dKVJD2tdKZT44DquT0C6EhCfuw7kAVFO3UhXAv6tnM+Ii/rdjelK90tX8updaTHsTBVxpT96ubJVelcq17vS4728xRBxpduwxZDelTwaVyrVuBJuPULunQok6Up4AX1TNBl1q5GuBMRi1A2IYmZGuhLwv74W+IyY7psidCUPutKrD2pdqSpx8bU4NSNdCYinoDwgiqkZdCWx/znnM+KiflVEXWn+0FcjI3brAcHGK8raONM5vdtdIK510murxLVOm2tz6LUhcW2OzbUuem2N/ODT5lo3vTYsrnXbXJtLr62VH6TZXJtHr43ID5xsrvXQa+vkBzPKtfN3f2BkBK7rdeG6ojPb+bqifa7RrSuaPbJH9sge2SN7ZI/skT2yR/bIHtkje2SP7JE9ssdoDut65LByW2K9RrEe+UpNcj1yh7Ejcsgp9uOZ1Y378QAFN9XZeBvcjyfoxP14/JLTHVX244EbEqu0sv145jjEBWeuDtuiYGNwjcOJ783aDuTvzSpGuVmydX+CPXez7g917ZEL3x/KK1+WsrPow7D/015XP/JCtLvMKXhOgwfbQK226hX7qbwcgwe7Qe3h3P1ClecyeLAp1Jwv1ypXeW6DB3tDHbxy9cEqL9fgwRZRZ29z3/kqL8/gwU5RRWv63lV5HoMHG0ZNit6/FfDYp5qM9Gwk4mCHOInKk2dPgwVnlVNYvjXEN5EY5S5J6fsjB+3mXWz3m1p3y8z3m+L+vesucv+z3VP4t+Nsq39fuL/Ov2/dwurfWx1O/PumoL1/T99vrPy7ke9/1iC3zmhha/3E5N4LLT0cRWXzIpgnkFtOic2N5HYboVa25dRpuA8FXhwC0wfVDaP2PAu3nArRLaeCcHVL4sIC5iGtqVtYmrUA94Fnnio3ymgpeWCnyDllTuxFTyQSHUh4H8LLnjuFN3KOu0DllgruyXbcCsHtsOP6BfckO25QcE+044YE9wQ7blhw2wVX9PV40teo0teo2tfjrK1G1b4ea8eVfW2z48q+HmPHlX092o4r+3qUHVf2tVVwkxziNDYEGTu5wD5Lx+WwU/RMGFDEVlGhtlL4X6SkazV2//yt4CrhY8NFyX6aV9L5h8NoyXAy96C5sxqoBuRm3CWp2bi3WTBDqZjBVEx/KmZFKmZpKqZXx2wueYDN9J3jJYz5w2xub/7KzoUYyaszUgRIkVRG4m6eihlMxfSnYlakYpZqmQs1UsTOSMPu6vhwrtgmpnE0g232WOhhmy95n+v/HvbEssuXNrrl+S7YGssuX1r9l+l/wQ5ZdvnSt+tN2gc2yrLLl14547M7YL8su3xp+SmbrA7bZtk=
*/