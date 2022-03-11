
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