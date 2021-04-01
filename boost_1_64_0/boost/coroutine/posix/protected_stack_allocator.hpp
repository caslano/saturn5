
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
pynxQ1rTFyJCMmNII5H6uUHH2X+PeOaOjdQ11PIqyVM0zpMpNYq/9m59Bgh1sLbRDxTs0FxJGD5ERHB4hwk7rkykOYJxrThGfgHU9Dloy0ouUmRPasUV0e59KKgWUb0tmxyAnMOdNXu0scKsHdy9iImYH+L7hp1v34nh5A1QkI2vLu9Oed0SV5GDAMOW0DkRcO7uUSxMXMbUyAqljpi9Vd22qAhHHmzHxGYyrX0Yqiah5SQ3ZYDzQKf8e2MRjboBUu+HF5GyCH1q8vhPKPQypnZRcHSVTp+cKpcxuENtIhKt02gzDoyFs+2n0ihia03tgeARde/fli5X/HFbkgzEMVj4IN/epu3E8eDae3Zyz4bEYe0dDMHeJlMMruv2YNIdco+6ZZHc+HybSzTqWHnLP+FBaitn3irwFL5idUgwQd3bnUVA3UgeQdYXnjxTOnJ39F9hG+VPfbI5ueF48KPUkmE7oGC73d7QAEaJGN5fXMKsqSvtFM4xhlg2ZHOTr1tWJh3o3LCjYISJY6+GNoPOte7nGqLGZ7Ctsujz9oSWFwKRHcHDHtrzFqZxaA==
*/