
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "advance_backward.hpp" header
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