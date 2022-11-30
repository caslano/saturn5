
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_SPINLOCK_RTM_H
#define BOOST_FIBERS_SPINLOCK_RTM_H

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <random>
#include <thread>

#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/cpu_relax.hpp>
#include <boost/fiber/detail/rtm.hpp>
#include <boost/fiber/detail/spinlock_status.hpp>

namespace boost {
namespace fibers {
namespace detail {

template< typename FBSplk >
class spinlock_rtm {
private:
    FBSplk              splk_{};

public:
    spinlock_rtm() = default;

    spinlock_rtm( spinlock_rtm const&) = delete;
    spinlock_rtm & operator=( spinlock_rtm const&) = delete;

    void lock() noexcept {
        static thread_local std::minstd_rand generator{ std::random_device{}() };
        std::size_t collisions = 0 ;
        for ( std::size_t retries = 0; retries < BOOST_FIBERS_RETRY_THRESHOLD; ++retries) {
            std::uint32_t status;
            if ( rtm_status::success == ( status = rtm_begin() ) ) {
                // add lock to read-set
                if ( spinlock_status::unlocked == splk_.state_.load( std::memory_order_relaxed) ) {
                    // lock is free, enter critical section
                    return;
                }
                // lock was acquired by another thread
                // explicit abort of transaction with abort argument 'lock not free'
                rtm_abort_lock_not_free();
            }
            // transaction aborted
            if ( rtm_status::none != (status & rtm_status::may_retry) ||
                 rtm_status::none != (status & rtm_status::memory_conflict) ) {
                // another logical processor conflicted with a memory address that was
                // part or the read-/write-set
                if ( BOOST_FIBERS_CONTENTION_WINDOW_THRESHOLD > collisions) {
                    std::uniform_int_distribution< std::size_t > distribution{
                        0, static_cast< std::size_t >( 1) << (std::min)(collisions, static_cast< std::size_t >( BOOST_FIBERS_CONTENTION_WINDOW_THRESHOLD)) };
                    const std::size_t z = distribution( generator);
                    ++collisions;
                    for ( std::size_t i = 0; i < z; ++i) {
                        cpu_relax();
                    }
                } else {
                    std::this_thread::yield();
                }
            } else if ( rtm_status::none != (status & rtm_status::explicit_abort) &&
                        rtm_status::none == (status & rtm_status::nested_abort) ) {
                // another logical processor has acquired the lock and
                // abort was not caused by a nested transaction
                // wait till lock becomes free again
                std::size_t count = 0;
                while ( spinlock_status::locked == splk_.state_.load( std::memory_order_relaxed) ) {
                    if ( BOOST_FIBERS_SPIN_BEFORE_SLEEP0 > count) {
                        ++count;
                        cpu_relax();
                    } else if ( BOOST_FIBERS_SPIN_BEFORE_YIELD > count) {
                        ++count; 
                        static constexpr std::chrono::microseconds us0{ 0 };
                        std::this_thread::sleep_for( us0);
#if 0
                        using namespace std::chrono_literals;
                        std::this_thread::sleep_for( 0ms);
#endif
                    } else {
                        std::this_thread::yield();
                    }
                }
            } else {
                // transaction aborted due: 
                //  - internal buffer to track transactional state overflowed
                //  - debug exception or breakpoint exception was hit
                //  - abort during execution of nested transactions (max nesting limit exceeded)
                // -> use fallback path
                break;
            }
        }
        splk_.lock();
    }

    bool try_lock() noexcept {
        if ( rtm_status::success != rtm_begin() ) {
            return false;
        }

        // add lock to read-set
        if ( spinlock_status::unlocked != splk_.state_.load( std::memory_order_relaxed) ) {
            // lock was acquired by another thread
            // explicit abort of transaction with abort argument 'lock not free'
            rtm_abort_lock_not_free();
        }
        return true;
    }

    void unlock() noexcept {
        if ( spinlock_status::unlocked == splk_.state_.load( std::memory_order_acquire) ) {
            rtm_end();
        } else {
            splk_.unlock();
        }
    }
};

}}}

#endif // BOOST_FIBERS_SPINLOCK_RTM_H

/* spinlock_rtm.hpp
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
*/