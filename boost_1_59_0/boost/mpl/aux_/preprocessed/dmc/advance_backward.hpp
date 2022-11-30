
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