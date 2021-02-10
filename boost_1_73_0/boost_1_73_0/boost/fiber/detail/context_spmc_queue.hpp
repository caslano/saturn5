
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
khgVDPwYJvEA1kwL7cLZJDkJlwmc+YuFP09WEB6DP1/1eKeT+RFyQ6DXBvh13XCNUTQgNnUleH7P+U/tdMdLTmC8XEzDKEmjRfhhlcbxdBwskvRwGh7CAQz2f4O/WmkZPoBBJdZEAXjhvXju0QR9SznT21RzQ8XGf+SVRuj4BOb+LHC+gX/+FPA71I263kKGZ5UGMt4YUYiMIRGKBgu54RvVbGFdqbUFjVfzMIonsfOLkFnV5hzeUBQdN8t3jnWYKZz/PLg9WoEnJbKmQvJ8PTAXsJ4tKplFIM/whJ7D1zaCoyAeLyZRMgnnTsSwVgxqJaQhFmHj3LHqYFqiqu1VJLI0TCBNhSxUs2GULNjrrR2isxb/8CGwtWpRK+4cPruEK2QIrIVkOJMzw3ZMvZuyVltuO+hIkhZjQLTlJEmiuEt01/Odd9i02sCawyB6vj8g7sYco+eQNEzqWpFsNE6cYcokr75l2eBLMLMQYc0lZtMDu506Q17cbHO6bTtrXfMMQ8eY7eHOi8mDVUlWUbB3MDwvIs9xJt2pbYIFZVIYwSpMWw9idbJiF5qyh0pMafqinsgIShN5syVPqd1da8tqbLusK02uUHakMp2mYjIvOa87921RIDZrFOoHsILqh6CGDks6i4FanegaggJF
*/