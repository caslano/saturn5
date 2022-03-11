
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