
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_CONTEXT_SPMC_QUEUE_H
#define BOOST_FIBERS_DETAIL_CONTEXT_SPMC_QUEUE_H

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <type_traits>
#include <utility>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/context.hpp>

// David Chase and Yossi Lev. Dynamic circular work-stealing deque.
// In SPAA ’05: Proceedings of the seventeenth annual ACM symposium
// on Parallelism in algorithms and architectures, pages 21–28,
// New York, NY, USA, 2005. ACM.
//
// Nhat Minh Lê, Antoniu Pop, Albert Cohen, and Francesco Zappa Nardelli. 2013.
// Correct and efficient work-stealing for weak memory models.
// In Proceedings of the 18th ACM SIGPLAN symposium on Principles and practice
// of parallel programming (PPoPP '13). ACM, New York, NY, USA, 69-80.

#if BOOST_COMP_CLANG
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif

namespace boost {
namespace fibers {
namespace detail {

class context_spmc_queue {
private:
    class array {
    private:
        typedef std::atomic< context * >                atomic_type;
        typedef atomic_type                             storage_type; 

        std::size_t         capacity_;
        storage_type    *   storage_;

    public:
        array( std::size_t capacity) :
            capacity_{ capacity },
            storage_{ new storage_type[capacity_] } {
            for ( std::size_t i = 0; i < capacity_; ++i) {
                ::new ( static_cast< void * >( std::addressof( storage_[i]) ) ) atomic_type{ nullptr };
            }
        }

        ~array() {
            for ( std::size_t i = 0; i < capacity_; ++i) {
                reinterpret_cast< atomic_type * >( std::addressof( storage_[i]) )->~atomic_type();
            }
            delete [] storage_;
        }

        std::size_t capacity() const noexcept {
            return capacity_;
        }

        void push( std::size_t bottom, context * ctx) noexcept {
            reinterpret_cast< atomic_type * >(
                std::addressof( storage_[bottom % capacity_]) )
                    ->store( ctx, std::memory_order_relaxed);
        }

        context * pop( std::size_t top) noexcept {
            return reinterpret_cast< atomic_type * >(
                std::addressof( storage_[top % capacity_]) )
                    ->load( std::memory_order_relaxed);
        }

        array * resize( std::size_t bottom, std::size_t top) {
            std::unique_ptr< array > tmp{ new array{ 2 * capacity_ } };
            for ( std::size_t i = top; i != bottom; ++i) {
                tmp->push( i, pop( i) );
            }
            return tmp.release();
        }
    };

    std::atomic< std::size_t >     top_{ 0 };
    std::atomic< std::size_t >     bottom_{ 0 };
    std::atomic< array * >         array_;
    std::vector< array * >                                  old_arrays_{};
    char                                                    padding_[cacheline_length];

public:
    context_spmc_queue( std::size_t capacity = 4096) :
        array_{ new array{ capacity } } {
        old_arrays_.reserve( 32);
    }

    ~context_spmc_queue() {
        for ( array * a : old_arrays_) {
            delete a;
        }
        delete array_.load();
    }

    context_spmc_queue( context_spmc_queue const&) = delete;
    context_spmc_queue & operator=( context_spmc_queue const&) = delete;

    bool empty() const noexcept {
        std::size_t bottom = bottom_.load( std::memory_order_relaxed);
        std::size_t top = top_.load( std::memory_order_relaxed);
        return bottom <= top;
    }

    void push( context * ctx) {
        std::size_t bottom = bottom_.load( std::memory_order_relaxed);
        std::size_t top = top_.load( std::memory_order_acquire);
        array * a = array_.load( std::memory_order_relaxed);
        if ( (a->capacity() - 1) < (bottom - top) ) {
            // queue is full
            // resize
            array * tmp = a->resize( bottom, top);
            old_arrays_.push_back( a);
            std::swap( a, tmp);
            array_.store( a, std::memory_order_relaxed);
        }
        a->push( bottom, ctx);
        std::atomic_thread_fence( std::memory_order_release);
        bottom_.store( bottom + 1, std::memory_order_relaxed);
    }

    context * pop() {
        std::size_t bottom = bottom_.load( std::memory_order_relaxed) - 1;
        array * a = array_.load( std::memory_order_relaxed);
        bottom_.store( bottom, std::memory_order_relaxed);
        std::atomic_thread_fence( std::memory_order_seq_cst);
        std::size_t top = top_.load( std::memory_order_relaxed);
        context * ctx = nullptr;
        if ( top <= bottom) {
            // queue is not empty
            ctx = a->pop( bottom);
            BOOST_ASSERT( nullptr != ctx);
            if ( top == bottom) {
                // last element dequeued
                if ( ! top_.compare_exchange_strong( top, top + 1,
                                                     std::memory_order_seq_cst,
                                                     std::memory_order_relaxed) ) {
                    // lose the race
                    ctx = nullptr;
                }
                bottom_.store( bottom + 1, std::memory_order_relaxed);
            }
        } else {
            // queue is empty
            bottom_.store( bottom + 1, std::memory_order_relaxed);
        }
        return ctx;
    }

