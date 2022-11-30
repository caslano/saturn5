
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