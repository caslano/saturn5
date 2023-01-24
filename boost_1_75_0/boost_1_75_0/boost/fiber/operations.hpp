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
2JEn47gxdk+Wxt0UQz3TvMWzn4PWGIhnP0f7n1UpWvoa94nH+bXX/MKTRGvYz7InyYXvN2zmKsmZsPXrTPfsH6qtz5HpOftQVLdYV101ED5WRzU7Jz2JHYfdZMbdlK7reDmq00Oxi9SOPwSc2k4jFx+zmqbVseZCqLlqtbkIXXNvseZ2AYrzmv/9BG/OC82xeTrwhNbcDdQcK/bmE6I5iDIKDbE6pm1hDYVSQ2+pDcF8VEYk4OBXUfgcm9u1lp2iVwkodD6uemVdWghq8c7niP9xMnZa88r6qQ4Inc9xGIx4AmFwGvUr7gmafDYj3Z5Q10HiP9kC/7GRfjJ4+nEjjMxpAqR0/3RCSgnE7Ta2QUqAf98DbPFJBsMWGgJay6pgHFTJe4RflmCZl33LzKEyuZi32jdvPOVlvudvL5bLNogUo/e5QEqg323QKYH+Wq5zu3BzGDJDx0ORGYqIQGYoO0y4XZi1TnW7sHGD6nbBtait0fj+x/3dLlhSn12O2pe/CyXQ/3DdT5tN85AQfS0qPgqPasIVAvqoy7J70Fkc94kA9updu6Dec3+7Z1wDmvjWOmQUZE5MTOZGWaYyMOVq3qPK57vpVDw1/weP6w2SVGVnofoZofOZQGqh/iFGNN8Ic6e2iWukqYU+845QBl3/Dud/+bP4HVzAjFsm6Y2UyEQ+fFi0aqQEN7tO+RsHm9MCp6xQCCtGxx5la3qS
*/