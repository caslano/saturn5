
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
HN+uF5b1eIiwTtRCYSHGuRZ8QiKn8ievdqCsVIoyu3Ki/FV+4fXh1u+lPqQJ6bsVNcCHTEVVUPpLmPSv5brRletKh6COuEhHpLos5OryBnAyKHFSl5dQXXYF9HqE6vIapkgFQuCnMEUKGNXlaiupS6qUXU6GOOUKdUMKqA+TIEDEW9WsHO3xWqQ2maynI9YvLSZYsQAuOpCY6wh8m03LkvbkUd0nRdk/QVkskaqnEVlJanLk36yczX+H1NSFUlPXicwMbQU86vvRVeHqTyNF7L+NtJferj0G0EKWpNCXx6GmIql7foFMVt+b8ERkvcafMjX7MdJjz39JjyP9mep7JrN/36pGPqj4pMHNuZVvhP+zLb56XMMThGaTxpYhrm+LjfoZhZxSzNmzXDvcJB1+Dh9ZNLzngPj/YjGX7WTzsqm6ceMRUfZ67eGf1S7TzRw6j62ikHyvLSZVoLe0o4BAcIDE3jwGVQEr2voTCTut5g+GN73fZOfJUrP7TVJjLZbK3m/CTN1EwEfnGY/+zknnGUMnw+a71AEQNSGs5LegrWr6BTE+GcskU8aTVmFPxp4oDeQXxy3NPxIXta3kTJRnSTrdGVLYoFH3RAuegd3uNULgQgQuVJRuiDf2X6WBnh2KPQUH2DqV1vF9lJZj1sNyiJsZbbEUFPegY63zqNQp5kn47oWzsamW5z+JtVDWR5R1szgAUvujgBcmkMqtpXLtsPJCYDWlfljMUi/Sxn+t0rXiPW7Q5oq7LKjlPYF+errdb+RBBtHsIgzdd3It9qQX1UckwVpTiJaGKi19hdpfCOmbCQRVeE4R73LpRY9Q6zd2S2StcgGzUJcR+q1dpMt0aDguI7WHvnPOWjFjV9jyFalusBcc/BhSwvYCo2s7meBBw1OCni15tJlot1yvq3YLPdoJWqczipIC76+jwUsMhV5ic7uoIyQaF733OslEFQ/VJaNG+u34hBXjviBAmEJtKAL/iCDWHi4NQF5K5T3dkPamYXsLThC/yC7b2TBJrZrkIVrEhSDJeOi+7MlxE27yjIWXJE9h7aK3nEy18fR+q1276AfWqA4yfwnP92C+U/vxNBlWmZ/H8qOt/mj/4g7F0LK0yFuma0qxX9eU3FpwAVMzQOzPrKAdnSUdJ7fLdiRataZNYy1AZgOZfRCyaT0cCH0tQkKJviSkL9lPqhVNmoWkOLZCFb7kGVdj0vQJFyr0wRp8oBjW//3vw5Nj88lmUGHS9grrU/vDmuNyaEjVdYoGFmVoCD8e5CGSMcfFeHDT13I8yJLDoThFU1vxpWrKsJ9IN1merdmFTtT1JQuvTZrcuC9RM6bgGOGwqhDzjBAsRTt0VEJ8Tr0m9eBhHEWakIU7lEajSNlLaugVU/YQFOghuSJJmPkmQzjcMxKzgtuZeNEDsubBVLCTNkWDHpkB9ZbiJg45RqIEe3bYk1HItlMcJC/i+jNmptmj+V/h/lF6UQsivDEQTjDH/k0Gme7GQIO86jSzaHnb9//2P51qeTXZ31LR5A0EsrfJ8K3ArqU2Q0mxF49da98Y7/iqZWXNy70yUWY5tWhoYnpRPGXdAlmkpF/9Ulrh/WzGn1F11xwTqrvML1U3W5oE1WM5xgOeeXqlvOVieAnadp+DDPF7cLRC2Qb9CdH5eU6Lr6nuNQkLB1+59zMT3ZfVDfRIKeMOHbKMAneyBC3wJlGdzRpaLKA4gkRK7AOJzMOoB/D64f4A6tq0mLKfsBWLP1H8MMesuZhafFT1Vr7eyxyK8bJqlE5ZknSEJEFOKv/UG6z8NbJXvCHKChqp3OQ3FEfFS6lPbuS9YSi994YuJSWj+i57X+bDrj7Zq72KyTTQlkAjiCE=
*/