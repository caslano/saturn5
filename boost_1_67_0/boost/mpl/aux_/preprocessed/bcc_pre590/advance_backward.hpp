
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