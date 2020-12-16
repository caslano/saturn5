
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
3vLfFP2lOSkMTHGKFr7oZ2zhe4U5L7fwQ+8JYeBLN/nhHKR4CHESMp8gIwXk7WbIkQT5og6JS/KVdOefrBJ3pTZwBF7QyEGhollua/ynecwCDJKFP1vELHgcnYbquXRsqXFi6VoI9Mj5S6dTDjLi/GPN8tqQKX2xi9x0RAFjo5Cz84SImy0nyl1Umb4nsTKPmCuz9ABMlNvrmomTJEe9UbHCGZSZTL5SIYGs6Ym4bXNF9AwFROFs1L9uw3VIzNalUnP+wEtl7DXF3lFUuRVUuetOYOUmmiv34t+gco/WwSCJNsyGqISHebLP44ows787KJj97AditvzFkMw+Tcw+f9yG2TrI7DdRMM9F0Weo6DxRNMdc9KN3oehfoKjs5d70DCaT+RPBDjhuM3ofR9glUcTaanqVcXCIGHXs/PVFDxWmLk64D2pZzp44Rin2h/FIKTXBcZBe9EBKcwK8FRFv63+iVc/EWwTy9mUkNXuJbN0fQf6Rb5CqkCLTvycy3XcTmSJJpihApoTIXCrITDCTWfUOkFkEZDCeAsKoBZ1d2W7F8zt5zMboYfEy8dlw3RvlDhBA9SWw4lW0EMFOp5ZdhO+Gzt5M7B7+iNhdLNldHGD3bWJ32TGbVvlyP7D7XgTBHCO89znse4wDT17XXQ+TyMlTurO/5zLApRw3x3eWR436vNj615P5CvFXTvx9/yPyN8XM3xXIX1+dv7xxVfL253Mlb5eYeHvvXMkbdovh0N7p6k0xSMYILmdGVbyOon3xJtgin/B3CVU6RZVehaXvhtK864iANdjp6E/BoTPyYP4qWzCzu5LlUYfnDkqZ+hKXvmr53JR933rIRsIdXApiGwgPKGyAgI4ahrrkzbj2aAzZf643n16iKiqgubWnIlr/UxLch+l0kmnNPq6paJCAxlO8LRLUv9g7EvAoi+vuZgNLDnaBBFbAEmvQVQJGE2tQqIkGWTVKVKypRQURjKKImEBECEcCJq4oXoiAisUDBQWpcomaeBE88bbWtrEa/ddtFVGr1mP73ryZt/P/+2+yaanQlv3E/P/MvGPmfzPz5s2bN0EgivcTwL0T0CiUdtYHYno4WsTZL9nc1yWieO8PjHCk/Z0opYlxG8c9atNMZQiqxcBu/DNxTFesErGBRGzdVxqxOiDG0zq1zuaDqVxDrFzQ+A2UYxb0ntlg7pkN3DPfB0VPV0h4iKwScDsl3NjIOLG5D7pbbX/xRFvxleKY8maoK5U63Ph6A/Xin73TZrmM9ZdyIp7H16geirYKzOZbqscSVycjV6wahZDvybJ5jqdq3/Cl1jwXwGwuW6WUsqdyNsb2xGw6FQdKKI9eX4OCyFL9CbwQU62kN8595p3/0yge+357y09bVYgYPt/BcEGhFT75IEuFVmjluAmW5US+6s8OJ6v6IZeYoM74nFX9OTxBrXlBKOzzutBoDVC6qr+IIPcTkDPMkFMJMgiQxklo1OSQCxJ4MQG/txOBS8zARxJwOpOV+vtBb9FkQIn6OqFI3UyVXTUY//T21pdAAXyEJcNWBz36qw7CP/t561HPC+/vYvykpuJcG863pKqcsZxoVs15aT3a8DbZLLZXUUW/+MymomVgQw33To0jGFDBE33hu5xxub54yrc8aUP5EaJ8pR3l17YD5eVuG9xM+WBnUg0Bq60+WTL2lLUa4qtNeQNXXdnVQ1UuBvWqGkRL8g/QeMySaQXfVpwjdMPl1kw8NnRXLxuqHKnsH6+3Q/XSdqj6iKpaTeygRiz8lFYTpkZc2AKNeFaKumnBW7/BaX+ZF00jUwbSbVzehY20FpDpDQOpIuUqVq0whzfTmzTbDoLqqJhpHieVLy5VxyeLOaQ=
*/