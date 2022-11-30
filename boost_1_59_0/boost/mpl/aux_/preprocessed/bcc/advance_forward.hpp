
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "advance_forward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_forward;
template<>
struct advance_forward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_forward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_forward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_forward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_forward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef typename next<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_forward.hpp
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
*/