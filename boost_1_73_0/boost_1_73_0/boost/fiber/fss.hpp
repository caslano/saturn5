
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
fwUAAGwMAAA4AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9QUk9YWV9JU1NVRVJDRVJULjNVVAUAAbZIJGCtVm1v2zYQ/q5fcfC+JIEj9w3o2nXFVFdZvDiWIcltDQQQaImKuMikIFJ5wbr/vjtSju22WfKhDhzK57vn3p472r8YwNFPe3k+wcGjr8y+M3zhuTGat+pvnpsfG2TZV3B/aHiB5xNcjWBr9TU7hCdZfYUDa5X1vt7Rc5Y9wd0FBUn/RmR8kdEjSpxlbz9WzV0rLisDB+NDeP7mza9wDC+evXg2hI9MCl5DYrhc8fZyCO8KK/mjYre3vubvh8ANsNrfA0wroUGr0tywlgM+1yLnUvMCmIaC67wVK/wgJJiKQylqDuNovpzM/hzCTSXyqse5Ux3oSnV1ARW75tDynItrB9Ow1oAqEQHxC6ENYnZGKOmjew6Gt2vdw1AQrNYK2DUTNVuhO2agMqbRb0ejvGtrzGRUqFyP8k0p/Mqsv8lqidGs2R2oxoBR0Gk+BNIfwloVoqQTS4TCplvVQlfDbVjoUBYj1YLmdd3Doang2qXAIemrNSRNaDB6YejQSmrydlOp9Z4ilrUHKrtWojssC+oVCgs/hE4WvLX6thAbL32V
*/