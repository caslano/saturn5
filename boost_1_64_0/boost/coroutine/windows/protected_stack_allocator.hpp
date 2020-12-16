
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
tejyc8ff38ZvxOE3tzXP9abtvsR/2PZuxkpWHurdiTXGNxdP/If12NTJ+1DeD5zmOciE1sZTe+Zxjd8orZcYf1rn121qIX51uXx7484Z6z49/MdnCQfNI/T/06n9VqrudJ7m4rOEC2l92duTqvTBvXx9IIP1ixwrGZ3/d+hnmaR3B/1IpiC/MbqZFelZwuos0nqWsDKrz72D8cTuxTv+NmV3jHuWsCCHuWcJk3PK5278lFzK8Syhn3NFIs8S+ufx2bOE7nnl8yyhZ5zrgWcJt+SzfpH+kV8+zxLqFlCvRN6/jA/ye3ZQ0Nx5NV8h5XiWkKOweniWkLiI+nqWsM88wn7fUtR6zxJWF1M/NVhYXDmeJQwooX2eJVxf0nrPEkJTaApNoSk0/fvTxDC/Gcx70PtwRKKj1ZInqnLfxXPwwKUuC02MB7jHb75qsdb4nNhvK7+Dx0b5PWZ5blLP+SOdv0e7FkeZD5LG9WiUa0C9lMYHtHNOd73ZYd3uFH4Hu9ZNMy+RzbWgmrJcCwYl9V1+aZPbQD55pS3iPZn9jZTdVJn1Xf+VNSWt9K28b+MZ84xY144MyhpjO/4uOpHVNlJrSzp/F0rbPqf0BL8ZO6aV3rWmRV3pY6WVvohrb6c7pLPtQ+ozwPa6V1K2a+LGFurgurpOYOanVq9iPiu/dkHtjbFOedX7+I1QyLYjxc26GiyrYHsVPXaPUw/X5gTb6Go+Sv5JqW032ucw19QktptF+jvVNdy6eDGQbn9N1+fK2ttRLDPYVpx4KVf9DYBV3xp+G9SVT1nLE5szKp8yGikjt/po6+as2pJdPMPFg+64xCaKZnMQlxTSxqoDJTLaNynE0TyIQ6Pg+pvD90Ut59Nu6XtZ3ymPOUHe2AjfR6ubPDvMEzL7bB8dCbf9bObqOd76RlHKYqP1zciUQn1TiXUy34f5Xty6Zwh+LkiTSBk5tUWZPYOuVynoC2JWQUxu91m+KVWl8V33yIv7OoESyW3TtorkUrZ6l8mn3erT27pVabRZO2rHYrlvVmnS2zfKa6QO1ZlBjeA+V4mL/bhIA3XLaV2kGLYSd3GcVdQ+KOB720hQv0GWuzbUd5Moo4T611IHeSZFq2aEeraUt7R+a5vrrG8fqZ4xiEWnWO2Trp5ydkfKU1T5+P9L9TP1SauOeeWRLj65dkRejM+0TLYb9M8o+YL+Il0wX24b6eKwn4ZL08K6XlnUtaTvY3yOElPrDkWqa2rrs2mTdNEp1KOsctWj643yp7etXLYf4zsxibX9I8msq2ldtDYRL36OQe/FKS9Gngz6k/wnLI8nWFfb9/vNA6Mi5A9+r+YX7zq2lzboO+JfRR9Orm5i01G6TvattN6Zly7Il126pOLCkTQUUV5WMc5iOz4filOu+bQg1uzoYL/Jsy6j9kWLVyqkqa2ezayvkMN2lF0mWowai08K+cmUTjzNexGXRhwuzYfmkr5o0AcsKyNRQWmzSmdddWnKpJYv2C/aVSG3tkRcPGecSCJNPM3lVRd9+jLKSqltQTxokVR7fa4d/P0Sqx8kkd/nrgVsO432xEvnHBD8Du9V2XIQt6TyZSPo7/pYQhNx8V3QJyuI5Znh9k8i+71IEE/xopH66ROWv1/nHGKb0WIbG+xP5J1x6bhJl1Rc4i/to2B/yzulbNAu7Sebz3GZ9evgbyNx6WR5c9Bfgn3g+0ZiE5FWOXXtB+X3ta6edc5vBv44JiJ9to1UnIhSd5rJXz04l0QS4RiIE4/k6hoVxFBsg2PS8hQGifv4ZOKYVX1KOJ7UYZ11tfPalnxdI+VPJb99nhBOjHZWF/sk2lVKncOVUVpbg79VkgfHlXYG56i21nW2D3I=
*/