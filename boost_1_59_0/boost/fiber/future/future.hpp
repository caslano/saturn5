
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_FUTURE_HPP
#define BOOST_FIBERS_FUTURE_HPP

#include <algorithm>
#include <chrono>
#include <exception>
#include <utility>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/exceptions.hpp>
#include <boost/fiber/future/detail/shared_state.hpp>
#include <boost/fiber/future/future_status.hpp>

namespace boost {
namespace fibers {
namespace detail {

template< typename R >
struct future_base {
    typedef typename shared_state< R >::ptr_type   ptr_type;

    ptr_type           state_{};

    future_base() = default;

    explicit future_base( ptr_type  p) noexcept :
        state_{std::move( p )} {
    }

    ~future_base() = default;

    future_base( future_base const& other) :
        state_{ other.state_ } {
    }

    future_base( future_base && other) noexcept :
        state_{ other.state_ } {
        other.state_.reset();
    }

    future_base & operator=( future_base const& other) noexcept {
        if ( BOOST_LIKELY( this != & other) ) {
            state_ = other.state_;
        }
        return * this;
    }

    future_base & operator=( future_base && other) noexcept {
        if ( BOOST_LIKELY( this != & other) ) {
            state_ = other.state_;
            other.state_.reset();
        }
        return * this;
    }

    bool valid() const noexcept {
        return nullptr != state_.get();
    }

    std::exception_ptr get_exception_ptr() {
        if ( BOOST_UNLIKELY( ! valid() ) ) {
            throw future_uninitialized{};
        }
        return state_->get_exception_ptr();
    }

    void wait() const {
        if ( BOOST_UNLIKELY( ! valid() ) ) {
            throw future_uninitialized{};
        }
        state_->wait();
    }

    template< typename Rep, typename Period >
    future_status wait_for( std::chrono::duration< Rep, Period > const& timeout_duration) const {
        if ( BOOST_UNLIKELY( ! valid() ) ) {
            throw future_uninitialized{};
        }
        return state_->wait_for( timeout_duration);
    }

    template< typename Clock, typename Duration >
    future_status wait_until( std::chrono::time_point< Clock, Duration > const& timeout_time) const {
        if ( BOOST_UNLIKELY( ! valid() ) ) {
            throw future_uninitialized{};
        }
        return state_->wait_until( timeout_time);
    }
};

template< typename R >
struct promise_base;

}

template< typename R >
class shared_future;

template< typename Signature >
class packaged_task;

template< typename R >
class future : private detail::future_base< R > {
private:
    typedef detail::future_base< R >  base_type;

    friend struct detail::promise_base< R >;
    friend class shared_future< R >;
    template< typename Signature >
    friend class packaged_task;

    explicit future( typename base_type::ptr_type const& p) noexcept :
        base_type{ p } {
    }

public:
    future() = default;

    future( future const&) = delete;
    future & operator=( future const&) = delete;

    future( future && other) noexcept :
        base_type{ std::move( other) } {
    }

    future & operator=( future && other) noexcept {
        if ( BOOST_LIKELY( this != & other) ) {
            base_type::operator=( std::move( other) );
        }
        return * this;
    }

    shared_future< R > share();

    R get() {
        if ( BOOST_UNLIKELY( ! base_type::valid() ) ) {
            throw future_uninitialized{};
        }
        typename base_type::ptr_type tmp{};
        tmp.swap( base_type::state_);
        return std::move( tmp->get() );
    }

    using base_type::valid;
    using base_type::get_exception_ptr;
    using base_type::wait;
    using base_type::wait_for;
    using base_type::wait_until;
};

template< typename R >
class future< R & > : private detail::future_base< R & > {
private:
    typedef detail::future_base< R & >  base_type;

    friend struct detail::promise_base< R & >;
    friend class shared_future< R & >;
    template< typename Signature >
    friend class packaged_task;

    explicit future( typename base_type::ptr_type const& p) noexcept :
        base_type{ p  } {
    }

public:
    future() = default;

    future( future const&) = delete;
    future & operator=( future const&) = delete;

    future( future && other) noexcept :
        base_type{ std::move( other) } {
    }

    future & operator=( future && other) noexcept {
        if ( BOOST_LIKELY( this != & other) ) {
            base_type::operator=( std::move( other) );
        }
        return * this;
    }

    shared_future< R & > share();

    R & get() {
        if ( BOOST_UNLIKELY( ! base_type::valid() ) ) {
            throw future_uninitialized{};
        }
        typename base_type::ptr_type tmp{};
        tmp.swap( base_type::state_);
        return tmp->get();
    }

    using base_type::valid;
    using base_type::get_exception_ptr;
    using base_type::wait;
    using base_type::wait_for;
    using base_type::wait_until;
};

template<>
class future< void > : private detail::future_base< void > {
private:
    typedef detail::future_base< void >  base_type;

    friend struct detail::promise_base< void >;
    friend class shared_future< void >;
    template< typename Signature >
    friend class packaged_task;

    explicit future( base_type::ptr_type const& p) noexcept :
        base_type{ p } {
    }

public:
    future() = default;

    future( future const&) = delete;
    future & operator=( future const&) = delete;

    inline
    future( future && other) noexcept :
        base_type{ std::move( other) } {
    }

    inline
    future & operator=( future && other) noexcept {
        if ( BOOST_LIKELY( this != & other) ) {
            base_type::operator=( std::move( other) );
        }
        return * this;
    }