    context * steal() {
        std::size_t top = top_.load( std::memory_order_acquire);
        std::atomic_thread_fence( std::memory_order_seq_cst);
        std::size_t bottom = bottom_.load( std::memory_order_acquire);
        context * ctx = nullptr;
        if ( top < bottom) {
            // queue is not empty
            array * a = array_.load( std::memory_order_consume);
            ctx = a->pop( top);
            BOOST_ASSERT( nullptr != ctx);
            // do not steal pinned context (e.g. main-/dispatcher-context)
            if ( ctx->is_context( type::pinned_context) ) {
                return nullptr;
            }
            if ( ! top_.compare_exchange_strong( top, top + 1,
                                                 std::memory_order_seq_cst,
                                                 std::memory_order_relaxed) ) {
                // lose the race
                return nullptr;
            }
        }
        return ctx;
    }
};

}}}

#if BOOST_COMP_CLANG
#pragma clang diagnostic pop
#endif

#endif // BOOST_FIBERS_DETAIL_CONTEXT_SPMC_QUEUE_H

/* context_spmc_queue.hpp
mpn13HrLtVXXHdleVy8vQMCXQB6lSh2YNL86Y16FuWxFdWmBbChZOYqEmnXg1k+EDoycYwIqNwOFNUD3EZAiaEOaIuhJNLTPsM/yAGfcBU+qBlbYeaY6i1WdVB3rbHvVPlm1p3YYVGNckW2/5S7XY74JaR1vwP0RrvLJCLA86jlPVoR3PwEK9cna3Gy6aYjgPkL7+xngwxmp+dYlVaAKC/w2SSPEEOmIRw+xoNik0POQcjIpknS2KtSsIaJZRXwR1By2Ku2p5v5QM1WRi204H6qn19Ph1YlWv4XWUGczrTvR7u5NVCz7FF6NfaeZ46LI4fcSNbQGySPbeNCR1tK4tNJNTEwrzuws8ckRLeReKnodCK8ckpR7shWckdpRziFzEk2pC07F1MiZ1Dy6sL4eaOZpBEqRbO6SDBEmCHUH2v5TZfHfipvATrX4OZC8ln0YQRlZ/+UHtseXTqmqBAS0FmtgP6IgBbgwApDSaz945aav8TWCPr9qcJqevoCVvpNU8U/B9jG/zUIyPvWpS+zcjIluV8yYt8qalAVJuDrs0EGK43aQLJNi8JlbGVABiPNlG9fJNspPEBzNkg3sAPlOfBcOXEDdktxL0fSFqsMI/UhwN9vEqyxTJR/+SF3ixhBJot6M+feJG38g3zSdgIKLXZpRlEOO3zSIiH0/JiEZ5az4LAMplXAne/ESM3r+rrnYm1XoNlu0d8ErxojW8Xsy4cTvWPxMZ0HxAwLN1MUJdKQp/v3XLS33nRQbZ4J5V2+lRifTW7mRnta4W37h/NRNta1iNRc4fq92ClUvvaoOfO99kDbXhoy3P91eFz0veg4psR0ZYCu4DC9ghYy1UAz1gLyu0dhe15QPJDjf9/FupmgfzezY2pJWGNSKjus3eL8VkbqAUFluO8uBILv1SxAdTQcu7+mq+2ZE5Rx8tt4Dfi3d7n1ox3bUbGKtDT7vJ/b1D5Yv5g9VLK1XVXdTVUtNVS3lqszNbgNHq5r6zeKm7l8PifN/GWr7YGGF0aIPuBV0YKcDbUvoNJAP7JTE7n8CZxrOfTzEn9NWm6kDr1JKgDZVc6Lbkkh1JXaDunidAna1bqpja5CS541t9g3QiqRzJegL5fMd7Aj/ctDr+n7nypvMv1bpev7NJP59nMf8m8z823lI8M9oNP8S4vAvF3ejE9mjwFei4z5gMBvYjN5foMzYgDGTzpvczPp2iIPuPBkWKxL5xNKC6FONFMQFFx5rQTRBPoXi/Fsq64RSMUOVkcYWM+U5iS4JdBZPLmWV0dd1gWrF/6AkL0iLCmKVbyBJ9+iFKN3bUbqlsfsPwKsn1G+6CbU4UVEunqpVNT5TNX3t1fR1YzV8t9s9oprrrNWsO6CqGWuuJjeu1CeqWvvhYIsME6/UCVpaGhG9MCpaUEgtOEm0YLy1BV24BZ/DqxW8QlVZJtBcS2je7o9opljRfPaNQiPjbX7vzG6mjZQrBdAEK9DjCig60UQmnfzKlVvvc7E/4gEuGpGTCd1QgW6yFd0oRtcBGy47cZAmiNP7el2Y2ohjQsfNTzceisX9/8l8fiqsrtM3L8wLj3tGilrSUKPkvATeMgI9GLNm0VXNMjbfAs4S/V6c/BCFgMPPyH3DfWnVZMD72803IlO3eJZE8nxfDmtPYZHU7FPd4gXCC7XiX1o9tJ3+wSw+/UPncqr/yd6VwEVVhPHdZYEVETBRMI8sqSgz8SjX1IKi2sqSyhKzklKTNJUUisojQxREVDRTM6/MK8XsRjMF8UDDCw+8RSlb3A7t1CxpvvnezL637O6b97Dzt++XsW/ezDfffP9vvrm/ucXD6Z8FeCwkhn008o/UGzeJUW3EjTHSKY8Y2WI=
*/