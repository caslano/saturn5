
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_PROTECTED_STACK_ALLOCATOR_H
#define BOOST_COROUTINES_PROTECTED_STACK_ALLOCATOR_H

extern "C" {
#include <windows.h>
}

#include <cmath>
#include <cstddef>
#include <new>

#include <boost/config.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/stack_traits.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {

struct stack_context;

template< typename traitsT >
struct basic_protected_stack_allocator
{
    typedef traitsT traits_type;

    void allocate( stack_context & ctx, std::size_t size)
    {
        BOOST_ASSERT( traits_type::minimum_size() <= size);
        BOOST_ASSERT( traits_type::is_unbounded() || ( traits_type::maximum_size() >= size) );

        // page at bottom will be used as guard-page
        const std::size_t pages(
            static_cast< std::size_t >( 
                std::floor(
                    static_cast< float >( size) / traits_type::page_size() ) ) );
        BOOST_ASSERT_MSG( 2 <= pages, "at least two pages must fit into stack (one page is guard-page)");
        const std::size_t size_ = pages * traits_type::page_size();
        BOOST_ASSERT( 0 != size && 0 != size_);

        void * limit = ::VirtualAlloc( 0, size_, MEM_COMMIT, PAGE_READWRITE);
        if ( ! limit) throw std::bad_alloc();

        DWORD old_options;
#if defined(BOOST_DISABLE_ASSERTS)
        ::VirtualProtect(
            limit, traits_type::page_size(), PAGE_READWRITE | PAGE_GUARD /*PAGE_NOACCESS*/, & old_options);
#else
        const BOOL result = ::VirtualProtect(
            limit, traits_type::page_size(), PAGE_READWRITE | PAGE_GUARD /*PAGE_NOACCESS*/, & old_options);
        BOOST_ASSERT( FALSE != result);
#endif

        ctx.size = size_;
        ctx.sp = static_cast< char * >( limit) + ctx.size;
    }

    void deallocate( stack_context & ctx)
    {
        BOOST_ASSERT( ctx.sp);
        BOOST_ASSERT( traits_type::minimum_size() <= ctx.size);
        BOOST_ASSERT( traits_type::is_unbounded() || ( traits_type::maximum_size() >= ctx.size) );

        void * limit = static_cast< char * >( ctx.sp) - ctx.size;
        ::VirtualFree( limit, 0, MEM_RELEASE);
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