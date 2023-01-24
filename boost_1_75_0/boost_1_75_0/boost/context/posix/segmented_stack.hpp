
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
eMrFLCmGyA+nVnMSrbWvqkqK5aQEC0yB77sMOK3bAgAe+4cPvH587U+fy5y5HwRKa5RQWGzjBizFkNOTp2n15AiyWFWOfu6wW9e5Mn2du1zo7IuBXIYmIyaGz4R2hB7T0ZR3RGGXQcBdLPjpEJPCdkhKKZobrQGp1KsuVRCllOboroTj9slgiKQgjRJuJ/qEUEEi7BJI+CTUtjX5vSMKf2Dqg9YXbSFQIgd9xwBULKvT7G+sE7jFEvBg6prp3DLsb1I+9sOsZT2Kd/xfHEwn5CLHeUeWO+4+vkmPnPnVO9h/6W50IZnPZuSjIrgZ45tYWXJcjBkN3h4H0NXyt2h8olsgQhFTXVZYbSnyHJ1lyGj+t0NEWBLuLngslwO395cAhG5FQwBVXbN9c5dr2ze58Nrr6Dwn05rBoMdoNODnPpDR+7Ehv/g370H6B9idC65ctWxv7/HqJcXB7jX+7z/Jef1bl7n/1JyiOMFs1vw6ly6Cc85nWYYQwsdhICFnOHzuhBA38jyv+QtatwUAcOVR++BHf/uN5594nt6mDyScVvg6msWwdEeI6H83hTjETK1IlzgsshqyMT7CbONV1udnEFJga0+RBUGytQ3aXnmkViAFWa7CPaLi+G4bhNzjkDKZ/J0aABV8+GQFtFaLwwsfYuAugEHo5yKaOzoItesq4jYaYIMFEfr8J25ANJo8ZPaFzxPLnwQ9Ff2kZCEX
*/