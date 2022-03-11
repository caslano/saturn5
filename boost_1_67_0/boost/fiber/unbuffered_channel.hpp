
//          Copyright Oliver Kowalke 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_UNBUFFERED_CHANNEL_H
#define BOOST_FIBERS_UNBUFFERED_CHANNEL_H

#include <atomic>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include <boost/config.hpp>

#include <boost/fiber/channel_op_status.hpp>
#include <boost/fiber/context.hpp>
#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/convert.hpp>
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
#include <boost/fiber/detail/exchange.hpp>
#endif
#include <boost/fiber/detail/spinlock.hpp>
#include <boost/fiber/exceptions.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

template< typename T >
class unbuffered_channel {
public:
    using value_type = typename std::remove_reference<T>::type;

private:
    using wait_queue_type = context::wait_queue_t;

    struct slot {
        value_type  value;
        context *   ctx;

        slot( value_type const& value_, context * ctx_) :
            value{ value_ },
            ctx{ ctx_ } {
        }

        slot( value_type && value_, context * ctx_) :
            value{ std::move( value_) },
            ctx{ ctx_ } {
        }
    };

    // shared cacheline
    std::atomic< slot * >       slot_{ nullptr };
    // shared cacheline
    std::atomic_bool            closed_{ false };
    mutable detail::spinlock    splk_producers_{};
    wait_queue_type             waiting_producers_{};
    mutable detail::spinlock    splk_consumers_{};
    wait_queue_type             waiting_consumers_{};
    char                        pad_[cacheline_length];

    bool is_empty_() {
        return nullptr == slot_.load( std::memory_order_acquire);
    }

    bool try_push_( slot * own_slot) {
        for (;;) {
            slot * s = slot_.load( std::memory_order_acquire);
            if ( nullptr == s) {
                if ( ! slot_.compare_exchange_strong( s, own_slot, std::memory_order_acq_rel) ) {
                    continue;
                }
                return true;
            }
            return false;
        }
    }

    slot * try_pop_() {
        slot * nil_slot = nullptr;
        for (;;) {
            slot * s = slot_.load( std::memory_order_acquire);
            if ( nullptr != s) {
                if ( ! slot_.compare_exchange_strong( s, nil_slot, std::memory_order_acq_rel) ) {
                    continue;}
            }
            return s;
        }
    }

public:
    unbuffered_channel() = default;

    ~unbuffered_channel() {
        close();
    }

    unbuffered_channel( unbuffered_channel const&) = delete;
    unbuffered_channel & operator=( unbuffered_channel const&) = delete;

    bool is_closed() const noexcept {
        return closed_.load( std::memory_order_acquire);
    }

    void close() noexcept {
        context * active_ctx = context::active();
        // set flag
        if ( ! closed_.exchange( true, std::memory_order_acquire) ) {
            // notify current waiting  
            slot * s = slot_.load( std::memory_order_acquire);
            if ( nullptr != s) {
                // notify context
                active_ctx->schedule( s->ctx);
            }
            // notify all waiting producers
            detail::spinlock_lock lk1{ splk_producers_ };
            while ( ! waiting_producers_.empty() ) {
                context * producer_ctx = & waiting_producers_.front();
                waiting_producers_.pop_front();
                auto expected = reinterpret_cast< std::intptr_t >( this);
                if ( producer_ctx->twstatus.compare_exchange_strong( expected, static_cast< std::intptr_t >( -1), std::memory_order_acq_rel) ) {
                    // notify context
                    active_ctx->schedule( producer_ctx);
                } else if ( static_cast< std::intptr_t >( 0) == expected) {
                    // no timed-wait op.
                    // notify context
                    active_ctx->schedule( producer_ctx);
                }
            }
            // notify all waiting consumers
            detail::spinlock_lock lk2{ splk_consumers_ };
            while ( ! waiting_consumers_.empty() ) {
                context * consumer_ctx = & waiting_consumers_.front();
                waiting_consumers_.pop_front();
                auto expected = reinterpret_cast< std::intptr_t >( this);
                if ( consumer_ctx->twstatus.compare_exchange_strong( expected, static_cast< std::intptr_t >( -1), std::memory_order_acq_rel) ) {
                    // notify context
                    active_ctx->schedule( consumer_ctx);
                } else if ( static_cast< std::intptr_t >( 0) == expected) {
                    // no timed-wait op.
                    // notify context
                    active_ctx->schedule( consumer_ctx);
                }
            }
        }
    }

