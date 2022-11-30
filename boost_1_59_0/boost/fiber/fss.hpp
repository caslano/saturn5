
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
//          based on tss.hpp from boost.thread

#ifndef BOOST_FIBERS_FSS_H
#define BOOST_FIBERS_FSS_H

#include <boost/config.hpp>

#include <boost/fiber/context.hpp>
#include <boost/fiber/detail/fss.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

template< typename T >
class fiber_specific_ptr {
private:
    struct default_cleanup_function : public detail::fss_cleanup_function {
        void operator()( void * data) noexcept override {
            delete static_cast< T * >( data);
        }
    };

    struct custom_cleanup_function : public detail::fss_cleanup_function {
        void (*fn)(T*);

        explicit custom_cleanup_function( void(*fn_)(T*) ) noexcept :
            fn{ fn_ } {
        }

        void operator()( void * data) override {
            if ( BOOST_LIKELY( nullptr != fn) ) {
                fn( static_cast< T * >( data) );
            }
        }
    };

    detail::fss_cleanup_function::ptr_t cleanup_fn_;

public:
    using element_type = T;

    fiber_specific_ptr() :
        cleanup_fn_{ new default_cleanup_function() } {
    }

    explicit fiber_specific_ptr( void(*fn)(T*) ) :
        cleanup_fn_{ new custom_cleanup_function( fn) } {
    }

    ~fiber_specific_ptr() {
        context * active_ctx = context::active();
        if ( nullptr != active_ctx) {
            active_ctx->set_fss_data(
                this, cleanup_fn_, nullptr, true);
        }
    }

    fiber_specific_ptr( fiber_specific_ptr const&) = delete;
    fiber_specific_ptr & operator=( fiber_specific_ptr const&) = delete;

    T * get() const noexcept {
        BOOST_ASSERT( context::active() );
        void * vp = context::active()->get_fss_data( this);
        return static_cast< T * >( vp);
    }

    T * operator->() const noexcept {
        return get();
    }

    T & operator*() const noexcept {
        return * get();
    }

    T * release() {
        T * tmp = get();
        context::active()->set_fss_data(
            this, cleanup_fn_, nullptr, false);
        return tmp;
    }

    void reset( T * t) {
        T * c = get();
        if ( BOOST_LIKELY( c != t) ) {
            context::active()->set_fss_data(
                this, cleanup_fn_, t, true);
        }
    }
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif //  BOOST_FIBERS_FSS_H

/* fss.hpp
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
*/