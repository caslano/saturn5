
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_SPINLOCK_RTM_H
#define BOOST_FIBERS_SPINLOCK_RTM_H

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