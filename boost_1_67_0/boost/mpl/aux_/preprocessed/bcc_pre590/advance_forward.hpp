
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