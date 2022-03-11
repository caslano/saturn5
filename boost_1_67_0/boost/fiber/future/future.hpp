
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