
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
FtVeWbFWVaLVMha5RLU0p75U+mh8OFD5FKWonCCZPvQmruJBSSbudIXMbqeWWzh/zqU6xWdkw/bSrehqlUW2pSi4jNJc6yi4dMFYZ+mSLdr7DQs/b/y0ktY11Vgw+hvWb39GVFC1oW11PD9sLoR49npWsvrdo3eid2eijT/VhaZg5PuVxHe3PNZuhrkHTAjX3rcXj0k1cRYDZjYHN+FeNsbt/kJPf5ZY3AF0FBjCY0twZyLVqRUyt7F+LAwvRoMD+APYmhbT5BusrqN8M8NasCLuNhhOANuZR9hJtMTNdhSuBHxRrtkvujcAxhHMvXDXTIzm6dsXYHv7jmph+/KMe2yLCvhi0P01SmF4jsOvnLbqT4gIgPEcYdUVQ9cDbyxudl/u0bLpW7AmR8r7lx/wdM8zrrYUAFu2I+2GfYOXpeyZsM9IJTcH7wJIr+de3J0NurA1i1zgZ9H+ko2AX7KqHVEEdKVcsTbLextwru3FVGYjiZrI5I/snzTmW8IlFnpGBOjaxUsdm00dokoChJAox24L41SD8CeJ26p8JO4gIhsewySJLaO/Mnb4ikH84kQ26qJPi0Ze4M7vO4zXsGfSwFeyWY7c0Z9L9dzARGINk+i2BWdQpPSMZ0c+DtdodXgXHHf55QGPIHQ4qGdac/mLFc/7PPVDbw+WpDeFIWHZBqGxeFS3XxSnH/DMmAzIbv6U22Jo0YezFqDcju95
*/