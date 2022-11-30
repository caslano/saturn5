
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