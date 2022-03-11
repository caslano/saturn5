
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