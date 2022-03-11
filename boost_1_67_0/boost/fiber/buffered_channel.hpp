
//          Copyright Oliver Kowalke 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_FIBERS_BUFFERED_CHANNEL_H
#define BOOST_FIBERS_BUFFERED_CHANNEL_H

#include <atomic>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <type_traits>

#include <boost/config.hpp>

#include <boost/fiber/channel_op_status.hpp>
#include <boost/fiber/context.hpp>
#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/convert.hpp>
#include <boost/fiber/detail/spinlock.hpp>
#include <boost/fiber/exceptions.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

template< typename T >
class buffered_channel {
public:
    using value_type = typename std::remove_reference<T>::type;

private:
    using wait_queue_type = context::wait_queue_t;
	using slot_type = value_type;

    mutable detail::spinlock   splk_{};
    wait_queue_type                                     waiting_producers_{};
    wait_queue_type                                     waiting_consumers_{};
	slot_type                                       *   slots_;
	std::size_t                                         pidx_{ 0 };
	std::size_t                                         cidx_{ 0 };
	std::size_t                                         capacity_;
    bool                                                closed_{ false };

	bool is_full_() const noexcept {
		return cidx_ == ((pidx_ + 1) % capacity_);
	}

	bool is_empty_() const noexcept {
		return cidx_ == pidx_;
	}

    bool is_closed_() const noexcept {
        return closed_;
    }

public:
    explicit buffered_channel( std::size_t capacity) :
            capacity_{ capacity } {
        if ( BOOST_UNLIKELY( 2 > capacity_ || 0 != ( capacity_ & (capacity_ - 1) ) ) ) { 
            throw fiber_error{ std::make_error_code( std::errc::invalid_argument),
                               "boost fiber: buffer capacity is invalid" };
        }
        slots_ = new slot_type[capacity_];
    }

    ~buffered_channel() {
        close();
        delete [] slots_;
    }

    buffered_channel( buffered_channel const&) = delete;
    buffered_channel & operator=( buffered_channel const&) = delete;

    bool is_closed() const noexcept {
        detail::spinlock_lock lk{ splk_ };
        return is_closed_();
    }

