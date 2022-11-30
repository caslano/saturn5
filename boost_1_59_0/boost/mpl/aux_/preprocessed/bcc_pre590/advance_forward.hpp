
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