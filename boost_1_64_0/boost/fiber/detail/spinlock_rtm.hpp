
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
7Bbwk+2dI/qUo7F3jtXeWL3P4x28UdobiI8wIi4hKzo4Q9ob+Fcif4bZwVpQzPKVdIjbOyzsLTYGPO03rb0jiU1RnZnS3kCsQnEzTXVmSXsD34f8WUq4MfER9cvxiDCvINQRe9eifc0/SMBz7Bbwk+3tEn1yaeztsrF3VaL5I97B+6S9gbgtI+Iar6KDfdLewF8d+X1mB8OGvUPgP8KxuL1rhL3F5oqlv2rtXZt4ZS5Xp1/aG4j9c7m4flOduLQ38K9CflwJNya+1lCjDsxbK8wrCBFi7zDa1/xrCzzHbgE/2d5u0Se3xt5uG3sHEws+5B18StobiO8yIq7DKjo4iPYW3z8hf9Dg48CXNHAGub1Dqr3dzN69P2vtHU7si+rMlvYGYj2Km22qMyTtDfwq5AOxOvkxEgHzhhV7RwgALut4bTueJ9s7V/QpV2PvXBt71yVO+4B38HVpbyAexoi4fKbo4Bxpb+Bvi/w5Bh8HvqSBs47bu0q1dy6zd+gnrb1rEt++z9V5T9obiO8xIq7+KNSZK+0N/H7kz0W+9TFSi3+JguaVhLC0t3W8th3Pk+2dJ/qUp7F3no29I4lS7OAn0t5A/P096AAQRQcT0t7Afxf5CSUhcCUPnBFu76Bq7zxm7/gPWnuHEqezlsU6fksI4hQU96WpzgJpb+DXIx+I1cmPkTD+sY1p7zABwGUdr23H82R7e0SfPBp7e4i9xdjX+y7v4A/S3kDsYURc2E508Bdpb+AfhvxflITAlTxw1nJ716n29jB7x77X2rsqsRiq8wfaW6x/8Q4X94dUB9czKxD895APxOrkx0iNmv5JggTAZR2vbcfzZHt7RZ+8Gnt7bfPv0Du8g26nmn8vyzsARNFBr1PNv39/G/iMmGn+7WX2nvttivz7ure5Oj6nmn9PRXE+U51StLdY/53zGXE88+980ad8jb3zbfPv+BzewTJpbyDePod3oMzsYIVTzb97OJ8RM82/85m9WxekyL/XRnUqpb2BWIniKk11/E41//7jLeAz4njm3wWiTwUaexfY5t+xt3gHA9LeQNwIOxAwOxhEe4v1jzifETPNvwuYvR3fpMi/B97k6lRJewNx5psgDohCnZBTzb+ncj4jjmf+XSj6VKixd6Ft/j33Dd7BGmlvIL7wBu9AjdnBsFPNv2/nfEbMNP8uZPae9lWK/HtHVKdW2huItSiu1lQn4lTz70rOZ8TxzL99ok8+jb19tvl36+u8g3XS3kDc83XegTqzg1Gnmn9vxPmMmGn+7WP29n+ZIv/+6DWuTr20NxBnv8bF1ZvqxJxq/j2T8xlxPPPvItGnIo29i2zzbwd2sEHaG4jDr/IONJgdbHSq+fcLnM+ImebfRczes75IkX8f9SpXp0naG4hNKK7JVKfZqebftZzPiOOZfxeLPhVr7F1sm39Pe4V38ABpbyCe9ArvwAFmB1ucav69J+czYqb5dzGzd2R+ivzbiepMkfYG4pdDIA6IQp1Wp5p/z+Z8RhzP/LtE9KlEY+8S2/zbP8Q72CbtDcRC7ECb2cF2p5p/D78MfEbMNP8uYfYe+jxF/n3hy1ydDmlvIHaguA5TndNI/t2E/NPGJf/mb8LF1i7R+fFJxstxuSJxAK/AaeQoP5ErEgdgMeEU13gXeo32AgEzv6J7KocaJrhp+r/2S9y+XST9r3wJ7AdE+fqdpP9/vIiv3zNO/+H1+0efpkj/r38RX7+T9P88FAdE8fqdpP+HI3/auKT/EwpbZwpsaxK7zMZX/aTUiMzGV/2mMS8jpYYf+ZdlXGrAq/7cT1KUGs+8gK/6Salx9wv4qt9Up5eUGhciv3dcSo0JhW1OCmxDiROex2kFUtY=
*/