
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_PROMISE_HPP
#define BOOST_FIBERS_PROMISE_HPP

#include <algorithm>
#include <memory>
#include <utility>

#include <boost/config.hpp>
#include <boost/core/pointer_traits.hpp>

#include <boost/fiber/exceptions.hpp>
#include <boost/fiber/future/detail/shared_state.hpp>
#include <boost/fiber/future/detail/shared_state_object.hpp>
#include <boost/fiber/future/future.hpp>

namespace boost {
namespace fibers {
namespace detail {

template< typename R >
struct promise_base {
    typedef typename shared_state< R >::ptr_type   ptr_type;

    bool            obtained_{ false };
    ptr_type        future_{};

    promise_base() :
        promise_base{ std::allocator_arg, std::allocator< promise_base >{} } {
    }

    template< typename Allocator >
    promise_base( std::allocator_arg_t, Allocator alloc) {
        typedef detail::shared_state_object< R, Allocator >  object_type;
        typedef std::allocator_traits< typename object_type::allocator_type > traits_type;
        typedef pointer_traits< typename traits_type::pointer > ptrait_type;
        typename object_type::allocator_type a{ alloc };
        typename traits_type::pointer ptr{ traits_type::allocate( a, 1) };
        typename ptrait_type::element_type* p = boost::to_address(ptr);

        try {
            traits_type::construct( a, p, a);
        } catch (...) {
            traits_type::deallocate( a, ptr, 1);
            throw;
        }
        future_.reset(p);
    }

    ~promise_base() {
        if ( future_ && obtained_) {
            future_->owner_destroyed();
        }
    }

    promise_base( promise_base const&) = delete;
    promise_base & operator=( promise_base const&) = delete;

    promise_base( promise_base && other) noexcept :
        obtained_{ other.obtained_ },
        future_{ std::move( other.future_) } {
        other.obtained_ = false;
    }

    promise_base & operator=( promise_base && other) noexcept {
        if ( BOOST_LIKELY( this != & other) ) {
            promise_base tmp{ std::move( other) };
            swap( tmp);
        }
        return * this;
    }

    future< R > get_future() {
        if ( BOOST_UNLIKELY( obtained_) ) {
            throw future_already_retrieved{};
        }
        if ( BOOST_UNLIKELY( ! future_) ) {
            throw promise_uninitialized{};
        }
        obtained_ = true;
        return future< R >{ future_ };
    }

    void swap( promise_base & other) noexcept {
        std::swap( obtained_, other.obtained_);
        future_.swap( other.future_);
    }

    void set_exception( std::exception_ptr p) {
        if ( BOOST_UNLIKELY( ! future_) ) {
            throw promise_uninitialized{};
        }
        future_->set_exception( p);
    }
};

}

template< typename R >
class promise : private detail::promise_base< R > {
private:
    typedef detail::promise_base< R >  base_type;

public:
    promise() = default;

    template< typename Allocator >
    promise( std::allocator_arg_t, Allocator alloc) :
        base_type{ std::allocator_arg, alloc } {
    }

    promise( promise const&) = delete;
    promise & operator=( promise const&) = delete;

    promise( promise && other) noexcept = default;
    promise & operator=( promise && other) = default;

    void set_value( R const& value) {
        if ( BOOST_UNLIKELY( ! base_type::future_) ) {
            throw promise_uninitialized{};
        }
        base_type::future_->set_value( value);
    }

    void set_value( R && value) {
        if ( BOOST_UNLIKELY( ! base_type::future_) ) {
            throw promise_uninitialized{};
        }
        base_type::future_->set_value( std::move( value) );
    }

    void swap( promise & other) noexcept {
        base_type::swap( other);
    }

    using base_type::get_future;
    using base_type::set_exception;
};

template< typename R >
class promise< R & > : private detail::promise_base< R & > {
private:
    typedef detail::promise_base< R & >  base_type;

public:
    promise() = default;

    template< typename Allocator >
    promise( std::allocator_arg_t, Allocator alloc) :
        base_type{ std::allocator_arg, alloc } {
    }

    promise( promise const&) = delete;
    promise & operator=( promise const&) = delete;

    promise( promise && other) noexcept = default;
    promise & operator=( promise && other) noexcept = default;

    void set_value( R & value) {
        if ( BOOST_UNLIKELY( ! base_type::future_) ) {
            throw promise_uninitialized{};
        }
        base_type::future_->set_value( value);
    }

    void swap( promise & other) noexcept {
        base_type::swap( other);
    }

    using base_type::get_future;
    using base_type::set_exception;
};

template<>
class promise< void > : private detail::promise_base< void > {
private:
    typedef detail::promise_base< void >  base_type;

public:
    promise() = default;

    template< typename Allocator >
    promise( std::allocator_arg_t, Allocator alloc) :
        base_type{ std::allocator_arg, alloc } {
    }

    promise( promise const&) = delete;
    promise & operator=( promise const&) = delete;

    promise( promise && other) noexcept = default;
    promise & operator=( promise && other) noexcept = default;

    inline
    void set_value() {
        if ( BOOST_UNLIKELY( ! base_type::future_) ) {
            throw promise_uninitialized{};
        }
        base_type::future_->set_value();
    }

    inline
    void swap( promise & other) noexcept {
        base_type::swap( other);
    }

    using base_type::get_future;
    using base_type::set_exception;
};

template< typename R >
void swap( promise< R > & l, promise< R > & r) noexcept {
    l.swap( r);
}

}}

#endif // BOOST_FIBERS_PROMISE_HPP

/* promise.hpp
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
*/