    shared_future< void > share();

    inline
    void get() {
        if ( BOOST_UNLIKELY( ! base_type::valid() ) ) {
            throw future_uninitialized{};
        }
        base_type::ptr_type tmp{};
        tmp.swap( base_type::state_);
        tmp->get();
    }

    using base_type::valid;
    using base_type::get_exception_ptr;
    using base_type::wait;
    using base_type::wait_for;
    using base_type::wait_until;
};


template< typename R >
class shared_future : private detail::future_base< R > {
private:
    typedef detail::future_base< R >   base_type;

    explicit shared_future( typename base_type::ptr_type const& p) noexcept :
        base_type{ p } {
    }

public:
    shared_future() = default;

    ~shared_future() = default;

    shared_future( shared_future const& other) :
        base_type{ other } {
    }

    shared_future( shared_future && other) noexcept :
        base_type{ std::move( other) } {
    }

    shared_future( future< R > && other) noexcept :
        base_type{ std::move( other) } {
    }

    shared_future & operator=( shared_future const& other) noexcept {
        if ( BOOST_LIKELY( this != & other) ) {
            base_type::operator=( other); 
        }
        return * this;
    }

    shared_future & operator=( shared_future && other) noexcept {
        if ( BOOST_LIKELY( this != & other) ) {
            base_type::operator=( std::move( other) ); 
        }
        return * this;
    }

    shared_future & operator=( future< R > && other) noexcept {
        base_type::operator=( std::move( other) ); 
        return * this;
    }

    R const& get() const {
        if ( BOOST_UNLIKELY( ! valid() ) ) {
            throw future_uninitialized{};
        }
        return base_type::state_->get();
    }

    using base_type::valid;
    using base_type::get_exception_ptr;
    using base_type::wait;
    using base_type::wait_for;
    using base_type::wait_until;
};

template< typename R >
class shared_future< R & > : private detail::future_base< R & > {
private:
    typedef detail::future_base< R & >  base_type;

    explicit shared_future( typename base_type::ptr_type const& p) noexcept :
        base_type{ p } {
    }

public:
    shared_future() = default;

    ~shared_future() = default;

    shared_future( shared_future const& other) :
        base_type{ other } {
    }

    shared_future( shared_future && other) noexcept :
        base_type{ std::move( other) } {
    }

    shared_future( future< R & > && other) noexcept :
        base_type{ std::move( other) } {
    }

    shared_future & operator=( shared_future const& other) noexcept {
        if ( BOOST_LIKELY( this != & other) ) {
            base_type::operator=( other);
        }
        return * this;
    }

    shared_future & operator=( shared_future && other) noexcept {
        if ( BOOST_LIKELY( this != & other) ) {
            base_type::operator=( std::move( other) );
        }
        return * this;
    }

    shared_future & operator=( future< R & > && other) noexcept {
        base_type::operator=( std::move( other) );
        return * this;
    }

    R & get() const {
        if ( BOOST_UNLIKELY( ! valid() ) ) {
            throw future_uninitialized{};
        }
        return base_type::state_->get();
    }

    using base_type::valid;
    using base_type::get_exception_ptr;
    using base_type::wait;
    using base_type::wait_for;
    using base_type::wait_until;
};

template<>
class shared_future< void > : private detail::future_base< void > {
private:
    typedef detail::future_base< void > base_type;

    explicit shared_future( base_type::ptr_type const& p) noexcept :
        base_type{ p } {
    }

public:
    shared_future() = default;

    ~shared_future() = default;

    inline
    shared_future( shared_future const& other) :
        base_type{ other } {
    }

    inline
    shared_future( shared_future && other) noexcept :
        base_type{ std::move( other) } {
    }

    inline
    shared_future( future< void > && other) noexcept :
        base_type{ std::move( other) } {
    }

    inline
    shared_future & operator=( shared_future const& other) noexcept {
        if ( BOOST_LIKELY( this != & other) ) {
            base_type::operator=( other);
        }
        return * this;
    }

    inline
    shared_future & operator=( shared_future && other) noexcept {
        if ( BOOST_LIKELY( this != & other) ) {
            base_type::operator=( std::move( other) );
        }
        return * this;
    }

    inline
    shared_future & operator=( future< void > && other) noexcept {
        base_type::operator=( std::move( other) );
        return * this;
    }

    inline
    void get() const {
        if ( BOOST_UNLIKELY( ! valid() ) ) {
            throw future_uninitialized{};
        }
        base_type::state_->get();
    }

    using base_type::valid;
    using base_type::get_exception_ptr;
    using base_type::wait;
    using base_type::wait_for;
    using base_type::wait_until;
};


template< typename R >
shared_future< R >
future< R >::share() {
    if ( BOOST_UNLIKELY( ! base_type::valid() ) ) {
        throw future_uninitialized{};
    }
    return shared_future< R >{ std::move( * this) };
}

template< typename R >
shared_future< R & >
future< R & >::share() {
    if ( BOOST_UNLIKELY( ! base_type::valid() ) ) {
        throw future_uninitialized{};
    }
    return shared_future< R & >{ std::move( * this) };
}

inline
shared_future< void >
future< void >::share() {
    if ( BOOST_UNLIKELY( ! base_type::valid() ) ) {
        throw future_uninitialized{};
    }
    return shared_future< void >{ std::move( * this) };
}

}}

#endif

/* future.hpp
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
*/