
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
M3Hsih+WV+AelAEtnV5dJnmiuLpNpW0gL4z2GqU1K3z/p8/k4EJoN4ditAxyL5BrHxyUW5rYY8sCsgrrF0kM2Uxyy9+bVE20QDhPr9qZfxqCliaoQf7KquNDYXHKcVPf6NAKeioBHwfJtqJ1O6HPOQ1jxrItxXXf5AZ0Uh8rxy7rDStahs8S54BBuNeXeFdbXPPgrc3BSD5a1Liioisz87EzMc+59Q5Z2Snb0JbfcnK42cZ/YkOhJgs4ePZbaMMxM1O07lNseH+DlgrZky/9e2SjTJpPnW+t0xECS0rcSnafTTezT3FHzQzSor2Bu2YyA5qjqeqQf1RKuTl/8YAIaWpiJ7ZSWVAbbwWefqcXa496FmxqTbSGLnlla9WqDEnqtoKUNPxS6uRIbHA+bq9wm9LOtZQaonw66dcA/XRwDwXdVdeKhTcXZIU52nfrZ9+MT2SUQR25x2uGPv3CVJqwmTNSn69pXFUlnwkrCoLvMYWDyO93TV7rgli3S6rCkd7AVrGkpp6hDujBCzDdJRqoq7yq08MNFmfbCOwbcmcH/WbySAHDRom0rWga8g==
*/