    channel_op_status push( value_type const& value) {
        context * active_ctx = context::active();
        slot s{ value, active_ctx };
        for (;;) {
            if ( BOOST_UNLIKELY( is_closed() ) ) {
                return channel_op_status::closed;
            }
            if ( try_push_( & s) ) {
                detail::spinlock_lock lk{ splk_consumers_ };
                // notify one waiting consumer
                while ( ! waiting_consumers_.empty() ) {
                    context * consumer_ctx = & waiting_consumers_.front();
                    waiting_consumers_.pop_front();
                    auto expected = reinterpret_cast< std::intptr_t >( this);
                    if ( consumer_ctx->twstatus.compare_exchange_strong( expected, static_cast< std::intptr_t >( -1), std::memory_order_acq_rel) ) {
                        // notify context
                        active_ctx->schedule( consumer_ctx);
                        break;
                    }
                    if ( static_cast< std::intptr_t >( 0) == expected) {
                        // no timed-wait op.
                        // notify context
                        active_ctx->schedule( consumer_ctx);
                        break;
                    }
                }
                // suspend till value has been consumed
                active_ctx->suspend( lk);
                // resumed
                if ( nullptr == s.ctx) {
                    // value has been consumed
                    return channel_op_status::success;
                }
                // channel was closed before value was consumed
                return channel_op_status::closed;
            }
            detail::spinlock_lock lk{ splk_producers_ };
            if ( BOOST_UNLIKELY( is_closed() ) ) {
                return channel_op_status::closed;
            }
            if ( is_empty_() ) {
                continue;
            }
            active_ctx->wait_link( waiting_producers_);
            active_ctx->twstatus.store( static_cast< std::intptr_t >( 0), std::memory_order_release);
            // suspend this producer
            active_ctx->suspend( lk);
            // resumed, slot mabye free
        }
    }

    channel_op_status push( value_type && value) {
        context * active_ctx = context::active();
        slot s{ std::move( value), active_ctx };
        for (;;) {
            if ( BOOST_UNLIKELY( is_closed() ) ) {
                return channel_op_status::closed;
            }
            if ( try_push_( & s) ) {
                detail::spinlock_lock lk{ splk_consumers_ };
                // notify one waiting consumer
                while ( ! waiting_consumers_.empty() ) {
                    context * consumer_ctx = & waiting_consumers_.front();
                    waiting_consumers_.pop_front();
                    auto expected = reinterpret_cast< std::intptr_t >( this);
                    if ( consumer_ctx->twstatus.compare_exchange_strong( expected, static_cast< std::intptr_t >( -1), std::memory_order_acq_rel) ) {
                        // notify context
                        active_ctx->schedule( consumer_ctx);
                        break;
                    } if ( static_cast< std::intptr_t >( 0) == expected) {
                        // no timed-wait op.
                        // notify context
                        active_ctx->schedule( consumer_ctx);
                        break;
                    }
                }
                // suspend till value has been consumed
                active_ctx->suspend( lk);
                // resumed
                if ( nullptr == s.ctx) {
                    // value has been consumed
                    return channel_op_status::success;
                }
                // channel was closed before value was consumed
                return channel_op_status::closed;
            }
            detail::spinlock_lock lk{ splk_producers_ };
            if ( BOOST_UNLIKELY( is_closed() ) ) {
                return channel_op_status::closed;
            }
            if ( is_empty_() ) {
                continue;
            }
            active_ctx->wait_link( waiting_producers_);
            active_ctx->twstatus.store( static_cast< std::intptr_t >( 0), std::memory_order_release);
            // suspend this producer
            active_ctx->suspend( lk);
            // resumed, slot mabye free
        }
    }

    template< typename Rep, typename Period >
    channel_op_status push_wait_for( value_type const& value,
                                     std::chrono::duration< Rep, Period > const& timeout_duration) {
        return push_wait_until( value,
                                std::chrono::steady_clock::now() + timeout_duration);
    }

    template< typename Rep, typename Period >
    channel_op_status push_wait_for( value_type && value,
                                     std::chrono::duration< Rep, Period > const& timeout_duration) {
        return push_wait_until( std::forward< value_type >( value),
                                std::chrono::steady_clock::now() + timeout_duration);
    }

