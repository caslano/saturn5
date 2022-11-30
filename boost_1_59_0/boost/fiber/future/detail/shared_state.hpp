
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_SHARED_STATE_H
#define BOOST_FIBERS_DETAIL_SHARED_STATE_H

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstddef>
#include <exception>
#include <memory>
#include <mutex>
#include <type_traits>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/intrusive_ptr.hpp>

#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/future/future_status.hpp>
#include <boost/fiber/condition_variable.hpp>
#include <boost/fiber/exceptions.hpp>
#include <boost/fiber/mutex.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

class shared_state_base {
private:
    std::atomic< std::size_t >  use_count_{ 0 };
    mutable condition_variable  waiters_{};

protected:
    mutable mutex       mtx_{};
    bool                ready_{ false };
    std::exception_ptr  except_{};

    void mark_ready_and_notify_( std::unique_lock< mutex > & lk) noexcept {
        BOOST_ASSERT( lk.owns_lock() );
        ready_ = true;
        lk.unlock();
        waiters_.notify_all();
    }

    void owner_destroyed_( std::unique_lock< mutex > & lk) {
        BOOST_ASSERT( lk.owns_lock() );
        if ( ! ready_) {
            set_exception_(
                    std::make_exception_ptr( broken_promise() ),
                    lk);
        }
    }

    void set_exception_( std::exception_ptr except, std::unique_lock< mutex > & lk) {
        BOOST_ASSERT( lk.owns_lock() );
        if ( BOOST_UNLIKELY( ready_) ) {
            throw promise_already_satisfied();
        }
        except_ = except;
        mark_ready_and_notify_( lk);
    }

    std::exception_ptr get_exception_ptr_( std::unique_lock< mutex > & lk) {
        BOOST_ASSERT( lk.owns_lock() );
        wait_( lk);
        return except_;
    }

    void wait_( std::unique_lock< mutex > & lk) const {
        BOOST_ASSERT( lk.owns_lock() );
        waiters_.wait( lk, [this](){ return ready_; });
    }

    template< typename Rep, typename Period >
    future_status wait_for_( std::unique_lock< mutex > & lk,
                             std::chrono::duration< Rep, Period > const& timeout_duration) const {
        BOOST_ASSERT( lk.owns_lock() );
        return waiters_.wait_for( lk, timeout_duration, [this](){ return ready_; })
                    ? future_status::ready
                    : future_status::timeout;
    }

    template< typename Clock, typename Duration >
    future_status wait_until_( std::unique_lock< mutex > & lk,
                               std::chrono::time_point< Clock, Duration > const& timeout_time) const {
        BOOST_ASSERT( lk.owns_lock() );
        return waiters_.wait_until( lk, timeout_time, [this](){ return ready_; })
                    ? future_status::ready
                    : future_status::timeout;
    }

    virtual void deallocate_future() noexcept = 0;

public:
    shared_state_base() = default;

    virtual ~shared_state_base() = default;

    shared_state_base( shared_state_base const&) = delete;
    shared_state_base & operator=( shared_state_base const&) = delete;

    void owner_destroyed() {
        std::unique_lock< mutex > lk{ mtx_ };
        owner_destroyed_( lk);
    }

    void set_exception( std::exception_ptr except) {
        std::unique_lock< mutex > lk{ mtx_ };
        set_exception_( except, lk);
    }

    std::exception_ptr get_exception_ptr() {
        std::unique_lock< mutex > lk{ mtx_ };
        return get_exception_ptr_( lk);
    }

    void wait() const {
        std::unique_lock< mutex > lk{ mtx_ };
        wait_( lk);
    }

    template< typename Rep, typename Period >
    future_status wait_for( std::chrono::duration< Rep, Period > const& timeout_duration) const {
        std::unique_lock< mutex > lk{ mtx_ };
        return wait_for_( lk, timeout_duration);
    }

    template< typename Clock, typename Duration >
    future_status wait_until( std::chrono::time_point< Clock, Duration > const& timeout_time) const {
        std::unique_lock< mutex > lk{ mtx_ };
        return wait_until_( lk, timeout_time);
    }

    friend inline
    void intrusive_ptr_add_ref( shared_state_base * p) noexcept {
        p->use_count_.fetch_add( 1, std::memory_order_relaxed);
    }

