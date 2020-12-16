
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
ucvA4C1N2Jt6+3g3jvPFJnPrTsWUn9P5xvR3rXe41AUep8XjrQG9NRwmeYDvYTRf3EfXaPVC/tq93vj6eC9d4BtPqtx5e5EWaO2Pa5vgfpN0tRnOUT1X5OyDstvRHcfzTyd43NPhfVvEcsi3wM5P91qD3bDtmfPJk0dl+qdvUzqeoze27PI6ZaTggy2fIPgnCr4r68pRQVmfLHBtU0+hsNPJFPjdMd4j3SPdYd6pQvc7ZbDHQeTVccmICZn9xdMlzRmS5o4c6yLHs59pi9MjSLR7LLCHk5wP47NifQxW2zmN4MXeum7ngmJ0/Iz1LnQisidbw1HYk21tTGWZ7c5RcCHLOg2lqw7kEQ9D/VN5c+QsKMva3PWMdeH0o+WoYTtHTTAuBzu2Owd8hNDAs8icBv3SedqmS7zStP3486Hv2TFS54BVPlnnkrJzYbS7C8vC8X8MNF8eGdwljfm5WOUXHHtf5qVGLif/NkPjMqCh8UjjCuhHtI4M7tHlfe4h+4x+Cn2DU0zf4Crg9cgEVzfMeQj22XB3ovoe9Y/gZ2bJ3YHXqu3IOhVtVG3fBG1YBiTXGf0BpOP5/jJYPxOZnEcL5Nto/Td/F4s/vZ7rk9B0eZCzATdAHqIiy+Y5M6roj8gCkFx5GEA6l4dfSh7c903GB95sbJHi2UZu8cuU06rfu83MJ90eYjt3GNuy91rcCfZJ8WwPds7mbqiDWvf2mMD2B/Ul37unLHMd+XnqQ6R9ZX6e9gXs2X+2Z/1+Gs+JU2neW4b3d/GP8TE92v59mh/BdwmtD7pf6oRr93Du8ESRk9sm+P4Of4ueoX3Avs7DQtO1ndjGTZGxN+r4MflhX+px0DHgIB7r+AkNF2TyLYL6jT76y6NBLjh7fDDc+/FsWea6wnOoH4I/X4Z+ndtW+pn7SVR+xEE8kf8l8E3fNG3BK4aP+jjk8xrhQDkQvjmDYOKZB8T/w9YHe4evlNsxohO+a6tM5APZ3zKyvw3lori6zoBh185j+CQTPt6EU4b+mRjPskn/He5tJpjoDea0yzA+ew38ExN/mtGbNzEz/iQTP8TEH2/i80281XuBiT/TpB8+0fctLqzjmaLMvn2vW+7gdRDt32t/J9GrMEpHJzJirclm6Cfv5t4CDJIz/Gl+67yrFftYxV7v+paZ06bN8LtPTHMXkmu845Pq6lHcHs+pa0Pr+lhwHwPfU8WwBL9TpDymMoz44DoPw+SdMl3nUZjZ61fr0+xLEVzPmexOCtt1Iq7zLKqNNRxYs5b2yKzhVgnCuc649Z+G68juEzPbn89RWPvL0VF+ue0xEcLif/Yj/F3om2CcB/X76s/1fr/SAtP/Jq5FRK+K0u/aT/pUvzR29UZNlHosNLAej6E4l7fLR2HemAb379Dn7wV0Di7O9LvjKA7vGbX92gkUn+tsYTN2voNg+uzGPhMD3x2RMvjQCx/nFg1onLsR+klt3v9jfOvwqnOMR2vNeLSE8tRgxqNrQsajh8l41M1rf46UWgo238561AEpf7L+cth64/wYrWcovgRxzXGi6Bn3x6TAfsqZN73vKfYzaSKMKQXvjvHc5+YftomVkmYypgEeRJvTY5opkmbfibjP3+HB2HeHY+CdvS8InakTYQzNdAY2hq6S9NMlvcZhXZoZQhvfb8F6irT3l/SzJX1BXvhYO0rxw7m8WxO8nCR29HmCFzo4A92lAH1pH70fxRVrGqoeHeu3sJ1OI3iE4ToQl7txXBmEjM9nEXyqjM81PDtkfF5tzifXmvH5HGfzzJfbFmpQAnprGE5Vri3w8buRvc8Fez9sB35jbMZ4qRfGS0mvSsZxXwR6hTuoEzgmP7g4fEw+byKExSc=
*/