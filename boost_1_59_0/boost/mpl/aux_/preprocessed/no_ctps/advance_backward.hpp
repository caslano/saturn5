
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