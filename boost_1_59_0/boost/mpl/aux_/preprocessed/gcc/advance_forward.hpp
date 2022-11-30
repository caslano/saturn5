
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