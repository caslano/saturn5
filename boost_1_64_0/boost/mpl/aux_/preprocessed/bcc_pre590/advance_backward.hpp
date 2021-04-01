
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
CC9RtEv8lUEh959zVH9RehqUA6NJ8A7SNqGJJ31+4QAaOAKH0/h18D0eAxSQH0pLPtyElLXirvQX4U7mCqui+6TfLnJ8FDuiWctEzYs95Jez/UASlWPr+rTnTaTordjA2FwZs4LtMe8KRJ3N7JFwRVfzHPDnuiI2B7VLOKJJB5Hbw+6NTgyd5O7sQ0Ez44BT1S9zD072cg5NCa+Hj+Nh1RRfKURZN4Oxdw5Y3KR0+vjl8u11jqCLGetQrmNyPPABVlC4BPQ/+qLSmhE/TzlkbjEzxvgRPCh9TFmbKdiF/+wBf7K5kTj1VG54nQLJ7E1i52OFHpJ0beZSJ5L/1g4/9lJm/OnB/tZQEqr47wCvjsw4d4+/0I9eaaWcEmYPqoVKagQdwV68YvoPlxNlon+2mSckeEFuDOTc6xbQJRxPBrKJVS69ThNbpZl92fnPsDjY7gpqT1YC54e/yicUiZvmg1ViQjbaTLJxvB6x/AnF5dUPAaMBmCOMz3f2C5a2zF7RSLbc8F1EQUfslPRKHRF1MBEwJ2QsG94ejKgSpIqxsSwJsLzr0rG7+k8KKA==
*/