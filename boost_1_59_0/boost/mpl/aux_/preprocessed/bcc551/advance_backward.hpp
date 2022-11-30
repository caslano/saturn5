
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_backward.hpp" header
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
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
*/