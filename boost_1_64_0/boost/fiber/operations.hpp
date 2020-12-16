//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_THIS_FIBER_OPERATIONS_H
#define BOOST_THIS_FIBER_OPERATIONS_H

#include <chrono>

#include <boost/config.hpp> 

#include <boost/fiber/algo/algorithm.hpp>
#include <boost/fiber/context.hpp>
#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/convert.hpp>
#include <boost/fiber/fiber.hpp>
#include <boost/fiber/scheduler.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace this_fiber {

inline
fibers::fiber::id get_id() noexcept {
    return fibers::context::active()->get_id();
}

inline
void yield() noexcept {
    fibers::context::active()->yield();
}

template< typename Clock, typename Duration >
void sleep_until( std::chrono::time_point< Clock, Duration > const& sleep_time_) {
    std::chrono::steady_clock::time_point sleep_time = boost::fibers::detail::convert( sleep_time_);
    fibers::context * active_ctx = fibers::context::active();
    active_ctx->twstatus.store( static_cast< std::intptr_t >( 0), std::memory_order_release);
    active_ctx->wait_until( sleep_time);
}

template< typename Rep, typename Period >
void sleep_for( std::chrono::duration< Rep, Period > const& timeout_duration) {
    fibers::context * active_ctx = fibers::context::active();
    active_ctx->twstatus.store( static_cast< std::intptr_t >( 0), std::memory_order_release);
    active_ctx->wait_until( std::chrono::steady_clock::now() + timeout_duration);
}

template< typename PROPS >
PROPS & properties() {
    fibers::fiber_properties * props = fibers::context::active()->get_properties();
    if ( BOOST_LIKELY( nullptr == props) ) {
        // props could be nullptr if the thread's main fiber has not yet
        // yielded (not yet passed through algorithm_with_properties::
        // awakened()). Address that by yielding right now.
        yield();
        // Try again to obtain the fiber_properties subclass instance ptr.
        // Walk through the whole chain again because who knows WHAT might
        // have happened while we were yielding!
        props = fibers::context::active()->get_properties();
        // Could still be hosed if the running manager isn't a subclass of
        // algorithm_with_properties.
        BOOST_ASSERT_MSG( props, "this_fiber::properties not set");
    }
    return dynamic_cast< PROPS & >( * props );
}

}

namespace fibers {

inline
bool has_ready_fibers() noexcept {
    return boost::fibers::context::active()->get_scheduler()->has_ready_fibers();
}

template< typename SchedAlgo, typename ... Args >
void use_scheduling_algorithm( Args && ... args) noexcept {
    boost::fibers::context::active()->get_scheduler()
        ->set_algo( new SchedAlgo( std::forward< Args >( args) ... ) );
}

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_THIS_FIBER_OPERATIONS_H

/* operations.hpp
IsKuyCGlIc7hE4yh6zTXXyW8BJgDrV6yaQExOme7ErzXXyLB2/Nn9DTbSzGs7jiW85p6PuXabvxngomdjv1kW1uy8Wx2bNDoDUuO3vINFnozkqc3Vqf3Yl1S9PKs9NKSp7fzUY3eH+baw1HRZ6mosWBhO/fFrNDxZdQld1/MJALS779Z3daJ+2IGxcEfekt78GU2Rys/fkTgEDsLMTyTbVvEArqGQGNQ1zwroTrUR3AMAA9DEVzdh8B4BzNkeUygVq3gmEf0oRWHR55tDvodDgJiYLyM75/MfVo6pUsVx7j/JS51on4HtjAlnDVfbW2cfhutDaaut95cbT2cj5iivKvS73nTMF01gOK0CmfKXvSM5qe6TetiR3L+4iS7wbM4Ai7GEXAej4Bng64bxlj8DCvu7+R9YxzFoosQmdrB+ZGG1TAh/fAZG6SpgDRSRts9ovCnVHijKHyLufA7d0DhAVS7Ax/TJvRKvEyLzou6/vMH/zuhP9pKFpyuFxl+meFnkZMZOTIjR2XkQEaHNYqjz1sPNzxMmzzYQHwsd946aeIZzeaxeU3SFUJJaNcXZJl8p4Rk+dw4T22qr18sI/0ptYALcuAHPi1v8GmRYY+rE8T4CoWK5B2uIBB4Tfu9baZrzKkoOulcskh+eJLkanrWJLnqfE4qC0mrp1PRNQuoo1aGmThTiGuV0FJGkwQe+RRK4E0ogXNZAn+1XKzjhKT+msplinI3m8sNWf4fP67c4XnyZWstG06/hTaV8aYLVQv0ruqGf/xVvSMB3m2CQ+1yz3mYTZpopB9IVfI1e9WFrRdw5Q8Hm5u6ybNI2F8yjQG95QiBdhlOF6jcTlo3N5HWZUL10VKBqoAk7TBQIcjNBTGgEBvZwjjTnfI/gP3s3RgQtIP2PeYhS/sed0/y7eu3aV+/1r77U6Ose5LbdwI3yqu3xbfveVkJ2zeXUE0QqErMqBbcprdvUbW1fQNZevuuu+Enat8iceB3DWk60+83h1pyRQ7XYiyNvl/Gm+kfjJko3rlRJnYVw2gkg8qOmNXWiS1i6/c+eY3le5++Mv5796nan763S35v3r3l781pHu17P0cfqelx/t4T+SO9f6to9v6ah1dxD/Fd/q3wt4nni3Grdc2GT1yPCS7kOD37XS/XVzhAUvhNeeD3+pB5j+UgYaSj6r2/Fat3K1avjqvngupFRhnNKy1RheheusoyGsy56qtWxj443wd40x36By+KZFDZc57ajcOwdWl9zAMsD1Oo/99Fziu6xy/0f/LtDUTKqKR2HKeCU9hTJ3JaUqWE5fNFeT/WYywzF3KjPniLsHwey05IcqfxjhWCx2H0aRM7rwaNc7zSgfEIaGaZttkrj6iwnflUwHcM4KtOQ4ykgUUeEV/QO/8e5OSmRtNKuyrHOHo+pZQTFr6jTV79RV34owV0SOTPVMn7ttDoZapky81kmAWAYcYSEAGT5Z8CTaH+wMvzoLGxOw1oRGTugljPqqEx7qDulp615xfeCcbHx+4j+ePNmKfuIB+zoZgUVApYEJU52QKn5yCSHPIEIxVT6FR/vA29oiKu5AfHePtxHrHDnr2Gd5N13M6PDdtfLrQZtlfysM2xX7Bs4y2dGbYT7h/xwm3evdxwY0XDNd5OhxPRJKg6rrPKh39c3voHcK+nr5MOGvWuvlTAoT0TTtphz2RlsqqcUOon6IbcTo4yR1qyqGsXU71vY+Ok5fRcJA9bcyB1gbs3YheoxC5QyV3gWZiSVR8O3+VQTNIakdxvssyoMY22Y0UbexS0qlY+VIvoFhDdPDu6pyi6zOVQKv3jBiw92Vx6gFZ6j1lR9fjfd5ME0GfLIP8hdrs6KeZPdNk=
*/