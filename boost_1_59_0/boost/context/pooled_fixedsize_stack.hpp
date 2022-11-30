
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_POOLED_pooled_fixedsize_H
#define BOOST_CONTEXT_POOLED_pooled_fixedsize_H

#include <atomic>
#include <cstddef>
#include <cstdlib>
#include <new>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/pool/pool.hpp>

#include <boost/context/detail/config.hpp>
#include <boost/context/stack_context.hpp>
#include <boost/context/stack_traits.hpp>

#if defined(BOOST_CONTEXT_USE_MAP_STACK)
extern "C" {
#include <sys/mman.h>
#include <stdlib.h>
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

#if defined(BOOST_CONTEXT_USE_MAP_STACK)
namespace detail {
template< typename traitsT >
struct map_stack_allocator {
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    static char * malloc( const size_type bytes) {
        void * block;
        if ( ::posix_memalign( &block, traitsT::page_size(), bytes) != 0) {
            return 0;
        }
        if ( mmap( block, bytes, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_FIXED | MAP_STACK, -1, 0) == MAP_FAILED) {
            std::free( block);
            return 0;
        }
        return reinterpret_cast< char * >( block);
    }
    static void free( char * const block) {
        std::free( block);
    }
};
}
#endif

template< typename traitsT >
class basic_pooled_fixedsize_stack {
private:
    class storage {
    private:
        std::atomic< std::size_t >                                  use_count_;
        std::size_t                                                 stack_size_;
#if defined(BOOST_CONTEXT_USE_MAP_STACK)
        boost::pool< detail::map_stack_allocator< traitsT > >       storage_;
#else
        boost::pool< boost::default_user_allocator_malloc_free >    storage_;
#endif

    public:
        storage( std::size_t stack_size, std::size_t next_size, std::size_t max_size) :
                use_count_( 0),
                stack_size_( stack_size),
                storage_( stack_size, next_size, max_size) {
            BOOST_ASSERT( traits_type::is_unbounded() || ( traits_type::maximum_size() >= stack_size_) );
        }

        stack_context allocate() {
            void * vp = storage_.malloc();
            if ( ! vp) {
                throw std::bad_alloc();
            }
            stack_context sctx;
            sctx.size = stack_size_;
            sctx.sp = static_cast< char * >( vp) + sctx.size;
#if defined(BOOST_USE_VALGRIND)
            sctx.valgrind_stack_id = VALGRIND_STACK_REGISTER( sctx.sp, vp);
#endif
            return sctx;
        }

        void deallocate( stack_context & sctx) BOOST_NOEXCEPT_OR_NOTHROW {
            BOOST_ASSERT( sctx.sp);
            BOOST_ASSERT( traits_type::is_unbounded() || ( traits_type::maximum_size() >= sctx.size) );

#if defined(BOOST_USE_VALGRIND)
            VALGRIND_STACK_DEREGISTER( sctx.valgrind_stack_id);
#endif
            void * vp = static_cast< char * >( sctx.sp) - sctx.size;
            storage_.free( vp);
        }

        friend void intrusive_ptr_add_ref( storage * s) noexcept {
            ++s->use_count_;
        }

        friend void intrusive_ptr_release( storage * s) noexcept {
            if ( 0 == --s->use_count_) {
                delete s;
            }
        }
    };

    intrusive_ptr< storage >    storage_;

public:
    typedef traitsT traits_type;

    basic_pooled_fixedsize_stack( std::size_t stack_size = traits_type::default_size(),
                           std::size_t next_size = 32,
                           std::size_t max_size = 0) BOOST_NOEXCEPT_OR_NOTHROW :
        storage_( new storage( stack_size, next_size, max_size) ) {
    }

    stack_context allocate() {
        return storage_->allocate();
    }

    void deallocate( stack_context & sctx) BOOST_NOEXCEPT_OR_NOTHROW {
        storage_->deallocate( sctx);
    }
};

typedef basic_pooled_fixedsize_stack< stack_traits >  pooled_fixedsize_stack;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_POOLED_pooled_fixedsize_H

/* pooled_fixedsize_stack.hpp
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
*/