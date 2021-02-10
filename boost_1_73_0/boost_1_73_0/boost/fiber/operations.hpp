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
e2iP4DyA8B9QSwMECgAAAAgALWdKUlyBFNgRBgAA/A0AAD0ACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1BST1hZX0lTU1VFUkNFUlRfQkxPQi4zVVQFAAG2SCRgrVZtb9s2EP6uX3HwgMEOHLlrC3R9xRxXWbw4liHJbQ0EECiJirjKoiBSedm6/747Uo7tJG3yoQ5sKRTv7rm75x7KPe/BwU/7OC65g0c/sfnG+MHrxmjRyL95qh82iONvYP/Q8ByvTwg1gq3Vt3gAT7L6Bn1jFXex3tF9HD8h3DmBpJ8RGZ/HdIsr1rKzn8j6phEXhYb+ZAC/vX79OxzC82fPnw3hI6sELyHUvEp4czGEd5lZ+aNg19eu4h+GwDWw0t1zGBVCgZK5vmINB7wvRcorxTNgCjKu0kYk+I+oQBccclFymPiL1XT+5xCuCpEWnZ8b2YIqZFtmULBLDg1Pubi0bmrWaJA5ekD/mVAafbZayMrF8Bw0b9aqc0MgWKkksEsmSpZgOKah0LpWb0ajtG1KzGSUyVSN0k0p3EKv72S1QjRrdgOy1qAltIoPgfYPYS0zkdMVS4SLdZuUQhXDLSwMWGUj2YDiZdm5Q1PBlU2BQ9hVa0g7oUb0QtNFyUpR
*/