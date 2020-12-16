
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
hQm9wD4l2j/EPxCh7HoOR6H0mNbbQ/Js5eRZg3llN0PnZPXutFiU+uksq0rMQvz3fobxcNDNNCIOLJYRWlZ+GsW5hWyfjIei+/0OsfQzfra6TwaL3sYW6qbgMO9LyWLlTj3NkUU/wAfGkTRy+WuxVYFosWNFBIRJ/M2dBNdcwXab66niGx20phVfwN0GCoVZ/Xl2tqp9A5Vs6RDbGWYdYqva+8POHOKYx8IsR+GTkBkcbtlei/yrSzC+ftuQXJBYEhiYkk2TriLLhVnkzc2vX8LX2zIMpn1KW6U81eBrqCQK/Dn+bdSIt//CnKD4smsDpHYuNNQjhv93dcwQ3jbeqt9uXp/NWk5hXpGbMdjDtvIu4jz2MC+QGhtN58/xooHdWNg3iF4zYNCztC4J7PYsQV3Ad7rmh6YxB8B1zIl7PSPFQXf9YEa2d2H9A6jWyexji4N8cmF3oEG9nnUtshJW/3wr42b1/Mpw8X7CG4whYWP8AoruW5PsBTsoqu9SvyTXCU+Urj24DtaFov1bKxXT815NxDzwuuzVXtGr17Plh3bUZU4niF69ZEbogsZ81kXhFXu1V9ervcFe2okQvZhAvfQGjsalzu7IzyjaEvhIC0KjqAib1x7cD+L8OsZCqxeJPDZYiB0BefArKL/RFRiyhc8E2+BNF5UNtFsskcRzjQS8VYWvL+HDz39sVufL28t1phHxibqN1hsO4Mx3XcrqAVlUwxMHKo5mg/6PGv8Ea/bCTj+hH9RxvTPSMBZiGnA3Vopp0HmKPUvoE6Iu6UmOuThHH1SFg4dJd2QCKvkExNAWMRQF6NeMpU8U30mTzFGNNi2wsAX9MbVoQR/x0MbOwtDB5hNRtVQv+ZYsxhEv62dZU+PYLPXUxlLtsAWix2WiyfaPZXlo5dHmkMVBHzqL+dDC2uC2vcA2z8h3mVOttzipQYuTyizOKnddZu2yQiuTvGRZZIi8Yi6a8v7L3jjTEmQ2DK18gpkWHWAHzvby5xecRbwrjCObsDROGJf++apxsfkHpReNp1ITsFQylnLll287LpXpbkhPluswwpNI9l+UXpRLWJvEiUXNPJj1rZQFNZsP6rSRNQ32K3+Zr/Y6lV+o5P444pdF1heu/28I9n+aGm7OlAh64jR8a8DecNgqOEBdPm9NhV3eOB5NDlbiRiZmVjQyBV0Vt5mr4ta5Kh7/6/zL2YKIVw5D9r+/Joeo1B4FegvaTJmbVfxXwiEYT36Hk5svO2uHcwpysCWSzeam7KIbJmE3NCZHl2yPgF62iNBa0ov8cCfTga5SX7t4kn2J7F32apmHOlvh8oV+/nO9UT8uVvQjscO7xKlbn1c4FQ5fjh6fL4PhwkWW3HT2yL5o8XViz2Qp0bT1Tk6n3dEFB+SIFGjQ9BpyqlKhlVZLxV8llyP/VxlRtN4uRJ+yKmyDIhV93QhlrF//eFUdjztLbtv8rdhz0G9B1ovxefTRGM4Mi6VCXpiOxx+8ot/0wGcG3xdjAn1qlIFBk+y4qazjpgaHutSpbHYpVR1zmEtZC8uXzUbQHWShptC2hrEPQbU4BypN10gM1OSyL+k36G/6JrsgBvuo9NkKcam47Z+VzYYCVZJAQeE0n5eEDYe/7gCnk9/CdUFTUgBKekPnurg4htoQQ+5ZmPWKYO/uRyjERGxu5ZcfiZQYwhNo8GKnukq1iv1fq9K7SCkb7vvPtRzzECyNvWW+letpIExTw/Era62q75cydIEG33SsCxFCFxpIEy3C32y3s8LBR+6viCHUYktog52BBO4KXDs5dH9Fx82WaP5lWaDB2I5Mao1gixTBPgiwNJS/uKPyywJ6+/cytZda6e9Q12LCKmPX7Eo=
*/