
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