    template< typename Clock, typename Duration >
    channel_op_status push_wait_until( value_type const& value,
                                       std::chrono::time_point< Clock, Duration > const& timeout_time_) {
        context * active_ctx = context::active();
        slot s{ value, active_ctx };
        std::chrono::steady_clock::time_point timeout_time = detail::convert( timeout_time_);
        for (;;) {
            if ( BOOST_UNLIKELY( is_closed() ) ) {
                return channel_op_status::closed;
            }
            if ( try_push_( & s) ) {
                detail::spinlock_lock lk{ splk_consumers_ };
                // notify one waiting consumer
                while ( ! waiting_consumers_.empty() ) {
                    context * consumer_ctx = & waiting_consumers_.front();
                    waiting_consumers_.pop_front();
                    auto expected = reinterpret_cast< std::intptr_t >( this);
                    if ( consumer_ctx->twstatus.compare_exchange_strong( expected, static_cast< std::intptr_t >( -1), std::memory_order_acq_rel) ) {
                        // notify context
                        active_ctx->schedule( consumer_ctx);
                        break;
                    }
                    if ( static_cast< std::intptr_t >( 0) == expected) {
                        // no timed-wait op.
                        // notify context
                        active_ctx->schedule( consumer_ctx);
                        break;
                    }
                }
                // suspend this producer
                active_ctx->twstatus.store( reinterpret_cast< std::intptr_t >( this), std::memory_order_release);
                if ( ! active_ctx->wait_until( timeout_time, lk) ) {
                    // clear slot
                    slot * nil_slot = nullptr, * own_slot = & s;
                    slot_.compare_exchange_strong( own_slot, nil_slot, std::memory_order_acq_rel);
                    // resumed, value has not been consumed
                    return channel_op_status::timeout;
                }
                // resumed
                if ( nullptr == s.ctx) {
                    // value has been consumed
                    return channel_op_status::success;
                }
                // channel was closed before value was consumed
                return channel_op_status::closed;
            }
            detail::spinlock_lock lk{ splk_producers_ };
            if ( BOOST_UNLIKELY( is_closed() ) ) {
                return channel_op_status::closed;
            }
            if ( is_empty_() ) {
                continue;
            }
            active_ctx->wait_link( waiting_producers_);
            active_ctx->twstatus.store( reinterpret_cast< std::intptr_t >( this), std::memory_order_release);
            // suspend this producer
            if ( ! active_ctx->wait_until( timeout_time, lk) ) {
                // relock local lk
                lk.lock();
                // remove from waiting-queue
                waiting_producers_.remove( * active_ctx);
                return channel_op_status::timeout;
            }
            // resumed, slot maybe free
        }
    }

    template< typename Clock, typename Duration >
    channel_op_status push_wait_until( value_type && value,
                                       std::chrono::time_point< Clock, Duration > const& timeout_time_) {
        context * active_ctx = context::active();
        slot s{ std::move( value), active_ctx };
        std::chrono::steady_clock::time_point timeout_time = detail::convert( timeout_time_);
        for (;;) {
            if ( BOOST_UNLIKELY( is_closed() ) ) {
                return channel_op_status::closed;
            }
            if ( try_push_( & s) ) {
                detail::spinlock_lock lk{ splk_consumers_ };
                // notify one waiting consumer
                while ( ! waiting_consumers_.empty() ) {
                    context * consumer_ctx = & waiting_consumers_.front();
                    waiting_consumers_.pop_front();
                    auto expected = reinterpret_cast< std::intptr_t >( this);
                    if ( consumer_ctx->twstatus.compare_exchange_strong( expected, static_cast< std::intptr_t >( -1), std::memory_order_acq_rel) ) {
                        // notify context
                        active_ctx->schedule( consumer_ctx);
                        break;
                    } if ( static_cast< std::intptr_t >( 0) == expected) {
                        // no timed-wait op.
                        // notify context
                        active_ctx->schedule( consumer_ctx);
                        break;
                    }
                }
                // suspend this producer
                active_ctx->twstatus.store( reinterpret_cast< std::intptr_t >( this), std::memory_order_release);
                if ( ! active_ctx->wait_until( timeout_time, lk) ) {
                    // clear slot
                    slot * nil_slot = nullptr, * own_slot = & s;
                    slot_.compare_exchange_strong( own_slot, nil_slot, std::memory_order_acq_rel);
                    // resumed, value has not been consumed
                    return channel_op_status::timeout;
                }
                // resumed
                if ( nullptr == s.ctx) {
                    // value has been consumed
                    return channel_op_status::success;
                }
                // channel was closed before value was consumed
                return channel_op_status::closed;
            }
            detail::spinlock_lock lk{ splk_producers_ };
            if ( BOOST_UNLIKELY( is_closed() ) ) {
                return channel_op_status::closed;
            }
            if ( is_empty_() ) {
                continue;
            }
            active_ctx->wait_link( waiting_producers_);
            active_ctx->twstatus.store( reinterpret_cast< std::intptr_t >( this), std::memory_order_release);
            // suspend this producer
            if ( ! active_ctx->wait_until( timeout_time, lk) ) {
                // relock local lk
                lk.lock();
                // remove from waiting-queue
                waiting_producers_.remove( * active_ctx);
                return channel_op_status::timeout;
            }
            // resumed, slot maybe free
        }
    }

