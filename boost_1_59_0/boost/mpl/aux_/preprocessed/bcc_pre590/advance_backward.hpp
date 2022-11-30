
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