    void close() noexcept {
        context * active_ctx = context::active();
        detail::spinlock_lock lk{ splk_ };
        if ( ! closed_) {
            closed_ = true;
            // notify all waiting producers
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

    channel_op_status try_push( value_type const& value) {
        context * active_ctx = context::active();
        detail::spinlock_lock lk{ splk_ };
        if ( BOOST_UNLIKELY( is_closed_() ) ) {
            return channel_op_status::closed;
        }
        if ( is_full_() ) {
            return channel_op_status::full;
        }
        slots_[pidx_] = value;
        pidx_ = (pidx_ + 1) % capacity_;
        // notify one waiting consumer
        while ( ! waiting_consumers_.empty() ) {
            context * consumer_ctx = & waiting_consumers_.front();
            waiting_consumers_.pop_front();
            auto expected = reinterpret_cast< std::intptr_t >( this);
            if ( consumer_ctx->twstatus.compare_exchange_strong( expected, static_cast< std::intptr_t >( -1), std::memory_order_acq_rel) ) {
                lk.unlock();
                // notify context
                active_ctx->schedule( consumer_ctx);
                break;
            }
            if ( static_cast< std::intptr_t >( 0) == expected) {
               lk.unlock();
                // no timed-wait op.
                // notify context
                active_ctx->schedule( consumer_ctx);
                break;
            }
        }
        return channel_op_status::success;
    }

    channel_op_status try_push( value_type && value) {
        context * active_ctx = context::active();
        detail::spinlock_lock lk{ splk_ };
        if ( BOOST_UNLIKELY( is_closed_() ) ) {
            return channel_op_status::closed;
        }
        if ( is_full_() ) {
            return channel_op_status::full;
        }
        slots_[pidx_] = std::move( value);
        pidx_ = (pidx_ + 1) % capacity_;
        // notify one waiting consumer
        while ( ! waiting_consumers_.empty() ) {
            context * consumer_ctx = & waiting_consumers_.front();
            waiting_consumers_.pop_front();
            auto expected = reinterpret_cast< std::intptr_t >( this);
            if ( consumer_ctx->twstatus.compare_exchange_strong( expected, static_cast< std::intptr_t >( -1), std::memory_order_acq_rel) ) {
                lk.unlock();
                // notify context
                active_ctx->schedule( consumer_ctx);
                break;
            }
            if ( static_cast< std::intptr_t >( 0) == expected) {
               lk.unlock();
                // no timed-wait op.
                // notify context
                active_ctx->schedule( consumer_ctx);
                break;
            }
        }
        return channel_op_status::success;
    }

    channel_op_status push( value_type const& value) {
        context * active_ctx = context::active();
        for (;;) {
            detail::spinlock_lock lk{ splk_ };
            if ( BOOST_UNLIKELY( is_closed_() ) ) {
                return channel_op_status::closed;
            }
            if ( is_full_() ) {
                active_ctx->wait_link( waiting_producers_);
                active_ctx->twstatus.store( static_cast< std::intptr_t >( 0), std::memory_order_release);
                // suspend this producer
                active_ctx->suspend( lk);
            } else {
                slots_[pidx_] = value;
                pidx_ = (pidx_ + 1) % capacity_;
                // notify one waiting consumer
                while ( ! waiting_consumers_.empty() ) {
                    context * consumer_ctx = & waiting_consumers_.front();
                    waiting_consumers_.pop_front();
                    auto expected = reinterpret_cast< std::intptr_t >( this);
                    if ( consumer_ctx->twstatus.compare_exchange_strong( expected, static_cast< std::intptr_t >( -1), std::memory_order_acq_rel) ) {
                        lk.unlock();
                        // notify context
                        active_ctx->schedule( consumer_ctx);
                        break;
                    }
                    if ( static_cast< std::intptr_t >( 0) == expected) {
                        lk.unlock();
                        // no timed-wait op.
                        // notify context
                        active_ctx->schedule( consumer_ctx);
                        break;
                    }
                }
                return channel_op_status::success;
            }
        }
    }

    channel_op_status push( value_type && value) {
        context * active_ctx = context::active();
        for (;;) {
            detail::spinlock_lock lk{ splk_ };
            if ( BOOST_UNLIKELY( is_closed_() ) ) {
                return channel_op_status::closed;
            }
            if ( is_full_() ) {
                active_ctx->wait_link( waiting_producers_);
                active_ctx->twstatus.store( static_cast< std::intptr_t >( 0), std::memory_order_release);
                // suspend this producer
                active_ctx->suspend( lk);
            } else {
                slots_[pidx_] = std::move( value);
                pidx_ = (pidx_ + 1) % capacity_;
                // notify one waiting consumer
                while ( ! waiting_consumers_.empty() ) {
                    context * consumer_ctx = & waiting_consumers_.front();
                    waiting_consumers_.pop_front();
                    auto expected = reinterpret_cast< std::intptr_t >( this);
                    if ( consumer_ctx->twstatus.compare_exchange_strong( expected, static_cast< std::intptr_t >( -1), std::memory_order_acq_rel) ) {
                        lk.unlock();
                        // notify context
                        active_ctx->schedule( consumer_ctx);
                        break;
                    }
                    if ( static_cast< std::intptr_t >( 0) == expected) {
                        lk.unlock();
                        // no timed-wait op.
                        // notify context
                        active_ctx->schedule( consumer_ctx);
                        break;
                    }
                }
                return channel_op_status::success;
            }
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
        std::chrono::steady_clock::time_point timeout_time = detail::convert( timeout_time_);
        for (;;) {
            detail::spinlock_lock lk{ splk_ };
            if ( BOOST_UNLIKELY( is_closed_() ) ) {
                return channel_op_status::closed;
            }
            if ( is_full_() ) {
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
            } else {
                slots_[pidx_] = value;
                pidx_ = (pidx_ + 1) % capacity_;
                // notify one waiting consumer
                while ( ! waiting_consumers_.empty() ) {
                    context * consumer_ctx = & waiting_consumers_.front();
                    waiting_consumers_.pop_front();
                    auto expected = reinterpret_cast< std::intptr_t >( this);
                    if ( consumer_ctx->twstatus.compare_exchange_strong( expected, static_cast< std::intptr_t >( -1), std::memory_order_acq_rel) ) {
                        lk.unlock();
                        // notify context
                        active_ctx->schedule( consumer_ctx);
                        break;
                    }
                    if ( static_cast< std::intptr_t >( 0) == expected) {
                        lk.unlock();
                        // no timed-wait op.
                        // notify context
                        active_ctx->schedule( consumer_ctx);
                        break;
                    }
                }
                return channel_op_status::success;
            }
        }
    }

    template< typename Clock, typename Duration >
    channel_op_status push_wait_until( value_type && value,
                                       std::chrono::time_point< Clock, Duration > const& timeout_time_) {
        context * active_ctx = context::active();
        std::chrono::steady_clock::time_point timeout_time = detail::convert( timeout_time_);
        for (;;) {
            detail::spinlock_lock lk{ splk_ };
            if ( BOOST_UNLIKELY( is_closed_() ) ) {
                return channel_op_status::closed;
            }
            if ( is_full_() ) {
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
            } else {
                slots_[pidx_] = std::move( value);
                pidx_ = (pidx_ + 1) % capacity_;
                // notify one waiting consumer
                while ( ! waiting_consumers_.empty() ) {
                    context * consumer_ctx = & waiting_consumers_.front();
                    waiting_consumers_.pop_front();
                    auto expected = reinterpret_cast< std::intptr_t >( this);
                    if ( consumer_ctx->twstatus.compare_exchange_strong( expected, static_cast< std::intptr_t >( -1), std::memory_order_acq_rel) ) {
                        lk.unlock();
                        // notify context
                        active_ctx->schedule( consumer_ctx);
                        break;
                    }
                    if ( static_cast< std::intptr_t >( 0) == expected) {
                        lk.unlock();
                        // no timed-wait op.
                        // notify context
                        active_ctx->schedule( consumer_ctx);
                        break;
                    }
                }
                return channel_op_status::success;
            }
        }
    }

    channel_op_status try_pop( value_type & value) {
        context * active_ctx = context::active();
        detail::spinlock_lock lk{ splk_ };
        if ( is_empty_() ) {
            return is_closed_()
                ? channel_op_status::closed
                : channel_op_status::empty;
        }
        value = std::move( slots_[cidx_]);
        cidx_ = (cidx_ + 1) % capacity_;
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
        return channel_op_status::success;
    }

    channel_op_status pop( value_type & value) {
        context * active_ctx = context::active();
        for (;;) {
            detail::spinlock_lock lk{ splk_ };
            if ( is_empty_() ) {
                if ( BOOST_UNLIKELY( is_closed_() ) ) {
                    return channel_op_status::closed;
                }
                active_ctx->wait_link( waiting_consumers_);
                active_ctx->twstatus.store( static_cast< std::intptr_t >( 0), std::memory_order_release);
                // suspend this consumer
                active_ctx->suspend( lk);
            } else {
                value = std::move( slots_[cidx_]);
                cidx_ = (cidx_ + 1) % capacity_;
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
                return channel_op_status::success;
            }
        }
    }

    value_type value_pop() {
        context * active_ctx = context::active();
        for (;;) {
            detail::spinlock_lock lk{ splk_ };
            if ( is_empty_() ) {
                if ( BOOST_UNLIKELY( is_closed_() ) ) {
                    throw fiber_error{
                        std::make_error_code( std::errc::operation_not_permitted),
                        "boost fiber: channel is closed" };
                }
                active_ctx->wait_link( waiting_consumers_);
                active_ctx->twstatus.store( static_cast< std::intptr_t >( 0), std::memory_order_release);
                // suspend this consumer
                active_ctx->suspend( lk);
            } else {
                value_type value = std::move( slots_[cidx_]);
                cidx_ = (cidx_ + 1) % capacity_;
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
                return value;
            }
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
        std::chrono::steady_clock::time_point timeout_time = detail::convert( timeout_time_);
        for (;;) {
            detail::spinlock_lock lk{ splk_ };
            if ( is_empty_() ) {
                if ( BOOST_UNLIKELY( is_closed_() ) ) {
                    return channel_op_status::closed;
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
            } else {
                value = std::move( slots_[cidx_]);
                cidx_ = (cidx_ + 1) % capacity_;
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
                return channel_op_status::success;
            }
        }
    }

    class iterator {
    private:
        typedef typename std::aligned_storage< sizeof( value_type), alignof( value_type) >::type  storage_type;

        buffered_channel    *   chan_{ nullptr };
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

        explicit iterator( buffered_channel< T > * chan) noexcept :
            chan_{ chan } {
            increment_();
        }

        iterator( iterator const& other) noexcept :
            chan_{ other.chan_ } {
        }

        iterator & operator=( iterator const& other) noexcept {
            if ( BOOST_LIKELY( this != & other) ) {
                chan_ = other.chan_;
            }
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
typename buffered_channel< T >::iterator
begin( buffered_channel< T > & chan) {
    return typename buffered_channel< T >::iterator( & chan);
}

template< typename T >
typename buffered_channel< T >::iterator
end( buffered_channel< T > &) {
    return typename buffered_channel< T >::iterator();
}

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_BUFFERED_CHANNEL_H

/* buffered_channel.hpp
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
*/