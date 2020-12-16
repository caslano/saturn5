
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_SEGMENTED_STACK_ALLOCATOR_H
#define BOOST_COROUTINES_SEGMENTED_STACK_ALLOCATOR_H

#include <cstddef>
#include <new>

#include <boost/config.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/stack_context.hpp>
#include <boost/coroutine/stack_traits.hpp>

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
namespace coroutines {

template< typename traitsT >
struct basic_segmented_stack_allocator
{
    typedef traitsT traits_type;

    void allocate( stack_context & ctx, std::size_t size = traits_type::minimum_size() )
    {
        void * limit = __splitstack_makecontext( size, ctx.segments_ctx, & ctx.size);
        if ( ! limit) throw std::bad_alloc();

        // ctx.size is already filled by __splitstack_makecontext
        ctx.sp = static_cast< char * >( limit) + ctx.size;

        int off = 0;
        __splitstack_block_signals_context( ctx.segments_ctx, & off, 0);
    }

    void deallocate( stack_context & ctx)
    { __splitstack_releasecontext( ctx.segments_ctx); }
};

typedef basic_segmented_stack_allocator< stack_traits > segmented_stack_allocator;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_SEGMENTED_STACK_ALLOCATOR_H

/* segmented_stack_allocator.hpp
bI+5ulu1tvZ8X+L+vwl7l8X51mlaXervxfYQVQquV+uuEtQ5rTNXtbYXsoevmr8rqfNUxxlt7T+qoR/qSH0RwyNT7M+t5e/gvzFaW2fZvmRdP/eq4dZzXcg+xPruX8m4G/i7rXWghn7ar926seNT7NMIiGix2hibd37Z2or62Pi91hHZM7jDiBbB8/OEurf0Z9s8oetbBc/PE6rYWv18Sp7QMj/rLs4T6trGeF/Oo+5pzXBvHiMXhVr4nBYKuVZ/u5cL/frv13+//vv136//fv33679f//3679d/v/779d+v//7P/8rYh1BeK6tdolXWErQ4rZ/WR0vUBmjXaMnaIO3E9fboL1Of2W3/x832rNmzlD3PHuBb5f/ZYd/dbH9qR3UPNYBeR+V4cvTwXfLIPPYgZdt3tc27zgo+1x6xN7mRvUx9IkJHIyJCdSbZnzLGfi17RMYPtEdrpWfOlQcXtKfCHqWJmfbYBN/Z/az9VqN8D0Rv+0YnyCMT7Sm0V3VB11AoVb4ek2HvUW+56k61pmfsvyrl2ZvshfnC/umXjetStYrm9hXZj7xI3r86w3OKec/Sux/vGt9ubZe2R9un7a0b9t8EsY/tlL1nFdQOtLcc7+3nm35u1z7QgnewD/p5gby972X2uPp5oVZau1SrqhXSgs8v0spq2yqc/axHBc9u4d3jb+w9eUI9gn272Bsdqw7ye58vmKteYp93P3vP06Z6f2OqfcytzEVGzn//duwD5iHWvpxq5i/We432rt3ZIKfPZS/L6XdvTd88N+d5o/PYVzZcn3L72U376/OD8cU73uvcceX2ecA5Ywjul6esfWL2mrRQKI/+0D4h+7lTnvPuYZTn2Ouy4UY1nCqOabdq92pLtTnaAu2I/eAjXoyw79celcLsv4vP3GvfbPDfcTF/o2fYZzxKXcIc927kXTzPmmgPWOvD4TP9Dubsnio5/b/Pzwe00+PInVdz/A/7sEwLfGBjlRwf2OLndm2r9p72cVHz/ed27gRahyoOADhv8zzPvu/bw7PvO1EhZKdQD5GiQpKkUimEIpRsUUJSKEmWQraK7KGUJWRPsu8tv4lKe51T59Q53xy/M/PNd++de/9zZ+Z7M3eYb79s/+5mJ/vYw0pWkPJSfNYGsb0Uo+nn3WNxP+ymWsZd5nD33NihzNWMkc2k7xprNUfbtp413sc40m7ecVxcxvu3td2j6anOLYzFi0rsIYb3afXZ4Xu817DKsTRM++3HboW8RxO8K9TLGMS7HFvrvSdgbNGrU8PcXzIWf7H7WqccZ6nEZZmxtMYmzdaeEXXdY5rpPliCMXVdvDt6zFimIeKt/52s735UjP+vzvEVXy788v4hvpdi+xdi2hQx1Y9+N6Y/xfNPYriyvXGF2rpOnyi9xb2wPsaCOjbWzzLOz/8j3KS08bnb9EtjD2ut916he3vH3fOabrzc+ObGtnt3IPZAmLbYZt7L+/tPff3y42TXSu8eGhO5KMF90jx/3NbDB9XBvc6oHMYSu6c2tM3lx9Q/3xczqb9j8sf46f+XYvjTMSqWYnd5PKWRLxfBsZvDPGhnqgzef2vonW+xCVumfPeEO/Q1Hq6zcfzGgXaq6b2kXEF7/jxmld3L3ODcnKr8r9O31O9T5ArSS5v3svPRbufpRmG/St9MmiY0z/vn8UrIe7E+7fL+1N9utXwtdWhAC4YwgZGsYger2cnlMd7rc/p6QTzF2jyG7KThhz7qe21wXjcP2jE7i/vZ9/t/65y7f9mW3PX+vA2riJOuAL/c51vJYv1lx4htOzZRL9vXV/T/wc65f3Tur3jU2EPH/MIeP0/XuF6Q9s/r+NPxfHn9fl0v29JBvac=
*/