
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