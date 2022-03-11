
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
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
*/