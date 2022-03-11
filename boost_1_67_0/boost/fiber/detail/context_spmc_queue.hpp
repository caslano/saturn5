
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
+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
*/