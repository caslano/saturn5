
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

    promise( promise && other) = default;
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

    promise( promise && other) = default;
    promise & operator=( promise && other) = default;

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

    promise( promise && other)  = default;
    promise & operator=( promise && other) = default;

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