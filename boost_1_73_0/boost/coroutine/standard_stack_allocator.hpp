
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
+HzuM/M0vgtgPfg7jfdCvV9dqvH/QdvpH+FRcJG2V65reen8EeznU17Nub8HYEvYHraGXWAH2A22g4fC9rCv2Os4ZEfnMSTvEm5XXQ/mHFcFCBcuhhF4DWwAr4WN4HXwQLgU9oI3wyPgLXAY3A5HwS/g8fA2OA7eDifp9Xy9XgDvhHPgXXAevAfOh/fC38GH4Q3wMXgjXA2XaTh3ajh3wWfg3XAtXAufhc/B5+Am+Dz8CL4A
*/