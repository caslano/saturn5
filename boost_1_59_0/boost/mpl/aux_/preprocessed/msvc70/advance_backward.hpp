
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