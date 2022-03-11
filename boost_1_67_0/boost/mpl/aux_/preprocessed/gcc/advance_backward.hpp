
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