    channel_op_status pop( value_type & value) {
        context * active_ctx = context::active();
        slot * s = nullptr;
        for (;;) {
            if ( nullptr != ( s = try_pop_() ) ) {
                {
                    detail::spinlock_lock lk{ splk_producers_ };
                    // notify one waiting producer
                    while ( ! waiting_producers_.empty() ) {
                        context * producer_ctx = & waiting_producers_.front();
                        waiting_producers_.pop_front();
                        auto expected = reinterpret_cast< std::intptr_t >( this);
                        if ( producer_ctx->twstatus.compare_exchange_strong( expected, static_cast< std::intptr_t >( -1), std::memory_order_acq_rel) ) {
                            lk.unlock();
                            // notify context
                            active_ctx->schedule( producer_ctx);
                            break;
                        } if ( static_cast< std::intptr_t >( 0) == expected) {
                            lk.unlock();
                            // no timed-wait op.
                            // notify context
                            active_ctx->schedule( producer_ctx);
                            break;
                        }
                    }
                }
                value = std::move( s->value);
                // notify context
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
                active_ctx->schedule( detail::exchange( s->ctx, nullptr) );
#else
                active_ctx->schedule( std::exchange( s->ctx, nullptr) );
#endif
                return channel_op_status::success;
            }
            detail::spinlock_lock lk{ splk_consumers_ };
            if ( BOOST_UNLIKELY( is_closed() ) ) {
                return channel_op_status::closed;
            }
            if ( ! is_empty_() ) {
                continue;
            }
            active_ctx->wait_link( waiting_consumers_);
            active_ctx->twstatus.store( static_cast< std::intptr_t >( 0), std::memory_order_release);
            // suspend this consumer
            active_ctx->suspend( lk);
            // resumed, slot mabye set
        }
    }

    value_type value_pop() {
        context * active_ctx = context::active();
        slot * s = nullptr;
        for (;;) {
            if ( nullptr != ( s = try_pop_() ) ) {
                {
                    detail::spinlock_lock lk{ splk_producers_ };
                    // notify one waiting producer
                    while ( ! waiting_producers_.empty() ) {
                        context * producer_ctx = & waiting_producers_.front();
                        waiting_producers_.pop_front();
                        auto expected = reinterpret_cast< std::intptr_t >( this);
                        if ( producer_ctx->twstatus.compare_exchange_strong( expected, static_cast< std::intptr_t >( -1), std::memory_order_acq_rel) ) {
                            lk.unlock();
                            // notify context
                            active_ctx->schedule( producer_ctx);
                            break;
                        } if ( static_cast< std::intptr_t >( 0) == expected) {
                            lk.unlock();
                            // no timed-wait op.
                            // notify context
                            active_ctx->schedule( producer_ctx);
                            break;
                        }
                    }
                }
                // consume value
                value_type value = std::move( s->value);
                // notify context
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
                active_ctx->schedule( detail::exchange( s->ctx, nullptr) );
#else
                active_ctx->schedule( std::exchange( s->ctx, nullptr) );
#endif
                return std::move( value);
            }
            detail::spinlock_lock lk{ splk_consumers_ };
            if ( BOOST_UNLIKELY( is_closed() ) ) {
                throw fiber_error{
                        std::make_error_code( std::errc::operation_not_permitted),
                        "boost fiber: channel is closed" };
            }
            if ( ! is_empty_() ) {
                continue;
            }
            active_ctx->wait_link( waiting_consumers_);
            active_ctx->twstatus.store( static_cast< std::intptr_t >( 0), std::memory_order_release);
            // suspend this consumer
            active_ctx->suspend( lk);
            // resumed, slot mabye set
        }
    }

    template< typename Rep, typename Period >
    channel_op_status pop_wait_for( value_type & value,
                                    std::chrono::duration< Rep, Period > const& timeout_duration) {
        return pop_wait_until( value,
                               std::chrono::steady_clock::now() + timeout_duration);
    }

