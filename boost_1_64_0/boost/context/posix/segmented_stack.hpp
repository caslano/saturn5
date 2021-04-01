
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_SEGMENTED_H
#define BOOST_CONTEXT_SEGMENTED_H

#include <cstddef>
#include <new>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>
#include <boost/context/stack_context.hpp>
#include <boost/context/stack_traits.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

// forward declaration for splitstack-functions defined in libgcc
extern "C" {
void *__splitstack_makecontext( std::size_t,
                                void * [BOOST_CONTEXT_SEGMENTS],
                                std::size_t *);

void __splitstack_releasecontext( void * [BOOST_CONTEXT_SEGMENTS]);

void __splitstack_resetcontext( void * [BOOST_CONTEXT_SEGMENTS]);

void __splitstack_block_signals_context( void * [BOOST_CONTEXT_SEGMENTS],
                                         int * new_value, int * old_value);
}

namespace boost {
namespace context {

template< typename traitsT >
class basic_segmented_stack {
private:
    std::size_t     size_;

public:
    typedef traitsT traits_type;

    basic_segmented_stack( std::size_t size = traits_type::default_size() ) BOOST_NOEXCEPT_OR_NOTHROW :
        size_( size) {
    }

    stack_context allocate() {
        stack_context sctx;
        void * vp = __splitstack_makecontext( size_, sctx.segments_ctx, & sctx.size);
        if ( ! vp) throw std::bad_alloc();

        // sctx.size is already filled by __splitstack_makecontext
        sctx.sp = static_cast< char * >( vp) + sctx.size;

        int off = 0;
        __splitstack_block_signals_context( sctx.segments_ctx, & off, 0);

        return sctx;
    }

    void deallocate( stack_context & sctx) BOOST_NOEXCEPT_OR_NOTHROW {
        __splitstack_releasecontext( sctx.segments_ctx);
    }
};

typedef basic_segmented_stack< stack_traits > segmented_stack;
# if defined(BOOST_USE_SEGMENTED_STACKS)
typedef segmented_stack default_stack;
# endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_SEGMENTED_H

/* segmented_stack.hpp
R2+mbEfjXMxiQG7ZsethtkpKFtWhOzP8IuLchGE53sMWVfNDZ6SXHN8P6tCm1WBljkovfo9WB9tt/9Rp4RpxzYD+BB6fRILtOleh/VXUWkYZ1OK42BCxdJ3G3TG4egx+MLw+3dROnlmxM+7kYL0Mams23bdZVBL3s0kcA5k1Ufb4Xg+Q9Zd1ikPmonxOcWaIpMMlCJid8J/jyjusp6qLm57adJORcfqfH+5kgkyTpK0K9h+ePC3wFVB2hrlnOxfFY1QRctwoOC+0asJSMTU0Oe1UeOZ5BvA6zXmYzUnWepbEl5Icph5obdwk8r1LPrNUBe2xEeGyeSLGqbC1CnTEGc7TO2APGuaFvaUHbNXBWqyBGq+cQhsDvkXB8/tdWPCLvJ+uIpjTM9lDbD7I3q3YVrh3gtcAvvX/tPTk16Q3ZSpu5BjT5074IKOYcM2zztinc57X0AjLR6FrFADPVzDWnPn1yZxkjYasONJhxIOQRn7pLv7DgMNlmeKsftONQAtUZWWN8DVA1V7D+50GwCRxoUAcqgWMgD0GFm5SHTFWIs3VdTcHxUie2CnQXw==
*/