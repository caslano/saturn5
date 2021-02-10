
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
drrlBDfQmY6H/igI+96dG3Ruwv7U6wQD34NTaJycw+9lrvn9qQGNjC00AeDMOT1zjnFD/wspkatQUqVLjV9klUTgyQ147l3P2os+/wBPLIsjImJkiopSlj9gefJII0BEsmxBor8M0GTm+aPJYGI5eWL9xPIoK2MKl9p6xcj0s2WxXEGSG6Rwrd185CyGo0IJ29rZ8RE6qyBKiUAporD++QGSutj5Q+vCMtFFHJ15m4mmPoGjFAmaIU/3ZWGPMfO8DQbt6WR0e5POeDDS2taIIFEIFByD1xTmegqITfI26awnxXo+GFzD8UJwxdWqoBYePSFzF/wRyW4Zhm9gcF3qgZQgJ9/VDKXHVGFbwTwZ6DjXQeoYQ7OaJyNgCdQJrjSxm7UDVSpta5eu53+rnXOle2KXYN8dDGspkltUCJTjEZZEmOYxSeu702FgedPhEK6udIealOUk23JuT3hafzT2A7/jDydWPxiZnd4f7t1o2DOUlIooFmlEWK7Cum419yLs4FwV+wq9i4C7uGb9jQC4LvF6zThWJpSqTBI4iokicAXNXWet2vgF6rKkWUGFlXcbY7WBlnFQVJXcXUYNQzNJ/1OyLtqF9Y+1z+dqrR3XiO86R29sOwZfNjQSVeDtg78OfSY4FakT8WVbT+aj
*/