    template< typename Clock, typename Duration >
    channel_op_status pop_wait_until( value_type & value,
                                      std::chrono::time_point< Clock, Duration > const& timeout_time_) {
        context * active_ctx = context::active();
        slot * s = nullptr;
        std::chrono::steady_clock::time_point timeout_time = detail::convert( timeout_time_);
        for (;;) {
            if ( nullptr != ( s = try_pop_() ) ) {
                {
                    detail::spinlock_lock lk{ splk_producers_ };
                    // notify one waiting producer
                    while ( ! waiting_producers_.empty() ) {
                        context * producer_ctx = & waiting_producers_.front();
                        waiting_producers_.pop_front();
                        auto expected = reinterpret_cast< std::intptr_t >( this);
                        if ( producer_ctx->twstatus.compare_exchange_strong( expected, static_cast< std::intptr_t >( -1), std::memory_order_acq_rel) ) {
                            lk.unlock();
                            // notify context
                            active_ctx->schedule( producer_ctx);
                            break;
                        }
                        if ( static_cast< std::intptr_t >( 0) == expected) {
                            lk.unlock();
                            // no timed-wait op.
                            // notify context
                            active_ctx->schedule( producer_ctx);
                            break;
                        }
                    }
                }
                // consume value
                value = std::move( s->value);
                // notify context
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
                active_ctx->schedule( detail::exchange( s->ctx, nullptr) );
#else
                active_ctx->schedule( std::exchange( s->ctx, nullptr) );
#endif
                return channel_op_status::success;
            }
            detail::spinlock_lock lk{ splk_consumers_ };
            if ( BOOST_UNLIKELY( is_closed() ) ) {
                return channel_op_status::closed;
            }
            if ( ! is_empty_() ) {
                continue;
            }
            active_ctx->wait_link( waiting_consumers_);
            active_ctx->twstatus.store( reinterpret_cast< std::intptr_t >( this), std::memory_order_release);
            // suspend this consumer
            if ( ! active_ctx->wait_until( timeout_time, lk) ) {
                // relock local lk
                lk.lock();
                // remove from waiting-queue
                waiting_consumers_.remove( * active_ctx);
                return channel_op_status::timeout;
            }
        }
    }

    class iterator {
    private:
        typedef typename std::aligned_storage< sizeof( value_type), alignof( value_type) >::type  storage_type;

        unbuffered_channel  *   chan_{ nullptr };
        storage_type            storage_;

        void increment_() {
            BOOST_ASSERT( nullptr != chan_);
            try {
                ::new ( static_cast< void * >( std::addressof( storage_) ) ) value_type{ chan_->value_pop() };
            } catch ( fiber_error const&) {
                chan_ = nullptr;
            }
        }

    public:
        using iterator_category = std::input_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type *;
        using reference = value_type &;

        using pointer_t = pointer;
        using reference_t = reference;

        iterator() noexcept = default;

        explicit iterator( unbuffered_channel< T > * chan) noexcept :
            chan_{ chan } {
            increment_();
        }

        iterator( iterator const& other) noexcept :
            chan_{ other.chan_ } {
        }

        iterator & operator=( iterator const& other) noexcept {
            if ( this == & other) return * this;
            chan_ = other.chan_;
            return * this;
        }

        bool operator==( iterator const& other) const noexcept {
            return other.chan_ == chan_;
        }

        bool operator!=( iterator const& other) const noexcept {
            return other.chan_ != chan_;
        }

        iterator & operator++() {
            reinterpret_cast< value_type * >( std::addressof( storage_) )->~value_type();
            increment_();
            return * this;
        }

        const iterator operator++( int) = delete;

        reference_t operator*() noexcept {
            return * reinterpret_cast< value_type * >( std::addressof( storage_) );
        }

        pointer_t operator->() noexcept {
            return reinterpret_cast< value_type * >( std::addressof( storage_) );
        }
    };

    friend class iterator;
};

template< typename T >
typename unbuffered_channel< T >::iterator
begin( unbuffered_channel< T > & chan) {
    return typename unbuffered_channel< T >::iterator( & chan);
}

template< typename T >
typename unbuffered_channel< T >::iterator
end( unbuffered_channel< T > &) {
    return typename unbuffered_channel< T >::iterator();
}

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_UNBUFFERED_CHANNEL_H

/* unbuffered_channel.hpp
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
*/