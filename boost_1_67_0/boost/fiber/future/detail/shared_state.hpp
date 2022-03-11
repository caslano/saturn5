
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