    friend inline
    void intrusive_ptr_release( shared_state_base * p) noexcept {
        if ( 1 == p->use_count_.fetch_sub( 1, std::memory_order_release) ) {
            std::atomic_thread_fence( std::memory_order_acquire);
            p->deallocate_future();
        }
    }
};

template< typename R >
class shared_state : public shared_state_base {
private:
    typename std::aligned_storage< sizeof( R), alignof( R) >::type  storage_{};

    void set_value_( R const& value, std::unique_lock< mutex > & lk) {
        BOOST_ASSERT( lk.owns_lock() );
        if ( BOOST_UNLIKELY( ready_) ) {
            throw promise_already_satisfied{};
        }
        ::new ( static_cast< void * >( std::addressof( storage_) ) ) R( value );
        mark_ready_and_notify_( lk);
    }

    void set_value_( R && value, std::unique_lock< mutex > & lk) {
        BOOST_ASSERT( lk.owns_lock() );
        if ( BOOST_UNLIKELY( ready_) ) {
            throw promise_already_satisfied{};
        }
        ::new ( static_cast< void * >( std::addressof( storage_) ) ) R( std::move( value) );
        mark_ready_and_notify_( lk);
    }

    R & get_( std::unique_lock< mutex > & lk) {
        BOOST_ASSERT( lk.owns_lock() );
        wait_( lk);
        if ( except_) {
            std::rethrow_exception( except_);
        }
        return * reinterpret_cast< R * >( std::addressof( storage_) );
    }

public:
    typedef intrusive_ptr< shared_state >    ptr_type;

    shared_state() = default;

    virtual ~shared_state() {
        if ( ready_ && ! except_) {
            reinterpret_cast< R * >( std::addressof( storage_) )->~R();
        }
    }

    shared_state( shared_state const&) = delete;
    shared_state & operator=( shared_state const&) = delete;

    void set_value( R const& value) {
        std::unique_lock< mutex > lk{ mtx_ };
        set_value_( value, lk);
    }

    void set_value( R && value) {
        std::unique_lock< mutex > lk{ mtx_ };
        set_value_( std::move( value), lk);
    }

    R & get() {
        std::unique_lock< mutex > lk{ mtx_ };
        return get_( lk);
    }
};

template< typename R >
class shared_state< R & > : public shared_state_base {
private:
    R   *   value_{ nullptr };

    void set_value_( R & value, std::unique_lock< mutex > & lk) {
        BOOST_ASSERT( lk.owns_lock() );
        if ( BOOST_UNLIKELY( ready_) ) {
            throw promise_already_satisfied();
        }
        value_ = std::addressof( value);
        mark_ready_and_notify_( lk);
    }

    R & get_( std::unique_lock< mutex > & lk) {
        BOOST_ASSERT( lk.owns_lock() );
        wait_( lk);
        if ( except_) {
            std::rethrow_exception( except_);
        }
        return * value_;
    }

public:
    typedef intrusive_ptr< shared_state >    ptr_type;

    shared_state() = default;

    virtual ~shared_state() = default;

    shared_state( shared_state const&) = delete;
    shared_state & operator=( shared_state const&) = delete;

    void set_value( R & value) {
        std::unique_lock< mutex > lk{ mtx_ };
        set_value_( value, lk);
    }

    R & get() {
        std::unique_lock< mutex > lk{ mtx_ };
        return get_( lk);
    }
};

template<>
class shared_state< void > : public shared_state_base {
private:
    inline
    void set_value_( std::unique_lock< mutex > & lk) {
        BOOST_ASSERT( lk.owns_lock() );
        if ( BOOST_UNLIKELY( ready_) ) {
            throw promise_already_satisfied();
        }
        mark_ready_and_notify_( lk);
    }

    inline
    void get_( std::unique_lock< mutex > & lk) {
        BOOST_ASSERT( lk.owns_lock() );
        wait_( lk);
        if ( except_) {
            std::rethrow_exception( except_);
        }
    }

public:
    typedef intrusive_ptr< shared_state >    ptr_type;

    shared_state() = default;

    virtual ~shared_state() = default;

    shared_state( shared_state const&) = delete;
    shared_state & operator=( shared_state const&) = delete;

    inline
    void set_value() {
        std::unique_lock< mutex > lk{ mtx_ };
        set_value_( lk);
    }

    inline
    void get() {
        std::unique_lock< mutex > lk{ mtx_ };
        get_( lk);
    }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_SHARED_STATE_H

/* shared_state.hpp
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
*/