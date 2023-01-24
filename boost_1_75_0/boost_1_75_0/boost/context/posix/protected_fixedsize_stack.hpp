
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_PROTECTED_FIXEDSIZE_H
#define BOOST_CONTEXT_PROTECTED_FIXEDSIZE_H

extern "C" {
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
}

#include <cmath>
#include <cstddef>
#include <new>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>
#include <boost/context/stack_context.hpp>
#include <boost/context/stack_traits.hpp>

#if defined(BOOST_USE_VALGRIND)
#include <valgrind/valgrind.h>
#endif

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

#if defined(BOOST_CONTEXT_USE_MAP_STACK)
        void * vp = ::mmap( 0, size__, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_STACK, -1, 0);
#elif defined(MAP_ANON)
        void * vp = ::mmap( 0, size__, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
#else
        void * vp = ::mmap( 0, size__, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif
        if ( MAP_FAILED == vp) throw std::bad_alloc();

        // conforming to POSIX.1-2001
#if defined(BOOST_DISABLE_ASSERTS)
        ::mprotect( vp, traits_type::page_size(), PROT_NONE);
#else
        const int result( ::mprotect( vp, traits_type::page_size(), PROT_NONE) );
        BOOST_ASSERT( 0 == result);
#endif

        stack_context sctx;
        sctx.size = size__;
        sctx.sp = static_cast< char * >( vp) + sctx.size;
#if defined(BOOST_USE_VALGRIND)
        sctx.valgrind_stack_id = VALGRIND_STACK_REGISTER( sctx.sp, vp);
#endif
        return sctx;
    }

    void deallocate( stack_context & sctx) BOOST_NOEXCEPT_OR_NOTHROW {
        BOOST_ASSERT( sctx.sp);

#if defined(BOOST_USE_VALGRIND)
        VALGRIND_STACK_DEREGISTER( sctx.valgrind_stack_id);
#endif

        void * vp = static_cast< char * >( sctx.sp) - sctx.size;
        // conform to POSIX.4 (POSIX.1b-1993, _POSIX_C_SOURCE=199309L)
        ::munmap( vp, sctx.size);
    }
};

typedef basic_protected_fixedsize_stack< stack_traits > protected_fixedsize_stack;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_PROTECTED_FIXEDSIZE_H

/* protected_fixedsize_stack.hpp
xt8PoGFjzoBLrF9zAO1r78EKg7ixyfV/+lHGHx9w5wcqLu1eZ7EIWwdmP/zkkLntkNpyKruL8vFHGLgT6B2PmxcouUAe30DcXKN/9M3iY2+9kjALKQ+5F94EVLyPBG2rQISUTRt3QejJ6BaOkprJZMaFC1dRSpEVGcPhkM2NdUajEX/lIxv8jZ98NwubUc4933ix5rE/ucHVq+f43GMTrr3yHJPtIb6KgLB2AgZnI0fgkOYmmF2or8Fih35/GjsBlenkN4AWl/TeM5lMjIiLttZ4j2U+4PtatwUAXFfZVSxvOOPuF0IitUSo5AJ0GjJG5U+HcAMiiRLOZF3XDLMj1C+9F3XvLsL0KBcG6SxaK0wVyj+FBhHnxIX4cPTHnYhlvwEkRCoDliEzERUFWYb/E1EipA0LH9pxCdGCQpN6mohN19zEqRAogYLoKOTAEdCQfw3x18TrY9Qgan2XfH2TCn2S2xDN/dVkH+8bnkV0XiM9dVnjjGQ46rP/J49QLAzHP/ANLu6+Ee7C6Lk4LLU1CGE4PtpA/tm7ENfO4IZzFgbWdB+r5izEFD0fEdLZ//zLex/cwwQIgMo0Wunoh/v2nMdkjG533aUlRJO0RfdzITDGsbe7z+7OHgjB81pT5Dlra0NG4zXee2aLj/9nG8BH2J8Ltm++h3/5Ncneaxf4fx4/4MWnnmUx22PhtvDuCM5ugjgFg7uhl6HGLzEc
*/