
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_PROTECTED_FIXEDSIZE_H
#define BOOST_CONTEXT_PROTECTED_FIXEDSIZE_H

extern "C" {
#include <windows.h>
}

#include <cmath>
#include <cstddef>
#include <new>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>
#include <boost/context/stack_context.hpp>
#include <boost/context/stack_traits.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {

template< typename traitsT >
class basic_protected_fixedsize_stack {
private:
    std::size_t     size_;

public:
    typedef traitsT traits_type;

    basic_protected_fixedsize_stack( std::size_t size = traits_type::default_size() ) BOOST_NOEXCEPT_OR_NOTHROW :
        size_( size) {
    }

    stack_context allocate() {
        // calculate how many pages are required
        const std::size_t pages(        
            static_cast< std::size_t >(
                std::ceil(
                    static_cast< float >( size_) / traits_type::page_size() ) ) );
        // add one page at bottom that will be used as guard-page
        const std::size_t size__ = ( pages + 1) * traits_type::page_size();

        void * vp = ::VirtualAlloc( 0, size__, MEM_COMMIT, PAGE_READWRITE);
        if ( ! vp) throw std::bad_alloc();

        DWORD old_options;
#if defined(BOOST_DISABLE_ASSERTS)
        ::VirtualProtect(
            vp, traits_type::page_size(), PAGE_READWRITE | PAGE_GUARD /*PAGE_NOACCESS*/, & old_options);
#else
        const BOOL result = ::VirtualProtect(
            vp, traits_type::page_size(), PAGE_READWRITE | PAGE_GUARD /*PAGE_NOACCESS*/, & old_options);
        BOOST_ASSERT( FALSE != result);
#endif

        stack_context sctx;
        sctx.size = size__;
        sctx.sp = static_cast< char * >( vp) + sctx.size;
        return sctx;
    }

    void deallocate( stack_context & sctx) BOOST_NOEXCEPT_OR_NOTHROW {
        BOOST_ASSERT( sctx.sp);

        void * vp = static_cast< char * >( sctx.sp) - sctx.size;
        ::VirtualFree( vp, 0, MEM_RELEASE);
    }
};

typedef basic_protected_fixedsize_stack< stack_traits > protected_fixedsize_stack;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_PROTECTED_FIXEDSIZE_H

/* protected_fixedsize_stack.hpp
dmreoWObdyNEYi0rO4xYyXYepOvUdh1te8XSvoDYMf9a3rfV6dj3gs3bAIIjR/qCeOrXAVuHS/YHb5ZWOlZgLtP6xqF3FGtSs5mw8mdDghANc0EdzFbxbdtqj9wwCMAfhmNsb2+n27T1A/8omOIKXOwemD243lTq082R8y9QSwMECgAAAAgALWdKUiuQJdK/BAAACgoAADIACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0JVRkZFUlNJWkUuM1VUBQABtkgkYK1VbXObRhD+zq/YUT9UyhBk2UndtGmnWMYJjSI0IMVxRzPMCQ5zMdzRuyOy2vS/d+9AkfIyE38ItnRo2X327dnFWw/g0Xe7HM/AwTev1H5SvPDcGy2keEcz/XWDNP0A3R8arvF8gKsxHKw+pCN4kNUHGFqrtPf13Nyn6QPcrU2Q5mtsjNepuUVJZ9nbT0Wzk+y21DCcjmDy7NnP8BhOTybnLlwSzmgFiaZ8Q+WtC89zK/mjJPf3nqK/u0A1kMr7BHBZMgVKFHpLJAW8r1hGuaI5EAU5VZlkG/zBOOiSQsEqCtNocRPOX7iwLVlW9jg70YIqRVvlUJL3FCTNKHvfwTREahAFIiB+zpRGzFYzwT10T0FTWase
*/