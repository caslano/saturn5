
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
mfP7/beV91hA14oeEJ8WZIRGTDpRIhaABxgIohUZhlTpaFuRPOe6fhY93Kx1j3DQgzaNwFKsRXvm4E5LETfUyb4UalXD50zTmtP++8ba2krin/Y+44Gtzb5f6y6QOh7qs0FZOBV6j+fzjHnlqo7K5MjzqwF6RBhzwaI/PTbSEzs4p/UZl7sKEcIeIBxyZniGa6HlII5OJMf1Ta5Zz22p8g11h47baujfoRqxKs6wuo9VCcBNs4c8BFEzSnVElLUoLaZFoF1jyTG5zybaLZ0XuWKPQHw6/HYRC0IK7doT375lTfGl4wI8Gx4dDFTcmPIQBNIU723Psx5wsQIaBU9PeymcfFAZ4GBp/2bCWX7BCnHb8wyV/c091APts3790fF34GrUk7CfGeE5BJcEQRcLI+juFX3cF8hdYwlrj5UjqS8Ui4uGuuqJdyHWfkVU0qtusdYAh/WOMcYxYuq/+RlLHR7l4TxNJo178dSdnbGASD7qR0aEAhA50PwEVxuwojtGFPdqPMgGI8vltjtRh3ZBG/EsdWu1/CR3KK6/Ni86NZC2YAoHNweyfwFZwg==
*/