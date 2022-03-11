
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