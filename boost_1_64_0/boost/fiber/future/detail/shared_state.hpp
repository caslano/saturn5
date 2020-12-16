
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
wTC/KjEP1RGUTEl/vU0HukmCriTQeRL0Eh1RPKDqK4mKJqLUYGU9cE1iHiEx9xohI6JUiohu36OPiIbtMURE9SUNj/VhRC1/TyQs6BMkKo2I2uAVmXf30ROVRokDrtE1d+9gQdS64Qzzpg8FcHsdZjdhHioxN0DMvViPIuRumEQ8dIMScvoa0J5MXZQ5uiurpHcvsYo5wKrjUDdJTMrwoJQ8lHSl7zcI/Grop//++y79+edXRXb++Tjj+edTSyv1PcmWccbx6+BtlRm/JhM8jT+4Kba+OnIFunKb3rW/GIm+u45J+t5DIuGf1wUHM7tuMLNT9usCxZl+AmIdoeguUazEhPDj4X0CxWsSxXhCkShRDLuuSgPk/v2VX5/rNVY9xLEOHzOKncEdA3he3o3sqYCbws87si/hrw4Oeux8DzbAtR0kxovFrAPRsGOHnEZTRc4UdAoeqThELne+suBOuWnLrewPps0N2dprGfRJATstKL0oNYr139eYVdqtLWqnTv+3RB5cEcVcwUXvSVcwJ7j/H6Yvy1ZjRShRYk8hLTZBZR6oTFvdX90DkhS8pp8aPrQ/m4a8DOu6kupqYVbX1puAQXDhzFVEs5Vb0jTtYZykFQ3NQJzpRU6E/QcSxiYoT44H2OZUX910NKPphGXLuwJL/2no1dbg3CX+DMP1Z9l693w63cJo3MGSe6l2aoiQC6Yar1a1+VuQJZb3XTGnfFEHdfcmY/AQK2PwWwclg6dIBg8bWFrN66z2qzcV4dVEBe6BCSVIsX1++kCBN/z9X7frGAKDLDZ+90UWS+h9QsG97cm0yE+ZnlRNg/Ih7T5G8cz+A7LdU4PnP9xY5XYb6U+4Xd2fL0/wwoYEGlJD0liqkGKylGIXisf6cmGrLZTN9yRrvS5UW5iKLfyIWnj8HdnCB2QL8weI2fwnu1W5rcbv38fo59diyvAkZRmkdZukv6Xvix7MmLt0iUnaqotYB7ygm0jElrVBFslZmO+vFnko14UXBvPStEZXBvPcWm3dm0cLdMYevoh8k4/fFkPIuMmRTersj2y+Z/o8WtgKm78kNJ+05Ogoxjp5XGVnIHHTSsxpnmoSi08kyTrflpKdJiX7vJfF4tdqTe7jIhafcOGnZ3+rw66CzxTvdznYe7Z470f5eZ6qbn9l+w9okk8diGyjgieKM3mN7QQJ7G2XmxlqekHheXVZbn0WbCzQZXkwi9036+uqNZLfTWGuMAppxDZfQ/o0RNQ9+TZ+w+5swpBj8aVpH0Oi7I1Zoje6WW8kDDlBErvcxm1pL8jOQ/BlHNwtwfFYUg8b5Ag8L9iMs7eqpnhSkLYbO4blS1rHsHxp0tHAF9QTO9l2bZ/Uk+lST2b0/w1Gt4p/Rnv56a1ifiUBZ1rkhNisBsJ2ipv2KKLl/BtAlvKLP5rdNJek7zvbqe+8v1fyZIbkyV39qv0RomwOnkMZOxEP/LpADn3zPV5xSFnY9mfpxjs0ebY0sQzY46byrtFTR7eN1Mqv98hWzpStnJtRCYsf7r5BJ1oJ/e2D86ZjwyoFn6ncXpi1PZL5rC0jxPmgm2tZxEd3pT48uMrq039lemo3Nj0Xm54vm76gLxNwG3mP2jM5pGRuhghW2mRO0e1VmscJ01Qnyb3i+OzT4SR/OVRuksOhvNJV5n11Z4UhUIaJKZ5EdYR+rymcFO2KdOOF4W9DsrChaciftGHchK5n9aMNdcyahcD+3qp/n0xbv2fGyS08OXzr2R+5EfTJaBK9oh/r8HvfKZUE4+EXPqPFlbeXpjEulNXhzk9b2RAsIcz4vIVsi+X15t+KsK0a3clOFu+UvWWWVJnBvcWWoVntxYduhfAxwW/0oRs=
*/