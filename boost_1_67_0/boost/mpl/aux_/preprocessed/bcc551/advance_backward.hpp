
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