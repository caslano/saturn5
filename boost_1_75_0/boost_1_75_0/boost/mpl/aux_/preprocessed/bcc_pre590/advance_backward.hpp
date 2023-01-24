
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "advance_backward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_backward;
template<>
struct advance_backward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_backward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_backward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_backward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_backward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef typename prior<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_backward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_backward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_backward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_backward.hpp
q5tyc0hD5yuASG72sYoo3idbIowwwukvvq9qtgAOhz49sQo/W5224zDXz7Y/TH+pBfdLLVCIf7Nl9S662ZoJYVhHnn+Ab29MYXZp3PamHDI5OfvqZ7HIeb0zXw619mfM4BHBBfs+P4Qcled3H31ZqFvPZ3WUOL6wdaCTDrxK37g2GmsTchWwXWqGflO5uH5cFfN8WF0Vw+mYhpueBiHYJL5m1ECP894fvIkKIx5nXzSJaf5eYmks4Dj+YwX2c6pVxFH0ct1lmqafBzC0oOmp3NKatiytL9uJASDlGGsTsz5+w/M+cDrr6m+L7+pEMilDkdu6yUAKui4qeB7AT1mtTz5d81aMGv1kmvognOtwPjW9xKrw6rvdoLGE9bcOAtS3ZM3Rq9Zz3zjelQqqI36NBNuhzMad75znuAhGePR9OsvX4JRmYuJS5eGFQv8/n8K8enRj0vGw28OFGLr+ElOQ3GHMPZSFaOUlZFnZJ/lQOycMyTUd4kmL46jCvhOvOMY2fGirfvrGaSddFR7Gmw+y4kyLSwNzZmvfMjPfZ6NL2piJDENpaQ8U3ztxqeexiPCeXeZ8m/nm6Mh0wWDAhJB2ZudtrRv/NX9okFhkOWlWTXHFx+ONjnFI7TanWGLUpgHMKrSaaWwVyxFOcx1majdynsWzHANWNpYV7zMjvq0/9UFUikMJXRrow9uHVfmFTA3q4a5gESaiFsaxqwPr
*/