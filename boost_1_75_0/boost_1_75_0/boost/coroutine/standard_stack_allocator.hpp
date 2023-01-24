
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_STANDARD_STACK_ALLOCATOR_H
#define BOOST_COROUTINES_STANDARD_STACK_ALLOCATOR_H

#if defined(BOOST_USE_VALGRIND)
#include <valgrind/valgrind.h>
#endif

#include <cstddef>
#include <cstdlib>
#include <new>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/stack_context.hpp>
#include <boost/coroutine/stack_traits.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {

template< typename traitsT >
struct basic_standard_stack_allocator
{
    typedef traitsT traits_type;

    void allocate( stack_context & ctx, std::size_t size = traits_type::minimum_size() )
    {
        BOOST_ASSERT( traits_type::minimum_size() <= size);
        BOOST_ASSERT( traits_type::is_unbounded() || ( traits_type::maximum_size() >= size) );

        void * limit = std::malloc( size);
        if ( ! limit) throw std::bad_alloc();

        ctx.size = size;
        ctx.sp = static_cast< char * >( limit) + ctx.size;
#if defined(BOOST_USE_VALGRIND)
        ctx.valgrind_stack_id = VALGRIND_STACK_REGISTER( ctx.sp, limit);
#endif
    }

    void deallocate( stack_context & ctx)
    {
        BOOST_ASSERT( ctx.sp);
        BOOST_ASSERT( traits_type::minimum_size() <= ctx.size);
        BOOST_ASSERT( traits_type::is_unbounded() || ( traits_type::maximum_size() >= ctx.size) );

#if defined(BOOST_USE_VALGRIND)
        VALGRIND_STACK_DEREGISTER( ctx.valgrind_stack_id);
#endif

        void * limit = static_cast< char * >( ctx.sp) - ctx.size;
        std::free( limit);
    }
};

typedef basic_standard_stack_allocator< stack_traits >  standard_stack_allocator;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_STANDARD_STACK_ALLOCATOR_H

/* standard_stack_allocator.hpp
ztutoT/kTzq7XpVc9oaTd2B0ttIYZXpXz7+VW3ywK4LDnubIYeFKub/dnfxEDhuLGWuW+3ubclyWR5IW7Bf6kbKpSAeS1HyoV1lGtoclE85D2coEOoWfuqRr5T9+hrSLO8a+9VSDqZOO/ORK6eFH7ox1fXNr0woVKJw5PVTBkP0KK4LNt2tmtJFk3WRJUAv85q2OrPCoHZgBCXYXFzoItmawc0mLRR6TT1GVCkdxVR9Cmxe2oc18tjWIG49Hxirqi2piG9Fj+K0GcnUXetUd7fFSTdzeTWUTwq6nodRuTUYHNpBnBfpdAtA5PqH16Ndd+S10Xti8sEpR7Oqi3H82+UCctSjG6iDgi3K96LPYgKjaLbvXt0GshFkhKBwDb0CGFyd+zIRnR+vLD5DLnCeHHlZdi5ntx4oXeCzTZVc58Fz4D7bpWAfqRwE78Tv+ziBQe1kBB0V73YCQWkx3X/iOvSXE/MrRWM06gndzCYFuIATyRKy4Tjzz3eJWnlV1Iao2XthVV+YXWn+qARFd/x5+Pb+M0L488UM5C5F6ccH84q2p3g+k9wDRFnmA+FO4sO2H7Bsoh8ZWi6ZqXGSNHJ5Pze0723uO75p7u1y3ZfFMtGVF/cMIHAGy7Qtu2utfV0zsVnqN775yH/ll7MO237xvMH6kYSQ6s+/8Kwco0NN0p5g70rYt8DJCB3BvMB7yYmc1FjkACriL7Dvzet/N
*/