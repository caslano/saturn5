
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_FIXEDSIZE_H
#define BOOST_CONTEXT_FIXEDSIZE_H

#include <cstddef>
#include <cstdlib>
#include <new>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>
#include <boost/context/stack_context.hpp>
#include <boost/context/stack_traits.hpp>

#if defined(BOOST_CONTEXT_USE_MAP_STACK)
extern "C" {
#include <sys/mman.h>
}
#endif

#if defined(BOOST_USE_VALGRIND)
#include <valgrind/valgrind.h>
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {

template< typename traitsT >
class basic_fixedsize_stack {
private:
    std::size_t     size_;

public:
    typedef traitsT traits_type;

    basic_fixedsize_stack( std::size_t size = traits_type::default_size() ) BOOST_NOEXCEPT_OR_NOTHROW :
        size_( size) {
    }

    stack_context allocate() {
#if defined(BOOST_CONTEXT_USE_MAP_STACK)
        void * vp = ::mmap( 0, size_, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_STACK, -1, 0);
        if ( vp == MAP_FAILED) {
            throw std::bad_alloc();
        }
#else
        void * vp = std::malloc( size_);
        if ( ! vp) {
            throw std::bad_alloc();
        }
#endif
        stack_context sctx;
        sctx.size = size_;
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
#if defined(BOOST_CONTEXT_USE_MAP_STACK)
        ::munmap( vp, sctx.size);
#else
        std::free( vp);
#endif
    }
};

typedef basic_fixedsize_stack< stack_traits >  fixedsize_stack;
# if ! defined(BOOST_USE_SEGMENTED_STACKS)
typedef fixedsize_stack default_stack;
# endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_FIXEDSIZE_H

/* fixedsize_stack.hpp
YjMzt1TlS3t776/l4V4Vv6PYZvwQVaddajzIN7Y5l1OHtqzl7Xm2bmY49yOyMaH+zUP9yvm7QwOCQkL8I3z9QnqH1AtpHNIgpEvIGJZbV0uvh9RhZfWAAPt633q7abO8qZ45G59sRwdVryy23Ed8LmOF8k3l22iI4z7iMYNVnPdKb49aW9w87ukgv6N/KO8gC3U5rkUtxz2Z1Fdtp/0Y6DrO9xjXTt9VTud74ouBlyLxyRhi
*/