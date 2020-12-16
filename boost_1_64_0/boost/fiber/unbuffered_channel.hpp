
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
/KWOz4u/dORzMfPZot6v+lLH5/wvHflcou/Prb7U8fnbqCOfS/X7qd+I6vj8bNSRzxELn9M4/hfV8bkk6sjncv3xgvOjOj5nRx35PMPC5xYc//iHjs8fQ6o1HJ+USBF/4oE5xws58ygHlMFikbooL8kU2E+kZQGsJlbAawr1J9IaA9ITK5DKBVyQv5Ty/bH8TM7HE8be2s6vwoUkc1/Gg5/H91HVE78TvxO/E78TvxO/E78TvxO/E78TvxO/E7//4Z/9fiK8X8j4+zp5P5Hnj0+2pk9b4SybbiDCqa2rLAPuga35CDIhZ7380pDPmLF2R9386rKk3tXRgQXi0yv0LaJVXOJZKBFaApsR1YTZyITKNhVxgR4zoICcQWMZrBY/2dJpww6cRq/4gdNo+9VjR9YSqXARZgAJw7YF6CKyypDPWP3EjjoMZeCdmq7ZSNcVG5sh3K8e2FFHX6ZSF2zBk29Q79fzqjyi5VvpVqztzyJHIs3FdVXR9nlVXUQlJ+17Jd0l4IwbX9xR17v6+95kZaKnENvVzUYPklKMh6WxbQVLgBSkMNj7dWPuApbVNfmVpozqmwCFvPQMkJTlvIYBY8BVsCStHzQ7T1zsu6kS/tuIT8arP0cKou0LKgFIhMrEFV9GGGhX13QVfh/iNPfNDVtD9NElqEEf8b5yCDyEs+BvlpHytKCrs7aID/8aX6wXQkHSPU28AS9fd3/dhkdFo/LVNWWFwMVRmyCN72OVXAwRFw9sYS7exVyc8zPmolwJpx6U8usdTbhJ0c6vjtQ0unAOMYtu/XaVvJ2vwf70l19wfwqp8RGiToWI5gMi+eHQoGu2oHEU0dha0JiHNN7ONN6/VNBYQmNo0r1iDAWhNrzYDfCK0aQ+2J23EUfSoN7VMJioQ/V4QIhWVHMtVfPkS5pqzqFqPD+082n0xZuPmK4qtA+rAMh9+2oeVm3ksOK7/n6HdxOjFBt132ORrIql1vZRlpquvP8R+9AIZRk3PSRhGq5v98O2+vbMj1tftb38U89zeefvJzL4XAIH/iGbgogmQCMU48jLPI0blc74TyX8eeIWf10VPRtTBX1/XTfoN6829YRKr/H6ih11/ZYmgm0cgSL308W+b2XJr7fhulaxGNt87W/Y6N/eRfFsEW0fBYqXmnb97B34oTifS/SjwdFT5YWY7cFyTF2cLDXDlirsasIqdaYCkbZIaDHWUERlxt65oy7qabz+eKvR/LZ9j/6ZVawocviL73KZta4Gn5Cg5hm3vStv9fbBZ9FnXQYaYN7cOb/s6Aolbq7bJr5mWNamYAmwAwZ+7/eIiV1W7qgT91FSPvgefHHysIcgaz5ntaTUu2E9q/Z+tLhtMd0NICL97QxIn4fpl1P5dEr/Uwok3RBtTYVTKXFzM0i8KtpNSJjuqycrPlimrEpQKblV8GW/umgPuhsz4iP9Vrl8R53dI8gxes6O6fPAljue7Oh6Cv6dAyy4CP69/iT9PQR/O8Pft/7Fv3rfX2OB/vVBa/+uXS77d6Qb6t9rEoT+7f4i6t/7UP8uY/373O1AYh1ypEuB6vaFJMyg0aGDyzW/elbzqgTknEeUa/z36Ou1ly1VT2ovWYoVN5P1FV8N9YsBGDMrzTLhf1Evm9mgUficGEzNe1fXvkrdye8uSxGNrH1OJjTLmP8oPJJzxZBDoLOZ/SVEUSGd5TlYLDKUPL2Jt1KjQlgwBJ2PkjuXCWt12UZkrnHFXTvqkGmhvKpM6jbKCzYOgGtMhXrKQgEuhKjKjT9CiapE4mvCD7Z9jvowX8f/p+8X/Afe5PIXGdkBrSjPckVa0TOapc9XkF+dV4WUgboqJbmdvUhYT0/tIfqgabk=
*/