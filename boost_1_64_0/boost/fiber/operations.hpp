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
nKp/N/S+zZvzdqdI69GPQjT+8QRc82N+yU9s7nue1i16WcvGxMq5p9pEDeJBL+EepiQgO1knN8l00GEn9JahNE9iM6SyeG6T0dnderpC3uy+jEa33nkGMfkGcV9LSsMxGTOH0tuSEE53XgcQtiFjR31ShzQ/HwLxQxG3CnZ6mnqjQQGeRu0bl+9gsBS8qbvzPaapwiwMGz0YUvpE1miCAYwFIejE6wTRfTz/GgxjzISPwt7oxOy20iiV3M2/qz4tjEkMVPJ860RJqnYukRhTt5ldvcbGnTce5wojXG2a7jqQW4jczONxgpXOHhPv5W8kLXe0RAUeQ3j4F9FIiUWQumKYie16/AwmYDcoOuvo9br9w3iGac+Qx+t4KFDJ2bJ8lHjMc1o+oMnMrJRWC/NydXkk/rpHmCudQuHli8gD2Nlfk4YSxGnv8BgvbfodwFlCIyvLtdg4wN5zmWmxdP4vj9RdpGmCqrXmeeBjXyFiP94aC/Ilt0G+1d+PCGYddfV6DnE54OQQBqm+np/IezCowQSBFofqUqBusALcrACokJGDs6PH2xKcrhZEAw==
*/