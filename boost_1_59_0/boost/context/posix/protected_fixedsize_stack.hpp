
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
#include <boost/core/ignore_unused.hpp>

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
        const std::size_t pages = (size_ + traits_type::page_size() - 1) / traits_type::page_size();
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
        const int result( ::mprotect( vp, traits_type::page_size(), PROT_NONE) );
        boost::ignore_unused(result);
        BOOST_ASSERT( 0 == result);

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