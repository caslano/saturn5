
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