
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
#include <boost/fiber/waker.hpp>
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
	using slot_type = value_type;

    mutable detail::spinlock   splk_{};
    wait_queue                                          waiting_producers_{};
    wait_queue                                          waiting_consumers_{};
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
        detail::spinlock_lock lk{ splk_ };
        if ( ! closed_) {
            closed_ = true;
            waiting_producers_.notify_all();
            waiting_consumers_.notify_all();
        }
    }

    channel_op_status try_push( value_type const& value) {
        detail::spinlock_lock lk{ splk_ };
        if ( BOOST_UNLIKELY( is_closed_() ) ) {
            return channel_op_status::closed;
        }
        if ( is_full_() ) {
            return channel_op_status::full;
        }
        slots_[pidx_] = value;
        pidx_ = (pidx_ + 1) % capacity_;
        waiting_consumers_.notify_one();
        return channel_op_status::success;
    }

    channel_op_status try_push( value_type && value) {
        detail::spinlock_lock lk{ splk_ };
        if ( BOOST_UNLIKELY( is_closed_() ) ) {
            return channel_op_status::closed;
        }
        if ( is_full_() ) {
            return channel_op_status::full;
        }
        slots_[pidx_] = std::move( value);
        pidx_ = (pidx_ + 1) % capacity_;
        waiting_consumers_.notify_one();
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
                waiting_producers_.suspend_and_wait( lk, active_ctx);
            } else {
                slots_[pidx_] = value;
                pidx_ = (pidx_ + 1) % capacity_;
                waiting_consumers_.notify_one();
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
                waiting_producers_.suspend_and_wait( lk, active_ctx);
            } else {
                slots_[pidx_] = std::move( value);
                pidx_ = (pidx_ + 1) % capacity_;

                waiting_consumers_.notify_one();
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
                if ( ! waiting_producers_.suspend_and_wait_until( lk, active_ctx, timeout_time)) {
                    return channel_op_status::timeout;
                }
            } else {
                slots_[pidx_] = value;
                pidx_ = (pidx_ + 1) % capacity_;
                waiting_consumers_.notify_one();
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
                if ( ! waiting_producers_.suspend_and_wait_until( lk, active_ctx, timeout_time)) {
                    return channel_op_status::timeout;
                }
            } else {
                slots_[pidx_] = std::move( value);
                pidx_ = (pidx_ + 1) % capacity_;
                // notify one waiting consumer
                waiting_consumers_.notify_one();
                return channel_op_status::success;
            }
        }
    }

    channel_op_status try_pop( value_type & value) {
        detail::spinlock_lock lk{ splk_ };
        if ( is_empty_() ) {
            return is_closed_()
                ? channel_op_status::closed
                : channel_op_status::empty;
        }
        value = std::move( slots_[cidx_]);
        cidx_ = (cidx_ + 1) % capacity_;
        waiting_producers_.notify_one();
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
                waiting_consumers_.suspend_and_wait( lk, active_ctx);
            } else {
                value = std::move( slots_[cidx_]);
                cidx_ = (cidx_ + 1) % capacity_;
                waiting_producers_.notify_one();
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
                waiting_consumers_.suspend_and_wait( lk, active_ctx);
            } else {
                value_type value = std::move( slots_[cidx_]);
                cidx_ = (cidx_ + 1) % capacity_;
                waiting_producers_.notify_one();
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
                if ( ! waiting_consumers_.suspend_and_wait_until( lk, active_ctx, timeout_time)) {
                    return channel_op_status::timeout;
                }
            } else {
                value = std::move( slots_[cidx_]);
                cidx_ = (cidx_ + 1) % capacity_;
                waiting_producers_.notify_one();
                return channel_op_status::success;
            }
        }
    }

    class iterator {
    private:
        typedef typename std::aligned_storage< sizeof( value_type), alignof( value_type) >::type  storage_type;

        buffered_channel    *   chan_{ nullptr };
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

        explicit iterator( buffered_channel< T > * chan) noexcept :
            chan_{ chan } {
            increment_( true);
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