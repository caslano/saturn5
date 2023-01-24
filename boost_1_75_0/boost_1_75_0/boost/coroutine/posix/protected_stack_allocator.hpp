
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
6WR+hRMzRUM/3DDBiRHhiHAIEzaxKjMhMXztx88Pg8Qmr0k+yJDwY278ELQCBn/CA0J2EcS7fLt/2X27+9rk1SXNrggTi5fqtr/+vuoOQnDXe5ByUFftvLeSQ9sUb01oMCocvJ01LB4Thm2C7aw2r+fVQvLIke6pJJ9s7a6c/utvKd1OsmRYkMVSOXZyslSNOTVn0bQ8mb+JUk/gZuePLjkCYMWMsmJXmvZttJgNlUC5NSRLzF99fFVD4c9McH2Y/do861WzTUxZKiykfNlb4zO9QEN52XEiyWftiTZoUoY3u4k+nbaL9zwAaAotdygJmxx9FrR43aAHTHBv4J/UFGg2nioiKnMtiASGStd/Zh4JyyYvulHTBGu6CuSfxa5ZU9w/sLwa5ZnpNKee80thZ3a0mOY5LLRxbRt9W187E9fRxj85VRbbGWLxtVkjvIwiyW+KW45MUFMlrS8rXKg6g5xDvBKa6G2uDqzUBawy5+tw0A9dYM0PLBXNRqTKm+xKllEXe6LJu41rubSRMk/BL06SAGUCMP7JjFF2V7uVmY/svjwlrEnRipzqq+NuKwSJC3KCa5G7OlzHGOymZsWaGgmFBvEbSjeDvBWU+odFY06rFI2jnWXTCn9BPOKOL55JVIk6TLD+4frV+LCPf/CVHgm2aTefg3nbZFUXwn9gAzFQD/6NK9s+t2Ol+naD9/6miHTnU2dJh/A6KYwA
*/