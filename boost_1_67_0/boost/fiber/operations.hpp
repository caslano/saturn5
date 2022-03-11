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
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
*/