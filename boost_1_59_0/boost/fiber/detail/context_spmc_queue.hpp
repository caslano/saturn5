
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
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
*/