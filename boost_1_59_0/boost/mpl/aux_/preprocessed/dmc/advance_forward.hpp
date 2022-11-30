
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