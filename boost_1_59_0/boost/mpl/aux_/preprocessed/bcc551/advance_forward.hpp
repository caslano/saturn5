
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_forward.hpp" header
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