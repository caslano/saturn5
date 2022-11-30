
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