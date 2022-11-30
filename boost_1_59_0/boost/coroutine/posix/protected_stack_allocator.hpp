
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_PROTECTED_STACK_ALLOCATOR_H
#define BOOST_COROUTINES_PROTECTED_STACK_ALLOCATOR_H

extern "C" {
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
}

#if defined(BOOST_USE_VALGRIND)
#include <valgrind/valgrind.h>
#endif

#include <cmath>
#include <cstddef>
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
struct basic_protected_stack_allocator
{
    typedef traitsT traits_type;

    void allocate( stack_context & ctx, std::size_t size = traits_type::minimum_size() )
    {
        BOOST_ASSERT( traits_type::minimum_size() <= size);
        BOOST_ASSERT( traits_type::is_unbounded() || ( traits_type::maximum_size() >= size) );

        // page at bottom will be used as guard-page
        const std::size_t pages(
            static_cast< std::size_t >( 
                std::floor(
                    static_cast< float >( size) / traits_type::page_size() ) ) );
        BOOST_ASSERT_MSG( 2 <= pages, "at least two pages must fit into stack (one page is guard-page)");
        const std::size_t size_( pages * traits_type::page_size() );
        BOOST_ASSERT( 0 != size && 0 != size_);
        BOOST_ASSERT( size_ <= size);

        // conform to POSIX.4 (POSIX.1b-1993, _POSIX_C_SOURCE=199309L)
#if defined(MAP_ANON)
        void * limit = ::mmap( 0, size_, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
#else
        void * limit = ::mmap( 0, size_, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif
        if ( MAP_FAILED == limit) throw std::bad_alloc();

        // conforming to POSIX.1-2001
#if defined(BOOST_DISABLE_ASSERTS)
        ::mprotect( limit, traits_type::page_size(), PROT_NONE);
#else
        const int result( ::mprotect( limit, traits_type::page_size(), PROT_NONE) );
        BOOST_ASSERT( 0 == result);
#endif

        ctx.size = size_;
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
        // conform to POSIX.4 (POSIX.1b-1993, _POSIX_C_SOURCE=199309L)
        ::munmap( limit, ctx.size);
    }
};

typedef basic_protected_stack_allocator< stack_traits > protected_stack_allocator;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_PROTECTED_STACK_ALLOCATOR_H

/* protected_stack_allocator.hpp
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
*/