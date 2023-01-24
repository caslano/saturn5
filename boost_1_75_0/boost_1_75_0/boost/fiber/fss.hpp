
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
HpANT3qekurhtM9VyJZGqQYKyJNiWrmW1sA/vZM+ZbyWU+FJEylJYUmbeZKFkjYDTrKR672llVTZZkPTrNB2CA3sOARDjy1ECBcmwvVHD0Rwc8YTtZkZzqnNsjJ1vheUifm+q0zM94wyMd/ZZep8jykT851RJub7ujLf+V72Mgxhmn6+51CSfr5zKEk/31ZK0s/3YErSz/e0APM9LcB8n3oJP9XP93eUpJ/vzyhJzLep5DyavUyrbPpVR9QzBGXBSb+LT/pn7RKUs06a7+kMVzWNPAlX0e1xCP4VbOMVXAYVhLAKiFUEJrYGmVixtx4nqKjx51Hv5K3UtcuHTOANXY0jJr6UTc37L8ZJoknfIwbLfOJFLgDV1n0lJenXfQEl6dc9l5L06+6kJP26D6Mkbd1BeNp23eFKyn/dvS/gp/p1/4mS9Ot+jJK0fUbXd1DZYIb/nWgjdMdddD0K1NO24iM4eaiX69PRt+qaXXQjupI/L6+OkQ6An4Jqeo/j7935+3Re7vxeSj+5l95H8fQbd1H6vz7i+n+8XC0vt5c/d/Ln+/zZiX93fid7p8va33dyvUr+lHlVx/n7Yv7pAp4+hz9n8fQpe+n2/1bsSp0yHp4WdmAYxfs2jBe47iN6XisKXMYL9OI1RvNnF/68bSd9cG4P1fzHHv7hT3vow8aPqcCXvMBhUWA/L7DrY3pu4c+3PqaaX+Hvz/H3p3j5
*/