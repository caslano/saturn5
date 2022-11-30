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
    active_ctx->wait_until( sleep_time);
}

template< typename Rep, typename Period >
void sleep_for( std::chrono::duration< Rep, Period > const& timeout_duration) {
    fibers::context * active_ctx = fibers::context::active();
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