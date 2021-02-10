
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
1HOSvCDcUiWp/mzlvEzUI+50nr3/mNf3DbvNJQzHIzg6Pf0NXsObw6P3JkxIxWgBkaTVija3JpxleufPnGy3lqAfTaASSGE9AoxzJkDwtdyQhgI+FyyllaAZEAEZFWnDVvjCKpA5hTUrKIyD2cLzP5mwyVma9zj3vAWR87bIICd3FBqaUnbXwdSkkcDXiID4GRMSMVvJeGVheAqSNqXoYVQSpBAcyB1hBVlhOCIhl7IWv9t22jYFVmJnPBV2uqPCymX5pKoFZlOSe+C1BMmhFdQEZW9CyTO2VitShJt1uyqYyM19WhiwymzegKBF0cOhK6OiK4FC1LNlKkuoMXsm1SJ4JVS0Tc7LR4ZIaw+0bpsKwyEtaJdxJN6Etspoo+01EbsoPcua8mdats89A15hVjBwIvCiAayIYMKEGy++DOYx3Dhh6PjxAoILcPxFj3fl+RPUBsOoDdBt3VCBWTTAyrpgNHsU/JeedMOKL2E8D6fBLE6c8didxbF37WKmyXUExzA4OoW/2krp++0ABgVbKQHAiXV8Yh3ihnpLKBH3iaBStRpvVJVA4OgSfOfaNX6KvnwNkpWUtxI2hElW3cIaa76IZ9j45k51hGPfq0pNlBVJv2jMaOEHs8iLjFesSos2o3CmkuiEmX80dLyU
*/