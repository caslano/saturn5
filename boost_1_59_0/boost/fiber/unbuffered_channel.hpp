
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
#include <boost/fiber/waker.hpp>

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
    struct slot {
        value_type  value;
        waker       w;

        slot( value_type const& value_, waker && w) :
            value{ value_ },
            w{ std::move(w) } {
        }

        slot( value_type && value_, waker && w) :
            value{ std::move( value_) },
            w{ std::move(w) } {
        }
    };

    // shared cacheline
    std::atomic< slot * >       slot_{ nullptr };
    // shared cacheline
    std::atomic_bool            closed_{ false };
    mutable detail::spinlock    splk_producers_{};
    wait_queue                  waiting_producers_{};
    mutable detail::spinlock    splk_consumers_{};
    wait_queue                  waiting_consumers_{};
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
        // set flag
        if ( ! closed_.exchange( true, std::memory_order_acquire) ) {
            // notify current waiting  
            slot * s = slot_.load( std::memory_order_acquire);
            if ( nullptr != s) {
                // notify context
                s->w.wake();
            }
            detail::spinlock_lock lk1{ splk_producers_ };
            waiting_producers_.notify_all();

            detail::spinlock_lock lk2{ splk_consumers_ };
            waiting_consumers_.notify_all();
        }
    }

    channel_op_status push( value_type const& value) {
        context * active_ctx = context::active();
        slot s{ value, {} };
        for (;;) {
            if ( BOOST_UNLIKELY( is_closed() ) ) {
                return channel_op_status::closed;
            }
            s.w = active_ctx->create_waker();
            if ( try_push_( & s) ) {
                detail::spinlock_lock lk{ splk_consumers_ };
                waiting_consumers_.notify_one();
                // suspend till value has been consumed
                active_ctx->suspend( lk);
                // resumed
                if ( BOOST_UNLIKELY( is_closed() ) ) {
                    // channel was closed before value was consumed
                    return channel_op_status::closed;
                }
                // value has been consumed
                return channel_op_status::success;
            }
            detail::spinlock_lock lk{ splk_producers_ };
            if ( BOOST_UNLIKELY( is_closed() ) ) {
                return channel_op_status::closed;
            }
            if ( is_empty_() ) {
                continue;
            }

            waiting_producers_.suspend_and_wait( lk, active_ctx);
            // resumed, slot mabye free
        }
    }

    channel_op_status push( value_type && value) {
        context * active_ctx = context::active();
        slot s{ std::move( value), {} };
        for (;;) {
            if ( BOOST_UNLIKELY( is_closed() ) ) {
                return channel_op_status::closed;
            }
            s.w = active_ctx->create_waker();
            if ( try_push_( & s) ) {
                detail::spinlock_lock lk{ splk_consumers_ };
                waiting_consumers_.notify_one();
                // suspend till value has been consumed
                active_ctx->suspend( lk);
                // resumed
                if ( BOOST_UNLIKELY( is_closed() ) ) {
                    // channel was closed before value was consumed
                    return channel_op_status::closed;
                }
                // value has been consumed
                return channel_op_status::success;
            }
            detail::spinlock_lock lk{ splk_producers_ };
            if ( BOOST_UNLIKELY( is_closed() ) ) {
                return channel_op_status::closed;
            }
            if ( is_empty_() ) {
                continue;
            }
            waiting_producers_.suspend_and_wait( lk, active_ctx);
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
        slot s{ value, {} };
        std::chrono::steady_clock::time_point timeout_time = detail::convert( timeout_time_);
        for (;;) {
            if ( BOOST_UNLIKELY( is_closed() ) ) {
                return channel_op_status::closed;
            }
            s.w = active_ctx->create_waker();
            if ( try_push_( & s) ) {
                detail::spinlock_lock lk{ splk_consumers_ };
                waiting_consumers_.notify_one();
                // suspend this producer
                if ( ! active_ctx->wait_until(timeout_time, lk, waker(s.w))) {
                    // clear slot
                    slot * nil_slot = nullptr, * own_slot = & s;
                    slot_.compare_exchange_strong( own_slot, nil_slot, std::memory_order_acq_rel);
                    // resumed, value has not been consumed
                    return channel_op_status::timeout;
                }
                // resumed
                if ( BOOST_UNLIKELY( is_closed() ) ) {
                    // channel was closed before value was consumed
                    return channel_op_status::closed;
                }
                // value has been consumed
                return channel_op_status::success;
            }
            detail::spinlock_lock lk{ splk_producers_ };
            if ( BOOST_UNLIKELY( is_closed() ) ) {
                return channel_op_status::closed;
            }
            if ( is_empty_() ) {
                continue;
            }

            if (! waiting_producers_.suspend_and_wait_until( lk, active_ctx, timeout_time))
            {
                return channel_op_status::timeout;
            }
            // resumed, slot maybe free
        }
    }

    template< typename Clock, typename Duration >
    channel_op_status push_wait_until( value_type && value,
                                       std::chrono::time_point< Clock, Duration > const& timeout_time_) {
        context * active_ctx = context::active();
        slot s{ std::move( value), {} };
        std::chrono::steady_clock::time_point timeout_time = detail::convert( timeout_time_);
        for (;;) {
            if ( BOOST_UNLIKELY( is_closed() ) ) {
                return channel_op_status::closed;
            }
            s.w = active_ctx->create_waker();
            if ( try_push_( & s) ) {
                detail::spinlock_lock lk{ splk_consumers_ };
                waiting_consumers_.notify_one();
                // suspend this producer
                if ( ! active_ctx->wait_until(timeout_time, lk, waker(s.w))) {
                    // clear slot
                    slot * nil_slot = nullptr, * own_slot = & s;
                    slot_.compare_exchange_strong( own_slot, nil_slot, std::memory_order_acq_rel);
                    // resumed, value has not been consumed
                    return channel_op_status::timeout;
                }
                // resumed
                if ( BOOST_UNLIKELY( is_closed() ) ) {
                    // channel was closed before value was consumed
                    return channel_op_status::closed;
                }
                // value has been consumed
                return channel_op_status::success;
            }
            detail::spinlock_lock lk{ splk_producers_ };
            if ( BOOST_UNLIKELY( is_closed() ) ) {
                return channel_op_status::closed;
            }
            if ( is_empty_() ) {
                continue;
            }
            if (! waiting_producers_.suspend_and_wait_until( lk, active_ctx, timeout_time))
            {
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
                    waiting_producers_.notify_one();
                }
                value = std::move( s->value);
                // notify context
                s->w.wake();
                return channel_op_status::success;
            }
            detail::spinlock_lock lk{ splk_consumers_ };
            if ( BOOST_UNLIKELY( is_closed() ) ) {
                return channel_op_status::closed;
            }
            if ( ! is_empty_() ) {
                continue;
            }
            waiting_consumers_.suspend_and_wait( lk, active_ctx);
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
                    waiting_producers_.notify_one();
                }
                // consume value
                value_type value = std::move( s->value);
                // notify context
                s->w.wake();
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
            waiting_consumers_.suspend_and_wait( lk, active_ctx);
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
                    waiting_producers_.notify_one();
                }
                // consume value
                value = std::move( s->value);
                // notify context
                s->w.wake();
                return channel_op_status::success;
            }
            detail::spinlock_lock lk{ splk_consumers_ };
            if ( BOOST_UNLIKELY( is_closed() ) ) {
                return channel_op_status::closed;
            }
            if ( ! is_empty_() ) {
                continue;
            }
            if ( ! waiting_consumers_.suspend_and_wait_until( lk, active_ctx, timeout_time)) {
                return channel_op_status::timeout;
            }
        }
    }

    class iterator {
    private:
        typedef typename std::aligned_storage< sizeof( value_type), alignof( value_type) >::type  storage_type;

        unbuffered_channel  *   chan_{ nullptr };
        storage_type            storage_;

        void increment_( bool initial = false) {
            BOOST_ASSERT( nullptr != chan_);
            try {
                if ( ! initial) {
                    reinterpret_cast< value_type * >( std::addressof( storage_) )->~value_type();
                }
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

        iterator() = default;

        explicit iterator( unbuffered_channel< T > * chan) noexcept :
            chan_{ chan } {
            increment_( true);
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